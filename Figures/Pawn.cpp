#include "Pawn.h"

Pawn::Pawn(int x, int y, char side, char square) :
    positionX(x),
    positionY(y),
    side(side),
    square(square)
  {

  }

char Pawn::getSquare(){
    return square;
  }

char Pawn::getSide(){
    return side;
  }

bool Pawn::checkMove(Field* (&chessField)[8][8], int x, int y){
  if(chessField[positionX][positionY]->getSide() == 'w' && x >= positionX) return false;
  else if(chessField[positionX][positionY]->getSide() == 'b' && x <= positionX) return false;

    if(firstMove){
      if(abs(positionX - x) < 3 && positionY == y && chessField[x][y]->getSquare() == ' '){
        positionX = x;
        firstMove = false;
        return true;
      }
      else if(abs(positionX - x) == 1 && abs(positionY - y) == 1){
        if(chessField[x][y]->getSquare() == ' ') return false;
        positionX = x;
        firstMove = false;
        return true;
      }
      return false;
    }

    if(abs(positionX - x) == 1 && positionY == y && chessField[x][y]->getSquare() == ' '){
      positionX = x;
      return true;
    }
    else if(abs(positionX - x) == 1 && abs(positionY - y) == 1){
      if(chessField[x][y]->getSquare() == ' ') return false;
      positionX = x;
      firstMove = false;
      return true;
    }
    return false;
  }
