#include "osmlayer.h"

OsmLayer::OsmLayer(QObject *parent) : QObject(parent)
{

}

void OsmLayer::setName(const QString &name)
{
    m_name = name;
}

QString OsmLayer::name() const
{
    return m_name;
}

void OsmLayer::setFilter(const QString &filter)
{
    m_filter = filter;
}

QString OsmLayer::filter() const
{
    return m_filter;
}

void OsmLayer::setSymbol(const QString &symbol)
{
    m_symbol = symbol;
}

QString OsmLayer::symbol() const
{
    return m_symbol;
}

void OsmLayer::setMaxScale(const QString &maxScale)
{
    m_maxScale = maxScale;
}

QString OsmLayer::maxScale() const
{
    return m_maxScale;
}

void OsmLayer::setMinScale(const QString &minScale)
{
    m_minScale = minScale;
}

QString OsmLayer::minScale() const
{
    return m_minScale;
}

void OsmLayer::setRenderer(OsmRenderer *renderer)
{
    m_renderer = renderer;
}

OsmRenderer* OsmLayer::renderer() const
{
    return m_renderer;
}
