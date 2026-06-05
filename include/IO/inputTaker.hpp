#pragma once
#include "IO/actions.hpp"


class InputTaker {
public:
  virtual ~InputTaker() = default;

  virtual int getBet(int balance) = 0;
  virtual MainMenuActions getMenuAction() = 0;
  virtual BetweenHandActions getBetweenHandsAction() = 0;
  virtual HandActions getHandAction() = 0;
};