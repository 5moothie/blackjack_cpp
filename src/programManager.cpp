#include "raylib.h"
#include "programManager.hpp"

void ProgramManager::start() {

  InitWindow(1200, 800, "BlackJacker");


  while(!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawText("Congrats, first window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }
}