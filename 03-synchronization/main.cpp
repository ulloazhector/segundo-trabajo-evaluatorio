#include "Bathroom.h"
#include <iostream>
#include <string>
#include <thread>

using namespace std;

// Bathroom status values
enum statusValues { EMPTY,
                    MALE,
                    FEMALE };

// Global object variable
Bathroom bathroom(EMPTY);

void useBathroom(int gender) {
    // start mutex to access bathroom method increment and set the status
    cout << (gender == MALE ? "Male" : "Female") << " using bathroom" << endl;
    // end mutex
}

int main() {

    thread person(useBathroom, FEMALE);
    person.join();

    return 0;
}