#pragma once

#include "Math\MathInternal.hpp"

namespace Mathematics
{
    struct angle;

    struct vec2
    {
    private:
        float m_X, m_Y;

    public:
        // Constructor that returns a vec2 with x being vx, and y being vy 
        vec2(float vx, float vy) : m_X(vx), m_Y(vy) {}
        // Constructor that returns a vec2 with x being vec.x and y being vec.y
        vec2(const vec2& vec) : m_X(vec.m_X), m_Y(m_Y) {}
        // Constructor that returns a vec2 from an angle
        static vec2 fromAngle(const angle& angle);

        
        // Equivalent of Vec2(0.0f, 0.0f)
        static vec2 zero() { return vec2(0.0f, 0.0f); }
        // Equivalent of Vec2(1.0f, 1.0f)
        static vec2 one() { return vec2(1.0f, 1.0f); }
        // Equivalent of Vec2(0.0f, 1.0f)
        static vec2 up() { return vec2(0.0f, 1.0f); }
        // Equivalent of Vec2(0.0f, -1.0f)
        static vec2 down() { return vec2(0.0f, -1.0f); }
        // Equivalent of Vec2(-1.0f, 0.0f)
        static vec2 left() { return vec2(-1.0f, 0.0f); }
        // Equivalent of Vec2(1.0f, 0.0f)
        static vec2 right() { return vec2(1.0f,0.0f); }

        // Returns the X value of the vector
        float x() const { return m_X; }
        // Returns the Y value of the vector
        float y() const { return m_Y; }
        // Returns a new Vec2 made of the X and Y values of the vector
        vec2 xy() const { return vec2(m_X, m_Y); }
        // Returns a new Vec2 made of the y and X values of the vector
        vec2 yx() const { return vec2(m_Y, m_X); }
        // Returns a new Vec2 made of the X and X values of the vector
        vec2 xx() const { return vec2(m_X, m_X); }
        // Returns a new Vec2 made of the Y and Y values of the vector
        vec2 yy() const { return vec2(m_Y, m_Y); }

        // Returns the same vector, but with its magnitude being 1
        vec2& normalize()
        {
            float l = this->length();
            if (l > 0.0f) 
            {
                float inverseLength = 1.0f / l;

                m_X *= inverseLength; 
                m_Y *= inverseLength;
            }

            return *this;
        }

        // Returns a new vector, that is the same as the original one, but normalized
        vec2 getUnitVector() const
        {
            vec2 copy = *this;
            copy.normalize();

            return copy;
        }

        // Returns the magnitude of the vector
        float length() const
        {
            return MathInternal::sqrt( (m_X * m_X) + (m_Y * m_Y) );
        }
        // Returns the magnitude of the vector, but squared
        float lengthSquared() const
        {
            return (m_X * m_X) + (m_Y * m_Y);
        }
        // Returns the dot product of the vector with the one specified as a parameter
        float dotProduct(const vec2& other) const
        {
            return (m_X * other.m_X) + (m_Y * other.m_Y); 
        }
        // Returns the distance between the vector, and the one specified as a parameter
        float distance(const vec2& other) const
        {
            return MathInternal::sqrt( (other.m_X - m_X) * (other.m_X - m_X)  +  (other.m_Y - m_Y) * (other.m_Y - m_Y) );
        }
        // Returns the distance between the vector, and the one specified as a parameter, but squared
        float distanceSquared(const vec2& other) const
        {
            return (other.m_X - m_X) * (other.m_X - m_X)  +  (other.m_Y - m_Y) * (other.m_Y - m_Y);
        }


        static float length(const vec2& vec) 
        {
            return MathInternal::sqrt( (vec.m_X * vec.m_X) + (vec.m_Y * vec.m_Y) );
        }
        static float lengthSquared(const vec2& vec) 
        {
            return (vec.m_X * vec.m_X) + (vec.m_Y * vec.m_Y);
        }

        static float dotProduct(const vec2& vec1, const vec2& vec2)
        {
            return (vec1.m_X * vec2.m_X) + (vec1.m_Y * vec2.m_Y); 
        }

        static float distance(const vec2& vec1, const vec2& vec2)
        {
            return MathInternal::sqrt( (vec1.m_X - vec2.m_X) * (vec1.m_X - vec2.m_X)  +  (vec1.m_Y - vec2.m_Y) * (vec1.m_Y - vec2.m_Y) );
        }
        static float distanceSquared(const vec2& vec1, const vec2& vec2)
        {
            return (vec1.m_X - vec2.m_X) * (vec1.m_X - vec2.m_X)  +  (vec1.m_Y - vec2.m_Y) * (vec1.m_Y - vec2.m_Y);
        }

        static vec2 lerp(const vec2& start, const vec2& end, float t)
        {
            t = MathInternal::clamp01(t);
            return vec2(start.x() + (end.x() - start.x()) * t, start.y() + (end.y() - start.y()) * t);
        }
        static vec2 lerpUnclamped(const vec2& start, const vec2& end, float t)
        {
            return vec2(start.x() + (end.x() - start.x()) * t, start.y() + (end.y() - start.y()) * t);
        }
        

        vec2& operator+=(const vec2& other)
        {
            this->m_X += other.m_X;
            this->m_Y += other.m_Y;

            return *this;
        }
        vec2& operator-=(const vec2& other)
        {
            this->m_X -= other.m_X;
            this->m_Y -= other.m_Y;

            return *this;
        }
        vec2& operator*=(float scalar)
        {
            this->m_X *= scalar;
            this->m_Y *= scalar;

            return *this;
        }
        vec2& operator/=(float scalar)
        {
            if (scalar == 0.0f) return *this;

            scalar = 1.0f / scalar;

            this->m_X *= scalar;
            this->m_Y *= scalar;

            return *this;
        }


        // Returns a float pointer of the vector's value at the specified index (x -> 0, y -> 1)
        // The specified index is clamped between 0 and 1
        float* operator[](int index)
        {
            index = Mathf::clamp01(index);

            if (index == 0) { return &m_X; }
            else { return &m_Y; }

        }
        
    };

    // Arithmetic Operators

    inline vec2 operator+(const vec2& a, const vec2& b)
    {
        return vec2(a.x() + b.x(), a.y() + b.y());
    }
    inline vec2 operator-(const vec2& a, const vec2& b)
    {
        return vec2(a.x() - b.x(), a.y() - b.y());
    }
    inline vec2 operator*(const vec2& vec, float scalar)
    {
        return vec2(vec.x() * scalar, vec.y() * scalar);
    }
    inline vec2 operator/(const vec2& vec, float scalar)
    {
        if (scalar == 0) return vec;

        scalar = 1.0f / scalar;

        return vec2(vec.x() * scalar, vec.y() * scalar);
    }


    inline bool operator==(const vec2& a, const vec2& b)
    {
        return MathInternal::abs(a.x() - b.x()) < Constants::Epsilon && MathInternal::abs(a.y() - b.y()) < Constants::Epsilon;
    }
    inline bool operator!=(const vec2& a, const vec2& b)
    {
        return !(a == b);
    }


    
}