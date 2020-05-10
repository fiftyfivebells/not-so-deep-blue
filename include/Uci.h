#ifndef UCI_H
#define UCI_H

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
