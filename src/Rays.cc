#include "../include/Rays.h"

Bitboard Rays::rays[64][8];

void Rays::init() {

  for (int square = 0; square < 64; ++square) {
    rays[square][Rays::North] = 0x0101010101010100 << square;
    rays[square][Rays::South] = 0x0080808080808080 >> (63 - square);
    rays[square][Rays::East] = 2 * ((1ull << (square | 7)) - (1ull << square));
    rays[square][Rays::West] = (1ull << square) - (1ull << (square & 56));
  }
  // Bitboard north = 0x0101010101010100;
  // for (int square = SQ_A1; square <= SQ_H8; ++square, north <<= 1)
  //   rays[square][Rays::North] = north;
  Bitboard northeast = 0x8040201008040200;
  for (int file = 0; file < 8; ++file, northeast = eastOne(northeast)) {
    Bitboard ne = northeast;
    for (int r8 = 0; r8 < 64; r8 += 8, ne <<= 8)
      rays[r8+file][Rays::NorthEast] = ne;
  }

  Bitboard northwest = 0x102040810204000;
  for (int file = 7; file > -1; --file, northwest = westOne(northwest)) {
    Bitboard nw = northwest;
    for (int r8 = 0; r8 < 64; r8 += 8, nw <<= 8)
      rays[file+r8][Rays::NorthWest] = nw;
  }

  Bitboard southwest = 0x40201008040201;
  for (int file = 7; file >= 0; --file, southwest = westOne(southwest)) {
    Bitboard sw = southwest;
    for (int r8 = 56; r8 >= 0; r8 -= 8, sw >>= 8)
      rays[file+r8][Rays::SouthWest] = sw;
  }

  Bitboard southeast = 0x2040810204080;
  for (int file = 7; file >= 0; --file, southeast = eastOne(southeast)) {
    Bitboard se = southeast;
    for (int r8 = 63; r8 >= 0; r8 -=8, se >>= 8)
      rays[r8-file][Rays::SouthEast] = se;
  }
}

Bitboard Rays::getRayBoard(Direction d, int s) { return rays[s][d]; }
