#pragma once
class GameDisplay {
public:
  virtual ~GameDisplay() = default;

  virtual void showMainMenu() = 0;
  virtual void showTable() = 0;
  virtual void showBettingScreen() = 0;
  virtual void showBetweenHandsMenu() = 0;
};