//
//  Camera.cpp
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

#include "Camera.hpp"

//----------------------------------------
//	CONSTRUCTOR
//----------------------------------------
#pragma mark -
#pragma mark CONSTRUCTOR

Camera::Camera(void)
{
    yaw = 0.0f;
    pitch = 0.0f;
    position = Vector3(0.0f, 0.0f, 0.0f);
    initialMove = Vector2(0.0f, 0.0f);
    finalMove = Vector2(0.0f, 0.0f);
    orientation = Quaternion();
    previousOrientation = Quaternion();
};

Camera::Camera(float pitch, float yaw, Vector3 position)
{
    this->yaw = yaw;
    this->pitch = pitch;
    this->position = position;
    
    initialMove = Vector2(0.0f, 0.0f);
    finalMove = Vector2(0.0f, 0.0f);
};

//----------------------------------------
//	GETTERS, SETTERS
//----------------------------------------
#pragma mark -
#pragma mark GETTERS, SETTERS

Vector3 Camera::getPosition() const
{
    return position;
}

void Camera::setPosition(Vector3 val)
{
    position = val;
}

float Camera::getYaw() const
{
    return yaw;
}

void Camera::setYaw(float val)
{
    yaw = val;
}

float Camera::getPitch() const
{
    return pitch;
}

void Camera::setPitch(float val)
{
    pitch = val;
}

//----------------------------------------
//	FUNCTIONALITY
//----------------------------------------
#pragma mark -
#pragma mark FUNCTIONALITY

void Camera::updateCamera(const TouchTypes &type, const Vector2 &change, const Vector2 &current, const Vector2 &center, const float &sphereRadius)
{    
    float msec = 5.0f;
    initialMove = change;
    finalMove = current;
    if (type == singleMiddle)
    {
        Vector3 start = mapToSphere(initialMove, center, sphereRadius);
        Vector3 end = mapToSphere(finalMove, center, sphereRadius);
        Quaternion delta = Quaternion::createFromVectors(start, end);
        orientation = delta.rotated(previousOrientation);
    }
    else if (type == doubleMiddle)
    {
//        std::cout << "Initial V3:" << initialMove.x << ", " << initialMove.y << std::endl;
//        std::cout << "Final V3:" << finalMove.x << ", " << finalMove.y << std::endl;

        if (initialMove.x >= 0 && initialMove.y >= 0 &&
            finalMove.x <= 0 && finalMove.y <= 0)
        {
            position.z += msec;
        }
        else if (initialMove.x <= 0 && initialMove.y <= 0 &&
                 finalMove.x >= 0 && finalMove.y >= 0)
        {
            position.z -= msec;
        }
    }
}

Matrix4 Camera::buildViewMatrix()
{
    Matrix4 orientationMatrix = orientation.toMatrix();
    
    previousOrientation = orientation;
    
    return  orientationMatrix * Matrix4::translation(-position);
}

Vector3 Camera::mapToSphere(const Vector2 &touchpoint, const Vector2 &centerPoint, const float &trackballRadius) const
{
    Vector2 p = touchpoint - centerPoint;
    p.y = -p.y;
    
    const float safeRadius = trackballRadius - 1;
    
    if (p.length() > safeRadius)
    {
        float theta = atan2(p.y, p.x);
        p.x = safeRadius * cos(theta);
        p.y = safeRadius * sin(theta);
    }
    
    float z = sqrt(trackballRadius * trackballRadius - p.lengthSquared());
    Vector3 mapped = Vector3(p.x, p.y, z);
    return mapped / trackballRadius;
}