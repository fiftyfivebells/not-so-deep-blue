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

 private:
  std::vector<Move> moves;
  std::vector<Move> legalMoves;

  void generateWhitePawnMoves(const Chessboard &);
  void generateBlackPawnMoves(const Chessboard &);

  void generateRookMoves(const Chessboard &);
  void generateKnightMoves(const Chessboard &);
  void generateBishopMoves(const Chessboard &);
  void generateQueenMoves(const Chessboard &);
  void generateKingMoves(const Chessboard &);

  void addMoves(const Chessboard &, Square, PieceType, Bitboard, Bitboard);
};

#endif
