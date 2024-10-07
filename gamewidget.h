#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QPainter>

class Ship {
public:
    QRect rect;
    int speed;
    int scoreValue;

    Ship(int x, int y, int width, int height, int speed, int score)
        : rect(x, y, width, height), speed(speed), scoreValue(score) {}

    void move() {
        rect.moveLeft(rect.left() - speed);
    }
};

class Torpedo {
public:
    QRect rect;
    int speed;

    Torpedo(int x, int y, int width, int height, int speed)
        : rect(x, y, width, height), speed(speed) {}

    void move() {
        rect.moveTop(rect.top() - speed);
    }
};

class GameWidget : public QWidget {
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame();
    void checkCollisions();
    void spawnShips();

private:
    QList<Ship> ships;
    QList<Torpedo> torpedoes;
    QTimer *timer;
    int score;
    int torpedoCount;
    int level;
};

#endif // GAMEWIDGET_H
