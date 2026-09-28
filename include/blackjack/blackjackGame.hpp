#pragma once

#include "blackjack/actions.hpp"
#include "blackjack/components/dealer.hpp"
#include "blackjack/components/player.hpp"
#include "blackjack/components/playerHand.hpp"
#include <cstddef>
#include <vector>
#include <vector>


class BlackjackGame {
private:
  Dealer dealer;
  Player player;
  Shoe shoe;

public:
  BlackjackGame();

  // clears dealer's and player's hands, reshuffles if needed
  void resetTable();
  // gives hands to player and dealer
  void setUpRound(std::vector<int> playerBets);
  // check winner and assign money
  void finalizeRound();

  void carryOutPlayerAction(HandActions action);
  [[nodiscard]] const std::vector<PlayerHand>& getPlayerHands() const { return player.getAllHands(); }
  [[nodiscard]] const PlayerHand& getPlayerActiveHand() const { return player.getActiveHandConst(); }
  [[nodiscard]] const size_t getPlayerActiveHandNumber() const { return player.getActiveHandNumber(); }
  [[nodiscard]] long long getPlayerBalance() const noexcept {return player.getBalance(); }
  [[nodiscard]] std::vector<HandActions> getPlayerAvailableActions() const;

  // throws if dealer hand hasn't been played out yet  
  void playOutDealer();
  [[nodiscard]] const Hand& getDealerHand() const { return dealer.getHand(); };
  [[nodiscard]] const Card& getDealerFirstCard() const { return dealer.getFirstCard(); }
};