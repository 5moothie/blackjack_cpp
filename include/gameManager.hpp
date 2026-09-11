#pragma once


#include "blackjack/blackjackGame.hpp"
#include "gameScreens.hpp"


class GameManager {
private:
  GameScreen gameScreen;
  BlackjackGame blackjackGame;


  void update();
  void draw();

public:
  void start();
};