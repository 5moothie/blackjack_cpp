#pragma once

#include "blackjack/IO/actions.hpp"
#include "blackjack/components/dealer.hpp"
#include "blackjack/components/player.hpp"
#include "blackjack/components/playerHand.hpp"
#include <vector>


class BlackjackGame {
private:
  Dealer dealer;
  Player player;
  Shoe shoe;

public:
  BlackjackGame();

  void carryOutPlayerAction(HandActions action);
  void playOutDealer();

  [[nodiscard]] const std::vector<PlayerHand>& getPlayerHands() const { return player.getAllHands(); }
  [[nodiscard]] const PlayerHand& getPlayerActiveHand() const { return player.getActiveHandConst(); }
  [[nodiscard]] long long getPlayerBalance() const {return player.getBalance(); }

  // throws if dealer hand hasn't been played out yet
  [[nodiscard]] const Hand& getDealerHand() const { return dealer.getHand(); };
  [[nodiscard]] const Card& getDealerFirstCard() const { return dealer.getFirstCard(); }
  
};