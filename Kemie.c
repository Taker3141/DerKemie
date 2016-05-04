#include "fxlib.h"

int AddIn_main(int isAppli, unsigned short OptionNum)
{
	unsigned int key;

	render();
	
	while(1)
	{
		GetKey(&key);
	}

	return 1;
}

int render()
{
	int i;
	
	Bdisp_AllClr_DDVRAM();
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
