//
//  OBJMesh.cpp
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

#include "OBJMesh.hpp"

/*
OBJ files look generally something like this:

v xpos ypos zpos
..more vertices

vt xtex ytex
...more texcoords

vn xnorm ynorm znorm
...more normals

f vert index / tex index / norm index  vert index / tex index / norm index  vert index / tex index / norm index
...more faces

(i.e there's a set of float/float/float for each vertex of a face)

OBJ files can also be split up into a number of submeshes, making loading them
in even more annoying. 
*/

//----------------------------------------
//	CONSTRUCTOR
//----------------------------------------
#pragma mark -
#pragma mark CONSTRUCTOR

OBJMesh::OBJMesh(std::string filename)
{
    loadOBJMesh(filename);
}

//----------------------------------------
//	FUNCTIONALITY
//----------------------------------------
#pragma mark -
#pragma mark FUNCTIONALITY

bool OBJMesh::loadOBJMesh(std::string filename)
{
	std::ifstream f(filename.c_str(), std::ios::in);

	if(!f)
    {//Oh dear, it can't find the file :(
		return false;
	}

	/*
	Stores the loaded in vertex attributes
	*/
	std::vector<Vector2>inputTexCoords;
	std::vector<Vector3>inputVertices;
	std::vector<Vector3>inputNormals;

	/*
	SubMeshes temporarily get kept in here
	*/
	std::vector<OBJSubMesh *>inputSubMeshes;

	OBJSubMesh *currentMesh = new OBJSubMesh();
	inputSubMeshes.push_back(currentMesh);	//It's safe to assume our OBJ will have a mesh in it ;)

	while(!f.eof())
    {
		std::string currentLine;
		f >> currentLine;

		if(currentLine == OBJCOMMENT)
        {		//This line is a comment, ignore it
			continue;
		}
		else if(currentLine == OBJMESH
                /*|| currentLine == OBJUSEMTL*/ ||
                currentLine == OBJOBJECT)
        {	//This line is a submesh!
			currentMesh = new OBJSubMesh();
			inputSubMeshes.push_back(currentMesh);
		}
		else if(currentLine == OBJVERT)
        {	//This line is a vertex
			Vector3 vertex;
			f >> vertex.x; f >> vertex.y; f >> vertex.z;
			inputVertices.push_back(vertex);
		}
		else if(currentLine == OBJNORM)
        {	//This line is a Normal!
			Vector3 normal;
			f >> normal.x; f >> normal.y; f >> normal.z;
			inputNormals.push_back(normal);
		}
		else if(currentLine == OBJTEX)
        {	//This line is a texture coordinate!
			Vector2 texCoord;
			f >> texCoord.x; f >> texCoord.y;
			/*
			TODO! Some OBJ files might have 3D tex coords...
			*/
			inputTexCoords.push_back(texCoord);
		}
		else if(currentLine == OBJFACE)
        {	//This is an object face!
			if(!currentMesh)
            {
				inputSubMeshes.push_back(new OBJSubMesh());
				currentMesh = inputSubMeshes[inputSubMeshes.size()-1];
			}

			std::string	faceData;		//Keep the entire line in this!
			std::vector<int> faceIndices;	//Keep the extracted indices in here!
		
			getline(f, faceData);		//Use a string helper function to read in the entire face line

			/*
			It's possible an OBJ might have normals defined, but not tex coords!
			Such files should then have a face which looks like this:

				f <vertex index>//<normal index>
				instead of <vertex index>/<tex coord>/<normal index>

				you can be some OBJ files will have "/ /" instead of "//" though... :(
			*/
			bool skipTex = false;
			if(faceData.find("//") != std::string::npos)
            {
				skipTex = true;
			}

			/*
			Count the number of slashes, but also convert the slashes to spaces
			so that string streaming of ints doesn't fail on the slash

				"f  0/0/0" becomes "f 0 0 0" etc
			*/
			for(size_t i = 0; i < faceData.length(); ++i)
            {
				if(faceData[i] == '/')
                {
					faceData[i] = ' ';
				}
			}

			/*
			Now string stream the indices from the string into a temporary
			vector.
			*/
			int tempIndex;
			std::stringstream ss(faceData);

			while(ss >> tempIndex)
            {
				faceIndices.push_back(tempIndex);
			}

			//If the face indices vector is a multiple of 3, we're looking at triangles
			//with some combination of vertices, normals, texCoords
			if((faceIndices.size() % 3) == 0)
            {		//This face is a triangle (probably)!
				if(faceIndices.size() == 3)
                {	//This face has only vertex information;
					currentMesh->vertIndices.push_back(faceIndices.at(0));
					currentMesh->vertIndices.push_back(faceIndices.at(1));
					currentMesh->vertIndices.push_back(faceIndices.at(2));
				}
				else if(faceIndices.size() == 9)
                {	//This face has vertex, normal and tex information!
					for(int i = 0; i < 9; i += 3)
                    {
						currentMesh->vertIndices.push_back(faceIndices.at(i));
						currentMesh->texIndices.push_back(faceIndices.at(i+1));
						currentMesh->normIndices.push_back(faceIndices.at(i+2));
					}
				}
				else if(faceIndices.size() == 6)
                {	//This face has vertex, and one other index...
					for(int i = 0; i < 6; i += 2)
                    {
						currentMesh->vertIndices.push_back(faceIndices.at(i));
						if(!skipTex)
                        {		// a double slash means it's skipping tex info...
							currentMesh->texIndices.push_back(faceIndices.at(i+1));
						}
						else
                        {
							currentMesh->normIndices.push_back(faceIndices.at(i+1));
						}
					}
				}
			}
			else
            {
				//Uh oh! Face isn't a triangle. Have fun adding stuff to this ;)
                cout << "Not a triangle";
			}
		}
		else
        {
			//std::cout << "OBJMesh::LoadOBJMesh Unknown file data:" << currentLine << std::endl;
		}
	}

	f.close();

	//We now have all our mesh data loaded in...Now to convert it into OpenGL vertex buffers!
	for(unsigned int i = 0; i < inputSubMeshes.size(); ++i)
    {
		OBJSubMesh *sm = inputSubMeshes[i];

		/*
		We're going to be lazy and turn the indices into an absolute list
		of vertex attributes (it makes handling the submesh list easier)
		*/
		if(!sm->vertIndices.empty())
        {
			OBJMesh *m = new OBJMesh();

			m->numVertices = sm->vertIndices.size();
            
			m->vertices	= new Vector3[m->numVertices];
            static bool colorr = false;
            m->colours = new Vector4[m->numVertices];
			for(unsigned int j = 0; j < sm->vertIndices.size(); ++j)
            {
				m->vertices[j] = inputVertices[sm->vertIndices[j]-1];
                if (colorr == false)
                {
                    Vector3 ref = m->vertices[j];
                    m->colours[j] = Vector4(ref.x, ref.y, ref.z, 1.0f);
                }
                else
                {
                    m->colours[j] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
                }
			}
colorr = true;
			if(!sm->texIndices.empty())
            {
				m->textureCoords = new Vector2[m->numVertices];
				for(unsigned int j = 0; j < sm->texIndices.size(); ++j)
                {
					m->textureCoords[j] = inputTexCoords[sm->texIndices[j]-1];
				}
			}

#ifndef OBJ_USE_NORMALS
			if(sm->normIndices.empty())
            {
				m->generateNormals();
			}
			else
            {
				m->normals = new Vector3[m->numVertices];

				for(unsigned int j = 0; j < sm->normIndices.size(); ++j)
                {
					m->normals[j] = inputNormals[sm->normIndices[j] - 1];
				}
			}
#endif
#ifndef OBJ_USE_TANGENTS_BUMPMAPS
			m->generateTangents();
#endif

			m->bufferData();
			addChild(m);
		}
        
		delete inputSubMeshes[i];
	}
	return true;
}

/*
Draws the current OBJMesh. The handy thing about overloaded virtual functions
is that they can still run the code they have 'overridden', by calling the 
parent class function as you would a static function. So all of the new stuff
you've been building up in the Mesh class as the tutorials go on, will 
automatically be used by this overloaded function. Once 'this' has been drawn,
all of the children of 'this' will be drawn
*/
void OBJMesh::draw()
{
	Mesh::draw();
	for(unsigned int i = 0; i < children.size(); ++i)
    {
		children.at(i)->setTexture(texture);
		children.at(i)->draw();
	}
};