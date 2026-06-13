#include "IO/raylibDisplay.hpp"

void RaylibDisplay::showMainMenu() {
    DrawText("BLACKJACK", 250, 150, 40, GOLD);
    DrawText("Press P, to play", 270, 300, 20, RAYWHITE);
    DrawText("Press Q, to quit", 270, 350, 20, RAYWHITE);
}

void RaylibDisplay::showBettingScreen(const Player& player, int currentBet, const std::string& errorMsg) {
    int screenWidth = GetScreenWidth();

    const char* title = "BETTING:";
    int titleWidth = MeasureText(title, 40);
    DrawText(title, (screenWidth - titleWidth) / 2, 100, 40, YELLOW);

    const char* balanceText = TextFormat("YOUR BALANCE: %d", player.getBalance());
    int balanceWidth = MeasureText(balanceText, 20);
    DrawText(balanceText, (screenWidth - balanceWidth) / 2, 200, 20, RAYWHITE);

    const char* betText = TextFormat("CURRENT BET: %d", currentBet);
    int betWidth = MeasureText(betText, 30);
    DrawText(betText, (screenWidth - betWidth) / 2, 250, 30, GREEN);

    const char* instruction = "ENTER TO SUBMIT BET";
    int instructionWidth = MeasureText(instruction, 15);
    DrawText(instruction, (screenWidth - instructionWidth) / 2, 300, 15, LIGHTGRAY);

    if (!errorMsg.empty()) {
        int errorWidth = MeasureText(errorMsg.c_str(), 20);
        DrawText(errorMsg.c_str(), (screenWidth - errorWidth) / 2, 350, 20, RED);
    }
}

void RaylibDisplay::showTable(const Dealer& dealer, const Player& player) {
    DrawText("TABLE", 250, 20, 20, LIGHTGRAY);

    std::string actionsText="H - Hit | S - Stand";

    if (player.hasActiveHand()) {
        if (player.canDoubleActiveHand()) {
            actionsText += " | D - Double";
        }
        if (player.canSplitActiveHand()) {
            actionsText += " | P - Split";
        }
    }

    int actionsWidth = MeasureText(actionsText.c_str(), 20);
    DrawText(actionsText.c_str(), (GetScreenWidth() - actionsWidth) / 2, 550, 20, RAYWHITE);

    // DEALER
    DrawText("DEALER:", 100, 80, 20, RED);
    int startX = 100;
    int startY = 120;

    for (const auto& card : dealer.getHand().getCards()) {
        Rectangle cardRec = { (float)startX, (float)startY, 90, 130 };
        DrawRectangleRounded({cardRec.x + 5, cardRec.y + 5, cardRec.width, cardRec.height}, 0.1f, 10, Fade(BLACK, 0.4f));
        DrawRectangleRounded(cardRec, 0.1f, 10, RAYWHITE);
        DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, 2, DARKGRAY);
        DrawText(card.toString().c_str(), startX + 10, startY + 15, 18, BLACK);
        startX += 100;
    }

    // PLAYER
    DrawText(TextFormat("PLAYER (Balance: %d):", player.getBalance()), 100, 290, 20, BLUE);
    startX = 100;
    startY = 330;

    for (const auto& hand : player.getAllHands()) {
        for (const auto& card : hand.getCards()) {
            Rectangle cardRec = { (float)startX, (float)startY, 90, 130 };
            DrawRectangleRounded({cardRec.x + 5, cardRec.y + 5, cardRec.width, cardRec.height}, 0.1f, 10, Fade(BLACK, 0.4f));
            DrawRectangleRounded(cardRec, 0.1f, 10, RAYWHITE);
            DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, 2, DARKGRAY);
            DrawText(card.toString().c_str(), startX + 10, startY + 15, 18, BLACK);
            startX += 100;
        }
        startX += 40;
    }
}

void RaylibDisplay::showHandResults(const Dealer& dealer, const Player& player) {
    DrawText("RESULTS", 330, 20, 40, YELLOW);

    // DEALER
    DrawText("DEALER:", 100, 80, 20, RED);
    int startX = 100;
    int startY = 120;

    for (const auto& card : dealer.getHand().getCards()) {
        Rectangle cardRec = { (float)startX, (float)startY, 90, 130 };
        DrawRectangleRounded({cardRec.x + 5, cardRec.y + 5, cardRec.width, cardRec.height}, 0.1f, 10, Fade(BLACK, 0.4f));
        DrawRectangleRounded(cardRec, 0.1f, 10, RAYWHITE);
        DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, 2, DARKGRAY);
        DrawText(card.toString().c_str(), startX + 10, startY + 15, 18, BLACK);

        startX += 100;
    }

    // PLAYER
    DrawText(TextFormat("PLAYER (Balance: %d):", player.getBalance()), 100, 290, 20, BLUE);
    startX = 100;
    startY = 330;

    const Hand& dealersHand = dealer.getHand();
    for (const auto& hand : player.getAllHands()) {
        int handStartX = startX;
        for (const auto& card : hand.getCards()) {
            Rectangle cardRec = { (float)startX, (float)startY, 90, 130 };
            DrawRectangleRounded({cardRec.x + 5, cardRec.y + 5, cardRec.width, cardRec.height}, 0.1f, 10, Fade(BLACK, 0.4f));
            DrawRectangleRounded(cardRec, 0.1f, 10, RAYWHITE);
            DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, 2, DARKGRAY);

            DrawText(card.toString().c_str(), startX + 10, startY + 15, 18, BLACK);
            startX += 100;
        }

        // RESULTS
        if (hand.isBust()) {
            DrawText("BUST!", handStartX, startY + 145, 20, RED);
        }
        else if (hand.isBlackjack()) {
            if (dealersHand.isBlackjack()) {
                DrawText("PUSH (Tie)", handStartX, startY + 145, 20, GRAY);
            } else {
                DrawText("BLACKJACK!", handStartX, startY + 145, 20, GOLD);
            }
        }
        else if (dealersHand.isBlackjack()) {
            DrawText("LOST", handStartX, startY + 145, 20, RED);
        }
        else if (dealersHand.isBust() || hand.getValue() > dealersHand.getValue()) {
            DrawText("WON!", handStartX, startY + 145, 20, GREEN);
        }
        else if (hand.getValue() < dealersHand.getValue()) {
            DrawText("LOST", handStartX, startY + 145, 20, RED);
        }
        else {
            DrawText("PUSH", handStartX, startY + 145, 20, GRAY);
        }

        startX += 40;
    }
    DrawText("N - Next Hand  |  M - Main Menu", 180, 530, 20, LIGHTGRAY);
}