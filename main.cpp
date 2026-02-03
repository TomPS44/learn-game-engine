#include <iostream>
#include "Math.hpp"

void logVec2(const vec2& vec)
{
    std::cout << "(" << vec.x() << ", " << vec.y() << ")" << std::endl;
}
void logVec3(const vec3& vec)
{
    std::cout << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")" << std::endl;
}


int main() 
{
    logVec3(vec3::moveTowards(vec3::zero(), vec3::one() * 2.0f, 2.0f));
    
    return 0;
}



// super cool namespace color : #E6DD9A