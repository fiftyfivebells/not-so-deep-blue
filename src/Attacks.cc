#include "../include/Attacks.h"

Bitboard Attacks::rookAttacks[64];
Bitboard Attacks::bishopAttacks[64];
Bitboard Attacks::queenAttacks[64];
Bitboard Attacks::knightAttacks[64];
Bitboard Attacks::kingAttacks[64];
Bitboard Attacks::pawnAttacks[2][64];

void Attacks::initRookAttacks() {
  for (int square = SQ_A1; square < 64; ++square)
    rookAttacks[square] = Rays::getRayBoard(Rays::North, square) |
                          Rays::getRayBoard(Rays::South, square) |
                          Rays::getRayBoard(Rays::East, square) |
                          Rays::getRayBoard(Rays::West, square);
}

void Attacks::initBishopAttacks() {
  for (int square = SQ_A1; square < 64; ++square)
    bishopAttacks[square] = Rays::getRayBoard(Rays::NorthWest, square) |
                            Rays::getRayBoard(Rays::NorthEast, square) |
                            Rays::getRayBoard(Rays::SouthWest, square) |
                            Rays::getRayBoard(Rays::SouthEast, square);
}

void Attacks::initQueenAttacks() {
  for (int square = SQ_A1; square < 64; ++square)
    queenAttacks[square] = rookAttacks[square] | bishopAttacks[square];
}

void Attacks::initKnightAttacks() {
  for (int square = SQ_A1; square < 64; ++square) {
    Bitboard sq = 1ull << square;
    Bitboard attacks = (((sq << 17) | (sq >> 15)) & ~FileA) |
                       (((sq << 10) | (sq >> 6)) & ~(FileA | FileB)) |
                       (((sq << 15) | (sq >> 17)) & ~FileH) |
                       (((sq >> 10) | (sq << 6)) & ~(FileG | FileH));

    knightAttacks[square] = attacks;
  }
}

void Attacks::initKingAttacks() {
  for (int square = SQ_A1; square < 64; ++square) {
    Bitboard sq = 1ull << square;
    Bitboard attacks = eastOne(sq) | westOne(sq);
    sq |= attacks;
    attacks |= northOne(sq) | southOne(sq);

    kingAttacks[square] = attacks;
  }
}

void initWhitePawnAttacks() {
  for (int square = SQ_A2; square < 56; ++square) {
    Bitboard sq = 1ull << square;
    Attacks::pawnAttacks[WHITE][square] = norWestOne(sq) | norEastOne(sq);
  }
}

void initBlackPawnAttacks() {
  for (int square = SQ_H7; square > 7; --square) {
    Bitboard sq = 1ull << square;
    Attacks::pawnAttacks[BLACK][square] = souWestOne(sq) | souEastOne(sq);
  }
}

void Attacks::initPawnAttacks() {
  initWhitePawnAttacks();
  initBlackPawnAttacks();
}

void Attacks::initAttacks() {
  initRookAttacks();
  initBishopAttacks();
  initQueenAttacks();
  initKnightAttacks();
  initKingAttacks();
  initPawnAttacks();
}

Bitboard getRookAttacks(Square sq, Bitboard occupied) {
  Bitboard attacks = Rays::getRayBoard(Rays::North, sq) |
                     Rays::getRayBoard(Rays::South, sq) |
                     Rays::getRayBoard(Rays::West, sq) |
                     Rays::getRayBoard(Rays::East, sq);

  if (Rays::getRayBoard(Rays::North, sq) & occupied) {
    int blocker = bitScanForward(Rays::getRayBoard(Rays::North, sq) & occupied);
    attacks &= ~Rays::getRayBoard(Rays::North, blocker);
  }

  if (Rays::getRayBoard(Rays::East, sq) & occupied) {
    int blocker = bitScanForward(Rays::getRayBoard(Rays::East, sq) & occupied);
    attacks &= ~Rays::getRayBoard(Rays::East, blocker);
  }

  if (Rays::getRayBoard(Rays::South, sq) & occupied) {
    int blocker = bitScanReverse(Rays::getRayBoard(Rays::South, sq) & occupied);
    attacks &= ~Rays::getRayBoard(Rays::South, blocker);
  }

  if (Rays::getRayBoard(Rays::North, sq) & occupied) {
    int blocker = bitScanReverse(Rays::getRayBoard(Rays::West, sq) & occupied);
    attacks &= ~Rays::getRayBoard(Rays::West, blocker);
  }

  return attacks;
}

