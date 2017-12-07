#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#define ROW 8
#define COL 8
#define MAX_PIECES 30

char removedPieces[MAX_PIECES],playerWhoSaved,virtualBoard[ROW][COL];
int indexRP,flagx,pointer,maxMoves,firstMoveK1,firstMoveR1,firstMoveR12,firstMoveR2,firstMoveR22,firstMoveK2;
int numMovesK1,numMovesK2;
char moves[500][6];

void printBoard(int row,int col,char board[][col]);
void initialize_board(int row,int col,char board[][col]);
void player1(int row,int col,char board[][col]);
void player2(int row,int col,char board[][col]);
int checkLastPlaceP1(char lastPiece);
int checkBishopMoveP1(int input0,int input1,int input2,int input3,char board[][COL]);
int checkRookMoveP1(int input0,int input1,int input2,int input3,char board[][COL]);
int checkLastPlaceP2(char lastPiece);
int checkBishopMoveP2(int input0,int input1,int input2,int input3,char board[][COL]);
int checkRookMoveP2(int input0,int input1,int input2,int input3,char board[][COL]);
void SetColor(int ForgC);
void saveGame(int col,char board[][col]);
void loadGame(int col,char board[][col]);
int isP1Checked(int col,char board[][col]);
int isP2Checked(int col,char board[][col]);
void equateArrays(int col,char board[][col]);
int canP1Move(int col,char board[][col]);
int canP2Move(int col,char board[][col]);
void executeInVirtBoard(int col,char board[][col],int Rowfinal,int Colfinal,int Rowinit,int Colinit);
int canBishopP1Move(int col,char board[][col],int i,int j);
int canRookP1Move(int col,char board[][col],int i,int j);
int canBishopP2Move(int col,char board[][col],int i,int j);
int canRookP2Move(int col,char board[][col],int i,int j);
void saveMoves(int input1,int input2,int input3,int input4,char promotion);
