#ifndef header_H
#define header_H
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#define MAXR 20
#define MAXC 50

struct
{
	int numcols; 
	int numrows;
	int endrow;
	char teks[MAXR][MAXC];
} matriks;

void editorKeyPresses();
/*Procedure yang berisi tentang pemilihan perintah dimana setiap inputan akan dihandle*/

void editorSaveFile(char *fname);
/*Procedure menyimpan data yang ada pada array ke dalam file*/

void editorOpenFile(char *fname);
/*Membaca sebuah file dan menampilkan isinya pada layar*/

void editorPrint();
/*Procedure menampilkan isi dalam array*/

void curStat();
/*Procedure untuk menampilkan status dari */

void findword(char *word);
/*Procedure mencari kata dalam array*/

void displaySet();
/*Procedure berisi program untuk mengatur tampilan pada terminal*/

void help();
/*menampilkan help atau panduan pengguna*/

void tampilan_awal();
/*Tampilan awal pada awal run program*/

void SetCP(char x, char y);
/*Procedure untuk memindahkan cursor*/

#endif

