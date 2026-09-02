#pragma once

#include "blackjack/components/playerHand.hpp"
#include "blackjack/components/shoe.hpp"

#include <vector>

// #define int long long  // honorable mention ~ Ula

/*
Since the balance is an integer for simplicity, the bets must be even. F. eg. 10, 20, 50, 100, 200, 500 chips
*/
class Player {
private:
  std::vector<PlayerHand> hands{};
  size_t activeHand;
  long long balance;

  
  PlayerHand& getActiveHand();
public:
  Player(long long balance): balance(balance), activeHand(0), hands{} {}

  [[nodiscard]] const PlayerHand& getActiveHandConst() const;
  // activates next hand, when no more hands - does nothing
  void activateNextHand() noexcept;
  [[nodiscard]] bool hasActiveHand() const noexcept { return handsLeftToPlay() > 0; };
  [[nodiscard]] const std::vector<PlayerHand>& getAllHands() const noexcept { return hands; };
  // hands left to play including active hand
  [[nodiscard]] size_t handsLeftToPlay() const noexcept { return hands.size() - activeHand; }
  [[nodiscard]] long long getBalance() const noexcept  { return balance; }

  [[nodiscard]] bool canDoubleActiveHand() const;
  [[nodiscard]] bool canSplitActiveHand() const;

  void hitActiveHand(Shoe& shoe);
  void doubleActiveHand(Shoe& shoe);
  void standActiveHand();
  void splitActiveHand(Shoe& shoe);

  void settleHands(const Hand& dealersHand);
  void clearHands() noexcept;
  void addHand(long long bet, Shoe& shoe);
};

// activateNextHand activates next hand 
// activateNextHand does nothing when no more hands
// hasActiveHand returns true when a active hand exists
// hasActiveHand returns false when all hands finished
// handsLeftToPlay correctly returns amount of hands remaining for play (including active)
// canDoubleActiveHand returns true when hand is 2 cards and wasn't split before
// canDoubleActiveHand returns false after splitting
// canDoubleActiveHand returns false after hitting
// canSplitActiveHand returns true when hand has 2 of the value cards
// canSplitActiveHand returns false after hitting
// canSplitActiveHand returns false when hand consists of 2 different value cards
// hitActiveHand adds card to the hand
// hitActiveHand activates next hand if it busts after hitting
// doubleActiveHand adds card to hand if hand can be doubled
// doubleActiveHand throws when hand cannot be doubled
// doubleActiveHand actiavtes next hand if went succesfully
// doubleActiveHand doubles the bet on the hand
// standActiveHand does nothing to the hand
// standActiveHand activates next hand
// splitActiveHand splits cards and draws one card for each of them
// splitActiveHand remains on the previously active hand
// splitActiveHand throws when hand is not splittable
// settleHands correctly manipulates player balance when player wins
// settleHands correctly manipulates player balance when dealer wins
// settleHands correctly manipulates player balance when player has blackjack, and dealer doesn't
// settleHands correctly manipulates player balance when player and dealer both have blackjack
// settleHands correctly manipulates player balance when player and dealer both bust
// clearHands removes all hands
// addHand adds hand at the end
// addHand throws when balance is not sufficient