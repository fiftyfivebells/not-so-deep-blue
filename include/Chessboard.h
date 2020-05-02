#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Bitboard.h"

class Chessboard {
 public:
  Chessboard();
  Bitboard *getWhitePieces();
  Bitboard *getBlackPieces();
  Bitboard getEmptySquares() const;
  void setEmptySquares();
  Bitboard getOccupiedSquares() const;
  void setOccupiedSquares();
  PieceType getPieceAtSquare(Color, Square) const;
  void printAsBits(const Bitboard b) const;
  void setToFenString(std::string fen);
  void clearBitboards();
  Color getSideToMove() const;
  Square getEnPassantTarget() const;
  char getTurnNumber() const;
  char getHalfMoveClock() const;

 private:
  Bitboard pieces[2][6];
  Bitboard emptySquares;
  Bitboard occupiedSquares;
  char castleAvailability;
  char halfMoveClock;
  char turnNumber;
  Color sideToMove;
  Square enPassantTarget;
  Square makeSquareFromFen(std::string);
};

#endif
