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
  Color enemy = cb.getInactiveSide();
  Bitboard rooks = cb.getPiecesByType(active, ROOK);

  while (rooks) {
    Square fromSquare = popLSB(rooks);
    Bitboard allMoves = cb.getAttacksFromSquare(fromSquare, active);

    addMoves(cb, fromSquare, ROOK, allMoves, cb.getPiecesToAttack(enemy));
  }
}


    addMoves(cb, fromSquare, ROOK, moves, cb.getPiecesToAttack(enemy));
  }
}

void MoveGenerator::addMoves(const Chessboard &cb, Square from, PieceType pt,
                             Bitboard allMoves, Bitboard attacked) {

  Color active = cb.getActiveSide();
  Color enemy = (active == WHITE) ? BLACK : WHITE;

  // exclude king attacks
  allMoves &= ~(cb.getPiecesByType(enemy, KING));

  Bitboard quietMoves = allMoves & ~attacked;
  while (quietMoves) {
    Square to = popLSB(quietMoves);
    moves.push_back(Move(from, to, pt));
  }

  Bitboard attacks = allMoves & attacked;
  while (attacks) {
    Square to = popLSB(attacks);
    PieceType capture = cb.getPieceAtSquare(enemy, to);

    Move m(from, to, pt, Move::CAPTURE);
    m.setCapturedPiece(capture);

    moves.push_back(m);
  }
}
