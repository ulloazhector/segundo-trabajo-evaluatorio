#ifndef _BATHROOM_H_
#define _BATHROOM_H_

class Bathroom {
private:
    int status;
    int count;

public:
    Bathroom();
    int getStatus();
    int getCount();
};

#endif