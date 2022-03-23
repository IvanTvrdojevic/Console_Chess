#include <iostream>
#include <string>
#include "conio.h"

//*****************************************************************************
// CLASES
// Abstract class
class Field{
private:

public:
  virtual char getSquare() = 0;
  virtual bool checkMove(Field* (&chessField)[8][8], int x, int y) = 0;
  virtual char getSide() = 0;
};

// Squares with no figures
class EmptySquare : public Field{
private:
  char square = ' ';

public:
  char getSquare(){
    return square;
  }
  bool checkMove(Field* (&chessField)[8][8], int x, int y){return true;}
  char getSide(){
    return 'N';
  }
};

// Pawn class
class Pawn : public Field{
private:
  int positionX = 0;
  int positionY = 0;
  char square = ' ';
  char side = ' ';
  bool firstMove = true;
  bool eaten = false;

public:
  Pawn(int x, int y, char side, char square) :
    positionX(x),
    positionY(y),
    side(side),
    square(square)
  {

  }

  char getSquare(){
    return square;
  }

  char getSide(){
    return side;
  }

  bool checkMove(Field* (&chessField)[8][8], int x, int y){
    // Check which color is making a move, according to it validate the move
    if(chessField[positionX][positionY]->getSide() == 'w' && x >= positionX) return false;
    else if(chessField[positionX][positionY]->getSide() == 'b' && x <= positionX) return false;

    //On the first move of a pawn it can go 2 squares up
      if(firstMove){
        // Check that if pawn is going 2 places up it is not jumping over a piece
        // This check is for white side
        if(chessField[positionX][positionY]->getSide() == 'w' &&
          abs(positionX - x) == 2 &&
          chessField[x + 1][positionY]->getSquare() != ' ') return false;

        // This check is for black side
        if(chessField[positionX][positionY]->getSide() == 'b' &&
            abs(positionX - x) == 2 &&
            chessField[x - 1][positionY]->getSquare() != ' ') return false;

        // Check if first move is valid if it is set firstMove is set to false
        // This check is for white side
        if(abs(positionX - x) < 3 && positionY == y && chessField[x][y]->getSquare() == ' '){
          positionX = x;
          firstMove = false;
          return true;
        }
        // This check is for black side
        else if(abs(positionX - x) == 1 && abs(positionY - y) == 1){
          if(chessField[x][y]->getSquare() == ' ') return false;
          positionX = x;
          firstMove = false;
          return true;
        }
        return false;
      }

      // if its not its first move a pawn can only move up one square
      if(abs(positionX - x) == 1 && positionY == y && chessField[x][y]->getSquare() == ' '){
        positionX = x;
        return true;
      }
      // Pawn can move 1 square diagonally (forwards) but only if it can eat a piece
      else if(abs(positionX - x) == 1 && abs(positionY - y) == 1){
        if(chessField[x][y]->getSquare() == ' ') return false;
        positionX = x;
        positionY = y;
        firstMove = false;
        return true;
      }
      return false;
    }
};

class Rook : public Field{
private:
  int positionX = 0;
  int positionY = 0;
  char square = ' ';
  char side = ' ';
  bool firstMove = true;
  bool eaten = false;

public:
  Rook(int x, int y, char side, char square) :
    positionX(x),
    positionY(y),
    side(side),
    square(square)
  {

  }

  char getSquare(){
    return square;
  }

  char getSide(){
    return side;
  }

  bool validateMove(Field* (&chessField)[8][8], int x, int y){
    if(positionX != x && positionY != y) return false;
    // Moving on x axis, y is fixed
    if(positionX != x){
      if(positionX > x){
        for(int i = positionX - 1; i > x; i--){
          if(chessField[i][y]->getSquare() != ' ') return false;
        }
      }

      if(positionX < x){
        for(int i = positionX + 1; i < x; i++){
          if(chessField[i][y]->getSquare() != ' ') return false;
        }
      }
    }

    // Moving on y axis, x is fixed
    if(positionY != y){
      if(positionY > y){
        for(int j = positionY - 1; j > y; j--){
          if(chessField[x][j]->getSquare() != ' ') return false;
        }
      }

      if(positionY < y){
        for(int j = positionY + 1; j < y; j++){
          if(chessField[x][j]->getSquare() != ' ') return false;
        }
      }
    }
    return true;
  }

  bool checkMove(Field* (&chessField)[8][8], int x, int y){
    if(validateMove(chessField, x, y)){
      positionX = x;
      positionY = y;
      return true;
    }
    return false;
  }
};

class Bishop : public Field{
private:
  int positionX = 0;
  int positionY = 0;
  char square = ' ';
  char side = ' ';
  bool firstMove = true;
  bool eaten = false;

public:
  Bishop(int x, int y, char side, char square) :
    positionX(x),
    positionY(y),
    side(side),
    square(square)
  {

  }

  char getSquare(){
    return square;
  }

  char getSide(){
    return side;
  }

  bool validateMove(Field* (&chessField)[8][8], int x, int y){
    if(positionX == x || positionY == y) return false;
    if(abs(positionX - x) != abs(positionY - y)) return false;

    if(positionX - 1 > x && positionY - 1 > y){
      for(int i = 1; i < positionX - x; i++){
        if (chessField[positionX - i][positionY - i]->getSquare() != ' ') return false;
      }
    }

    if(positionX + 1 < x && positionY - 1 > y){
      for(int i = 1; i < x - positionX; i++){
        if (chessField[positionX + i][positionY - i]->getSquare() != ' ') return false;
      }
    }

    if(positionX + 1 < x && positionY + 1 < y){
      for(int i = 1; i < x - positionX; i++){
        if (chessField[positionX + i][positionY + i]->getSquare() != ' ') return false;
      }
    }

    if(positionX - 1 > x && positionY + 1 < y){
      for(int i = 1; i < positionX - x; i++){
        if (chessField[positionX - i][positionY + i]->getSquare() != ' ') return false;
      }
    }
    return true;
  }

  bool checkMove(Field* (&chessField)[8][8], int x, int y){
    if(validateMove(chessField, x, y)){
      positionX = x;
      positionY = y;
      return true;
    }
    return false;
  }
};

class Knight : public Field{
private:
  int positionX = 0;
  int positionY = 0;
  char square = ' ';
  char side = ' ';
  bool firstMove = true;
  bool eaten = false;

public:
  Knight(int x, int y, char side, char square) :
    positionX(x),
    positionY(y),
    side(side),
    square(square)
  {

  }

  char getSquare(){
    return square;
  }

  char getSide(){
    return side;
  }

  bool checkMove(Field* (&chessField)[8][8], int x, int y){
    if(abs(positionX - x) > 2 || abs(positionY - y) > 2) return false;
    if(abs(positionX - x) >= 2 && abs(positionY - y) >= 2) return false;
    if(abs(positionX - x) == abs(positionY - y)) return false;
    if(positionX == x || positionY == y) return false;

    positionX = x;
    positionY = y;
    return true;
  }
};

class Queen : public Field{
private:
  int positionX = 0;
  int positionY = 0;
  char square = ' ';
  char side = ' ';
  bool firstMove = true;
  bool eaten = false;

public:
  Queen(int x, int y, char side, char square) :
    positionX(x),
    positionY(y),
    side(side),
    square(square)
  {

  }

  char getSquare(){
    return square;
  }

  char getSide(){
    return side;
  }

  bool checkMove(Field* (&chessField)[8][8], int x, int y){
    Rook tmpRook(positionX, positionY, 'a', 'a');
    Bishop tmpBishop(positionX, positionY, 'a', 'a');
    if(tmpRook.validateMove(chessField, x, y) || tmpBishop.validateMove(chessField, x, y)){
      positionX = x;
      positionY = y;
      return true;
    }
    return false;
  }
};

class King : public Field{
private:
  int positionX = 0;
  int positionY = 0;
  char square = ' ';
  char side = ' ';
  bool firstMove = true;
  bool eaten = false;

public:
  King(int x, int y, char side, char square) :
    positionX(x),
    positionY(y),
    side(side),
    square(square)
  {

  }

  char getSquare(){
    return square;
  }

  char getSide(){
    return side;
  }

  bool checkMove(Field* (&chessField)[8][8], int x, int y){
  if(abs(positionX - x) > 1 || abs(positionY - y) > 1) return false;
  positionX = x;
  positionY = y;
  return true;
  }
};

//*****************************************************************************

//*****************************************************************************
// HELPER FUNCTIONS
// Initializing the chess board, used only once at the begining
void initializeBoard(Field* (&chessField)[8][8]){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      chessField[i][j] = new EmptySquare();
    }
  }

  chessField[0][0] = new Rook(0, 0, 'b', 'r');
  chessField[0][7] = new Rook(0, 7, 'b', 'r');
  chessField[7][0] = new Rook(7, 0, 'w', 'R');
  chessField[7][7] = new Rook(7, 7, 'w', 'R');

  chessField[0][2] = new Bishop(0, 2, 'w', 'b');
  chessField[0][5] = new Bishop(0, 5, 'w', 'b');
  chessField[7][2] = new Bishop(7, 2, 'w', 'B');
  chessField[7][5] = new Bishop(7, 5, 'w', 'B');

  chessField[7][1] = new Knight(7, 1, 'w', 'k');
  chessField[7][6] = new Knight(7, 6, 'w', 'k');
  chessField[0][1] = new Knight(0, 1, 'b', 's');
  chessField[0][6] = new Knight(0, 6, 'b', 's');

  chessField[7][4] = new Queen(7, 4, 'w', 'Q');
  chessField[0][4] = new Queen(0, 4, 'b', 'q');

  chessField[7][3] = new King(7, 3, 'w', 'K');
  chessField[0][3] = new King(0, 3, 'b', 'G');

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      //napravi ovo sa switch-case-om

      if(i == 1) chessField[i][j] = new Pawn(i, j, 'b', 'p');
      else if(i == 6) chessField[i][j] = new Pawn(i, j, 'w', 'D');
    }
  }
}

// Drawing the board on screen
void drawBoard(Field* (&chessField)[8][8]){
  for(int i = 0; i < 8; i++){
    std::cout<<i<<"|";
    for(int j = 0; j < 8; j++){
      std::cout<<"  "<<chessField[i][j]->getSquare();
    }
    if(i == 7){
      std::cout<<"\n |";
      break;
    }
    std::cout<<"\n |\n";
  }
  std::cout<<"_________________________"<<std::endl;
  std::cout<<"    0  1  2  3  4  5  6  7"<<std::endl;
}

// Move figure by swapping and deleting the swapped figure
// by setting swapped field to EmptyField


//*****************************************************************************

int main(){

  Field* chessField[8][8];
  initializeBoard(chessField);

  bool checkMate = false;
  while(!checkMate){
    drawBoard(chessField);
    int x, y;
    std::cin >> x >> y;
    int xx, yy;
    std::cin >> xx >> yy;
    if(chessField[x][y]->checkMove(chessField, xx, yy)){
      std::swap(chessField[x][y], chessField[xx][yy]);
      chessField[x][y] = new EmptySquare();
    }
    system("cls");
  }

}

/*
class base{
public:
  virtual void print(){}
};

class derived : public base{
public:
  void print(){
    std::cout<<"joj"<<std::endl;
  }
};

//pass by reference, fixed dimeonsion known at compile time
// source: https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
void printaj(base* (&baseptr)[3][3]){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      baseptr[i][j]->print();
    }
  }
  std::cout<<"userem se"<<std::endl;
}

int main()
{
  base* baseptr[3][3];
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      baseptr[i][j] = new derived();
      baseptr[i][j]->print();
    }
  }
  printaj(baseptr);
}
*/
