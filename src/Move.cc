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

unsigned int Move::getToSquare() const { return 1; }

void Move::setToSquare(Square to) {}

unsigned int Move::getFromSquare() const { return 1; }

void Move::setFromSquare(Square from) {}

unsigned int Move::getPieceType() const { return 1; }

void Move::setPieceType(PieceType pt) {}

unsigned int Move::getCapturedPiece() const {}

void Move::setCapturedPiece(PieceType pt) {}

unsigned int Move::getFlag() const { return 1; }

void Move::setFlag(unsigned int flag) {}

bool Move::operator==(Move other) const { return true; }
bool Move::operator!=(Move other) const { return true; }
