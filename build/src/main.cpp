#include "main.h"

int main(int argc, char** argv) 
{
#ifdef MTH_DEBUG
    std::cout << "Hello, World! Debug mode! (MTH_DEBUG)" << std::endl;
#else
    std::cout << "Hello, World! Release mode! (MTH_RELEASE)" << std::endl;
#endif
}