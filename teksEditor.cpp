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

void InsertNewLine(teks * L, int CurLine)
{
	address above, below;
	
	address pos = First(*L);
	address P = Alokasi('\0');
	
	if(P != Nil)
	{
		for(int i=1; i<CurLine; i++)
			pos = Down(pos);
		
		above = pos;
		below = Down(pos);
		
		Up(P) = above;
		if(above != Nil)
			Down(above) = P;
		                
		Down(P) = below;
		if(below != Nil)
			Up(below) = P;
			
		while(above != Nil)
		{
			above = Next(above);
			if(above != Nil)
				Down(above) = Nil;
		} 
		
		while(below!=Nil)
		{                
			below = Next(below);
			if(below != Nil)
				Up(below) = Nil;
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
					above = Next(above);
					Down(above) = move;	
					above = Next(above);
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
					Up(below) = move;
					below = Next(below);
				}else
					below = Nil;
				if(move != Nil)
				{
					Down(move) = below;
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
	address below, above, move;
	
	for(int i=1; i<CurLine;i++)
			pos = Down(pos);
	for(int i=1; i<CurCol-1;i++)
		pos = Next(pos);
	
	above = Up(pos);
	below = Down(pos);
	
	if(CurCol == 1 && CurLine != 1) // kondisi ketika deletion berada di awal
	{
		if(Info(pos) != Nil) // ketika baris ada isi
		{	
			move = above;
			while (Next(move) != Nil) // menuju last node pada baris atas
				move = Next(move);
			
			// menyambungkan baris pos dengan atasnya
			if(Info(move) == Nil) // baris atas hanya insert line
			{
				Info(move) = Info(pos);
				Next(move) = Next(pos);
				Prev(Next(pos)) = move;
				DeAlokasi(&pos);
				pos = Next(move);
			}
			else // baris atas ada isi
			{
				Next(move) = pos; 
				Prev(pos) = move;
			}	
			
			move = Up(move);
			if(move != Nil) // ketika atas above menunjuk pada baris atas
			{
				move = Next(move);
				while(move != Nil || pos != Nil)
				{
					if(move == Nil && pos != Nil)
					{
						Up(pos) = Nil;
						pos = Next(pos);
					}	
					else if (move != Nil && pos == Nil)
					{
						Down(move) = Nil;
						move = Next(move);
					} 
					else
					{
						Up(pos) = move;
						Down(move) = pos;
						
						pos = Next(pos);
						move = Next(move);
					}
				}
			}
			else // ketika tidak ada karakter pada baris di atas above
			{
				Up(pos) = Nil;
				while(Next(pos) != Nil)
				{
					pos = Next(pos);
					Up(pos) = Nil;
				}
			}
		}
		else // ketika yang baris yang dihapus baru insert line saja
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
		else if(Next(pos) != Nil)
		{
			Next(Prev(pos)) = Next(pos);
			Prev(Next(pos)) = Prev(pos);
			
			move = Next(pos);
			above = Next(above);
			
			while(above != Nil && move != Nil)
			{
				if(above != Nil && move == Nil)
				{
					Down(above) = Nil;
					above = Next(above);
				}
				else if(above == Nil && move != Nil)
				{
					Up(move) = Nil;
					move = Next(move);
				}
				else
				{
					Up(move) = above;
					Down(above) = move;
					
					above = Next(above);
					move = Next(move);
				}
			}
			
			move = pos;
			
			while(below != Nil && move != Nil)
			{
				if(below != Nil && move == Nil)
				{
					Up(below) = Nil;
					below = Next(below);
				}
				else if(below == Nil && move != Nil)
				{
					Down(move) = Nil;
					move = Next(move);
				}
				else
				{
					Down(move) = below;
					Up(below) = move;
					
					below = Next(below);
					move = Next(move);
				}
			}
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
							if(CurrentCollumns > getLength(teksEditor, CurrentLine))
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
				InsertNewLine(&teksEditor, CurrentLine);
				CurrentLine++;
				CurrentCollumns = 1;
			}
			/*** Shortcut key ***/
			/*Ctrl + Q (Quit shortcut)*/
			else if(key == 17)
			{
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


void help(){
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
