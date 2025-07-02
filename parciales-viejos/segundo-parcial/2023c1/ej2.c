/*
    i) el ventilador tiene que funcionar siemrpe asi que le pondría interrupción para saber cuadno prenderlo o apagarlo, el otro polling para chequear
       constantemente la temperatura. 

       sistema de temperatura: 
        - va a requerir 2 registros: 
            ° temperatura
            ° cronometro
        - como todo el tiempo tiene que ver la temperatura vamos a usar polling

        ventilador: 
        - va a necesitar un registro
            ° engine
        - como solo hay que prenderlo y apagarlo usamos interrupciones

        Para la catedra: 

            - sensor: 
                + operaciones:
                    * read: devuelve el promedio de los ultimos T segundos
                    * write: Guardamos el valor de T
                + registros:
                    * TEMP: Promedio de los ultimos T segundos
                    * TEMP_MAX: 
                    * TEMP_MIN:
                    * T: T segundos
                + interrupciones: se levanta la interrupción INT_MOV_OK cuando se llegue a destino.

            - ventilador: 
                + operaciones:
                    * write: Configura maximo y minimo
                + registros:
                    * ENCENDIDO: on/off

        // solo lee la temperatura
        int read(int *data) {
            sema_wait(&mutex)
            int temp = IN(TEMP)
            copy_to_sur(data,&temp, sizeof(temp))
            return IO_OK
        }

        int write(int *data) {
            

            return IO_OK
        }

        int driver_init() {
            sema_init(&muTEX,0)
            request_irq(INT_MOV_OK, mov_handler)
            return IO_OK
        }

        int driver_remove() {
            free_irq(int_mov_ok)
            return IO_OK
        }
		 
*/