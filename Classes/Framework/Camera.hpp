//
//  Camera.hpp
//  OpenGL iOS Framework
//
//  Modified by RHVT on 24/01/12.
//  Copyright (c) 2012 Mittra Software. All rights reserved.
//
//
//	           (\___/)
//             (o\ /o)
//            /|:.V.:|\
//		      \\::::://
//        -----`"" ""`-----

#pragma once
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Quaternion.hpp"
#include "Common.hpp"

class Camera
{
public:
    Camera(void);
    
	Camera(float pitch, float yaw, Vector3 position);
	~Camera(void) {};

	Vector3 getPosition() const;
	void setPosition(Vector3 val);
	float getYaw() const;
	void setYaw(float val);
	float getPitch() const;
	void setPitch(float val);
    
    void updateCamera(const TouchTypes &type, const Vector2 &change, const Vector2 &current, const Vector2 &center, const float &sphereRadius);
    Matrix4 buildViewMatrix();
    Vector3 mapToSphere(const Vector2 &touchpoint, const Vector2 &centerPoint, const float &trackballRadius) const;

protected:
    float yaw;
	float pitch;
	Vector3 position;
    Vector2 initialMove;
    Vector2 finalMove;
    Quaternion orientation;
    Quaternion previousOrientation;
};

