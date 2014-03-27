#include "moteur.hpp"
#include <stdlib.h> //srand
#include <iostream>
#include <ctime>


#include "vect3D.hpp"

int main(int , char **)
{
	srand( static_cast<unsigned> (time(0)));


	Moteur * m = Moteur::create();

	m->start();

	Moteur::destroy();

	return 0;
}
