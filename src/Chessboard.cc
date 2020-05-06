#include "../include/Chessboard.h"

#include <iostream>
#include <iterator>
#include <sstream>

#include "../include/Attacks.h"

Chessboard::Chessboard() {
  // pieces[0][0] = PAWN_START & ALL_WHITE_START;
  // pieces[0][1] = ROOK_START & ALL_WHITE_START;
  // pieces[0][2] = KNIGHT_START & ALL_WHITE_START;
  // pieces[0][3] = BISHOP_START & ALL_WHITE_START;
  // pieces[0][4] = QUEEN_START & ALL_WHITE_START;
  // pieces[0][5] = KING_START & ALL_WHITE_START;

  // pieces[1][0] = PAWN_START & ALL_BLACK_START;
  // pieces[1][1] = ROOK_START & ALL_BLACK_START;
  // pieces[1][2] = KNIGHT_START & ALL_BLACK_START;
  // pieces[1][3] = BISHOP_START & ALL_BLACK_START;
  // pieces[1][4] = QUEEN_START & ALL_BLACK_START;
  // pieces[1][5] = KING_START & ALL_BLACK_START;

  // emptySquares = ~(ALL_BLACK_START | ALL_WHITE_START);
  // occupiedSquares = ~emptySquares;

  setToFenString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Chessboard::Chessboard(std::string fenString) { setToFenString(fenString); }

Bitboard Chessboard::getAllPieces(Color c) const {
  Bitboard allPieces = EMPTY;

  for (int p = PAWN; p < 6; ++p) allPieces |= pieces[c][p];

  return allPieces;
}

Bitboard Chessboard::getPiecesByType(Color c, PieceType pt) {
  return pieces[c][pt];
}

Bitboard* Chessboard::getWhitePieces() { return pieces[0]; }

Bitboard* Chessboard::getBlackPieces() { return pieces[1]; }

Bitboard Chessboard::getEmptySquares() const { return emptySquares; }

void Chessboard::setEmptySquares() { emptySquares = ~occupiedSquares; }

Bitboard Chessboard::getOccupiedSquares() const { return occupiedSquares; }

void Chessboard::setOccupiedSquares() {
  occupiedSquares = EMPTY;

  for (int color = WHITE; color <= BLACK; ++color)
    for (int piece = PAWN; piece <= KING; ++piece)
      occupiedSquares |= pieces[color][piece];
}

bool Chessboard::isColorAttackingSquare(Color c, Square s) {
  Bitboard sq = 1ull << s;
  Bitboard occupied = getOccupiedSquares();
  Color opposite = (c == WHITE) ? BLACK : WHITE;

  if (Attacks::getPawnAttacks(s, opposite, getPiecesByType(WHITE, PAWN)))
    return true;
  if (Attacks::getNonSlidingAttacks(KNIGHT, s, getPiecesByType(c, KNIGHT)))
    return true;
  if (Attacks::getNonSlidingAttacks(KING, s, getPiecesByType(c, KING)))
    return true;

  Bitboard bishopsQueens = getPiecesByType(c, BISHOP) | getPiecesByType(c, QUEEN);
  if (Attacks::getSlidingAttacks(BISHOP, s, bishopsQueens))
    return true;

  Bitboard rooksQueens = getPiecesByType(c, ROOK) | getPiecesByType(c, QUEEN);
  if (Attacks::getSlidingAttacks(ROOK, s, rooksQueens))
    return true;

  return false;
}

PieceType Chessboard::getPieceAtSquare(Color c, Square s) const {
  Bitboard square = 1ull << s;

  PieceType piece;

  if (square & pieces[c][PAWN])
    piece = PAWN;
  else if (square & pieces[c][ROOK])
    piece = ROOK;
  else if (square & pieces[c][KNIGHT])
    piece = KNIGHT;
  else if (square & pieces[c][BISHOP])
    piece = BISHOP;
  else if (square & pieces[c][QUEEN])
    piece = QUEEN;
  else if (square & pieces[c][KING])
    piece = KING;
  else
    piece = NONE;
  //    throw((c == WHITE ? std::string("White") : std::string("Black")) + "
  //    piece at square " + std::to_string(boardIndex) + " does not exist.");

  return piece;
}

Bitboard Chessboard::getAttacksFromSquare(Square s, Color c) {
  PieceType pt = getPieceAtSquare(c, s);

  Bitboard sameSide = getAllPieces(c);
  Bitboard attacks;
  switch (pt) {
    case PAWN: attacks = getPawnAttacksFromSquare(s, c, sameSide);
      break;
    case ROOK: attacks = getRookAttacksFromSquare(s, sameSide);
      break;
    case BISHOP: attacks = getBishopAttacksFromSquare(s, sameSide);
      break;
    case KNIGHT: attacks = getKnightAttacksFromSquare(s, sameSide);
      break;
    case QUEEN: attacks = getQueenAttacksFromSquare(s, sameSide);
      break;
    case KING: attacks = getKingAttacksFromSquare(s, sameSide);
      break;
    case NONE: attacks = EMPTY;
      break;
  }
  return attacks;
}

Bitboard Chessboard::getPawnAttacksFromSquare(Square s, Color c, Bitboard friends) {
  return Attacks::getPawnAttacks(s, c, getOccupiedSquares()) & ~friends;
}

Bitboard Chessboard::getRookAttacksFromSquare(Square s, Bitboard friends) {
  return Attacks::getSlidingAttacks(ROOK, s, getOccupiedSquares()) & ~friends;
}

Bitboard Chessboard::getBishopAttacksFromSquare(Square s, Bitboard friends) {
  return Attacks::getSlidingAttacks(BISHOP, s, getOccupiedSquares()) & ~friends;
}

Bitboard Chessboard::getQueenAttacksFromSquare(Square s, Bitboard friends) {
  return Attacks::getSlidingAttacks(QUEEN, s, getOccupiedSquares()) & ~friends;
}

Bitboard Chessboard::getKingAttacksFromSquare(Square s, Bitboard friends) {
  return Attacks::getNonSlidingAttacks(KING, s, getOccupiedSquares()) & ~friends;
}

Bitboard Chessboard::getKnightAttacksFromSquare(Square s, Bitboard friends) {
  return Attacks::getNonSlidingAttacks(KNIGHT, s, getOccupiedSquares()) & ~friends;
}

Square Chessboard::makeSquareFromFen(std::string fen) {
  File f = (File)(fen[0] - 'a');
  Rank r = (Rank)(fen[1] - '0');

  return (Square)((r * 8) + f);
}

void Chessboard::setToFenString(std::string fen) {
  std::istringstream fenStream(fen);
  std::string entry;

  clearBitboards();

  int pos = SQ_A8;

  fenStream >> entry;

  for (char current : entry) {
    switch (current) {
      case 'p':
        pieces[BLACK][PAWN] |= (1ull << pos++);
        break;
      case 'r':
        pieces[BLACK][ROOK] |= (1ull << pos++);
        break;
      case 'n':
        pieces[BLACK][KNIGHT] |= (1ull << pos++);
        break;
      case 'b':
        pieces[BLACK][BISHOP] |= (1ull << pos++);
        break;
      case 'q':
        pieces[BLACK][QUEEN] |= (1ull << pos++);
        break;
      case 'k':
        pieces[BLACK][KING] |= (1ull << pos++);
        break;
      case 'P':
        pieces[WHITE][PAWN] |= (1ull << pos++);
        break;
      case 'R':
        pieces[WHITE][ROOK] |= (1ull << pos++);
        break;
      case 'N':
        pieces[WHITE][KNIGHT] |= (1ull << pos++);
        break;
      case 'B':
        pieces[WHITE][BISHOP] |= (1ull << pos++);
        break;
      case 'Q':
        pieces[WHITE][QUEEN] |= (1ull << pos++);
        break;
      case 'K':
        pieces[WHITE][KING] |= (1ull << pos++);
        break;
      case '/':
        pos -= 16;  // back to the beginning of row, then -8 to next row
        break;
      default:
        pos += static_cast<Bitboard>(current - '0');
    }
  }

  fenStream >> entry;
  sideToMove = entry == "w" ? WHITE : BLACK;

  fenStream >> entry;
  castleAvailability = 0;
  for (char current : entry) {
    switch (current) {
      case 'K': castleAvailability |= 0b0001;
        break;
      case 'Q': castleAvailability |= 0b0010;
        break;
      case 'k': castleAvailability |= 0b0100;
        break;
      case 'q': castleAvailability |= 0b1000;
    }
  }

  fenStream >> entry;
  enPassantTarget = (entry == "-") ? NO_SQ : makeSquareFromFen(entry);

  fenStream >> halfMoveClock;

  setOccupiedSquares();
  setEmptySquares();
}

void Chessboard::clearBitboards() {
  for (int color = WHITE; color <= BLACK; ++color)
    for (int piece = PAWN; piece <= KING; ++piece) pieces[color][piece] = EMPTY;

  occupiedSquares = EMPTY;
  emptySquares = EMPTY;
}
