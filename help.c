#include "kota.H"

void help(){
	FILE *data;
	char help[600];
	
	data = fopen("help.txt", "r"); //membuka file dan hanya membacanya saja
	
	system("cls");
	while(!feof(data)) //membaca baris dari data
		{ fgets(help, sizeof(help), data); //membaca string yang ada di file
		printf("%s", help); //menampilkan string dari yanf sudah dibaca
	}
	
	printf("\n\t");
	fclose(data); //menutup file
	system("pause");
	main(); //kembali ke main
}
}
