#ifndef MOVE_H
#define MOVE_H

#include "Bitboard.h"

#define SQUARE_BITS 63
#define PIECE_BITS 7
#define FLAG_BITS 7

class Move {
 public:
  Move();
  Move(Square, Square, PieceType, unsigned int = 0);
  Move(Move &);

  enum Flag : unsigned int {
    QUIET_MOVE = 0,
    D_PAWN_PUSH,
    K_CASTLE,
    Q_CASTLE,
    CAPTURE,
    EP_CAPTURE,
    PROMOTION,
    CAP_PROMOTION
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

  std::string getMoveNotation() const;

  bool operator==(Move) const;
  bool operator!=(Move) const;

 private:
  unsigned int move;
};

#endif
