#include "model.hpp"

#include <fstream>
#include <sstream>
#include <cstdio>

Model::Model(const std::string & file)
{
	std::ifstream objFile(file);
	std::string   ligne, nom;
	Groupe * 	  g;
	
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texCoord;

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
					g->setMaterial(search->second);
				}

			}
			else if (mot == "o")
			{
				nom.clear();
				ss >> nom;
				g = new Groupe();
				_groupes.insert(std::pair<const std::string, Groupe *>(nom, g));
				std::cout << "Nouvel objet (" << nom << ")" << std::endl;
			}
			else if (mot == "v")
			{
				GLfloat x, y, z;

				ss >> x >> y >> z;

				g->addVertex(x, y, z);

			}
			else if (mot == "vn")
			{
				GLfloat x, y, z;

				ss >> x >> y >> z;

				g->addNormal(x, y, z);
			}
			else if (mot == "vt")
			{
				GLfloat u, v;

				ss >> u >> v;

				g->addTexCoord(u, v);
			}
			else if (mot == "f")
			{
				std::string face;
				unsigned int v, n, t;

				ss >> face;
				sscanf(face.c_str(), "%u/%u/%u", &v, &n, &t);
				g->addFace(v, t, n);

				ss >> face;
				sscanf(face.c_str(), "%u/%u/%u", &v, &n, &t);
				g->addFace(v, t, n);

				ss >> face;
				sscanf(face.c_str(), "%u/%u/%u", &v, &n, &t);
				g->addFace(v, t, n);
			}
			else
			{
				std::cout << "Tag non géré (" << mot << ")" << std::endl;
			}

		}
	}
}


Model::~Model()
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

void Model::draw()
{
	// for (std::map<const std::string, Groupe *>::iterator i = _groupes.begin(); i != _groupes.end(); ++i)
	// {
	// 	i->second->draw();
	// }
	_groupes.begin()->second->draw();
}

void Model::loadMtl(const std::string & path)
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



Groupe::Groupe():_mat(NULL), _callId(0)
{}

Groupe::~Groupe()
{}

void Groupe::setMaterial(Material * m)
{
	_mat = m;
}

void Groupe::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
	_vertices.push_back(x);
	_vertices.push_back(y);
	_vertices.push_back(z);
}

void Groupe::addNormal(GLfloat x, GLfloat y, GLfloat z)
{
	_normals.push_back(x);
	_normals.push_back(y);
	_normals.push_back(z);
}

void Groupe::addTexCoord(GLfloat u, GLfloat v)
{
	_texCoord.push_back(u);
	_texCoord.push_back(v);
}

void Groupe::addFace(unsigned int v, unsigned int n, unsigned int t)
{
	_faces.push_back(v);
	_faces.push_back(n);
	_faces.push_back(t);
}

void Groupe::addVertexNormalTex(GLfloat vx, GLfloat vy, GLfloat vz, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat u, GLfloat v)
{
	addVertex(vx, vy, vz);
	addNormal(nx, ny, nz);
	addTexCoord(u, v);
}

void Groupe::draw()
{
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
					std::cout << (_faces[i*3]-1) << ", " <<_vertices[(_faces[i*3]-1)*3] << ", " << _vertices[(_faces[i*3]-1)*3 +1]  << ", " << _vertices[(_faces[i*3]-1)*3 + 2] << std::endl;
					glNormal3fv(	_normals.data()  + 	(_faces[i*3 + 1]-1)*3);
					glTexCoord2fv(	_texCoord.data() + 	(_faces[i*3 + 2]-1)*2);
					glVertex3fv(	_vertices.data() + 	(_faces[i*3]-1)*3);
				}
			glEnd();

		glEndList();
	}
}