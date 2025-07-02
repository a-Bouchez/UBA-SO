/*
    Se desea escribir un driver para la famosa impresora Headaches Persistent.

    El manual del controlador indica que para comenzar una impresión, se debe:
      - Ingresar en el registro de 32 bits LOC_TEXT_POINTER la dirección de memoria donde
        empieza el buffer que contiene el string a imprimir.
      - Ingresar en el registro de 32 bits LOC_TEXT_SIZE la cantidad de caracteres que se deben
        leer del buffer.
      - Colocar la constante START en el registro LOC_CTRL.

    En este momento:
      - Si la impresora detecta que no hay suficiente tinta para comenzar, escribirá rápidamente
        el valor LOW_INK en el registro LOC_CTRL y el valor READY en el registro LOC_STATUS.
      - Caso contrario, la impresora comenzará la impresión, escribiendo el valor PRINTING en el
        registro LOC_CTRL y el valor BUSY en el registro LOC_STATUS.
      - Al terminar, la impresora escribirá el valor FINISHED en LOC_CTRL y READY en LOC_STATUS.

    Un problema a tener en cuenta es que, por la mala calidad del hardware, estas impresoras suelen
    detectar erróneamente bajo nivel de tinta. Sin embargo, el fabricante asegura que:
        “alcanza con probar hasta 5 veces para saber con certeza si hay o no nivel bajo de tinta”.

    El controlador soporta además el uso de interrupciones:
      - HP_LOW_INK_INT: se lanza cuando la impresora detecta que hay nivel bajo de tinta.
      - HP_FINISHED_INT: se lanza al terminar una impresión.

    Se pide implementar las funciones:
      - int driver_init()
      - int driver_remove()
      - int driver_write()

    Piense cuidadosamente si conviene utilizar polling, interrupciones o una mezcla de ambos.
    Justifique la elección. Además, debe asegurarse de que el código no cause condiciones de carrera.
    Las impresiones deben ser bloqueantes. No hace falta implementar spooling.
*/

extern int LOC_TEXT_POINTER;
extern int LOC_TEXT_SIZE;
extern int LOC_CTRL;
extern int LOW_INK;
extern int READY;
extern int LOC_STATUS;
extern int PRINTING;
extern int BUSY;
extern int FINISHED;
extern int HP_LOW_INK_INT;
extern int HP_FINISHED_INT;
extern int IO_OK;
extern int IO_ERROR;
extern int STRING_LEN;

typedef semaphore;
typedef aotmic_int;
typedef uint32_t;

semaphore mutex;
semaphore finished_sem;
aotmic_int low_ink_bool;

int driver_init() {
  request_irq(HP_LOW_INK_INT, low_ink_handler);
  request_irq(HP_FINISHED_INT, finished_handler);
  sema_init(&finished_sem,0);
  sema_init(&mutex,1);
  return IO_OK;
}

// quise hacerlo con este handler y no pude 
void low_ink_handler(int sig) {
  atomic_inc(&low_ink_bool);
}

void finished_handler(int sig) {
  sema_signal(&finished_sem);
}

int driver_remove() {
  free_irq(HP_LOW_INK_INT);
  free_irq(HP_FINISHED_INT);
  return IO_OK;
}

int driver_write(void *udata) {
  sema_wait(&mutex);

  // copiamos el buffer del que vamos a leer 
  void* kdata = kmalloc(sizeof(uint32_t));
  copy_from_user(kdata, udata, sizeof(uint32_t));
  
  // arrancamos a cargar todo 
  OUT(LOC_TEXT_POINTER, (uint32_t) kdata);        // pasamos a dodne apuenta el buffer
  OUT(LOC_TEXT_SIZE, STRING_LEN);                 // tamaño de lo que queremos escribir, no me lo dieron así qeu definí alguno 
  OUT(LOC_CTRL,READY);                            // tamos ready

  // parece que tan ready no estabamos
  if (low_ink_bool == 1)
  {
    // vamos a probar 5 veces para ver si está con poca tinta o no
    int num_errors=1;   // lo pongo en 1 porque la primera la probé afuera
    int printer_status;
    while (num_errors <5)
    {
      // si está imprimiendo me las tomo
      if ((printer_status = IN(LOC_CTRL)) == PRINTING)
      {
        break;
      }
      OUT(LOC_CTRL,READY);    // el que la sigue la consifue
      num_errors++;
    }

    if (num_errors == 5)
    {
      // ggs no hay tinta
      kfree(kdata);
      sema_signal(mutex);
      return IO_ERROR;
    }  
  }

  // terminamos de imprimir
  sema_wait(&finished_sem);
  
  // le devolvemos a dios lo suyo
  kfree(kdata);
  sema_signal(&mutex);
  return IO_OK;
}