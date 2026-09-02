#include <catch2/catch_test_macros.hpp>


TEST_CASE("after initialization handsLeftToPlay() = 0") {

}

TEST_CASE("after initialization getBalance returns the constructor balance") {

}

TEST_CASE("after initialization getAllHands returns an empty collection") {

}

TEST_CASE("initialization with zero balance succeeds") {

}

TEST_CASE("initialization with negative balance throws") {

}

TEST_CASE("getActiveHandConst throws when called with no activeHand") {

}

TEST_CASE("activateNextHand activates next hand with 3 hands") {

}

TEST_CASE("activateNextHand does nothing when no remaining hands (handsLeftToPlay doesn't underflow)") {

}

TEST_CASE("after initialization hasActiveHand returns false") {

}

TEST_CASE("hasActiveHand returns true when a active hand exists") {

}

TEST_CASE("hasActiveHand returns false when all hands finished") {

}

TEST_CASE("handsLeftToPlay correctly returns amount of hands remaining for play (including active)") {

}

TEST_CASE("canDoubleActiveHand returns true when hand is 2 cards and wasn't split before") {

}

TEST_CASE("canDoubleActiveHand returns false after splitting") {

}

TEST_CASE("canDoubleActiveHand returns false after hitting") {

}

TEST_CASE("canDoubleActiveHand returns false when the supplied balance is insufficient") {

}

TEST_CASE("canSplitActiveHand returns true when hand has 2 of the value cards") {

}

TEST_CASE("canSplitActiveHand returns false after hitting") {

}

TEST_CASE("canSplitActiveHand returns false when hand consists of 2 different value cards") {

}

TEST_CASE("canSplitActiveHand returns false when the supplied balance is insufficient") {

}

TEST_CASE("hitActiveHand adds card to the hand") {

}

TEST_CASE("hitActiveHand activates next hand if it busts after hitting") {

}

TEST_CASE("hitActiveHand activates next hand if hand value goes to 21") {

}

TEST_CASE("hitActiveHand leaves the hand active when its value remains below 21") {

}

TEST_CASE("during hitActiveHand Shoe cards are consumed correctly") {

}

TEST_CASE("doubleActiveHand adds one card to hand if hand can be doubled") {

}

TEST_CASE("doubleActiveHand throws when hand cannot be doubled and leaves the state unchanged") {

}

TEST_CASE("doubleActiveHand throws when the balance is insufficient and leaves the state unchanged") {

}

TEST_CASE("doubleActiveHand actiavtes next hand") {

}

TEST_CASE("doubleActiveHand doubles the bet on the hand") {

}

TEST_CASE("doubleActiveHand decreases the balance by original bet") {

}

TEST_CASE("standActiveHand leaves hand and balance unchanged") {

}

TEST_CASE("standActiveHand activates next hand") {

}

TEST_CASE("splitActiveHand splits cards and draws one card for each of them") {

}

TEST_CASE("after splitActiveHand active hand remains on the original hand") {

}

TEST_CASE("splitActiveHand throws when hand is not splittable and leaves the state unchanged") {

}

TEST_CASE("splitActiveHand decreases balance by original bet") {

}

TEST_CASE("both hands cannot be treated as blackjack after a splitActiveHand") {

}

TEST_CASE("settleHands throws when there are still active hands") {

}

TEST_CASE("settleHands leaves balance unchanged when a regular player hand loses") {

}

TEST_CASE("settleHands returns the bet when a regular player hand ties the dealer") {

}

TEST_CASE("settleHands leaves a busted player hand's bet lost") {

}

TEST_CASE("settleHands pays even money when a regular player hand beats the dealer") {

}

TEST_CASE("settleHands keeps the wager when the dealer beats a regular player hand") {

}

TEST_CASE("settleHands pays 3:2 plus the original wager when the player has blackjack and the dealer does not") {

}

TEST_CASE("settleHands returns the original wager when both the player and dealer have blackjack") {

}

TEST_CASE("settleHands keeps both wagers lost when both the player and dealer bust") {

}

TEST_CASE("clearHands removes all hands") {

}

TEST_CASE("clearHands throws if there is an active hand") {

}

TEST_CASE("clearHands preserves balance") {

}

TEST_CASE("after clearHands the player can add a new hand") {

}

TEST_CASE("addHand adds hand to the end") {

}

TEST_CASE("addHand throws when balance is not sufficient") {

}

TEST_CASE("addHand when insufficient balance throws and leaves state unchanged") {

}

TEST_CASE("addHand adds hand if the bet is exact available balance") {

}

TEST_CASE("addHand throws on non-positive bet") {

}

TEST_CASE("addHand throws on odd bet") {

}

TEST_CASE("addHand when the shoe runs out of cards leaves balance and hands unchanged") {

}

TEST_CASE("getActiveHandConst throws when there is no active hand") {

}

TEST_CASE("canDoubleActiveHand throws when there is no active hand") {

}

TEST_CASE("canSplitActiveHand throws when there is no active hand") {

}

TEST_CASE("hitActiveHand throws when there is no active hand") {

}

TEST_CASE("doubleActiveHand throws when there is no active hand") {

}

TEST_CASE("standActiveHand throws when there is no active hand") {

}

TEST_CASE("splitActiveHand throws when there is no active hand") {

}

