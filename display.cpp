#include "teksEditor.H"


void tampilan_awal()
{
	SetCP(30,5);
	printf("TTTTTT  TTTTTT  TT  TT   TTTTT         \n");
	SetCP(30,6);
	printf("  TT    TT      TT TT   TT             \n");
	SetCP(30,7);
	printf("  TT    TTTTT   TTT      TTTT          \n");
	SetCP(30,8);
	printf("  TT    TT      TT TT       TT         \n");
	SetCP(30,9);
	printf("  TT    TTTTTT  TT  TT  TTTTT          \n");
	
	SetCP(30,11);
	printf("TTTTTT  TTTT     TT  TTTTTTTT   TTTTT    TTTTT         \n");
	SetCP(30,12);
	printf("TT      TT  TT   TT     TT     TT   TT   TT  TT        \n");
	SetCP(30,13);
	printf("TTTTT   TT  TT   TT     TT     TT   TT   TTTTT         \n");
	SetCP(30,14);
	printf("TT      TT  TT   TT     TT     TT   TT   TT  TT        \n");
	SetCP(30,15);
	printf("TTTTTT  TTTT     TT     TT      TTTTT    TT   TT       \n");
	
	SetCP(30,17);
	printf("TT     TT  TT   TT  TTTTTT          \n");
	SetCP(30,18);
	printf("TT     TT  TT   TT  TT    			\n");
	SetCP(30,19);
	printf(" TT   TT   TT   TT  TTTTT  			\n");
	SetCP(30,20);
	printf("  TT TT    TT   TT  TT  			\n");
	SetCP(30,21);
	printf("   TTT      TTTTT   TTTTTT			\n\n\n\n\n\n\n\n");
	
	SetCP(30,28);
	system("pause");
	system("cls");
	
}

void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

int menu()
{
	SetCP(0,1);
	printf("________________________|");
	SetCP(0,6);
    printf("|_______________________|");
	int Set[] = {7,7,7,7}; // DEFAULT COLORS
    int counter = 2;
    char key;
	bool active = true;
    while(active)
    {

        SetCP(0,2);
        color(Set[0]);
        printf("|Open File    [CTRL + O]|");

        SetCP(0,3);
        color(Set[1]);
        printf("|Save File    [CTRL + S]|");

        SetCP(0,4);
        color(Set[2]);
        printf("|Save As      [CTRL + A]|");

        SetCP(0,5);
        color(Set[3]);
        printf("|Back         [   ESC  ]|");

        key = _getch();

        if(key == 72 && (counter >=2 && counter <= 4))
        {
            counter--;
        }
        if(key == 80 && (counter >=1 && counter <= 3))
        {
            counter++;
        }
        if(key == '\r')//carriage return
        {
            if(counter == 1)
            {
                // if enter is click and highlight is on 1 the program will run the code here
                active = false;
                color(7);
                return 1;
            }
            if(counter == 2)
            {
				active = false;
				color(7);
				return 2;
			}
            if(counter == 3)
            {
				active = false;
				color(7);
				return 3;
			}
            if(counter == 4)
            {
				active = false;
				color(7);
				return 4;
			}
        }
        
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;

        if(counter == 1)
        {
            Set[0] = 12;
        }
        if(counter == 2)
        {
            Set[1] = 12;
        }
        if(counter == 3)
        {
            Set[2] = 12;
        }
        if(counter == 4)
        {
            Set[3] = 12;
        }
    }
}