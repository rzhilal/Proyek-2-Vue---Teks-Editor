#include "kota.H"

void editorKeyPresses ()
{
	char *filename;
	bool isopen = false;
	bool isedited = false;
	char confirm;
	
	while(matriks.numrows != MAXR)
	{
		while(matriks.numcols < MAXC-2)
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
						if(matriks.numrows <= 0) // reset limit bawah row berada di 0
						{
							matriks.numrows = 0;
						}
						matriks.numcols = strlen(matriks.teks[matriks.numrows]) - 1;
						if(matriks.numcols == -1) // reset limit bawah colom berada di 0
						{
							matriks.numcols = 0;
						}
						matriks.teks[matriks.numrows][matriks.numcols] = '\0';
						system("cls");
						editorPrint();
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
					isedited = true;
					break;
				}
				
				/*** Shortcut key ***/
				
				/*Ctrl + S (Save ke file)*/
				else if(matriks.teks[matriks.numrows][matriks.numcols] == 19)
				{
					matriks.teks[matriks.numrows][matriks.numcols] = '\0';
					editorSaveFile("Bismilah.txt");
				}
				
				/*Ctrl + T (Line and Column menu)*/
				else if(matriks.teks[matriks.numrows][matriks.numcols] == 20)
				{
					matriks.teks[matriks.numrows][matriks.numcols] = '\0';
					curStat();
					editorPrint();
				}
				
				/*Ctrl + O (Open file) */
				else if (matriks.teks[matriks.numrows][matriks.numcols] == 15)
		 		{
		 			system("cls");
		 			printf("\n\n\tNama file : ");
		 			scanf("%s", filename);
		 			system("cls");
					editorOpenFile(filename);
					isopen = true;
				}
				
				/*Ctrl + U (Save As) */
				else if (matriks.teks[matriks.numrows][matriks.numcols] == 21)
		 		{ 
		 			system("cls");
		 			printf("\n\n\tSimpan sebagai dengan nama : ");
		 			scanf("%s", filename);
		 			system("cls");
					editorSaveFile(filename);
					isopen = true;
					isedited = false;
				}
				/*Ctrl + E (Help) */
				else if(matriks.teks[matriks.numrows][matriks.numcols] == 5)
				{
					//belum
				}
				/*Ctrl + Q (Quit From the program)*/
				else if (matriks.teks[matriks.numrows][matriks.numcols] == 17)
				{
					matriks.teks[matriks.numrows][matriks.numcols] = '\0';
					if(isopen && !isedited) // ketika file sudah disave isopen dalam keadaan true dan isedited false
					{
						exit(0);
					}
					else
					{
						system("cls");
						if(isedited)
						{
							printf("\n\n\tSave File (Y/N) : ");
							confirm = getch();
		 					switch(toupper(confirm))
		 					{
		 						case 89 :
		 							{
										system("cls");
		 								printf("\n\n\tNama file : ");
		 								scanf("%s", filename);
							 			system("cls");
										editorSaveFile(filename);
										exit(0);
									}
								default:
									{
										exit(0);
									}
							}
						}
					}
				}
			}
			/*** Handle Standar ***/
			else
			{
				printf("%c", matriks.teks[matriks.numrows][matriks.numcols]);
				matriks.numcols++;
				isedited = true;
			}
		}
		printf("\n");
		matriks.numrows++;
		matriks.numcols = 0;
	}
}

void editorPrint()
{
	for(int i = 0; i <= matriks.numrows; ++i)
	{
		if(i != matriks.numrows)
		{
			printf("%s\n", matriks.teks[i]);
		}else
		{
			printf("%s", matriks.teks[i]);
		}
	}
}
