#ifndef MATERIAL_H
#define MATERIAL_H

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <iostream>


class Material
{
private:
	GLfloat _ambient[4];
	GLfloat _diffuse[4];
	GLfloat _specular[4];
	GLfloat _emission[4];
	GLfloat _shininess;

	GLuint  _texId;

//on passe en paramètre tout le bloc de texte à parser pour le material
public:
	Material();
	Material(const std::string & materialText);
	~Material();

	void apply();
	

private:
	void openTex(const std::string & path);

};


#endif