#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), score(0), torpedoCount(10), level(1) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
    timer->start(30);
    spawnShips();
}

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    for (const Ship &ship : ships) {
        painter.drawRect(ship.rect);
    }
    for (const Torpedo &torpedo : torpedoes) {
        painter.drawRect(torpedo.rect);
    }
    painter.drawText(10, 10, "Score: " + QString::number(score));
    painter.drawText(10, 30, "Torpedoes left: " + QString::number(torpedoCount));
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && torpedoCount > 0) {
        torpedoes.append(Torpedo(width() / 2, height() - 20, 5, 10, 5));
        torpedoCount--;
    }
}

void GameWidget::updateGame() {
    for (Ship &ship : ships) {
        ship.move();
    }
    for (Torpedo &torpedo : torpedoes) {
        torpedo.move();
    }
    checkCollisions();
    update();
}

void GameWidget::checkCollisions() {
    for (int i = 0; i < torpedoes.size(); ++i) {
        for (int j = 0; j < ships.size(); ++j) {
            if (torpedoes[i].rect.intersects(ships[j].rect)) {
                score += ships[j].scoreValue;
                ships.removeAt(j);
                torpedoes.removeAt(i);
                break;
            }
        }
    }
}

void GameWidget::spawnShips() {
    ships.append(Ship(width(), 50, 50, 20, 2, 3));
    ships.append(Ship(width(), 100, 70, 20, 1, 2));
    ships.append(Ship(width(), 150, 90, 20, 1, 1));
}
