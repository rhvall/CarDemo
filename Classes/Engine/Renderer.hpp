//
//  Renderer.hpp
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

#include "OGLRenderer.hpp"
#include "OBJMesh.hpp"
#include "Camera.hpp"

using namespace std;
class Renderer : public OGLRenderer
{
public:
    Renderer(float width, float height);
    virtual ~Renderer(void);
    void startProgram();
    virtual void renderScene();
    void updateScene(float msec);
    void updateCamera(const TouchTypes &isFinal, const Vector2 &change, const Vector2 &current = Vector2(0.0f, 0.0f));
    void updateCamera(const TouchTypes &isFinal, const Vector2 &change, const Vector2 &current = Vector2(0.0f, 0.0f), const Vector2 &center = Vector2(0.0f, 0.0f), const float &sphereRadius = 1);
    void changeSelectedObject(int objIndex);
protected:

    Mesh *cube;
    float angle;
    
    GLuint texture;
    
    OBJMesh *sillon;
    OBJMesh *current;
    OBJMesh *patas1;
    OBJMesh *patas2;
    
    Camera *aCam;
    
    GLuint secondTexture;
    GLuint firstTexture;
};

