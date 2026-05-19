/**
 * @author     A. KHOUK
 * @date       12.09.2024
 * @version    0.8
 * @copyright  Copyright (c) 2026, A. KHOUK.
 * @license    MIT licence
 */

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QString>
#include <QHash>

class Translator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(bool rtl READ rtl NOTIFY languageChanged)

public:
    explicit Translator(QObject *parent = nullptr);

    QString language() const;
    void setLanguage(const QString &language);
    bool rtl() const;

    Q_INVOKABLE QString text(const QString &key) const;

signals:
    void languageChanged();

private:
    QString m_language;
    QHash<QString, QHash<QString, QString>> m_texts;
};

#endif // TRANSLATOR_H
