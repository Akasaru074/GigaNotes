#include "notesmodel.h"
#include "database/databasemanager.h"
#include <QDebug>

NotesModel::NotesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    loadNotes();
}

int NotesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return static_cast<int>(m_notes.size());
}

QVariant NotesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_notes.size())
        return QVariant();

    const Note &note = m_notes.at(index.row());

    switch (role) {
    case IdRole:      return note.id;
    case TitleRole:   return note.title;
    case ContentRole: return note.content;
    case DateRole:    return note.createdAt;
    default:          return QVariant();
    }
}

QHash<int, QByteArray> NotesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "title";
    roles[ContentRole] = "content";
    roles[DateRole] = "date";
    return roles;
}

void NotesModel::addNote(const QString &title, const QString &content)
{
    Note note;
    note.title = title;
    note.content = content;

    if (DatabaseManager::instance().addNote(note)) {
        beginInsertRows(QModelIndex(), 0, 0);
        m_notes.insert(m_notes.begin(), note);
        endInsertRows();
    }
}

void NotesModel::removeNote(int index)
{
    if (index < 0 || index >= m_notes.size()) return;

    int idToRemove = m_notes[index].id;

    if (DatabaseManager::instance().removeNote(idToRemove)) {
        beginRemoveRows(QModelIndex(), index, index);
        m_notes.erase(m_notes.begin() + index);
        endRemoveRows();
    }
}

void NotesModel::loadNotes()
{
    beginResetModel();
    m_notes = DatabaseManager::instance().getAllNotes();
    endResetModel();
}
