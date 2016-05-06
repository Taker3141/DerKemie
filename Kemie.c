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

int selected = 0;
int displayAtoms = 0;
int camX = 0, camY = 0;
DISPBOX left, across;
Atom atoms[2];

int AddIn_main(int isAppli, unsigned short OptionNum)
{
	unsigned int key;
	left.left = 0; left.top = 0; left.right = 21; left.bottom = 63;
	across.left = 22; across.right = 127;

	atoms[0].number =  1; atoms[0].charge = 0; atoms[0].x = 3; atoms[0].y = 1; atoms[0].Electrons.eByte = 0x01;
	atoms[1].number = 10; atoms[1].charge = 0; atoms[1].x = 3; atoms[1].y = 0; atoms[1].Electrons.eByte = 0xFF;
	atoms[2].number =  7; atoms[2].charge = 0; atoms[2].x = 2; atoms[2].y = 1; atoms[2].Electrons.eByte = 0x57;
	render();
	
	while(1)
	{
		GetKey(&key);
		if(key == KEY_CTRL_UP && selected > 0) selected--;
		if(key == KEY_CTRL_DOWN && selected < 2) selected++;
		if(key == KEY_CTRL_EXE) 
		{
			if(!displayAtoms) displayAtoms = 1;
			else displayAtoms = 0;
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
	
	for(i = 0; i < 22; i++) Bdisp_SetPoint_VRAM(22, i + selected * 21, 1);
	if(displayAtoms)
	{
		across.top = selected * 21; across.bottom = (selected + 1) * 21;
		Bdisp_AreaClr_VRAM(&across);
		for(i = 0; i < 106; i++) 
		{
			Bdisp_SetPoint_VRAM(22 + i, selected * 21, 1);
			Bdisp_SetPoint_VRAM(22 + i, (selected + 1) * 21, 1);
		}
		for(i = 0; i < 22; i++) Bdisp_SetPoint_VRAM(127, i + selected * 21, 1);
	}
}

char* symbols[] = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar"};
int renderAtom(Atom a)
{
	int i;
	int posX = (a.x * 15) - camX;
	int posY = 63 - (a.y * 15) + camY;
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
