#ifndef RAYS_H
#define RAYS_H

#include "Bitboard.h"

namespace Rays {

enum Direction {
  North,
  South,
  East,
  West,
  NorthWest,
  NorthEast,
  SouthWest,
  SouthEast
};


  extern Bitboard rays[64][8];

  void init();

  Bitboard getRayBoard(Direction, int);
}

#endif
