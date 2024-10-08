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

    // Рисуем подводную лодку в виде треугольника
    painter.setBrush(Qt::blue);  // Задаем цвет для подводной лодки
    QPolygon submarineShape;
    submarineShape << QPoint(submarine.rect.left(), submarine.rect.bottom())
                   << QPoint(submarine.rect.right(), submarine.rect.bottom())
                   << QPoint(submarine.rect.center().x(), submarine.rect.top());
    painter.drawPolygon(submarineShape);

    // Рисуем корабли
    for (const Ship &ship : ships) {
        painter.setBrush(Qt::green);  // Задаем цвет для кораблей
        painter.drawRect(ship.rect);
    }

    // Рисуем торпеды
    for (const Torpedo &torpedo : torpedoes) {
        painter.setBrush(Qt::red);  // Задаем цвет для торпед
        painter.drawRect(torpedo.rect);
    }

    // Отображаем счет, оставшиеся торпеды и уровень
    painter.drawText(10, 10, "Score: " + QString::number(score));
    painter.drawText(10, 30, "Torpedoes left: " + QString::number(torpedoCount));
    painter.drawText(10, 50, "Level: " + QString::number(level));
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
        submarine.moveRight(this->width());  // Передаем ширину окна
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
                spawnShips(); // Спавним новый корабль при уничтожении старого
                checkLevel(); // Проверка уровня
                return; // Выход из цикла, так как мы удалили торпеду
            }
        }
    }

    // Удаляем корабли, которые вышли за границу экрана
    for (int j = ships.size() - 1; j >= 0; --j) {
        if (ships[j].rect.right() < 0) {
            ships.removeAt(j);
            spawnShips(); // Спавним новый корабль
        }
    }
}

void GameWidget::spawnShips() {
    int randomY = qrand() % (height() - 100) + 50; // Случайное Y для нового корабля
    ships.append(Ship(width(), randomY, 50, 20, 2 + level, 3)); // Добавляем новый корабль с увеличенной скоростью на более высоких уровнях
}

void GameWidget::checkLevel() {
    int previousLevel = level;  // Store the current level before checking

    // Update the level based on the score
    if (score >= 40) {
        level = 5; // Уровень 3 от 20 до 30 очков
    }
    else if (score >= 30) {
        level = 4; // Уровень 2 от 10 до 20 очков
        }
    else if (score >= 20) {
        level = 3; // Уровень 2 от 10 до 20 очков
        }
     else if (score >= 10) {
        level = 2; // Уровень 2 от 10 до 20 очков
    } else if (score >= 0) {
        level = 1; // Уровень 1 от 0 до 10 очков
    }

    // Reset torpedoCount only when moving to a higher level
    if (level > previousLevel) {
        torpedoCount = 10;
    }
}

