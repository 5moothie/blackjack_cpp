#include "blackjack/blackjackGame.hpp"
#include "blackjack/actions.hpp"
#include <stdexcept>
#include <vector>


BlackjackGame::BlackjackGame(): dealer(false), player(1000), shoe(6, 1.5f) {}


void BlackjackGame::carryOutPlayerAction(HandActions action) {
  switch (action) {
    case HandActions::HIT:
      player.hitActiveHand(shoe);
      break;

    case HandActions::STAND:
      player.standActiveHand();
      break;

    case HandActions::SPLIT:
      player.splitActiveHand(shoe);
      break;
    
    case HandActions::DOUBLE:
      player.splitActiveHand(shoe);
      break;
  }
}

std::vector<HandActions> BlackjackGame::getPlayerAvailableActions() const {
  if(!player.hasActiveHand())
    throw std::runtime_error("The player does not have active hand, therefore you can't get his actions");

  std::vector<HandActions> handActions = {HandActions::STAND, HandActions::HIT};
  
  if(player.canDoubleActiveHand())
    handActions.push_back(HandActions::DOUBLE);

  if(player.canSplitActiveHand())
    handActions.push_back(HandActions::SPLIT);

  return handActions;
}


void BlackjackGame::playOutDealer() {
  if(player.hasActiveHand())
    throw std::runtime_error("Player hasn't finished his turn.");

  dealer.playOutHand(shoe);
}

void BlackjackGame::resetTable() {
  if(shoe.needsReshuffle())
    shoe.reshuffle();

  player.clearHands();
  dealer.clearHand();
}

void BlackjackGame::setUpRound(std::vector<int> playerBets) {
  if(player.hasActiveHand() || dealer.hasHand())
    throw std::runtime_error("Initializing new round while one is still in play.");

  if(playerBets.size() < 0 || playerBets.size() > 4) 
    throw std::runtime_error("Player has to have at least one and at most four hands.");
  
  for(int bet : playerBets)
    player.addHand(bet, shoe);
}

void BlackjackGame::finalizeRound() {
  player.settleHands(dealer.getHand());
}