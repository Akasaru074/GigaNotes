#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager()
{

}

DatabaseManager::~DatabaseManager()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

bool DatabaseManager::connect()
{

    const QString driver = "QSQLITE";

    if (!QSqlDatabase::isDriverAvailable(driver)) {
        qCritical() << "Driver" << driver << "is not available.";
        return false;
    }

    m_database = QSqlDatabase::addDatabase(driver);

    QString location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(location);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString dbPath = dir.filePath(DATABASE_FILENAME);
    m_database.setDatabaseName(dbPath);

    qDebug() << "Database path:" << dbPath;

    if (!m_database.open()) {
        qCritical() << "Error opening database:" << m_database.lastError().text();
        return false;
    }

    return createTables();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;


    QString createQuery = R"(
        CREATE TABLE IF NOT EXISTS notes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            content TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";

    if (!query.exec(createQuery)) {
        qCritical() << "Error creating tables:" << query.lastError().text();
        return false;
    }

    return true;
}
