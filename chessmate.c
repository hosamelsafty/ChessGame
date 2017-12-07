#include "chessmate.h"

indexRP=0;pointer=0;maxMoves=0;firstMoveK1=1;firstMoveR1=1;firstMoveR12=1;firstMoveR2=1;firstMoveR22=1;firstMoveK2=1;
numMovesK1=0;numMovesK2=0;

void printBoard(int row,int col,char board[][col])
{ //prints the board and pieces and removed pieces
    int i,j=8,k,rpCounter=0;
    SetColor(10);
    printf("\n    A   B   C   D   E   F   G   H \t\t");
    SetColor(12);
    printf("  Removed pieces\n\t\t\t\t\t\t  --------------\n");
    SetColor(15);
    printf("  ---------------------------------\n");
    for(i=0; i<row; i++)
    {
        SetColor(10);
        printf("%d ",j-i);
        SetColor(15);
        printf("|");
        for(j=0; j<col; j++)
        {
            if(isalpha(board[i][j]))
            {
                if(islower(board[i][j])) //prints each kind of pieces in a certain color
                {
                    SetColor(14);
                    printf(" %c ",board[i][j]);
                    SetColor(15);
                    printf("|");
                }
                else
                {
                    SetColor(11);
                    printf(" %c ",board[i][j]);
                    SetColor(15);
                    printf("|");
                }
            }
            else printf(" %c |",board[i][j]);
            SetColor(15);
        }
        SetColor(10);
        printf(" %d\t       ",j-i);
        SetColor(12);
        if(i==0) //printing the removed pieces next to the board (5 pieces in every row)
        {
            for(k=0; k<indexRP && rpCounter!=5; k++)
            {
                if(isupper(removedPieces[k]))
                {
                    printf("%c    ",removedPieces[k]);
                    rpCounter++;
                }
            }
        }
        if(i==1)
        {
            rpCounter=0;
            for(k; k<indexRP && rpCounter!=5 && indexRP>5; k++)
            {
                if(isupper(removedPieces[k]))
                {
                    printf("%c    ",removedPieces[k]);
                    rpCounter++;
                }
            }
        }
        if(i==2)
        {
            rpCounter=0;
            for(k; k<indexRP && rpCounter!=5 && indexRP>10; k++)
            {
                if(isupper(removedPieces[k]))
                {
                    printf("%c    ",removedPieces[k]);
                    rpCounter++;
                }
            }
        }
        if(i==5)
        {
            rpCounter=0;
            for(k=0; k<indexRP && rpCounter!=5; k++)
            {
                if(islower(removedPieces[k]))
                {
                    printf("%c    ",removedPieces[k]);
                    rpCounter++;
                }
            }
        }
        if(i==6)
        {
            rpCounter=0;
            for(k; k<indexRP && indexRP>5 && rpCounter!=5; k++)
            {
                if(islower(removedPieces[k]))
                {
                    printf("%c    ",removedPieces[k]);
                    rpCounter++;
                }
            }
        }
        if(i==7)
        {
            rpCounter=0;
            for(k; k<indexRP && indexRP>10 && rpCounter!=5; k++)
            {
                if(islower(removedPieces[k]))
                {
                    printf("%c    ",removedPieces[k]);
                    rpCounter++;
                }
            }
        }
        SetColor(15);
        printf("\n  ---------------------------------\n");
    }
    SetColor(10);
    printf("\n    A   B   C   D   E   F   G   H\n");
    SetColor(15);
}
void initialize_board(int row,int col,char board[][col])
{//gives the board its initial value which is the normal distribution of pieces
    int i,j;
    for(j=0; j<8; j++)
    {
        if(j%2==0)
        {
            board[2][j]=board[4][j]='-';
            board[3][j]=board[5][j]='.';
        }
        else
        {
            board[2][j]=board[4][j]='.';
            board[3][j]=board[5][j]='-';
        }
    }
    board[0][0]=board[0][7]='R';
    board[0][1]=board[0][6]='N';
    board[0][2]=board[0][5]='B';
    board[0][3]='Q';
    board[0][4]='K';
    for(i=0; i<8; i++) board[1][i]='P';
    board[7][0]=board[7][7]='r';
    board[7][1]=board[7][6]='n';
    board[7][2]=board[7][5]='b';
    board[7][3]='q';
    board[7][4]='k';
    for(i=0; i<8; i++) board[6][i]='p';
}
void player1(int row,int col,char board[][col])
{//takes input from player 1 and deals with it
    SetColor(14);
    printf("\nPlayer 1 turn, enter your move: ");
    SetColor(15);
    int input[4],flag=1;
    char handle[50];
    while(flag) //this loop ends only when a move is valid and executed
    {
        flagx=0;
        fflush(stdin);
        gets(handle); //taking input form the user
        if(strlen(handle)==4 && handle[0]=='S' && handle[1]=='A' && handle[2]=='V' && handle[3]=='E')
        {//save
            playerWhoSaved='1';
            saveGame(COL,board);
            SetColor(10);
            printf("Saved Successfully.\n");
            SetColor(15);
            printf("Enter a move if you would like to continue: ");
            continue;
        }
        if(strlen(handle)==4 && handle[0]=='L' && handle[1]=='O' && handle[2]=='A' && handle[3]=='D')
        {//load
            loadGame(COL,board);
            system("cls");
            printBoard(ROW,COL,board);
            if(playerWhoSaved=='0'){

                printf("Failed to load game, No saved games.");
                SetColor(14);
                printf("\nPlayer 1 turn, enter your move: ");
                SetColor(15);
                continue;
            }
            pointer=maxMoves=0; //changing the number of max moves after playing after undo-ing several moves
            if(playerWhoSaved=='1')
            {//giving the turn to the proper player
                SetColor(14);
                printf("\nPlayer 1 turn, enter your move: ");
                SetColor(15);
                continue;
            }
            else return; //to player 2
        }
        if(strlen(handle)==4 && handle[0]=='U' && handle[1]=='N' && handle[2]=='D' && handle[3]=='O')
        {//undo
            if(pointer==0)
            {
                printf("No moves to undo, enter a move: ");
                continue;
            }
            pointer--;
            if(moves[pointer][4]=='0' && moves[pointer][5]=='0')//no removed pieces and no promotion
            {
                //undo castling right direction
                if(moves[pointer][1]=='0' && moves[pointer][0]=='4' && moves[pointer][3]=='0' && moves[pointer][2]=='2'){
                   if(board[0][3]=='R' && board[0][1]=='.' && board[0][2]=='K' && board[0][0]=='-' && board[0][4]=='-'){
                     board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                     if(abs(moves[pointer][3]-'0'-moves[pointer][2]-'0')%2==0) board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='-';
                     else board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='.';
                     board[0][0]='R';board[0][3]='.';
                     firstMoveK2=1;firstMoveR2=1;
                     return;
                   }
                }
                //undo castling left direction
                if(moves[pointer][1]=='0' && moves[pointer][0]=='4' && moves[pointer][3]=='0' && moves[pointer][2]=='6'){
                   if(board[0][5]=='R' && board[0][7]=='.' && board[0][6]=='K' && board[0][4]=='-'){
                     board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                     if(abs(moves[pointer][3]-'0'-moves[pointer][2]-'0')%2==0) board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='-';
                     else board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='.';
                     board[0][7]='R';board[0][5]='.';
                     firstMoveK2=1;firstMoveR22=1;
                     return;
                   }
                }
                board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                if(abs(moves[pointer][3]-'0'-moves[pointer][2]-'0')%2==0) board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='-';
                else board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='.';
                if(board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=='K'){
                    numMovesK2--;
                    if(numMovesK2==0) firstMoveK2=1;
                }
                return;
            }
            if(moves[pointer][4]!='0' && moves[pointer][5]=='0') //in case of a removed piece
            {
                board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']=moves[pointer][4];
                indexRP--;
                if(board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=='K'){
                    numMovesK2--;
                    if(numMovesK2==0) firstMoveK2=1;
                }
                return;
            }
            if(moves[pointer][4]=='0' && moves[pointer][5]!='0') //in case of promotion
            {
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='P';
                board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                if(abs(moves[pointer][3]-'0'-moves[pointer][2]-'0')%2==0) board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='-';
                else board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='.';
                return;
            }
            if(moves[pointer][4]!='0' && moves[pointer][5]!='0')//in case of a removed piece and promotion
            {
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='P';
                board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']=moves[pointer][4];
                indexRP--;
                return;
            }
        }
        if(strlen(handle)==4 && handle[0]=='R' && handle[1]=='E' && handle[2]=='D' && handle[3]=='O')
        {//redo
            if(pointer==maxMoves)
            {
                printf("No undo-ed moves to redo, enter a move: ");
                continue;
            }
            if(moves[pointer][5]=='0')//no promotion
            {
                //redo castling left direction
                if(moves[pointer][1]=='7' && moves[pointer][0]=='4' && moves[pointer][3]=='7' && moves[pointer][2]=='2'){
                   if(board[7][3]=='-' && board[7][1]=='-' && board[7][2]=='.' && board[7][0]=='r' && board[7][4]=='k'){
                     board[7][2]='k';board[7][3]='r';
                     board[7][0]=board[7][4]='.';
                     pointer++;
                     return;
                   }
                }
                //redo castling right direction
                if(moves[pointer][1]=='7' && moves[pointer][0]=='4' && moves[pointer][3]=='7' && moves[pointer][2]=='6'){
                   if(board[7][5]=='-' && board[7][6]=='.' && board[7][7]=='r' && board[7][4]=='k'){
                     board[7][6]='k';board[7][5]='r';
                     board[7][7]='-';
                     board[7][4]='.';
                     pointer++;
                     return;
                   }
                }
                if(board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=='k') numMovesK1++;
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']=board[moves[pointer][1]-'0'][moves[pointer][0]-'0'];
                if(abs(moves[pointer][1]-'0'-moves[pointer][0]-'0')%2==0) board[moves[pointer][1]-'0'][moves[pointer][0]-'0']='-';
                else board[moves[pointer][1]-'0'][moves[pointer][0]-'0']='.';
                if(moves[pointer][4]!='0')
                {
                    removedPieces[indexRP]=moves[pointer][4];
                    indexRP++;
                }
                pointer++;
                return;
            }
            if(moves[pointer][5]!='0')//promotion
            {
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']=moves[pointer][5];
                if(abs(moves[pointer][1]-'0'-moves[pointer][0]-'0')%2==0) board[moves[pointer][1]-'0'][moves[pointer][0]-'0']='-';
                else board[moves[pointer][1]-'0'][moves[pointer][0]-'0']='.';
                if(moves[pointer][4]!='0')
                {
                    removedPieces[indexRP]=moves[pointer][4];
                    indexRP++;
                }
                pointer++;
                return;
            }
        }
        //if the player wanted castling (E1C1)
        if(strlen(handle)==4 && handle[0]=='E' && handle[1]=='1' && handle[2]=='C' && handle[3]=='1' && firstMoveK1 && firstMoveR1 && board[7][3]=='-' && board[7][1]=='-' && board[7][2]=='.' && !isP1Checked(COL,board)){
            executeInVirtBoard(COL,board,7,3,7,4);
            if(isP1Checked(COL,virtualBoard)){ //checking if the squares in between the rook and the king are attacked
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
            executeInVirtBoard(COL,board,7,2,7,4);
            if(isP1Checked(COL,virtualBoard)){
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
            board[7][2]='k';board[7][4]='.';
            board[7][3]='r';board[7][0]='.';
            saveMoves(4,7,2,7,'0');
            maxMoves=pointer;
            numMovesK1++;
            firstMoveK1=firstMoveR1=0;
            printf("\n");
            return;
        }
        //if the player wanted castling (E1G1) with same algorithm of E1C1
        if(strlen(handle)==4 && handle[0]=='E' && handle[1]=='1' && handle[2]=='G' && handle[3]=='1' && firstMoveK1 && firstMoveR12 && board[7][5]=='-' && board[7][6]=='.' && !isP1Checked(COL,board)){
            executeInVirtBoard(COL,board,7,5,7,4);
            if(isP1Checked(COL,virtualBoard)){
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
            executeInVirtBoard(COL,board,7,6,7,4);
            if(isP1Checked(COL,virtualBoard)){
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
            board[7][6]='k';board[7][4]='.';
            board[7][5]='r';board[7][7]='-';
            saveMoves(4,7,6,7,'0');
            maxMoves=pointer;
            numMovesK1++;
            firstMoveK1=firstMoveR1=0;
            printf("\n");
            return;
        }
        if(strlen(handle)>5 || strlen(handle)<4)//invalid input
        {
            SetColor(12);
            printf("Invalid move, enter a valid move: ");
            SetColor(15);
            continue;
        }
        else if(strlen(handle)==4)
        {//checking if the move is valid
            if(handle[0]>='A' && handle[0]<='H' && handle[2]>='A' && handle[2]<='H' && handle[1]>'0' && handle[1]<'9' && handle[3]>'0' && handle[3]<'9')
            {
                handle[1]='8'-(handle[1]-'1');
                handle[3]='8'-(handle[3]-'1');
                input[0]=handle[0]-'A';
                input[1]=handle[1]-'0';
                input[2]=handle[2]-'A';
                input[3]=handle[3]-'0';
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
        }
        else
        {//promotion
            if(handle[0]>='A' && handle[0]<='H' && handle[2]>='A' && handle[2]<='H' && handle[1]>'0' && handle[1]<'9' && handle[3]>'0' && handle[3]<'9')
            {
                if(handle[4]=='q' || handle[4]=='b' || handle[4]=='r' || handle[4]=='n')
                {
                    handle[1]='8'-(handle[1]-'1');
                    handle[3]='8'-(handle[3]-'1');
                    input[0]=handle[0]-'A';
                    input[1]=handle[1]-'0';
                    input[2]=handle[2]-'A';
                    input[3]=handle[3]-'0';
                    if(board[input[1]-1][input[0]]!='p')
                    {
                        SetColor(12);
                        printf("Invalid move, enter a valid move: ");
                        SetColor(15);
                        continue;
                    }
                }
                else
                {
                    SetColor(12);
                    printf("Invalid move, enter a valid move: ");
                    SetColor(15);
                    continue;
                }
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
        }
        switch (board[input[1]-1][input[0]])//movements restriction for the pieces
        {
        case 'p'://pawn
            if(input[1]==7 && ((input[0]==input[2]&&(input[1]-input[3])==2) && (board[input[3]-1][input[2]]=='.' || board[input[3]-1][input[2]]=='-'))) flag=0; //the first 2 squares move for the pawn
            else if((input[0]==input[2]&&(input[1]-input[3])==1) && (board[input[3]-1][input[2]]=='.' || board[input[3]-1][input[2]]=='-'))
            {
                if(input[3]==1 && strlen(handle)==4)
                {
                    printf("Error,You must promote the pawn to another piece, enter a move: ");
                }
                else if(input[3]==1 && strlen(handle)==5)
                {
                    board[input[1]-1][input[0]]=handle[4];
                    flag=0;
                }
                else flag=0;
            }
            else if(input[1]-input[3]==1 && abs(input[2]-input[0])==1 && isupper(board[input[3]-1][input[2]]))
            {
                if(input[3]==1 && strlen(handle)==4)
                {
                    printf("Error,You must promote the pawn to another piece, enter a move: ");
                }
                else if(input[3]==1 && strlen(handle)==5)
                {
                    board[input[1]-1][input[0]]=handle[4];
                    flag=0;
                    flagx=1;//flagx is for knowing if the move resulted in removing a piece
                }
                else
                {
                    flag=0;
                    flagx=1;
                }
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'b'://bishop
            if(abs(input[0]-input[2])==abs(input[3]-input[1]) && input[0]!=input[2]) flag=checkBishopMoveP1(input[0],input[1],input[2],input[3],board);
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'r'://rook
            if((input[0]-input[2]==0 && abs(input[3]-input[1])>0) || (input[3]-input[1]==0 && abs(input[0]-input[2])>0)) flag=checkRookMoveP1(input[0],input[1],input[2],input[3],board);
            if(!flag){
                if(input[0]==0 && input[1]-1==7) firstMoveR1=0; //to know if the rook moved before
                else if(input[0]==7 && input[1]-1==7) firstMoveR12=0;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'q'://queen
            if(abs(input[0]-input[2])==abs(input[3]-input[1])&& input[0]!=input[2]) flag=checkBishopMoveP1(input[0],input[1],input[2],input[3],board);//both the movements of the bishop and rook
            else if((input[0]-input[2]==0 && abs(input[3]-input[1])>0) || (input[3]-input[1]==0 && abs(input[0]-input[2])>0)) flag=checkRookMoveP1(input[0],input[1],input[2],input[3],board);
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'n'://knight
            if((abs(input[0]-input[2])==2 && abs(input[3]-input[1])==1) || (abs(input[0]-input[2])==1 && abs(input[3]-input[1])==2)) flag=checkLastPlaceP1(board[input[3]-1][input[2]]);
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'k'://king
            if((abs(input[0]-input[2])==1 && abs(input[3]-input[1])<2) || (abs(input[3]-input[1])==1 && abs(input[0]-input[2])<2)) flag=checkLastPlaceP1(board[input[3]-1][input[2]]);
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        default://refused move
            SetColor(12);
            printf("Invalid move, enter a valid move: ");
            SetColor(15);
        }
        if(!flag) //move was valid
        {
            executeInVirtBoard(COL,board,input[3]-1,input[2],input[1]-1,input[0]);
            if(isP1Checked(COL,virtualBoard)) //to refuse the move if it results in check on the same player
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                flag=1;
            }
            else if(flagx) //a piece was removed
            {
                removedPieces[indexRP]=board[input[3]-1][input[2]];
                indexRP++;
            }
        }
    }
    if(board[input[1]-1][input[0]]=='k'){ //to know if the king moved before
        firstMoveK1=0;
        numMovesK1++;
    }
    if(strlen(handle)==5) saveMoves(input[0],input[1]-1,input[2],input[3]-1,handle[4]); //saving the moves for undo and redo
    else saveMoves(input[0],input[1]-1,input[2],input[3]-1,'0');
    maxMoves=pointer;
    board[input[3]-1][input[2]]=board[input[1]-1][input[0]];//executing the move
    if(abs(input[1]-1-input[0])%2==0) board[input[1]-1][input[0]]='-';
    else board[input[1]-1][input[0]]='.';
    printf("\n");
}
void player2(int row,int col,char board[][col])
{//the same code as player 1 but for player 2
    SetColor(11);
    printf("\nPlayer 2 turn, enter your move: ");
    SetColor(15);
    int input[4],flag=1;
    char handle[50];
    while(flag)
    {
        flagx=0;
        fflush(stdin);
        gets(handle);
        if(strlen(handle)==4 && handle[0]=='S' && handle[1]=='A' && handle[2]=='V' && handle[3]=='E')
        {
            playerWhoSaved='2';
            saveGame(COL,board);
            SetColor(10);
            printf("Saved Successfully.\n");
            SetColor(15);
            printf("Enter a move if you would like to continue: ");
            continue;
        }
        if(strlen(handle)==4 && handle[0]=='L' && handle[1]=='O' && handle[2]=='A' && handle[3]=='D')
        {
            loadGame(COL,board);
            system("cls");
            printBoard(ROW,COL,board);
            if(playerWhoSaved=='0')
            {
                printf("Failed to load game, No saved games.");
                SetColor(11);
                printf("\nPlayer 2 turn, enter your move: ");
                SetColor(15);
                continue;
            }
            pointer=maxMoves=0;
            if(playerWhoSaved=='2')
            {
                SetColor(11);
                printf("\nPlayer 2 turn, enter your move: ");
                SetColor(15);
                continue;
            }
            else return;
        }
        if(strlen(handle)==4 && handle[0]=='U' && handle[1]=='N' && handle[2]=='D' && handle[3]=='O')
        {
            if(pointer==0)
            {
                printf("No moves to undo, enter a move: ");
                continue;
            }
            pointer--;
            if(moves[pointer][4]=='0' && moves[pointer][5]=='0')
            {
                if(moves[pointer][1]=='7' && moves[pointer][0]=='4' && moves[pointer][3]=='7' && moves[pointer][2]=='2'){
                   if(board[7][3]=='r' && board[7][1]=='-' && board[7][2]=='k' && board[7][0]=='.' && board[7][4]=='.'){
                     board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                     if(abs(moves[pointer][3]-'0'-moves[pointer][2]-'0')%2==0) board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='-';
                     else board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='.';
                     board[7][0]='r';board[7][3]='-';
                     firstMoveK1=1;firstMoveR1=1;
                     return;
                   }
                }
                if(moves[pointer][1]=='7' && moves[pointer][0]=='4' && moves[pointer][3]=='7' && moves[pointer][2]=='6'){
                   if(board[7][5]=='r' && board[7][7]=='-' && board[7][6]=='k' && board[7][4]=='.'){
                     board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                     if(abs(moves[pointer][3]-'0'-moves[pointer][2]-'0')%2==0) board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='-';
                     else board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='.';
                     board[7][7]='r';board[7][5]='-';
                     firstMoveK1=1;firstMoveR12=1;
                     return;
                   }
                }
                board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                if(abs(moves[pointer][3]-'0'-moves[pointer][2]-'0')%2==0) board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='-';
                else board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='.';
                if(board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=='k'){
                    numMovesK1--;
                    if(numMovesK1==0) firstMoveK1=1;
                }
                return;
            }
            if(moves[pointer][4]!='0' && moves[pointer][5]=='0')
            {
                board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']=moves[pointer][4];
                indexRP--;
                if(board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=='k'){
                    numMovesK1--;
                    if(numMovesK1==0) firstMoveK1=1;
                }
                return;
            }
            if(moves[pointer][4]=='0' && moves[pointer][5]!='0')
            {
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='p';
                board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                if(abs(moves[pointer][3]-'0'-moves[pointer][2]-'0')%2==0) board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='-';
                else board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='.';
                return;
            }
            if(moves[pointer][4]!='0' && moves[pointer][5]!='0')
            {
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']='p';
                board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=board[moves[pointer][3]-'0'][moves[pointer][2]-'0'];
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']=moves[pointer][4];
                indexRP--;
                return;
            }
        }
        if(strlen(handle)==4 && handle[0]=='R' && handle[1]=='E' && handle[2]=='D' && handle[3]=='O')
        {
            if(pointer==maxMoves)
            {
                printf("No undo-ed moves to redo, enter a move: ");
                continue;
            }
            if(moves[pointer][5]=='0')
            {
                if(moves[pointer][1]=='0' && moves[pointer][0]=='4' && moves[pointer][3]=='0' && moves[pointer][2]=='2'){
                   if(board[0][3]=='.' && board[0][1]=='.' && board[0][2]=='-' && board[0][0]=='R' && board[0][4]=='K'){
                     board[0][2]='K';board[0][3]='R';
                     board[0][0]=board[0][4]='-';
                     pointer++;
                     return;
                   }
                }
                if(moves[pointer][1]=='0' && moves[pointer][0]=='4' && moves[pointer][3]=='0' && moves[pointer][2]=='6'){
                   if(board[0][5]=='.' && board[0][6]=='-' && board[0][7]=='R' && board[0][4]=='K'){
                     board[0][6]='K';board[0][5]='R';
                     board[0][7]='.';
                     board[0][4]='-';
                     pointer++;
                     return;
                   }
                }
                if(board[moves[pointer][1]-'0'][moves[pointer][0]-'0']=='K') numMovesK2++;
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']=board[moves[pointer][1]-'0'][moves[pointer][0]-'0'];
                if(abs(moves[pointer][1]-'0'-moves[pointer][0]-'0')%2==0) board[moves[pointer][1]-'0'][moves[pointer][0]-'0']='-';
                else board[moves[pointer][1]-'0'][moves[pointer][0]-'0']='.';
                if(moves[pointer][4]!='0')
                {
                    removedPieces[indexRP]=moves[pointer][4];
                    indexRP++;
                }
                pointer++;
                return;
            }
            if(moves[pointer][5]!='0')
            {
                board[moves[pointer][3]-'0'][moves[pointer][2]-'0']=moves[pointer][5];
                if(abs(moves[pointer][1]-'0'-moves[pointer][0]-'0')%2==0) board[moves[pointer][1]-'0'][moves[pointer][0]-'0']='-';
                else board[moves[pointer][1]-'0'][moves[pointer][0]-'0']='.';
                if(moves[pointer][4]!='0')
                {
                    removedPieces[indexRP]=moves[pointer][4];
                    indexRP++;
                }
                pointer++;
                return;
            }
        }
        if(strlen(handle)==4 && handle[0]=='E' && handle[1]=='8' && handle[2]=='C' && handle[3]=='8' && firstMoveK2 && firstMoveR2 && board[0][3]=='.' && board[0][1]=='.' && board[0][2]=='-' && !isP2Checked(COL,board)){
            executeInVirtBoard(COL,board,0,3,0,4);
            if(isP2Checked(COL,virtualBoard)){
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
            executeInVirtBoard(COL,board,0,2,0,4);
            if(isP2Checked(COL,virtualBoard)){
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
            board[0][2]='K';board[0][4]='-';
            board[0][3]='R';board[0][0]='-';
            saveMoves(4,0,2,0,'0');
            maxMoves=pointer;
            numMovesK2++;
            firstMoveK2=firstMoveR2=0;
            printf("\n");
            return;
        }
        if(strlen(handle)==4 && handle[0]=='E' && handle[1]=='8' && handle[2]=='G' && handle[3]=='8' && firstMoveK2 && firstMoveR22 && board[0][5]=='.' && board[0][6]=='-' && !isP2Checked(COL,board)){
            executeInVirtBoard(COL,board,0,5,0,4);
            if(isP2Checked(COL,virtualBoard)){
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
            executeInVirtBoard(COL,board,0,6,0,4);
            if(isP2Checked(COL,virtualBoard)){
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
            board[0][6]='K';board[0][4]='-';
            board[0][5]='R';board[0][7]='.';
            saveMoves(4,0,6,0,'0');
            maxMoves=pointer;
            numMovesK2++;
            firstMoveK2=firstMoveR22=0;
            printf("\n");
            return;
        }
        if(strlen(handle)>5 || strlen(handle)<4)
        {
            SetColor(12);
            printf("Invalid move, enter a valid move: ");
            SetColor(15);
            continue;
        }
        else if(strlen(handle)==4)
        {
            if(handle[0]>='A' && handle[0]<='H' && handle[2]>='A' && handle[2]<='H' && handle[1]>'0' && handle[1]<'9' && handle[3]>'0' && handle[3]<'9')
            {
                handle[1]='8'-(handle[1]-'1');
                handle[3]='8'-(handle[3]-'1');
                input[0]=handle[0]-'A';
                input[1]=handle[1]-'0';
                input[2]=handle[2]-'A';
                input[3]=handle[3]-'0';
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
        }
        else
        {
            if(handle[0]>='A' && handle[0]<='H' && handle[2]>='A' && handle[2]<='H' && handle[1]>'0' && handle[1]<'9' && handle[3]>'0' && handle[3]<'9')
            {
                if(handle[4]=='Q' || handle[4]=='B' || handle[4]=='R' || handle[4]=='N')
                {
                    handle[1]='8'-(handle[1]-'1');
                    handle[3]='8'-(handle[3]-'1');
                    input[0]=handle[0]-'A';
                    input[1]=handle[1]-'0';
                    input[2]=handle[2]-'A';
                    input[3]=handle[3]-'0';
                    if(board[input[1]-1][input[0]]!='P')
                    {
                        SetColor(12);
                        printf("Invalid move, enter a valid move: ");
                        SetColor(15);
                        continue;
                    }
                }
                else
                {
                    SetColor(12);
                    printf("Invalid move, enter a valid move: ");
                    SetColor(15);
                    continue;
                }
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                continue;
            }
        }
        switch (board[input[1]-1][input[0]])
        {
        case 'P':
            if(input[1]==2 && ((input[0]==input[2]&&(input[3]-input[1])==2) && (board[input[3]-1][input[2]]=='.' || board[input[3]-1][input[2]]=='-'))) flag=0;
            else if((input[0]==input[2]&&(input[3]-input[1])==1) && (board[input[3]-1][input[2]]=='.' || board[input[3]-1][input[2]]=='-'))
            {
                if(input[3]==8 && strlen(handle)==4)
                {
                    printf("Error,You must promote the pawn to another piece, enter a move: ");
                }
                else if(input[3]==8 && strlen(handle)==5)
                {
                    board[input[1]-1][input[0]]=handle[4];
                    flag=0;
                }
                else flag=0;
            }
            else if(input[3]-input[1]==1 && abs(input[2]-input[0])==1 && islower(board[input[3]-1][input[2]]))
            {
                if(input[3]==8 && strlen(handle)==4)
                {
                    printf("Error,You must promote the pawn to another piece, enter a move: ");
                }
                else if(input[3]==8 && strlen(handle)==5)
                {
                    board[input[1]-1][input[0]]=handle[4];
                    flag=0;
                    flagx=1;
                }
                else
                {
                    flag=0;
                    flagx=1;
                }
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'B':
            if(abs(input[0]-input[2])==abs(input[3]-input[1]) && input[0]!=input[2]) flag=checkBishopMoveP2(input[0],input[1],input[2],input[3],board);
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'R':
            if((input[0]-input[2]==0 && abs(input[3]-input[1])>0) || (input[3]-input[1]==0 && abs(input[0]-input[2])>0)) flag=checkRookMoveP2(input[0],input[1],input[2],input[3],board);
            if(!flag){
                if(input[0]==0 && input[1]-1==0) firstMoveR2=0;
                else if(input[0]==7 && input[1]-1==0) firstMoveR22=0;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'Q':
            if(abs(input[0]-input[2])==abs(input[3]-input[1])&& input[0]!=input[2]) flag=checkBishopMoveP2(input[0],input[1],input[2],input[3],board);
            else if((input[0]-input[2]==0 && abs(input[3]-input[1])>0) || (input[3]-input[1]==0 && abs(input[0]-input[2])>0)) flag=checkRookMoveP2(input[0],input[1],input[2],input[3],board);
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'N':
            if((abs(input[0]-input[2])==2 && abs(input[3]-input[1])==1) || (abs(input[0]-input[2])==1 && abs(input[3]-input[1])==2)) flag=checkLastPlaceP2(board[input[3]-1][input[2]]);
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        case 'K':
            if((abs(input[0]-input[2])==1 && abs(input[3]-input[1])<2) || (abs(input[3]-input[1])==1 && abs(input[0]-input[2])<2)) flag=checkLastPlaceP2(board[input[3]-1][input[2]]);
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
            }
            break;
        default:
            SetColor(12);
            printf("Invalid move, enter a valid move: ");
            SetColor(15);
        }
        if(!flag)
        {
            executeInVirtBoard(COL,board,input[3]-1,input[2],input[1]-1,input[0]);
            if(isP2Checked(COL,virtualBoard))
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                flag=1;
            }
            else if(flagx)
            {
                removedPieces[indexRP]=board[input[3]-1][input[2]];
                indexRP++;
            }
        }
    }
    if(board[input[1]-1][input[0]]=='K'){
        firstMoveK2=0;
        numMovesK2++;
    }
    if(strlen(handle)==5) saveMoves(input[0],input[1]-1,input[2],input[3]-1,handle[4]);
    else saveMoves(input[0],input[1]-1,input[2],input[3]-1,'0');
    maxMoves=pointer;
    board[input[3]-1][input[2]]=board[input[1]-1][input[0]];
    if(abs(input[1]-1-input[0])%2==0) board[input[1]-1][input[0]]='-';
    else board[input[1]-1][input[0]]='.';
    printf("\n");
}
int checkLastPlaceP1(char lastPlace)
{
    if(isalpha(lastPlace))//checking the final destination square if it contains a piece
    {
        if(isupper(lastPlace))//a piece of the enemy
        {
            flagx=1;
            return 0;
        }
        else
        { //a piece that belongs to player 1
            SetColor(12);
            printf("Invalid move, enter a valid move: ");
            SetColor(15);
            return 1;
        }
    }
    else return 0;
}
int checkBishopMoveP1(int input0,int input1,int input2,int input3,char board[][COL])
{
    int j=0,i;
    if(input2>input0 && input3>input1)//checking the east south direction
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1+j][i+1]=='.' || board[input1+j][i+1]=='-')//checking if a piece is in the way
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP1(board[input3-1][input2]);
    }
    else if(input2<input0 && input3<input1)//the north west direction
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1-2-j][i-1-2*j]=='.' || board[input1-2-j][i-1-2*j]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP1(board[input3-1][input2]);
    }
    else if(input2>input0 && input3<input1)//north east
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1-2-j][i+1]=='.' || board[input1-2-j][i+1]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP1(board[input3-1][input2]);
    }
    else if(input2<input0 && input3>input1)//south west
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1+j][i-1-2*j]=='.' || board[input1+j][i-1-2*j]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP1(board[input3-1][input2]);
    }
}
int checkRookMoveP1(int input0,int input1,int input2,int input3,char board[][COL])
{
    int  j=0,i;
    if(input2>input0)//checking the east direction
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1-1][i+1]=='.' || board[input1-1][i+1]=='-')//if a piece is in the way
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP1(board[input3-1][input2]);
    }
    else if(input2<input0)//moving left
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1-1][i-1-2*j]=='.' || board[input1-1][i-1-2*j]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP1(board[input3-1][input2]);
    }
    else if(input3>input1)//down
    {
        for(i=input1; i<input3-1; i++)
        {
            if(board[input1+j][input0]=='.' || board[input1+j][input0]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP1(board[input3-1][input2]);
    }
    else if(input3<input1)//up
    {
        for(i=input1; i<2*input1-input3-1; i++)
        {
            if(board[input1-2-j][input0]=='.' || board[input1-2-j][input0]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP1(board[input3-1][input2]);
    }
}
void SetColor(int ForgC)//coloring the game
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
void saveGame(int col,char board[][col])
{
    FILE * save;
    save=fopen("Save Game.txt","w");
    if(save==NULL) printf("Failed to open save game file for saving.\n");
    else
    {
        fwrite(board,64,1,save);//64 byte 1 element
        fprintf(save,"%c%d",playerWhoSaved,indexRP);
        fwrite(removedPieces,indexRP,1,save);
        fclose(save);
    }
}
void loadGame(int col,char board[][col])
{
    playerWhoSaved='0';
    FILE * load;
    load=fopen("Save Game.txt","r");
    if(load!=NULL)
    {
        fread(board,64,1,load);
        fread(&playerWhoSaved,1,1,load);
        fscanf(load,"%d",&indexRP);
        fread(removedPieces,indexRP,1,load);
        fclose(load);
    }
}
int isP1Checked(int col,char board[][col])
{
    int i,j,k,l,flag1,flag2,flag3,flag4;
    for(i=0; i<8; i++)//a loop from the start of the board to the end
    {
        for(j=0; j<8; j++)
        {
            flag1=1,flag2=1,flag3=1,flag4=1,l=0;
            if(isalpha(board[i][j])&&isupper(board[i][j]))//if the piece is an uppercase
            {
                switch(board[i][j])
                {
                case 'P':
                    if(board[i+1][j+1]=='k' || board[i+1][j-1]=='k') return 1;
                    break;

                case 'N':
                    if(board[i+1][j+2]=='k' || board[i+1][j-2]=='k' || board[i-2][j+1]=='k' || board[i-2][j-1]=='k') return 1;
                    if(board[i-1][j+2]=='k' || board[i-1][j-2]=='k' || board[i+2][j+1]=='k' || board[i+2][j-1]=='k') return 1;
                    break;

                case 'R':
                    for(k=i; k<i+7; k++)//checking up and down
                    {
                        if(flag1 && k<7 && board[k+1][j]=='k') return 1;
                        else if(isalpha(board[k+1][j])) flag1=0;
                        if(flag2 && k-1-2*l>=0 && board[k-1-2*l][j]=='k') return 1;
                        else if(isalpha(board[k-1-2*l][j])) flag2=0;
                        l++;
                    }
                    l=0,flag1=1,flag2=1;
                    for(k=j; k<j+7; k++)//checking the right and left
                    {
                        if(flag1 && k<7 && board[i][k+1]=='k') return 1;
                        else if(isalpha(board[i][k+1])) flag1=0;
                        if(flag2 && k-1-2*l>=0 && board[i][k-1-2*l]=='k') return 1;
                        else if(isalpha(board[i][k-1-2*l])) flag2=0;
                        l++;
                    }
                    break;

                case 'B':
                    for(k=1; k<8; k++)//checking the 4 directions with flags to stop if needed
                    {
                        if(flag1 && i+k<8 && j+k<8 && board[i+k][j+k]=='k') return 1;
                        else if(isalpha(board[i+k][j+k])) flag1=0;
                        if(flag2 && i-k>=0 && j-k>=0 && board[i-k][j-k]=='k') return 1;
                        else if(isalpha(board[i-k][j-k])) flag2=0;
                        if(flag3 && i-k>=0 && j+k<8 && board[i-k][j+k]=='k') return 1;
                        else if(isalpha(board[i-k][j+k])) flag3=0;
                        if(flag4 && i+k<8 && j-k>=0 && board[i+k][j-k]=='k') return 1;
                        else if(isalpha(board[i+k][j-k])) flag4=0;
                    }
                    break;

                case 'Q':
                    for(k=1; k<8; k++)//the same as bishop
                    {
                        if(flag1 && i+k<8 && j+k<8 && board[i+k][j+k]=='k') return 1;
                        else if(isalpha(board[i+k][j+k])) flag1=0;
                        if(flag2 && i-k>=0 && j-k>=0 && board[i-k][j-k]=='k') return 1;
                        else if(isalpha(board[i-k][j-k])) flag2=0;
                        if(flag3 && i-k>=0 && j+k<8 && board[i-k][j+k]=='k') return 1;
                        else if(isalpha(board[i-k][j+k])) flag3=0;
                        if(flag4 && i+k<8 && j-k>=0 && board[i+k][j-k]=='k') return 1;
                        else if(isalpha(board[i+k][j-k])) flag4=0;
                    }
                    flag1=1,flag2=1;
                    for(k=i; k<i+7; k++)//the same as rook
                    {
                        if(flag1 && k<7 && board[k+1][j]=='k') return 1;
                        else if(isalpha(board[k+1][j])) flag1=0;
                        if(flag2 && k-1-2*l>=0 && board[k-1-2*l][j]=='k') return 1;
                        else if(isalpha(board[k-1-2*l][j])) flag2=0;
                        l++;
                    }
                    l=0,flag1=1,flag2=1;
                    for(k=j; k<j+7; k++)
                    {
                        if(flag1 && k<7 && board[i][k+1]=='k') return 1;
                        else if(isalpha(board[i][k+1])) flag1=0;
                        if(flag2 && k-1-2*l>=0 && board[i][k-1-2*l]=='k') return 1;
                        else if(isalpha(board[i][k-1-2*l])) flag2=0;
                        l++;
                    }
                case 'K': if(board[i][j+1]=='k' || board[i][j-1]=='k' || board[i+1][j]=='k' || board[i-1][j]=='k' || board[i+1][j+1]=='k' || board[i-1][j-1]=='k' || board[i+1][j-1]=='k' || board[i-1][j+1]=='k') return 1;
                default:
                    continue;
                }
            }
            else continue;
        }
    }
    return 0;
}
void equateArrays(int col,char board[][col])
{
    int i,j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            virtualBoard[i][j]=board[i][j];
        }
    }
}
int canP1Move(int col,char board[][col])
{
    int i,j;//executing every valid move for player 1 in a virtual board until founding one that removes the check or finding non
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(isalpha(board[i][j])&&islower(board[i][j]))
            {
                switch(board[i][j])
                {
                case 'p':
                    if(board[i-1][j]=='.' || board[i-1][j]=='-')
                    {
                        executeInVirtBoard(COL,board,i-1,j,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if(i==6 && (board[i-2][j]=='.' || board[i-2][j]=='-') && (board[i-1][j]=='.' || board[i-1][j]=='-')){
                        executeInVirtBoard(COL,board,i-2,j,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((isupper(board[i-1][j+1])) && i-1>-1 && j+1<8)
                    {
                        executeInVirtBoard(COL,board,i-1,j+1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((isupper(board[i-1][j-1])) && i-1>-1 && j-1>-1)
                    {
                        executeInVirtBoard(COL,board,i-1,j-1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    break;

                case 'n':
                    if((board[i+1][j+2]=='.' || board[i+1][j+2]=='-' || isupper(board[i+1][j+2])) && i+1<8 && j+2<8)
                    {
                        executeInVirtBoard(COL,board,i+1,j+2,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i+1][j-2]=='.' || board[i+1][j-2]=='-' || isupper(board[i+1][j-2])) && i+1<8 && j-2>-1)
                    {
                        executeInVirtBoard(COL,board,i+1,j-2,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i-1][j+2]=='.' || board[i-1][j+2]=='-' || isupper(board[i-1][j+2])) && i-1>-1 && j+2<8)
                    {
                        executeInVirtBoard(COL,board,i-1,j+2,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i-1][j-2]=='.' || board[i-1][j-2]=='-' || isupper(board[i-1][j-2])) && i-1>-1 && j-2>-1)
                    {
                        executeInVirtBoard(COL,board,i-1,j-2,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i+2][j+1]=='.' || board[i+2][j+1]=='-' || isupper(board[i+2][j+1])) && i+2<8 && j+1<8)
                    {
                        executeInVirtBoard(COL,board,i+2,j+1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i+2][j-1]=='.' || board[i+2][j-1]=='-' || isupper(board[i+2][j-1])) && i+2<8 && j-1>-1)
                    {
                        executeInVirtBoard(COL,board,i+2,j-1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i-2][j+1]=='.' || board[i-2][j+1]=='-' || isupper(board[i-2][j+1])) && i-2>-1 && j+1<8)
                    {
                        executeInVirtBoard(COL,board,i-2,j+1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i-2][j-1]=='.' || board[i-2][j-1]=='-' || isupper(board[i-2][j-1])) && i-2>-1 && j-1>-1)
                    {
                        executeInVirtBoard(COL,board,i-2,j-1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    break;

                case 'r':
                    if(canRookP1Move(COL,board,i,j)) return 1;
                    break;

                case 'b':
                    if(canBishopP1Move(COL,board,i,j)) return 1;
                    break;

                case 'q':
                    if(canBishopP1Move(COL,board,i,j)) return 1;
                    if(canRookP1Move(COL,board,i,j)) return 1;
                    break;

                case 'k':
                    if(i+1<8 && j+1<8 && ((isalpha(board[i+1][j+1]) && isupper(board[i+1][j+1])) || board[i+1][j+1]=='.' || board[i+1][j+1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i+1,j+1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if(i-1>=0 && j-1>=0 && ((isalpha(board[i-1][j-1]) && isupper(board[i-1][j-1])) || board[i-1][j-1]=='.' || board[i-1][j-1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i-1,j-1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if(i+1<8 && j-1>=0 && ((isalpha(board[i+1][j-1]) && isupper(board[i+1][j-1])) || board[i+1][j-1]=='.' || board[i+1][j-1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i+1,j-1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if(i-1>=0 && j+1<8 && ((isalpha(board[i-1][j+1]) && isupper(board[i-1][j+1])) || board[i-1][j+1]=='.' || board[i-1][j+1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i-1,j+1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if(j+1<8 && ((isalpha(board[i][j+1]) && isupper(board[i][j+1])) || board[i][j+1]=='.' || board[i][j+1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i,j+1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if(j-1>=0 && ((isalpha(board[i][j-1]) && isupper(board[i][j-1])) || board[i][j-1]=='.' || board[i][j-1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i,j-1,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if(i+1<8 && ((isalpha(board[i+1][j]) && isupper(board[i+1][j])) || board[i+1][j]=='.' || board[i+1][j]=='-'))
                    {
                        executeInVirtBoard(COL,board,i+1,j,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    if(i-1>=0 && ((isalpha(board[i-1][j]) && isupper(board[i-1][j])) || board[i-1][j]=='.' || board[i-1][j]=='-'))
                    {
                        executeInVirtBoard(COL,board,i-1,j,i,j);
                        if(!isP1Checked(COL,virtualBoard)) return 1;
                    }
                    break;
                }
            }
            else continue;
        }
    }
    return 0;
}
void executeInVirtBoard(int col,char board[][col],int Rowfinal,int Colfinal,int Rowinit,int Colinit)
{
    equateArrays(COL,board);
    virtualBoard[Rowfinal][Colfinal]=virtualBoard[Rowinit][Colinit];
    if(abs(Rowinit-Colinit)%2==0) virtualBoard[Rowinit][Colinit]='-';
    else virtualBoard[Rowinit][Colinit]='.';
}
int canBishopP1Move(int col,char board[][col],int i,int j)
{
    int flag1=1,flag2=1,flag3=1,flag4=1,k;
    for(k=1; k<8; k++)
    {
        if(flag1 && i+k<8 && j+k<8 && (board[i+k][j+k]=='.' || board[i+k][j+k]=='-'))
        {
            executeInVirtBoard(COL,board,i+k,j+k,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
        }
        else if(flag1 && i+k<8 && j+k<8 && isalpha(board[i+k][j+k]) && isupper(board[i+k][j+k]))
        {
            executeInVirtBoard(COL,board,i+k,j+k,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
            flag1=0;
        }
        else if(flag1 && i+k<8 && j+k<8 && isalpha(board[i+k][j+k]) && islower(board[i+k][j+k])) flag1=0;
        if(flag2 && i-k>=0 && j-k>=0 && (board[i-k][j-k]=='.' || board[i-k][j-k]=='-'))
        {
            executeInVirtBoard(COL,board,i-k,j-k,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
        }
        else if(flag2 && i-k>=0 && j-k>=0 && isalpha(board[i-k][j-k]) && isupper(board[i-k][j-k]))
        {
            executeInVirtBoard(COL,board,i-k,j-k,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
            flag2=0;
        }
        else if(flag2 && i-k>=0 && j-k>=0 && isalpha(board[i-k][j-k]) && islower(board[i-k][j-k])) flag2=0;
        if(flag3 && i-k>=0 && j+k<8 && (board[i-k][j+k]=='.' || board[i-k][j+k]=='-'))
        {
            executeInVirtBoard(COL,board,i-k,j+k,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
        }
        else if(flag3 && i-k>=0 && j+k<8 && isalpha(board[i-k][j+k]) && isupper(board[i-k][j+k]))
        {
            executeInVirtBoard(COL,board,i-k,j+k,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
            flag3=0;
        }
        else if(flag3 && i-k>=0 && j+k<8 && isalpha(board[i-k][j+k]) && islower(board[i-k][j+k])) flag3=0;
        if(flag4 && i+k<8 && j-k>=0 && (board[i+k][j-k]=='.' || board[i+k][j-k]=='-'))
        {
            executeInVirtBoard(COL,board,i+k,j-k,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
        }
        else if(flag4 && i+k<8 && j-k>=0 && isalpha(board[i+k][j-k]) && isupper(board[i+k][j-k]))
        {
            executeInVirtBoard(COL,board,i+k,j-k,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
            flag4=0;
        }
        else if(flag4 && i+k<8 && j-k>=0 && isalpha(board[i+k][j-k]) && islower(board[i+k][j-k])) flag4=0;
    }
    return 0;
}
int canRookP1Move(int col,char board[][col],int i,int j)
{
    int flag1=1,flag2=1,l=0,k;
    for(k=i; k<i+7; k++)
    {
        if(flag1 && k<7 && (board[k+1][j]=='.' || board[k+1][j]=='-'))
        {
            executeInVirtBoard(COL,board,k+1,j,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
        }
        else if(flag1 && k<7 && isalpha(board[k+1][j]) && isupper(board[k+1][j]))
        {
            executeInVirtBoard(COL,board,k+1,j,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
            flag1=0;
        }
        else if(flag1 && k<7 && isalpha(board[k+1][j]) && islower(board[k+1][j])) flag1=0;
        if(flag2 && k-1-2*l>=0 && (board[k-1-2*l][j]=='.' || board[k-1-2*l][j]=='-'))
        {
            executeInVirtBoard(COL,board,k-1-2*l,j,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
        }
        else if(flag2 && k-1-2*l>=0 && isalpha(board[k-1-2*l][j]) && isupper(board[k-1-2*l][j]))
        {
            executeInVirtBoard(COL,board,k-1-2*l,j,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
            flag2=0;
        }
        else if(flag2 && k-1-2*l>=0 && isalpha(board[k-1-2*l][j]) && islower(board[k-1-2*l][j])) flag2=0;
        l++;
    }
    l=0,flag1=1,flag2=1;
    for(k=j; k<j+7; k++)
    {
        if(flag1 && k<7 && (board[i][k+1]=='.' || board[i][k+1]=='-'))
        {
            executeInVirtBoard(COL,board,i,k+1,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
        }
        else if(flag1 && k<7 && isalpha(board[i][k+1]) && isupper(board[i][k+1]))
        {
            executeInVirtBoard(COL,board,i,k+1,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
            flag1=0;
        }
        else if(flag1 && k<7 && isalpha(board[i][k+1]) && islower(board[i][k+1])) flag1=0;
        if(flag2 && k-1-2*l>=0 && (board[i][k-1-2*l]=='.' || board[i][k-1-2*l]=='-'))
        {
            executeInVirtBoard(COL,board,i,k-1-2*l,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
        }
        else if(flag2 && k-1-2*l>=0 && isalpha(board[i][k-1-2*l]) && isupper(board[i][k-1-2*l]))
        {
            executeInVirtBoard(COL,board,i,k-1-2*l,i,j);
            if(!isP1Checked(COL,virtualBoard)) return 1;
            flag2=0;
        }
        else if(flag2 && k-1-2*l>=0 && isalpha(board[i][k-1-2*l]) && islower(board[i][k-1-2*l])) flag2=0;
    }
    return 0;
}
int checkLastPlaceP2(char lastPlace)
{
    if(isalpha(lastPlace))
    {
        if(islower(lastPlace))
        {
            flagx=1;
            return 0;
        }
        else
        {
            SetColor(12);
            printf("Invalid move, enter a valid move: ");
            SetColor(15);
            return 1;
        }
    }
    else return 0;
}
int checkBishopMoveP2(int input0,int input1,int input2,int input3,char board[][COL])
{
    int j=0,i;
    if(input2>input0 && input3>input1)
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1+j][i+1]=='.' || board[input1+j][i+1]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP2(board[input3-1][input2]);
    }
    else if(input2<input0 && input3<input1)
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1-2-j][i-1-2*j]=='.' || board[input1-2-j][i-1-2*j]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP2(board[input3-1][input2]);
    }
    else if(input2>input0 && input3<input1)
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1-2-j][i+1]=='.' || board[input1-2-j][i+1]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP2(board[input3-1][input2]);
    }
    else if(input2<input0 && input3>input1)
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1+j][i-1-2*j]=='.' || board[input1+j][i-1-2*j]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP2(board[input3-1][input2]);
    }
}
int checkRookMoveP2(int input0,int input1,int input2,int input3,char board[][COL])
{
    int  j=0,i;
    if(input2>input0)
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1-1][i+1]=='.' || board[input1-1][i+1]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP2(board[input3-1][input2]);
    }
    else if(input2<input0)
    {
        for(i=input0; i<abs(input2-input0)+input0-1; i++)
        {
            if(board[input1-1][i-1-2*j]=='.' || board[input1-1][i-1-2*j]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP2(board[input3-1][input2]);
    }
    else if(input3>input1)
    {
        for(i=input1; i<input3-1; i++)
        {
            if(board[input1+j][input0]=='.' || board[input1+j][input0]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP2(board[input3-1][input2]);
    }
    else if(input3<input1)
    {
        for(i=input1; i<2*input1-input3-1; i++)
        {
            if(board[input1-2-j][input0]=='.' || board[input1-2-j][input0]=='-')
            {
                j++;
            }
            else
            {
                SetColor(12);
                printf("Invalid move, enter a valid move: ");
                SetColor(15);
                return 1;
            }
        }
        return checkLastPlaceP2(board[input3-1][input2]);
    }
}
int canRookP2Move(int col,char board[][col],int i,int j)
{
    int flag1=1,flag2=1,l=0,k;
    for(k=i; k<i+7; k++)
    {
        if(flag1 && k<7 && (board[k+1][j]=='.' || board[k+1][j]=='-'))
        {
            executeInVirtBoard(COL,board,k+1,j,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
        }
        else if(flag1 && k<7 && isalpha(board[k+1][j]) && islower(board[k+1][j]))
        {
            executeInVirtBoard(COL,board,k+1,j,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
            flag1=0;
        }
        else if(flag1 && k<7 && isalpha(board[k+1][j]) && isupper(board[k+1][j])) flag1=0;
        if(flag2 && k-1-2*l>=0 && (board[k-1-2*l][j]=='.' || board[k-1-2*l][j]=='-'))
        {
            executeInVirtBoard(COL,board,k-1-2*l,j,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
        }
        else if(flag2 && k-1-2*l>=0 && isalpha(board[k-1-2*l][j]) && islower(board[k-1-2*l][j]))
        {
            executeInVirtBoard(COL,board,k-1-2*l,j,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
            flag2=0;
        }
        else if(flag2 && k-1-2*l>=0 && isalpha(board[k-1-2*l][j]) && isupper(board[k-1-2*l][j])) flag2=0;
        l++;
    }
    l=0,flag1=1,flag2=1;
    for(k=j; k<j+7; k++)
    {
        if(flag1 && k<7 && (board[i][k+1]=='.' || board[i][k+1]=='-'))
        {
            executeInVirtBoard(COL,board,i,k+1,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
        }
        else if(flag1 && k<7 && isalpha(board[i][k+1]) && islower(board[i][k+1]))
        {
            executeInVirtBoard(COL,board,i,k+1,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
            flag1=0;
        }
        else if(flag1 && k<7 && isalpha(board[i][k+1]) && isupper(board[i][k+1])) flag1=0;
        if(flag2 && k-1-2*l>=0 && (board[i][k-1-2*l]=='.' || board[i][k-1-2*l]=='-'))
        {
            executeInVirtBoard(COL,board,i,k-1-2*l,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
        }
        else if(flag2 && k-1-2*l>=0 && isalpha(board[i][k-1-2*l]) && islower(board[i][k-1-2*l]))
        {
            executeInVirtBoard(COL,board,i,k-1-2*l,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
            flag2=0;
        }
        else if(flag2 && k-1-2*l>=0 && isalpha(board[i][k-1-2*l]) && isupper(board[i][k-1-2*l])) flag2=0;
    }
    return 0;
}
int canBishopP2Move(int col,char board[][col],int i,int j)
{
    int flag1=1,flag2=1,flag3=1,flag4=1,k;
    for(k=1; k<8; k++)
    {
        if(flag1 && i+k<8 && j+k<8 && (board[i+k][j+k]=='.' || board[i+k][j+k]=='-'))
        {
            executeInVirtBoard(COL,board,i+k,j+k,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
        }
        else if(flag1 && i+k<8 && j+k<8 && isalpha(board[i+k][j+k]) && islower(board[i+k][j+k]))
        {
            executeInVirtBoard(COL,board,i+k,j+k,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
            flag1=0;
        }
        else if(flag1 && i+k<8 && j+k<8 && isalpha(board[i+k][j+k]) && isupper(board[i+k][j+k])) flag1=0;
        if(flag2 && i-k>=0 && j-k>=0 && (board[i-k][j-k]=='.' || board[i-k][j-k]=='-'))
        {
            executeInVirtBoard(COL,board,i-k,j-k,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
        }
        else if(flag2 && i-k>=0 && j-k>=0 && isalpha(board[i-k][j-k]) && islower(board[i-k][j-k]))
        {
            executeInVirtBoard(COL,board,i-k,j-k,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
            flag2=0;
        }
        else if(flag2 && i-k>=0 && j-k>=0 && isalpha(board[i-k][j-k]) && isupper(board[i-k][j-k])) flag2=0;
        if(flag3 && i-k>=0 && j+k<8 && (board[i-k][j+k]=='.' || board[i-k][j+k]=='-'))
        {
            executeInVirtBoard(COL,board,i-k,j+k,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
        }
        else if(flag3 && i-k>=0 && j+k<8 && isalpha(board[i-k][j+k]) && islower(board[i-k][j+k]))
        {
            executeInVirtBoard(COL,board,i-k,j+k,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
            flag3=0;
        }
        else if(flag3 && i-k>=0 && j+k<8 && isalpha(board[i-k][j+k]) && isupper(board[i-k][j+k])) flag3=0;
        if(flag4 && i+k<8 && j-k>=0 && (board[i+k][j-k]=='.' || board[i+k][j-k]=='-'))
        {
            executeInVirtBoard(COL,board,i+k,j-k,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
        }
        else if(flag4 && i+k<8 && j-k>=0 && isalpha(board[i+k][j-k]) && islower(board[i+k][j-k]))
        {
            executeInVirtBoard(COL,board,i+k,j-k,i,j);
            if(!isP2Checked(COL,virtualBoard)) return 1;
            flag4=0;
        }
        else if(flag4 && i+k<8 && j-k>=0 && isalpha(board[i+k][j-k]) && isupper(board[i+k][j-k])) flag4=0;
    }
    return 0;
}
int canP2Move(int col,char board[][col])
{
    int i,j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(isalpha(board[i][j])&&isupper(board[i][j]))
            {
                switch(board[i][j])
                {
                case 'P':
                    if(board[i+1][j]=='.' || board[i+1][j]=='-')
                    {
                        executeInVirtBoard(COL,board,i+1,j,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if(i==1 && (board[i+2][j]=='.' || board[i+2][j]=='-') && (board[i+1][j]=='.' || board[i+1][j]=='-')){
                        executeInVirtBoard(COL,board,i+2,j,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((islower(board[i+1][j+1])) && i+1<8 && j+1<8)
                    {
                        executeInVirtBoard(COL,board,i+1,j+1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((islower(board[i+1][j-1])) && i+1<8 && j-1>-1)
                    {
                        executeInVirtBoard(COL,board,i+1,j-1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    break;

                case 'N':
                    if((board[i+1][j+2]=='.' || board[i+1][j+2]=='-' || islower(board[i+1][j+2])) && i+1<8 && j+2<8)
                    {
                        executeInVirtBoard(COL,board,i+1,j+2,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i+1][j-2]=='.' || board[i+1][j-2]=='-' || islower(board[i+1][j-2])) && i+1<8 && j-2>-1)
                    {
                        executeInVirtBoard(COL,board,i+1,j-2,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i-1][j+2]=='.' || board[i-1][j+2]=='-' || islower(board[i-1][j+2])) && i-1>-1 && j+2<8)
                    {
                        executeInVirtBoard(COL,board,i-1,j+2,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i-1][j-2]=='.' || board[i-1][j-2]=='-' || islower(board[i-1][j-2])) && i-1>-1 && j-2>-1)
                    {
                        executeInVirtBoard(COL,board,i-1,j-2,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i+2][j+1]=='.' || board[i+2][j+1]=='-' || islower(board[i+2][j+1])) && i+2<8 && j+1<8)
                    {
                        executeInVirtBoard(COL,board,i+2,j+1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i+2][j-1]=='.' || board[i+2][j-1]=='-' || islower(board[i+2][j-1])) && i+2<8 && j-1>-1)
                    {
                        executeInVirtBoard(COL,board,i+2,j-1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i-2][j+1]=='.' || board[i-2][j+1]=='-' || islower(board[i-2][j+1])) && i-2>-1 && j+1<8)
                    {
                        executeInVirtBoard(COL,board,i-2,j+1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if((board[i-2][j-1]=='.' || board[i-2][j-1]=='-' || isupper(board[i-2][j-1])) && i-2>-1 && j-1>-1)
                    {
                        executeInVirtBoard(COL,board,i-2,j-1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    break;

                case 'R':
                    if(canRookP2Move(COL,board,i,j)) return 1;
                    break;

                case 'B':
                    if(canBishopP2Move(COL,board,i,j)) return 1;
                    break;

                case 'Q':
                    if(canBishopP2Move(COL,board,i,j)) return 1;
                    if(canRookP2Move(COL,board,i,j)) return 1;
                    break;

                case 'K':
                    if(i+1<8 && j+1<8 && ((isalpha(board[i+1][j+1]) && islower(board[i+1][j+1])) || board[i+1][j+1]=='.' || board[i+1][j+1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i+1,j+1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if(i-1>=0 && j-1>=0 && ((isalpha(board[i-1][j-1]) && islower(board[i-1][j-1])) || board[i-1][j-1]=='.' || board[i-1][j-1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i-1,j-1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if(i+1<8 && j-1>=0 && ((isalpha(board[i+1][j-1]) && islower(board[i+1][j-1])) || board[i+1][j-1]=='.' || board[i+1][j-1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i+1,j-1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if(i-1>=0 && j+1<8 && ((isalpha(board[i-1][j+1]) && islower(board[i-1][j+1])) || board[i-1][j+1]=='.' || board[i-1][j+1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i-1,j+1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if(j+1<8 && ((isalpha(board[i][j+1]) && islower(board[i][j+1])) || board[i][j+1]=='.' || board[i][j+1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i,j+1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if(j-1>=0 && ((isalpha(board[i][j-1]) && islower(board[i][j-1])) || board[i][j-1]=='.' || board[i][j-1]=='-'))
                    {
                        executeInVirtBoard(COL,board,i,j-1,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if(i+1<8 && ((isalpha(board[i+1][j]) && islower(board[i+1][j])) || board[i+1][j]=='.' || board[i+1][j]=='-'))
                    {
                        executeInVirtBoard(COL,board,i+1,j,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    if(i-1>=0 && ((isalpha(board[i-1][j]) && islower(board[i-1][j])) || board[i-1][j]=='.' || board[i-1][j]=='-'))
                    {
                        executeInVirtBoard(COL,board,i-1,j,i,j);
                        if(!isP2Checked(COL,virtualBoard)) return 1;
                    }
                    break;
                }
            }
            else continue;
        }
    }
    return 0;
}
int isP2Checked(int col,char board[][col])
{
    int i,j,k,l,flag1,flag2,flag3,flag4;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            flag1=1,flag2=1,flag3=1,flag4=1,l=0;
            if(isalpha(board[i][j])&&islower(board[i][j]))
            {
                switch(board[i][j])
                {
                case 'p':
                    if(board[i-1][j+1]=='K' || board[i-1][j-1]=='K') return 1;
                    break;

                case 'n':
                    if(board[i+1][j+2]=='K' || board[i+1][j-2]=='K' || board[i-1][j+2]=='K' || board[i-1][j-2]=='K') return 1;
                    if(board[i+2][j+1]=='K' || board[i+2][j-1]=='K' || board[i-2][j+1]=='K' || board[i-2][j-1]=='K') return 1;
                    break;

                case 'r':
                    for(k=i; k<i+7; k++)
                    {
                        if(flag1 && k<7 && board[k+1][j]=='K') return 1;
                        else if(isalpha(board[k+1][j])) flag1=0;
                        if(flag2 && k-1-2*l>=0 && board[k-1-2*l][j]=='K') return 1;
                        else if(isalpha(board[k-1-2*l][j])) flag2=0;
                        l++;
                    }
                    l=0,flag1=1,flag2=1;
                    for(k=j; k<j+7; k++)
                    {
                        if(flag1 && k<7 && board[i][k+1]=='K') return 1;
                        else if(isalpha(board[i][k+1])) flag1=0;
                        if(flag2 && k-1-2*l>=0 && board[i][k-1-2*l]=='K') return 1;
                        else if(isalpha(board[i][k-1-2*l])) flag2=0;
                        l++;
                    }
                    break;

                case 'b':
                    for(k=1; k<8; k++)
                    {
                        if(flag1 && i+k<8 && j+k<8 && board[i+k][j+k]=='K') return 1;
                        else if(isalpha(board[i+k][j+k])) flag1=0;
                        if(flag2 && i-k>=0 && j-k>=0 && board[i-k][j-k]=='K') return 1;
                        else if(isalpha(board[i-k][j-k])) flag2=0;
                        if(flag3 && i-k>=0 && j+k<8 && board[i-k][j+k]=='K') return 1;
                        else if(isalpha(board[i-k][j+k])) flag3=0;
                        if(flag4 && i+k<8 && j-k>=0 && board[i+k][j-k]=='K') return 1;
                        else if(isalpha(board[i+k][j-k])) flag4=0;
                    }
                    break;

                case 'q':
                    for(k=1; k<8; k++)
                    {
                        if(flag1 && i+k<8 && j+k<8 && board[i+k][j+k]=='K') return 1;
                        else if(isalpha(board[i+k][j+k])) flag1=0;
                        if(flag2 && i-k>=0 && j-k>=0 && board[i-k][j-k]=='K') return 1;
                        else if(isalpha(board[i-k][j-k])) flag2=0;
                        if(flag3 && i-k>=0 && j+k<8 && board[i-k][j+k]=='K') return 1;
                        else if(isalpha(board[i-k][j+k])) flag3=0;
                        if(flag4 && i+k<8 && j-k>=0 && board[i+k][j-k]=='K') return 1;
                        else if(isalpha(board[i+k][j-k])) flag4=0;
                    }
                    flag1=1,flag2=1;
                    for(k=i; k<i+7; k++)
                    {
                        if(flag1 && k<7 && board[k+1][j]=='K') return 1;
                        else if(isalpha(board[k+1][j])) flag1=0;
                        if(flag2 && k-1-2*l>=0 && board[k-1-2*l][j]=='K') return 1;
                        else if(isalpha(board[k-1-2*l][j])) flag2=0;
                        l++;
                    }
                    l=0,flag1=1,flag2=1;
                    for(k=j; k<j+7; k++)
                    {
                        if(flag1 && k<7 && board[i][k+1]=='K') return 1;
                        else if(isalpha(board[i][k+1])) flag1=0;
                        if(flag2 && k-1-2*l>=0 && board[i][k-1-2*l]=='K') return 1;
                        else if(isalpha(board[i][k-1-2*l])) flag2=0;
                        l++;
                    }
                case 'k': if(board[i][j+1]=='K' || board[i][j-1]=='K' || board[i+1][j]=='K' || board[i-1][j]=='K' || board[i+1][j+1]=='K' || board[i-1][j-1]=='K' || board[i+1][j-1]=='K' || board[i-1][j+1]=='K') return 1;
                default:
                    continue;
                }
            }
            else continue;
        }
    }
    return 0;
}
void saveMoves(int input1,int input2,int input3,int input4,char promotion)
{//6 cols : 4 for the move, 1 for removed pieces and 1 for promotion
    moves[pointer][0]=input1+'0';
    moves[pointer][1]=input2+'0';
    moves[pointer][2]=input3+'0';
    moves[pointer][3]=input4+'0';
    if(flagx) moves[pointer][4]=removedPieces[indexRP-1];
    else moves[pointer][4]='0';
    moves[pointer][5]=promotion;
    pointer++;
    maxMoves++;
}
