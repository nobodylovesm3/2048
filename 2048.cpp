#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;

const int WIDTH = 4,
          HEIGHT = 4;
const char UP = 'w',
          DOWN = 's',
          LEFT = 'a',
          RIGHT = 'd';

void moveToRight(int board[HEIGHT][WIDTH]) {
    for (int row = 0; row < HEIGHT; row++) {
        int newCellColumn = WIDTH - 1;

        for (int col = WIDTH - 1; col >= 0; col--) {
            if (board[row][col] != 0) {
                board[row][newCellColumn] = board[row][col];

                if (col != newCellColumn) {
                    board[row][col] = 0;
                }

                newCellColumn--;
            }
        }
    }
}

void mergeToRight(int board[HEIGHT][WIDTH]) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = WIDTH - 1; col > 0; col--) {
            if (board[row][col] == board[row][col - 1]) {
                board[row][col] += board[row][col - 1];
                board[row][col - 1] = 0;
            }
        }
    }
}

void copyBoard(int to[HEIGHT][WIDTH], int from[HEIGHT][WIDTH]) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            to[row][col] = from[row][col];
        }
    }
}

void rotateRight(int board[HEIGHT][WIDTH]) {
    int rotated[HEIGHT][WIDTH] = {0};

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            rotated[col][WIDTH - row - 1] = board[row][col];
        }
    }

    copyBoard(board, rotated);
}

void spawnNewNumber(int board[HEIGHT][WIDTH]) {
    int emptyCellsCounter = 0;

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (board[row][col] == 0) {
                emptyCellsCounter++;
            }
        }
    }

    if (emptyCellsCounter == 0) {
        return;
    }

    int randomNumberSpawnIndex = rand() % 4;

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (board[row][col] == 0 && randomNumberSpawnIndex == 0) {
                board[row][col] = 2;
            }

            randomNumberSpawnIndex--;
        }
    }
}

void makeMoveToRight(int board[HEIGHT][WIDTH]) {
    moveToRight(board);
    mergeToRight(board);
    moveToRight(board);
    spawnNewNumber(board);
}

void makeMove(int board[HEIGHT][WIDTH], char direction) {
    if (direction == UP) {
        rotateRight(board);
        makeMoveToRight(board);
        rotateRight(board);
        rotateRight(board);
        rotateRight(board);
    } else if (direction == LEFT) {
        rotateRight(board);
        rotateRight(board);
        makeMoveToRight(board);
        rotateRight(board);
        rotateRight(board);
    } else if (direction == RIGHT) {
        makeMoveToRight(board);
    } else {
        rotateRight(board);
        rotateRight(board);
        rotateRight(board);
        makeMoveToRight(board);
        rotateRight(board);
    }
}

bool canMove(int board[HEIGHT][WIDTH]) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if ((col > 0 && board[row][col] == board[row][col - 1]) || (col > 0 && board[row][col] == board[row][col+1])) {
                return true;
            }

            if ((row > 0 && board[row][col] == board[row - 1][col]) || (row > 0 && board[row][col] == board[row + 1][col])) {
                return true;
            }

        }
    }

    return false;
}

bool isCompleted(int board[HEIGHT][WIDTH]) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (board[row][col] == 2048) {
                return true;
            }
        }
    }

    return false;
}


void printBorder(){
  cout << "~!~";
  for (int amountOfDashes = 0; amountOfDashes < WIDTH; amountOfDashes++){
    for (int amountOfDashesByColumns = -1;amountOfDashesByColumns < WIDTH; amountOfDashesByColumns++){
      cout << '-';
    }

    if (amountOfDashes != 0){
      cout << '-';
    }
  }
  cout << "~!~" << endl;
}

void createEmptyBoard(int newBoard[HEIGHT][WIDTH]){
  int board[HEIGHT][WIDTH] = {
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    };

    newBoard = board;
}

void populateBoardForTheFirstTime(int board[HEIGHT][WIDTH]){
  int randomRowIndex,
      randomColIndex;

  do {
    randomRowIndex = rand() % HEIGHT;
    randomColIndex = rand() % WIDTH;

  } while (board[randomRowIndex][randomColIndex] != 0);

      board[randomRowIndex][randomColIndex] = 2;
}


void printBoard(int board[HEIGHT][WIDTH]) {
    printBorder();
    for (int row = 0; row < HEIGHT; row++) {
        cout << '|';
        for (int col = 0; col < WIDTH; col++) {
            cout << ' ' << setw(WIDTH - 1);
            cout << board[row][col] << setw(2) << '|';
        }

        cout << "\n";
    }

    printBorder();
}

char toLowerCase(char directionSymbol){
  if (directionSymbol >= 'A' && directionSymbol <= 'Z'){
    return (char) (directionSymbol + 32);
  }
  return directionSymbol;
}

bool isPopulated(int board[HEIGHT][WIDTH]){
  int counterOfTwos = 0;

  for (int row = 0; row < HEIGHT; row++) {
      for (int col = 0; col < WIDTH; col++) {
          if (board[row][col] == 2){
            counterOfTwos++;
          }
          if (counterOfTwos == 2){
            return true;
          }
      }
    }
    return false;
  }

  void printMessage(){
    cout << " Choose a direction:\n 'w' -> up;\n 'a' -> left;\n 'd' -> right;\n 's' -> down.\n Decision: ";
  }


  //create hasEmptyNumbers -> add check for empty cells -> move in all directions!
  // int board[HEIGHT][WIDTH] = {
  //   {4,2,4,2},
  //   {0,4,2,4},
  //   {8,2,4,2},
  //   {0,4,2,4},
  //  };


int main() {
    srand( time(NULL));

    int board[HEIGHT][WIDTH] = { 0 };

    while (!isPopulated(board)){
      populateBoardForTheFirstTime(board);
    }


    printBoard(board);
    cout << "\n";

    while (canMove(board) && !isCompleted(board)) {
        char direction;
        printMessage();
        cin >> direction;
        direction = toLowerCase(direction);

        makeMove(board, direction);
        printBoard(board);
    }

    if (isCompleted(board)) {
        cout << "You win!\n";
    } else if (!canMove(board)) {
        cout << "You lose!\n";
    }

    return 0;
}
