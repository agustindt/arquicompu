#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "EasyPIO.h" // Incluir EasyPIO

// Declaraciones de funciones
void mostrarMenu();
void leerOpcion(int *opcion);
void ejecutarSecuenciaAutoFantastico();
void ejecutarSecuenciaLaCarrera();
void ejecutarSecuenciaAdicional1();
void ejecutarSecuenciaAdicional2();
void leerPassword(char *password);
int compararPassword(const char *passwordIngresada, const char *passwordCorrecta);
void retardo(unsigned long int *a );
void apagarLuces();
char teclaPresionada();
int Leds(int num); // Función para controlar los LEDs

// Variables globales
const char passwordCorrecta[] = "12345"; // Contraseña correcta

// Definición de pines GPIO para los LEDs
const int led[] = {7, 8, 25, 24, 23, 18, 15, 14}; // Pines GPIO a los cuales están conectados los LEDs
const int numPines = 8; // Número de pines GPIO utilizados

// Función para mostrar el valor de i en binario
void display_binary(int i){ 
    int t;
    for(t=128; t>0; t = t/2){
        if(i & t) printf("* ");
        else printf(" ");   
        printf("\n");
 }
 
}

int main() {
int intentos = 0;
char passwordIngresada[6];

    // Inicialización de EasyPIO
    pioInit();

    // Configuración de los pines como salida para los LEDs
   for (int i = 0; i < numPines; i++) {
        pinMode(led[i], OUTPUT);
    }

    // Proceso de autenticación por contraseña
    while (intentos < 3) {
        printf("Ingrese su password de 5 dígitos: ");
        leerPassword(passwordIngresada);
        if (compararPassword(passwordIngresada, passwordCorrecta)) {
            printf("Bienvenido al Sistema\n");
            break;
        } else {
            printf("Password no válida\n");
            intentos++;
        }
    }

    if (intentos == 3) {
        printf("Ha excedido el número de intentos permitidos\n");
        return 1; // Salir del programa
    }

    int opcion = 0;
    while (1) {
        mostrarMenu();
        leerOpcion(&opcion);

        switch (opcion) {
            case 1:
                ejecutarSecuenciaAutoFantastico();
                break;
            case 2:
                ejecutarSecuenciaLaCarrera();
                break;
            case 3:
                ejecutarSecuenciaAdicional1();
                break;
            case 4:
                ejecutarSecuenciaAdicional2();
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }
    }

    return 0;
}

// Implementaciones de funciones

void mostrarMenu() {
    printf("\n--- Menú de Secuencias de Luces ---\n");
    printf("1. Auto Fantástico\n");
    printf("2. La Carrera\n");
    printf("3. Secuencia Adicional 1\n");
    printf("4. Secuencia Adicional 2\n");
    printf("Seleccione una opción: ");
}


void leerOpcion(int *opcion) { 
    scanf("%d", opcion); // Leer la opción seleccionada por el usuario
}

void leerPassword(char *password) {
    scanf("%5s", password); // Leer exactamente 5 caracteres
}

int compararPassword(const char *passwordIngresada, const char *passwordCorrecta) {
    return strcmp(passwordIngresada, passwordCorrecta) == 0;
}

void retardo(unsigned long int *a) {
    // Inicializa ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE); // No espera por la entrada del usuario
    keypad(stdscr, TRUE);

    int ch = getch();

    // Detecta la tecla de flecha hacia abajo
    if (ch == KEY_DOWN) {
        *a += 50;
    }
    // Detecta la tecla de flecha hacia arriba
    if (*a > 50 && ch == KEY_UP) {
        *a -= 50;
    }

    // Espera por el tiempo especificado en *a milisegundos
    usleep(*a * 1000);

    // Termina ncurses
    endwin();
}

int Leds (int posicion) {
    Leds(1 << posicion); // Encender el LED en la posición indicada
}

void apagarLuces() {
    Leds(0); // Apagar todos los LEDs
}

// int Leds(int num) {
//     int i, numval;
//     for (i = 0; i < numPines; i++) {
//         numval = (num >> i) & 0x01;
//         digitalWrite(led[i], numval);
//     }
//     delayMillis(300); // Retardo de 300 milisegundos entre cambios de estado de los LEDs
//     return 0;
// }



void ejecutarSecuenciaAutoFantastico() {  
    int direccion = 1;
    int posicion = 0;
    const int MAX_POSICION = 7;
    const int MIN_POSICION = 0;
    velocidadActual = 1000;

    while (1) {
        display_binary(posicion); // Mostrar el valor de la posición en binario
        Leds(posicion); // Encender el LED en la posición indicada
        retardo(&velocidadActual); // Retardo de acuerdo a la velocidad actual
        posicion += direccion; // Actualizar la posición
        if (posicion == MAX_POSICION || posicion == MIN_POSICION) { // Cambiar la dirección
            direccion = -direccion; // Cambiar la dirección
        }
        if (teclaPresionada() == 'E') { // SALIR
          return;
        }
    }
}

void ejecutarSecuenciaLaCarrera() {
    int posiciones[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int numPosiciones = sizeof(posiciones) / sizeof(posiciones[0]);
    velocidadActual = 1000;

    while (1) {
        for (int i = 0; i < numPosiciones; i++) {
            display_binary(posiciones[i]); // Mostrar el valor de la posición en binario
            Leds(posiciones[i]); // Encender el LED en la posición indicada
            retardo(&velocidadActual); // Retardo de acuerdo a la velocidad actual
            apagarLuces(); // Apagar todos los LEDs
            if (teclaPresionada() == 'E') { // SALIR
                return;
            }
        }
    }
}

void ejecutarSecuenciaAdicional1() {
    // Implementar la secuencia adicional 1 usando un algoritmo específico
    // Ejemplo:
    int posicion = 0;
    const int MAX_POSICION = 7;
    velocidadActual = 1000;

    while (1) {
        display_binary(posicion); // Mostrar el valor de la posición en binario
        Leds(posicion); // Encender el LED en la posición indicada
        retardo(&velocidadActual); // Retardo de acuerdo a la velocidad actual
        apagarLuces(); // Apagar todos los LEDs
        posicion = (posicion + 1) % (MAX_POSICION + 1); // Actualizar la posición
        if (teclaPresionada() == 'E') { // SALIR
            return;
        }
    }
}

void ejecutarSecuenciaAdicional2() {
    // Implementar la secuencia adicional 2 usando una tabla de datos específica
    // Ejemplo:
    int posiciones[] = {0, 1, 3, 4, 6, 7};
    int numPosiciones = sizeof(posiciones) / sizeof(posiciones[0]); // Número de posiciones
    velocidadActual = 1000;

    while (1) {
        for (int i = 0; i < numPosiciones; i++) { // Recorrer todas las posiciones
            display_binary(posiciones[i]);  // Mostrar el valor de la posición en binario
            Leds(posiciones[i]); // Encender el LED en la posición indicada
            retardo(&velocidadActual); // Retardo de acuerdo a la velocidad actual
            apagarLuces(); // Apagar todos los LEDs
            if (teclaPresionada() == 'E') { // SALIR
                return;
            }
        }
    } 
}
