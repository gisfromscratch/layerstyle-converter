#include "osmrenderer.h"

OsmRenderer::OsmRenderer(QObject *parent) : QObject(parent)
{

}

void OsmRenderer::setName(const QString &name)
{
    m_name = name;
}

QString OsmRenderer::name() const
{
    return m_name;
}

void OsmRenderer::setSymbolType(const QString &symbolType)
{
    m_symbolType = symbolType;
}

QString OsmRenderer::symbolType() const
{
    return m_symbolType;
}

void OsmRenderer::setAlpha(const QString &alpha)
{
    m_alpha = alpha;
}

QString OsmRenderer::alpha() const
{
    return m_alpha;
}

void OsmRenderer::addSymbol(OsmSymbol *symbol)
{
    m_symbols.append(symbol);
}

QList<OsmSymbol*> OsmRenderer::symbols() const
{
    return m_symbols;
}
