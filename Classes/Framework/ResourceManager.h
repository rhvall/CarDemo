//
//  ResourceManager.h
//  CarDemo
//
//  Created by RHVT on 27/11/12.
//  Copyright (c) 2012 Mittra Software. All rights reserved.
//

#pragma once

#import <QuartzCore/QuartzCore.h>
#include <string>
#include <fstream>
#include <unistd.h>

#include "OGLRenderer.hpp"

class ResourceManager
{
public:
    static std::string getResourcePath();
    static GLuint generateTexture(const std::string &name);

protected:
    
private:
    
};
