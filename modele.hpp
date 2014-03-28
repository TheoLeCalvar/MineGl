#ifndef MODEL_H
#define MODEL_H 

#include <vector>
#include <map>

#include "material.hpp"

class Groupe;

class Modele
{
private:
	std::map<const std::string, Groupe *> _groupes;
	std::map<const std::string, Material *> _materials;

	std::vector<GLfloat> 	_vertices;
	std::vector<GLfloat> 	_normals;
	std::vector<GLfloat> 	_texCoord;

	bool					_useTex;

public:
	Modele(const std::string & file);
	~Modele();

	virtual void draw();
	void 	useTex(bool b);
	bool 	useTex(){return _useTex;}
	
private:
	void loadMtl(const std::string & path);
	void parse(const std::string & file);
};


class Groupe
{
private:
	std::vector<GLfloat> *_vertices;
	std::vector<GLfloat> *_normals;
	std::vector<GLfloat> *_texCoord;
	std::vector<unsigned int> _faces;

	Material * _mat;

	GLuint 		_callId;

	bool 		_useTex;

public:
	Groupe(std::vector<GLfloat> * vertices, std::vector<GLfloat> * normals, std::vector<GLfloat> * texCoord);
	~Groupe();

	void setMaterial(Material * m);
	void addFace(unsigned int v, unsigned int n, unsigned int t);

	void draw();

	void 	useTex(bool b){_useTex = b;}
	bool 	useTex(){return _useTex;}
	
};




#endif
