#ifndef MESSAGE_H
#define MESSAGE_H

// don't include Window.h here
// As C++ is lexical, include the headers
// in main.cpp in the correct order,
// ie, regarding the use of METATYPE

//#include "Window.h"

#include <QString>
#include <QStringList>
#include <QMetaType>

class Message
{

public:
    Message();
    Message(const Message &other);
    ~Message();

    Message(const QString &body, const QStringList &headers);

    QString body() const;
    QStringList headers() const;

private:
    QString m_body;
    QStringList m_headers;
};

Q_DECLARE_METATYPE(Message);

#endif // MESSAGE_H
