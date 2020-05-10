#ifndef SEARCH_H
#define SEARCH_H

#include "Chessboard.h"

class Search {
 public:
  Search();
  Search(Chessboard &);

  Move findBestMove();

 private:
  Chessboard cb;
};

#endif
