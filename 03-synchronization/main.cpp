#include "Bathroom.h"
#include <chrono>
#include <cstdlib> // random number
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <time.h>

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

// Entrada al baño
void inBathroom(int gender) {
    // No puede estar entrando una persona mientras otra está saliendo,
    // tampoco pueden entrar 2 o más al mismo tiempo
    mtxBathroom.lock();

    if (bathroom.getStatus() == EMPTY) {
        mtxQueue.lock();
    } else if (bathroom.getStatus() != gender) {
        mtxBathroom.unlock();
        mtxQueue.lock(); // Fila para el género opuesto al que está usando el baño
    }

    bathroom.setStatus(gender);
    bathroom.increment();

    cout << "\033[1;32m+\033[0m "
         << (gender == MALE ? "Hombre" : "Mujer\t") << "\t| Total: \033[1m"
         << bathroom.getCount()
         << "\033[0m"
         << endl;

    mtxBathroom.unlock();
}

// Salida del baño
void outBathroom(int gender) {
    mtxBathroom.lock();

    bathroom.decrement();
    cout << "\033[1;31m-\033[0m " 
    << (gender == MALE ? "Hombre" : "Mujer\t") 
    << "\t| Total: \033[1m" 
    << bathroom.getCount() 
    << "\033[0m" 
    << endl;

    if (bathroom.getCount() == 0) {
        bathroom.setStatus(EMPTY);
        cout << "--------------------------" << endl;
        mtxQueue.unlock();
    }
    mtxBathroom.unlock();
}

void useBathroom(int gender) {
    inBathroom(gender);
    this_thread::sleep_for(chrono::microseconds(rand() % 50));
    outBathroom(gender);
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < CANT_THREADS; i++) {
        thread(useBathroom, rand() % 2 + 1).detach();
        this_thread::sleep_for(chrono::microseconds(20));
    }

    this_thread::sleep_for(chrono::seconds(10));

    return 0;
}