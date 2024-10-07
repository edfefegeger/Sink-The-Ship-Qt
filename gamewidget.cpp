#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), score(0), torpedoCount(10), level(1), submarine(width() / 2 - 25, height() - 50, 50, 20) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
    timer->start(30);
    spawnShips();
}


void GameWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Рисуем подводную лодку
    painter.drawRect(submarine.rect);

    // Рисуем корабли
    for (const Ship &ship : ships) {
        painter.drawRect(ship.rect);
    }

    // Рисуем торпеды
    for (const Torpedo &torpedo : torpedoes) {
        painter.drawRect(torpedo.rect);
    }

    // Отображаем счет и оставшиеся торпеды
    painter.drawText(10, 10, "Score: " + QString::number(score));
    painter.drawText(10, 30, "Torpedoes left: " + QString::number(torpedoCount));
}


void GameWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && torpedoCount > 0) {
        // Запускаем торпеду из центра подводной лодки
        torpedoes.append(Torpedo(submarine.rect.center().x() - 2, submarine.rect.top() - 10, 5, 10, 5));
        torpedoCount--;
    }

    // Управляем подводной лодкой с помощью стрелок
    if (event->key() == Qt::Key_Left) {
        submarine.moveLeft();
    }
    if (event->key() == Qt::Key_Right) {
        submarine.moveRight();
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
