#include "IO/raylibInputTaker.hpp"

MainMenuActions RaylibInputTaker::getMenuAction() {
    if (IsKeyPressed(KEY_P)) return MainMenuActions::PLAY;
    if (IsKeyPressed(KEY_Q)) return MainMenuActions::QUIT;
    
    return MainMenuActions::NONE; 
}

int RaylibInputTaker::getBet(const Player& player) {
    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 48) && (key <= 57)) {
            currentBetInput = currentBetInput * 10 + (key - 48);
            betErrorMsg = "";
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        currentBetInput /= 10;
        betErrorMsg = "";
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (currentBetInput == 0) {
            return 0;
        }

        int balance = player.getBalance();

        if (currentBetInput > balance) {
            betErrorMsg = "Bet can't be more than your current balance, try again";
            currentBetInput = 0;
            return 0;
        }

        if (currentBetInput % 2 != 0) {
            betErrorMsg = "Bet must be an even number, try again";
            currentBetInput = 0;
            return 0;
        }

        int finalBet = currentBetInput;
        currentBetInput = 0;
        betErrorMsg = "";
        return finalBet;
    }
    return 0;
}

BetweenHandActions RaylibInputTaker::getBetweenHandsAction(const Player& player) {
    if (IsKeyPressed(KEY_N)) return BetweenHandActions::NEXT_HAND;
    if (IsKeyPressed(KEY_M)) return BetweenHandActions::MAIN_MENU;
    
    return BetweenHandActions::NONE;
}

HandActions RaylibInputTaker::getHandAction(const Player& player) {
    if (IsKeyPressed(KEY_H)) return HandActions::HIT;
    if (IsKeyPressed(KEY_S)) return HandActions::STAND;
    if (IsKeyPressed(KEY_D)) return HandActions::DOUBLE;
    if (IsKeyPressed(KEY_P)) return HandActions::SPLIT;

    return HandActions::NONE;
}