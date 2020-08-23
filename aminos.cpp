#ifndef AMINOS_CPP
#define AMINOS_CPP

#include "aminos.h"


Aminos::Aminos()
{
	aminos.setlen(20);

	aminos.x[0].Name.add("ALA");
	aminos.x[1].Name.add("ARG");
	aminos.x[2].Name.add("ASN");
	aminos.x[3].Name.add("ASP");
	aminos.x[4].Name.add("CYS");
	aminos.x[5].Name.add("GLN");
	aminos.x[6].Name.add("GLU");
	aminos.x[7].Name.add("GLY");
	aminos.x[8].Name.add("HIS");
	aminos.x[9].Name.add("ILE");
	aminos.x[10].Name.add("LEU");
	aminos.x[11].Name.add("LYS");
	aminos.x[12].Name.add("MET");
	aminos.x[13].Name.add("PHE");
	aminos.x[14].Name.add("PRO");
	aminos.x[15].Name.add("SER");
	aminos.x[16].Name.add("THR");
	aminos.x[17].Name.add("TRP");
	aminos.x[18].Name.add("TYR");
	aminos.x[19].Name.add("VAL");

	amattp.setlen(83);
	
	amattp.x[0].add("C   ");
	amattp.x[1].add("CA  ");
	amattp.x[2].add("CB  ");
	amattp.x[3].add("CD  ");
	amattp.x[4].add("CD1 ");
	amattp.x[5].add("CD2 ");
	amattp.x[6].add("CE  ");
	amattp.x[7].add("CE1 ");
	amattp.x[8].add("CE2 ");
	amattp.x[9].add("CE3 ");
	amattp.x[10].add("CG  ");
	amattp.x[11].add("CG1 ");
	amattp.x[12].add("CG2 ");
	amattp.x[13].add("CH2 ");
	amattp.x[14].add("CZ  ");
	amattp.x[15].add("CZ2 ");
	amattp.x[16].add("CZ3 ");
	amattp.x[17].add("H   ");
	amattp.x[18].add("H1  ");
	amattp.x[19].add("H2  ");
	amattp.x[20].add("HA  ");
	amattp.x[21].add("HA2 ");
	amattp.x[22].add("HA3 ");
	amattp.x[23].add("HB  ");
	amattp.x[24].add("HB1 ");
	amattp.x[25].add("HB2 ");
	amattp.x[26].add("HB3 ");
	amattp.x[27].add("HD1 ");
	amattp.x[28].add("HD11");
	amattp.x[29].add("HD12");
	amattp.x[30].add("HD13");
	amattp.x[31].add("HD2 ");
	amattp.x[32].add("HD21");
	amattp.x[33].add("HD22");
	amattp.x[34].add("HD23");
	amattp.x[35].add("HD3 ");
	amattp.x[36].add("HE  ");
	amattp.x[37].add("HE1 ");
	amattp.x[38].add("HE2 ");
	amattp.x[39].add("HE21");
	amattp.x[40].add("HE22");
	amattp.x[41].add("HE3 ");
	amattp.x[42].add("HG  ");
	amattp.x[43].add("HG1 ");
	amattp.x[44].add("HG11");
	amattp.x[45].add("HG12");
	amattp.x[46].add("HG13");
	amattp.x[47].add("HG2 ");
	amattp.x[48].add("HG21");
	amattp.x[49].add("HG22");
	amattp.x[50].add("HG23");
	amattp.x[51].add("HG3 ");
	amattp.x[52].add("HH  ");
	amattp.x[53].add("HH11");
	amattp.x[54].add("HH12");
	amattp.x[55].add("HH2 ");
	amattp.x[56].add("HH21");
	amattp.x[57].add("HH22");
	amattp.x[58].add("HXT ");
	amattp.x[59].add("HZ  ");
	amattp.x[60].add("HZ1 ");
	amattp.x[61].add("HZ2 ");
	amattp.x[62].add("HZ3 ");
	amattp.x[63].add("N   ");
	amattp.x[64].add("ND1 ");
	amattp.x[65].add("ND2 ");
	amattp.x[66].add("NE  ");
	amattp.x[67].add("NE1 ");
	amattp.x[68].add("NE2 ");
	amattp.x[69].add("NH1 ");
	amattp.x[70].add("NH2 ");
	amattp.x[71].add("NZ  ");
	amattp.x[72].add("O   ");
	amattp.x[73].add("OD1 ");
	amattp.x[74].add("OD2 ");
	amattp.x[75].add("OE1 ");
	amattp.x[76].add("OE2 ");
	amattp.x[77].add("OG  ");
	amattp.x[78].add("OG1 ");
	amattp.x[79].add("OH  ");
	amattp.x[80].add("OXT ");
	amattp.x[81].add("SD  ");
	amattp.x[82].add("SG  ");


	/*aminos.x[0].ReInit(12);
	aminos.x[1].ReInit(25);
	aminos.x[2].ReInit(16);
	aminos.x[3].ReInit(15);
	aminos.x[4].ReInit(13);
	aminos.x[5].ReInit(19);
	aminos.x[6].ReInit(18);
	aminos.x[7].ReInit(9);
	aminos.x[8].ReInit(19);
	aminos.x[9].ReInit(21);
	aminos.x[10].ReInit(21);
	aminos.x[11].ReInit(23);
	aminos.x[12].ReInit(19);
	aminos.x[13].ReInit(22);
	aminos.x[14].ReInit(16);
	aminos.x[15].ReInit(13);
	aminos.x[16].ReInit(16);
	aminos.x[17].ReInit(26);
	aminos.x[18].ReInit(23);
	aminos.x[19].ReInit(18);*/

}

void Aminos::SetAminoAcid(int id_amn, Molecule &mol)
{
	if((id_amn>=0)&&(id_amn<20))
	{
		vecT<char> str;
		str.pst(aminos.x[id_amn].Name);
		aminos.x[id_amn]	= mol;
		aminos.x[id_amn].Name.pst(str);
	}
}



#endif