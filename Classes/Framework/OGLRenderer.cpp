//
//  OGLRenderer.cpp
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

#include "OGLRenderer.hpp"

/*
Creates an OpenGL 3.2 CORE PROFILE rendering context. Sets itself
as the current renderer of the passed 'parent' Window. Not the best
way to do it - but it kept the Tutorial code down to a minimum!
*/

//----------------------------------------
//	CONSTRUCTOR
//----------------------------------------
#pragma mark -
#pragma mark CONSTRUCTOR

OGLRenderer::OGLRenderer(float width, float height)
{
    //glClearColor(0.5f,0.5f,0.2f,1.0f);
	init = false;
    currentShader = 0;
    this->width = width;
    this->height = height;
    
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER,
                              renderbuffer);
    glViewport(0, 0, width, height);

}

void OGLRenderer::generateDepthBuffer()
{
    glGenRenderbuffers(1, &depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER,
                              depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
        std::cout << "Failed to make complete depth framebuffer object" << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
		exit(0);
	}
    glEnable (GL_DEPTH_TEST);

}

/*
Destructor. Deletes the default shader, and the OpenGL rendering context.
*/
OGLRenderer::~OGLRenderer(void)
{
	delete currentShader;
}

/*
Returns TRUE if everything in the constructor has gone to plan.
Check this to end the application if necessary...
*/
bool OGLRenderer::hasInitialized() const
{
	return init;
}

/*
Used by some later tutorials when we want to have framerate-independent
updates on certain datatypes. Really, OGLRenderer should have its own
timer, so it can just sit and look after itself (potentially even in
another thread...), but it's fine for the tutorials.

STUDENTS: Don't put your entity update routine in this, or anything like
that - it's just asking for trouble! Strictly speaking, even the camera
shouldn't be in here...(I'm lazy)
*/

/*
Updates the uniform matrices of the current shader. Assumes that
the shader has uniform matrices called modelMatrix, viewMatrix,
projMatrix, and textureMatrix. Updates them with the relevant
matrix data. Sanity checks currentShader, so is always safe to
call.
*/

//----------------------------------------
//	SHADER
//----------------------------------------
#pragma mark -
#pragma mark SHADER

void OGLRenderer::updateShaderMatrices()
{
	if(currentShader)
    {
		glUniformMatrix4fv(glGetUniformLocation(currentShader->getProgram(), "modelMatrix"), 1, false, (float*)&modelMatrix);
		glUniformMatrix4fv(glGetUniformLocation(currentShader->getProgram(), "viewMatrix") , 1, false, (float*)&viewMatrix);
		glUniformMatrix4fv(glGetUniformLocation(currentShader->getProgram(), "projMatrix") , 1, false, (float*)&projMatrix);
//		glUniformMatrix4fv(glGetUniformLocation(currentShader->getProgram(), "textureMatrix"), 1,false, (float*)&textureMatrix);
	}
}

void OGLRenderer::setCurrentShader(Shader*s)
{
	currentShader = s;
	glUseProgram(s->getProgram());
}

//----------------------------------------
//	TEXTURES
//----------------------------------------
#pragma mark -
#pragma mark TEXTURES

void OGLRenderer::setTextureRepeating(GLuint target, bool repeating)
{
	glBindTexture(GL_TEXTURE_2D, target);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeating ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeating ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//----------------------------------------
//	FUNTIONALITY
//----------------------------------------
#pragma mark -
#pragma mark FUNTIONALITY

void OGLRenderer::drawLine2D(const Vector3 &from, const Vector3 &to, uint32 colourargb)
{
	Matrix4 tempProj	= projMatrix;
//	Matrix4 tempModel	= modelMatrix;
//	Matrix4 tempView	= viewMatrix;
    
	projMatrix = Matrix4::orthographic(-1,1,width,0,height,0);
	modelMatrix.identity();
	viewMatrix.identity();
    
	updateShaderMatrices();
    
	GLuint bufferObject[2];
    
	Vector3 positions[2] = { from, to };
    
	Vector4 colours[2];
    
    glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vector3), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_BUFFER);
    
    glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vector4), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(COLOUR_BUFFER);     
    
    
	glDrawArrays(GL_LINES, 0, 2);
    
    glDeleteBuffers(2, bufferObject);

    projMatrix = tempProj;
	viewMatrix = viewMatrix;
	modelMatrix = modelMatrix;
	updateShaderMatrices();
}
