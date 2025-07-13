// Kashan Ahmad this game allows you to play reversi
//

#include "liblab8part2.h"
#include "lab8part2.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);
void createBoard(int n, char board[][26]);
void takeInput(char board[][26]);
void flipTiles(char board[][26], int n);
void checkValidAndFlip(char board[][26], int n, char whiteMoves [n*n][2], char blackMoves [n*n][2], int WMoves, int BMoves, bool flip); // add a bool flip
int search(char board[][26], int n,
           char colour, char colourMoves [n*n][2]);  
                          // but made into int to return amount of moves
char computerColour();
char oppositeColour(char compColour);
char oppositeTurn(char turn);
void game (char board[][26], int n, char computerColour, char userColour);
char Winner(int user, int computer);
int findWinner(char board[][26],int n, char colour);
bool fullBoard (char board[][26], int n);
int makeMove(const char board[][26], int n, char turn, int *row, int *col);

int main(void) {
  // take in user input for length of the array
  int n;
  printf("Enter the board dimension: ");
  scanf("%d", &n);
  char compColour, userColour;
  compColour = computerColour();
  userColour = oppositeColour(compColour);
  char board[n][26];
  createBoard(n, board);
  //printBoard(board, n);
  game (board, n, compColour, userColour);
  return 0;
}
void printBoard(char board[][26], int n) {
  // print the abcd
  char letter = 'a';
  printf("  ");
  for (int i = 0; i < n; i++) {
    printf("%c", letter + i);
  }
  printf("\n");
  // print array with letter columbs
  for (int row = 0; row < n; row++) {
    printf("%c ", letter + row);
    for (int col = 0; col < n; col++) {
      printf("%c", board[row][col]);
    }
    printf("\n");
  }
  // printf("\n")
}
void createBoard(int n, char board[][26]) {
  int colour = 0;
  int count = 0;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if ((n / 2 - 1 == row && n / 2 - 1 == col) ||
          (n / 2 == row && n / 2 == col) ||
          (n / 2 - 1 == row && n / 2 == col) ||
          (n / 2 == row && n / 2 - 1 == col)) {
        if (colour == 0) {
          board[row][col] = 'W';
          colour++;
        } else {
          board[row][col] = 'B';
          count++;
          if (count == 2) colour--;
        }
      } else
        board[row][col] = 'U';
    }
  }
}
void takeInput(char board[][26]) {
  char colour;
  char userRow;
  char userCol;
  bool stop = false;
  printf("Enter board configuration: \n");
  while (stop == false) {
    scanf(" %c%c%c", &colour, &userRow,
          &userCol);  // added a space in front of the first %c to ignore white
                      // space
    if (colour == '!' && userRow == '!' && userCol == '!')
      stop = true;
    else {
      int row = userRow - 'a';
      int col = userCol - 'a';
      board[row][col] = colour;
    }
  }
}

// part 3
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  // deltaRow is the row direction, 1 means going down, and -1 means going up
  // deltaCol is the col direction, 1 means going right, and -1 means going left
  char checkColour;
  if (colour == 'W')
    checkColour = 'B';
  else
    checkColour = 'W';
bool found = false;
if (positionInBounds(n,row+deltaRow,col+deltaCol)==true && board[row][col] == 'U' && board[row+deltaRow][col+deltaCol]==checkColour){
    row = row + 2*deltaRow;
    col = col + 2*deltaCol;
bool search = true;
//int count = 3;
  while ((positionInBounds(n,row,col)==true && found == false && search==true)&&(board[row][col] == 'U' || board[row][col] == colour || board[row][col]==checkColour)){
  if (board[row][col] == colour){
    found = true;
      return found;
          } else if (board[row][col] == 'U') {  // changed colour to U
            // not valid
            search = false;
         } else if ((row == 0 || row < n|| col<n|| col == 0) && board[row][col] == colour) {
            search = false;
          }

    row = row + deltaRow;
    col = col + deltaCol;
    //row = row + count*deltaRow;
    //col = col + count*deltaCol;
    //count++;
  }
}
return found;
                           }
int search(char board[][26], int n, char colour, char colourMoves[n*n][2]) {
//okay im really close, just have extra moves, trying fixing the conditions
 int count = 0;
 bool found = false;
  for (int row = 0; row<n; row++){
    found = false;
    for (int col = 0; col<n; col++){
      found = false;
      for (int deltaRow = -1; deltaRow<=1 && found == false; deltaRow++){
        for (int deltaCol = -1; deltaCol<=1 && found == false; deltaCol++){
          if ( (deltaRow!=0||deltaCol!=0) && positionInBounds(n, row+deltaRow, col + deltaCol) == true && (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) == true)){
            char RowCoordinate = (char)('a' + (row));  // got rid of -subRow
            char ColCoordinate = (char)('a' + col);    // got rif of +addCol
            colourMoves [count][0] = RowCoordinate;
            colourMoves [count][1] = ColCoordinate;
           // printf("%c%c\n", RowCoordinate, ColCoordinate);
            count++;
            found = true;
        }
      }
    }
  }
}
return count;
}

//check if coordinates within bound
bool positionInBounds(int n, int row, int col) {
  if (row >= 0 && row < n && col >= 0 && col < n)
    return true;
  else
    return false;
}

int checkValidAndFlipComp(char board[][26], int n, char compRow, char compCol, char colour, bool flip, int moves){
  bool valid = true;
  int row;
  int col;
int score = 0;
row = compRow - 'a';
col = compCol - 'a';

       bool exit = false;
        for (int deltaRow = -1; deltaRow<=1 && valid == true; deltaRow++){
          exit = false;
        int validCount = 0;
          for (int deltaCol = -1; deltaCol<=1; deltaCol++){
            exit = false; //i addded this, check if it works
                      validCount = 0;
           if (positionInBounds(n, row+deltaRow, col + deltaCol) == true && (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) == true) && (deltaRow!=0||deltaCol!=0)){
            int countPlaces = 0;
              for (int move=2; exit == false; move++){
                int moveRow = row + move*deltaRow;
                int moveCol = col + move*deltaCol;
                countPlaces ++;
                if (positionInBounds(n, moveRow, moveCol) == false|| board[moveRow][moveCol] == 'U' || board[moveRow][moveCol] == colour){
                    if (board[moveRow][moveCol] == colour){
                      validCount = countPlaces;
                    }                  
                    exit = true;
                }
              }
           }

           if (validCount !=0 && flip == true){
            for (int moveTotal = 1; moveTotal<=validCount; moveTotal++){
             // for (int moveC = 0; moveC <= validCount; moveC++){
                board[row + moveTotal*deltaRow][col + moveTotal*deltaCol] = colour;
              //}
            }
           }
           else {
            score = score+validCount;
           }
          }
        }
if (flip==true)
    board[row][col] = colour;

return score;
 
                      }

int makeMove(const char board[][26], int n, char turn, int *row, int *col){ 
    char compMoves[n*n][2];
    char oppMoves[n*n][2];
    int compmoves;
  //  bool minMoves = false;
    char boardCopy[n][26];
    int oppscores[n*n];
    int oppMaxScore;
    int oppPieces;
    //copy main board into board copy
    for (int i = 0; i<n; i++){
      for (int j = 0; j<n;j++){
        boardCopy[i][j] = board[i][j];
      }
    }
        compmoves = search(board, n, turn,compMoves); //this finds the total current moves for computer
        if (compmoves>0){ //if a move is avalaible
            int scores[compmoves]; //storing scores
 //           int max = 0;
  //          int maxIndex = 0;

            for (int i = 0; i<compmoves; i++){ //puts all the scores in index
                scores[i] = checkValidAndFlipComp(board, n, compMoves[i][0], compMoves[i][1], turn, false, compmoves);
 
            //if avaliable move in corners, take it
            if (((int)compMoves[i][0]-'a'==0||(int)compMoves[i][0]-'a'==n-1)&&(compMoves[i][1]-'a'==0||compMoves[i][1]-'a'==n-1)){
            *row = (int)(compMoves[i][0] - 'a');
            *col =(int) (compMoves[i][1] - 'a'); 
            return 0;
              }
            }
            //what to do no that we have stored the maxScores for the computer to move.......
            int oppmoves = 0;
            oppMaxScore = 0;
            int oppMovesBefore = 0;
            int oppPlaces[compmoves];
            bool minMoves = false;
            int oppMinMoves; 
            char oppositeCol = oppositeColour(turn);
            for (int i = 0; i<compmoves; i++){ //for everysingle computer move, itterate to find result of move

                oppMovesBefore = search(board,n,oppositeCol,oppMoves); //oppsite moves before switch
                checkValidAndFlipComp(boardCopy, n, compMoves[i][0], compMoves[i][1], turn, true, compmoves);//update copy of board 
                oppmoves = search(boardCopy,n,oppositeCol,oppMoves); //opposite moves after switch//if oppmoves equal to 0, then just take first occurance of highest value
                if (oppmoves>0){
                  for (int row1 = 0; row1<oppmoves; row1++){
               oppscores[row1] = checkValidAndFlipComp(boardCopy, n, oppMoves[row1][0], oppMoves[row1][1], oppositeCol, false, oppmoves);
                  } 
                oppMaxScore = oppscores[0];
                oppMinMoves = oppscores[0];
                for (int row2 = 0; row2<oppmoves; row2++){ //find max score and fill storearray with 0's
                if (oppscores[row2]>oppMaxScore){
                    oppMaxScore = oppscores[row2];
                }
            }       
                }
                oppPlaces[i] = scores[i] - (oppmoves-oppMovesBefore);
                scores[i] = scores[i] - oppMaxScore;
                for (int row3 = 0; row3<n; row3++){
                  for (int col2 = 0; col2<n; col2++){
                    boardCopy [row3][col2] = board[row3][col2]; //reset board copy for reuse
                  }
                }
            }
                oppPieces = findWinner(board,n,oppositeCol); //finds how many opposite colour there are
                if (oppPieces<(n*n)/9){ //if less than one eighth of the board is opposite colour, go easy 
                  minMoves = true;
                }
            //now we want to compare the 2 storing arrays and see which one has lowest value if going easy
          if (minMoves==true){
              for (int i = 0; i<compmoves;i++){
             if (oppPlaces[i]<scores[i]){
               scores[i] = oppPlaces[i];
             }
            }
            }
            //if going hard, find highest values
          else{
           for (int i = 0; i<compmoves;i++){
             if (oppPlaces[i]>scores[i]){
               scores[i] = oppPlaces[i];
                }
              } //now we want to find the highest value in the array
            }

           int updateMax = scores[0]; //intialize updateMax 
           int updateMaxIndex = 0;
           if (minMoves == true){ //if going easy
              for (int i = 0; i<compmoves; i++){
              if (scores[i]<updateMax){ //replaced score[i]
                updateMax = scores[i];//scores[i];
                updateMaxIndex = i;
              }
            }
              minMoves = false; //set it to false
           }
           else {
            for (int i = 0; i<compmoves; i++){
              if (scores[i]>updateMax){ //find best move with smallest "hit"
                updateMax = scores[i];
                updateMaxIndex = i;
              }
            }
           }
            *row = (int)(compMoves[updateMaxIndex][0] - 'a'); //store the row
            *col =(int) (compMoves[updateMaxIndex][1] - 'a'); //store the col
        }
        else {
          return -1;
        }
return 0;
}
char computerColour(){
    char computerColour;
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);
    return computerColour;
}
char oppositeColour(char compColour){
    char userColour;
    if (compColour=='W'){
        userColour = 'B';
    }
    else{
    userColour = 'W';
    }
return userColour;
}
char oppositeTurn(char turn){
    if (turn=='W')
    return 'B';
    else
        return 'W';
}

void game (char board[][26], int n, char computerColour, char userColour){
    char turn = 'B'; 
    bool win = false;
    bool validMove = true;
    char userMoves[n*n][2];
    char compMoves[n*n][2];
    int compmoves;
    int usermoves;
    char userRow;
    char userCol;
    bool userNoMove = false;
    bool compNoMove = false;
    int row = 0;
    int col = 0;
    int AIrow = 0;
    int AIcol = 0;
    printBoard(board,n);
    while (win == false && validMove == true){
    if (turn == userColour){
        usermoves = search(board, n, turn,userMoves);
        bool tempValidMove = false;
        if (usermoves > 0){
       // printf("Enter move for colour %c (RowCol): ", userColour); 
       // scanf(" %c%c", &userRow, &userCol);
       //replace smarter with smartest
       findSmarterMove(board, n, userColour, &AIrow, &AIcol);
       userRow = (char)(AIrow+'a');
       userCol = (char)(AIcol+'a');
       printf("Testing AI move (row, col): %c%c\n", userRow, userCol);
          userNoMove = false;
          for (int i = 0; i<usermoves && tempValidMove == false; i++){
              if (userMoves[i][0] == userRow && userMoves[i][1] == userCol){
                tempValidMove = true;
                checkValidAndFlipComp(board, n, userRow, userCol, userColour, true, usermoves);
                //printBoard(board,n);
              }
          }
          if (tempValidMove == false){
            validMove = false;
            userNoMove=true;
            printf("Invalid move. \n");
            printf("%c player wins.", computerColour);
          }
        }
        else{
          printf("%c player has no valid move. \n", userColour);
          userNoMove = true;
        }
        if (userNoMove == false){
         printBoard(board, n);
        }
    }
    else { // computers turn to make a move
        int check = makeMove(board,n,computerColour, &row, &col);
        if (check!=-1){
          compmoves = search(board,n,computerColour, compMoves);
          char UpdateRow = (char)('a' + row);
          char UpdateCol = (char)('a' + col);
          checkValidAndFlipComp(board, n, UpdateRow, UpdateCol, computerColour, true, compmoves);
            printf("Computer places %c at %c%c. \n", computerColour, UpdateRow, UpdateCol);
        }
        
        else {
          printf("%c player has no valid move. \n", computerColour);
          compNoMove = true;
        }
        if (compNoMove == false){
          printBoard(board, n);
        }
    }
            turn = oppositeTurn(turn);
    if (fullBoard(board,n) == true){
      win = true;
    }
    if ((userNoMove == true && compNoMove == true) || win == true){//board is full
      win = true;
        int userPieces = findWinner(board, n, userColour);
        int compPieces = findWinner(board, n, computerColour);  
        if (userPieces > compPieces){
          //printBoard(board,n);
          printf("%c player wins.",userColour);
      }
        else if (compPieces > userPieces){
          //printBoard(board,n);
          printf("%c player wins.",computerColour);
        }
      else{
        //printBoard(board,n);
        printf("Draw!");
      }
      }
    }
}

int findWinner(char board[][26],int n, char colour ){
  int pieces = 0;
  for (int i = 0; i<n; i++){
    for (int j = 0; j<n; j++){
      if (board[i][j] == colour){
        pieces++;
      }
    }
  }
  return pieces;
}

bool fullBoard (char board[][26], int n){
  bool boardfull = true;
  for (int i = 0; i<n && boardfull == true; i++){
    for (int j = 0; j<n && boardfull == true; j++){
      if (board[i][j] == 'U'){
        boardfull = false;
      }
    }
  }
  return boardfull;
}
