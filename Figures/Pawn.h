#include "Field.h"

class Pawn : public Field{
private:
  int positionX = 0;
  int positionY = 0;
  char square = ' ';
  char side = ' ';
  bool firstMove = true;
  bool eaten = false;

public:
  Pawn(int x, int y, char side, char square);
  char getSquare();
  char getSide();
  bool checkMove(Field* (&chessField)[8][8], int x, int y);
};
