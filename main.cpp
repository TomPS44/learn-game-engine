#include <iostream>
#include <concepts>

// #include "Math.hpp"
#include "Vectors.hpp"
#include "Matrices.hpp"
#include "Quaternions.hpp"

template<std::floating_point F>
void logVec2(const vec2<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}
template<std::floating_point F>
void logVec3(const vec3<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}
template<std::floating_point F>
void logQuat(const quat<F>& quat)
{
    std::cout << "(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
}
template<std::floating_point F>
void logMat4(const mat4<F>& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << mat.columns[j][i] << " ";
        }

        std::cout << '\n';
    }
}
template<std::floating_point F>
void logMat3(const mat3<F>& mat)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << mat.columns[j][i] << " ";
        }

        std::cout << '\n';
    }
}
template<std::floating_point F>
void logMat2(const mat2<F>& mat)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            std::cout << mat.columns[j][i] << " ";
        }

        std::cout << '\n';
    }
    std::cout << "" << std::endl;
}


int main() 
{


    mat3f diag = mat3f::diagonal(44.4f);

    // mat3f invDiag = diag.getComatrix().getTransposedMat() * ( 1.0f / diag.determinant<float>() );

    std::cout << diag.determinant<float>() << std::endl;
    std::cout << '\n';

    logMat3(diag * diag.getInvertedMat());
    

    return 0;
}



// super cool namespace color : #E6DD9A