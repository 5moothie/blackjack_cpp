#include <iostream>
#include <memory>
#include "blackjack/game.hpp"
#include "IO/inputTaker.hpp"
#include "IO/gameDisplay.hpp"
#include "IO/consoleInputTaker.hpp"
#include "IO/consoleDisplay.hpp"
#include "raylib.h"
#include "IO/raylibDisplay.hpp"

/*
TODOS:
- Raylib frontend
- tests for backend components
*/

int main() {
  //SetConsoleOutputCP(65001);

  //std::unique_ptr<GameDisplay> gameDisplay = std::make_unique<ConsoleDisplay>();
  //std::unique_ptr<InputTaker> inputTaker = std::make_unique<ConsoleInputTaker>();

  //Game game(std::move(gameDisplay), std::move(inputTaker));
  
  //game.run();

  InitWindow(800, 600, "Blackjack");
  SetTargetFPS(60);

  RaylibDisplay display;

  Player dummyPlayer(1000);
  Dealer dummyDealer(false);

  int testScreen = 0;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE)) {
      if (testScreen == 0) testScreen = 1;
      else testScreen = 0;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    //temporary
    if (testScreen == 0) {
      display.showMainMenu();
    } else if (testScreen == 1) {
      display.showTable(dummyDealer, dummyPlayer);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}