#include "../include/Chessboard.h"

#include <iostream>
#include <iterator>
#include <sstream>

#include "../include/Attacks.h"

Chessboard::Chessboard() {
  setToFenString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Chessboard::Chessboard(std::string fenString) { setToFenString(fenString); }

Bitboard Chessboard::getAllPieces(Color c) const {
  Bitboard allPieces = EMPTY;

  for (int p = PAWN; p < 6; ++p) allPieces |= pieces[c][p];

  return allPieces;
}

Bitboard Chessboard::getPiecesByType(Color c, PieceType pt) const {
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

bool Chessboard::isColorAttackingSquare(Color c, Square s) const {
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
    case PAWN:
      attacks = getPawnAttacksFromSquare(s, c, sameSide);
      break;
    case ROOK:
      attacks = getRookAttacksFromSquare(s, sameSide);
      break;
    case BISHOP:
      attacks = getBishopAttacksFromSquare(s, sameSide);
      break;
    case KNIGHT:
      attacks = getKnightAttacksFromSquare(s, sameSide);
      break;
    case QUEEN:
      attacks = getQueenAttacksFromSquare(s, sameSide);
      break;
    case KING:
      attacks = getKingAttacksFromSquare(s, sameSide);
      break;
    case NONE:
      attacks = EMPTY;
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

bool Chessboard::isColorInCheck(Color c) const {
  Bitboard king = getPiecesByType(c, KING);
  Square s = (Square)bitScanForward(king);

  Color enemy = (c == WHITE) ? BLACK : WHITE;

  return isColorAttackingSquare(enemy, s);
}

bool Chessboard::canWhiteCastleKS() const {
  if (!(castleAvailability & 0b0001)) return false;

  Bitboard castleSquares = (1ull << SQ_F1) | (1ull << SQ_G1);
  bool notEmpty = castleSquares & getOccupiedSquares();
  bool underAttack = isColorAttackingSquare(BLACK, SQ_F1) ||
                     isColorAttackingSquare(BLACK, SQ_G1);

  return !notEmpty && !underAttack && !isColorInCheck(WHITE);
}

bool Chessboard::canWhiteCastleQS() const {
  if (!(castleAvailability & 0b0010)) return false;

  Bitboard castleSquares = (1ull << SQ_B1) | (1ull << SQ_C1) | (1ull << SQ_D1);
  bool notEmpty = castleSquares & getOccupiedSquares();
  bool underAttack = isColorAttackingSquare(BLACK, SQ_B1) ||
                     isColorAttackingSquare(BLACK, SQ_C1) ||
                     isColorAttackingSquare(BLACK, SQ_D1);

  return !notEmpty && !underAttack && !isColorInCheck(WHITE);
}

bool Chessboard::canBlackCastleKS() const {
  if (!(castleAvailability & 0b0100)) return false;

  Bitboard castleSquares = (1ull << SQ_F8) | (1ull << SQ_G8);
  bool notEmpty = castleSquares & getOccupiedSquares();
  bool underAttack = isColorAttackingSquare(WHITE, SQ_F8) ||
                     isColorAttackingSquare(WHITE, SQ_G8);

  return !notEmpty && !underAttack && !isColorInCheck(BLACK);
}

bool Chessboard::canBlackCastleQS() const {
  if (!(castleAvailability & 0b1000)) return false;

  Bitboard castleSquares = (1ull << SQ_B8) | (1ull << SQ_C8) | (1ull << SQ_D8);
  bool notEmpty = castleSquares & getOccupiedSquares();
  bool underAttack = isColorAttackingSquare(WHITE, SQ_B8) ||
                     isColorAttackingSquare(WHITE, SQ_C8) ||
                     isColorAttackingSquare(WHITE, SQ_D8);

  return !notEmpty && !underAttack && !isColorInCheck(BLACK);
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
  activeSide = entry == "w" ? WHITE : BLACK;

  fenStream >> entry;
  castleAvailability = 0;
  for (char current : entry) {
    switch (current) {
      case 'K':
        castleAvailability |= 0b0001;
        break;
      case 'Q':
        castleAvailability |= 0b0010;
        break;
      case 'k':
        castleAvailability |= 0b0100;
        break;
      case 'q':
        castleAvailability |= 0b1000;
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

void Chessboard::movePiece(Square from, Square to, PieceType pt, Color c) {
  Bitboard moveMask = (1ull << from) | (1ull << to);

  pieces[c][pt] ^= moveMask;
  allPieces[c] ^= moveMask;
  occupiedSquares ^= moveMask;
}

void Chessboard::removePiece(Square s, PieceType pt, Color c) {
  Bitboard squareMask = 1ull << s;

  pieces[c][pt] ^= squareMask;
  allPieces[c] ^= squareMask;
  occupiedSquares ^= squareMask;
}

void Chessboard::addPiece(Square s, PieceType pt, Color c) {
  Bitboard square = 1ull << s;

  pieces[c][pt] |= square;
  allPieces[c] |= square;
  occupiedSquares |= square;
}

void Chessboard::performMove(Move m) {
  Square to = m.getToSquare();
  Square from = m.getFromSquare();
  PieceType pt = m.getPieceType();
  unsigned int flag = m.getFlag();
  PieceType capture;
  PieceType promotion;
  Color enemy = (activeSide == WHITE) ? BLACK : WHITE;

  if (enPassantTarget)
    enPassantTarget = NO_SQ;

  movePiece(from, to, pt, activeSide);

  switch(flag) {
    case Move::QUIET_MOVE:
      break;
    case Move::D_PAWN_PUSH:
      enPassantTarget = (activeSide == WHITE) ? (Square)(from + 8) : (Square)(from - 8);
      break;
    case Move::K_CASTLE:
      if (activeSide == WHITE)
        movePiece(SQ_H1, SQ_F1, ROOK, WHITE);
      else
        movePiece(SQ_H8, SQ_F8, ROOK, BLACK);
      break;
    case Move::Q_CASTLE:
      if (activeSide == WHITE)
        movePiece(SQ_A1, SQ_B1, ROOK, WHITE);
      else
        movePiece(SQ_A8, SQ_B8, ROOK, BLACK);
      break;
    case Move::CAPTURE:
      capture = m.getCapturedPiece();
      removePiece(to, capture, enemy);
      break;
    case Move::EP_CAPTURE:
      if (activeSide == WHITE)
        removePiece((Square)(to - 8), PAWN, BLACK);
      else
        removePiece((Square)(to + 8), PAWN, WHITE);
      break;
    case Move::PROMOTION:
      promotion = m.getPromotionPiece();
      removePiece(to, pt, activeSide);
      addPiece(to, promotion, activeSide);
      break;
    case Move::CAP_PROMOTION:
      promotion = m.getPromotionPiece();
      capture = m.getCapturedPiece();
      removePiece(to, pt, activeSide);
      removePiece(to, capture, enemy);
      addPiece(to, promotion, activeSide);
  }

  if (pt == PAWN || flag == Move::CAPTURE)
    halfMoveClock = 0;
  else
    ++halfMoveClock;

  if (castleAvailability)
    updateCastleAvailability(m);

  activeSide = (activeSide == WHITE) ? BLACK : WHITE;
}
