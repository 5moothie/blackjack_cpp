#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

#include "blackjack/components/dealer.hpp"


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
	Shoe shoe(6, 0.5f);

	while(!dealer.hasHand()) {
		dealer.newHand(shoe);
		if(dealer.getFirstCard().getValue() != 11 && dealer.getFirstCard().getValue() != 10)
			dealer.clearHand();
	} 

	REQUIRE(dealer.peekForBlackjack());
}

TEST_CASE("peekForBlackJack throws when the first card is not ace or 10-val card") {
	Dealer dealer(false);
	Shoe shoe(6, 0.5f);

	while(!dealer.hasHand()) {
		dealer.newHand(shoe);
		if(dealer.getFirstCard().getValue() == 11 ||  dealer.getFirstCard().getValue() == 10)
			dealer.clearHand();
	}

	REQUIRE_THROWS(dealer.peekForBlackjack());
}

TEST_CASE("isBust returns true when the hand is more than 21") {
	Dealer dealer(false);
	Shoe shoe(6, 0.5f);
	bool foundBust = false;

	for(int attempt = 0; attempt < 100 && !foundBust; ++attempt) {
		dealer.newHand(shoe);
		dealer.playOutHand(shoe);
		foundBust = dealer.getHand().isBust();
		if(!foundBust)
			dealer.clearHand();
	}

	REQUIRE(foundBust);
	REQUIRE(dealer.isBust());
}

TEST_CASE("isBust returns false when the hand is not more than 21") {
	Dealer dealer(false);
	Shoe shoe(6, 0.5f);
	bool foundNonBust = false;

	for(int attempt = 0; attempt < 100 && !foundNonBust; ++attempt) {
		dealer.newHand(shoe);
		dealer.playOutHand(shoe);
		foundNonBust = !dealer.getHand().isBust();
		if(!foundNonBust)
			dealer.clearHand();
	}

	REQUIRE(foundNonBust);
	REQUIRE_FALSE(dealer.isBust());
}

TEST_CASE("playOutHand hits till hard 16 included on hitOnSoft17 = false, then stands") {
	Dealer dealer(false);
	Shoe shoe(6, 0.5f);
	dealer.newHand(shoe);

	dealer.playOutHand(shoe);

	REQUIRE((dealer.isBust() || dealer.getHand().getValue() > 16));
}

TEST_CASE("playOutHand hits till soft 16 included on hitOnSoft17 = false, then stands") {
	Dealer dealer(false);
	Shoe shoe(6, 0.5f);
	dealer.newHand(shoe);

	dealer.playOutHand(shoe);

	REQUIRE((dealer.isBust() || dealer.getHand().getValue() > 16));
}

TEST_CASE("playOutHand hits till hard 16 included on hitOnSoft17 = true, then stands") {
	Dealer dealer(true);
	Shoe shoe(6, 0.5f);
	dealer.newHand(shoe);

	dealer.playOutHand(shoe);

	REQUIRE((dealer.isBust() || dealer.getHand().getValue() > 16));
}

TEST_CASE("playOutHand hits till soft 17 included on hitOnSoft17 = true, then stands") {
	Dealer dealer(true);
	Shoe shoe(6, 0.5f);
	dealer.newHand(shoe);

	dealer.playOutHand(shoe);

	REQUIRE((dealer.isBust() || dealer.getHand().getValue() > 17 || !dealer.getHand().isSoft()));
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