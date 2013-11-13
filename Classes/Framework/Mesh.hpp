//
//  Mesh.hpp
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

enum MeshBuffer
{ 
    VERTEX_BUFFER, 
    COLOUR_BUFFER,
	TEXTURE_BUFFER,
	NORMAL_BUFFER,
	TANGENT_BUFFER,
	INDEX_BUFFER,
    MAX_BUFFER
};

class Mesh
{
public:
    Mesh(void);
    ~Mesh(void);

	void setTexture(GLuint tex) { texture = tex;}
	GLuint getTexture() { return texture;}
	void setBumpMap(GLuint tex) { bumpTexture = tex; }
	GLuint getBumpMap() { return bumpTexture; }
    
    virtual void draw();
    static Mesh *generateTriangle();
    static Mesh *generateCCube(const Vector3 &cubeCenter, const float &radius);
	static Mesh *generateQuad();


protected:
	Vector3 generateTangent(const Vector3 &a, const Vector3 &b,
                            const Vector3 &c, const Vector2 &ta,
                            const Vector2 &tb, const Vector2 &tc);
    void bufferData();
    void generateNormals();
	void generateTangents();

    GLuint bufferObject[MAX_BUFFER];
    GLuint numVertices;
    GLuint type;
	GLuint arrayObject;
	GLuint texture;
    
	Vector2 *textureCoords;
    Vector3 *vertices;
    Vector4 *colours;

	GLuint numIndices;
	unsigned int *indices;

	Vector3 *normals;
	Vector3 *tangents;
	GLuint bumpTexture;
};

