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
						matriks.numrows--;
						if(matriks.numrows <= 0)
						{
							matriks.numrows = 0;
						}
						matriks.numcols = strlen(matriks.teks[matriks.numrows]) - 1;
						matriks.teks[matriks.numrows][matriks.numcols] = '\0';
						system("cls");
						for(int i=0; i<= matriks.numrows;i++)
						{
							if(i != matriks.numrows)
							{
								printf("%s\n", matriks.teks[i]);
							}
							else
							{
								printf("%s", matriks.teks[i]);
							}
						}
					}
					else //kondisi berada ditengah maupun akhir
					{
						matriks.teks[matriks.numrows][matriks.numcols] = '\0';
						matriks.numcols--;
						printf("\b \b");
					}
				}
				
				/***Handle Enter***/
				else if(matriks.teks[matriks.numrows][matriks.numcols] == 13)
				{
					matriks.teks[matriks.numrows][matriks.numcols] = '\0';
					break;
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

