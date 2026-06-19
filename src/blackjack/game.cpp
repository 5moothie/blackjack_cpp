#include "blackjack/game.hpp"
#include "../../include/blackjack/actions.hpp"

Game::Game(std::unique_ptr<GameDisplay> display, std::unique_ptr<InputTaker> input)
    : dealer(false), player(1000), shoe(6, 1.5), gameDisplay(std::move(display)), inputTaker(std::move(input)), currentState(GameState::MAIN_MENU)
{}

void Game::update() {
    switch (currentState) {

        case GameState::MAIN_MENU: {
            MainMenuActions action = inputTaker->getMenuAction();
            if (action == MainMenuActions::PLAY) {
                if (player.getBalance() <= 0) {
                    player.setBalance(1000);
                }
                currentState = GameState::BETTING;
            } else if (action == MainMenuActions::QUIT) {
                currentState = GameState::EXIT;
            }
            break;
        }

        case GameState::BETTING: {
            int betAmount = inputTaker->getBet(player);
            if (betAmount > 0) {
                player.playNewHand(betAmount, shoe);
                dealer.newHand(shoe);
                dealerTurnPending = false;
                currentState = GameState::PLAYER_TURN;
            }
            break;
        }

        case GameState::PLAYER_TURN: {
            if (!player.hasActiveHand()) {
                this->dealerTurnPending = false;
                currentState = GameState::DEALER_TURN;
                break;
            }

            if (player.getActiveHandConst().isBlackjack()) {
                player.activateNextHand();
                break;
            }

            HandActions action = inputTaker->getHandAction(player);

            if (action != HandActions::NONE) {
                switch(action) {
                    case HandActions::HIT:
                        player.hitActiveHand(shoe);
                        break;
                    case HandActions::STAND:
                        player.standActiveHand();
                        break;
                    case HandActions::DOUBLE:
                        if (player.canDoubleActiveHand()) {
                            player.doubleActiveHand(shoe);
                        }
                        break;
                    case HandActions::SPLIT:
                        if (player.canSplitActiveHand()) {
                            player.splitActiveHand(shoe);
                        }
                        break;
                    default:
                        break;
                }
            }
            break;
        }

        case GameState::DEALER_TURN: {
            if (!this->dealerTurnPending) {
                this->dealerTurnPending = true;
                break;
            }

            dealer.playOutHand(shoe);
            player.settleHands(dealer.getHand());

            this->dealerTurnPending = false;
            currentState = GameState::RESULTS;
            break;
        }

        case GameState::RESULTS: {
            if(shoe.needsReshuffle()) {
                shoe.reshuffle();
            }

            BetweenHandActions action = inputTaker->getBetweenHandsAction(player);

            if (action == BetweenHandActions::NEXT_HAND) {
                if (player.getBalance() > 0) {
                    player.clearHands();
                    dealer.clearHand();
                    this->dealerTurnPending = false;
                    currentState = GameState::BETTING;
                }
            }
            else if (action == BetweenHandActions::MAIN_MENU) {
                player.clearHands();
                dealer.clearHand();
                this->dealerTurnPending = false;
                currentState = GameState::MAIN_MENU;
            }
            break;
        }

        case GameState::EXIT:
            break;
    }
}

void Game::draw() {
    switch (currentState) {
        case GameState::MAIN_MENU:
            gameDisplay->showMainMenu();
            break;

        case GameState::BETTING:
            gameDisplay->showBettingScreen(player, inputTaker->getCurrentBetInput(), inputTaker->getErrorMessage());
            break;

        case GameState::PLAYER_TURN:
        case GameState::DEALER_TURN:
            gameDisplay->showTable(dealer, player, currentState == GameState::DEALER_TURN);
            break;

        case GameState::RESULTS:
            gameDisplay->showHandResults(dealer, player);
            break;

        case GameState::EXIT:
            break;
    }
}