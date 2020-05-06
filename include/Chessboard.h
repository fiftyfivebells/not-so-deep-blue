#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Bitboard.h"

class Chessboard {
 public:
  Chessboard();
  Chessboard(std::string);
  Bitboard getAllPieces(Color) const;
  Bitboard getPiecesByType(Color, PieceType);
  Bitboard getEmptySquares() const;
  void setEmptySquares();
  Bitboard getOccupiedSquares() const;
  void setOccupiedSquares();
  PieceType getPieceAtSquare(Color, Square) const;
  bool isColorAttackingSquare(Color, Square);
  Bitboard getAttacksFromSquare(Square, Color);
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
  Bitboard getPawnAttacksFromSquare(Square, Color, Bitboard);
  Bitboard getRookAttacksFromSquare(Square, Bitboard);
  Bitboard getBishopAttacksFromSquare(Square, Bitboard);
  Bitboard getQueenAttacksFromSquare(Square, Bitboard);
  Bitboard getKnightAttacksFromSquare(Square, Bitboard);
  Bitboard getKingAttacksFromSquare(Square, Bitboard);
};

#endif
