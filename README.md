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
### Start Menu
![alt text](https://gitlab.com/Den-One/city-building-card-game/-/blob/main/documents/build_state.jpg?ref_type=heads)
### Income State
![alt text](https://gitlab.com/Den-One/city-building-card-game/-/blob/main/documents/income_state.jpg)
### Build State
![alt text](https://gitlab.com/Den-One/city-building-card-game/-/blob/main/documents/build_state.jpg)
### New Player's Card Stack
![alt text](https://gitlab.com/Den-One/city-building-card-game/-/blob/main/documents/display_new_card.jpg)
### Switch to Another Player
![alt text](https://gitlab.com/Den-One/city-building-card-game/-/blob/main/documents/go_to_next.jpg)
### Unlock Landmark to Win
![alt text](https://gitlab.com/Den-One/city-building-card-game/-/blob/main/documents/unlock_landmark.jpg)

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

