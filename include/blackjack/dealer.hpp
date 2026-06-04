#include "blackjack/hand.hpp"
#include "blackjack/shoe.hpp"

#include<optional>

class Dealer{
private:
  std::optional<Hand> hand;
  bool hitOnSoft17;
  
  [[nodiscard]] bool shouldDrawCard() const noexcept;

public:
  Dealer(bool hitOnSoft17): hitOnSoft17(hitOnSoft17) {}

  [[nodiscard]] bool hasHand() const noexcept {return hand.has_value();}
  [[nodiscard]] const Hand& getHand() const;
  [[nodiscard]] const Card& getFirstCard() const;

  [[nodiscard]] bool isBust() const;


  void playOutHand(Shoe& shoe);
  void newHand(Shoe& shoe) { hand.emplace(0, shoe.getCard(), shoe.getCard()); }
};