#pragma once
#include <cmath>

#include "Math\Constants.hpp"

namespace Mathematics
{
    struct Angle
    {
    private:
        float m_Radians;

        explicit Angle(float inRad) : m_Radians(inRad) {}

    public: 
        static Angle FromRadians(float angle) { return Angle(angle); } 
        static Angle FromDegrees(float angle) { return Angle(angle * Constants::DegToRad); }

        float AsDegrees() const { return m_Radians * Constants::RadToDeg; }
        float AsRadians() const { return m_Radians; }

        Angle& Normalize()
        {
            m_Radians = std::fmod(m_Radians, 2.0f * Constants::PI);
            if (m_Radians < 0) m_Radians += 2.0f * Constants::PI;
            return *this;
        }

        static Angle Lerp(float startDeg, float endDeg, float t);
        static Angle Lerp(const Angle& start, const Angle& end, float t);
        static Angle ShortLerp(float startDeg, float endDeg, float t);
        static Angle ShortLerp(const Angle& start, const Angle& end, float t);



        Angle& operator+=(const Angle& other)
        {
            m_Radians += other.AsRadians();
            return *this;
        }
        Angle& operator-=(const Angle& other)
        {
            m_Radians -= other.AsRadians();
            return *this;
        }
        Angle& operator*=(float scalar)
        {
            m_Radians *= scalar;
            return *this;
        }
        Angle& operator/=(float scalar)
        {
            m_Radians /= scalar;
            return *this;
        }

    };

    inline Angle operator+(const Angle& a, const Angle& b) 
    {
        return Angle::FromRadians(a.AsRadians() + b.AsRadians());
    }
    inline Angle operator-(const Angle& a, const Angle& b) 
    {
        return Angle::FromRadians(a.AsRadians() - b.AsRadians());
    }
    inline Angle operator*(const Angle& a, float scalar) 
    {
        return Angle::FromRadians(a.AsRadians() * scalar);
    }
    inline Angle operator/(const Angle& a, float scalar) 
    {
        return Angle::FromRadians(a.AsRadians() / scalar);
    }

    inline bool operator>(const Angle& a, const Angle& b) 
    {
        return a.AsRadians() > b.AsRadians();
    }
    inline bool operator<(const Angle& a, const Angle& b) 
    {
        return a.AsRadians() < b.AsRadians();
    }

    inline bool operator==(const Angle& a, const Angle& b)
    {
        return std::abs(a.AsRadians() - b.AsRadians()) < Constants::Epsilon;
    }
    inline bool operator!=(const Angle& a, const Angle& b)
    {
        return !(a == b);
    }



    inline Angle operator"" _deg(long double d) 
    {
        return Angle::FromDegrees(static_cast<float>(d));
    }
    inline Angle operator"" _rad(long double d) 
    {
        return Angle::FromRadians(static_cast<float>(d));
    }

    
}

#include "Math\Mathf.hpp"

namespace Mathematics {
    // ON DÉFINIT LE CODE ICI
    // Maintenant, le compilateur connaît Mathf::Clamp01 grâce à l'include juste au-dessus !
    
    inline Angle Angle::Lerp(float startDeg, float endDeg, float t)
    {
        return Angle::FromDegrees(Mathf::Lerp(startDeg, endDeg, t));
    }

    inline Angle Angle::Lerp(const Angle& start, const Angle& end, float t)
    {
        return Angle::FromRadians(Mathf::Lerp(start.AsRadians(), end.AsRadians(), Mathf::Clamp01(t)));
    }

    inline Angle Angle::ShortLerp(float startDeg, float endDeg, float t)
    {
        float delta = Angle::FromDegrees(endDeg).AsRadians() - Angle::FromDegrees(startDeg).AsRadians();

        float fullCircle = 2.0f * Constants::PI;
        delta = std::fmod(delta, fullCircle);

        if (delta > Constants::PI) delta -= fullCircle;
        if (delta < -Constants::PI) delta += fullCircle;

        // On peut utiliser Mathf sans erreur
        return Angle::FromRadians(Angle::FromDegrees(startDeg).AsRadians() + delta * Mathf::Clamp01(t));
    }

    inline Angle Angle::ShortLerp(const Angle& start, const Angle& end, float t) 
    {
        float delta = end.AsRadians() - start.AsRadians();

        float fullCircle = 2.0f * Constants::PI;
        delta = std::fmod(delta, fullCircle);

        if (delta > Constants::PI) delta -= fullCircle;
        if (delta < -Constants::PI) delta += fullCircle;

        // On peut utiliser Mathf sans erreur
        return Angle::FromRadians(start.AsRadians() + delta * Mathf::Clamp01(t));
    }
}