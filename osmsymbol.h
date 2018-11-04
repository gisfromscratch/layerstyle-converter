#ifndef OSMSYMBOL_H
#define OSMSYMBOL_H

#include <QMap>
#include <QObject>

class OsmSymbol : public QObject
{
    Q_OBJECT
public:
    explicit OsmSymbol(QObject *parent = nullptr);

    void setSymbolClass(const QString &symbolClass);
    QString symbolClass() const;

    void setPass(const QString &pass);
    QString pass() const;

    void setProperty(const QString &name, const QString &value);
    QMap<QString, QString> properties() const;

signals:

public slots:

private:
    QString m_symbolClass;
    QString m_pass;
    QMap<QString, QString> m_properties;
};

#endif // OSMSYMBOL_H
