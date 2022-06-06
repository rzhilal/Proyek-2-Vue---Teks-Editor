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

#define ESC "\x1b"
#define CSI "\x1b["


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

/*Display*/

void refreshScreen(teks L, int line, int collumns); //Salman

void refreshBlank(); //Zahra

void tampilan_awal(); //Hapid

void tampilan(int line, int collumns); //Salman

int menu(); //Hapid

void color(int color); //Hapid

bool EnableVTMode(); //Salman

/*File Operations*/

void clearlist(teks *L); //Haposan

void editorSaveFile(char *fname, teks L); //Haposan

void openFile(char *fname, teks *L, int *col, int *line); //Zahra

void help();

/*Handle Input*/

bool IsEmpty (teks L);

void CreateTeks (teks * L);

address Alokasi (infotype X);

void DeAlokasi (address *P);

void InsertFirstRow (teks * L, address P);

void InsertNewLine(teks * L, int CurLine, int CurCol);

void InsertChar (teks * L, address New, int CurCol, int CurLine);

void InsVChar (teks * L, infotype X, int CurLine, int CurCol);

void editorKeyProses(); //Rezki bagian cursor dan sisanya hilal

int getMaxRow(teks L);

void DelChar(teks * L, int CurCol, int CurLine);

int getLength(teks L, int CurLine);

/*Cursor*/

void SetCP(char x, char y); //Rezki

#endif


