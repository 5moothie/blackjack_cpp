#include <catch2/catch_test_macros.hpp>

#include "card/card.hpp"
#include "card/rank.hpp"
#include "card/suit.hpp"

TEST_CASE("Card gets rank correctly") {
  for(auto rank : ALL_RANKS) {
    Card card(rank, Suit::Spades);

    REQUIRE(card.getRank() == rank);
 }
}

TEST_CASE("Card gets suit correctly") {
  for(auto suit : ALL_SUITS ) {
    Card card(Rank::Five, suit);

    REQUIRE(card.getSuit() == suit);
  }
}

TEST_CASE("Card gets value correctly") {
  
  Card five(Rank::Five, Suit::Spades);
  Card jack(Rank::Jack, Suit::Spades);
  Card king(Rank::King, Suit::Spades);
  Card ace(Rank::Ace, Suit::Spades);



  REQUIRE(five.getValue() == 5);
  REQUIRE(jack.getValue() == 10);
  REQUIRE(king.getValue() == 10);
  REQUIRE(ace.getValue() == 11);
}