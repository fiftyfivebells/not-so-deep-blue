#include "../include/Uci.h"

Uci::Uci() {}

void Uci::uciCommunication() {
  std::string line;
  std::string entry;

  while (std::getline(std::cin, line)) {
    std::istringstream input(line);
    input >> entry;

    if (entry == "uci")
      engineInfo();
    else if (entry == "setoption")
      setOption(input);
    else if (entry == "ucinewgame")
      startNewGame();
    else if (entry == "isready")
      std::cout << "readyok" << std::endl;
    else if (entry == "position")
      setPosition(input);
    else if (entry == "go")
      go(input);
    else if (entry == "stop")
      break;
    else if (entry == "quit")
      break;
  }
}

void Uci::engineInfo() {
  std::cout << "id name Not So Deep Blue" << std::endl;
  std::cout << "id author Stephen Bell" << std::endl;

  std::cout << "uciok" << std::endl;
}

void Uci::startNewGame() {
  cb->setToFenString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

