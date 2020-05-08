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

void MoveGenerator::generateMoves(const Chessboard &cb) {
  Color active = cb.getActiveSide();

  if (active == WHITE) generateWhitePawnMoves(cb);
  else generateBlackPawnMoves(cb);

  generateRookMoves(cb);
  generateKnightMoves(cb);
  generateBishopMoves(cb);
  generateQueenMoves(cb);
  generateKingMoves(cb);
}

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

void MoveGenerator::generateKnightMoves(const Chessboard &cb) {
  Color active = cb.getActiveSide();
  Color enemy = cb.getInactiveSide();
  Bitboard knights = cb.getPiecesByType(active, KNIGHT);

  while (knights) {
    Square fromSquare = popLSB(knights);
    Bitboard allMoves = cb.getAttacksFromSquare(fromSquare, active);

    addMoves(cb, fromSquare, KNIGHT, allMoves, cb.getPiecesToAttack(enemy));
  }
}

void MoveGenerator::generateBishopMoves(const Chessboard &cb) {
  Color active = cb.getActiveSide();
  Color enemy = cb.getInactiveSide();
  Bitboard bishops = cb.getPiecesByType(active, BISHOP);

  while (bishops) {
    Square fromSquare = popLSB(bishops);
    Bitboard allMoves = cb.getAttacksFromSquare(fromSquare, active);

    addMoves(cb, fromSquare, BISHOP, allMoves, cb.getPiecesToAttack(enemy));
  }
}

void MoveGenerator::generateQueenMoves(const Chessboard &cb) {
  Color active = cb.getActiveSide();
  Color enemy = cb.getInactiveSide();
  Bitboard queens = cb.getPiecesByType(active, QUEEN);

  while (queens) {
    Square fromSquare = popLSB(queens);
    Bitboard allMoves = cb.getAttacksFromSquare(fromSquare, active);

    addMoves(cb, fromSquare, QUEEN, allMoves, cb.getPiecesToAttack(enemy));
  }
}

void MoveGenerator::generateKingMoves(const Chessboard &cb) {
  Color active = cb.getActiveSide();
  Color enemy = cb.getInactiveSide();
  Bitboard king = cb.getPiecesByType(active, KING);

  while (king) {
    Square fromSquare = popLSB(king);
    Bitboard allMoves = cb.getAttacksFromSquare(fromSquare, active);

    addMoves(cb, fromSquare, KING, allMoves, cb.getPiecesToAttack(enemy));
  }
}

void MoveGenerator::addMoves(const Chessboard &cb, Square from, PieceType pt,
                             Bitboard allMoves, Bitboard attacked) {

  Color active = cb.getActiveSide();
  Color enemy = cb.getInactiveSide();

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
