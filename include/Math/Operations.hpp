#pragma once 

#include "Math\Angle.hpp"
#include "Math\Vector2.hpp"
#include "Math\Vector3.hpp"
#include "Vector3.hpp"

namespace Mathematics
{
    // ----------- Angle.hpp --------------
    inline angle angle::angleBetween(const vec2& a, const vec2& b)
    {
        //
        // Soit v et u des vecteurs
        //
        // v • u = ||v|| ||u|| cos(θ)
        //
        //            (   v • u   )
        //  θ = arccos(-----------)
        //            (||v|| ||u||)
        //
        //          ↑↑↑↑↑↑↑↑↑
        //       comes from here

        float dot = vec2::dotProduct(a.getUnitVector(), b.getUnitVector());

        return angle::fromRadians(MathInternal::acos(MathInternal::clamp(dot, -1.0f, 1.0f)));
    }

    // ----------- Vector2.hpp --------------

    inline vec2 vec2::fromAngle(const angle& angle)
    { 
        return vec2(MathInternal::cos(angle.asRadians()), MathInternal::sin(angle.asRadians())); 
    }

    // ----------- Vector3.hpp --------------

    inline vec3::vec3(const vec2& xy) : m_X(xy.x()), m_Y(xy.y()), m_Z(0.0f) {}
    inline vec3::vec3(const vec2& xy, float vz) : m_X(xy.x()), m_Y(xy.y()), m_Z(vz) {}

    vec3::operator vec2() const { return vec2(m_X, m_Y); }

    inline vec2 vec3::xx() const { return vec2(m_X, m_X); }
    inline vec2 vec3::yy() const { return vec2(m_Y, m_Y); }
    inline vec2 vec3::zz() const { return vec2(m_Z, m_Z); }
    inline vec2 vec3::xy() const { return vec2(m_X, m_Y); }
    inline vec2 vec3::xz() const { return vec2(m_X, m_Z); }
    inline vec2 vec3::yx() const { return vec2(m_Y, m_X); }
    inline vec2 vec3::yz() const { return vec2(m_Y, m_Z); }
    inline vec2 vec3::zx() const { return vec2(m_Z, m_X); }
    inline vec2 vec3::zy() const { return vec2(m_Z, m_Y); }
}