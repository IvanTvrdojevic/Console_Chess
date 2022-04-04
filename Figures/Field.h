#ifndef FIELD_H
#define FIELD_h

class Field{
private:

public:
  virtual char getSquare() = 0;
  virtual bool checkMove(Field* (&chessField)[8][8], int x, int y) = 0;
  virtual char getSide() = 0;
};

#endif
