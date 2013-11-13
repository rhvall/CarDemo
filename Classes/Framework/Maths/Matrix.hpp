//
//  Matrix.hpp
//  OpenGL iOS Framework
//
//  Modified by RHVT on 24/01/12.
//  Copyright (c) 2012 Mittra Software. All rights reserved.
//

#pragma once
#include <iostream>
#include "Common.hpp"
#include "Vector.hpp"

//----------------------------------------
//	MATRIX 2 X 2
//----------------------------------------
#pragma mark -
#pragma mark MATRIX 2 X 2

template <typename T>
struct Matrix2T
{
    Matrix2T()
    {
        x.x = 1; x.y = 0;
        y.x = 0; y.y = 1;
    }
    Matrix2T(const T *m)
    {
        x.x = m[0]; x.y = m[1];
        y.x = m[2]; y.y = m[3];
    }
    Vector2T<T> x;
    Vector2T<T> y;
};

//----------------------------------------
//	MATRIX 3 X 3
//----------------------------------------
#pragma mark -
#pragma mark MATRIX 3 X 3

template <typename T>
struct Matrix3T
{
    Matrix3T()
    {
        x.x = 1; x.y = 0; x.z = 0;
        y.x = 0; y.y = 1; y.z = 0;
        z.x = 0; z.y = 0; z.z = 1;
    }
    
    Matrix3T(const T *m)
    {
        x.x = m[0]; x.y = m[1]; x.z = m[2];
        y.x = m[3]; y.y = m[4]; y.z = m[5];
        z.x = m[6]; z.y = m[7]; z.z = m[8];
    }
    
    static Matrix3T transpose(const Matrix3T<T> in)
    {
        Matrix3T m;
        m.x.x = in.x.x; m.x.y = in.y.x; m.x.z = in.z.x;
        m.y.x = in.x.y; m.y.y = in.y.y; m.y.z = in.z.y;
        m.z.x = in.x.z; m.z.y = in.y.z; m.z.z = in.z.z;
        return m;
    }
    
    const T *pointer() const
    {
        return &x.x;
    }
    
    Vector3 x;
    Vector3 y;
    Vector3 z;
};

//----------------------------------------
//	MATRIX 4 X 4
//----------------------------------------
#pragma mark -
#pragma mark MATRIX 4 X 4

template <typename T>
struct Matrix4T
{
    Matrix4T()
    {
        x.x = 1; x.y = 0; x.z = 0; x.w = 0;
        y.x = 0; y.y = 1; y.z = 0; y.w = 0;
        z.x = 0; z.y = 0; z.z = 1; z.w = 0;
        w.x = 0; w.y = 0; w.z = 0; w.w = 1;
    }
    
    Matrix4T(const Matrix3T<T>& m)
    {
        x.x = m.x.x; x.y = m.x.y; x.z = m.x.z; x.w = 0;
        y.x = m.y.x; y.y = m.y.y; y.z = m.y.z; y.w = 0;
        z.x = m.z.x; z.y = m.z.y; z.z = m.z.z; z.w = 0;
        w.x = 0;     w.y = 0;     w.z = 0;     w.w = 1;
    }
    
    Matrix4T(const T *m)
    {
        x.x = m[0];  x.y = m[1];  x.z = m[2];  x.w = m[3];
        y.x = m[4];  y.y = m[5];  y.z = m[6];  y.w = m[7];
        z.x = m[8];  z.y = m[9];  z.z = m[10]; z.w = m[11];
        w.x = m[12]; w.y = m[13]; w.z = m[14]; w.w = m[15];
    }
    
    Matrix4T operator *(const Matrix4T &b) const
    {
        Matrix4T m;
        m.x.x = x.x * b.x.x + x.y * b.y.x + x.z * b.z.x + x.w * b.w.x;
        m.x.y = x.x * b.x.y + x.y * b.y.y + x.z * b.z.y + x.w * b.w.y;
        m.x.z = x.x * b.x.z + x.y * b.y.z + x.z * b.z.z + x.w * b.w.z;
        m.x.w = x.x * b.x.w + x.y * b.y.w + x.z * b.z.w + x.w * b.w.w;
        m.y.x = y.x * b.x.x + y.y * b.y.x + y.z * b.z.x + y.w * b.w.x;
        m.y.y = y.x * b.x.y + y.y * b.y.y + y.z * b.z.y + y.w * b.w.y;
        m.y.z = y.x * b.x.z + y.y * b.y.z + y.z * b.z.z + y.w * b.w.z;
        m.y.w = y.x * b.x.w + y.y * b.y.w + y.z * b.z.w + y.w * b.w.w;
        m.z.x = z.x * b.x.x + z.y * b.y.x + z.z * b.z.x + z.w * b.w.x;
        m.z.y = z.x * b.x.y + z.y * b.y.y + z.z * b.z.y + z.w * b.w.y;
        m.z.z = z.x * b.x.z + z.y * b.y.z + z.z * b.z.z + z.w * b.w.z;
        m.z.w = z.x * b.x.w + z.y * b.y.w + z.z * b.z.w + z.w * b.w.w;
        m.w.x = w.x * b.x.x + w.y * b.y.x + w.z * b.z.x + w.w * b.w.x;
        m.w.y = w.x * b.x.y + w.y * b.y.y + w.z * b.z.y + w.w * b.w.y;
        m.w.z = w.x * b.x.z + w.y * b.y.z + w.z * b.z.z + w.w * b.w.z;
        m.w.w = w.x * b.x.w + w.y * b.y.w + w.z * b.z.w + w.w * b.w.w;
        return m;
    }
    
    Matrix4T &operator *=(const Matrix4T &b)
    {
        Matrix4T m = *this * b;
        return (*this = m);
    }
    
    inline Vector3T<T> operator *(const Vector3T<T> &v) const
    {
		Vector3T<T> vec;
        
		float temp;
        
		vec.x = v.x * x.x + v.y * x.y + v.z * x.z  + w.x;
		vec.y = v.x * y.x + v.y * y.y + v.z * y.z  + w.y;
		vec.z = v.x * z.x + v.y * z.y + v.z * z.z  + w.z;
        
		temp =  v.x * w.x + v.y * w.y + v.z * w.z + w.w;
        
		vec.x = vec.x/temp;
		vec.y = vec.y/temp;
		vec.z = vec.z/temp;
        
		return vec;
	}
    
    inline Vector4T<T> operator *(const Vector4T<T> &v) const
    {
		return Vector4T<T>(
                       v * x,
                       v * y,
                       v * z,
                       v * w
                      );
	}
    
    //Handy string output for the matrix. Can get a bit messy, but better than nothing!
    inline friend std::ostream& operator <<(std::ostream& o, const Matrix4T& m)
    {
		o << "Mat4(";
		o << "\t"	<< m.x << std::endl;
		o << "\t\t" << m.y << std::endl;
		o << "\t\t" << m.z << std::endl;
		o << "\t\t" << m.w << ")" <<std::endl;
		return o;
	}
    
    static Matrix4T<T> transpose(const Matrix4T<T> in)
    {
        Matrix4T m;
        m.x.x = in.x.x; m.x.y = in.y.x; m.x.z = in.z.x; m.x.w = in.w.x;
        m.y.x = in.x.y; m.y.y = in.y.y; m.y.z = in.z.y; m.y.w = in.w.y;
        m.z.x = in.x.z; m.z.y = in.y.z; m.z.z = in.z.z; m.z.w = in.w.z;
        m.w.x = in.x.w; m.w.y = in.y.w; m.w.z = in.z.w; m.w.w = in.w.w;
        return m;
    }
    
    Matrix3T<T> toMat3() const
    {
        Matrix3T<T> m;
        m.x.x = x.x; m.y.x = y.x; m.z.x = z.x;
        m.x.y = x.y; m.y.y = y.y; m.z.y = z.y;
        m.x.z = x.z; m.y.z = y.z; m.z.z = z.z;
        return m;
    }
    
    const T *pointer() const
    {
        return &x.x;
    }
    
    static Matrix4T<T> identity()
    {
        return Matrix4T();
    }
    
    static Matrix4T<T> translate(T x, T y, T z)
    {
        Matrix4T m;
        m.x.x = 1; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = 1; m.y.z = 0; m.y.w = 0;
        m.z.x = 0; m.z.y = 0; m.z.z = 1; m.z.w = 0;
        m.w.x = x; m.w.y = y; m.w.z = z; m.w.w = 1;
        return m;
    }
    
    static Matrix4T<T> scale(T s)
    {
        Matrix4T m;
        m.x.x = s; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = s; m.y.z = 0; m.y.w = 0;
        m.z.x = 0; m.z.y = 0; m.z.z = s; m.z.w = 0;
        m.w.x = 0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
        return m;
    }
    
    static Matrix4T<T> rotate(T degrees)
    {
        T radians = degrees * 3.14159f / 180.0f;
        T s = std::sin(radians);
        T c = std::cos(radians);
        
        Matrix4T m = identity();
        m.x.x =  c; m.x.y = s;
        m.y.x = -s; m.y.y = c;
        return m;
    }
    
    Matrix4T<T> rotate(T degrees, const Vector3& axis)
    {
        T radians = degrees * 3.14159f / 180.0f;
        T s = std::sin(radians);
        T c = std::cos(radians);
        
        Matrix4T m = identity();
        m.x.x = c + (1 - c) * axis.x * axis.x;
        m.x.y = (1 - c) * axis.x * axis.y - axis.z * s;
        m.x.z = (1 - c) * axis.x * axis.z + axis.y * s;
        m.y.x = (1 - c) * axis.x * axis.y + axis.z * s;
        m.y.y = c + (1 - c) * axis.y * axis.y;
        m.y.z = (1 - c) * axis.y * axis.z - axis.x * s;
        m.z.x = (1 - c) * axis.x * axis.z - axis.y * s;
        m.z.y = (1 - c) * axis.y * axis.z + axis.x * s;
        m.z.z = c + (1 - c) * axis.z * axis.z;
        return m;
    }
    
    static Matrix4T<T> frustum(T left, T right, T bottom, T top, T near, T far)
    {
        T a = 2 * near / (right - left);
        T b = 2 * near / (top - bottom);
        T c = (right + left) / (right - left);
        T d = (top + bottom) / (top - bottom);
        T e = - (far + near) / (far - near);
        T f = -2 * far * near / (far - near);
        Matrix4T m;
        m.x.x = a; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = b; m.y.z = 0; m.y.w = 0;
        m.z.x = c; m.z.y = d; m.z.z = e; m.z.w = -1;
        m.w.x = 0; m.w.y = 0; m.w.z = f; m.w.w = 1;
        return m;
    }
    
    Vector3T<T> getPositionVector() const
    {
        return Vector3T<T>(w.x, w.y, w.z);
    }
    
    void setPositionVector(const Vector3T<T> &in)
    {
        w.x = in.x;
        w.y = in.y;
        w.z = in.z;
    }
    
    Vector3T<T> getScalingVector() const
    {
        return Vector3T<T>(x.x, y.y, z.z);
    }
    
    void setScalingVector(const Vector3T<T> &in)
    {
        x.x = in.x;
        y.y = in.y;
        z.z = in.z;		
    }
    
    static Matrix4T<T> rotation(float degrees, const Vector3T<T> &inaxis)
    {
        Matrix4T<T> m;
        
        Vector3T<T> axis = inaxis;
        
        axis.normalize();
        
        float c = cos((float)degToRad(degrees));
        float s = sin((float)degToRad(degrees));
        
        m.x.x = (axis.x * axis.x) * (1.0f - c) + c;
        m.y.x = (axis.y * axis.x) * (1.0f - c) + (axis.z * s);
        m.z.x = (axis.z * axis.x) * (1.0f - c) - (axis.y * s);
        
        m.x.y = (axis.x * axis.y) * (1.0f - c) - (axis.z * s);
        m.y.y = (axis.y * axis.y) * (1.0f - c) + c;
        m.z.y = (axis.z * axis.y) * (1.0f - c) + (axis.x * s);
        
        m.x.z = (axis.x * axis.z) * (1.0f - c) + (axis.y * s);
        m.y.z = (axis.y * axis.z) * (1.0f - c) - (axis.x * s);
        m.z.z = (axis.z * axis.z) * (1.0f - c) + c;
        
        return m;
    }
    
    static Matrix4T<T> scale(const Vector3T<T> &scale)
    {
        Matrix4T<T> m;
        
        m.x.x = scale.x;
        m.y.y = scale.y;
        m.z.z = scale.z;	
        
        return m;
    }
    
    
    static Matrix4T<T> translation(const Vector3T<T> &translation)
    {
        Matrix4T<T> m;
        
        m.w.x = translation.x;
        m.w.y = translation.y;
        m.w.z = translation.z;
        
        return m;
    }
    
    static Matrix4T<T> perspective(float znear, float zfar, float aspect, float fov)
    {
        Matrix4T<T> m;
        
        const float h = 1.0f / tan(fov * PI_OVER_360);
        float neg_depth = znear-zfar;
        
        m.x.x = h / aspect;
        m.y.y = h;
        m.z.z = (zfar + znear)/neg_depth;
        m.z.w = -1.0f;
        m.w.z = 2.0f * (znear * zfar) / neg_depth;
        m.w.w = 0.0f;
        
        return m;
    }
    
    //http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
    static Matrix4T<T> orthographic(float znear, float zfar,float right, float left, float top, float bottom)
    {
        Matrix4T<T> m;
        
        m.x.x = 2.0f / (right-left);
        m.y.y = 2.0f / (top-bottom);
        m.z.z = -2.0f / (zfar-znear);
        
        m.w.x = -(right+left)/(right-left);
        m.w.y = -(top+bottom)/(top-bottom);
        m.w.z = -(zfar+znear)/(zfar-znear);
        m.w.w = 1.0f;
        
        return m;
    }
    
    static Matrix4T<T> buildViewMatrix(const Vector3T<T> &from, const Vector3T<T> &lookingAt, const Vector3T<T> &up /*= Vector3(1,0,0)*/)
    {
        Matrix4T<T> r;
        r.SetPositionVector(Vector3T<T>(-from.x,-from.y,-from.z));
        
        Matrix4T<T> m;
        
        Vector3T<T> f = (lookingAt - from);
        f.normalize();
        
        Vector3T<T> s = Vector3T<T>::Cross(f,up);
        Vector3T<T> u = Vector3T<T>::Cross(s,f);
        
        m.x.x = s.x;
        m.x.y = s.y;
        m.x.z = s.z;
        
        m.y.x = u.x;
        m.y.y = u.y;
        m.y.z = u.z;
        
        m.z.x = -f.x;
        m.z.x = -f.y;
        m.z.z = -f.z;
        
        return m * r;
    }
     
    Vector4 x;
    Vector4 y;
    Vector4 z;
    Vector4 w;
};

typedef Matrix2T<float> Matrix2;
typedef Matrix3T<float> Matrix3;
typedef Matrix4T<float> Matrix4;
