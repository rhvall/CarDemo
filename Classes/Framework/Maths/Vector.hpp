//
//  Vector.hpp
//  OpenGL iOS Framework
//
//  Modified by RHVT on 24/01/12.
//  Copyright (c) 2012 Mittra Software. All rights reserved.
//

#pragma once
#include <cmath>
#include <iostream>

const float Pi = 4 * std::atan(1.0f);
const float TwoPi = 2 * Pi;

//----------------------------------------
//	VECTOR 2
//----------------------------------------
#pragma mark -
#pragma mark VECTOR 2

template <typename T>
struct Vector2T
{
    Vector2T(void)
    {
        toZero();
    }
    
    Vector2T(T x, T y) : x(x), y(y)
    {
    }
    
    void toZero()
    {
        memset(&x, 0, sizeof(T));
        memset(&y, 0, sizeof(T));
	}
    
    T dot(const Vector2T& v) const
    {
        return x * v.x + y * v.y;
    }
    
    inline Vector2T operator +(const Vector2T& v) const
    {
        return Vector2T(x + v.x, y + v.y);
    }
    
    Vector2T operator -(const Vector2T& v) const
    {
        return Vector2T(x - v.x, y - v.y);
    }
    
    Vector2T operator /(float s) const
    {
        return Vector2T(x / s, y / s);
    }
    
    Vector2T operator *(float s) const
    {
        return Vector2T(x * s, y * s);
    }
    
    inline friend std::ostream& operator<<(std::ostream &o, const Vector2T &v)
    {
		o << "(" << v.x << "," << v.y << ")" << std::endl;
		return o;
	}
    
    void normalize()
    {
        float s = 1.0f / length();
        x *= s;
        y *= s;
    }
    
    Vector2T normalized() const
    {
        Vector2T v = *this;
        v.normalize();
        return v;
    }

    T lengthSquared() const
    {
        return x * x + y * y;
    }
    
    T length() const
    {
        return sqrt(lengthSquared());
    }
    
    operator Vector2T<float>() const
    {
        return Vector2T<float>(x, y);
    }
    
    bool operator==(const Vector2T& v) const
    {
        return x == v.x && y == v.y;
    }
    
    Vector2T lerp(float t, const Vector2T& v) const
    {
        return Vector2(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t);
    }
    
    template <typename P>
    P *write(P *pData)
    {
        Vector2T *pVector = (Vector2T *)pData;
        *pVector++ = *this;
        return (P *) pVector;
    }

    T x;
    T y;
};

//----------------------------------------
//	VECTOR 3
//----------------------------------------
#pragma mark -
#pragma mark VECTOR 3

template <typename T>
struct Vector3T
{    
    Vector3T(void)
    {
        toZero();
    }
    
    Vector3T(T x, T y, T z) : x(x), y(y), z(z)
    {
    }
    
    void toZero()
    {
        memset(&x, 0, sizeof(T));
        memset(&y, 0, sizeof(T));
        memset(&z, 0, sizeof(T));
	}
    
//    Vector3T(const Vector3T<T> &v)
//    {
//        x = v.x;
//        y = v.y;
//        z = v.z;        
//    }
    
    void normalize()
    {
		float lengthVal = length();
		if(lengthVal != 0.0f)
        {
			lengthVal = 1.0f / lengthVal;
			x = x * lengthVal;
			y = y * lengthVal;
			z = z * lengthVal;
		}
	}

    
    Vector3T normalized() const
    {
        Vector3T v = *this;
        v.normalize();
        return v;
    }
    
    Vector3T cross(const Vector3T& v) const
    {
        return Vector3T(y * v.z - z * v.y,
                       z * v.x - x * v.z,
                       x * v.y - y * v.x);
    }
    
    static Vector3T cross(const Vector3T &a, const Vector3T &b)
    {
		return Vector3T((a.y*b.z) - (a.z*b.y) , (a.z*b.x) - (a.x*b.z) , (a.x*b.y) - (a.y*b.x));	
	}
    
    T dot(const Vector3T& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    
    static T dot(const Vector3T &a, const Vector3T &b)
    {
        return (a.x * b.x)+(a.y * b.y)+(a.z * b.z);
	}
    
    Vector3T operator +(const Vector3T &v) const
    {
        return Vector3T(x + v.x, y + v.y,  z + v.z);
    }
    
    void operator +=(const Vector3T &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    
    void operator -=(const Vector3T &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    
    void operator /=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
    }
    
    Vector3T operator -(const Vector3T &v) const
    {
        return Vector3T(x - v.x, y - v.y,  z - v.z);
    }
    
    Vector3T operator -() const
    {
        return Vector3T(-x, -y, -z);
    }
    
    Vector3T operator *(T s) const
    {
        return Vector3T(x * s, y * s, z * s);
    }
    
    Vector3T operator /(T s) const
    {
        return Vector3T(x / s, y / s, z / s);
    }
    
    bool operator ==(const Vector3T& v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }
    
	inline Vector3T operator *(const Vector3T  &a) const
    {
		return Vector3T(x * a.x,y * a.y, z * a.z);
	}
    
	inline Vector3T operator /(const Vector3T  &a) const
    {
		return Vector3T(x / a.x,y / a.y, z / a.z);
	};
    
	inline bool	operator !=(const Vector3T &A)const
    {
        return (A.x == x && A.y == y && A.z == z) ? false : true;
    };
    
    inline friend std::ostream& operator<<(std::ostream& o, const Vector3T& v)
    {
		o << "(" << v.x << "," << v.y << "," << v.z <<")" << std::endl;
		return o;
	}
    
    Vector3T lerp(float t, const Vector3T &v) const
    {
        return Vector3T(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t,
                       z * (1 - t) + v.z * t);
    }
    
    const T* pointer() const
    {
        return &x;
    }
    
    T length() const
    {
		return sqrt((x * x) + (y * y) + (z * z));	
	}
    
    void invert()
    {
		x = -x;
		y = -y;
		z = -z;		
    }
    
    Vector3T inverse() const
    {
		return Vector3T(-x, -y, -z);
	}
    
    template <typename P>
    P *write(P *pData)
    {
        Vector3T<T> *pVector = (Vector3T<T> *)pData;
        *pVector++ = *this;
        return (P *)pVector;
    }

    T x;
    T y;
    T z;
};

//----------------------------------------
//	VECTOR 4
//----------------------------------------
#pragma mark -
#pragma mark VECTOR 4

template <typename T>
struct Vector4T
{
    Vector4T()
    {
        toOnes();
    }
    
    Vector4T(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
    {
    
    }
    
    void toOnes()
    {
        memset(&x, 1, sizeof(T));
        memset(&y, 1, sizeof(T));
        memset(&z, 1, sizeof(T));
        memset(&w, 1, sizeof(T));
	}
        
//    Vector4T(Vector4T<T> &v)
//    {
//        x = v.x;
//        y = v.y;
//        z = v.z;
//        w = v.w;
//    }
    
    T dot(const Vector4T &v) const
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }
    
    Vector4T lerp(float t, const Vector4T &v) const
    {
        return Vector4T(x * (1 - t) + v.x * t,
                       y * (1 - t) + v.y * t,
                       z * (1 - t) + v.z * t,
                       w * (1 - t) + v.w * t);
    }
    
    inline friend std::ostream& operator <<(std::ostream &o, const Vector4T &v)
    {
		o << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")" << std::endl;
		return o;
	}
    
    const T *pointer() const
    {
        return &x;
    }
    
    T x;
    T y;
    T z;
    T w;
};

typedef Vector2T<bool> bVector2;

typedef Vector2T<int> iVector2;
typedef Vector3T<int> iVector3;
typedef Vector4T<int> iVector4;

typedef Vector2T<float> Vector2;
typedef Vector3T<float> Vector3;
typedef Vector4T<float> Vector4;
