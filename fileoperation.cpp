#include "teksEditor.H"

void editorSaveFile(char *fname, teks L)
{
	address rec, pos;
	rec = First(L);
	pos = rec;
	
	FILE *fptr = NULL; // pendeklarasian tipe data file

    fptr = fopen(fname, "w+"); // pada variabel fptr kita ingin membuka sebuah file dengan mode w+(overwrite)
    
    while(rec != Nil)
    {
    	while(pos != Nil)
    	{
    		fprintf(fptr, "%c", Info(pos));
    		pos = Next(pos);
		}
		rec = Down(rec);
		pos = rec;
		if(rec != Nil)
			fprintf(fptr, "\n");
	}
	fclose(fptr);
}


void clearlist(teks *L)
{
	address pos, move, rec, rec_pos;
	pos = First(*L);
	
	if(First(*L) != Nil)
	{
		while (Down(pos)!= Nil)
			pos = Down(pos);
		
		move =pos;
		while (Next(move) != Nil)
			move = Next(move);
	
		
		while(pos != Nil)
		{
			rec_pos = Up(pos);
			move = pos;
			while(Next(move) != Nil)
				move = Next(move);
				
			while(move != Nil)
			{
				rec = Prev(move);
				if (rec != Nil)
					Next(rec) = Nil;
				else
					rec = Nil;
		
				DeAlokasi(&move);
				move = rec;
			}
			pos = rec_pos;
		}
		First(*L) = Nil;
	}
}

void openFile(char *fname, teks *L, int *col, int *line)
{
	FILE *fp;
	char c; //penampung 1 karakter pada file
	
	*col = 1;
	*line = 1;
	
	fp = fopen(fname,"r"); //open file
	if (fp == NULL)
	{
		printf("File tidak dapat dibuka");
		SetCP(2,0);
	}	
	do {
		c = fgetc(fp); //baca file 1 karakter
		if ( feof(fp) ) {
			break ; //kondisi ketika sudah end file keluar deri perulangan
		} 
		if ( c == '\n')
		{
			InsertNewLine(&(*L), *line, *col); //untuk menginsert new line pada file ke list dengan baris baru
			*line = *line + 1;
			*col = 1;
		}
		else
		{
			InsVChar(&(*L), c, *col, *line); //insert karakter pada list
			*col = *col + 1;
		} 
		
	}while(1);
	
	fclose(fp);
}