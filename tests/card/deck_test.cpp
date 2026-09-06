#include <catch2/catch_test_macros.hpp>

#include "card/deck.hpp"
#include "card/suit.hpp"
#include <exception>
#include <set>
#include <stdexcept>

TEST_CASE("Deck contains 52 cards") {
  Deck deck;

  auto cards = std::move(deck).releaseCards();

  REQUIRE(cards.size() == 52);
}

TEST_CASE("Deck contains every card exactly once") {
  Deck deck;
  auto cards = std::move(deck).releaseCards();

  std::set<std::pair<Rank, Suit>> uniqueCards;

  for(const auto& card : cards)
  {
    uniqueCards.insert({
      card.getRank(),
      card.getSuit()
    });
  }

  REQUIRE(uniqueCards.size() == 52);
}

TEST_CASE("Deck contains 13 cards of each suit") {
  Deck deck;
  auto cards = std::move(deck).releaseCards();

  int hearts = 0;
  int diamonds = 0;
  int clubs = 0;
  int spades = 0;

  for(const auto& card : cards)
  {
    switch(card.getSuit())
    {
      case Suit::Hearts:   hearts++; break;
      case Suit::Diamonds: diamonds++; break;
      case Suit::Clubs:    clubs++; break;
      case Suit::Spades:   spades++; break;
    }
  }

  REQUIRE(hearts == 13);
  REQUIRE(diamonds == 13);
  REQUIRE(clubs == 13);
  REQUIRE(spades == 13);
}

TEST_CASE("Deck throws on second release") {
  Deck deck;

  auto cards = std::move(deck).releaseCards();
  
  REQUIRE_THROWS(std::move(deck).releaseCards());
}