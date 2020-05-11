#ifndef SEARCH_H
#define SEARCH_H

#include "Chessboard.h"

class Search {
 public:
  Search();
  Search(Chessboard &);

  void findBestMove();

  //private:
  Chessboard cb;
  Move bestMove;

  int alphaBeta(Chessboard &, int, int, int);
  int evaluate(Chessboard &);
  int quiesce(Chessboard &, int, int);
};

#endif
