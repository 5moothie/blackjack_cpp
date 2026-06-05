#include <iostream>
#include<windows.h>
#include <memory>
#include "blackjack/game.hpp"
#include "IO/inputTaker.hpp"
#include "IO/gameDisplay.hpp"
#include "IO/consoleInputTaker.hpp"
#include "IO/consoleDisplay.hpp"

/*
TODOS:
- Player
- Dealer

- Game

- GameDisplay
*/

int main() {
  SetConsoleOutputCP(65001);

  std::unique_ptr<GameDisplay> gameDisplay = std::make_unique<ConsoleDisplay>();
  std::unique_ptr<InputTaker> inputTaker = std::make_unique<ConsoleInputTaker>();

  Game game(std::move(gameDisplay), std::move(inputTaker));
  
  game.run();
}