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
1. MainWindow::rollButtonClicked -> GameLogic::handleRollButtonClicked
2. GameLogic::playerBalanceChanged -> MainWindow::updatePlayerBalanceLabel

### Move to next Player & Player Bought a building & Player clicked skip button
1. MainWindow::skipClicked -> GameLogic::moveToNextPlaer
2. GameLogic::buildStageFinished -> MainWindow::repaintPlayerPanel
