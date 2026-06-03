#include "rank.hpp"
#include "suit.hpp"
#include <string>

class Card {
private:
  Rank rank;
  Suit suit;
public:
  Card(Rank rank, Suit suit): rank(rank), suit(suit) {}

  [[nodiscard]] Rank getRank() noexcept {return rank;}
  [[nodiscard]] Suit getSuit() noexcept {return suit;}

  [[nodiscard]] int getValue() noexcept;

  [[nodiscard]] std::string rankToString() noexcept;
  [[nodiscard]] std::string suitToString() noexcept;
  [[nodiscard]] std::string toString() noexcept {return rankToString() + suitToString();}
};