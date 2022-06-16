#include "Bathroom.h"
#include <chrono>   // chronometer
#include <cstdlib>  // random number
#include <iostream> // i/o
#include <mutex>    // mutex
#include <string>   // string
#include <thread>   // threads
#include <time.h>   // time

#define CANT_THREADS 100

using namespace std;

// Bathroom status values
enum statusValues { EMPTY,
                    MALE,
                    FEMALE };

// Global object variable
Bathroom bathroom(EMPTY);

// Mutex
mutex mtxQueue, mtxBathroom;

/*
    mtxBathroom -> EXCLUSIÓN MUTUA
    mtxQueue    -> SINCRONIZACIÓN
*/

// Styled strings
string redString(string s) { return "\033[1;32m" + s + "\033[0m "; }
string greenString(string s) { return "\033[1;31m" + s + "\033[0m "; }
string boldString(int s) { return "\033[1m" + to_string(s) + "\033[0m "; }

// Entrada al baño
void inBathroom(int gender) {
    // No puede estar entrando una persona mientras otra está saliendo,
    // tampoco pueden entrar 2 o más al mismo tiempo (MUT EX)
    mtxBathroom.lock();

    if (bathroom.getStatus() == EMPTY) {
        mtxQueue.lock(); // (SYNC)
    } else if (bathroom.getStatus() != gender) {
        mtxBathroom.unlock(); // Libera el baño porque se va a bloquear en la fila de espera
        mtxQueue.lock();      // Fila para el género opuesto al que está usando el baño
    }

    bathroom.setStatus(gender);
    bathroom.increment();

    cout << redString("+") << (gender == MALE ? "Hombre" : "Mujer\t") << "\t| Total: " << boldString(bathroom.getCount()) << endl;

    mtxBathroom.unlock();
}

// Salida del baño
void outBathroom(int gender) {

    mtxBathroom.lock();

    bathroom.decrement();
    cout << greenString("-") << (gender == MALE ? "Hombre" : "Mujer\t") << "\t| Total: " << boldString(bathroom.getCount()) << endl;

    if (bathroom.getCount() == 0) {
        bathroom.setStatus(EMPTY);
        cout << "--------------------------" << endl;
        mtxQueue.unlock(); // Los que estaban en la fila PUEDEN competir por el uso del procesador (pasan a READY)
    }

    mtxBathroom.unlock();
}

// Uso del baño
void useBathroom(int gender) {
    inBathroom(gender);
    this_thread::sleep_for(chrono::microseconds(rand() % 50));
    outBathroom(gender);
}

int main() {
    // seed random numbers
    srand(time(NULL));

    // generate threads
    for (int i = 0; i < CANT_THREADS; i++) {
        // Create threads without saving references
        thread(useBathroom, rand() % 2 + 1).detach();
        this_thread::sleep_for(chrono::microseconds(20));
    }

    // sleep main thread
    this_thread::sleep_for(chrono::seconds(3));

    return 0;
}