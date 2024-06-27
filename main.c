#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char empty[] = "\x1b[0m[ ]";
char filled[] = "\x1b[0;33m[*]";
char player[] = "\x1b[0;34m[^]";

int playerPos[2] = {5,9};

int GAMEWIDTH = 10;
int GAMEHEIGHT = 10;

// Block 1 
// Player 2
// Enemie 3

int gameboard[10][10] = {
  {0,0,0,0,0,0,0,0,0,0}, 
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0}
};

int alive = 1;

void drawBoard(int board[10][10]){
  for (int y = 0; y < GAMEHEIGHT; y++){ 
    for (int x = 0; x < GAMEWIDTH; x++){
      if (board[x][y] == 1){
        printf("%s", filled);
      } else if (board[x][y] == 2) {
        printf("%s", player);
      } else {
        printf("%s", empty);
      }
    }
    printf("\n");
  }
}

int main(){  
  char ch;
  printf("\x1b[s");
  while(alive){
    int curBoard[10][10];
    memcpy(curBoard, gameboard, sizeof(curBoard));

    if(_kbhit()){
      ch = _getch();

      if (ch == 'a' && playerPos[0] > 0){
        playerPos[0] -= 1;
      } else if (ch == 'd' && playerPos[0] < 9) {
        playerPos[0] += 1;
      }
    }

    curBoard[playerPos[0]][playerPos[1]] = 2;
    drawBoard(curBoard);
    printf("\x1b[u");
  }

  return 0;
}
