# Blackjack (C++)

The goal of this project is to analyze the game of blackjack and the chance of beating it unnoticed.

By beating it I mean achieving above 1 EV (estimated value) with <= 2 counts in your head. Ideally the EV should be achivable with randomized mistakes and 98% accuracy to strategy. The EV will be calculated by simulating the game (probably).

Future goals:
- find basic strategy myself (maybe some monte carlo or simulated annealing?)
- prove that counting cards works by simulating it
- try to find a variation of counting where you don't vary bet and it still wins.
- UI
- the game itself

TODOS:
- create a background class for UI (with destructor of texture) and revert the MainMenuIO destructor to default
- write:
  - blackjackRayLibIO
  - mainMenuIO
- add tests for BlackjackGame
- change folder structure
- add settings