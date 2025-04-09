# City Building Card Game
Welcome to city-building card game! This project is inspired by the popular board game
Machi Koro.

**Read in:** [English](#) | [Русский (Russian)](README.ru.md)

## Table of Contents
- [About Machi Koro](#about-machi-koro)
- [Download Latest Release](#download-latest-release)
- [Features](#features)
- [Gameplay Description](#gameplay-description)
  - [Start Menu (Offline)](#start-menu-offline-mode---choose-number-of-players)
  - [Start Menu (Online)](#start-menu-online-mode---create-server-or-connect-client)
  - [Income State](#income-state)
  - [Build State](#build-state)
  - [New Player's Card Stack](#new-players-card-stack)
  - [Switch Player](#switch-to-another-player)
  - [Win Condition](#unlock-landmark-to-win)
- [Gameplay Rules](#gameplay-rules)
  - [Preparation](#prepation-to-the-game)
  - [Winning](#winning)
  - [Turn Structure](#turn-structure)
    - [Roll Dice](#1-roll-the-dice)
    - [Collect Income](#2-collect-income)
    - [Build Phase](#3build)
  - [Payments](#payments-between-players)
  - [Activation Order](#sequence-of-build-activations)
  - [Multiple Payments](#multiple-payments)
  - [Card Effects](#explanation-of-the-effects-of-the-card)

## About Machi Koro
Machi Koro is a fast-paced, card-based city-building game. For more information, check out
the [Machi Koro Wikipedia page](https://en.wikipedia.org/wiki/Machi_Koro).

## Download Latest Release
[2025-04-08 Release for Windows](https://gitlab.com/Den-One/city-building-card-game/-/archive/release-2025-04-08/city-building-card-game-release-2025-04-08.zip)

## Features

- Interactive UI made with Qt 6.8 framework and C++17.
- Multiplayer support [in development]

## Gameplay Description
### Start Menu (Offline mode) - Choose Number of Players
![Start Menu](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/start_menu.jpg)

* Select offline mode if you want to play from one device, controlling the moves of all players;
* To start - click on Start Offline Game.

### Start Menu (Online mode) - Create Server or Connect Client
![Start Menu Online](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/start_menu_online.jpg)

* Select offline mode if you want to play from diffrent devices in a local network;
* First player should create a server and choose players number;
* Click on "Create Server" button to run server in a local network;
* Click on "Connect to Server" button to connect to local server;
* A pop-up window will confirm the success or failure of the connection attempt.

### Income State
![Income State](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/income_state.jpg)

* Press the button "roll 1 dice" or "roll 2 dice" (if you own a Train Station);
* Wait for update for "Dice Result" label;
* If the dice rolls the number shown on the top of the card, the card is activated and players receive income;
* It leads to update of "Coins" label.

### Build State
![Build State](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/build_state.jpg)

* Check the card price in the lower left corner of the card;
* If you have enough coins:
* Select a card from the bank (on the left side of the screen);
* Or select a landmark (on the upper right side of the screen);
* Or click the "skip" button;
* Do it one more time, if the dice rolled a double and you own an amusement park.

### New Player's Card Stack
![New Player's Card Stack](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/display_new_card.jpg)

* Each purchased card is moved to the player's building inventory, reducing the coin balance;
* After buying or skipping a turn, the turn immediately passes to the next player.

### Switch to Another Player
![Switch to Another Player](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/go_to_next.jpg)

* The new active player is displayed on top of the right tab with a green dot;
* The player's tab with a green dot always has active buttons to press, the rest are inactive buttons;
* Any player can at any time select another player's section to view his cards according to the game conditions.

### Unlock Landmark to Win
![Unlock Landmark to Win](https://gitlab.com/Den-One/city-building-card-game/-/raw/main/documents/unlock_landmark.jpg)

* The main goal of the game is to buy all the attractions;
* If you have enough coins to buy, buy the landmark; 
* The purchased landmark is displayed in gold.

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

### Payments Between Players

If a player can't fully repay another player due to insufficient coins, they 
must pay whatever they have. The bank does not cover the remaining debt. If 
the debtor has no coins at all, the owed player receives nothing.


The order of business activations must be **strictly followed**. **Cafés and 
restaurants** are activated first. If a player owes coins to another 
(due to their restaurants), this payment is settled before they collect 
income from their other businesses.

### Example of One Player Turn

1. The dice result is "3".
2. The dice activates the effect of opponent red cards.
3. The debtor does not have enough coins to pay the debt of opponent's card effect,
so opponent doesn't get any coins.
4. The player receives one coin for each of his groceries.

### Sequence of Build Activations

When a single die roll triggers multiple types of businesses, they must be activated 
in this specific order:

1. **Cafés & Restaurants (Red cards)**
2. **Medium Businesses (Green cards)**
3. **Small Businesses (Blue cards)**
4. **Large Businesses (Purple cards)**

**Important**: If you own multiple copies of the same business card, each one is 
activated separately whenever the corresponding number is rolled.

### Multiple Payments

If a player owes coins to multiple opponents simultaneously, the payments are 
resolved in reverse turn order **(counterclockwise)**. 


The debtor must fully settle the debt with the first opponent before paying 
the next one. If they lack sufficient funds, they pay what they can to each 
creditor in sequence, with no compensation from the bank for any remaining 
unpaid amounts.

### Explanation of the Effects of the Card

**SHOPPING MALL** - This establishment doesn’t produce income on its own but 
boosts earnings from your shop or cafe-type cards. **The Shopping Mall** enhances 
all your cards of these types. For example, if you own two **Bakeries**, 
rolling a **2** or **3** will now grant you **4** coins in total 
(instead of the usual 2).

**BUSINESS CENTER** - When activated, the current player can swap one of 
their business cards with an opponent's. They decide which card to offer 
and which one to request in return. However, the player has the option to 
decline the exchange and keep their cards as they are.

(Key points: The active player controls the trade, choosing both the card 
to give and the one to take—or they may choose not to trade at all.)

*Business Center feature is currently in development and not yet available. Stay tuned for updates!*
