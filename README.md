## Some Card Type notes

### Railway Station
1. Take an active player pointer
2. Checks amount of money
3. If the number is less or equal to zero, increment money

**Objects to take**: active player ptr


### Shopping Mall
1. Take an active player pointer
2. Get all the cards, called by current dice
3. If such a card has type "Cafe" or "Shop", get the sum of them
4. Add the sum of such card to active player money.


### Amusement Park
1. Take an active player pounter
2. Calls event onExtraTurnRequred
3. TurnManager handles event

### Radio Tower
1. Calls event onRollTheDiceOnce
2. 

### Player class
QVector<Card*> getBuildsWithCurerntDice();


### What a Specific Card should do?
* know when it should be triggered.

### Class GameEvents should generate game events
* emits dic

### What events?
These events made by landmarks
1. ActivePlayerHasNoMoney()
2. DiceRollerEqualOrMoreThen10()
3. CanRollTheDiceTwice()
4. addCoinIftriggered()
5. RollsAreEqual()
6. RollDice()
7. NoBuildAreBuild()

So it means we've got en event.
The type of the card controlls the roll dice and checks condition of work

1. ownerGetCoins(ActivePlayer, Players, 1..n)
2. activePlayerGetCoins(ActivePlayer, 1..n)
3.

Next events made by blue cards
1. If roll == 1, call ownerGetCoins(1) // field
2. if roll == 2, call iwnerGetCoins(2) // farm
3. If roll == 3 or 4 and owner has 1 landmark, call ownerGetCoins(1) // Cucuruz filed
4. if roll == 4, call ownerGetCoins(1) // Glowers field
5. if roll == 5, call ownerGetCoins(1) // forest
6. If roll == 7, ownerGetCoins(3) // Graps
7. If roll == 8 and ownerHasLandmark(Port), ownerGetCoins(3) // fish ship
8. if roll == 9 ownerGetCoins(5) // mining
9. If roll == 10 ownerGetCoins(3) // Apple Garden
10. if roll == 12 or 14, RollDice(ActivePlayer) and if ownerHasLandmark(Port), ownerGetCoins(rollResult)

signal buildingIsBuild(), slot if buildingOfType() get activePlayerCoins(5)
signal checkIfActivePlayerHasType(), slot activePlayerGetCoins(1)
signal checkIfActivePlayerHasGroupOfTypes(), slot 
signal 

Maybe I should add an argument to initial a class

setCardIsBlocked()
setCardIsActive()


Next events made by green cards
1. roll == 2 && ownerHasLandmark(), activePlayerGetCoins(2) // universam
2. roll == 4 && getCardBackToReserve(Card) and activePlayerGetCoins(8) // demontag
3. roll == 5 || 6 activePlayerLossCoins(2) 




So it means that events might be listened not only by specific cards

So all the cards are listen to roll. If the roll equal to their neds, they call their signals
