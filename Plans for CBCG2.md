# City Building Card Game 2

## Main Goal
Improve and clarify the user experience.

---

## 1. The main screen should be dockedWidget.
* The main screen should use a dock widget system.
* The current tab-based approach (when other players’ fields are hidden) is a bad idea and should be removed.

## UI Behavior
* Cards should respond to mouse movement with a subtle “bounce” effect (similar to macOS dock behavior).
* Inactive windows should appear greyed out.
* Each window should be movable within the dock system.

## Window Structure
* Each player has their own window displaying their table (cards).
* The shop is a separate area, likely positioned above or centrally.
* In some cases, it may also make sense to allow separate windows.

### 2 Players Case
--------------------------|
|                         |
|          Shop           |
|                         |
|-------------------------|
|            |            |
|   Play 1   |   Play 2   |
|            |            |
--------------------------|

### 3 Players Case
--------------------------|
|            |            |
|    Shop    |   Play 3   |
|            |            |
|-------------------------|
|            |            |
|   Play 1   |   Play 2   |
|            |            |
--------------------------|

### 4 Players Case
--------------------------|
|           Shop          |
|-------------------------|
|            |            |
|   Play 4   |   Play 3   |
|            |            |
|-------------------------|
|            |            |
|   Play 1   |   Play 2   |
|            |            |
--------------------------|

---

## 2. Scalability
* The UI should be fully scalable.
* Cards should automatically scale up/down depending on available space.
* If space is limited, cards should:
    * Become smaller
    * Be arranged into multiple rows

---

## 3. Separated Architecture
* Game data (logic layer) is one independent part.
* UI (widgets) is another independent part.

## Communication
* Widgets should emit signals describing user actions and state changes.
* These signals can be sent to other application instances (for multiplayer interaction).

---

## 4. Interaction Details
* The interaction should feel similar to classic solitaire:
    * Drag & drop cards
    * Click to select cards
* The player should:
    * Be able to choose where to place a card
    * Feel a sense of control and flexibility
* Additional features:
    * Ability to sort cards
    * Possibly a search bar for cards
    * Placement preview before confirming an action
    * Snappy and responsive placement behavior

---

## 5. Dice Roll System
* Dice rolling should be implemented as a popup dialog with animation.

## Behavior:
* First, calculate the result
* Then display a short animation
* Use multiple animation variations to avoid the feeling that the result is predetermined.

---

## 6. Zoom Behavior
* Zooming out may hide non-essential details:
    * Card descriptions can be hidden
* Important gameplay information must always remain visible

---

## 7. Multi-Instance Development
* The system should be designed from the beginning to support multiple application instances (one per player).
* Inter-application communication must be considered early in development.

---

## 8. Development Strategy
* Do not build the entire system at once.
* Clearly separate:
    * Data layer
    * UI layer
    * Communication between UI and data
* Develop and test these parts independently
