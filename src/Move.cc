#include "../include/Move.h"

Move::Move() {}

Move::Move(Square from, Square to, PieceType pt, unsigned int flags) {
  move = 0;
  move |= (pt & PIECE_BITS);
  move |= ((from & SQUARE_BITS) << 9);
  move |= ((to & SQUARE_BITS) << 15);
  move |= ((flags & FLAG_BITS) << 21);
}

Move::Move(Move &other) { this->move = other.move; }

unsigned int Move::getMove() const { return move; }

Square Move::getToSquare() const {
  return (Square)((move >> 15) & SQUARE_BITS);
}

void Move::setToSquare(Square to) {
  unsigned int bitMask = SQUARE_BITS << 15;
  move = (move & ~bitMask) | ((to << 15) & bitMask);
}

Square Move::getFromSquare() const {
  return (Square)((move >> 9) & SQUARE_BITS);
}

void Move::setFromSquare(Square from) {
  unsigned int bitMask = SQUARE_BITS << 9;
  move = (move & ~bitMask) | ((from << 9) & bitMask);
}

PieceType Move::getPieceType() const {
  return (PieceType)(move & PIECE_BITS);
}

void Move::setPieceType(PieceType pt) {
  unsigned int bitMask = PIECE_BITS;
  move = (move & ~bitMask) | (pt & bitMask);
}

PieceType Move::getCapturedPiece() const {
  return (PieceType)((move >> 3) & PIECE_BITS);
}

void Move::setCapturedPiece(PieceType pt) {
  unsigned int bitMask = PIECE_BITS << 3;
  move = (move & ~bitMask) | ((pt << 3) & bitMask);
}

PieceType Move::getPromotionPiece() const {
  return (PieceType)((move >> 6) & PIECE_BITS);
}

void Move::setPromotionPiece(PieceType pt) {
  unsigned int bitMask = PIECE_BITS << 6;
  move = (move & ~bitMask) | ((pt << 6) & bitMask);
}

unsigned int Move::getFlag() const { return (move >> 21) & FLAG_BITS; }

void Move::setFlag(unsigned int flag) {
  unsigned int bitMask = FLAG_BITS << 21;
  move = (move & ~bitMask) | ((flag << 21) & bitMask);
}

std::string Move::getMoveNotation() const {
  Square from = getFromSquare();
  Square to = getToSquare();

  std::string notation = getFenFromSquare(from) + getFenFromSquare(to);

  if (getFlag() == PROMOTION || getFlag() == CAP_PROMOTION) {
    switch(getPromotionPiece()) {
      case ROOK: notation += "r";
        break;
      case KNIGHT: notation += "n";
        break;
      case BISHOP: notation += "b";
        break;
      case QUEEN: notation += "q";
        break;
      default:
        break;
    }
  }

  return notation;
}

bool Move::operator==(Move other) const {
  return (move & 0xffff) == (other.getMove() & 0xffff);
}

bool Move::operator!=(Move other) const {
  return (move & 0xffff) != (other.getMove() & 0xffff);
}
