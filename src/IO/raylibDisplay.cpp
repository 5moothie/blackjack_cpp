#include "IO/raylibDisplay.hpp"

void RaylibDisplay::showMainMenu() {
    DrawText("BLACKJACK", 250, 150, 40, GOLD);
    DrawText("Press [P], to play", 270, 300, 20, RAYWHITE);
    DrawText("Press [Q], to quit", 270, 350, 20, RAYWHITE);
}

void RaylibDisplay::showBettingScreen(const Player& player) {
    DrawText("BETTING:", 300, 50, 30, YELLOW);
}

void RaylibDisplay::showTable(const Dealer& dealer, const Player& player) {
    DrawText("TABLE (Game in progress...)", 300, 50, 30, LIGHTGRAY);
    DrawText("Press [H] - Hit | [S] - Stand", 250, 500, 20, RAYWHITE);

    DrawRectangle(350, 100, 100, 150, RED);
    DrawText("Dealer", 365, 160, 20, WHITE);

    DrawRectangle(350, 300, 100, 150, BLUE);
    DrawText("Player", 370, 360, 20, WHITE);
}

void RaylibDisplay::showHandResults(const Dealer& dealer, const Player& player) {
    DrawText("RESULT", 300, 200, 30, BLACK);
}