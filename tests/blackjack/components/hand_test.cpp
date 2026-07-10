#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "blackjack/components/hand.hpp"
#include "card/card.hpp"
#include "card/rank.hpp"
#include "card/suit.hpp"

TEST_CASE("Hand created with one card contains one correct card") {
  Card c1(Rank::Ace, Suit::Clubs);
  Hand hand(Card(Rank::Ace, Suit::Clubs));

  auto cards = hand.getCards();

  REQUIRE(cards.size() == 1);
  REQUIRE(cards[0].getRank() == c1.getRank());
  REQUIRE(cards[0].getSuit() == c1.getSuit());
}

TEST_CASE("Hand created with 2 cards contains 2 correct cards") {
  Card c1(Rank::King, Suit::Clubs);
  Card c2(Rank::Two, Suit::Spades);

  Hand hand(Card(Rank::King, Suit::Clubs), Card(Rank::Two, Suit::Spades));

  auto cards = hand.getCards();

  REQUIRE(cards.size() == 2);
  REQUIRE(cards[0].getRank() == c1.getRank());
  REQUIRE(cards[0].getSuit() == c1.getSuit());
  REQUIRE(cards[1].getRank() == c2.getRank());
  REQUIRE(cards[1].getSuit() == c2.getSuit());
}

TEST_CASE("hit adds correct card to the hand") {
  Hand hand(Card(Rank::King, Suit::Clubs), Card(Rank::Two, Suit::Spades));
  hand.hit(Card(Rank::Five, Suit::Spades));
  Card c = Card(Rank::Five, Suit::Spades);
  
  auto cards = hand.getCards();

  REQUIRE(cards.back().getRank() == c.getRank());
  REQUIRE(cards.back().getSuit() == c.getSuit());
}

TEST_CASE("getSize correctly returns amount of cards") {
  Hand hand(Card(Rank::King, Suit::Clubs));
  REQUIRE(hand.getSize() == 1);
  
  for(int i = 2; i < 10; i++) {
    hand.hit(Card(Rank::Five, Suit::Spades));
    REQUIRE(hand.getSize() == i);
  }
}

TEST_CASE("getValue returns correct value for hard hands without ace") {
  Hand val12Hand(Card(Rank::King, Suit::Clubs), Card(Rank::Two, Suit::Spades));
  Hand val7Hand(Card(Rank::Five, Suit::Spades), Card(Rank::Two, Suit::Spades));
  Hand val15Hand(Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));
  Hand val25Hand(Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));
  val25Hand.hit(Card(Rank::King, Suit::Spades));

  REQUIRE(val12Hand.getValue() == 12);
  REQUIRE(val7Hand.getValue() == 7);
  REQUIRE(val15Hand.getValue() == 15);
  REQUIRE(val25Hand.getValue() == 25);
}

TEST_CASE("getValue returns correct value for soft hands") {
  Hand val13Hand(Card(Rank::Ace, Suit::Spades), Card(Rank::Two, Suit::Diamonds));
  Hand val20Hand(Card(Rank::Ace, Suit::Spades), Card(Rank::Nine, Suit::Diamonds));
  Hand val21Hand(Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Diamonds));

  REQUIRE(val13Hand.getValue() == 13);
  REQUIRE(val20Hand.getValue() == 20);
  REQUIRE(val21Hand.getValue() == 21);
}

TEST_CASE("getValue returns correct value for hard hands with ace") {
  Hand val16Hand(Card(Rank::Ace, Suit::Spades), Card(Rank::Eight, Suit::Spades));
  val16Hand.hit(Card(Rank::Seven, Suit::Spades));

  Hand aceAceHand(Card(Rank::Ace, Suit::Spades), Card(Rank::Ace, Suit::Diamonds));

  Hand multipleAceVal18Hand(Card(Rank::Ace, Suit::Spades), Card(Rank::Four, Suit::Spades));
  multipleAceVal18Hand.hit(Card(Rank::Ace, Suit::Diamonds));
  multipleAceVal18Hand.hit(Card(Rank::Ace, Suit::Spades));
  multipleAceVal18Hand.hit(Card(Rank::Ace, Suit::Hearts));
  

  REQUIRE(val16Hand.getValue() == 16);
  REQUIRE(aceAceHand.getValue() == 12);
  REQUIRE(multipleAceVal18Hand.getValue() == 18);
}

TEST_CASE("isBust returns true above 21") {
  Hand val25Hand(Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));
  val25Hand.hit(Card(Rank::King, Suit::Spades));

  Hand val22Hand(Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));
  val22Hand.hit(Card(Rank::Seven, Suit::Spades));

  REQUIRE(val25Hand.getValue() == 25);
  REQUIRE(val25Hand.isBust() == true);
  REQUIRE(val22Hand.getValue() == 22);
  REQUIRE(val22Hand.isBust() == true);
}

TEST_CASE("isBust returns false below or equal to 21") {
  Hand val21Hand(Card(Rank::Nine, Suit::Spades), Card(Rank::King, Suit::Clubs));
  val21Hand.hit(Card(Rank::Two, Suit::Spades));

  Hand val15Hand(Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));

  REQUIRE(val21Hand.getValue() == 21);
  REQUIRE(val21Hand.isBust() == false);
  REQUIRE(val15Hand.getValue() == 15);
  REQUIRE(val15Hand.isBust() == false);
}

TEST_CASE("isBlackjack returns true on ace and 10 value card") {
  Hand aceKing(Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Clubs));
  Hand aceTen(Card(Rank::Ace, Suit::Spades), Card(Rank::Ten, Suit::Clubs));

  REQUIRE(aceKing.isBlackjack() == true);
  REQUIRE(aceTen.isBlackjack() == true);
}

TEST_CASE("isBlackjack returns false on 2 cards that aren't blackjack") {
  Hand fiveTen(Card(Rank::Five, Suit::Spades), Card(Rank::Ten, Suit::Clubs));
  Hand NineAce(Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));

  REQUIRE(fiveTen.isBlackjack() == false);
  REQUIRE(NineAce.isBlackjack() == false);
}

TEST_CASE("isBlackjack returns false on more cards that sum up to 21") {
  Hand withoutAce21(Card(Rank::Five, Suit::Spades), Card(Rank::Ten, Suit::Clubs));
  withoutAce21.hit(Card(Rank::Six, Suit::Hearts));

  Hand withAce21(Card(Rank::Five, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  withAce21.hit(Card(Rank::Five, Suit::Hearts));

  REQUIRE(withoutAce21.getValue() == 21);
  REQUIRE(withoutAce21.isBlackjack() == false);
  REQUIRE(withAce21.getValue() == 21);
  REQUIRE(withAce21.isBlackjack() == false);
}

TEST_CASE("isSoft returns true when there is ace to be softened") {
  Hand nineAce(Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  Hand fourAce(Card(Rank::Four, Suit::Spades), Card(Rank::Ace, Suit::Clubs));

  REQUIRE(nineAce.isSoft() == true);
  REQUIRE(fourAce.isSoft() == true);
}

TEST_CASE("isSoft returns false with no ace") {
  Hand fiveTen(Card(Rank::Five, Suit::Spades), Card(Rank::Ten, Suit::Clubs));
  Hand val15Hand(Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));

  REQUIRE(fiveTen.isSoft() == false);
  REQUIRE(val15Hand.isSoft() == false);
}

TEST_CASE("isSoft returns false with already softened ace") {
  Hand h1(Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  h1.hit(Card(Rank::Ten, Suit::Diamonds));
  
  Hand h2(Card(Rank::Four, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  h2.hit(Card(Rank::Seven, Suit::Diamonds));

  Hand h3(Card(Rank::Four, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  h3.hit(Card(Rank::Seven, Suit::Diamonds));
  h3.hit(Card(Rank::Ace, Suit::Clubs));
  
  REQUIRE(h1.isSoft() == false);
  REQUIRE(h2.isSoft() == false);
  REQUIRE(h3.isSoft() == false);
}

TEST_CASE("canDouble returns true when 2 cards in hand") {
  Hand h1(Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  Hand h2(Card(Rank::Four, Suit::Spades), Card(Rank::Seven, Suit::Clubs));
  
  REQUIRE(h1.canDouble() == true);
  REQUIRE(h2.canDouble() == true);
}

TEST_CASE("canDouble returns false on blackjack") {
  Hand h1(Card(Rank::King, Suit::Spades), Card(Rank::Ace, Suit::Clubs));

  REQUIRE(h1.canDouble() == false);
}

TEST_CASE("canDouble returns false when more/less than 2 cards in hand") {
  Hand h1(Card(Rank::Nine, Suit::Spades));
  Hand h2(Card(Rank::Four, Suit::Spades), Card(Rank::Seven, Suit::Clubs));
  h2.hit(Card(Rank::Seven, Suit::Diamonds));
  
  REQUIRE(h1.canDouble() == false);
  REQUIRE(h2.canDouble() == false);
}

TEST_CASE("canSplit returns true when 2 cards of same rank in hand") {
  Hand h1(Card(Rank::Nine, Suit::Spades), Card(Rank::Nine, Suit::Clubs));
  Hand h2(Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  
  REQUIRE(h1.canSplit() == true);
  REQUIRE(h2.canSplit() == true);
}

TEST_CASE("canSplit returns false when 2 cards of different rank in hand") {
  Hand h1(Card(Rank::Nine, Suit::Spades), Card(Rank::Ten, Suit::Clubs));
  Hand h2(Card(Rank::King, Suit::Spades), Card(Rank::Jack, Suit::Clubs));
  
  REQUIRE(h1.canSplit() == false);
  REQUIRE(h2.canSplit() == false);
}

TEST_CASE("canSplit returns false when 2 cards have same value but different rank") {
  Hand h1(Card(Rank::King, Suit::Spades), Card(Rank::Queen, Suit::Clubs));
  Hand h2(Card(Rank::Ten, Suit::Spades), Card(Rank::Jack, Suit::Clubs));

  REQUIRE(h1.canSplit() == false);
  REQUIRE(h2.canSplit() == false);
}

TEST_CASE("canSplit returns false when more/less then 2 cards of same rank in hand") {
  Hand h1(Card(Rank::Nine, Suit::Spades), Card(Rank::Nine, Suit::Clubs));
  h1.hit(Card(Rank::Nine, Suit::Clubs));
  Hand h2(Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  h2.hit(Card(Rank::King, Suit::Spades));
  
  REQUIRE(h1.canSplit() == false);
  REQUIRE(h2.canSplit() == false);
}

TEST_CASE("canSplit returns false when more/less then 2 cards of different rank in hand") {
  Hand h1(Card(Rank::Nine, Suit::Spades), Card(Rank::Nine, Suit::Clubs));
  h1.hit(Card(Rank::Ten, Suit::Clubs));
  Hand h2(Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  h2.hit(Card(Rank::Ten, Suit::Spades));
  
  REQUIRE(h1.canSplit() == false);
  REQUIRE(h2.canSplit() == false);
}

TEST_CASE("removeCardForSplit returns a correct card and keeps one card in Hand when splittable") {
  Hand h1(Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));

  Card removed = h1.removeCardForSplit();
  auto leftInHand = h1.getCards();

  REQUIRE(removed.getRank() == Rank::King);
  REQUIRE(leftInHand.size() == 1);
  REQUIRE(leftInHand[0].getRank() == Rank::King);
  REQUIRE(leftInHand[0].getSuit() != removed.getSuit());
}

TEST_CASE("removeCardForSplit throws when not splittable") {
  Hand h1(Card(Rank::Nine, Suit::Spades), Card(Rank::Ten, Suit::Clubs));

  REQUIRE_THROWS(h1.removeCardForSplit());
}
