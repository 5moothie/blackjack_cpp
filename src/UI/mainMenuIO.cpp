#include "UI/mainMenuIO.hpp"
#include "UI/screenManager.hpp"
#include <raylib.h>

MainMenuIO::MainMenuIO(ScreenManager& screenManager): 
    screenManager(screenManager), 
    background("assets/images/main_menu/main_menu_bg.jpg"),
    playButton("assets/images/main_menu/play_btn.jpg"),
    exitButton("assets/images/main_menu/exit_btn.jpg")
{
  update();
}


void MainMenuIO::update() {
  // update size and positions
  const int height = GetScreenHeight();
  const float halfHeight = (float)height/2;
  const int width = GetScreenWidth();
  const float halfWidth = (float)width/2;
  const int spacer = 20;

  background.scaleToContainTexture(width, height);
  background.positionInTheMiddle(width, height);

  playButton.setPositionByMiddle({halfWidth, halfHeight});
  exitButton.setPositionByMiddle({halfWidth, halfHeight + playButton.getHeight() + spacer});

  // check for pressed buttons
  Vector2 mousePos = GetMousePosition();
  bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

  if(playButton.isPressed(mousePos, mousePressed))
    screenManager.setScreen(ProgramScreen::BLACKJACK_GAME);

  if(exitButton.isPressed(mousePos, mousePressed))
    screenManager.requestClose();
}

void MainMenuIO::draw() const {
  BeginDrawing();

  ClearBackground(BLACK);
  
  background.draw();
  playButton.draw();
  exitButton.draw();

  EndDrawing();
}