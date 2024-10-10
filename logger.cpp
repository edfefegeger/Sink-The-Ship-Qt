#include "logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

logger::logger() {
    // Конструктор по умолчанию
}

void logger::logToFile(const QString &message, LogLevel level) {
    QFile logFile("game_log.txt");
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream logStream(&logFile);

        QString logLevelStr;
        switch (level) {
            case INFO:
                logLevelStr = "[INFO]";
                break;
            case WARNING:
                logLevelStr = "[WARNING]";
                break;
            case ERROR:
                logLevelStr = "[ERROR]";
                break;
        }

        logStream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << " "
                  << logLevelStr << " - " << message << "\n";
        logFile.close();
    }
}
