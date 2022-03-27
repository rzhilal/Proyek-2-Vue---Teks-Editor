#include "kota.H"

//void editorSaveFile(char *fname)
//{
//	FILE *fptr = NULL;
//
//    fptr = fopen(fname, "w+");
//    
//    for(int i = 0; i<=matriks.numrows;i++)
//    {
//    	fwrite(matriks.teks[i], sizeof(char), strlen(matriks.teks[i]), fptr);
//		fprintf(fptr, "\n");
//	}
//	fclose(fptr);
//}
//
//void editorOpenFile(char *fname)
//{
//	FILE *fptr = NULL;
//
//    fptr = fopen(fname, "r");
//    
//	matriks.numrows = 0;
//	
//	while(fgets(matriks.teks[matriks.numrows], MAXC, fptr)) 
//	{
//        matriks.teks[matriks.numrows][strlen(matriks.teks[matriks.numrows]) - 1] = '\0';
//        matriks.numrows++;
//    }
//    
//	editorPrint();  
//    fclose(fptr);
//}

