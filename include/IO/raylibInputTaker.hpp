#pragma once
#include "IO/inputTaker.hpp"
#include "raylib.h"

class RaylibInputTaker : public InputTaker {
public:
    MainMenuActions getMenuAction() override;
    int getBet(const Player& player) override;
    BetweenHandActions getBetweenHandsAction(const Player& player) override;
    HandActions getHandAction(const Player& player) override;
};