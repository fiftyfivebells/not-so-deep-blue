#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <iostream>

#include "Types.h"

typedef uint64_t Bitboard;

const Bitboard EMPTY = 0ull;

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

const Bitboard ALL_WHITE_START = 0xFFFF;
const Bitboard ALL_BLACK_START = 0xFFFF000000000000;

inline Bitboard northOne(Bitboard b) { return b << 8; }
inline Bitboard southOne(Bitboard b) { return b >> 8; }
inline Bitboard eastOne(Bitboard b) { return ((b << 1) & ~FileA); }
inline Bitboard westOne(Bitboard b) { return (b >> 1) & ~FileH; }
inline Bitboard norEastOne(Bitboard b) { return (b << 9) & ~FileA; }
inline Bitboard norWestOne(Bitboard b) { return (b << 7) & ~FileH; }
inline Bitboard souEastOne(Bitboard b) { return (b >> 7) & ~FileA; }
inline Bitboard souWestOne(Bitboard b) { return (b >> 9) & ~FileH;}

inline int bitCount(Bitboard b) { return __builtin_popcountll(b); }
inline int bitScanForward(Bitboard b) { return __builtin_ffsll(b) - 1; }
inline int bitScanReverse(Bitboard b) { return 63 - __builtin_clzll(b); }
inline Square popLSB(Bitboard &b) {
  int lsbIdx = bitScanForward(b);
  b &= b - 1;
  return (Square)lsbIdx;
}

inline void printAsBits(Bitboard b) {
    for (int row = 7; row >= 0; --row) {
    for (int col = 0; col <= 7; ++col) {
      if (b & (1ULL << ((row * 8) + col))) {
        std::cout << "1 ";
      } else {
        std::cout << "0 ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

#endif
