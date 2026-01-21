#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QAbstractListModel>
#include <vector>
#include "../entities/Note.h"

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

    // Обязательные методы
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // QML
    Q_INVOKABLE void addNote(const QString &title, const QString &content);
    Q_INVOKABLE void removeNote(int index);
    Q_INVOKABLE void updateNote(int id, const QString &title, const QString &content);

private:
    std::vector<Note> m_notes;
    void loadNotes();
};

#endif // NOTESMODEL_H
