#include "blackjack/game.hpp"
#include "IO/actions.hpp"

Game::Game(std::unique_ptr<GameDisplay> display, std::unique_ptr<InputTaker> input)
    : dealer(false), player(1000), shoe(6, 1.5), gameDisplay(std::move(display)), inputTaker(std::move(input))
{}

void Game::run() {
  bool running = true;
  while(running) {
    gameDisplay->showMainMenu();
    MainMenuActions action = inputTaker->getMenuAction();

    switch (action) {
      case MainMenuActions::PLAY:
        play();
        break;
      case MainMenuActions::QUIT:
        running = false;
        break;
    }
  }
}

void Game::play() {
  bool inGame = true;
  while(inGame) {
    int betAmount = bet();

    playHand(betAmount);

    switch(betweenHandsMenu()) {
      case BetweenHandActions::MAIN_MENU:
        inGame = false;
        break;
      case BetweenHandActions::NEXT_HAND:
        break;
    }
  }
}

int Game::bet() {
  gameDisplay->showBettingScreen();
  int betAmount = inputTaker->getBet(player.getBalance());
    
  return betAmount;
}

BetweenHandActions Game::betweenHandsMenu() {
  if(shoe.needsReshuffle())
    shoe.reshuffle();

  gameDisplay->showBetweenHandsMenu();
  BetweenHandActions action = inputTaker->getBetweenHandsAction();
  return action;
}

void Game::playHand(int bet) {
  player.playNewHand(bet, shoe);
  dealer.newHand(shoe);

  gameDisplay->showTable();

  while(player.hasActiveHand()) {
    if(player.getActiveHandConst().isBlackjack()) {
      player.activateNextHand(); 
      continue;
    }
    
    gameDisplay->showTable();
    HandActions action = inputTaker->getHandAction();
    
    switch(action) {
      case HandActions::HIT:
        player.hitActiveHand(shoe);
        break;
      case HandActions::STAND:
        player.standActiveHand();
        break;
      case HandActions::DOUBLE:
        player.doubleActiveHand(shoe);
        break;
      case HandActions::SPLIT:
        player.splitActiveHand(shoe);
        break;
    }
  }

  dealer.playOutHand(shoe);
  gameDisplay->showTable();

  player.settleHands(dealer.getHand());
  player.clearHands();
  dealer.clearHand();
}