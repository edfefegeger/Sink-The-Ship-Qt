#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

enum LogLevel {
    INFO,
    WARNING,
    ERROR
};

class logger {
public:
    logger();  // Объявляем конструктор по умолчанию
    void logToFile(const QString &message, LogLevel level);
};

#endif // LOGGER_H
