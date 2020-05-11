#include "../include/Search.h"
#include "../include/MoveGenerator.h"

Search::Search() : cb() {}

Search::Search(Chessboard &cb) : cb(cb) {}

void Search::findBestMove() {
  int max = std::numeric_limits<int>::min();
  int score;
  MoveGenerator mg(cb);
  mg.generateMoves(cb);
  mg.generateLegalMoves(cb);

  for (auto move : mg.getLegalMoves()) {
    Chessboard temp = cb;
    temp.makeMove(move);

    score = -alphaBeta(temp, std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::max(), 4);

    if (score > max) {
      max = score;
      std::cout << "setting best move to " << move.getMoveNotation()
                << std::endl;
      bestMove = move;
    }
  }

  cb.makeMove(bestMove);
  std::cout << cb.getStringRepresentation() << std::endl;
  std::cout << "bestmove " << bestMove.getMoveNotation() << std::endl;
}

int Search::alphaBeta(Chessboard &cb, int alpha, int beta, int depth) {
  if (depth == 0) return quiesce(cb, alpha, beta);

  int bestScore = std::numeric_limits<int>::min();

  MoveGenerator mg(cb);
  mg.generateMoves(cb);
  mg.generateLegalMoves(cb);

  if (mg.getLegalMoves().size() == 0)
    return (cb.isColorInCheck(cb.getActiveSide()))
               ? -(std::numeric_limits<int>::max())
               : 0;

  for (auto move : mg.getLegalMoves()) {
    Chessboard temp = cb;
    temp.makeMove(move);

    int score = -alphaBeta(temp, -beta, -alpha, depth - 1);

    if (score >= beta) return score;
    if (score > bestScore) {
      bestScore = score;
      if (score > alpha) alpha = score;
    }
  }
  return bestScore;
}

int Search::evaluate(Chessboard &cb) {
  int score = 0;
  Color active = cb.getActiveSide();

  score += (100 * bitCount(cb.getPiecesByType(WHITE, PAWN)));
  score += (320 * bitCount(cb.getPiecesByType(WHITE, KNIGHT)));
  score += (330 * bitCount(cb.getPiecesByType(WHITE, BISHOP)));
  score += (500 * bitCount(cb.getPiecesByType(WHITE, ROOK)));
  score += (900 * bitCount(cb.getPiecesByType(WHITE, QUEEN)));
  score += (20000 * bitCount(cb.getPiecesByType(WHITE, KING)));

  score -= (100 * bitCount(cb.getPiecesByType(BLACK, PAWN)));
  score -= (320 * bitCount(cb.getPiecesByType(BLACK, KNIGHT)));
  score -= (330 * bitCount(cb.getPiecesByType(BLACK, BISHOP)));
  score -= (500 * bitCount(cb.getPiecesByType(BLACK, ROOK)));
  score -= (900 * bitCount(cb.getPiecesByType(BLACK, QUEEN)));
  score -= (20000 * bitCount(cb.getPiecesByType(BLACK, KING)));
  // score *= (bitCount(cb.getAllPieces(WHITE) - cb.getAllPieces(BLACK)));
  score *= (active == WHITE) ? 1 : -1;

  return score;
}


}
