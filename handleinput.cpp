#include "kota.H"

void editorKeyPresses ()
{
	char *filename; // Menampung nama inputan untuk file
	char kata2[50]; // Menampung kata dari modul find
	bool isopen = false;
	bool isedited = false;
	char confirm;
	
	tampilan_awal();
	
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
					if(not isopen)
					{
						system("cls");
		 				printf("\n\n\tNama File: ");
		 				scanf("%s", filename);
		 				isopen = true;
		 				system("cls");
		 				editorPrint();
					}
					editorSaveFile(filename);
					isedited = false;
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
					matriks.teks[matriks.numrows][matriks.numcols] = '\0';
					help();
					system("cls");
					editorPrint();
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
		 								if(isopen)
		 								{
		 									editorSaveFile(filename);
		 									exit(0);
										}else
										{
											system("cls");
		 									printf("\n\n\tNama file : ");
		 									scanf("%s", filename);
							 				system("cls");
											editorSaveFile(filename);
											exit(0);	
										}
										
									}
								default:
									{
										exit(0);
									}
							}
						}
					}
				}
				/*Ctrl + F (Find)*/
				else if (matriks.teks[matriks.numrows][matriks.numcols] == 6)
				{
					matriks.teks[matriks.numrows][matriks.numcols] = '\0';
					system("cls");
					printf("\n\n\tKata yang dicari : ");
					scanf("%s", kata2);
					findword(kata2);
					printf("\n\n\t");
					system("pause");
					system("cls");
					editorPrint();
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
	system("cls");
	printf("\n\n\n\tBatas dari baris");
	printf("\n\n\tSave File (Y/N) : ");
	confirm = getch();
	switch(toupper(confirm))
	{
	case 89 :
		{
			if(isopen)
			{
				editorSaveFile(filename);
				exit(0);
			}else
			{
				system("cls");
		 		printf("\n\n\tNama file : ");
		 		scanf("%s", filename);
				system("cls");
				editorSaveFile(filename);
				exit(0);	
			}
									
		}
	default:
		{
		exit(0);
		}
	}
}

void editorPrint()
{
	for(int i = 0; i <= matriks.numrows; ++i) // perulangan dengan kondisi berakhir ketika i sampai baris sedang di edit
	{
		if(i != matriks.numrows) // ketika baris tidak sama dengan yang di edit setiap akhir dari yang di baca baris matriks akan ada end of line
		{
			printf("%s\n", matriks.teks[i]);
		}else
		{
			printf("%s", matriks.teks[i]);
		}
	}
}

void findword(char *word)
{
	int row[MAXR]; // yang menyimpan informasi bahwa ada kata di baris itu
	int j = 0; // indikator yang dijadikan indeks pada array row
	
	for (int i = 0; i <= matriks.numrows ; ++i) {
		if (!strcmp(matriks.teks[i], word)) 
		{
			row[j] = i;
			j++;
		}
	}
	if(j != 0)
	{
		printf("\n\n\tBaris ke : ");
		for(int i = 0; i<j; i++)
		{
			printf("%d, ", row[i]+1);
		}		
	}else
	{
		printf("\n\n\tKata tidak ada");
	}
}

void editorSaveFile(char *fname)
{
	FILE *fptr = NULL; // pendeklarasian tipe data file

    fptr = fopen(fname, "w+"); // pada variabel fptr kita ingin membuka sebuah dengan mode w+(overwrite)
    
    for(int i = 0; i<=matriks.numrows;i++)
    {
    	fwrite(matriks.teks[i], sizeof(char), strlen(matriks.teks[i]), fptr);
		fprintf(fptr, "\n"); // fungsi untuk ngeprint kedalam sebuah file
	}
	fclose(fptr);
}

void editorOpenFile(char *fname) 
{   
    FILE *fptr = NULL; // pendeklarasian var bertipe file

    fptr = fopen(fname, "r"); // membuka file dengan nama dari parameter dan dibuka dengan mode read
    
	if( fptr == NULL) //kondisi jika file tidak ada
	{
		printf("\n\n\tFile tidak ada\n\t");
		system("pause");
		system("cls");
	}else //kondisi ketika file dapat dibuka
	{
		matriks.numrows = 0; //reset ke 0
		while(fgets(matriks.teks[matriks.numrows], MAXC, fptr)) // membaca satu baris pada file dan diisi kedalam matriks
		{
        	matriks.teks[matriks.numrows][strlen(matriks.teks[matriks.numrows]) - 1] = '\0'; // akhir dari kolom diisi '\0'
        	matriks.numrows++;
    	}
		editorPrint(); //print teks yang ada di dalam matriks
	}  
    fclose(fptr); //tutup file
}

void curStat()
{
	system("cls");
	printf("\n\n\tLine : %d || Kolom : %d\n\n", matriks.numrows+1, matriks.numcols+1);
	system("pause");
	system("cls");
}



