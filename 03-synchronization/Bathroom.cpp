#include "Bathroom.h"

Bathroom::Bathroom(int status) {
    this->status = status;
    this->count = 0;
}

int Bathroom::getStatus() {
    return this->status;
}

int Bathroom::getCount() {
    return this->count;
}

void Bathroom::increment() {
    this->count++;
}

void Bathroom::decrement() {
    this->count--;
}