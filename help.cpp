#include "kota.h"

void help(){
	FILE *data; //pendeklarasian tipe data
	char help[600]; // array yang menyimpan si teks yang dalam file
	
	data = fopen("help.txt", "r"); //membuka file dan hanya membacanya saja
	
	system("cls");
	while(!feof(data)) //membaca baris dari data
		{ fgets(help, sizeof(help), data); //membaca string yang ada di file
		printf("%s", help); //menampilkan string dari yanf sudah dibaca
	}
	
	printf("\n\t");
	fclose(data); //menutup file
	system("pause");
}
