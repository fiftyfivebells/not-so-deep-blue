#include "../include/Move.h"

Move::Move() {}

Move::Move(Square from, Square to, PieceType pt, unsigned int flags) {
  move = 0;
  move |= (pt & PIECE_BITS);
  move |= ((from & SQUARE_BITS) << 9);
  move |= ((to & SQUARE_BITS) << 15);
  move |= ((flags & FLAG_BITS) << 21);
}

unsigned int Move::getMove() const { return move; }

unsigned int Move::getToSquare() const { return (move >> 15) & SQUARE_BITS; }

void Move::setToSquare(Square to) {}

unsigned int Move::getFromSquare() const { return (move >> 9) & SQUARE_BITS; }

void Move::setFromSquare(Square from) {}

unsigned int Move::getPieceType() const { return move & PIECE_BITS; }

void Move::setPieceType(PieceType pt) {}

unsigned int Move::getCapturedPiece() const { return (move >> 3) & PIECE_BITS; }

void Move::setCapturedPiece(PieceType pt) {}

unsigned int Move::getFlag() const { return (move >> 21) & FLAG_BITS; }

void Move::setFlag(unsigned int flag) {}

bool Move::operator==(Move other) const {
  return (move & 0xffff) == (other.getMove() & 0xffff);
}

bool Move::operator!=(Move other) const {
  return (move & 0xffff) != (other.getMove() & 0xffff);
}
