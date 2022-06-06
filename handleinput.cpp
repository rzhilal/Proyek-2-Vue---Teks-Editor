#include "teksEditor.H"

int getMaxRow(teks L)
{
	address pos = First(L);
	int count = 1;
	while(Down(pos) != Nil ){
		pos = Down(pos);
		count++;
	}
			
	return count;
}

int getLength(teks L, int CurLine)
{
	address pos = First(L);
	int count = 1;
	for(int i=1; i<CurLine;i++)
			pos = Down(pos);
	while(Next(pos) != Nil)
	{
		pos = Next(pos);
		count++;
	}
	if(Info(pos) == Nil)
		count = 0;
	return count;
}

void editorKeyProses()
{
	teks teksEditor;
	CreateTeks(&teksEditor);
	
	int CurrentLine = 1;
	int CurrentCollumns = 1;
	int max_Line = 0;
	int min_Line = 0;
	int max_Col = 0;
	int temp_int;
	address Position;
	
	bool isedited = false;
	bool isopen = false;
	char temp_char;
	char temp_file[55];
	char temp;
	int key;
	
	tampilan(CurrentLine, CurrentCollumns);
	
	while(1)
	{
		
		
		if(max_Line < CurrentLine)
		{
			max_Line = CurrentLine;
			min_Line++;
		} else if(min_Line > CurrentLine)
		{
			min_Line = CurrentLine;
			max_Line--;
		}
		
		refreshScreen(teksEditor, CurrentLine, CurrentCollumns);
		
		SetCP(CurrentCollumns-1, CurrentLine+1);
		temp=getch();
		key = temp;
		
		if(key == -32) // cursor interact
		{
		}
		
		else if(key <=31) //non printing character
		{
			/*Handle Backspace*/
			if(key == 8)
			{
				DelChar(&teksEditor, CurrentCollumns, CurrentLine);
				CurrentCollumns--;
				if(CurrentCollumns == 0)
				{
					CurrentLine--;
					if(CurrentLine == 0)
					{
						CurrentLine = 1;
						CurrentCollumns = 1;
					}else
					{
							CurrentCollumns = getLength(teksEditor, CurrentLine)+1;
					}
				}
			}
			/***Handle Enter***/                     
			else if(key == 13)
			{
				InsertNewLine(&teksEditor, CurrentLine, CurrentCollumns);
				CurrentLine++;
				CurrentCollumns = 1;
			}
			/*** Shortcut key ***/
			/*Ctrl + Q (Quit shortcut)*/
			else if(key == 17)
			{
				if(isedited)
				{
					printf(CSI "30;58H");
					printf("Save perubahan?(y/n) : ");
					scanf("%c", &temp_char);
					SetCP(2, 0);
					if (temp_char == 'y' || temp_char == 'Y')
					{
						if(isopen == true)
						{
							printf(CSI "30;58H");
							printf("                                      ");
							editorSaveFile( temp_file, teksEditor);
							printf(CSI "30;58H");
							printf("Saved");
							Sleep(200);
						}else
						{
							printf(CSI "30;58H");
							printf("                                      ");
							printf(CSI "30;58H");
							printf("Simpan dengan nama(.txt) : ");
							scanf("%s", temp_file);
							editorSaveFile( temp_file, teksEditor);
							printf(CSI "30;58H");
							printf("                                      ");
							printf(CSI "30;58H");
							printf("Saved");
							Sleep(200);
							SetCP(2, 0);	
						}
					}
				}
				exit(0);
			}
			/*Ctrl + O (Open Menu)*/
			else if(key == 15)
			{
				openmenu:
				if(isedited == true)
				{
					printf(CSI "30;58H");
					printf("Save perubahan?(y/n) : ");
					scanf("%c", &temp_char);
					SetCP(2, 0);
					if (temp_char == 'y' || temp_char == 'Y')
					{
						if(isopen == true)
						{
							printf(CSI "30;58H");
							printf("                                      ");
							editorSaveFile( temp_file, teksEditor);
							printf(CSI "30;58H");
							printf("Saved");
							Sleep(200);
						}else
						{
							printf(CSI "30;58H");
							printf("                                      ");
							printf(CSI "30;58H");
							printf("Simpan dengan nama(.txt) : ");
							scanf("%s", temp_file);
							editorSaveFile( temp_file, teksEditor);
							printf(CSI "30;58H");
							printf("                                      ");
							printf(CSI "30;58H");
							printf("Saved");
							Sleep(200);
							SetCP(2, 0);	
						}
					}
					printf(CSI "30;58H");
					printf("                                              ");
					printf(CSI "30;58H");
					printf("Nama File yang ingin dibuka(.txt) : ");
					scanf("%s", temp_file);
					clearlist(&teksEditor);
					openFile(temp_file, &teksEditor, &CurrentCollumns, &CurrentLine);
					SetCP(2, 0);
				}
				else
				{
					printf(CSI "30;58H");
					printf("Nama File yang ingin dibuka(.txt) : ");
					scanf("%s", temp_file);
					clearlist(&teksEditor);
					openFile(temp_file, &teksEditor, &CurrentCollumns, &CurrentLine);
					SetCP(2, 0);
				}
				isopen = true;
			}
			/*Ctrl + T (Menu tab)*/
			else if(key == 20)
			{
				temp_int = menu();
				switch(temp_int)
				{
					case 1 :
						goto openmenu;
					case 2 :
						goto savemenu;
					case 3:
						goto saveas;
					case 4:
						break;
				}
			}
			/*Ctrl + S (Save tab)*/
			else if(key == 19)
			{
				savemenu:
				if(isopen == false)
				{
					printf(CSI "30;58H");
					printf("Simpan dengan Nama(.txt) : ");
					scanf("%s", temp_file);
					editorSaveFile( temp_file, teksEditor);
					SetCP(2, 0);
				}
				else
				{
					printf(CSI "30;58H");
					printf("Saved");
					Sleep(200);
					editorSaveFile(temp_file, teksEditor);
				}
				isedited = false;
			}
			/*Ctrl + A (Save As)*/
			else if(key == 1)
			{
				saveas:
				printf(CSI "30;58H");
				printf("Simpan file dengan Nama(.txt) : ");
				scanf("%s", temp_file);
				editorSaveFile( temp_file, teksEditor);
				isedited = false;
				SetCP(2, 0);
			}
		}
		else if (key <= 126)// printing character
		{
			InsVChar(&teksEditor, temp, CurrentCollumns, CurrentLine);
			isedited = true;
			CurrentCollumns++;
		}
	}
}

bool IsEmpty (teks L)
{
	return (First(L)==Nil);	
}

void CreateTeks (teks * L)
{
	First(*L) = Nil;
}

address Alokasi (infotype X)
{
	address P;
	P = (address)malloc(sizeof(ElmtList));
	if(P != Nil){
		Info(P) = X;
		Next(P) = Nil;
		Prev(P) = Nil;
		Up(P) = Nil;
		Down(P) = Nil;
	}
	return P;
}

void DeAlokasi (address *P)
{
	Next(*P) = Nil;
	Prev(*P) = Nil;
	Up(*P) = Nil;
	Down(*P) = Nil;
	free(*P);
}

void InsertFirstRow (teks * L, address P)
{
	if(First(*L) == Nil)
		First(*L) = P;
	else
	{
		Down(P) = First(*L);
		Up(First(*L)) = P;
		First(*L) = P;
	}
}

void InsertNewLine(teks * L, int CurLine, int CurCol)
{
	address above, below, rec_up, rec_down, rec_pos, move;
	
	address pos = First(*L);
	address P = Alokasi('\0');
	
	above = Nil;
	below = Nil;
	
	if(P != Nil)
	{
		for(int i=1; i<CurLine;i++)
			pos = Down(pos);
		
		rec_up = Up(pos);
		rec_down = Down(pos);
		rec_pos = pos;
		
		for(int i=1; i<CurCol-1;i++)
			pos = Next(pos);
		
		move = pos;
		
		above = Up(pos);
		below = Down(pos);
		
		if(CurCol == 1) //kondisi ketika berada di awal
		{
			if(CurLine == 1) //kondisi ketika insert new line di first list
			{
				Up(pos) = P;
				Down(P) = pos;
				First(*L) = P;
			}
			else
			{
				Down(rec_up) = P;
				Up(P) = rec_up;
				Up(rec_pos) = P;
				Down(P) = rec_pos;
				
				rec_pos = Next(rec_pos);
				rec_up = Next(rec_up);
				
				while(rec_up != Nil)
				{
					Down(rec_up) = Nil;
					rec_up = Next(rec_up);
				}
				while(rec_pos != Nil)
				{
					Up(rec_pos) = Nil;
					rec_pos = Next(rec_pos);
				}
			}
		}
		else //kondisi berada di tengah atau akhir
		{
			if(Next(pos) != Nil) //kondisi di tengah
			{	
				pos = Next(pos);
				above = Up(pos);
				below = Down(pos);
				move = pos;
				
				while(above != Nil)
				{
					Down(above) = Nil;
					above = Next(above);
				}
				
				Next(Prev(pos)) = Nil;
				Prev(pos) = Nil;
				
				Up(move) = rec_pos;
				Down(rec_pos) = move;
				
				while(move != Nil || rec_pos != Nil)
				{
					if(rec_pos != Nil && move == Nil)
					{
						Down(rec_pos) = Nil;
						rec_pos = Next(rec_pos);
					}
					else if (rec_pos == Nil && move != Nil)
					{
						Up(move) = Nil;
						move = Next(move);
					}
					else
					{
						Down(rec_pos) = move;
						Up(move) = rec_pos;
						
						rec_pos = Next(rec_pos);
						move = Next(move);
					}
				}
				move = pos;
				
				while(move != Nil || rec_down != Nil)
				{
					if(rec_down != Nil && move == Nil)
					{
						Up(rec_down) = Nil;
						rec_down = Next(rec_down);
					}
					else if (rec_down == Nil && move != Nil)
					{
						Down(move) = Nil;
						move = Next(move);
					}
					else
					{
						Up(rec_down) = move;
						Down(move) = rec_down;
						
						rec_down = Next(rec_down);
						move = Next(move);
					}
				}
				DeAlokasi(&P);
			}
			else
			{
				if(rec_down == Nil) // akhir baris
				{
					Down(rec_pos) = P;
					Up(P) = rec_pos;
				}
				else
				{
					Down(rec_pos) = P;
					Up(P) = rec_pos;
					Up(rec_down) = P;
					Down(P) = rec_down;
					
					rec_down = Next(rec_down);
					rec_pos = Next(rec_pos);
					
					while(rec_down != Nil)
					{
						Up(rec_down) = Nil;
						rec_down = Next(rec_down);
					}
					
					while(rec_pos != Nil)
					{
						Down(rec_pos) = Nil;
						rec_pos = Next(rec_pos);
					}
				}
			}
		}
	}
}

void InsertChar (teks * L, address New, int CurCol, int CurLine)
{
	address pos;
	address move;
	address above = Nil;
	address below = Nil;
	
	pos = First(*L);
	move = New;
	
	if(pos == Nil)
		InsertFirstRow(&(*L), New);
		
	else
	{
		for(int i=1; i<CurLine;i++)
			pos = Down(pos);
		for(int i=1; i<CurCol-1;i++)
			pos = Next(pos);
		
		if(Up(pos) != Nil) 
			above = Up(pos);
		if(Down(pos) != Nil)
			below = Down(pos);
		                       
		if(Info(pos) == '\0') //kondisi ketika insert new line
		{
			Info(pos) = Info(New);
			DeAlokasi(&New);
		}
		
		else if(Next(pos) == Nil && CurCol != 1) //ketika posisi berada di akhir
		{
			Next(pos) = New;
			Prev(New) = pos;
		}
		else if (Next(pos) != Nil && CurCol != 1) //ketika karakter di insert diantara
		{
			Next(New) = Next(pos);
			Prev(New) = pos;
			Prev(Next(pos)) = New;
			Next(pos) = New;
		}		
		else // karakter di insert di awal ketika berada di kolom 1 // masih error
		{
			Next(New) = pos;
			Prev(pos) = New;
			
			if(above != Nil)
			{
				Down(above) = New;
				Up(New) = above;
				Up(pos) = Nil;
			}
			if(below != Nil)
			{
				Up(below) = New;
				Down(New) = below;
				Down(pos) = Nil;
			}
			
			if(pos == First(*L))
				First(*L) = New;
		}
	}
}

void InsVChar (teks * L, infotype X, int CurCol, int CurLine)
{
	address P = Alokasi(X);
	if(P != Nil)
	{
		InsertChar(&(*L), P, CurCol, CurLine);
	}
}

void DelChar(teks * L, int CurCol, int CurLine)
{
	address pos = First(*L);
	address below, above, move, rec_up, rec_down, rec_pos;
	
	for(int i=1; i<CurLine;i++)
			pos = Down(pos);
	
	rec_down = Down(pos);
	rec_pos = pos;
	rec_up = Up(pos);
	
	for(int i=1; i<CurCol-1;i++)
		pos = Next(pos);
	
	above = Up(pos);
	below = Down(pos); 
	
	if(CurCol == 1 && CurLine == 1);
	else if(pos == First(*L) && Next(pos) != Nil)
	{
		move = Next(pos);
		First(*L) = move;
		if(rec_down != Nil)
		{
			Up(rec_down) = move;
			Down(move) = rec_down;
		}else
			Down(move) = Nil;
	}
	
	else if(CurCol == 1 && CurLine != 1) // kondisi ketika deletion berada di awal
	{
		if(Info(pos) != Nil) // ketika baris ada isi
		{	
			move = rec_up;
			
			while(Next(move) != Nil && Info(move) != Nil)
				move = Next(move);	
	
			Next(move) = pos;
			Prev(pos) = move;
			
			Up(pos) = Nil;
			Down(pos) = Nil;
			
			if(rec_down != Nil)
			{
				Up(rec_down) = rec_up;
				Down(rec_up) = rec_down;
			}
			else
				Down(rec_up) = Nil;
		}
		else // ketika baris yang dihapus baru insert line saja
		{
			if(rec_down != Nil)
			{
				Up(rec_down) = rec_up;
				Down(rec_up) = rec_down;
			}
			else
				Down(rec_up) = Nil;
			
			DeAlokasi(&pos);
		}
	}
	else if(CurCol != 1) // deletion berada di tengah atau akhir
	{
		if(Next(pos) == Nil && Prev(pos) == Nil) // menjadi hanya line kosong
			Info(pos) = '\0';
		
		else if(Next(pos) == Nil && Prev(pos) != Nil ) // node yang dihapus berada di akhir
		{
			
			Next(Prev(pos)) = Nil;
			DeAlokasi(&pos); 
		}
		else if(Next(pos) != Nil) //node yang dihapus diantara
		{
			move = Next(pos);
			if(Prev(pos) != Nil)
				Next(Prev(pos)) = move;
			else
			{
				if(rec_up != Nil)
				{
					Down(rec_up) = move;
					Up(move) = rec_up;
				}
				else
					Up(move) = Nil;
			
				if(rec_down != Nil)
				{
					Up(rec_down) = move;
					Down(move) = rec_down;			
				}
				else
					Down(move) = Nil;
			}
			
			Prev(move) = Prev(pos);
	
			DeAlokasi(&pos);
		}
	}
}