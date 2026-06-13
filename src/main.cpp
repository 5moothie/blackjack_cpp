#include <iostream>
#include <memory>
#include "blackjack/game.hpp"
#include "IO/inputTaker.hpp"
#include "IO/gameDisplay.hpp"
#include "raylib.h"
#include "IO/raylibDisplay.hpp"
#include "IO/raylibInputTaker.hpp"

/*
TODOS:
- tests for backend components
*/

int main() {
  constexpr int screenWidth = 1200;
  constexpr int screenHeight = 800;
  InitWindow(screenWidth, screenHeight, "Blackjack");
  SetTargetFPS(60);

  std::unique_ptr<GameDisplay> display = std::make_unique<RaylibDisplay>();
  std::unique_ptr<InputTaker> input = std::make_unique<RaylibInputTaker>();

  Game game(std::move(display), std::move(input));

  while (!WindowShouldClose() && game.getGameState() != GameState::EXIT) {
    game.update();

    BeginDrawing();

    ClearBackground(BLACK);
    game.draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}