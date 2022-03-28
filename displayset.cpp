#include "kota.H"

void displaySet()
{
	TCHAR szOldTitle[MAX_PATH]; // variabel untuk menyimpen judul sebelumnya
   	TCHAR szNewTitle[MAX_PATH]; //variabel untuk menyimpan judul
   	SMALL_RECT windowSize = {0 , 0 , MAXC , MAXR}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize); //fungsi merubah windowsize
   	
	
	if( GetConsoleTitle(szOldTitle, MAX_PATH) ) //fungsi menyimpan judul sebelumnya
	{
		StringCchPrintf(szNewTitle, MAX_PATH, TEXT("Vue - Text Editor"), szOldTitle); // membuat judul baru
	
	    if( !SetConsoleTitle(szNewTitle) ); // fungsi merubah judul ke judul baru
	}
}

void tampilan_awal()
{
	printf("\n\n\n\n\n\n\n\n\t\tVUE - TEKS EDITOR");
	printf("\n\tCtrl+E untuk panduan dan shorcut\n\n\n\n\n\n\n\n\n\n\n");
	system("pause");
	system("cls");
}

