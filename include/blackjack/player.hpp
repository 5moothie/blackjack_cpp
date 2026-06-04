#include "blackjack/hand.hpp"
#include "blackjack/shoe.hpp"

#include<vector>


/*
Since the balance is int and bet is int for simplicity, the bets must be even. F. eg. 10, 20, 50, 100, 200, 500 chips
*/
class Player {
private:
  std::vector<Hand> hands{};
  size_t activeHand;
  int balance; 

  
  Hand& getActiveHand();
public:
  Player(int balance): balance(balance), activeHand(0), hands{} {}

  [[nodiscard]] const Hand& getActiveHand() const;
  void activateNextHand() noexcept {activeHand++;}
  [[nodiscard]] bool hasActiveHand() const noexcept { return handsLeftToPlay() > 0; };
  [[nodiscard]] const std::vector<Hand>& getAllHands() const noexcept { return hands; };
  [[nodiscard]] size_t handsLeftToPlay() const noexcept { return hands.size() - activeHand; }
  [[nodiscard]] int getBalance() const noexcept  { return balance; }

  [[nodiscard]] bool canDoubleActiveHand() const;
  [[nodiscard]] bool canSplitActiveHand() const;

  void hitActiveHand(Shoe& shoe);
  void doubleActiveHand(Shoe& shoe);
  void standActiveHand();
  void splitActiveHand(Shoe& shoe);

  void settleHands(const Hand& dealersHand);
  void clearHands() noexcept;
  void playNewHand(int bet, Shoe& shoe);
};