#include "kota.H"

void displaySet()
{
	TCHAR szOldTitle[MAX_PATH];
   	TCHAR szNewTitle[MAX_PATH];
   	SMALL_RECT windowSize = {0 , 0 , MAXC , MAXR}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
   	
   	// Save current console title.
	
	if( GetConsoleTitle(szOldTitle, MAX_PATH) )
	{
		// Build new console title string.
	
		StringCchPrintf(szNewTitle, MAX_PATH, TEXT("Vue - Text Editor"), szOldTitle);
	
	    // Set console title to new title
	    if( !SetConsoleTitle(szNewTitle) );
	}
}

void tampilan_awal()
{
	printf("\n\n\n\n\n\n\n\n\t\tVUE - TEKS EDITOR");
	printf("\n\tCtrl+E untuk panduan dan shorcut\n\n\n\n\n\n\n\n\n\n\n");
	system("pause");
	system("cls");
}

