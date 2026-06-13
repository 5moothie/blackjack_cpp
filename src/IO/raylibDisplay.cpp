#include "IO/raylibDisplay.hpp"

void RaylibDisplay::showMainMenu() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerY = screenHeight / 2;

    const char* title = "BLACKJACK";
    int titleWidth = MeasureText(title, 40);
    DrawText(title, (screenWidth - titleWidth) / 2, centerY - 100, 40, GOLD);

    const char* playText = "Press P, to play";
    int playWidth = MeasureText(playText, 20);
    DrawText(playText, (screenWidth - playWidth) / 2, centerY + 20, 20, RAYWHITE);

    const char* quitText = "Press Q, to quit";
    int quitWidth = MeasureText(quitText, 20);
    DrawText(quitText, (screenWidth - quitWidth) / 2, centerY + 70, 20, RAYWHITE);
}

void RaylibDisplay::showBettingScreen(const Player& player, int currentBet, const std::string& errorMsg) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerY = screenHeight / 2;

    const char* title = "BETTING:";
    int titleWidth = MeasureText(title, 40);
    DrawText(title, (screenWidth - titleWidth) / 2, centerY - 150, 40, YELLOW);

    const char* balanceText = TextFormat("YOUR BALANCE: %d", player.getBalance());
    int balanceWidth = MeasureText(balanceText, 20);
    DrawText(balanceText, (screenWidth - balanceWidth) / 2, centerY - 50, 20, RAYWHITE);

    const char* betText = TextFormat("CURRENT BET: %d", currentBet);
    int betWidth = MeasureText(betText, 30);
    DrawText(betText, (screenWidth - betWidth) / 2, centerY, 30, GREEN);

    const char* instruction = "ENTER TO SUBMIT BET";
    int instructionWidth = MeasureText(instruction, 15);
    DrawText(instruction, (screenWidth - instructionWidth) / 2, centerY + 60, 15, LIGHTGRAY);

    if (!errorMsg.empty()) {
        int errorWidth = MeasureText(errorMsg.c_str(), 20);
        DrawText(errorMsg.c_str(), (screenWidth - errorWidth) / 2, centerY + 110, 20, RED);
    }
}

void RaylibDisplay::showTable(const Dealer& dealer, const Player& player) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char* title = "TABLE";
    int titleWidth = MeasureText(title, 20);
    DrawText(title, (screenWidth - titleWidth) / 2, 20, 20, LIGHTGRAY);

    std::string actionsText = "H - Hit | S - Stand";
    if (player.hasActiveHand()) {
        if (player.canDoubleActiveHand()) {
            actionsText += " | D - Double";
        }
        if (player.canSplitActiveHand()) {
            actionsText += " | P - Split";
        }
    }
    int actionsWidth = MeasureText(actionsText.c_str(), 20);
    DrawText(actionsText.c_str(), (screenWidth - actionsWidth) / 2, screenHeight - 50, 20, RAYWHITE);

    // DEALER
    DrawText("DEALER:", 100, 80, 20, RED);
    int startX = 100;
    int startY = 120;

    for (const auto& card : dealer.getHand().getCards()) {
        Rectangle cardRec = { static_cast<float>(startX), static_cast<float>(startY), 90, 130 };

        DrawRectangleRounded({cardRec.x + 5, cardRec.y + 5, cardRec.width, cardRec.height}, 0.1f, 10, Fade(BLACK, 0.4f));
        DrawRectangleRounded(cardRec, 0.1f, 10, RAYWHITE);
        DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, 2, DARKGRAY);
        DrawText(card.toString().c_str(), startX + 10, startY + 15, 18, BLACK);
        startX += 100;
    }

    // PLAYER
    int playerTextY = screenHeight / 2 + 20;
    DrawText(TextFormat("PLAYER (Balance: %d):", player.getBalance()), 100, playerTextY, 20, BLUE);
    startX = 100;
    startY = playerTextY + 50;

    size_t activeHandIndex = player.getAllHands().size() - player.handsLeftToPlay();
    size_t currentHandIndex = 0;

    bool hasSplit = player.getAllHands().size() > 1;

    for (const auto& hand : player.getAllHands()) {
        bool isActiveHand = player.hasActiveHand() && (currentHandIndex == activeHandIndex);
        bool shouldHighlight = isActiveHand && hasSplit;

        if (shouldHighlight) {
            DrawText("PLAYING", startX, startY - 20, 15, GREEN);
        }

        for (const auto& card : hand.getCards()) {
            Rectangle cardRec = { static_cast<float>(startX), static_cast<float>(startY), 90, 130 };

            DrawRectangleRounded({cardRec.x + 5, cardRec.y + 5, cardRec.width, cardRec.height}, 0.1f, 10, Fade(BLACK, 0.4f));
            DrawRectangleRounded(cardRec, 0.1f, 10, RAYWHITE);

            Color borderColor = shouldHighlight ? GREEN : DARKGRAY;
            int borderWidth = shouldHighlight ? 4 : 2;
            DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, borderWidth, borderColor);

            DrawText(card.toString().c_str(), startX + 10, startY + 15, 18, BLACK);
            startX += 100;
        }
        startX += 40;
        currentHandIndex++;
    }
}

void RaylibDisplay::showHandResults(const Dealer& dealer, const Player& player) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char* title = "RESULTS";
    int titleWidth = MeasureText(title, 40);
    DrawText(title, (screenWidth - titleWidth) / 2, 20, 40, YELLOW);

    // DEALER
    DrawText("DEALER:", 100, 80, 20, RED);
    int startX = 100;
    int startY = 120;

    for (const auto& card : dealer.getHand().getCards()) {
        Rectangle cardRec = { static_cast<float>(startX), static_cast<float>(startY), 90, 130 };
        DrawRectangleRounded({cardRec.x + 5, cardRec.y + 5, cardRec.width, cardRec.height}, 0.1f, 10, Fade(BLACK, 0.4f));
        DrawRectangleRounded(cardRec, 0.1f, 10, RAYWHITE);
        DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, 2, DARKGRAY);
        DrawText(card.toString().c_str(), startX + 10, startY + 15, 18, BLACK);

        startX += 100;
    }

    // PLAYER
    int playerTextY = screenHeight / 2 + 20;
    DrawText(TextFormat("PLAYER (Balance: %d):", player.getBalance()), 100, playerTextY, 20, BLUE);
    startX = 100;
    startY = playerTextY + 50;

    const Hand& dealersHand = dealer.getHand();
    for (const auto& hand : player.getAllHands()) {
        int handStartX = startX;
        for (const auto& card : hand.getCards()) {
            Rectangle cardRec = { static_cast<float>(startX), static_cast<float>(startY), 90, 130 };
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

    if (player.getBalance() <= 0) {
        const char* overText = "GAME OVER! YOU ARE BROKE!";
        int overWidth = MeasureText(overText, 20);
        DrawText(overText, (screenWidth - overWidth) / 2, screenHeight - 100, 20, RED);

        const char* menuText = "M - Main Menu";
        int menuWidth = MeasureText(menuText, 20);
        DrawText(menuText, (screenWidth - menuWidth) / 2, screenHeight - 50, 20, LIGHTGRAY);
    } else {
        const char* nextText = "N - Next Hand  |  M - Main Menu";
        int nextWidth = MeasureText(nextText, 20);
        DrawText(nextText, (screenWidth - nextWidth) / 2, screenHeight - 50, 20, LIGHTGRAY);
    }
}