#include "../include/Search.h"
#include "../include/MoveGenerator.h"

Search::Search() : cb() {}

Search::Search(Chessboard &cb) : cb(cb) {}

Move Search::findBestMove() {

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


}
