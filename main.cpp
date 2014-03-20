#include "moteur.hpp"
#include <stdlib.h> //srand
#include <iostream>
#include <ctime>

#include "vect3D.hpp"

int main(int argc, char **argv)
{
	srand( static_cast<unsigned> (time(0)));


	int foo;

	// std::cin >> foo;


	Moteur * m = Moteur::create();

	m->start();

	Moteur::destroy();

	return 0;
}