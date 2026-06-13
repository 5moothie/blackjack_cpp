#pragma once

#include "blackjack/dealer.hpp"
#include "blackjack/player.hpp"
#include "IO/gameDisplay.hpp"
#include "IO/inputTaker.hpp"
#include "gameStates.hpp"

#include <memory>



class Game {
private:
  Dealer dealer;
  Player player;
  Shoe shoe;

  std::unique_ptr<GameDisplay> gameDisplay;
  std::unique_ptr<InputTaker> inputTaker;

  GameState currentState;

public:
  Game(std::unique_ptr<GameDisplay> display, std::unique_ptr<InputTaker> input);

  [[nodiscard]] GameState getGameState() const{return currentState;};

  void update();
  void draw();
};