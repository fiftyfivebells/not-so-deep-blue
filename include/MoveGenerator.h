#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <vector>

#include "Chessboard.h"
#include "Move.h"

class MoveGenerator {
 public:
  MoveGenerator();
  MoveGenerator(const Chessboard &);

  std::vector<Move> getMoves() const;
  std::vector<Move> getLegalMoves() const;

  void generateMoves(const Chessboard &);
  void generateLegalMoves(const Chessboard &);

 private:
  std::vector<Move> moves;
  std::vector<Move> legalMoves;

  void generateLegalMoves(const Chessboard &);

  void generateWPawnMoves(const Chessboard &);
  void generateWPawnSinglePush(const Chessboard &);
  void generateWPawnDoublePush(const Chessboard &);
  void generateWPawnLeftAttacks(const Chessboard &);
  void generateWPawnRightAttacks(const Chessboard &);

  void generateBPawnMoves(const Chessboard &);
  void generateBPawnSinglePush(const Chessboard &);
  void generateBPawnDoublePush(const Chessboard &);
  void generateBPawnLeftAttacks(const Chessboard &);
  void generateBPawnRightAttacks(const Chessboard &);

  void generatePawnPromotions(Square, Square, PieceType = NONE);

  void generateRookMoves(const Chessboard &);
  void generateKnightMoves(const Chessboard &);
  void generateBishopMoves(const Chessboard &);
  void generateQueenMoves(const Chessboard &);
  void generateKingMoves(const Chessboard &);

  void generateWhiteCastles(const Chessboard &);
  void generateBlackCastles(const Chessboard &);

  void addMoves(const Chessboard &, Square, PieceType, Bitboard, Bitboard);
};

#endif
