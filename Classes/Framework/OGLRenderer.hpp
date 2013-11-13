//
//  OGLRenderer.hpp
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

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "Vector.hpp"
#include "Quaternion.hpp"
#include "Matrix.hpp"

#include "Shader.hpp"
#include "Mesh.hpp"

#ifdef DEBUG
#define GL_BREAKPOINT glUniform4uiv(0,0,0);//Invalid, but triggers gdebugger ;)
#else
#define GL_BREAKPOINT //
#endif

#ifndef uint32
#define uint32 unsigned int
#endif

static const float biasValues[16] =
{
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0
};

static const Matrix4 biasMatrix(const_cast<float*>(biasValues));

class Shader;

class OGLRenderer
{
public:
    OGLRenderer(float width, float height);
	virtual ~OGLRenderer(void);

    void generateDepthBuffer();
	virtual void renderScene() = 0;
	virtual void updateScene(float msec) = 0;

	bool hasInitialized() const;
    
    void drawLine2D(const Vector3 &from, const Vector3 &to, uint32 colourargb);
    
protected:
	void updateShaderMatrices();
	void setCurrentShader(Shader *s);
	void setTextureRepeating(GLuint target, bool state);

	Shader *currentShader;

	Matrix4 projMatrix;	//Projection matrix
	Matrix4 modelMatrix; //Model matrix. NOT MODELVIEW
	Matrix4 viewMatrix;	//View matrix
	Matrix4 textureMatrix;	//Texture matrix
    
    GLuint framebuffer;
    GLuint renderbuffer;
    GLuint depthbuffer;

	int width;			//Render area width (not quite the same as window width)
	int height;			//Render area height (not quite the same as window height)
	bool init;			//Did the renderer initialise properly?
};