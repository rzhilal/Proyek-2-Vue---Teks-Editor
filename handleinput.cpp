#include "kota.H"

void editorKeyPresses ()
{
	while(matriks.numrows != MAXR)
	{
		while(matriks.numcols < MAXC-1)
		{
			matriks.teks[matriks.numrows][matriks.numcols] = getch(); //Input langsung dimasukan kedalam matriks
			
			/*** Handle non standar (dalam decimal nonstandar input (bernilai kurang dari 31) ***/
			if(matriks.teks[matriks.numrows][matriks.numcols] <= 31 || matriks.teks[matriks.numrows][matriks.numcols] == 127)
			{
				/*Handle Backspace*/
				if (matriks.teks[matriks.numrows][matriks.numcols] == 8)
				{	
					if(matriks.numcols <= 0) //kondisi ketika berada di posisi awal
					{
						
					}
					else //kondisi berada ditengah maupun akhir
					{
						
					}
				}
				
				/***Handle Enter***/
				else if(matriks.teks[matriks.numrows][matriks.numcols] == 13)
				{
					
				}
				
				/*** Shortcut key ***/
				
				/*Ctrl + S (Save ke file)*/
				else if(matriks.teks[matriks.numrows][matriks.numcols] == 19)
				{
					
				}
				
				/*Ctrl + T (Line and Column menu)*/
				else if(matriks.teks[matriks.numrows][matriks.numcols] == 20)
				{
					
				}
				
				/*Ctrl + O (Open file) */
				else if (matriks.teks[matriks.numrows][matriks.numcols] == 15)
		 		{
					
				}
			}
			/*** Handle Standar ***/	
			else
			{
				
			}
		}
		printf("\n");
		matriks.numrows++;
		matriks.numcols = 0;
	}
}

