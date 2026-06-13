#pragma once
#include "IO/inputTaker.hpp"
#include "raylib.h"

class RaylibInputTaker : public InputTaker {
private:
    int currentBetInput=0;
    std::string betErrorMsg;

public:
    MainMenuActions getMenuAction() override;
    int getBet(const Player& player) override;
    BetweenHandActions getBetweenHandsAction(const Player& player) override;
    HandActions getHandAction(const Player& player) override;

    [[nodiscard]] int getCurrentBetInput() const { return currentBetInput; }
    [[nodiscard]] std::string getErrorMessage() const { return betErrorMsg; }
};