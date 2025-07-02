#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
	Voy a separar todo de que son las cosas para despues:
	
	execve("./hai", ["./hai", "ls"], ...) --> inicio del programa 

	clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x26978b50) = 72731 --> crea proceso hijo

	nanosleep({tv_sec=1, tv_nsec=0}, 0x7ffc85f0fd10) = 0 --> hace un sleep

	write(1, "sup!\n", 5sup!) --> imprime por pantalla sup! 5 veces


	Basicamente arranca el programa, crea un hijo, se mete en el loop e imprime 5 veces con un segundo de diferencia por el spleep.
	No veo donde se ejecuta el ls asi que lo debe hacer el hijo despues de toda la ejecucion del padre, buscando encontre que existe el comando
	strace -f ./hai ls que me deja seguir los forks, ahi lo prubeo.

	que quilombo mal, sabemos que el 73689 es el uid del hijo asi que asumo que 73688 es el padre. El padre le tira 5 veces sup! al hijo
	y este le devuelve ya va hasta que despues alguien hace el ls

	Lo encontre jijijaja:

		[pid 73689] kill(73688, SIGINT)         = 0
		[pid 73688] <... nanosleep resumed>{tv_sec=1, tv_nsec=13949}) = ? ERESTART_RESTARTBLOCK (Interrupted by signal)
		[pid 73688] --- SIGINT {si_signo=SIGINT, si_code=SI_USER, si_pid=73689, si_uid=1000} ---
		[pid 73689] execve("/home/alex/.local/bin/ls", ["ls"],
	
	hijo manda sigInt al padre despues del 5 ya va y el padre hace el LS 

	Para responder a las preguntas:

		-1 ¿Cu´antos procesos se lanzan y qu´e comportamiento se puede observar de cada uno?

			se lanzan 2 procesos, el padre que es el que se encarga de pedirle al hijo la señal 5 hasta que manda la señal y ejecuta el exec y correr el ls.

		-2 ¿Utilizan los procesos alguna forma de IPC?¿Cu´al es y para qu´e se usa en este caso?

			Aca voy a meter resumen de que es IPC 

			Usan señales para que el padre se pueda comunicar con el hijo mediante los kills que se envian (idem para el hijo) usan las señales
				Sigurg --> se usan en el loop para que ambos printeen en pantalla sus mensajes
				sigint --> Se usa para que el padre ejecute exec y cambie su codigo al comando que le mandemos

			Por lo que el padre tiene 2 handlers, uno para la señal sigurg y otro para la señal sigint 
			El hijo tiene solo un handler que es para sigurg

		-3 ¿Qu´e puede deducir del programa a partir de las syscalls observadas?

			El programa arrcanca y se forkea un hijo, despues en un loop de 5 ciclos le consulta el padre al hijo con el SUP! y el hijo le respomde
			Ya va! hasta que al final el hijo le manda la señal sigint al padre, termina su proceso y este ejecuta el exec para ejecutar el binario
			Ls que fue el que le mandamos.

*/

/*
	argc es el número de argumentos incluyendo el nombre del programa.

	argv es un array de punteros a strings (char *), que contiene:

    argv[0]: el nombre con el que se invocó el programa (por ejemplo, "./hai")

    argv[1], argv[2], ..., argv[argc-1]: los argumentos que se pasaron en la línea de comandos.
*/

int contador = 0;
char **path_global; // para poder darle al handler

void sigurg_handler(int sig) {
	printf("Ya va!\n");
	// aumentamos el contador para que pueda salir del while el hijo
	++contador;
}

void sigint_handler(int sig) {
	// necesito argumentos por lo que voy a tener que crear variables globales
	execvp(path_global[1],&path_global[1]);
}

void rutina_hijo() {
	signal(SIGURG, sigurg_handler);

	while (contador < 5)
	{
		// si recibe señal aumenta el contador en 1 para eso se me ocurre meter otra var global que cuente las veces que se mando la señal
		// lo podemos meter en el hadler

		// el hijo spera una señal
		
	}

	kill(getppid(),SIGINT);

	exit(0);
}

int main(int argc, char* argv[]) {
  	
	// depues veo que recibo y como lo manejo, vamos a hacer la rutina del padr y del hijo
	// creamos var global para poder darle a los handlers despues, asi que igualamos el valor aca
	path_global = argv;

	int uid = fork();

	if (uid == 0)
	{
		rutina_hijo();
	}

	//setup del handler de las 2 señales que va a recibir el padre
	signal(SIGINT,sigint_handler);

	//El hijo se ejecuta y hace sus handlers, por las dudas aca pongo un ssleep de 1 seg
	sleep(1);

	// Mandamos 5 veces la señal y esperamos a que el hijo responda
	for (size_t i = 0; i < 5; i++)
	{
		// pid del hijo y señal 
		kill(uid,SIGURG);
		printf("sup!\n");
		sleep(1);
		// me esta printienado el sup antes o muchas veces, tenemos que esperar a que el hijo responda
	}
	
	// dejamos esto aca para matar lso zombies, lei que podemos hacer _exit(0) en el hijo y eso nos asegura de no dejar basura pero no lo vimos
	wait(NULL);
	
	return 0;
}
