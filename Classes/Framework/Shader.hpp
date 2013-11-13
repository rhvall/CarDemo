//
//  Shader.h
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

#import <QuartzCore/QuartzCore.h>

#include <string>
#include <fstream>
#include <unistd.h>

#include "OGLRenderer.hpp"
#include "ResourceManager.h"

#define SHADER_VERTEX 0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2

using namespace std;

class Shader
{
public:
    Shader(string vFile, string fFile, string gFile = "");
    ~Shader(void);

    GLuint getProgram() { return program; }
    bool linkProgram();
        
protected:
    void setDefaultAttributes();
    bool loadShaderFile(string from, string &into);
    GLuint generateShader(string from, GLenum type);
    GLuint objects[2];
    GLuint program;
    
    bool loadFailed;
};

