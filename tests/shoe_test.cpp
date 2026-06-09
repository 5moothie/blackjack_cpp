#include <catch2/catch_test_macros.hpp>

#include "blackjack/shoe.hpp"

TEST_CASE("Fresh shoe does not need reshuffle")
{
  Shoe shoe(6, 1.0f);

  REQUIRE_FALSE(shoe.needsReshuffle());
}

TEST_CASE("Can draw card from fresh shoe")
{
  Shoe shoe(6, 1.0f);

  REQUIRE_NOTHROW(shoe.getCard());
}

TEST_CASE("Reshuffle resets shoe state")
{
  Shoe shoe(1, 0.5f);

  while(!shoe.needsReshuffle())
  {
    (void)shoe.getCard();
  }

  shoe.reshuffle();

  REQUIRE_FALSE(shoe.needsReshuffle());
}

TEST_CASE("Shoe eventually requires reshuffle")
{
  Shoe shoe(1, 0.5f);

  bool reachedCutCard = false;

  for(int i = 0; i < 52; ++i)
  {
    (void)shoe.getCard();

    if(shoe.needsReshuffle())
    {
      reachedCutCard = true;
      break;
    }
  }

  REQUIRE(reachedCutCard);
}