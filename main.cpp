#include <QApplication>
#include "gamewidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Создаем виджет игры
    GameWidget game;
    game.resize(400, 475);  // Задаем размер окна игры
    game.show();

    return app.exec();  // Запускаем главный цикл приложения
}
