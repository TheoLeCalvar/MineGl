#include "moteur.hpp"
#include <stdlib.h> //srand
#include <ctime>

int main(int argc, char **argv)
{
	srand( static_cast<unsigned> (time(0)));

	Moteur * m = Moteur::create();

	m->start();

	return 0;
}