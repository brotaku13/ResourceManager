#include <processor/Processor.h>

#define MANAGER_TYPE 1 // == basic, 1 == extended

int main(){

    Processor proc(MANAGER_TYPE);
    proc.run();
    return 0;
}