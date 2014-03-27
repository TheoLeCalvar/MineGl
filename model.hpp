#ifndef MODEL_H
#define MODEL_H 

#include <vector>
#include <map>

#include "material.hpp"

class Groupe
{
private:
	std::vector<GLfloat> *_vertices;
	std::vector<GLfloat> *_normals;
	std::vector<GLfloat> *_texCoord;
	std::vector<unsigned int> _faces;

	Material * _mat;

	GLuint 		_callId;

public:
	Groupe(std::vector<GLfloat> * vertices, std::vector<GLfloat> * normals, std::vector<GLfloat> * texCoord);
	~Groupe();

	void setMaterial(Material * m);
	void addFace(unsigned int v, unsigned int n, unsigned int t);

	void draw();
	
};


class Model
{
private:
	std::map<const std::string, Groupe *> _groupes;
	std::map<const std::string, Material *> _materials;

	std::vector<GLfloat> 	_vertices;
	std::vector<GLfloat> 	_normals;
	std::vector<GLfloat> 	_texCoord;

public:
	Model(const std::string & file);
	~Model();

	virtual void draw();
	
private:
	void loadMtl(const std::string & path);
	void parse(const std::string & file);
};

#endif