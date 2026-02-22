#include <concepts>
#include <cmath>

namespace math
{
    template<std::floating_point F>
    inline quat<F>::quat(F qw, const vec3<F>& xyz)
    {
        w = qw;
        x = xyz.x;
        y = xyz.y;
        z = xyz.z;
    }

    template<std::floating_point F>
    inline quat<F>::quat(F qw, F qx, F qy, F qz)
    {
        w = qw;
        x = qx;
        y = qy;
        z = qz;
    }

    template<std::floating_point F>
    inline quat<F> quat<F>::identity()
    {
        F f0 = static_cast<F>(0.0);

        return quat<F>(static_cast<F>(1.0), f0, f0, f0);
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> quat<F>::XYZ() const
    {
        return vec3<f>(static_cast<f>(x), static_cast<f>(y), static_cast<f>(z));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> quat<F>::ZYX() const
    {
        return vec3<f>(static_cast<f>(z), static_cast<f>(y), static_cast<f>(x));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline quat<f> quat<F>::WXYZ() const
    {
        return quat<f>(static_cast<f>(w), static_cast<f>(x), static_cast<f>(y), static_cast<f>(z));
    }

    template<std::floating_point F>
    inline F* quat<F>::valuePtr() const
    {
        return &data[0];
    }

    template<std::floating_point F>
    inline quat<F>& quat<F>::normalized()
    {
        F l = this->length<F>();

        if (std::abs(l) > math::epsilon<F>()) 
        {
            F invLen = static_cast<F>(1.0) / l;
    
            w *= invLen;
            x *= invLen;
            y *= invLen;
            z *= invLen;
        }

        return *this;
    }
 
    template<std::floating_point F>
    template<std::floating_point f>
    inline quat<f> quat<F>::getUnitQuat() const
    {
        quat copy = *this;

        copy = copy.normalized();

        quat<f> unitCopy = quat<f>(static_cast<f>(copy.w),
                                   static_cast<f>(copy.x),
                                   static_cast<f>(copy.y),
                                   static_cast<f>(copy.z));

        return unitCopy;
    }

    template<std::floating_point F>
    inline quat<F>& quat<F>::conjugated()
    {
        x *= static_cast<F>(-1.0);
        y *= static_cast<F>(-1.0);
        z *= static_cast<F>(-1.0);

        return *this;
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline quat<f> quat<F>::getConjugatedQuat() const
    {
        quat copy = *this;

        copy = copy.conjugated();

        quat<f> conjCopy = quat<f>(static_cast<f>(copy.w),
                                   static_cast<f>(copy.x),
                                   static_cast<f>(copy.y),
                                   static_cast<f>(copy.z));

        return conjCopy;
    }

    template<std::floating_point F>
    template<Number N>
    inline N quat<F>::length() const 
    {
        return static_cast<N>(std::sqrt( (w * w) + (x * x) + (y * y) + (z * z) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N quat<F>::length(const quat<F>& quat)  
    {
        return static_cast<N>(std::sqrt( (quat.w * quat.w) + (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N quat<F>::lengthSquared() const 
    {
        return static_cast<N>( (w * w) + (x * x) + (y * y) + (z * z) );
    }

    template<std::floating_point F>
    template<Number N>
    inline N quat<F>::lengthSquared(const quat<F>& quat)  
    {
        return static_cast<N>( (quat.w * quat.w) + (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z) );
    }

    template<std::floating_point F>
    inline quat<F> quat<F>::fromAxisAngle(const vec3<F> axis, F angle)
    {
        vec3<F> rotAxis = axis.getUnitVector();
        F theta = (angle * math::degToRad<F>()) / static_cast<F>(2.0);

        F w = static_cast<F>(std::cos(theta));
        F x = rotAxis.x * static_cast<F>(std::sin(theta));
        F y = rotAxis.y * static_cast<F>(std::sin(theta));
        F z = rotAxis.z * static_cast<F>(std::sin(theta));

        return quat(w, x, y, z);
    }

    template<std::floating_point F>
    inline quat<F> quat<F>::lookAt(const vec3<F>& eye, const vec3<F>& target, const vec3<F>& up)
    {
        // 1. Calculer la direction vers laquelle on veut regarder
        vec3<F> forward = (target - eye).getUnitVector();

        // 2. Notre vecteur "avant" par défaut 
        vec3<F> localForward = vec3<F>(0, 0, 1);

        // 3. Trouver le produit scalaire (cosinus de l'angle)
        F dot = vec3<F>::dotProduct(localForward, forward);

        // Cas particuliers : si les vecteurs sont opposés
        if (std::abs(dot + static_cast<F>(1.0)) < math::epsilon<F>()) 
        {
            return quat<F>(0, up.x, up.y, up.z); // Rotation de 180° autour de l'axe Up
        }
        // Si les vecteurs sont déjà alignés
        if (std::abs(dot - static_cast<F>(1.0)) < math::epsilon<F>()) 
        {
            return quat<F>::identity();
        }

        // 4. Calculer l'axe de rotation (produit vectoriel)
        vec3<F> axis = vec3<F>::crossProduct(localForward, forward);

        // 5. Formule directe pour le quaternion de rotation entre deux vecteurs
        // q.w = sqrt(length(v1)^2 * length(v2)^2) + dot(v1, v2)
        // q.xyz = cross(v1, v2)
        F s = std::sqrt((static_cast<F>(1.0) + dot) * static_cast<F>(2.0));
        F invS = static_cast<F>(1.0) / s;

        return quat<F>(
            s * static_cast<F>(0.5),
            axis.x * invS,
            axis.y * invS,
            axis.z * invS
        )
        .normalized();
    }

    template<std::floating_point F>
    inline quat<F> quat<F>::fromEuler(const vec3<F>& rotation)
    {
        // Conversion en radians et calcul des demi-angles
        F x = (rotation.x * math::degToRad<F>()) * static_cast<F>(0.5);
        F y = (rotation.y * math::degToRad<F>()) * static_cast<F>(0.5);
        F z = (rotation.z * math::degToRad<F>()) * static_cast<F>(0.5);

        F cx = std::cos(x); F sx = std::sin(x);
        F cy = std::cos(y); F sy = std::sin(y);
        F cz = std::cos(z); F sz = std::sin(z);

        // Formule pour l'ordre YXZ
        return quat<F>(
            cx * cy * cz + sx * sy * sz, // w
            sx * cy * cz + cx * sy * sz, // x
            cx * sy * cz - sx * cy * sz, // y
            cx * cy * sz - sx * sy * cz  // z
        );
    }

    template<std::floating_point F>
    inline vec3<F> quat<F>::toEuler() const
    {
        vec3<F> angles;

        F sinX = static_cast<F>(2.0) * (w * x - y * z);
        
        if (std::abs(sinX) >= static_cast<F>(0.99999)) 
        {
            angles.x = std::copysign(math::pi<F>() / static_cast<F>(2.0), sinX);
            angles.y = static_cast<F>(2.0) * std::atan2(y, w);
            angles.z = static_cast<F>(0.0);
        } 
        else 
        {
            angles.x = std::asin(sinX);
            angles.y = std::atan2(static_cast<F>(2.0) * (w * y + z * x), static_cast<F>(1.0) - static_cast<F>(2.0) * (x * x + y * y));
            angles.z = std::atan2(static_cast<F>(2.0) * (w * z + x * y), static_cast<F>(1.0) - static_cast<F>(2.0) * (z * z + x * x));
        }

        angles.x *= math::radToDeg<F>();
        angles.y *= math::radToDeg<F>();
        angles.z *= math::radToDeg<F>();

        return angles;
    }

    template<std::floating_point F>
    inline quat<F> operator*(const quat<F> &a, const quat<F> &b)
    {
        return quat<F>
        (
            a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
            a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
            a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
            a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
        );
    }

    template<std::floating_point F>
    inline mat4<F> quat<F>::toMat4() const 
    {
        F xx = x * x;
        F yy = y * y;
        F zz = z * z;
        F xy = x * y;
        F wz = w * z;
        F wy = w * y;
        F wx = w * x;
        F xz = x * z;
        F yz = y * z;

        F f0 = static_cast<F>(0.0);

        return mat4(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy)    , f0,
                    2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx)    , f0,
                    2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy), f0,
                    f0               , f0               , f0               , static_cast<F>(1.0));
    }
}