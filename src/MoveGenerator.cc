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
  moves.clear();

  Color active = cb.getActiveSide();
  if (active == WHITE) generateWPawnMoves(cb);
  else generateBPawnMoves(cb);

  generateRookMoves(cb);
  generateKnightMoves(cb);
  generateBishopMoves(cb);
  generateQueenMoves(cb);
  generateKingMoves(cb);
}

void MoveGenerator::generateLegalMoves(const Chessboard &cb) {
  for (auto move : moves) {
    Chessboard temp = cb;
    temp.performMove(move);

    if (!temp.isColorInCheck(temp.getActiveSide()))
      legalMoves.push_back(move);
  }
}

void MoveGenerator::generateWPawnMoves(const Chessboard &cb) {
  generateWPawnSinglePush(cb);
  generateWPawnDoublePush(cb);
  generateWPawnLeftAttacks(cb);
  generateWPawnRightAttacks(cb);
}

void MoveGenerator::generateWPawnSinglePush(const Chessboard &cb) {
  Bitboard singlePush = cb.getPiecesByType(WHITE, PAWN) << 8;
  singlePush &= cb.getEmptySquares();

  Bitboard promotions = singlePush & Rank8;
  singlePush &= ~Rank8;

  while (singlePush) {
    Square toSquare = popLSB(singlePush);
    Square fromSquare = Square(toSquare - 8);
    moves.push_back(Move(fromSquare, toSquare, PAWN));
  }

  while (promotions) {
    Square toSquare = popLSB(promotions);
    Square fromSquare = (Square)(toSquare - 8);

    generatePawnPromotions(fromSquare, toSquare);
  }
}

void MoveGenerator::generateWPawnDoublePush(const Chessboard &cb) {
  Bitboard singlePush = (cb.getPiecesByType(WHITE, PAWN) << 8) & cb.getEmptySquares();
  Bitboard doublePush = (singlePush << 8) & cb.getEmptySquares() & Rank4;

  while (doublePush) {
    Square toSquare = popLSB(doublePush);
    Square fromSquare = Square(toSquare - 16);
    moves.push_back(Move(fromSquare, toSquare, PAWN, Move::D_PAWN_PUSH));
  }
}

void MoveGenerator::generateWPawnLeftAttacks(const Chessboard &cb) {
  Bitboard leftAttacks = (cb.getPiecesByType(WHITE, PAWN) << 7) & ~FileH;
  leftAttacks &= cb.getPiecesToAttack(BLACK);

  Bitboard leftAttackPromos = leftAttacks & Rank8;
  leftAttacks &= ~Rank8;

  Bitboard leftEP = (1ull << cb.getEnPassantTarget());
  leftEP &= (cb.getPiecesByType(WHITE, PAWN) << 7) & ~FileH;

  while (leftAttacks) {
    Square toSquare = popLSB(leftAttacks);
    Move move(Square(toSquare - 7), toSquare, PAWN, Move::CAPTURE);
    move.setCapturedPiece(cb.getPieceAtSquare(BLACK, toSquare));

    moves.push_back(move);
  }

  while (leftAttackPromos) {
    Square toSquare = popLSB(leftAttackPromos);
    PieceType capture = cb.getPieceAtSquare(BLACK, toSquare);

    generatePawnPromotions(Square(toSquare - 9), toSquare, capture);
  }

  if (leftEP) {
    Square toSquare = popLSB(leftEP);
    Move ep(Square(toSquare - 7), toSquare, PAWN, Move::EP_CAPTURE);
    ep.setCapturedPiece(PAWN);

    moves.push_back(ep);
  }
}

void MoveGenerator::generateWPawnRightAttacks(const Chessboard &cb) {
  Bitboard rightAttacks = (cb.getPiecesByType(WHITE, PAWN) << 9) & ~FileA;
  rightAttacks &= cb.getPiecesToAttack(BLACK);

  Bitboard rightAttackPromos = rightAttacks & Rank8;
  rightAttacks &= ~Rank8;

  Bitboard rightEP = (1ull << cb.getEnPassantTarget());
  rightEP &= (cb.getPiecesByType(WHITE, PAWN) << 9) & ~FileA;

  while (rightAttacks) {
    Square toSquare = popLSB(rightAttacks);
    Move move(Square(toSquare - 9), toSquare, PAWN, Move::CAPTURE);
    move.setCapturedPiece(cb.getPieceAtSquare(BLACK, toSquare));

    moves.push_back(move);
  }

  while (rightAttackPromos) {
    Square toSquare = popLSB(rightAttackPromos);
    PieceType capture = cb.getPieceAtSquare(BLACK, toSquare);

    generatePawnPromotions(Square(toSquare - 9), toSquare, capture);
  }

  if (rightEP) {
    Square toSquare = popLSB(rightEP);
    Move ep(Square(toSquare - 9), toSquare, PAWN, Move::EP_CAPTURE);
    ep.setCapturedPiece(PAWN);

    moves.push_back(ep);
  }
}


void MoveGenerator::generateBPawnMoves(const Chessboard &cb) {
  generateBPawnSinglePush(cb);
  generateBPawnDoublePush(cb);
  generateBPawnLeftAttacks(cb);
  generateBPawnRightAttacks(cb);
}

void MoveGenerator::generateBPawnSinglePush(const Chessboard &cb) {
  Bitboard singlePush = cb.getPiecesByType(BLACK, PAWN) >> 8;
  singlePush &= cb.getEmptySquares();

  Bitboard promotions = singlePush & Rank1;
  singlePush &= ~Rank1;

  while (singlePush) {
    Square toSquare = popLSB(singlePush);
    Square fromSquare = Square(toSquare + 8);
    moves.push_back(Move(fromSquare, toSquare, PAWN));
  }

  while (promotions) {
    Square toSquare = popLSB(promotions);

    generatePawnPromotions(Square(toSquare + 8), toSquare);
  }
}

void MoveGenerator::generateBPawnDoublePush(const Chessboard &cb) {
  Bitboard singlePush = (cb.getPiecesByType(BLACK, PAWN) >> 8) & cb.getEmptySquares();
  Bitboard doublePush = (singlePush << 8) & cb.getEmptySquares() & Rank5;

  while (doublePush) {
    Square toSquare = popLSB(doublePush);
    Square fromSquare = Square(toSquare + 16);
    moves.push_back(Move(fromSquare, toSquare, PAWN, Move::D_PAWN_PUSH));
  }
}

void MoveGenerator::generateBPawnLeftAttacks(const Chessboard &cb) {
  Bitboard leftAttacks = (cb.getPiecesByType(BLACK, PAWN) >> 9) & ~FileH;
  leftAttacks &= cb.getPiecesToAttack(WHITE);

  Bitboard leftAttackPromos = leftAttacks & Rank1;
  leftAttacks &= ~Rank1;

  Bitboard leftEP = (1ull << cb.getEnPassantTarget());
  leftEP &= (cb.getPiecesByType(BLACK, PAWN) >> 9) & ~FileH;

  while (leftAttacks) {
    Square toSquare = popLSB(leftAttacks);
    Move move(Square(toSquare + 9), toSquare, PAWN, Move::CAPTURE);
    move.setCapturedPiece(cb.getPieceAtSquare(WHITE, toSquare));

    moves.push_back(move);
  }

  while (leftAttackPromos) {
    Square toSquare = popLSB(leftAttackPromos);
    PieceType capture = cb.getPieceAtSquare(WHITE, toSquare);

    generatePawnPromotions(Square(toSquare + 9), toSquare, capture);
  }

  if (leftEP) {
    Square toSquare = popLSB(leftEP);
    Move ep(Square(toSquare + 9), toSquare, PAWN, Move::EP_CAPTURE);
    ep.setCapturedPiece(PAWN);

    moves.push_back(ep);
  }
}

void MoveGenerator::generateBPawnRightAttacks(const Chessboard &cb) {
  Bitboard rightAttacks = (cb.getPiecesByType(BLACK, PAWN) >> 7) & ~FileA;
  rightAttacks &= cb.getPiecesToAttack(WHITE);

  Bitboard rightAttackPromos = rightAttacks & Rank1;
  rightAttacks &= ~Rank1;

  Bitboard rightEP = (1ull << cb.getEnPassantTarget());
  rightEP &= (cb.getPiecesByType(BLACK, PAWN) >> 7) & ~FileA;

  while (rightAttacks) {
    Square toSquare = popLSB(rightAttacks);
    Move move(Square(toSquare + 7), toSquare, PAWN, Move::CAPTURE);
    move.setCapturedPiece(cb.getPieceAtSquare(WHITE, toSquare));

    moves.push_back(move);
  }

  while (rightAttackPromos) {
    Square toSquare = popLSB(rightAttackPromos);
    PieceType capture = cb.getPieceAtSquare(WHITE, toSquare);

    generatePawnPromotions(Square(toSquare + 7), toSquare, capture);
  }

  if (rightEP) {
    Square toSquare = popLSB(rightEP);
    Move ep(Square(toSquare + 7), toSquare, PAWN, Move::EP_CAPTURE);
    ep.setCapturedPiece(PAWN);

    moves.push_back(ep);
  }
}

void MoveGenerator::generatePawnPromotions(Square from, Square to, PieceType pt) {
  Move promotion(from, to, PAWN);
  if (pt == NONE) promotion.setFlag(Move::PROMOTION);

  else {
    promotion.setFlag(Move::CAP_PROMOTION);
    promotion.setCapturedPiece(pt);
  }

  Move queen(promotion);
  queen.setPromotionPiece(QUEEN);
  moves.push_back(queen);

  Move bishop(promotion);
  bishop.setPromotionPiece(BISHOP);
  moves.push_back(bishop);

  Move rook(promotion);
  rook.setPromotionPiece(ROOK);
  moves.push_back(rook);

  Move knight(promotion);
  knight.setPromotionPiece(KNIGHT);
  moves.push_back(knight);
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
                             Bitboard allMoves, Bitboard canAttack) {

  Color active = cb.getActiveSide();
  Color enemy = cb.getInactiveSide();

  // exclude king attacks
  allMoves &= ~(cb.getPiecesByType(enemy, KING));

  Bitboard quietMoves = allMoves & ~canAttack;
  while (quietMoves) {
    Square to = popLSB(quietMoves);
    moves.push_back(Move(from, to, pt));
  }

  Bitboard attacks = allMoves & canAttack;
  while (attacks) {
    Square to = popLSB(attacks);
    PieceType capture = cb.getPieceAtSquare(enemy, to);

    Move m(from, to, pt, Move::CAPTURE);
    m.setCapturedPiece(capture);

    moves.push_back(m);
  }
}
