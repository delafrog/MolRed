#ifndef AMINOS_H
#define AMINOS_H


#include "datatypes.h"
#include "linalg.h"
//#include "linalg.cpp"

class Aminos
{
public:

	vecT<Molecule> aminos;

	vecT<vecT<char>> amattp;	// типы атомов в аминокислотах pdb

	Aminos();

	void SetAminoAcid(int id_amn,Molecule &mol);
};


#endif