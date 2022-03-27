#include "kota.H"

void editorSaveFile(char *fname)
{
	
}

void editorOpenFile(char *fname)
{
	FILE *fptr = NULL;

    fptr = fopen(fname, "r");
    
	matriks.numrows = 0;
	
	while(fgets(matriks.teks[matriks.numrows], MAXC, fptr)) 
	{
        matriks.teks[matriks.numrows][strlen(matriks.teks[matriks.numrows]) - 1] = '\0';
        matriks.numrows++;
    }
    
	editorPrint();  
    fclose(fptr);
}

