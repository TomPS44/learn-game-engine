#pragma once

#include <cmath>
#include <concepts>

#include "Math\MathInternal.hpp"
#include "Math\Concepts.hpp"

namespace math
{
    template<std::floating_point F>
    struct vec3;

    template<std::floating_point F>
    struct mat4;

    template<std::floating_point F>
    struct alignas(16) quat  
    {
    public:
        union 
        {
            struct { F w, x, y, z; };
            F data[4];
        };

    public:
        quat(F qw, const vec3<F>& xyz);
        quat(F qw, F qx, F qy, F qz);

        static quat<F> identity();
        
        template<std::floating_point type>
        vec3<type> XYZ() const;
        template<std::floating_point type>
        vec3<type> ZYX() const;
        template<std::floating_point type>
        quat<type> WXYZ() const;

        F* valuePtr() const;

        quat& normalized();

        template<std::floating_point type>
        quat<type> getUnitQuat() const;

        quat& conjugated();

        template<std::floating_point type>
        quat<type> getConjugatedQuat() const;

        template<Number N>
        N length() const;
        template<Number N>
        N lengthSquared() const;

        template<Number N>
        static N length(const quat& quat);
        template<Number N>
        static N lengthSquared(const quat& quat);

        static quat fromAxisAngle(const vec3<F> axis, F angle);

        static quat lookAt(const vec3<F>& eye, const vec3<F>& target, const vec3<F>& up);

        static quat fromEuler(const vec3<F>& rotation);

        template<std::floating_point type>
        static vec3<type> rotatePointViaQuat(const vec3<F>& point, const quat<F>& rot)
        {
            
            quat qPoint = quat(static_cast<F>(0.0), point.XYZ());
            
            vec3 rotated = (rot * qPoint * rot.getConjugatedQuat<type>()).XYZ();

            return rotated;
        }

        vec3<F> toEuler() const;

        mat4<F> toMat4() const;
    };

    template<std::floating_point F>
    inline quat<F> operator*(const quat<F>& a, const quat<F>& b);
}

#include "Math\Quaternions\Quaternion.inl"