# Blackjack (C++)

The goal of this project is to analyze the game of blackjack and the chance of beating it unnoticed.

By beating it I mean achieving above 50% winrate with <= 2 counts in your head. Ideally above 50.5% winrate. The winration will be calculated by simulating the game (probably).

Future goals:
- find basic strategy myself (maybe some monte carlo or simulated annealing?)
- prove that counting cards works by simulating it
- try to find a variation of counting where you don't vary bet and it still wins.
- UI
- the game itself

TODOS:
- remove the current UI and go back to the console type for now
- remaining tests for everything
- restructure the structure to blackjack/components, blackjack/game, blackjack/game/IO