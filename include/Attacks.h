#ifndef ATTACKS_H
#define ATTACKS_H

#include "Rays.h"

namespace Attacks {
  extern Bitboard rookAttacks[64];
  extern Bitboard bishopAttacks[64];
  extern Bitboard queenAttacks[64];
  extern Bitboard knightAttacks[64];
  extern Bitboard kingAttacks[64];
  extern Bitboard pawnAttacks[2][64];

  void initAttacks();
  void initRookAttacks();
  void initBishopAttacks();
  void initQueenAttacks();
  void initKnightAttacks();
  void initKingAttacks();
  void initPawnAttacks();

  Bitboard getSlidingAttacks(PieceType, Square, Bitboard);
  Bitboard getNonSlidingAttacks(PieceType, Square, Bitboard);
  Bitboard getPawnAttacks(Square, Color, Bitboard);
};

#endif
