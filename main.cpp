#include <iostream>
#include "Math.hpp"

int main()
{
    std::cout << (Angle::Lerp(10.0f, 20.0f, 0.5f)).AsDegrees() << std::endl;



    return 0;
}


// super cool namespace color : #E6DD9A