#ifndef OSMRENDERER_H
#define OSMRENDERER_H

#include <QList>
#include <QObject>

class OsmSymbol;

class OsmRenderer : public QObject
{
    Q_OBJECT
public:
    explicit OsmRenderer(QObject *parent = nullptr);

    void setName(const QString &name);
    QString name() const;

    void setSymbolType(const QString &symbolType);
    QString symbolType() const;

    void setAlpha(const QString &alpha);
    QString alpha() const;

    void addSymbol(OsmSymbol *symbol);
    QList<OsmSymbol*> symbols() const;

signals:

public slots:

private:
    QString m_name;
    QString m_symbolType;
    QString m_alpha;
    QList<OsmSymbol*> m_symbols;
};

#endif // OSMRENDERER_H
