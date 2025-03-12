## Signal slot queue
### The build purchase by Player

It seems like making a CardReserve as a 4th class was a bed Idea. It's still a part of gameLogic.\n
Nothing desters it to get back. It makes communication between UI and logic too complicated.

1. CardWidget::clicked(QString cardTitle) -> MainWindow::handleCardClick(QString cardTitle)
2. MainWindow::cardWidgetClicked(QString cardTitle) -> GameLogic::checkCoinBalanceForCard(QString cardTitle)
3. GameLogic::tryToBuyCard(QString cardTitle, uchar playerBalance) -> CardReserve::handleTryToBuyCard(QString cardTitle, uchar playerBalance)
4. CardReserve::sellCardToPlayer(shared_ptr<Card> card) -> GameLogic::giveCardToPlayer(shared_ptr<Card> card);
5. GameLogic::playerBuildNewBuilding(shared_ptr<Card> card) -> MainWindpw::displayPlayerNewCard(shared_ptr<Card> card);


Let's try to shrink it
1. CardWidget::clicked(QString cardTitle) -> MainWindow::handleCardClick(QString cardTitle)
2. MainWindow::cardWidgetClicked(QString cardTitle) -> GameLogic::handleTryToBuyCard(QString cardTitle)
3. GameLogic::playerBuildNewBuilding(shared_ptr<Card> card) -> MainWindpw::displayPlayerNewCard(shared_ptr<Card> card);
