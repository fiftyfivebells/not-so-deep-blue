#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <iostream>
#include "Types.h"

typedef uint64_t Bitboard;

const Bitboard FileA = 0x0101010101010101;
const Bitboard FileB = FileA << 1;
const Bitboard FileC = FileB << 1;
const Bitboard FileD = FileC << 1;
const Bitboard FileE = FileD << 1;
const Bitboard FileF = FileE << 1;
const Bitboard FileG = FileF << 1;
const Bitboard FileH = FileG << 1;

const Bitboard Rank1 = 0xff;
const Bitboard Rank2 = Rank1 << 8;
const Bitboard Rank3 = Rank2 << 8;
const Bitboard Rank4 = Rank3 << 8;
const Bitboard Rank5 = Rank4 << 8;
const Bitboard Rank6 = Rank5 << 8;
const Bitboard Rank7 = Rank6 << 8;
const Bitboard Rank8 = Rank7 << 8;

const Bitboard PAWN_START = 0xff00000000ff00;
const Bitboard ROOK_START = 0x8100000000000081;
const Bitboard KNIGHT_START = 0x4200000000000042;
const Bitboard BISHOP_START = 0x2400000000000024;
const Bitboard QUEEN_START = 0x800000000000008;
const Bitboard KING_START = 0x1000000000000010;

const Bitboard ALL_WHITE = 0xFFFF;
const Bitboard ALL_BLACK = 0xFFFF000000000000;

void printBitboard(const Bitboard b) {
  for (int row = 7; row >= 0; --row) {
    for (int col = 0; col <= 7; ++col) {
      if (b & (1ULL << ((row * 8) + col))) {
        std::cout << "1 ";
      }
      else {
        std::cout << "0 ";
      }
    }
    std::cout << std::endl;
  }
  std::cout  << std::endl;
}

#endif
