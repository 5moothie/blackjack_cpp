#include "IO/raylibDisplay.hpp"
#include "raylib.h"
#include <unordered_map>
#include <string>
#include <algorithm>

constexpr float BASE_WIDTH = 1200.0f;
constexpr float BASE_HEIGHT = 800.0f;

static float getUIScale() {
    float scaleX = static_cast<float>(GetScreenWidth()) / BASE_WIDTH;
    float scaleY = static_cast<float>(GetScreenHeight()) / BASE_HEIGHT;
    return std::min(scaleX, scaleY);
}

static std::unordered_map<std::string, Texture2D> textureCache;

static Texture2D getCachedTexture(const std::string& path) {
    if (textureCache.find(path) == textureCache.end()) {
        textureCache[path] = LoadTexture(path.c_str());
    }
    return textureCache[path];
}

void RaylibDisplay::showMainMenu() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float scale = getUIScale();
    int centerY = screenHeight / 2;

    const char* title = "BLACKJACK";
    int titleSize = std::max(1, static_cast<int>(40 * scale));
    int titleWidth = MeasureText(title, titleSize);
    DrawText(title, (screenWidth - titleWidth) / 2, centerY - static_cast<int>(100 * scale), titleSize, GOLD);

    const char* playText = "Press P, to play";
    int playSize = std::max(1, static_cast<int>(20 * scale));
    int playWidth = MeasureText(playText, playSize);
    DrawText(playText, (screenWidth - playWidth) / 2, centerY + static_cast<int>(20 * scale), playSize, RAYWHITE);

    const char* quitText = "Press Q, to quit";
    int quitSize = std::max(1, static_cast<int>(20 * scale));
    int quitWidth = MeasureText(quitText, quitSize);
    DrawText(quitText, (screenWidth - quitWidth) / 2, centerY + static_cast<int>(70 * scale), quitSize, RAYWHITE);
}

void RaylibDisplay::showBettingScreen(const Player& player, int currentBet, const std::string& errorMsg) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float scale = getUIScale();
    int centerY = screenHeight / 2;

    const char* title = "BETTING:";
    int titleSize = std::max(1, static_cast<int>(40 * scale));
    int titleWidth = MeasureText(title, titleSize);
    DrawText(title, (screenWidth - titleWidth) / 2, centerY - static_cast<int>(150 * scale), titleSize, YELLOW);

    const char* balanceText = TextFormat("YOUR BALANCE: %d", player.getBalance());
    int balanceSize = std::max(1, static_cast<int>(20 * scale));
    int balanceWidth = MeasureText(balanceText, balanceSize);
    DrawText(balanceText, (screenWidth - balanceWidth) / 2, centerY - static_cast<int>(50 * scale), balanceSize, RAYWHITE);

    const char* betText = TextFormat("CURRENT BET: %d", currentBet);
    int betSize = std::max(1, static_cast<int>(30 * scale));
    int betWidth = MeasureText(betText, betSize);
    DrawText(betText, (screenWidth - betWidth) / 2, centerY, betSize, GREEN);

    const char* instruction = "ENTER TO SUBMIT BET";
    int instructionSize = std::max(1, static_cast<int>(15 * scale));
    int instructionWidth = MeasureText(instruction, instructionSize);
    DrawText(instruction, (screenWidth - instructionWidth) / 2, centerY + static_cast<int>(60 * scale), instructionSize, LIGHTGRAY);

    if (!errorMsg.empty()) {
        int errorSize = std::max(1, static_cast<int>(20 * scale));
        int errorWidth = MeasureText(errorMsg.c_str(), errorSize);
        DrawText(errorMsg.c_str(), (screenWidth - errorWidth) / 2, centerY + static_cast<int>(110 * scale), errorSize, RED);
    }
}

void RaylibDisplay::showTable(const Dealer& dealer, const Player& player, bool revealDealerHand) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float scale = getUIScale();

    const char* title = "TABLE";
    int titleSize = std::max(1, static_cast<int>(20 * scale));
    int titleWidth = MeasureText(title, titleSize);
    DrawText(title, (screenWidth - titleWidth) / 2, static_cast<int>(20 * scale), titleSize, LIGHTGRAY);

    std::string actionsText = "H - Hit | S - Stand";
    if (player.hasActiveHand()) {
        if (player.canDoubleActiveHand()) {
            actionsText += " | D - Double";
        }
        if (player.canSplitActiveHand()) {
            actionsText += " | P - Split";
        }
    }
    int actionsSize = std::max(1, static_cast<int>(20 * scale));
    int actionsWidth = MeasureText(actionsText.c_str(), actionsSize);
    DrawText(actionsText.c_str(), (screenWidth - actionsWidth) / 2, screenHeight - static_cast<int>(50 * scale),
        actionsSize, RAYWHITE);

    DrawText("DEALER:", static_cast<int>(100 * scale), static_cast<int>(80 * scale), titleSize, RED);
    int startX = static_cast<int>(100 * scale);
    int startY = static_cast<int>(120 * scale);
    float cardW = 120 * scale;
    float cardH = 168 * scale;
    float shadowOffset = 5 * scale;
    int spacing = static_cast<int>(135 * scale);
    int borderWidthNorm = std::max(1, static_cast<int>(2 * scale));
    int borderWidthHigh = std::max(2, static_cast<int>(4 * scale));

    size_t dealerCardIndex = 0;
    for (const auto& card : dealer.getHand().getCards()) {
        Rectangle cardRec = { static_cast<float>(startX), static_cast<float>(startY), cardW, cardH };

        DrawRectangleRounded({cardRec.x + shadowOffset, cardRec.y + shadowOffset, cardRec.width, cardRec.height},
            0.1f,
            10, Fade(BLACK, 0.4f));

        if (!revealDealerHand && dealerCardIndex == 0) {
            DrawRectangleRounded(cardRec, 0.1f, 10, DARKBLUE);
            DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, borderWidthNorm, SKYBLUE);
            const char* hiddenText = "?";
            int hiddenTextSize = std::max(1, static_cast<int>(44 * scale));
            int hiddenTextWidth = MeasureText(hiddenText, hiddenTextSize);
            DrawText(hiddenText,
                static_cast<int>(cardRec.x + (cardRec.width - hiddenTextWidth) / 2),
                static_cast<int>(cardRec.y + (cardRec.height - static_cast<float>(hiddenTextSize)) / 2.0f),
                hiddenTextSize,
                RAYWHITE);
        } else {
            Texture2D tex = getCachedTexture(card.toString());
            DrawTexturePro(tex, { 0.0f, 0.0f, static_cast<float>(tex.width), static_cast<float>(tex.height) },
                cardRec, { 0.0f, 0.0f }, 0.0f, WHITE);
            DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, borderWidthNorm, DARKGRAY);
        }

        startX += spacing;
        dealerCardIndex++;
    }

    int playerTextY = screenHeight / 2 + static_cast<int>(20 * scale);
    DrawText(TextFormat("PLAYER (Balance: %d):", player.getBalance()), static_cast<int>(100 * scale), playerTextY, titleSize, BLUE);
    startX = static_cast<int>(100 * scale);
    startY = playerTextY + static_cast<int>(50 * scale);

    size_t activeHandIndex = player.getAllHands().size() - player.handsLeftToPlay();
    size_t currentHandIndex = 0;
    bool hasSplit = player.getAllHands().size() > 1;

    for (const auto& hand : player.getAllHands()) {
        bool isActiveHand = player.hasActiveHand() && (currentHandIndex == activeHandIndex);
        bool shouldHighlight = isActiveHand && hasSplit;

        if (shouldHighlight) {
            DrawText("PLAYING", startX, startY - static_cast<int>(20 * scale), std::max(1, static_cast<int>(15 * scale)), GREEN);
        }

        for (const auto& card : hand.getCards()) {
            Rectangle cardRec = { static_cast<float>(startX), static_cast<float>(startY), cardW, cardH };

            DrawRectangleRounded({cardRec.x + shadowOffset, cardRec.y + shadowOffset, cardRec.width, cardRec.height},
                0.1f,
                10, Fade(BLACK, 0.4f));

            Texture2D tex = getCachedTexture(card.toString());
            DrawTexturePro(tex, { 0.0f, 0.0f, static_cast<float>(tex.width), static_cast<float>(tex.height) },
                cardRec, { 0.0f, 0.0f }, 0.0f, WHITE);

            Color borderColor = shouldHighlight ? GREEN : DARKGRAY;
            int borderWidth = shouldHighlight ? borderWidthHigh : borderWidthNorm;
            DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, borderWidth, borderColor);

            startX += spacing;
        }
        startX += static_cast<int>(50 * scale);
        currentHandIndex++;
    }
}

void RaylibDisplay::showHandResults(const Dealer& dealer, const Player& player) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float scale = getUIScale();

    const char* title = "RESULTS";
    int titleSize = std::max(1, static_cast<int>(40 * scale));
    int titleWidth = MeasureText(title, titleSize);
    DrawText(title, (screenWidth - titleWidth) / 2, static_cast<int>(20 * scale), titleSize, YELLOW);

    int smallTitleSize = std::max(1, static_cast<int>(20 * scale));
    DrawText("DEALER:", static_cast<int>(100 * scale), static_cast<int>(80 * scale), smallTitleSize, RED);

    int startX = static_cast<int>(100 * scale);
    int startY = static_cast<int>(120 * scale);
    float cardW = 120 * scale;
    float cardH = 168 * scale;
    float shadowOffset = 5 * scale;
    int spacing = static_cast<int>(135 * scale);
    int borderWidth = std::max(1, static_cast<int>(2 * scale));

    for (const auto& card : dealer.getHand().getCards()) {
        Rectangle cardRec = { static_cast<float>(startX), static_cast<float>(startY), cardW, cardH };

        DrawRectangleRounded({cardRec.x + shadowOffset, cardRec.y + shadowOffset, cardRec.width, cardRec.height},
            0.1f,
            10, Fade(BLACK, 0.4f));

        Texture2D tex = getCachedTexture(card.toString());
        DrawTexturePro(tex, { 0.0f, 0.0f, static_cast<float>(tex.width), static_cast<float>(tex.height) },
            cardRec, { 0.0f, 0.0f }, 0.0f, WHITE);

        DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, borderWidth, DARKGRAY);

        startX += spacing;
    }

    int playerTextY = screenHeight / 2 + static_cast<int>(20 * scale);
    DrawText(TextFormat("PLAYER (Balance: %d):", player.getBalance()), static_cast<int>(100 * scale), playerTextY, smallTitleSize, BLUE);
    startX = static_cast<int>(100 * scale);
    startY = playerTextY + static_cast<int>(50 * scale);
    int resultYOffset = static_cast<int>(190 * scale);

    const Hand& dealersHand = dealer.getHand();
    for (const auto& hand : player.getAllHands()) {
        int handStartX = startX;
        for (const auto& card : hand.getCards()) {
            Rectangle cardRec = { static_cast<float>(startX), static_cast<float>(startY), cardW, cardH };

            DrawRectangleRounded({cardRec.x + shadowOffset, cardRec.y + shadowOffset, cardRec.width, cardRec.height},
                0.1f,
                10, Fade(BLACK, 0.4f));

            Texture2D tex = getCachedTexture(card.toString());
            DrawTexturePro(tex, { 0.0f, 0.0f, static_cast<float>(tex.width), static_cast<float>(tex.height) },
                cardRec, { 0.0f, 0.0f }, 0.0f, WHITE);

            DrawRectangleRoundedLinesEx(cardRec, 0.1f, 10, borderWidth, DARKGRAY);

            startX += spacing;
        }

        if (hand.isBust()) {
            DrawText("BUST!", handStartX, startY + resultYOffset, smallTitleSize, RED);
        }
        else if (hand.isBlackjack()) {
            if (dealersHand.isBlackjack()) {
                DrawText("PUSH (Tie)", handStartX, startY + resultYOffset, smallTitleSize, GRAY);
            } else {
                DrawText("BLACKJACK!", handStartX, startY + resultYOffset, smallTitleSize, GOLD);
            }
        }
        else if (dealersHand.isBlackjack()) {
            DrawText("LOST", handStartX, startY + resultYOffset, smallTitleSize, RED);
        }
        else if (dealersHand.isBust() || hand.getValue() > dealersHand.getValue()) {
            DrawText("WON!", handStartX, startY + resultYOffset, smallTitleSize, GREEN);
        }
        else if (hand.getValue() < dealersHand.getValue()) {
            DrawText("LOST", handStartX, startY + resultYOffset, smallTitleSize, RED);
        }
        else {
            DrawText("PUSH", handStartX, startY + resultYOffset, smallTitleSize, GRAY);
        }

        startX += static_cast<int>(50 * scale);
    }

    if (player.getBalance() <= 0) {
        const char* overText = "GAME OVER! YOU ARE BROKE!";
        int overWidth = MeasureText(overText, smallTitleSize);
        DrawText(overText, (screenWidth - overWidth) / 2, screenHeight - static_cast<int>(100 * scale), smallTitleSize, RED);

        const char* menuText = "M - Main Menu";
        int menuWidth = MeasureText(menuText, smallTitleSize);
        DrawText(menuText, (screenWidth - menuWidth) / 2, screenHeight - static_cast<int>(50 * scale), smallTitleSize, LIGHTGRAY);
    } else {
        const char* nextText = "N - Next Hand  |  M - Main Menu";
        int nextWidth = MeasureText(nextText, smallTitleSize);
        DrawText(nextText, (screenWidth - nextWidth) / 2, screenHeight - static_cast<int>(50 * scale), smallTitleSize, LIGHTGRAY);
    }
}