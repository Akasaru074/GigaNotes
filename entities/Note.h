#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QDateTime>

struct Note {
    int id = -1;
    QString title;
    QString content; // MarkDown
    QString createdAt;
};

#endif // NOTE_H
