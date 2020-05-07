#include "../include/Move.h"

Move::Move() {}

Move::Move(Square from, Square to, PieceType pt, unsigned int flags) {
  move |= (pt & 7);
  move |= ((from & 63) << 9);
  move |= ((to & 63) << 15);
  move |= ((flags & 15) << 24);
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
