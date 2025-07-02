/*
    Se quiere tener un programa que reciba dos argumentos: un número entero N y una cadena de
    texto. Al ejecutarse el programa, si el tamaño de una palabra del texto es mayor a N , entonces esa
    palabra debe ser invertida y pasada a mayúsculas. Por ejemplo:
        $ ./wordInverter 4 "Hola, me gustaria introducirme al mundo!
        Hola, me AIRATSUG EMRICUDORTNI al ODNUM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void inv_may(char *palabra) {
    int len = strlen(palabra);
    // pasamos a mayusculas
    for (int i = 0; i < len; i++) {
        palabra[i] = toupper(palabra[i]);
    }
    // invertimos, para eso basicamente arrancamos con 2 i y cambiamos el primero por el ultimo hasta que llegemos a la mitad de la palabra
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char tmp = palabra[i];
        palabra[i] = palabra[j];
        palabra[j] = tmp;
    }
}

int main(int n, char *string[]) {

    int N = atoi(string[1]);  // Convertir argumento a entero

    char texto[1024];       // Buffer para la copia del texto

    // por las dudas no trabajo directamente en el puntero y hago una copia
    strncpy(texto, string[2], sizeof(texto) - 1);

    texto[sizeof(texto) - 1] = '\0';  // Asegurar terminación

    char *palabra = strtok(texto, " "); // Dividir en palabras, como ponemos " " las separa por espacio
    while (palabra != NULL) {
        if (strlen(palabra) > N) {
            inv_may(palabra);
        }
        printf("%s ", palabra);
        palabra = strtok(NULL, " ");  // Siguiente palabra
    }

    printf("\n");
    return 0;
}
