#ifndef UCI_H
#define UCI_H

#include "Search.h"
#include "Chessboard.h"
#include <sstream>
#include <thread>

class Uci {
 public:
  Uci();

  void uciCommunication();
  void engineInfo();
  void setOption(std::istringstream &);
  void inputIsReady();
  void startNewGame();
  void setPosition(std::istringstream &);
  void go(std::istringstream &);
  void getBestMove();

 private:
  Chessboard *cb;
};

#endif
