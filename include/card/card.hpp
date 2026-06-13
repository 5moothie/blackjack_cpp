#pragma once

#include "rank.hpp"
#include "suit.hpp"
#include <string>

class Card {
private:
  Rank rank;
  Suit suit;
public:
  Card(Rank rank, Suit suit): rank(rank), suit(suit) {}

  [[nodiscard]] Rank getRank() const noexcept {return rank;}
  [[nodiscard]] Suit getSuit() const noexcept {return suit;}

  [[nodiscard]] int getValue() const noexcept;

  [[nodiscard]] std::string rankToString() const noexcept;
  [[nodiscard]] std::string suitToString() const noexcept;
  [[nodiscard]] std::string toString() const noexcept {return rankToString() + ' ' + suitToString();}
};