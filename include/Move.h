#ifndef MOVE_H
#define MOVE_H

#include "Bitboard.h"
#include "Chessboard.h"

#define SQUARE_BITS 63
#define PIECE_BITS 7
#define FLAG_BITS 15

class Move {
 public:
  Move(Square, Square, PieceType, unsigned int = 0);
  Move();

  enum Flag : unsigned int {
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

  unsigned int getMove() const;
  Square getToSquare() const;
  void setToSquare(Square);

  Square getFromSquare() const;
  void setFromSquare(Square);

  PieceType getPieceType() const;
  void setPieceType(PieceType);

  PieceType getCapturedPiece() const;
  void setCapturedPiece(PieceType);

  PieceType getPromotionPiece() const;
  void setPromotionPiece(PieceType);

  unsigned int getFlag() const;
  void setFlag(unsigned int);

  bool operator==(Move) const;
  bool operator!=(Move) const;

 private:
  unsigned int move;
};

#endif
