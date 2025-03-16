## Signal slot paths
### Player buys a new Building | Landmark
1. CardWidget::clicked -> MainWindow::handleCardClick
2. MainWindow::cardWidgetClicked -> GameLogic::handleTryToBuyCard
3.1. GameLogic::playerBuildNewBuilding -> MainWindpw::displayPlayerNewCard
3.2. GameLogic::playerBuildLandmark -> MainWindow::unlockPlayerLandmark
4. MainWindow::updatedPlayersPanel -> GameLogic::prepateNextTurn

### User starts a new game & create players
1. CardWidget::showMainWindow -> MainWindow::handleShowMainWindow
2. MainWindow::createPlayers -> GameLogic::handleCreatePlayers

### Player clicked Roll Button
1.1. QPushButton::clicked -> MainWindow::onRollOneDiceClicked // roll the dice, display it
1.2. QPushButton::clicked -> MainWindow::onRollTwoDiceClicked // roll the dice, display it
2. MainWindow::checkPlayerCards -> GameLogic::processCheckPlayerCards // make Radio Tower work before step
3. GameLogic::playerCardActivatedBefore -> MainWindow::handlePlayerCardActivatedBefore // tower activated, ask a question

4.1. MainWindow::rollButtonClickedWithCanReroll -> state buyOrRecollState
4.2. MainWindow::diceRollAccepted -> GameLogic::handleRollButtonClicked
5. GameLogic::playerBalanceChanged -> MainWindow::updatePlayerBalanceLabel

### Move to next Player & Player Bought a building & Player clicked skip button
1. MainWindow::skipClicked -> GameLogic::moveToNextPlaer
2. GameLogic::buildStageFinished -> MainWindow::repaintPlayerPanel

### Railway Station Activation
1. Player::hasRailwayStation -> GameLogic::handlePlayerHasRailwayStation
2. GameLogic::playerHasRailwayStation -> MainWindow::unlockRollTwoDiceButton
3. 
