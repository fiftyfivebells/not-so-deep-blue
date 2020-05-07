#ifndef MOVE_H
#define MOVE_H

#include "Bitboard.h"
#include "Chessboard.h"

class Move {
 public:
  Move(Square, Square, PieceType, unsigned char = 0);
  Move();

  enum Flag : unsigned char {
    QUIET_MOVE = 0,
    D_PAWN_PUSH,
    K_CASTLE,
    Q_CASTLE,
    CAPTURE,
    EP_CAPTURE,
    N_PROMOTION,
    B_PROMOTION,
    R_PROMOTION,
    Q_PROMOTION,
    NP_CAPTURE,
    BP_CAPTURE,
    RP_CAPTURE,
    QP_CAPTURE
  };

  unsigned char getToSquare();
  void setToSquare(Square);

  unsigned char getFromSquare();
  void setFromSquare(Square);

  unsigned char getFlag();
  void setFlag(unsigned char);

  bool operator==(Move) const;
  bool operator!=(Move) const;

 private:
  unsigned int move;
};

#endif
