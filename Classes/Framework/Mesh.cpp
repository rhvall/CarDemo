//
//  Mesh.cpp
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

#include "Mesh.hpp"

//----------------------------------------
//            CONSTRUCTOR
//----------------------------------------
#pragma mark -
#pragma mark CONSTRUCTOR

Mesh::Mesh(void)
{
    for (int i =0; i < MAX_BUFFER; ++i)
    {
        bufferObject[i] = 0;
    }
    
    glGenVertexArraysOES(1, &arrayObject);
    
    numVertices = 0;
    vertices    = NULL;
    colours     = NULL;
	texture		= 0;
	textureCoords = NULL;
    type        = GL_TRIANGLES;

	indices = NULL;
	numIndices = 0;

	normals = NULL;

	tangents = NULL;
	bumpTexture = 0;
}

Mesh::~Mesh(void)
{
    glDeleteVertexArraysOES(1, &arrayObject);
    glDeleteBuffers(MAX_BUFFER, bufferObject);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &bumpTexture);
	delete []vertices;
    delete []colours;
	delete []textureCoords;
	delete []indices;
	delete []normals;
	delete []tangents;
}

//----------------------------------------
//            GRAPHICS MEMORY
//----------------------------------------
#pragma mark -
#pragma mark GRAPHICS MEMORY

void Mesh::bufferData()
{
    glBindVertexArrayOES(arrayObject);
    
    glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_BUFFER);

	if (textureCoords)
    {
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector2), textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}
    
    if (colours)
    {
        glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector4), colours, GL_STATIC_DRAW);
        glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(COLOUR_BUFFER);
    }

	if (indices)
    {
        glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
    }

	if (normals)
    {
        glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	if (tangents)
    {
		glGenBuffers(1, &bufferObject[TANGENT_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TANGENT_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), tangents, GL_STATIC_DRAW);
		glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TANGENT_BUFFER);
	}
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArrayOES(0);
}

void Mesh::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, bumpTexture);
	
	glBindVertexArrayOES(arrayObject);
    //glBindBuffer(GL_ARRAY_BUFFER, arrayObject);
	
	if (bufferObject[INDEX_BUFFER])
    {
        glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
	}
    else
    {
        glDrawArrays(type, 0, numVertices);
	}
	
	glBindVertexArrayOES(0);
}

//----------------------------------------
//            PRIMITIVES
//----------------------------------------
#pragma mark -
#pragma mark PRIMITIVES

Mesh *Mesh::generateTriangle()
{
    Mesh *m = new Mesh();
    m->numVertices = 3;
    m->vertices = new Vector3[m->numVertices];
    m->vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
    m->vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
    m->vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);
    
    m->colours = new Vector4[m->numVertices];
    m->colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    m->colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
    m->colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
    
    m->textureCoords = new Vector2[m->numVertices];
    m->textureCoords[0] = Vector2(0.5f, 0.0f);
    m->textureCoords[1] = Vector2(1.0f, 1.0f);
    m->textureCoords[2] = Vector2(0.0f, 1.0f);
    
    m->bufferData();
    return m;
}

Mesh *Mesh::generateQuad()
{
	Mesh *m = new Mesh();
	m->numVertices = 4;
	m->type = GL_TRIANGLE_STRIP;

	m->vertices		 = new Vector3[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];
	m->colours		 = new Vector4[m->numVertices];
	m->normals       = new Vector3[m->numVertices];
    m->tangents      = new Vector3[m->numVertices];

    m->vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
    m->vertices[1] = Vector3(-1.0f,  1.0f, 0.0f);
    m->vertices[2] = Vector3( 1.0f, -1.0f, 0.0f);
    m->vertices[3] = Vector3( 1.0f,  1.0f, 0.0f);

	m->textureCoords[0] = Vector2(0.0f, 1.0f);
	m->textureCoords[1] = Vector2(0.0f, 0.0f);
    m->textureCoords[2] = Vector2(1.0f, 1.0f);
    m->textureCoords[3] = Vector2(1.0f, 0.0f);

	for (int i = 0; i < 4; ++i)
    {
		m->colours[i] = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
        m->normals[i] = Vector3(0.0f, 0.0f,-1.0f);
        m->tangents[i] = Vector3(1.0f, 0.0f,0.0f);
	}

	m->bufferData();
	return m;
}

Mesh *Mesh::generateCCube(const Vector3 &cubeCenter, const float &radius)
{
	Mesh *m = new Mesh();
    
	m->numIndices = 36;
	m->numVertices = 8;
	m->vertices = new Vector3[m->numVertices];
	m->colours = new Vector4[m->numVertices];
    m->indices = new unsigned int[m->numIndices];
	m->type = GL_TRIANGLES;
    
	m->indices[0] = 0;		m->indices[1] = 1;		m->indices[2] = 2;
    m->indices[3] = 0;      m->indices[4] = 3;		m->indices[5] = 2;
    m->indices[6] = 0;		m->indices[7] = 4;      m->indices[8] = 7;
    m->indices[9] = 0;		m->indices[10] = 3;     m->indices[11] = 7;
	m->indices[24] = 0;     m->indices[25] = 4;     m->indices[26] = 5;
	m->indices[27] = 0;     m->indices[28] = 1;     m->indices[29] = 5;
	m->indices[12] = 5;     m->indices[13] = 1;     m->indices[14] = 2;
    m->indices[15] = 5;     m->indices[16] = 6;     m->indices[17] = 2;
    m->indices[18] = 5;     m->indices[19] = 4;     m->indices[20] = 7;
    m->indices[21] = 5;     m->indices[22] = 6;     m->indices[23] = 7;
	m->indices[30] = 2;     m->indices[31] = 6;     m->indices[32] = 7;
    m->indices[33] = 2;     m->indices[34] = 3;     m->indices[35] = 7;

	m->vertices[0].x = cubeCenter.x - radius;// BOTTOM_FRONT_LEFT
	m->vertices[0].y = cubeCenter.y - radius;
	m->vertices[0].z = cubeCenter.z + radius;
	m->colours[0] = Vector4(0.3f, 0.1f, 0.8f, 1.0f);//0x0C00FFFF;
    
	m->vertices[1].x = cubeCenter.x + radius;// BOTTOM_FRONT_RIGHT
	m->vertices[1].y = cubeCenter.y - radius;
	m->vertices[1].z = cubeCenter.z + radius;
	m->colours[1] = Vector4(0.3f, 0.1f, 0.8f, 1.0f);//0x0C00FFFF;
	
	m->vertices[2].x = cubeCenter.x + radius;// TOP_FRONT_RIGHT
	m->vertices[2].y = cubeCenter.y + radius;
	m->vertices[2].z = cubeCenter.z + radius;
	m->colours[2] = Vector4(0.3f, 0.1f, 0.8f, 1.0f);//0x0C00FFFF;
	
	m->vertices[3].x = cubeCenter.x - radius;// TOP_FRONT_LEFT
	m->vertices[3].y = cubeCenter.y + radius;
	m->vertices[3].z = cubeCenter.z + radius;
	m->colours[3] = Vector4(0.3f, 0.1f, 0.8f, 1.0f);//0x0C00FFFF;
	
	m->vertices[4].x = cubeCenter.x - radius;// BOTTOM_BACK_LEFT
	m->vertices[4].y = cubeCenter.y - radius;
	m->vertices[4].z = cubeCenter.z - radius;
	m->colours[4] = Vector4(0.7f, 0.4f, 0.2f, 1.0f);//0x07A0FFFF;
    
	m->vertices[5].x = cubeCenter.x + radius;// BOTTOM_BACK_RIGHT
	m->vertices[5].y = cubeCenter.y - radius;
	m->vertices[5].z = cubeCenter.z - radius;
	m->colours[5] = Vector4(0.7f, 0.4f, 0.2f, 1.0f);//0x07A0FFFF;
    
	m->vertices[6].x = cubeCenter.x + radius;// TOP_BACK_RIGHT
	m->vertices[6].y = cubeCenter.y + radius;
	m->vertices[6].z = cubeCenter.z - radius;
	m->colours[6] = Vector4(0.7f, 0.4f, 0.2f, 1.0f);//0x07A0FFFF;
	
	m->vertices[7].x = cubeCenter.x - radius;// TOP_BACK_LEFT
	m->vertices[7].y = cubeCenter.y + radius;
	m->vertices[7].z = cubeCenter.z - radius;
	m->colours[7] = Vector4(0.7f, 0.4f, 0.2f, 1.0f);//0x07A0FFFF;
    
	m->bufferData();
	return m;
}

//----------------------------------------
//            NORMALS & TANGENTS
//----------------------------------------
#pragma mark -
#pragma mark NORMALS & TANGENTS

void Mesh::generateNormals()
{
	if (!normals)
    {
		normals = new Vector3[numVertices];
	}

	if (indices)
    {
		for (GLuint i = 0; i < numIndices; i += 3)
        {
			unsigned int a = indices[i];
			unsigned int b = indices[i + 1];
			unsigned int c = indices[i + 2];

			Vector3 normal = Vector3::cross((vertices[b] - vertices[a]), (vertices[c] - vertices[a]));
		
			normals[a] += normal;
			normals[b] += normal;
			normals[c] += normal;
		}
	}
    else
    {
		for (GLuint i = 0; i < numVertices; i += 3)
        {
			Vector3 &a = vertices[i];
			Vector3 &b = vertices[i + 1];
			Vector3 &c = vertices[i + 2];
			
			Vector3 normal = Vector3::cross(c-a, b-a);
		
			normals[i] += normal;
			normals[i + 1] += normal;
			normals[i + 2] += normal;
		}
	}

	for (GLuint i = 0; i < numVertices; ++i)
    {
		normals[i].normalize();
	}
}

void Mesh::generateTangents()
{
	if(!tangents)
    {
		tangents = new Vector3[numVertices];
	}

	if (indices)
    {
		for (GLuint i = 0; i < numIndices; i += 3)
        {
			int a = indices[i];
			int b = indices[i + 1];
			int c = indices[i + 2];

			Vector3 tangent = generateTangent(vertices[a], vertices[b], vertices[c],
											  textureCoords[a], textureCoords[b], textureCoords[c]);
			tangents[a] += tangent;
			tangents[b] += tangent;
			tangents[c] += tangent;
		}
	}
    else
    {
		for (GLuint i = 0; i < numVertices; i +=3)
        {
			Vector3 tangent = generateTangent(vertices[i], vertices[i+1], vertices[i+2],
											  textureCoords[i], textureCoords[i + 1], textureCoords[i+2]);
			tangents[i] += tangent;
			tangents[i + 1] += tangent;
			tangents[i + 2] += tangent;
		}
	}

	for (GLuint i = 0; i < numVertices; ++i)
    {
		tangents[i].normalize();
	}
}

Vector3 Mesh::generateTangent(const Vector3 &a, const Vector3 &b,
						const Vector3 &c, const Vector2 &ta,
						const Vector2 &tb, const Vector2 &tc)
{
	Vector2 coord1 = tc - ta;
	Vector2 coord2 = tb - ta;
	Vector3 vertex1 = c - a;
	Vector3 vertex2 = b - a;
	Vector3 axis = Vector3(vertex1 * coord2.y - vertex2 * coord1.y);
	float factor = 1.0f / (coord1.x * coord2.y - coord2.x * coord1.y);
	return axis * factor;
}