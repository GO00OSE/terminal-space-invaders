#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char empty[]   = "\x1b[0m[ ]";
char filled[]  = "\x1b[0;33m[#]";
char player[]  = "\x1b[0;34m[^]";
char enemy[]   = "\x1b[0;31m[Y]";
char bullet1[] = "\x1b[0m[\x1b[0;32m,\x1b[0m]";
char bullet2[] = "\x1b[0m[\x1b[0;32m'\x1b[0m]";

int playerPos[2] = {5,9};

int GAMEWIDTH  = 10;
int GAMEHEIGHT = 10;

// empty 0
// Block 1 
// Player 2
// Enemies 3
// Bullet 4,5
// Enemy bullet 6,7

int gameboard[10][10] = {
  {0,0,0,0,0,0,0,0,0,0}, 
  {0,0,0,0,0,0,1,1,0,0},
  {0,0,0,0,0,0,1,1,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,3,0,0,0,0,1,1,0,0},
  {0,3,0,0,0,0,1,1,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,1,1,0,0},
  {0,0,0,0,0,0,1,1,0,0},
  {0,0,0,0,0,0,0,0,0,0}
};

int alive = 1;

void shoot(){
  gameboard[playerPos[0]][playerPos[1] - 1] = 4;
}

void drawBoard(int board[10][10]){
  for (int y = 0; y < GAMEHEIGHT; y++){ 
    for (int x = 0; x < GAMEWIDTH; x++){
      if (board[x][y] == 1){
        printf("%s", filled);
      } else if (board[x][y] == 2) {
        printf("%s", player);
      } else if (board[x][y] == 3) {
        printf("%s", enemy); 
      } else if (board[x][y] == 4 || board[x][y] == 7) {
        printf("%s", bullet1);
      } else if (board[x][y] == 5 || board[x][y] == 6){
        printf("%s", bullet2);
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
  printf("\x1b[?25l"); // Hide cursor
  
  clock_t lastTime = clock();
  double timeTaken;
  int tick = 0;

  while(alive){
    if(20*(clock() - lastTime)/CLOCKS_PER_SEC > 2){
      lastTime = clock();
      tick++;

      for (int y = 0; y < GAMEHEIGHT; y++){
        for (int x = 0; x < GAMEWIDTH; x++){
          if(gameboard[x][y] == 4){
            gameboard[x][y] = 5;
          } else if (gameboard[x][y] == 5){
            gameboard[x][y] = 0;
            if (y != 0){
              if (gameboard[x][y-1] != 0){
                gameboard[x][y-1] = 0;
              } else {
                gameboard[x][y-1] = 4;
              }
            } 
          } else if(gameboard[x][y] == 6){
            gameboard[x][y] = 7;
          } else if (gameboard[x][y] == 7){
            gameboard[x][y] = 0;
            if (y != 9){
              if (gameboard[x][y+1] != 0){
                gameboard[x][y+1] = 0;
              } else if(x == playerPos[0] && y + 1 == playerPos[1]){
                alive = 0;
              } else {
                gameboard[x][y+1] = 6;
              }
            } 
          } else if(gameboard[x][y] == 3){
            int r = rand() % 50; //random number between 0 and 49
            if (tick % 4 == 0){ //has a 1 in 50 chance to shoot
              gameboard[x][y+1] = 6; 
            }
          }
        }
      }
    }
    int curBoard[10][10];
    memcpy(curBoard, gameboard, sizeof(curBoard));

    if(_kbhit()){
      ch = _getch();

      if (ch == 'a' && playerPos[0] > 0){
        playerPos[0] -= 1;
      } else if (ch == 'w') {
        if (gameboard[playerPos[0]][playerPos[1] - 1] != 5 && gameboard[playerPos[0]][playerPos[1] - 1] != 4)
          shoot();
      } else if (ch == 'd' && playerPos[0] < 9) {
        playerPos[0] += 1;
      } else if (ch == 'q'){
        break;
      }
    }

    curBoard[playerPos[0]][playerPos[1]] = 2;
    drawBoard(curBoard);
    printf("\x1b[u");
  }
  
  for(int y = 0; y <= GAMEHEIGHT; y++){
    printf("\x1b[1E"); // Move to beginning of previous line
  }
  for(int y = 0; y <= GAMEHEIGHT; y++){
    printf("\x1b[1F"); // Move to beginning of previous line
    printf("\x1b[2K"); // Clear entire line
  } 
  printf("\x1b[?25h"); //Set cursor visable
  printf("\x1b[5m\x1b[1;31m[GAMEOVER]\x1b[25m\n\x1b[1;32mScore: %d \x1b[1;37m \n", 0);
  return 0;
}
