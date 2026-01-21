#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QVariant>
#include "entities/Note.h"

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

bool DatabaseManager::addNote(Note& note)
{
    QSqlQuery query;
    query.prepare("INSERT INTO notes (title, content) VALUES (:title, :content)");
    query.bindValue(":title", note.title);
    query.bindValue(":content", note.content);

    if (query.exec()) {
        note.id = query.lastInsertId().toInt();
        return true;
    }

    qCritical() << "Failed to add note:" << query.lastError().text();
    return false;
}

bool DatabaseManager::updateNote(const Note& note)
{
    QSqlQuery query;
    query.prepare("UPDATE notes SET title = :title, content = :content WHERE id = :id");
    query.bindValue(":title", note.title);
    query.bindValue(":content", note.content);
    query.bindValue(":id", note.id);

    if (query.exec()) {
        return true;
    }

    qCritical() << "Failed to update note:" << query.lastError().text();
    return false;
}

bool DatabaseManager::removeNote(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM notes WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

std::vector<Note> DatabaseManager::getAllNotes()
{
    std::vector<Note> notes;
    QSqlQuery query("SELECT id, title, content, created_at FROM notes ORDER BY created_at DESC");

    while (query.next()) {
        Note note;
        note.id = query.value(0).toInt();
        note.title = query.value(1).toString();
        note.content = query.value(2).toString();
        note.createdAt = query.value(3).toDateTime().toString("yyyy-MM-dd HH:mm");
        notes.push_back(note);
    }
    return notes;
}
