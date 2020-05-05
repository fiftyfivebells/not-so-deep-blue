#ifndef ATTACKS_H
#define ATTACKS_H

#include "Rays.h"

namespace Attacks {
  extern Bitboard rookAttacks[64];
  extern Bitboard bishopAttacks[64];
  extern Bitboard queenAttacks[64];

  void initRookAttacks();
  void initBishopAttacks();
  void initQueenAttacks();
};

#endif
