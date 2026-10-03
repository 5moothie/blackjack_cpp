#include "blackjack/UI/blackjackRayLibIO.hpp"
#include <raylib.h>

BlackjackRayLibIO::BlackjackRayLibIO(ScreenManager& screenManager): screenManager(screenManager) {}

void BlackjackRayLibIO::draw() const {
  BeginDrawing();

  ClearBackground(BLACK);

  Texture texture = LoadTexture("assets/images/cards/eight_spades.png");
  DrawTexture(texture, 20, 20, WHITE);

  EndDrawing();
}