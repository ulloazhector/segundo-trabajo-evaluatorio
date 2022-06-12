#include <iostream>
#include <thread>
#include "Bathroom.h" 

using namespace std;

void myFunction () {
    cout << "Hello from thread" << endl;
}

int main() {

    thread myThread(myFunction);
    myThread.join();

    return 0;
}