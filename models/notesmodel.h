#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QAbstractListModel>
#include <vector>
#include "../entities/Note.h"

/**
 * @brief Модель данных для отображения списка заметок в QML.
 * * Наследуется от QAbstractListModel. Предоставляет интерфейс для:
 * - Отображения данных в ListView (роли Title, Content, Date).
 * - Управления данными из QML (методы Q_INVOKABLE).
 */
class NotesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NoteRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        ContentRole,
        DateRole
    };

    explicit NotesModel(QObject *parent = nullptr);

    /**
     * @brief Возвращает количество строк (заметок) в модели.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Возвращает данные для конкретного индекса и роли.
     * @param index Индекс элемента в списке.
     * @param role Роль данных (например, TitleRole).
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Маппинг ролей (C++ enum) в имена свойств (QML string).
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Создает новую заметку.
     * Метод вызывается из QML. Сохраняет заметку в БД и обновляет интерфейс.
     * @param title Заголовок.
     * @param content Текст заметки.
     */
    Q_INVOKABLE void addNote(const QString &title, const QString &content);

    /**
     * @brief Удаляет существующую заметку.
     * @param index индекс заметки.
     */
    Q_INVOKABLE void removeNote(int index);

    /**
     * @brief Обновляет существующую заметку.
     * @param id ID заметки в базе данных.
     * @param title Новый заголовок.
     * @param content Новый текст.
     */
    Q_INVOKABLE void updateNote(int id, const QString &title, const QString &content);

private:
    std::vector<Note> m_notes;
    void loadNotes();
};

#endif // NOTESMODEL_H
