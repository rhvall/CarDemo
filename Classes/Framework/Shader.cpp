//
//  Shader.mm
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

#include "Shader.hpp"

Shader::Shader(string vFile, string fFile, string gFile)
{
	program	= glCreateProgram();
    
    string fullVFile = ResourceManager::getResourcePath().append(vFile);
    string fullFFile = ResourceManager::getResourcePath().append(fFile);
    
	objects[SHADER_VERTEX]	 = generateShader(fullVFile, GL_VERTEX_SHADER);
	objects[SHADER_FRAGMENT] = generateShader(fullFFile, GL_FRAGMENT_SHADER);
//	objects[SHADER_GEOMETRY] = 0; //If Geometry shaders are supported on iOS devides
//
//	if(!gFile.empty()) {
//        
//		objects[SHADER_GEOMETRY]	= GenerateShader(gFile, GL_GEOMETRY_SHADER);
//		glAttachShader(program,objects[SHADER_GEOMETRY]);
//	
//    }

	glAttachShader(program, objects[SHADER_VERTEX]);
	glAttachShader(program, objects[SHADER_FRAGMENT]);

	setDefaultAttributes();
}

Shader::~Shader(void)
{
	for(int i = 0; i < 3; ++i)
    {
		glDetachShader(program, objects[i]);
		glDeleteShader(objects[i]);
	}
    
	glDeleteProgram(program);
}

bool Shader::loadShaderFile(string from, string &into)
{
	ifstream	file;
	string		temp;

	cout << "Loading shader text from " << from << endl << endl;

	file.open(from.c_str());
	if(!file.is_open())
    {
		cout << "File does not exist!" << endl;
		exit(1);
        return false;
	}

	while(!file.eof())
    {
		getline(file,temp);
		into += temp + "\n";
	}

	cout << into << endl << endl;

	file.close();
	cout << "Loaded shader text!" << endl << endl;
	return true;
}

GLuint Shader::generateShader(string from, GLenum type)
{
	cout << "Compiling Shader..." << endl;
	string load;
	if(!loadShaderFile(from,load))
    {
		cout << "Compiling failed! error in the file" << endl;
		loadFailed = true;
		exit(1);
	}

	GLuint shader = glCreateShader(type);

	const char *chars = load.c_str();
	glShaderSource(shader, 1, &chars, 0);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
    {
		cout << "Compiling failed! The estatus:" << endl;
		GLchar error[256];
		glGetShaderInfoLog(shader, sizeof(error), 0, &error[0]);
		cout << error;
		loadFailed = true;
		exit(1);
	}
	
    cout << "Compiling success!" << endl << endl;
	loadFailed = false;
	return shader;
}

bool Shader::linkProgram()
{
	if(loadFailed)
    {
        return false;
    }
	
    glLinkProgram(program); 

	GLint code;
	glGetProgramiv(program, GL_LINK_STATUS, &code);
	return code == GL_TRUE ?  true : false;
}

void Shader::setDefaultAttributes()
{
	glBindAttribLocation(program, VERTEX_BUFFER,  "position");
	glBindAttribLocation(program, COLOUR_BUFFER,  "colour");
	glBindAttribLocation(program, NORMAL_BUFFER,  "normal");
	glBindAttribLocation(program, TANGENT_BUFFER, "tangent");
	glBindAttribLocation(program, TEXTURE_BUFFER, "texCoord");
}