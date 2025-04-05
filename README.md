# City Building Card Game
Welcome to city-building card game! This project is inspired by the popular board game
Machi Koro.

## About Machi Koro
Machi Koro is a fast-paced, card-based city-building game. For more information, check out
the [Machi Koro Wikipedia page](https://en.wikipedia.org/wiki/Machi_Koro).

## Features

- Interactive UI made with Qt 6.8 framework and C++17.
- Multiplayer support [in development]

## Getting Started

To get started with the project, follow these steps:

1. Clone the repository:
```bash
git https://gitlab.com/Den-One/city-building-card-game.git
```
2. Install dependencies.
3. Build and run the project.

## Gameplay Description
### Start Menu - Choose Number of Players
![Start Menu](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/start_menu.jpg)
### Income State
![Income State](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/income_state.jpg)
### Build State
![Build State](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/build_state.jpg)
### New Player's Card Stack
![New Player's Card Stack](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/display_new_card.jpg)
### Switch to Another Player
![Switch to Another Player](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/go_to_next.jpg)
### Unlock Landmark to Win
![Unlock Landmark to Win](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/unlock_landmark.jpg)

## Gameplay Rules
### Welcome to the game!
You are about to step into the role of a small-town mayor and transform your town into 
the most prosperous in the region. Build cafes and shops, establish industries, and 
boost your city's revenue. But beware—rival mayors are always on the move, dreaming of 
creating the greatest city on earth. You’ll find yourself in a fierce competition, and 
the winner will be the first to adorn their streets with iconic landmarks.

**Important Note**: The expansions **"Machi Koro Plus"** and **"Machi Koro Sharp"** 
add complexity and extend the gameplay. If this is your first time playing, we recommend 
starting with the base version of the game. Once you’re comfortable, 
feel free to incorporate the expansion cards for a more challenging experience.

### Prepation to the game
For your first few games, it’s recommended to play without the expansion cards 
(PLUS and SHARP). You can also remove promo cards if desired. To do this, check the 
label in the bottom right corner of the cards.

1. Starting Setup:
    * Each player receives 2 starting enterprise cards (Wheat Field and Bakery) and 
    places them face-up in front of themselves.
    * Each player also gets 4 landmark cards (Amusement Park, Train Station, Radio Tower, 
    and Shopping Mall) and places them face-down in front of themselves.
    * Remove any unused starting cards from the game.
2. Initial Coins:
    * Give each player 3 coins with a value of 1. The remaining coins form the bank.
3. Setting Up the Market:
    * Organize the enterprise cards by type and arrange them on the table in the order 
    of their activation.
4. Choosing the First Player:
    * Decide who goes first by rolling a die, drawing lots, or choosing the person who 
    recently traveled.

This setup ensures a smooth introduction to the game, allowing players to focus on 
mastering the basics before diving into more complex expansions.

### Winning
The game ends as soon as one player successfully builds all of their landmarks. 
That player is declared the winner and takes the title of the most successful mayor!

### Turn Structure
A player’s turn consists of three phases, and play proceeds clockwise:

1. Roll The Dice
2. Collect Income
3. Build

The player taking their turn is referred to as the active player.

### 1. Roll The Dice
During this phase, the active player rolls **1 die**. If they have built the 
**Train Station**, they can choose to roll **1 or 2 dice**. When rolling two dice, 
the results are added together, and only the total sum is used for activation.

### 2. Collect Income
In this phase, **all players** (not just the active player!) can earn income 
from their enterprises that match the dice roll. Each enterprise has an activation 
number. If the dice result matches this number, the enterprise’s effect is triggered 
immediately.

There are 4 types of enterprises, each generating income differently:
* Restaurants (Red Cards)
* Small Enterprises (Blue Cards)
* Medium Enterprises (Green Cards)
* Large Enterprises (Purple Cards)

### 3.Build
During this phase, the active player may (but is not required to) build 1 enterprise 
or 1 landmark by paying its construction cost. Spent coins are returned to the bank.

**Building Enterprise**

* To build a new enterprise, pay its cost to the bank and place the card in your city.
* If you have multiple copies of the same enterprise, stack them together in a column 
for easy organization.
* You cannot have more than 1 copy of each large enterprise, but you can own different 
types of large enterprises.

**Building Landmark**
* To build a landmark, pay its construction cost and flip its card to the colored 
side in your city.
* Starting from the next turn (of any player), you can use the landmark’s effects.
* Landmarks can be built in any order.

This turn structure ensures a dynamic and engaging gameplay experience, balancing 
strategy, resource management, and competition!

**All Signals Structure**

The whole list of all player signals from mainWindow
ui signals:
0 somebody clicked Dice 1 roll - 1
0 somebody clicked Dice 2 roll - 2
0 somebody clicked skip - 3
0 somebody clicked cardwiget - 4

ui slots:
7 wait a response in small window
if yes - sendIsUsed radio tower 10
if no - 9
12 update player balance 13

Logic slots:
1, 2 roll the dice, if no double - 5
1, 2, if park and double - 14
5 - check if current palyer has RadioTower
5- if has, ask to reroll - 6
 activate all palyers all cards if possible -
5. 8 if no, incometime 9
10 setRadioTowerIsUsedup
9 activatecards 11, 12
15 activate second roll 16

logic signals:
6 askToRerollCurrentPlayer - 7
11 sendplayernewvalance 12
14 send activate second buy 15

---------- application level ----------

connect(m_mainWindow.get(), &MainWindow::rollDiceButtonClicked, m_gameLogic.get(), &GameLogic::handleRollOneDiceButtonClicked);
connect(m_mainWindow.get(), &MainWindow::skipButtonClicked, m_gameLogic.get(), &GameLogic::handleSkipButtonClicked);
connect(m_mainWindow.get(), &MainWindow::cardWigetClicked, m_gameLogic.get(), &GameLogic::handleCardWigetClicked);

connect(m_gameLogic.get(), &GameLogic::updatePlayerBalance, m_mainWindow.get(), &MainWindow::handleUpdatePlayerBalance);
connect(m_gameLogic.get(), &GameLogic::updateDiceResult, m_mainWindow.get(), &MainWindow::handleUpdateDiceResult);
connect(m_gameLogic.get(), &GameLogic::incomeStateFinished, m_mainWindow.get(), &MainWindow::handleIncomeStateFinished);
connect(m_gameLogic.get(), &GameLogic::buyTwice, m_mainWindow.get(), &MainWindow::handleBuyTwice);


class Player
{
bool isAskedToReroll();
bool containsCard(CardId);

private:
    bool m_askedToReroll;
    bool m_decisionToReroll;
};

---------- MainWindow: ----------

signals:
connect(diceOneButton, &QPushButton::clicked, [this]() {
    enum rollOneDiceButtonClicked(); // 1
});

connect(diceTwoButton, &QPushButton::clicked, [this]() {
    enum rollTwoDiceButtonClicked(); // 2
});

connect(skipButton, &QPushButton::clicked, [this]() {
    enum skipButtonClicked(); // 3
});

connect(cardWidget, &QScrollWidget::cardWigetClicked, [this](int cardId) {
    enum cardWigetClicked(cardWidgetId); // 4
});


public slots:
void handleUpdatePlayerBalance(int playerId, int balance);

void handleUpdateDiceResult(int diceResult);


---------- GameLogic: ----------

signals:
void updatePlayerBalance(int playerId, int balance);

void updateDiceResult(int diceResult);

void buyTwice(int playerId);

slots:
void GameLogic::rollDiceButtonClicked(int rollsNumber)
{
    auto currentPlayer = m_players[m_currentPlayer];
    if (currentPlayer.contains(CardId::RadioTower) && currentPlayer.askedToReroll()) {
        currentPlayer->setAsckedToReroll(true);
        emit askToReroll(currentPlayer);
        return;
    }
    
    int const maxRollNumber = 2;
    vector<int> rollResults(maxRollNumber, 0);
    for (int i = 0; i < rollsNumber; ++i) {
        rollResults[i] = DiceRoller{}.rollDice(1);
    }
    
    emit updateRollResult(vector<int> rollResults);
    
    startIncomeState(vector<int> rollResults);
}

void GameLogic::startIncomeState(vector<int> rollresults)
{
    if (rollResults[0] == rollResults[1] && currentPlayer.contains(CardId::AmusmentPark) && !currentPlayer.buyTwice()) {
        currentPlayer->setBuyTwice(true);
    }

    activateCards(vector<int> rollResults) {
        for (int i = 0; i < m_players.size(); ++i) {
            m_players[i].activateCards() {
                emit balanceChanged(i);
            };            
        }
    };
    
    emit incomeStateFinished();
}

void GameLogic::handleSkipButtonClicked()
{
    if (currentPlayer.buyTWice()) {
        currentPlayer->setBuyTwice(false);
        emit buyTwice(currentPlayer->id());
        return;
    }
    
    setNextPlayerTurn() {
        m_currentPlayerId = (m_currentPlayerId + 1 >= m_players.size()) ? 0 : m_currentPlayerId + 1;
        emit setPlayerTurn(m_currentPlayerId);
    }
}

void GameLogic::handleCardWigetClicked(int cardId)
{
    auto currentPlayer = m_players[m_currentPlayerId];
    auto card = m_bank.find(cardId);
    if (currentPlayer.balance() >= card.price()) {
        currentPlayer.addCard(card);
        m_bank.removeCard(card);
    }
}


Income is written

-3. Before the start, wait from configData to read all data to partialy initialize the bank
-2. Before start, wait from startMenu signal about players count.
-1. For some players count, initialize all connections and data about players

0. Ini all solutions with specific cards to false.

Income State
1. Click on button "dice 1 roll" or "dice 2 rolls"
2. Check currentPlayer has RadioTower & wasn't asked before, if has ask to reroll.
3. MainWindow shows the window and send a signal with the answer of reroll.
4. Handler of result decies what to call, rollDiceButtonClicked to repeat or startIncomeState.
5. incomeState checks do player need to have buy twice ability
6. income state activates cards and after their work for each player, they update each player result, taking their id
7. signal to MainWindow income state is finished, so rewdraw it all.

Buy State
8 Click on card widget or skip button.
9.1. If clicked skip button, checks buyTwice, and if so, sets it not to buy and do nothing.
9.2. if clicked skip button and it wasn't set to buy twice, so just setNextPlayerTurn, so send a signal with new palyer id
9.3. If clicked card Widget, send id of that widget from mainWindow.
10.0. checks if current player can buy that card with that id, if so, BuyCard or sendSignal cantByCard to MainWindow
10.1. gameLogic puts that card by id to player and takes it from bank, emiting 2 signals about these changes with that id.
10.2. checks if all cards to win are bought, and if so, send a signal about it!
11. checks if player can buy twice, if so, puts it false for another time and call singal incomestate is finished, or emit buyStateFinished
12. Handle buy state finished as internal signal and send startNextPlayerTurn(m_playerId)
13. while taking another player, reset to zero all grey cards abilities


## Possible JSON Formats
### Standardized JSON message format

{
  "type": "message_type",
  "timestamp": "ISO8601_timestamp",
  "sender": "component_name",
  "data": {
    // type-specific data
  }
}

### 1. Game State Management

// Game initialization
{
  "type": "game_init",
  "data": {
    "player_count": 4
  }
}

// Player turn change
{
  "type": "player_turn_change",
  "data": {
    "player_id": 2
  }
}

// Game over
{
  "type": "game_over",
  "data": {
    "winner_id": 3
  }
}

### 2. Card Operations

// Card transfer
{
  "type": "card_transfer",
  "data": {
    "from": "bank",
    "to": "player_1",
    "card": {
      "id": 42,
      "type": "property",
      "name": "Boardwalk",
      "value": 400
    }
  }
}

// Card purchase attempt
{
  "type": "card_purchase_attempt",
  "data": {
    "player_id": 1,
    "card_id": 42
  }
}

// Card purchase failure
{
  "type": "card_purchase_failed",
  "data": {
    "player_id": 1,
    "card_id": 42,
    "reason": "insufficient_funds"
  }
}

### 3. Dice Operations

// Dice roll request
{
  "type": "dice_roll_request",
  "data": {
    "player_id": 1,
    "dice_count": 2
  }
}

// Dice roll result
{
  "type": "dice_roll_result",
  "data": {
    "player_id": 1,
    "results": [4, 5],
    "total": 9
  }
}

// Dice reroll confirmation
{
  "type": "dice_reroll_confirmation",
  "data": {
    "player_id": 1,
    "original_roll": [1, 1],
    "confirmed": true
  }
}

### 4. Player Actions

// Balance change
{
  "type": "balance_change",
  "data": {
    "player_id": 2,
    "amount": 200,
    "new_balance": 1200
  }
}

// State transition
{
  "type": "player_state_change",
  "data": {
    "player_id": 3,
    "new_state": "purchase"
  }
}

### Create a Message Factory:

class JsonMessageFactory {
public:
    static QJsonObject createGameInitMessage(int playerCount);
    static QJsonObject createCardTransferMessage(const QString& from, const QString& to, std::shared_ptr<Card> card);
    static QJsonObject createDiceRollMessage(int playerId, const QVector<int>& results);
    // ... other message creation methods
};


### Message Parser:

class JsonMessageParser {
public:
    static QString getMessageType(const QJsonObject& message);
    static int parsePlayerTurnChange(const QJsonObject& message);
    static std::tuple<QString, QString, std::shared_ptr<Card>> parseCardTransfer(const QJsonObject& message);
    // ... other parsing methods
};

### Modify your components to use JSON:

// In GameLogic:
void GameLogic::handleJsonMessage(const QJsonObject& message) {
    QString type = JsonMessageParser::getMessageType(message);
    
    if (type == "card_purchase_attempt") {
        auto [playerId, cardId] = JsonMessageParser::parseCardPurchaseAttempt(message);
        // Handle purchase
        QJsonObject response;
        if (purchaseSuccessful) {
            response = JsonMessageFactory::createCardTransferMessage("bank", 
                                                                   QString("player_%1").arg(playerId),
                                                                   card);
        } else {
            response = JsonMessageFactory::createPurchaseFailedMessage(playerId, cardId, "insufficient_funds");
        }
        emit jsonMessageReady(response);
    }
    // ... other message types
}

### Network Integration (for future):

// In your network handler:
void NetworkManager::sendMessage(const QJsonObject& message) {
    QJsonDocument doc(message);
    socket->write(doc.toJson());
}

void NetworkManager::onDataReceived(const QByteArray& data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isNull()) {
        emit jsonMessageReceived(doc.object());
    }
}

MainWindow:
startMenu -> Network































