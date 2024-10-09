#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
class Submarine {
public:
    QRect rect;

    Submarine(int x, int y, int width, int height)
        : rect(x, y, width, height) {}

    void moveLeft() {
        if (rect.left() > 0) {  // Проверяем левую границу
            rect.moveLeft(rect.left() - 10);  // Двигаем влево
        }
    }

    void moveRight(int screenWidth) {
        if (rect.right() < screenWidth) {  // Проверяем правую границу
            rect.moveLeft(rect.left() + 10);  // Двигаем вправо
        }
    }
};

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
    void restartGame();
    void showTopResults();  // слот для отображения топ-результатов

private:
    void checkLevel();
    void saveResult();  // метод для сохранения результата
    void loadTopResults();  // метод для загрузки топ-результатов

    QList<Ship> ships;
    QList<Torpedo> torpedoes;
    QTimer *timer;
    Submarine submarine;
    int score;
    int torpedoCount;
    int level;
    int ships_destroyed;
    QPushButton *restartButton;
    QPushButton *topResultsButton;  // Кнопка для показа топ-результатов

    QVector<QPair<int, QString>> topResults;  // Хранение пар (счет, имя)
};

#endif // GAMEWIDGET_H
