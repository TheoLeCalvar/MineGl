#ifndef MODEL_H
#define MODEL_H 

#include <vector>
#include <map>

#include "material.hpp"

class Groupe
{
private:
	std::vector<GLfloat> _vertices;
	std::vector<GLfloat> _normals;
	std::vector<GLfloat> _texCoord;
	std::vector<unsigned int> _faces;

	Material * _mat;

	GLuint 		_callId;

public:
	Groupe();
	~Groupe();

	void setMaterial(Material * m);

	void addVertex(GLfloat x, GLfloat y, GLfloat z);
	void addNormal(GLfloat x, GLfloat y, GLfloat z);
	void addTexCoord(GLfloat u, GLfloat v);
	void addFace(unsigned int v, unsigned int n, unsigned int t);
	void addVertexNormalTex(GLfloat vx, GLfloat vy, GLfloat vz, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat u, GLfloat v);

	void draw();
	
};


class Model
{
private:
	std::map<const std::string, Groupe *> _groupes;
	std::map<const std::string, Material *> _materials;

public:
	Model(const std::string & file);
	~Model();

	virtual void draw();
	
private:
	void loadMtl(const std::string & path);
};

#endif