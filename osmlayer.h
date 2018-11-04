#ifndef OSMLAYER_H
#define OSMLAYER_H

#include <QObject>

class OsmRenderer;

class OsmLayer : public QObject
{
    Q_OBJECT
public:
    explicit OsmLayer(QObject *parent = nullptr);

    void setName(const QString &name);
    QString name() const;

    void setFilter(const QString &filter);
    QString filter() const;

    void setSymbol(const QString &symbol);
    QString symbol() const;

    void setMaxScale(const QString &maxScale);
    QString maxScale() const;

    void setMinScale(const QString &minScale);
    QString minScale() const;

    void setRenderer(OsmRenderer *renderer);
    OsmRenderer* renderer() const;

signals:

public slots:

private:
    QString m_name;
    QString m_filter;
    QString m_symbol;
    QString m_maxScale;
    QString m_minScale;
    OsmRenderer *m_renderer;
};

#endif // OSMLAYER_H
