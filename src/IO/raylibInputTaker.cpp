#include "IO/raylibInputTaker.hpp"

MainMenuActions RaylibInputTaker::getMenuAction() {
    if (IsKeyPressed(KEY_P)) return MainMenuActions::PLAY;
    if (IsKeyPressed(KEY_Q)) return MainMenuActions::QUIT;
    
    return MainMenuActions::NONE; 
}

int RaylibInputTaker::getBet(const Player& player) {
    if (IsKeyPressed(KEY_ENTER)) return 10;
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
    
    return HandActions::NONE;
}