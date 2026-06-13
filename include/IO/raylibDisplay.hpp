#pragma once
#include "IO/gameDisplay.hpp"
#include "raylib.h"
#include "blackjack/dealer.hpp"
#include "blackjack/player.hpp"

class RaylibDisplay : public GameDisplay {
public:
    void showMainMenu() override;
    void showBettingScreen(const Player& player) override;
    void showTable(const Dealer& dealer, const Player& player) override;
    void showHandResults(const Dealer& dealer, const Player& player) override;
};