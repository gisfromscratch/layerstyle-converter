#include "osmsymbol.h"

OsmSymbol::OsmSymbol(QObject *parent) : QObject(parent)
{

}

void OsmSymbol::setSymbolClass(const QString &symbolClass)
{
    m_symbolClass = symbolClass;
}

QString OsmSymbol::symbolClass() const
{
    return m_symbolClass;
}

void OsmSymbol::setPass(const QString &pass)
{
    m_pass = pass;
}

QString OsmSymbol::pass() const
{
    return m_pass;
}

void OsmSymbol::setProperty(const QString &name, const QString &value)
{
    m_properties.insert(name, value);
}

QMap<QString, QString> OsmSymbol::properties() const
{
    return m_properties;
}
