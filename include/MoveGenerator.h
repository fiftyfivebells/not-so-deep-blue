#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "Chessboard.h"
#include "Move.h"
#include <vector>

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
};

#endif
