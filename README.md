# pokertools-cpp
Tools for poker related coding

Evaluators performance comparing to poker-eval project (same hardware and compiler):

| hands per second | evaluateHoldemHand | evaluateHoldem[N]CardsHand | poker-eval |
|------------------|--------------------|----------------------------|------------|
| 5 cards          | 76705551           | 80788332                   | 73925661   |
| 7 cards          | 67113601           | 68544628                   | 64718858   |