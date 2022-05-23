#include <stdio.h>
#include <stdlib.h>
#include "teksEditor.H"

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
			if(Next(pos) != Nil) //kondisi di tengah (error)
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
			
			while(above != Nil || move!=Nil)
			{
				if(above != Nil)
				{
					above = Next(above);
					if(above != Nil)
						Down(above) = move;
					if(move != Nil)
						Up(move) = above;
				}
				if(move != Nil)	
					move = Next(move);
			}
			move = New;
			
			while(below != Nil || move!=Nil)
			{
				if(below != Nil)
				{
					below = Next(below);
					if(below != Nil)
						Up(below) = move;
					if(move != Nil)
						Down(move) = below;	
				}
				
				if(move != Nil)
					move = Next(move);
			}
		}
		else if (Next(pos) != Nil && CurCol != 1) //ketika karakter di insert diantara
		{
			Next(New) = Next(pos);
			Prev(New) = pos;
			Prev(Next(pos)) = New;
			Next(pos) = New;
			
			while(above != Nil || move!=Nil)
			{
				if(above != Nil)
				{
					above = Next(above);
					if(above != Nil)
						Down(above) = move;	
				}else
					above = Nil;
				if(move != Nil)
				{
					Up(move) = above;
					move = Next(move);
				}	
			}
			move = New;
			while(below != Nil || move!=Nil)
			{
				if(below != Nil)
				{
					below = Next(below);
					if(below != Nil)
						Up(below) = move;	
				}else
					below = Nil;
				if(move != Nil)
				{
					Down(move) = below;
					move = Next(move);
				}
			}
		}		
		else // karakter di insert di awal ketika berada di kolom 1 // masih error
		{
			Next(New) = pos;
			Prev(pos) = New;
			
			while(above != Nil || move!=Nil)
			{
				if(above != Nil)
				{
					Down(above) = move;
					if(move != Nil)
						Up(move) = above;
					above = Next(above);	
				}
				if(move != Nil)
				{
					move = Next(move);
				}
			}
			move = New;
			while(below != Nil || move!=Nil)
			{
				if(below != Nil)
				{
					Up(below) = move;
					if(move != Nil)
						Down(move) = below;
					below = Next(below);	
				}
				if(move != Nil)
				{
					move = Next(move);
				}
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
	
	
	if(CurCol == 1 && CurLine != 1) // kondisi ketika deletion berada di awal
	{
		if(Info(pos) != Nil) // ketika baris ada isi
		{	
			move = rec_up;
			
			while(Next(move) != Nil && Info(move) != Nil)
				move = Next(move);	
	
			Next(move) = pos;
			Prev(pos) = move;
						
			while(rec_up != Nil || rec_down != Nil)
			{
				if(rec_up != Nil && rec_down == Nil)
				{
					Down(rec_up) = Nil;
					rec_up = Next(rec_up);
				}
				else if(rec_up == Nil  && rec_down != Nil)
				{
					Up(rec_down) = Nil;
					rec_down = Next(rec_down);
				}
				else
				{
					Down(rec_up) = rec_down;
					Up(rec_down) = rec_up;
					
					rec_up = Next(rec_up);
					rec_down = Next(rec_down);
				}
			}
		}
		else // ketika baris yang dihapus baru insert line saja
		{
			while(above != Nil || below != Nil)
			{
				if(above != Nil && below == Nil)
				{
					Down(above) = Nil;
					above = Next(above);
				}else if(above == Nil && below != Nil)
				{
					Up(below) = Nil;
					below = Next(below);
				}else
				{
					Down(above) = below;
					Up(below) = above;
					
					above = Next(above);
					below = Next(below);
				}
			}
			DeAlokasi(&pos);
		}
	}
	else if(CurCol != 1) // deletion berada di tengah atau akhir
	{
		if(Next(pos) == Nil && Prev(pos) == Nil) // menjadi hanya line kosong
			Info(pos) = '\0';
		
		else if(Next(pos) == Nil && Prev(pos) != Nil ) // node yang dihapus berada di akhir
		{
			if(above != Nil)
				Down(above) = Nil;
			if(below != Nil)
				Up(below) = Nil;
			
			Next(Prev(pos)) = Nil;
			
			DeAlokasi(&pos); 
		}
		
		else if(Next(pos) != Nil) //node yang dihapus diantara
		{
			move = Next(pos);
			
			if(CurCol != 2)
				Next(Prev(pos)) = move;
			
			while(above != Nil || move != Nil)
			{
				if(above != Nil && move == Nil)
				{
					Down(above) = Nil;
					above = Next(above);
				}
				else if(above == Nil || move != Nil)
				{
					Up(move) = Nil;
					move = Next(move);
				}
				else
				{
					Down(above) = move;
					Up(move) = above;
					
					above = Next(above);
					move = Next(move);
				}
			}
			move = Next(pos);
			
			while(below != Nil || move != Nil)
			{
				if(below != Nil && move == Nil)
				{
					Up(below) = Nil;
					below = Next(below);
				}
				else if(below == Nil || move != Nil)
				{
					Down(move) = Nil;
					move = Next(move);
				}
				else
				{
					Up(below) = move;
					Down(move) = below;
					
					below = Next(below);
					move = Next(move);
				}	
			}
		DeAlokasi(&pos);
		}
	}
}

void editorKeyProses()
{
	teks teksEditor;
	CreateTeks(&teksEditor);
	
	int CurrentLine = 1;
	int CurrentCollumns = 1;
	int temp_int;
	address Position;
	
	char temp;
	int key;
	
	refreshScreen(teksEditor, CurrentLine, CurrentCollumns);
	
	while(1)
	{
		refreshScreen(teksEditor, CurrentLine, CurrentCollumns);
		SetCP(CurrentCollumns-1, CurrentLine+2);
		temp=getch();
		key = temp;
		
		if(key == -32) // cursor interact
		{
			key=getch();
				switch(key)
				{
					case 72:
						{//up
							//program untuk memindahkan posisi cursor kearah atas
							CurrentLine--;
							if(CurrentLine == 0)
								CurrentLine = 1;
							else{
								temp_int = getLength(teksEditor, CurrentLine)+1;
								if(CurrentCollumns > temp_int)
									CurrentCollumns = temp_int;
								
							}
							break;
						}
					case 75:
						{//left
							//program untuk memindahkan posisi cursor kearah kiri
							CurrentCollumns--;
							if(CurrentCollumns == 0)
							{
								if(CurrentLine-1 != 0) //kondisi ketika bukan berada di baris 1
								{
									CurrentLine--;
									CurrentCollumns = getLength(teksEditor, CurrentLine)+1;
								}else //kondisi ketika berada di baris 1
								{
									CurrentCollumns = 1;
								}
							}
							break;
						}
					case 77:
						{//right
							//program untuk memindahkan posisi cursor kearah kanan
							CurrentCollumns++;
							temp_int = getLength(teksEditor, CurrentLine)+1;
							if(CurrentCollumns > getLength(teksEditor, CurrentLine)+1)
							{
								CurrentLine++;
								if(CurrentLine > getMaxRow(teksEditor))
								{
									CurrentLine--;
									CurrentCollumns = getLength(teksEditor, CurrentLine)+1;
								}
								else
									CurrentCollumns = 1;
							}
							break;
						}
					case 80:
						{//down
							//program untuk memindahkan posisi cursor kearah bawah
							if(CurrentLine+1 > getMaxRow(teksEditor))
								CurrentCollumns = getLength(teksEditor, CurrentLine)+1;
							else
							{
								CurrentLine++;
								temp_int = getLength(teksEditor, CurrentLine);
								if(CurrentCollumns > temp_int)
									CurrentCollumns = temp_int+1;
							}
						}
				}
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
//				editorSaveFile("Bismillah.txt", teksEditor);
				exit(0);
			}
		}
		else if (key <= 126)// printing character
		{
			InsVChar(&teksEditor, temp, CurrentCollumns, CurrentLine);
			CurrentCollumns++;
		}
	}
}

void refreshScreen(teks L, int line, int collumns)
{
	system("cls");
	address pos, move;
	
	pos = First(L);
	move = pos;
	
	printf("File (Ctrl+Tab) | Help (Ctrl+H)\n");
	printf("Line : %d | Collumns : %d\n\n", line, collumns);
	
	while(pos != Nil)
	{
		printf("%c", Info(pos));
		while(Next(move) != Nil)
		{
			move = Next(move);
			if(move != Nil)
				fflush(stdout);
				printf("%c", Info(move));
		}
		pos = Down(pos);
		move = pos;
			if(pos != Nil)
				printf("\n");
	}
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

void help()
{
	FILE *data;
	char help[600];
	
	data = fopen("help.txt", "r");
	
	system("cls");
	while(!feof(data)){
		fgets(help, sizeof(help), data);
		printf("%s", help);
	}
	
	printf("\n\t");
	fclose(data);
	system("pause");
}

void SetCP(char x, char y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	fflush(stdin);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

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

void tampilan_awal()
{
	printf("\n\n\n\n\n\n\n\n\t\t\tWELCOME TO VUE - TEKS EDITOR");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	system("pause");
	help();
	system("cls");
}

