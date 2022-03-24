#include "kota.H"

int n;	// number of string in the array
int i; // deklarasi variabel i 

void find()
{
	// input string yang di cari
	printf("Input nama character untuk menentukan baris: ");
	scanf("%s", matriks.teks);

	// mengecek nilai nya sama atau tidak dalam string compare
	for (i = 0; i < n; ++i) {
		if (!strcmp(matriks.teks[matriks.numrows][matriks.numcols]) {
			break;
		}
	}
}

void replace()
{
	// mengecek nilai index dengan variabel inputan user yaitu n karena tidak sama atau false
	if (i != n) {
		printf("Masukan kata :");
		scanf("%s", matriks.teks[matriks.numrows][matriks.numcols]);
		printf("\n\n");
		
	
//		printf("\n\n %s is present in the array at row %d", str, i);
	// pendeklarasian variabel j untuk menampilkan hasil dari inputan i 
		int j;
		for (j = 0; j < n; ++j) {
		printf("%s \n", s[j]);
		}
	}else {
		printf("%s is not present in the array", matriks.teks[matriks.numrows][matriks.numcols]);
	}
}
