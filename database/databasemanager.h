#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <vector>
#include <QString>
#include <QSqlDatabase>
#include <memory>
#include "entities/Note.h"

/**
 * @brief Класс Singleton для управления подключением к базе данных SQLite.
 *
 * Отвечает за открытие базы данных, создание таблиц и выполнение миграций.
 */
class DatabaseManager
{
public:
    /**
     * @brief Возвращает единственный экземпляр класса.
     * @return Ссылка на DatabaseManager.
     */
    static DatabaseManager& instance();

    /**
     * @brief Подключается к базе данных.
     * @return true, если подключение успешно, иначе false.
     */
    bool connect();

    /**
     * @brief Удаляет конструктор копирования (Singleton).
     */
    DatabaseManager(const DatabaseManager&) = delete;
    void operator=(const DatabaseManager&) = delete;

    bool addNote(Note& note);
    bool removeNote(int id);
    bool updateNote(const Note& note);
    std::vector<Note> getAllNotes();

private:
    DatabaseManager();
    ~DatabaseManager();

    bool createTables();

    QSqlDatabase m_database;
    const QString DATABASE_FILENAME = "notes_app.db";
};

#endif // DATABASEMANAGER_H
