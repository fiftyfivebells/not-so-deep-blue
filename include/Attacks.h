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

  Bitboard getBishopAttacks(int, Bitboard);
  Bitboard getRookAttacks(int, Bitboard);
  Bitboard getQueenAttacks(int, Bitboard);
  Bitboard getKnightAttacks(int, Bitboard);
  Bitboard getPawnAttacks(int, Bitboard);
  Bitboard getKingAttacks(int, Bitboard);
};

#endif
