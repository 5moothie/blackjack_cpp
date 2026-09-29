#include "UI/programManager.hpp"
#include "blackjack/UI/blackjackRayLibIO.hpp"
#include "raylib.h"
#include "UI/screenManager.hpp"
#include <memory>

void ProgramManager::start() {

  InitWindow(1200, 800, "BlackJacker");


  while(!WindowShouldClose()) {
    update();
    draw();
  }
}

void ProgramManager::update() {
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
  screenManager(std::make_unique<ScreenManager>()), 
  blackjackIO(std::make_unique<BlackjackRayLibIO>(*screenManager)),
  mainMenuIO(std::make_unique<MainMenuIO>(*screenManager)) {
  
}

