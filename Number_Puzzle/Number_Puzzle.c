#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char table[4][4][3] = {
        {"01", "14", "04", "07"}, 
        {"08", "10", "02", "11"},
        {"15", "03", "06", "13"},
        {"12", "09", "05", "  "}
    };
int ePosition[2] = {3, 3}, nMoves = 0;//emptyPosition

void shiftBox(int targetY, int targetX)
{
    int emptyY = ePosition[0];
    int emptyX = ePosition[1];
    strcpy(table[emptyY][emptyX], table[targetY][targetX]);
    strcpy(table[targetY][targetX], "  ");
    printf("\033[%d;%dH%s", ((emptyY * 2) + 5), ((emptyX * 6) + 3), table[emptyY][emptyX]);
    printf("\033[%d;%dH%s", ((targetY * 2) + 5), ((targetX * 6) + 3), "  ");
    ePosition[0] = targetY;
    ePosition[1] = targetX;
    nMoves += 1;
}

int main()
{
    char command;
    printf("Welcome to Number Shift Puzzle.\n");
    printf("Press the W, A, S or D Keys to move the Empty box in the Puzzle. ");
    printf("Press 0 to Exit.");
    printf("\033[4;1H ____  ____  ____  ____ ");
    for(int i = 1; i <= 7; i += 2)
    {
        for(int j = 1; j <= 19; j += 6)
        {
            int a = i / 2;
            int b = j / 5;
            printf("\033[%d;%dH| %s |", (i + 4), j, table[a][b]);
            printf("\033[%d;%dH|____|", (i + 5), j);
        }
    }
    printf("\n");
    while(1)
    {
        command = getchar();
        switch(command)
        {
            case 'w':
            case 'W':
                if(ePosition[0] != 0)
                {
                    shiftBox((ePosition[0] - 1), ePosition[1]);
                }
                break;
            case 'a':
            case 'A':
                if(ePosition[1] != 0)
                {
                    shiftBox(ePosition[0], (ePosition[1] - 1));
                }
                break;
            case 's':
            case 'S':
                if(ePosition[0] != 3)
                {
                    shiftBox((ePosition[0] + 1), ePosition[1]);
                }
                break;
            case 'd':
            case 'D':
                if(ePosition[1] != 3)
                {
                    shiftBox(ePosition[0], (ePosition[1] + 1));
                }
                break;
            case '0':
                exit(0);
                break;
            default:
                printf("\033[14;1HPress the keys W, A, S or D to Move or 0 to Exit.");
        }
        printf("\033[13;1H");
        if( !(strcmp(table[0][0], "01\0")) && !(strcmp(table[0][1], "02")) && !(strcmp(table[0][2], "03")) && !(strcmp(table[0][3], "04")) && 
        !(strcmp(table[1][0], "05")) && !(strcmp(table[1][1], "06")) && !(strcmp(table[1][2], "07")) && !(strcmp(table[1][3], "08")) && 
        !(strcmp(table[2][0], "09")) && !(strcmp(table[2][1], "10")) && !(strcmp(table[2][2], "11")) && !(strcmp(table[2][3], "12")) &&
        !(strcmp(table[3][0], "13")) && !(strcmp(table[3][1], "14")) && !(strcmp(table[3][2], "15")) && !(strcmp(table[3][3], "  ")) )
        {
            printf("\n Congratulations!!! You have successfully completed the Game in %d Moves.\n", nMoves);
            exit(0);
        }
    }
    return 0;
}