#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Bitboard.h"

class Chessboard {
 public:
  Chessboard();
  Chessboard(std::string);
  Bitboard getAllPieces(Color) const;
  Bitboard getEmptySquares() const;
  void setEmptySquares();
  Bitboard getOccupiedSquares() const;
  void setOccupiedSquares();
  PieceType getPieceAtSquare(Color, Square) const;
  void setToFenString(std::string);
  void clearBitboards();
  Color getSideToMove() const;
  Square getEnPassantTarget() const;
  char getTurnNumber() const;
  char getHalfMoveClock() const;

 private:
  Bitboard pieces[2][6];
  Bitboard allPieces[2];
  Bitboard emptySquares;
  Bitboard occupiedSquares;
  char castleAvailability;
  char halfMoveClock;
  char turnNumber;
  Color sideToMove;
  Square enPassantTarget;
  Square makeSquareFromFen(std::string);
  Bitboard *getWhitePieces();
  Bitboard *getBlackPieces();
};

#endif
