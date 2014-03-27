#include "material.hpp"
#include <sstream>
#include <SOIL/SOIL.h>

//material par défaut
Material::Material():_shininess(0.0f), _texId(0)
{
	_ambient[0] = 0.0f;
	_ambient[1] = 0.0f;
	_ambient[2] = 0.0f;
	_ambient[3] = 0.0f;

	_diffuse[0] = 0.8f;
	_diffuse[1] = 0.8f;
	_diffuse[2] = 0.8f;
	_diffuse[3] = 1.0f;

	_specular[0] = 0.0f;
	_specular[1] = 0.0f;
	_specular[2] = 0.0f;
	_specular[3] = 0.0f;

	_emission[0] = 0.0f;
	_emission[1] = 0.0f;
	_emission[2] = 0.0f;
	_emission[3] = 1.0f;

}

Material::Material(const std::string & texte)
{
	std::istringstream iss(texte);
	std::string ligne;

	while(std::getline(iss, ligne))
	{
		std::istringstream ss(ligne);
		std::string mot, parametre;

		ss >> mot;
		

		if (mot == "Ns")
		{
			ss >> _shininess;

			std::cout << "Ns found (value " << _shininess << ")" << std::endl;			

		}
		else if (mot == "Ka")
		{
			ss >> _ambient[0];
			ss >> _ambient[1];
			ss >> _ambient[2];

			std::cout << "Ka found (value " << _ambient[0] << "," << _ambient[1] << "," << _ambient[2] <<  ")" << std::endl;	
		}
		else if (mot == "Kd")
		{
			ss >> _diffuse[0];
			ss >> _diffuse[1];
			ss >> _diffuse[2];

			std::cout << "Kd found (value " << _diffuse[0] << "," << _diffuse[1] << "," << _diffuse[2] <<  ")" << std::endl;			
		}
		else if (mot == "Ks")
		{
			ss >> _specular[0];
			ss >> _specular[1];
			ss >> _specular[2];

			std::cout << "Ks found (value " << _specular[0] << "," << _specular[1] << "," << _specular[2] <<  ")" << std::endl;			
		}
		else if (mot == "map_Kd")
		{
			std::string filename;
			ss >> filename;

			openTex(filename);

			std::cout << "map_Kd found (value " << filename << ")" << std::endl;
		}
		else if (mot != "")
		{
			std::cout << "Material : Prefixe non pris en charge (" << mot << ")" << std::endl;
		}
	}
}

Material::~Material()
{
	glDeleteTextures(1, &_texId);
}

void Material::openTex(const std::string & path)
{
	int width, height;
	unsigned char * image;

	glEnable(GL_TEXTURE_2D);

	image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &_texId);
	glBindTexture(GL_TEXTURE_2D, _texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	SOIL_free_image_data(image);
}

void Material::apply()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, _emission);
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, _shininess);

	if (_texId)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _texId);
	}

}