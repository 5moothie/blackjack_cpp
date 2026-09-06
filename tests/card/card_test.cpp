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

TEST_CASE("Numbered cards get values correctly") {
  Card two(Rank::Two, Suit::Spades);
  Card five(Rank::Five, Suit::Spades);
  Card seven(Rank::Seven, Suit::Spades);
  Card ten(Rank::Ten, Suit::Spades);

  

  REQUIRE(two.getValue() == 2);
  REQUIRE(five.getValue() == 5);
  REQUIRE(seven.getValue() == 7);
  REQUIRE(ten.getValue() == 10);
}

TEST_CASE("Face cards get values correctly") {
  Card jack(Rank::Jack, Suit::Spades);
  Card queen(Rank::Queen, Suit::Spades);
  Card king(Rank::King, Suit::Spades);

  

  REQUIRE(jack.getValue() == 10);
  REQUIRE(queen.getValue() == 10);
  REQUIRE(king.getValue() == 10);
}

TEST_CASE("Ace gets value correctly") {
  Card ace(Rank::Ace, Suit::Spades);

  REQUIRE(ace.getValue() == 11);
}