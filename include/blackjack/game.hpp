#pragma once

#include "blackjack/dealer.hpp"
#include "blackjack/player.hpp"
#include "IO/gameDisplay.hpp"
#include "IO/inputTaker.hpp"

#include <memory>


class Game {
private:
  Dealer dealer;
  Player player;
  Shoe shoe;

  std::unique_ptr<GameDisplay> gameDisplay;
  std::unique_ptr<InputTaker> inputTaker;

  void play();
  int bet();
  void playHand(int bet);
  BetweenHandActions betweenHandsMenu();
public:
  Game(std::unique_ptr<GameDisplay> display, std::unique_ptr<InputTaker> input);

  void run();
};