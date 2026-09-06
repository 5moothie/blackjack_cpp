#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <vector>

#include "blackjack/components/dealer.hpp"
#include "card/card.hpp"
#include "card/rank.hpp"
#include "card/suit.hpp"
#include "../tests/mocks/testShoe.hpp"


TEST_CASE("doesn't have a hand after initialization") {
	Dealer dealer(false);

	REQUIRE_FALSE(dealer.hasHand());
}

TEST_CASE("has a hand after newHand") {
	Dealer dealer(false);
	Shoe shoe(1, 0.5f);

	dealer.newHand(shoe);

	REQUIRE(dealer.hasHand());
	REQUIRE_NOTHROW(dealer.getFirstCard());
}

TEST_CASE("clearHand clears hand") {
	Dealer dealer(false);
	Shoe shoe(1, 0.5f);
	dealer.newHand(shoe);

	dealer.clearHand();

	REQUIRE_FALSE(dealer.hasHand());
}

TEST_CASE("getHand gets hand after playing out hand") {
	Dealer dealer(false);
	Shoe shoe(1, 0.5f);
	dealer.newHand(shoe);

	REQUIRE_NOTHROW(dealer.playOutHand(shoe));
	REQUIRE_NOTHROW(dealer.getHand());
}

TEST_CASE("getHand throws when the hand hasn't been played out") {
	Dealer dealer(false);

	REQUIRE_THROWS_AS(dealer.getHand(), std::runtime_error);
}

TEST_CASE("getFirstCard returns first given card") {
	Dealer dealer(false);
	Shoe shoe(1, 0.5f);
	dealer.newHand(shoe);

	const auto& firstCard = dealer.getFirstCard();

	REQUIRE_NOTHROW(dealer.playOutHand(shoe));
	const auto& handFirstCard = dealer.getHand().getCards().front();

	REQUIRE(firstCard.getRank() == handFirstCard.getRank());
	REQUIRE(firstCard.getSuit() == handFirstCard.getSuit());
}

TEST_CASE("peekForBlackjack returns correctly when first card is ace or 10-val card") {
	Dealer dealer(false);
	TestShoe shoe;

	// King + Ace = blackjack (last card is first drawn)
	shoe.setShoe({Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Hearts)});
	dealer.newHand(shoe);
	REQUIRE(dealer.peekForBlackjack());
	dealer.clearHand();

	// Queen + Ace = blackjack
	shoe.setShoe({Card(Rank::Ace, Suit::Hearts), Card(Rank::Queen, Suit::Diamonds)});
	dealer.newHand(shoe);
	REQUIRE(dealer.peekForBlackjack());
	dealer.clearHand();

	// Ten + Ace = blackjack
	shoe.setShoe({Card(Rank::Ace, Suit::Clubs), Card(Rank::Ten, Suit::Spades)});
	dealer.newHand(shoe);
	REQUIRE(dealer.peekForBlackjack());
  dealer.clearHand();

  // Queen + Two = not blackjack (Queen is first card drawn)
  shoe.setShoe({Card(Rank::Two, Suit::Hearts), Card(Rank::Queen, Suit::Diamonds)});
	dealer.newHand(shoe);
	REQUIRE_FALSE(dealer.peekForBlackjack());

}

TEST_CASE("peekForBlackJack throws when the first card is not ace or 10-val card") {
	Dealer dealer(false);
	TestShoe shoe;

  shoe.setShoe({Card(Rank::Five, Suit::Hearts), Card(Rank::Eight, Suit::Spades)});
  dealer.newHand(shoe);
  REQUIRE_THROWS(dealer.peekForBlackjack());
  dealer.clearHand();
}

TEST_CASE("isBust returns true when the hand is more than 21") {
	Dealer dealer(false);
	TestShoe shoe;

	// Create a hand that will bust: King + Queen + Five = 25
	shoe.setShoe({Card(Rank::Queen, Suit::Hearts),Card(Rank::Five, Suit::Diamonds), Card(Rank::King, Suit::Spades)});
	dealer.newHand(shoe);
	dealer.playOutHand(shoe);

	REQUIRE(dealer.isBust());
	REQUIRE(dealer.getHand().isBust());
}

TEST_CASE("isBust returns false when the hand is not more than 21") {
	Dealer dealer(false);
	TestShoe shoe;

	// Create a hand that won't bust: Five + Six + Seven = 18
	shoe.setShoe({Card(Rank::Seven, Suit::Diamonds), Card(Rank::Six, Suit::Hearts), Card(Rank::Five, Suit::Spades)});
	dealer.newHand(shoe);
	dealer.playOutHand(shoe);

	REQUIRE_FALSE(dealer.isBust());
	REQUIRE_FALSE(dealer.getHand().isBust());
}

TEST_CASE("playOutHand hits till hard 16 included on hitOnSoft17 = false, then stands") {
	Dealer dealer(false);
	TestShoe shoe;

	// Create hand: Ten + Five = 15 (hard 15, should hit)
	// Then add Six to make 21 (should stand)
	shoe.setShoe({Card(Rank::Five, Suit::Diamonds), Card(Rank::Six, Suit::Hearts), Card(Rank::Ten, Suit::Spades)});
	dealer.newHand(shoe);
	dealer.playOutHand(shoe);

	REQUIRE_FALSE(dealer.isBust());
	REQUIRE(dealer.getHand().getValue() >= 17);
}

TEST_CASE("playOutHand hits till soft 16 included on hitOnSoft17 = false, then stands") {
	Dealer dealer(false);
	TestShoe shoe;

	shoe.setShoe({Card(Rank::Five, Suit::Diamonds), Card(Rank::Five, Suit::Hearts), Card(Rank::Ace, Suit::Spades)});
	dealer.newHand(shoe);
	dealer.playOutHand(shoe);

	REQUIRE_FALSE(dealer.isBust());
	REQUIRE(dealer.getHand().getValue() >= 17);
}

TEST_CASE("playOutHand hits till hard 16 included on hitOnSoft17 = true, then stands") {
	Dealer dealer(true);
	TestShoe shoe;

	shoe.setShoe({Card(Rank::Four, Suit::Diamonds), Card(Rank::Six, Suit::Hearts), Card(Rank::Ten, Suit::Spades)});
	dealer.newHand(shoe);
	dealer.playOutHand(shoe);

	REQUIRE_FALSE(dealer.isBust());
	REQUIRE(dealer.getHand().getValue() >= 17);
}

TEST_CASE("playOutHand hits till soft 17 included on hitOnSoft17 = true, then stands") {
	Dealer dealer(true);
	TestShoe shoe;

	// Cards drawn in order: Ace, Six, Five, Six
	shoe.setShoe({Card(Rank::Six, Suit::Clubs), Card(Rank::Five, Suit::Diamonds), Card(Rank::Six, Suit::Hearts), Card(Rank::Ace, Suit::Spades)});
	dealer.newHand(shoe);
	dealer.playOutHand(shoe);

	// Should have 4 cards total and be hard 18
	REQUIRE_FALSE(dealer.getHand().isSoft());
	REQUIRE(dealer.getHand().getSize() == 4);
	REQUIRE(dealer.getHand().getValue() == 18);
}

TEST_CASE("newHand creates new hand when hand empty") {
	Dealer dealer(false);
	Shoe shoe(1, 0.5f);

	REQUIRE_NOTHROW(dealer.newHand(shoe));
	REQUIRE(dealer.hasHand());
}

TEST_CASE("newHand throws when hand already exists") {
	Dealer dealer(false);
	Shoe shoe(1, 0.5f);
	dealer.newHand(shoe);

	REQUIRE_THROWS(dealer.newHand(shoe));
}

TEST_CASE("clearHand removes current hand") {
	Dealer dealer(false);
	Shoe shoe(1, 0.5f);
	dealer.newHand(shoe);
	dealer.clearHand();

	REQUIRE_FALSE(dealer.hasHand());
}