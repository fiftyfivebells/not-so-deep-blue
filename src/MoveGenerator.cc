#include "../include/MoveGenerator.h"

MoveGenerator::MoveGenerator() {
  generateMoves(Chessboard());
}
MoveGenerator::MoveGenerator(const Chessboard &cb) {
  generateMoves(cb);
}

void MoveGenerator::generateMoves(const Chessboard &cb) {}
