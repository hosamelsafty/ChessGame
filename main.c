#include "chessmate.h"

int main(void)
{
    char board[ROW][COL];
    SetColor(12); // Printing start screen
    printf("\n\t\t\t\t   Chessmate\n\t\t\t\t   ---------\n\n");
    SetColor(7);
    printf(" Main Menu\n ---------\n\n 1- New game.\n\n 2- Save game.\n\n 3- Load last game.\n\n Note:  While playing type:\n\t\t\t   -\"SAVE\" to save your game.\n\t\t\t   -\"LOAD\" to load the last game.");
    printf("\n\t\t\t   -\"UNDO\" to undo a move.\n\t\t\t   -\"REDO\" to redo a move.");
    printf("\n\n Press any key to start the game...\n\n\n");
    SetColor(15);
    getch();
    system("cls");
    initialize_board(ROW,COL,board);
    printBoard(ROW,COL,board);
    while(1) //Infinite loop until the game ends
    {
        player1(ROW,COL,board); //Takes a move from player one and executes it if it is valid
        system("cls");
        printBoard(ROW,COL,board);
        if(isP2Checked(COL,board) && !canP2Move(COL,board)) //player 2 is checked and he can't move so he lost the game.
        {
            SetColor(12);
            printf("\nPLAYER 2 IS CHECKMATED!\nPLAYER 1 WON!");
            getch();
            SetColor(15);
            return 0;
        }
        if(!isP2Checked(COL,board) && !canP2Move(COL,board)) //player 2 is not checked and he can't move so the game ended in stalemate
        {
            SetColor(10);
            printf("\nDRAW: THE GAME ENDED IN STALEMATE!");
            getch();
            SetColor(15);
            return 0;
        }
        if(isP2Checked(COL,board)) //player 2 is checked
        {
            SetColor(7);
            printf("\nPLAYER 2 IS IN CHECK!\n");
            SetColor(15);
        }
        player2(ROW,COL,board);
        system("cls");
        printBoard(ROW,COL,board);
        if(isP1Checked(COL,board) && !canP1Move(COL,board)) //player 1 is checked and he can't move so he lost the game.
        {
            SetColor(12);
            printf("\nPLAYER 1 IS CHECKMATED!\nPLAYER 2 WON!");
            getch();
            SetColor(15);
            return 0;
        }
        if(!isP1Checked(COL,board) && !canP1Move(COL,board)) //player 1 is not checked and he can't move so the game ended in stalemate
        {
            SetColor(10);
            printf("\nDRAW: THE GAME ENDED IN STALEMATE!");
            getch();
            SetColor(15);
            return 0;
        }
        if(isP1Checked(COL,board)) //player 1 is checked
        {
            SetColor(7);
            printf("\nPLAYER 1 IS IN CHECK!\n");
            SetColor(15);
        }
    }
    return 0;
}
