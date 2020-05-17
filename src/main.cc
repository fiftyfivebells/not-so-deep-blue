#include "../include/Attacks.h"
#include "../include/Rays.h"
#include "../include/Uci.h"

int main() {

  Rays::init();
  Attacks::initAttacks();

  Uci uci;
  uci.uciCommunication();
}
