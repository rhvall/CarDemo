//
//  Renderer.cpp
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

#include "Renderer.hpp"
#include "ResourceManager.h"

Renderer::Renderer(float width, float height) : OGLRenderer(width, height)
{
    init = true;
}

Renderer::~Renderer(void)
{
    delete cube;
}

void Renderer::startProgram()
{
    currentShader = new Shader("/TexturedVertex.vert", "/TexturedFragment.frag");
    
    if (!currentShader->linkProgram())
    {
        cout << "No link program!!" << endl;
        exit(1);
        return;
        
    }
    glUniform1i(glGetUniformLocation(currentShader->getProgram(), "diffuseTex"), 0);
    
    projMatrix = Matrix4::perspective(1.0f, 1500.0f, (float)width / (float)height, 40.0f);
    aCam = new Camera(-1.70f, 276.0f, Vector3(0.0f, 0.0f, 100.0f));
    angle = 0;
    
	viewMatrix = aCam->buildViewMatrix();
    
    string path = ResourceManager::getResourcePath();
    //    path += "/sillon.obj";
    string path0 = path + "/SillonOK.obj";
    string path1 = path + "/Sillon-patas.obj";
    string path2 = path + "/Sillon-patas-dos.obj";
    
    glEnable(GL_TEXTURE_2D);
    
    sillon = new OBJMesh(path0);
    firstTexture = ResourceManager::generateTexture("sillon0");
    sillon->setTexture(firstTexture);
    secondTexture = ResourceManager::generateTexture("sillon4");
    patas1 = new OBJMesh(path1);
    patas1->setTexture(ResourceManager::generateTexture("sillon1"));
    patas2 = new OBJMesh(path2);
    patas2->setTexture(ResourceManager::generateTexture("sillon2"));
    current = patas1;

//  cube = Mesh::generateCCube(Vector3(1.0f, 0.0f, 0.0f), 0.5f);
//  cube = Mesh::generateTriangle();
    
    glEnable(GL_DEPTH_TEST);
}

void Renderer::renderScene()
{
    glClearColor(0.5f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(currentShader->getProgram());
    
	viewMatrix = aCam->buildViewMatrix();
    //modelMatrix = Matrix4::translation(Vector3(1.0f, 0.0f, 0.0f)) * Matrix4::scale(5.0f);
    
    updateShaderMatrices();
    
    sillon->draw();
    current->draw();
    //cube->draw();
    
    glUseProgram(0);
}

void Renderer::updateScene(float msec)
{
    angle += 10.0f;
    if (angle > 360)
    {
        angle = 0;
    }

    //Here activates the rotation effect
    modelMatrix = Matrix4::rotation(angle, Vector3(0.0f, 1.0f, 1.0f)) * Matrix4::scale(15.0f) * Matrix4::translation(Vector3(0.0f, 0.0f, 0.0f));
}

void Renderer::updateCamera(const TouchTypes &isFinal, const Vector2 &change, const Vector2 &current, const Vector2 &center, const float &sphereRadius)
{
    aCam->updateCamera(isFinal, change, current, center, sphereRadius);
}

void Renderer::changeSelectedObject(int objIndex)
{
    if (objIndex == 0)
    {
        current = patas1;
    }
    else if (objIndex == 1)
    {
        current = patas2;
    }
    else
    {
        if (sillon->getTexture() == firstTexture)
        {
            sillon->setTexture(secondTexture);
        }
        else
        {
            sillon->setTexture(firstTexture);
        }
    }
}

