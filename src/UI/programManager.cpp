#include "UI/programManager.hpp"
#include "blackjack/UI/blackjackRayLibIO.hpp"
#include "raylib.h"
#include "UI/screenManager.hpp"
#include <memory>

void ProgramManager::start() {
  constexpr int width = 1920;
  constexpr int height = 1080;

  InitWindow(width, height, "BlackJacker");
  SetTargetFPS(60);
  SetExitKey(KEY_NULL);

  blackjackIO = std::make_unique<BlackjackRayLibIO>(*screenManager);
  mainMenuIO = std::make_unique<MainMenuIO>(*screenManager);

  while(!screenManager->shouldWindowClose()) {
    update();
    draw();
  }

  mainMenuIO.reset();
  blackjackIO.reset();
  CloseWindow();
}

void ProgramManager::update() {
  if(WindowShouldClose()) // so the program closes on X
    screenManager->requestClose();

  switch(screenManager->getScreen()) {
    case ProgramScreen::MAIN_MENU:
      mainMenuIO->update();
      break;
    
    case ProgramScreen::BLACKJACK_GAME:
      blackjackIO->update();
      break;
  }
}

void ProgramManager::draw() const {
  switch(screenManager->getScreen()) {
    case ProgramScreen::MAIN_MENU:
      mainMenuIO->draw();
      break;
    
    case ProgramScreen::BLACKJACK_GAME:
      blackjackIO->draw();
      break;
  }
}


ProgramManager::ProgramManager(): 
  screenManager(std::make_unique<ScreenManager>()) {
  
}

