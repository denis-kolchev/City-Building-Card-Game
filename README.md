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


QVector<Card*> getBuildsWithDiceAndType(CardType cardType);

fields:

QMap<Card*, uchar> builds; // How many card a player owns

uchar money;

QVector<uchar> curentDice;


### Possible Architecture solutions
1. Event-driven architecture 
2. Publish-subscribe pattern


The idea is that while player rollTheDice, we can publish some  
events. The Cards can be subscribed to the events to react to them.


// Event system
class EventBus {
public:
    using EventHandler = std::function<void()>;

    void subscribe(const std::string& eventName, EventHandler handler) {
        eventHandlers[eventName].push_back(handler);
    }

    void publish(const std::string& eventName) {
        if (eventHandlers.find(eventName) != eventHandlers.end()) {
            for (auto& handler : eventHandlers[eventName]) {
                handler();
            }
        }
    }

private:
    std::unordered_map<std::string, std::vector<EventHandler>> eventHandlers;
};

class Player {
public:
    Player(EventBus& eventBus) : eventBus(eventBus) {}

    void rollDice() {
        int dice1 = rollDie();
        int dice2 = rollDie();
        
        if (dice1 == dice2) {
            eventBus.publish("onDoublesRolled");
        }

        eventBus.publish("onDiceRolled");
    }

private:
    EventBus& eventBus;

    int rollDie() {
        return rand() % 6 + 1;
    }
};


class Card {
public:
    Card(EventBus& eventBus) : eventBus(eventBus) {}
    virtual ~Card() = default;

protected:
    EventBus& eventBus;
};

class AmusementPark : public Card {
public:
    AmusementPark(EventBus& eventBus, Game& game) : Card(eventBus), game(game) {
        // Subscribe to the "onDoublesRolled" event
        eventBus.subscribe("onDoublesRolled", [this]() {
            std::cout << "Amusement Park effect triggered!" << std::endl;
            game.grantExtraTurn();
        });
    }

private:
    Game& game;
};

class Game {
public:
    Game(EventBus& eventBus) : eventBus(eventBus) {}

    void playTurn(Player& player) {
        player.rollDice();

        // Check for extra turns
        while (extraTurns > 0) {
            extraTurns--;
            std::cout << "Taking an extra turn!" << std::endl;
            player.rollDice();
        }
    }

    void grantExtraTurn() {
        extraTurns++;
    }

private:
    EventBus& eventBus;
    int extraTurns = 0;
};


It still counts turns times.

class TurnManager {
public:
    TurnManager(EventBus& eventBus) : eventBus(eventBus) {
        // Subscribe to the "onExtraTurnRequested" event
        eventBus.subscribe("onExtraTurnRequested", [this]() {
            std::cout << "Extra turn granted!" << std::endl;
            takeTurn(); // Take an extra turn
        });
    }

    void startGame() {
        takeTurn();
    }

private:
    EventBus& eventBus;

    void takeTurn() {
        std::cout << "Starting a new turn..." << std::endl;
        eventBus.publish("onTurnStarted");
    }
};

class Card {
public:
    Card(EventBus& eventBus) : eventBus(eventBus) {}
    virtual ~Card() = default;

protected:
    EventBus& eventBus;
};

class AmusementPark : public Card {
public:
    AmusementPark(EventBus& eventBus) : Card(eventBus) {
        // Subscribe to the "onDoublesRolled" event
        eventBus.subscribe("onDoublesRolled", [this]() {
            std::cout << "Amusement Park effect triggered!" << std::endl;
            eventBus.publish("onExtraTurnRequested"); // Request an extra turn
        });
    }
};


Adding some Qt signal\slot system

class Player : public QObject {
    Q_OBJECT

public:
    Player(QObject* parent = nullptr) : QObject(parent) {}

    void rollDice() {
        int dice1 = rollDie();
        int dice2 = rollDie();

        qDebug() << "Rolled:" << dice1 << "and" << dice2;

        emit diceRolled(dice1, dice2);

        if (dice1 == dice2) {
            emit doublesRolled();
        }
    }

signals:
    void diceRolled(int dice1, int dice2);
    void doublesRolled();

private:
    int rollDie() {
        return rand() % 6 + 1;
    }
};

class Card : public QObject {
    Q_OBJECT

public:
    Card(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Card() = default;
};

class AmusementPark : public Card {
    Q_OBJECT

public:
    AmusementPark(QObject* parent = nullptr) : Card(parent) {
        // Connect the doublesRolled signal to the onDoublesRolled slot
        connect(parent, SIGNAL(doublesRolled()), this, SLOT(onDoublesRolled()));
    }

public slots:
    void onDoublesRolled() {
        qDebug() << "Amusement Park effect triggered! Requesting an extra turn...";
        emit extraTurnRequested();
    }

signals:
    void extraTurnRequested();
};

class TurnManager : public QObject {
    Q_OBJECT

public:
    TurnManager(QObject* parent = nullptr) : QObject(parent) {}

    void startGame() {
        takeTurn();
    }

public slots:
    void takeTurn() {
        qDebug() << "Starting a new turn...";
        // Logic for handling a turn
    }

    void handleExtraTurnRequested() {
        qDebug() << "Extra turn granted!";
        takeTurn();
    }
};

#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    Player player;
    TurnManager turnManager;
    AmusementPark amusementPark;

    // Connect signals and slots
    QObject::connect(&player, SIGNAL(doublesRolled()), &amusementPark, SLOT(onDoublesRolled()));
    QObject::connect(&amusementPark, SIGNAL(extraTurnRequested()), &turnManager, SLOT(handleExtraTurnRequested()));

    // Start the game
    turnManager.startGame();

    // Simulate a dice roll
    player.rollDice();

    return app.exec();
}


Cards can affect the active player (the one rolling the dice).
Cards can affect other players (e.g., stealing coins or triggering effects).
Cards can affect both the active player and their owner.
Cards can have stacking effects (e.g., multiple copies of the same card multiply the effect).
To handle this, we need to extend the system to:

Track multiple players and their card inventories.
Allow cards to target specific players (active player, card owner, or others).
Support stacking effects for multiple copies of the same card.


So that all means


### 1. Player class
* has a unique id
* a collection of its own cards
* methods to modify their state

START_COINS_NUMBER = 3;

clas Player : final public QObject {
    Q_OBJECT
    
public;
    Player(uchar id, QObject* parent = nullptr)
        : QObject(parent), m_id(id), coins(START_COINS_NUMBER) {}
    
    uchar id() const { return m_id; }
    
    uchar coins() const { return coins; }
    
    void addCoins(uchar amount) { coins += amount; };
    
    void takeCoins(uchar amount) { coins -= amount; }
    
    void buyBuild(Card* card) { cards.append(card); }
    
    const QList<Card*>& getCards() const { return cards; }
    
private:
    uchar m_id;
    uchar m_coins;
    QMap<Card*, int> cards;
};


class GameEvents final : public QObject {
    Q_OBJECT
    
public:
    GameEvents(QObject* parent = nullptr) : QObject(parent) {}
    
signals:
    void diceRolled(uchar dice1, uchar dice2, Player* activePlayer);
    
    void cardTriggered(Card* card, Player* active, Player* cardOwner);
    
public slots:
    void resolveCardEffects(int dice1, int dice2, Player* activePlayer) {
        // notify all player to resolve their card effects
        emit diceRolled(dice1, dice2, activePlayer);
    }
};


class Card : public QObject {
    Q_OBJECT

public:
    Card(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Card() = default;
};

class TakeCoinsCard : public Card {
    Q_OBJECT

public:
    TakeCoinsCard(int amount, QObject* parent = nullptr)
        : Card(parent), amount(amount) {
        // Connect to the diceRolled signal
        connect(parent, SIGNAL(diceRolled(int, int, Player*)), this, SLOT(onDiceRolled(int, int, Player*)));
    }

public slots:
    void onDiceRolled(int dice1, int dice2, Player* activePlayer) {
        // Check if this card should trigger based on the dice roll
        if (shouldTrigger(dice1, dice2)) {
            // Get the owner of this card
            Player* owner = qobject_cast<Player*>(parent());

            // Apply the effect
            if (owner == activePlayer) {
                // Affect the active player
                activePlayer->addCoins(amount);
            } else {
                // Affect the card owner
                owner->addCoins(amount);
            }
        }
    }

private:
    bool shouldTrigger(int dice1, int dice2) {
        // Example: Trigger if the dice sum matches a specific value
        return (dice1 + dice2) == 7;
    }

    int amount;
};

## Let's start over
### 1. Core Classes
* Player: id, coins, cards collection
* Card: base for derived classes with specific behavior
* GameEvents: central event system which emits signals for game events (like dice roll)
* Game Logic: manages the game state, players, and turn flow


### 2. Player
class Player : public QObject {
    Q_OBJECT

public:
    Player(int playerId, QObject* parent = nullptr)
        : QObject(parent), playerId(playerId), coins(0) {}

    int getPlayerId() const { return playerId; }
    int getCoins() const { return coins; }

    void addCoins(int amount) {
        coins += amount;
        qDebug() << "Player" << playerId << "now has" << coins << "coins.";
    }

    void takeCoins(int amount) {
        coins -= amount;
        qDebug() << "Player" << playerId << "lost" << amount << "coins.";
    }

    void addCard(QObject* card) {
        cards.append(card);
    }

    const QList<QObject*>& getCards() const {
        return cards;
    }

private:
    int playerId;
    int coins;
    QList<QObject*> cards;
};

### 3. GameEvent
class GameEvents : public QObject {
    Q_OBJECT

public:
    GameEvents(QObject* parent = nullptr) : QObject(parent) {}

signals:
    void diceRolled(int dice1, int dice2, Player* activePlayer);

public slots:
    void resolveCardEffects(int dice1, int dice2, Player* activePlayer) {
        emit diceRolled(dice1, dice2, activePlayer);
    }
};

### 4. Card classes

class Card : public QObject {
    Q_OBJECT

public:
    Card(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Card() = default;
};

class TakeCoinsCard : public Card {
    Q_OBJECT

public:
    TakeCoinsCard(int amount, QObject* parent = nullptr)
        : Card(parent), amount(amount) {
        connect(parent, SIGNAL(diceRolled(int, int, Player*)), this, SLOT(onDiceRolled(int, int, Player*)));
    }

public slots:
    void onDiceRolled(int dice1, int dice2, Player* activePlayer) {
        if (shouldTrigger(dice1, dice2)) {
            Player* owner = qobject_cast<Player*>(parent());

            // Count the number of copies of this card owned by the player
            int cardCount = 0;
            for (QObject* card : owner->getCards()) {
                if (card->metaObject()->className() == this->metaObject()->className()) {
                    cardCount++;
                }
            }

            // Apply the effect multiplied by the number of copies
            int totalAmount = amount * cardCount;
            if (owner == activePlayer) {
                activePlayer->addCoins(totalAmount);
            } else {
                owner->addCoins(totalAmount);
            }
        }
    }

private:
    bool shouldTrigger(int dice1, int dice2) {
        // Example: Trigger if the dice sum matches a specific value
        return (dice1 + dice2) == 7;
    }

    int amount;
};
