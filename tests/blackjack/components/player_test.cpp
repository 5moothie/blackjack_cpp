#include <catch2/catch_test_macros.hpp>

#include "blackjack/components/player.hpp"
#include "card/rank.hpp"
#include "card/suit.hpp"
#include "../../mocks/testShoe.hpp"

#include <stdexcept>
#include <vector>

namespace {
  Card card(Rank rank) { return Card(rank, Suit::Spades);
  }


  TestShoe shoe(std::initializer_list<Rank> ranks) {
    TestShoe result;
    std::vector<Card> cards;
    for (Rank rank : ranks)
      cards.push_back(card(rank));
    result.setShoe(std::move(cards));
    return result;
  }

  void addHand(Player& player, TestShoe& testShoe, long long bet = 20) {
    player.addHand(bet, testShoe);
  }

  void stand(Player& player) { player.standActiveHand();
  }

}

TEST_CASE("after initialization handsLeftToPlay() = 0") { 
  REQUIRE(Player(100).handsLeftToPlay() == 0); 
}

TEST_CASE("after initialization getBalance returns the constructor balance") { 
  REQUIRE(Player(123).getBalance() == 123); 
}

TEST_CASE("after initialization getAllHands returns an empty collection") { 
  REQUIRE(Player(100).getAllHands().empty()); 
}

TEST_CASE("initialization with zero balance succeeds") { 
  REQUIRE_NOTHROW(Player(0)); 
}

TEST_CASE("initialization with negative balance throws") { 
  REQUIRE_THROWS_AS(Player(-1), std::invalid_argument); 
}

TEST_CASE("getActiveHandConst throws when called with no activeHand") { 
  REQUIRE_THROWS(Player(100).getActiveHandConst()); 
}

TEST_CASE("activateNextHand activates next hand with 3 hands") {
  auto testShoe = shoe({Rank::Two, Rank::Three, Rank::Four, Rank::Five, Rank::Six, Rank::Seven});
  Player player(100); addHand(player, testShoe, 10); addHand(player, testShoe, 10); addHand(player, testShoe, 10);
  player.activateNextHand();
  REQUIRE(player.handsLeftToPlay() == 2); 
  REQUIRE(player.getActiveHandConst().getBet() == 10);
  
  player.activateNextHand();
  REQUIRE(player.handsLeftToPlay() == 1); 
  REQUIRE(player.getActiveHandConst().getBet() == 10);
}

TEST_CASE("activateNextHand does nothing when no remaining hands (handsLeftToPlay doesn't underflow)") {
  Player player(100); 
  player.activateNextHand(); 

  REQUIRE(player.handsLeftToPlay() == 0); 

  player.activateNextHand(); 
  REQUIRE(player.handsLeftToPlay() == 0);
}

TEST_CASE("after initialization hasActiveHand returns false") {
  REQUIRE_FALSE(Player(100).hasActiveHand());
}

TEST_CASE("hasActiveHand returns true when a active hand exists") {
  auto s = shoe({Rank::Two, Rank::Three}); 
  Player p(100); 

  addHand(p, s); 

  REQUIRE(p.hasActiveHand());
}

TEST_CASE("hasActiveHand returns false when all hands finished") {
  auto s = shoe({Rank::Two, Rank::Three}); 
  Player p(100); 

  addHand(p, s); 
  stand(p); 

  REQUIRE_FALSE(p.hasActiveHand());
}

TEST_CASE("hasActiveHand returns true when hands cleared and added") {
  auto s = shoe({Rank::Two, Rank::Three, Rank::King, Rank::Seven}); 
  Player p(100); 

  addHand(p, s); 
  stand(p); 
  p.clearHands();
  addHand(p, s);
  
  REQUIRE(p.hasActiveHand());
}

TEST_CASE("handsLeftToPlay correctly returns amount of hands remaining for play (including active)") {
  auto s = shoe({Rank::Two, Rank::Three, Rank::Four, Rank::Five, Rank::Six, Rank::Seven}); 
  Player p(100);

  addHand(p, s, 10); 
  addHand(p, s, 20);
  addHand(p, s, 30); 
  
  REQUIRE(p.handsLeftToPlay() == 3);

  p.activateNextHand();
  
  REQUIRE(p.handsLeftToPlay() == 2);
}

TEST_CASE("canDoubleActiveHand returns true when hand is 2 cards and wasn't split before") {
  auto s = shoe({Rank::Five, Rank::Six});
  Player p(40);

  addHand(p, s);

  REQUIRE(p.canDoubleActiveHand());
}

TEST_CASE("canDoubleActiveHand returns false after splitting") {
  auto s = shoe({Rank::Eight, Rank::Eight, Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);
  p.splitActiveHand(s);

  REQUIRE_FALSE(p.canDoubleActiveHand());
}

TEST_CASE("canDoubleActiveHand returns false after hitting") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two});
  Player p(100);

  addHand(p, s);
  p.hitActiveHand(s);

  REQUIRE_FALSE(p.canDoubleActiveHand());
}

TEST_CASE("canDoubleActiveHand returns false when the supplied balance is insufficient") {
  auto s = shoe({Rank::Five, Rank::Six});
  Player p(30);

  addHand(p, s);

  REQUIRE_FALSE(p.canDoubleActiveHand());
}

TEST_CASE("canSplitActiveHand returns true when hand has 2 of the value cards") {
  auto s = shoe({Rank::Nine, Rank::Nine});
  Player p(40);

  addHand(p, s);
  
  REQUIRE(p.canSplitActiveHand());
}

TEST_CASE("canSplitActiveHand returns false after hitting") {
  auto s = shoe({Rank::Five, Rank::Five, Rank::Two});
  Player p(100);
  
  addHand(p, s);
  p.hitActiveHand(s);
  
  REQUIRE_FALSE(p.canSplitActiveHand());
}

TEST_CASE("canSplitActiveHand returns false when hand consists of 2 different value cards") {
  auto s = shoe({Rank::King, Rank::Queen});
  Player p(100);
  
  addHand(p, s);
  
  REQUIRE_FALSE(p.canSplitActiveHand());
}

TEST_CASE("canSplitActiveHand returns false when the supplied balance is insufficient") {
  auto s = shoe({Rank::Nine, Rank::Nine});
  Player p(30);
  
  addHand(p, s);
  
  REQUIRE_FALSE(p.canSplitActiveHand());
}

TEST_CASE("hitActiveHand adds card to the hand") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two});
  Player p(100);

  addHand(p, s);
  p.hitActiveHand(s);

  REQUIRE(p.getActiveHandConst().getSize() == 3);
}

TEST_CASE("hitActiveHand activates next hand if it busts after hitting") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Ten, Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);
  addHand(p, s);
  p.hitActiveHand(s);

  REQUIRE(p.getActiveHandConst().getBet() == 20);
}

TEST_CASE("hitActiveHand activates next hand if hand value goes to 21") {
  auto s = shoe({Rank::Two, Rank::Six, Rank::Four, Rank::Nine, Rank::Ten});
  Player p(100);

  addHand(p, s);
  addHand(p, s);
  p.hitActiveHand(s);

  REQUIRE(p.getActiveHandConst().getValue() == 10);
}

TEST_CASE("hitActiveHand leaves the hand active when its value remains below 21") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two});
  Player p(100);

  addHand(p, s);
  p.hitActiveHand(s);

  REQUIRE(p.hasActiveHand());
  REQUIRE(p.getActiveHandConst().getValue() == 13);
}

TEST_CASE("during hitActiveHand Shoe cards are consumed correctly") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two});
  Player p(100);

  addHand(p, s);
  p.hitActiveHand(s);

  REQUIRE(s.getCards().empty());
}

TEST_CASE("doubleActiveHand adds one card to hand if hand can be doubled") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two});
  Player p(40);

  addHand(p, s);
  p.doubleActiveHand(s);

  REQUIRE(p.getAllHands()[0].getSize() == 3);
}

TEST_CASE("doubleActiveHand throws when hand cannot be doubled and leaves the state unchanged") {
  auto s = shoe({Rank::King, Rank::Ace});
  Player p(100);

  addHand(p, s);

  REQUIRE_THROWS(p.doubleActiveHand(s));
  REQUIRE(p.getAllHands()[0].getSize() == 2);
}

TEST_CASE("doubleActiveHand throws when the balance is insufficient and leaves the state unchanged") {
  auto s = shoe({Rank::Five, Rank::Six});
  Player p(30);

  addHand(p, s);

  REQUIRE_THROWS(p.doubleActiveHand(s));
  REQUIRE(p.getBalance() == 10);
  REQUIRE(p.getAllHands()[0].getSize() == 2);
}

TEST_CASE("doubleActiveHand actiavtes next hand") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two, Rank::Three, Rank::Four});
  Player p(100);

  addHand(p, s);
  addHand(p, s);
  p.doubleActiveHand(s);

  REQUIRE(p.getActiveHandConst().getValue() == 5);
}

TEST_CASE("doubleActiveHand doubles the bet on the hand") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two});
  Player p(40);

  addHand(p, s);
  p.doubleActiveHand(s);

  REQUIRE(p.getAllHands()[0].getBet() == 40);
}

TEST_CASE("doubleActiveHand decreases the balance by original bet") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two});
  Player p(100);

  addHand(p, s);
  p.doubleActiveHand(s);

  REQUIRE(p.getBalance() == 60);
}

TEST_CASE("standActiveHand leaves hand and balance unchanged") {
  auto s = shoe({Rank::Five, Rank::Six});
  Player p(100);

  addHand(p, s);
  stand(p);

  REQUIRE(p.getAllHands()[0].getSize() == 2);
  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("standActiveHand activates next hand") {
  auto s = shoe({Rank::Five, Rank::Six, Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);
  addHand(p, s);
  stand(p);

  REQUIRE(p.hasActiveHand());
  REQUIRE(p.getActiveHandConst().getValue() == 5);
}

TEST_CASE("splitActiveHand splits cards and draws one card for each of them") {
  auto s = shoe({Rank::Eight, Rank::Eight, Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);
  p.splitActiveHand(s);

  REQUIRE(p.getAllHands().size() == 2);
  REQUIRE(p.getAllHands()[0].getSize() == 2);
  REQUIRE(p.getAllHands()[1].getSize() == 2);
}

TEST_CASE("after splitActiveHand active hand remains on the original hand") {
  auto s = shoe({Rank::Eight, Rank::Eight, Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);
  p.splitActiveHand(s);

  REQUIRE(p.handsLeftToPlay() == 2);
}

TEST_CASE("splitActiveHand throws when hand is not splittable and leaves the state unchanged") {
  auto s = shoe({Rank::Five, Rank::Six});
  Player p(100);

  addHand(p, s);

  REQUIRE_THROWS(p.splitActiveHand(s));
  REQUIRE(p.getAllHands().size() == 1);
  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("splitActiveHand decreases balance by original bet") {
  auto s = shoe({Rank::Eight, Rank::Eight, Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);
  p.splitActiveHand(s);

  REQUIRE(p.getBalance() == 60);
}

TEST_CASE("both hands cannot be treated as blackjack after a splitActiveHand") {
  auto s = shoe({Rank::Ace, Rank::Ace, Rank::Ten, Rank::Ten});
  Player p(100);

  addHand(p, s);
  p.splitActiveHand(s);

  REQUIRE_FALSE(p.getAllHands()[0].isBlackjack());
  REQUIRE_FALSE(p.getAllHands()[1].isBlackjack());
}

TEST_CASE("settleHands throws when there are still active hands") {
  auto s = shoe({Rank::Five, Rank::Six});
  Player p(100);

  addHand(p, s);

  REQUIRE_THROWS(p.settleHands(Hand(card(Rank::Ten), card(Rank::Nine))));
}

TEST_CASE("settleHands leaves balance unchanged when a regular player hand loses") {
  auto s = shoe({Rank::Five, Rank::Five});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.settleHands(Hand(card(Rank::King), card(Rank::Nine)));

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("settleHands returns the bet when a regular player hand ties the dealer") {
  auto s = shoe({Rank::Five, Rank::Five});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.settleHands(Hand(card(Rank::Seven), card(Rank::Three)));

  REQUIRE(p.getBalance() == 100);
}

TEST_CASE("settleHands leaves a busted player hand's bet lost") {
  auto s = shoe({Rank::King, Rank::Queen, Rank::Two});
  Player p(100);

  addHand(p, s);
  p.hitActiveHand(s);
  p.settleHands(Hand(card(Rank::Seven), card(Rank::Three)));

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("settleHands pays even money when a regular player hand beats the dealer") {
  auto s = shoe({Rank::Ten, Rank::Six});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.settleHands(Hand(card(Rank::Ten), card(Rank::Five)));

  REQUIRE(p.getBalance() == 120);
}

TEST_CASE("settleHands keeps the wager when the dealer beats a regular player hand") {
  auto s = shoe({Rank::Ten, Rank::Five});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.settleHands(Hand(card(Rank::Ten), card(Rank::Six)));

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("settleHands pays 3:2 plus the original wager when the player has blackjack and the dealer does not") {
  auto s = shoe({Rank::Ace, Rank::King});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.settleHands(Hand(card(Rank::Ten), card(Rank::Nine)));

  REQUIRE(p.getBalance() == 130);
}

TEST_CASE("settleHands returns the original wager when both the player and dealer have blackjack") {
  auto s = shoe({Rank::Ace, Rank::King});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.settleHands(Hand(card(Rank::Ace), card(Rank::King)));

  REQUIRE(p.getBalance() == 100);
}

TEST_CASE("settleHands keeps both wagers lost when both the player and dealer bust") {
  auto s = shoe({Rank::King, Rank::Queen, Rank::Two});
  Player p(100);

  addHand(p, s);
  p.hitActiveHand(s);
  p.settleHands(Hand(card(Rank::King), card(Rank::Queen)));

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("clearHands removes all hands") {
  auto s = shoe({Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.clearHands();

  REQUIRE(p.getAllHands().empty());
}

TEST_CASE("clearHands throws if there is an active hand") {
  auto s = shoe({Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);

  REQUIRE_THROWS(p.clearHands());
}

TEST_CASE("clearHands preserves balance") {
  auto s = shoe({Rank::Two, Rank::Three});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.clearHands();

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("after clearHands the player can add a new hand") {
  auto s = shoe({Rank::Two, Rank::Three, Rank::Four, Rank::Five});
  Player p(100);

  addHand(p, s);
  stand(p);
  p.clearHands();

  REQUIRE_NOTHROW(p.addHand(20, s));
  REQUIRE(p.hasActiveHand());
}

TEST_CASE("addHand adds hand to the end") {
  auto s = shoe({Rank::Two, Rank::Three, Rank::Four, Rank::Five});
  Player p(100);

  addHand(p, s, 10);
  addHand(p, s, 20);

  REQUIRE(p.getAllHands().back().getBet() == 20);
}

TEST_CASE("addHand when insufficient balance throws and leaves state unchanged") {
  auto s = shoe({Rank::Two, Rank::Three});
  Player p(10);

  REQUIRE_THROWS(p.addHand(20, s));
  REQUIRE(p.getAllHands().empty());
  REQUIRE(p.getBalance() == 10);
}

TEST_CASE("addHand adds hand if the bet is exact available balance") {
  auto s = shoe({Rank::Two, Rank::Three});
  Player p(20);

  REQUIRE_NOTHROW(p.addHand(20, s));
  REQUIRE(p.getBalance() == 0);
}

TEST_CASE("addHand throws on non-positive bet") {
  auto s = shoe({Rank::Two, Rank::Three});
  Player p(100);

  REQUIRE_THROWS(p.addHand(0, s));
  REQUIRE_THROWS(p.addHand(-2, s));
}

TEST_CASE("addHand throws on odd bet") {
  auto s = shoe({Rank::Two, Rank::Three});
  Player p(100);

  REQUIRE_THROWS(p.addHand(21, s));
}

TEST_CASE("addHand when the shoe runs out of cards leaves balance and hands unchanged") {
  auto s = shoe({Rank::Two});
  Player p(100);

  REQUIRE_THROWS(p.addHand(20, s));
  REQUIRE(p.getAllHands().empty());
  REQUIRE(p.getBalance() == 100);
}

TEST_CASE("getActiveHandConst throws when there is no active hand") {
  REQUIRE_THROWS(Player(100).getActiveHandConst());
}

TEST_CASE("canDoubleActiveHand throws when there is no active hand") {
  REQUIRE_THROWS(Player(100).canDoubleActiveHand());
}

TEST_CASE("canSplitActiveHand throws when there is no active hand") {
  REQUIRE_THROWS(Player(100).canSplitActiveHand());
}

TEST_CASE("hitActiveHand throws when there is no active hand") {
  auto s = shoe({Rank::Two});
  Player p(100);

  REQUIRE_THROWS(p.hitActiveHand(s));
}

TEST_CASE("doubleActiveHand throws when there is no active hand") {
  auto s = shoe({Rank::Two});
  Player p(100);

  REQUIRE_THROWS(p.doubleActiveHand(s));
}

TEST_CASE("standActiveHand throws when there is no active hand") {
  REQUIRE_THROWS(Player(100).standActiveHand());
}

TEST_CASE("splitActiveHand throws when there is no active hand") {
  auto s = shoe({Rank::Two});
  Player p(100);
  
  REQUIRE_THROWS(p.splitActiveHand(s));
}
