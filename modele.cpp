#include "modele.hpp"

#include <fstream>
#include <sstream>
#include <cstdio>

Modele::Modele(const std::string & file)
{
	parse(file);
}

void Modele::parse(const std::string & file)
{
	std::ifstream objFile(file);
	std::string   ligne, nom;
	Groupe * 	  g;


	while(std::getline(objFile, ligne))
	{
		if (ligne[0] != '#')
		{
			std::istringstream ss(ligne);
			std::string mot, parametre;

			ss >> mot;

			if (mot == "mtllib")
			{
				ss >> parametre;				
				std::cout << "Chargement du fichier de material (" << parametre << ")" << std::endl;

				if (parametre[0] == '/')
				{
					loadMtl(parametre);
				}
				else
				{
					std::string path = file.substr(0, file.rfind('/')+1);
					path.append(parametre);

					loadMtl(path);
				}

			}
			else if (mot == "usemtl")
			{
				std::string mtl;
				std::map<const std::string, Material *>::const_iterator search;

				ss >> mtl;
				search = _materials.find(mtl);

				if (search == _materials.end())
				{
					std::cout << "Impossible de trouver le material '" << mtl << "'" << std::endl;
				}
				else
				{
					std::cout << "Set material " << search->first << " for " << nom << std::endl;
					g->setMaterial(search->second);
				}

			}
			else if (mot == "o" || mot == "g")
			{
				nom.clear();
				ss >> nom;
				g = new Groupe(&_vertices, &_normals, &_texCoord);
				g->useTex(_useTex);
				_groupes.insert(std::pair<const std::string, Groupe *>(nom, g));
				std::cout << "Nouvel objet (" << nom << ")" << std::endl;
			}
			else if (mot == "v")
			{
				GLfloat x, y, z;

				ss >> x >> y >> z;

				_vertices.push_back(x);
				_vertices.push_back(y);
				_vertices.push_back(z);

			}
			else if (mot == "vn")
			{
				GLfloat x, y, z;

				ss >> x >> y >> z;

				_normals.push_back(x);
				_normals.push_back(y);
				_normals.push_back(z);
			}
			else if (mot == "vt")
			{
				GLfloat u, v;

				ss >> u >> v;

				_texCoord.push_back(u);
				_texCoord.push_back(v);
			}
			else if (mot == "f")
			{
				std::string face;
				unsigned int v, n, t;

				for (int i = 0; i < 3; ++i)
				{
					ss >> face;
					if (_useTex)
					{
						sscanf(face.c_str(), "%u/%u/%u", &v, &t, &n);
					}
					else
					{
						sscanf(face.c_str(), "%u//%u", &v, &n);
						t = 0;
					}
					g->addFace(v, t, n);
				}

			}
			else
			{
				std::cout << "Tag non géré (" << mot << ")" << std::endl;
			}

		}
	}
}

Modele::~Modele()
{
	for (std::map<const std::string, Material *>::iterator i = _materials.begin(); i != _materials.end(); ++i)
	{
		delete i->second;
	}

	for (std::map<const std::string, Groupe *>::iterator i = _groupes.begin(); i != _groupes.end(); ++i)
	{
		delete i->second;
	}
}

void Modele::draw()
{
	for (std::map<const std::string, Groupe *>::iterator i = _groupes.begin(); i != _groupes.end(); ++i)
	{
		i->second->draw();
	}
}

void Modele::loadMtl(const std::string & path)
{
	std::ifstream matFile(path);
	std::string ligne, buffer, nom;

	while(std::getline(matFile, ligne))
	{
		if (ligne[0] != '#')
		{
			std::istringstream ss(ligne);
			std::string mot;

			ss >> mot;

			if (mot == "newmtl")
			{
				if (!nom.empty())
				{
					Material * tmp = new Material(buffer);
					_materials.insert(std::pair<const std::string, Material *>(nom, tmp)); 
					buffer.clear();
					nom.clear();
					tmp = NULL;
				}

				ss >> nom;
				std::cout << "Chargement d'un nouveau material " << nom << std::endl;
			}
			else
			{
				buffer.append(ligne);
				buffer.append("\n");
			}
		}
	}
	//pour charger le dernier matérial de la liste
	Material * tmp = new Material(buffer);
	_materials.insert(std::pair<const std::string, Material *>(nom, tmp)); 
	buffer.clear();
	nom.clear();
	tmp = NULL; 


	std::cout << _materials.size() << " matériaux chargés" << std::endl;
}

void Modele::useTex(bool b)
{
	_useTex = b;

	for (std::map<const std::string, Groupe *>::iterator i = _groupes.begin(); i != _groupes.end(); ++i)
	{
		i->second->useTex(_useTex);
	}
}

Groupe::Groupe(std::vector<GLfloat> * vertices, std::vector<GLfloat> * normals, std::vector<GLfloat> * texCoord):_vertices(vertices), _normals(normals), _texCoord(texCoord), _mat(NULL), _callId(0)
{}

Groupe::~Groupe()
{}

void Groupe::setMaterial(Material * m)
{
	_mat = m;
}

void Groupe::addFace(unsigned int v, unsigned int t, unsigned int n)
{
	_faces.push_back(v);
	_faces.push_back(n);
	if (_useTex)
	{
		_faces.push_back(t);
	}
	else
	{
		_faces.push_back(0);
	}
}


void Groupe::draw()
{
	glDisable(GL_BLEND);

	if (_callId)
	{
		glCallList(_callId);
	}
	else
	{
		_callId = glGenLists(1);

		glNewList(_callId, GL_COMPILE_AND_EXECUTE);
			if (_mat)
			{
				_mat->apply();
			}

			glBegin(GL_TRIANGLES);
				for (unsigned int i = 0; i*3 < _faces.size(); ++i)
				{
					glNormal3fv(	_normals->data()  + 	(_faces[i*3 + 1]-1)*3);

					if (_useTex)
						glTexCoord2fv(	_texCoord->data() + 	(_faces[i*3 + 2]-1)*2);

					glVertex3fv(	_vertices->data() + 	(_faces[i*3]-1)*3);

				}
			glEnd();

		glEndList();
	}
}
