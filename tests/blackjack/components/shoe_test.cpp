#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

#include "blackjack/components/shoe.hpp"

TEST_CASE("Fresh shoe does not need reshuffle") {
  Shoe shoe(6, 1.0f);

  REQUIRE_FALSE(shoe.needsReshuffle());
}

TEST_CASE("Can draw card from fresh shoe") {
  Shoe shoe(6, 1.0f);

  REQUIRE_NOTHROW(shoe.getCard());
}

TEST_CASE("There is correct number of cards in the shoe.") {
  Shoe sixDeck(6, 1.0);
  Shoe fourDeck(4, 1.0);

  for(int i = 0; i<6*52; i++)
    (void)sixDeck.getCard();

  for(int i = 0; i<4*52; i++)
    (void)fourDeck.getCard();

  REQUIRE_THROWS(fourDeck.getCard());
  REQUIRE_THROWS(sixDeck.getCard());
}

TEST_CASE("Constructor throws when cutCard >= amount of decks in the shoe.") {
  REQUIRE_THROWS_AS(Shoe(6, 6.1), std::invalid_argument);
}

TEST_CASE("Constructor throws when cutCard is < 0") {
  REQUIRE_THROWS_AS(Shoe(6, -1), std::invalid_argument);
}

TEST_CASE("Constructor throws when the number of decks is below 1") {
  REQUIRE_THROWS_AS(Shoe(0, 0), std::invalid_argument);
}

TEST_CASE("getCard throws on empty Shoe") {
  Shoe shoe(1, .5);

  for(int i = 0; i < 52; ++i)
    (void) shoe.getCard();

  REQUIRE_THROWS(shoe.getCard());
}

TEST_CASE("Reshuffle resets shoe state") {
  Shoe shoe(1, 0.5f);

  while(!shoe.needsReshuffle())
  {
    (void)shoe.getCard();
  }

  shoe.reshuffle();

  REQUIRE_FALSE(shoe.needsReshuffle());
}

TEST_CASE("Reshuffle resets shoe to the right amount of cards") {
  Shoe sixDeck(6, 1.0);
  Shoe fourDeck(4, 1.0);

  for(int i = 0; i<6*52; i++)
    (void)sixDeck.getCard();

  for(int i = 0; i<4*52; i++)
    (void)fourDeck.getCard();

  sixDeck.reshuffle();
  fourDeck.reshuffle();

  for(int i = 0; i<6*52; i++)
    (void)sixDeck.getCard();

  for(int i = 0; i<4*52; i++)
    (void)fourDeck.getCard();

  REQUIRE_THROWS(fourDeck.getCard());
  REQUIRE_THROWS(sixDeck.getCard());
}

TEST_CASE("NeedsReshuffle returns false before cut card") {
  Shoe shoe(2, 0.5f);

  constexpr int cardsBeforeCut = 52 * (2 - 0.5);
  for(int i = 0; i < cardsBeforeCut; ++i)
  {
    REQUIRE(!shoe.needsReshuffle());
    (void) shoe.getCard();
  }
}

TEST_CASE("NeedsReshuffle returns true after cut card") {
  Shoe shoe(2, 0.5f);

  constexpr int cardsBeforeCut = 52 * (2 - 0.5);
  for(int i = 0; i < cardsBeforeCut; ++i)
  {
    (void) shoe.getCard();
  }
  (void)shoe.getCard();

  for(int i = 0; i < 10; ++i) {
    REQUIRE(shoe.needsReshuffle());
    (void)shoe.getCard();
  }
}