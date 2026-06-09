#include <catch2/catch_test_macros.hpp>

#include "blackjack/hand.hpp"
#include "card/card.hpp"

TEST_CASE("Ace counts as 11 initially") {
  
  Hand hand(0, Card(Rank::Ace, Suit::Spades));

  REQUIRE(hand.getValue() == 11);
}