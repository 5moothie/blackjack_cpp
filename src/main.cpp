#include <iostream>
#include<windows.h>
#include <memory>
#include "blackjack/game.hpp"
#include "blackjack/IO/inputTaker.hpp"
#include "blackjack/IO/gameDisplay.hpp"
#include "blackjack/IO/consoleInputTaker.hpp"
#include "blackjack/IO/consoleDisplay.hpp"

/*
TODOS:
- Raylib frontend
- tests for backend components
*/

int main() {
  SetConsoleOutputCP(65001);

  std::unique_ptr<GameDisplay> gameDisplay = std::make_unique<ConsoleDisplay>();
  std::unique_ptr<InputTaker> inputTaker = std::make_unique<ConsoleInputTaker>();

  Game game(std::move(gameDisplay), std::move(inputTaker));
  
  game.run();
}