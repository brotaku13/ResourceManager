#include <processor/Processor.h>

#define MANAGER_TYPE 0 // == basic, 1 == extended

int main(){

    Processor proc(MANAGER_TYPE);
    proc.run();
    return 0;
}