#include "../include/Attacks.h"

Bitboard Attacks::rookAttacks[64];
Bitboard Attacks::bishopAttacks[64];
Bitboard Attacks::queenAttacks[64];
Bitboard Attacks::knightAttacks[64];
Bitboard Attacks::kingAttacks[64];

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

void Attacks::initAttacks() {
  initRookAttacks();
  initBishopAttacks();
  initQueenAttacks();
  initKnightAttacks();
  initKingAttacks();
}
