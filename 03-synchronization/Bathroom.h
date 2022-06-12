#ifndef _BATHROOM_H_
#define _BATHROOM_H_

class Bathroom {
private:
    int status;
    int count;

public:
    Bathroom(int);
    int getStatus();
    int getCount();
    void increment();
    void decrement();
};

#endif