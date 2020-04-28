#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Bitboard.h"

class Chessboard {
 public:
  Chessboard();
  Bitboard[] getWhitePieces();
  Bitboard[] getBlackPieces();

 private:
  Bitboard pieces[2][6];
};

#endif
