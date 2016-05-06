#include "fxlib.h"

typedef struct
{
	char number;
	char charge;
	char x, y;
	union
	{
		unsigned char eByte;
		struct
		{
			unsigned char t:2;
			unsigned char r:2;
			unsigned char b:2;
			unsigned char l:2;
		}e;
	}	
	Electrons;
}
Atom;

int category = 0;
int selectedX = 0;
int displayAtoms = 0;
int camX = 0, camY = 0;
DISPBOX left, across;
char* symbols[] = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr"};
Atom cat1[16];
Atom atoms[2];

int AddIn_main(int isAppli, unsigned short OptionNum)
{
	unsigned int key;
	left.left = 0; left.top = 0; left.right = 21; left.bottom = 63;
	across.left = 22; across.right = 127;
	
	cat1[0].number = 1; cat1[0].charge = 0; cat1[0].Electrons.eByte = 0x01;
	cat1[1].number = 5; cat1[1].charge = 0; cat1[1].Electrons.eByte = 0x15;
	cat1[2].number = 6; cat1[2].charge = 0; cat1[2].Electrons.eByte = 0x55;
	cat1[3].number = 7; cat1[3].charge = 0; cat1[3].Electrons.eByte = 0x57;
	cat1[4].number = 8; cat1[4].charge = 0; cat1[4].Electrons.eByte = 0x77;
	cat1[5].number = 9; cat1[5].charge = 0; cat1[5].Electrons.eByte = 0x7F;
	cat1[6].number = 14; cat1[6].charge = 0; cat1[6].Electrons.eByte = 0x55;
	cat1[7].number = 15; cat1[7].charge = 0; cat1[7].Electrons.eByte = 0x57;
	cat1[8].number = 16; cat1[8].charge = 0; cat1[8].Electrons.eByte = 0x77;
	cat1[9].number = 17; cat1[9].charge = 0; cat1[9].Electrons.eByte = 0x7F;
	cat1[10].number = 34; cat1[10].charge = 0; cat1[10].Electrons.eByte = 0x77;
	cat1[11].number = 35; cat1[11].charge = 0; cat1[11].Electrons.eByte = 0x7F;

	atoms[0].number =  1; atoms[0].charge = 0; atoms[0].x = 3; atoms[0].y = 1; atoms[0].Electrons.eByte = 0x01;
	atoms[1].number = 10; atoms[1].charge = 0; atoms[1].x = 3; atoms[1].y = 0; atoms[1].Electrons.eByte = 0xFF;
	atoms[2].number =  7; atoms[2].charge = 0; atoms[2].x = 2; atoms[2].y = 1; atoms[2].Electrons.eByte = 0x57;
	render();
	
	while(1)
	{
		GetKey(&key);
		if(key == KEY_CTRL_UP && category > 0) category--;
		if(key == KEY_CTRL_DOWN && category < 2) category++;
		if(key == KEY_CTRL_RIGHT && selectedX < 16) selectedX++;
		if(key == KEY_CTRL_LEFT && selectedX > 0) selectedX--;
		if(key == KEY_CTRL_EXE) 
		{
			if(!displayAtoms) displayAtoms = 1;
			else displayAtoms = 0;
			selectedX = 0;
		}
		if(key == KEY_CTRL_EXIT) displayAtoms = 0;
		if(key == KEY_CHAR_6) camX++;
		if(key == KEY_CHAR_4) camX--;
		if(key == KEY_CHAR_8) camY++;
		if(key == KEY_CHAR_2) camY--;
		render();
	}

	return 1;
}

int render()
{
	int i;
	
	Bdisp_AllClr_VRAM();
		
	renderAtom(atoms[0]);
	renderAtom(atoms[1]);
	renderAtom(atoms[2]);
	
	Bdisp_AreaClr_VRAM(&left);
	for(i = 0; i < 64; i++) Bdisp_SetPoint_VRAM(21, i, 1);
	for(i = 0; i < 22; i++) 
	{
		Bdisp_SetPoint_VRAM(i, 0, 1);
		Bdisp_SetPoint_VRAM(i, 21, 1);
		Bdisp_SetPoint_VRAM(i, 42, 1);
		Bdisp_SetPoint_VRAM(i, 63, 1);
	}
	
	PrintMini(1, 8, "N,O,F", 0);
	PrintMini(5, 30, "NA", 0); PrintMini(15, 28, "+", 0);
	for(i = 0; i < 7; i++) Bdisp_SetPoint_VRAM(7 + i, 60, 1);
	for(i = 0; i < 3; i++)
	{
		Bdisp_SetPoint_VRAM(4 + i, 54 + 2 * i, 1);
		Bdisp_SetPoint_VRAM(4 + i, 55 + 2 * i, 1);
		Bdisp_SetPoint_VRAM(16 - i, 54 + 2 * i, 1);
		Bdisp_SetPoint_VRAM(16 - i, 55 + 2 * i, 1);
	}
	Bdisp_SetPoint_VRAM(5, 53, 1); Bdisp_SetPoint_VRAM(6, 53, 1); Bdisp_SetPoint_VRAM(14, 53, 1); Bdisp_SetPoint_VRAM(15, 53, 1);
	Bdisp_SetPoint_VRAM(7, 52, 1); Bdisp_SetPoint_VRAM(13, 52, 1);
	Bdisp_SetPoint_VRAM(8, 51, 1); Bdisp_SetPoint_VRAM(9, 51, 1); Bdisp_SetPoint_VRAM(11, 51, 1); Bdisp_SetPoint_VRAM(12, 51, 1);
	Bdisp_SetPoint_VRAM(10, 50, 1);
	
	for(i = 0; i < 22; i++) Bdisp_SetPoint_VRAM(22, i + category * 21, 1);
	if(displayAtoms)
	{
		across.top = category * 21; across.bottom = (category + 1) * 21;
		Bdisp_AreaClr_VRAM(&across);
		for(i = 0; i < 106; i++) 
		{
			Bdisp_SetPoint_VRAM(22 + i, category * 21, 1);
			Bdisp_SetPoint_VRAM(22 + i, (category + 1) * 21, 1);
		}
		for(i = 0; i < 22; i++) Bdisp_SetPoint_VRAM(127, i + category * 21, 1);
		if(category == 0)
		{
			if(selectedX > 12) selectedX = 12;
			for(i = 0; i < 6; i++) renderAtomAt(cat1[i + ((selectedX < 6) ? 0 : (selectedX - 6))], 26 + i * 16, 18);
		}
	}
}

int renderAtom(Atom a)
{
	renderAtomAt(a, (a.x * 15) - camX, 63 - (a.y * 15) + camY);
}

int renderAtomAt(Atom a, int posX, int posY)
{
	int i;
	
	if(posX < -15 || posY < -15 || posX > 128 || posY > 64) return;
	if(symbols[a.number - 1][1] != 0) PrintXY(posX + 1, posY - 10, symbols[a.number - 1], 0);
	else PrintXY(posX + 4, posY - 10, symbols[a.number - 1], 0);
	
	if(a.Electrons.e.t == 1 || a.Electrons.e.t == 2) Bdisp_SetPoint_VRAM(posX + 7, posY - 14, 1);
	if(a.Electrons.e.t == 3) for(i = 0; i < 9; i++) {Bdisp_SetPoint_VRAM(posX + 3 + i, posY - 14, 1);};
	if(a.Electrons.e.r == 1 || a.Electrons.e.r == 2) Bdisp_SetPoint_VRAM(posX + 14, posY - 7, 1);
	if(a.Electrons.e.r == 3) for(i = 0; i < 9; i++) {Bdisp_SetPoint_VRAM(posX + 14, posY - 3 - i, 1);};
	if(a.Electrons.e.b == 1 || a.Electrons.e.b == 2) Bdisp_SetPoint_VRAM(posX + 7, posY, 1);
	if(a.Electrons.e.b == 3) for(i = 0; i < 9; i++) {Bdisp_SetPoint_VRAM(posX + 3 + i, posY, 1);};
	if(a.Electrons.e.l == 1 || a.Electrons.e.l == 2) Bdisp_SetPoint_VRAM(posX, posY - 7, 1);
	if(a.Electrons.e.l == 3) for(i = 0; i < 9; i++) {Bdisp_SetPoint_VRAM(posX, posY - 3 - i, 1);};
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section
