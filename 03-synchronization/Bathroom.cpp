#include "Bathroom.h"

Bathroom::Bathroom() {
    this->status = 0;
    this->count = 0;
}

int Bathroom::getStatus() {
    return this->status;
}

int Bathroom::getCount() {
    return this->count;
}