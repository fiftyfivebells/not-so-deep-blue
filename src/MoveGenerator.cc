#include "../include/MoveGenerator.h"

MoveGenerator::MoveGenerator() {
  generateMoves(Chessboard());
}
MoveGenerator::MoveGenerator(const Chessboard &cb) {
  generateMoves(cb);
}

void MoveGenerator::generateMoves(const Chessboard &cb) {}
std::vector<Move> MoveGenerator::getMoves() const { return moves; }
std::vector<Move> MoveGenerator::getLegalMoves() const { return legalMoves; }

void MoveGenerator::generateRookMoves(const Chessboard &cb) {
  Color active = cb.getActiveSide();
  Color enemy = (active == WHITE) ? BLACK : WHITE;
  Bitboard rooks = cb.getPiecesByType(active, ROOK);

  while (rooks) {
    Square fromSquare = popLSB(rooks);
    Bitboard moves = cb.getAttacksFromSquare(fromSquare, active);

    addMoves(cb, fromSquare, ROOK, moves, cb.getPiecesToAttack(enemy));
  }
}

