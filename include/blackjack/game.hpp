#pragma once

#include "blackjack/components/dealer.hpp"
#include "blackjack/components/player.hpp"
#include "blackjack/IO/gameDisplay.hpp"
#include "blackjack/IO/inputTaker.hpp"

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