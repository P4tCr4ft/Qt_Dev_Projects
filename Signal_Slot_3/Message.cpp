#include "Message.h"

Message::Message()
{

}
Message::~Message(){

}

Message::Message(const Message &other){

}

Message::Message(const QString &body, const QStringList &headers) :
    m_body(body),
    m_headers(headers)
{

}

QString Message::body() const {
    return m_body;
}

QStringList Message::headers() const {
    return m_headers;
}
