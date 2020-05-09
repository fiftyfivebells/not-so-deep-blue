#ifndef UCI_H
#define UCI_H

class Uci {
 public:
  Uci();

  void uciCommunication();
  void inputUci();
  void inputSetOption();
  void inputIsReady();
  void inputNewGame();
  void inputPosition();
  void inputGo();

 private:
};

#endif
