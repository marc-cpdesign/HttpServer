#ifndef HTTP_SERVER_HTTP_COOKIE_H
#define HTTP_SERVER_HTTP_COOKIE_H

#include <QByteArray>
#include <QDateTime>
#include <QString>
#include <QUrl>

#include "util.h"


struct HTTPSERVER_EXPORT HttpCookie
{
    QString name;
    QString value;
    int ageSeconds = -1;
    QDateTime expiration;
    QString domain;
    QString path;
    bool secure = false;
    bool httpOnly = false;

    HttpCookie() {}
    HttpCookie(QString name_, QString value_, int ageSeconds_ = -1, QDateTime expiration_ = QDateTime(), QString domain_ = "",
        QString path_ = "/", bool secure_ = false, bool httpOnly_ = false) : name(name_), value(value_), ageSeconds(ageSeconds_),
        expiration(expiration_), domain(domain_), path(path_), secure(secure_), httpOnly(httpOnly_) {}

    QByteArray toByteArray() const
    {
        QByteArray buf;

        buf += name.toLatin1();
        buf += '=';
        buf += QUrl::toPercentEncoding(value);

        if (expiration.isValid()) {
            buf += "; Expires=" + expiration.toString(Qt::RFC2822Date).toLatin1();
        }

        if (ageSeconds > 0) {
            buf += "; Max-Age=" + QString::number(ageSeconds).toLatin1();
        }

        if (!domain.isEmpty()) {
            buf += "; Domain=" + domain.toLatin1();
        }

        if (!path.isEmpty()) {
            buf += "; Path=" + QUrl::toPercentEncoding(path);
        }

        if (secure) {
            buf += "; Secure";
        }

        if (httpOnly) {
            buf += "; HttpOnly";
        }

        return buf;
    }
};

#endif // HTTP_SERVER_HTTP_COOKIE_H
