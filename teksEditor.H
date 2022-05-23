#ifndef teksEditor_H
#define teksEditor_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#define Nil NULL

#define Info(P) (P)->info
#define Next(P) (P)->next
#define Down(P) (P)->down
#define Up(P) (P)->up
#define Prev(P) (P)->prev
#define First(L) (L).First

//ARRAY OF LIST ANGGOTA
typedef char infotype;
typedef struct tElmtList *address;

typedef struct tElmtList {
	 infotype info;
	 address next;
	 address down;
	 address up;
	 address prev;
} ElmtList;

typedef struct {
	  address First;
} teks;

bool IsEmpty (teks L);

void CreateTeks (teks * L);

address Alokasi (infotype X);

void DeAlokasi (address *P);

void InsertFirstRow (teks * L, address P);

void InsertNewLine(teks * L,int CurLine);

void InsertChar (teks * L, address New, int CurCol, int CurLine);

void InsVChar (teks * L, infotype X, int CurLine, int CurCol);

void editorKeyProses();

void refreshScreen(teks L, int line, int collumns);

void refreshTeks_scrolling(teks L, int max_line, int max_collumns);

void refreshBlank(teks L, int min_line);

void refreshScreen(teks L, int line, int collumns);

void DelChar(teks * L, int CurCol, int CurLine);

int getLength(teks L, int CurLine);

void help();

void SetCP(char x, char y);

void tampilan_awal();

int getMaxRow(teks L);

void editorSaveFile(char *fname, teks L);

void openFile(char *fname, teks *L);

void resetArr(char *Arr, int size);

#endif


