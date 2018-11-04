#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <QXmlStreamReader>

#include "osmlayer.h"
#include "osmsymbol.h"
#include "osmrenderer.h"

static OsmLayer* readLayerRule(QXmlStreamReader &reader)
{
    OsmLayer *layer = new OsmLayer();
    QXmlStreamAttributes attributes = reader.attributes();
    if (attributes.hasAttribute("label"))
    {
        layer->setName(attributes.value("label").toString());
    }
    if (attributes.hasAttribute("filter"))
    {
        layer->setFilter(attributes.value("filter").toString());
    }
    if (attributes.hasAttribute("symbol"))
    {
        layer->setSymbol(attributes.value("symbol").toString());
    }
    if (attributes.hasAttribute("scalemaxdenom"))
    {
        layer->setMaxScale(attributes.value("scalemaxdenom").toString());
    }
    if (attributes.hasAttribute("scalemindenom"))
    {
        layer->setMinScale(attributes.value("scalemindenom").toString());
    }
    return layer;
}

static OsmRenderer* readRenderer(QXmlStreamReader &reader)
{
    OsmRenderer *renderer = new OsmRenderer();
    QXmlStreamAttributes attributes = reader.attributes();
    if (attributes.hasAttribute("name"))
    {
        renderer->setName(attributes.value("name").toString());
    }
    if (attributes.hasAttribute("type"))
    {
        renderer->setSymbolType(attributes.value("type").toString());
    }
    if (attributes.hasAttribute("alpha"))
    {
        renderer->setAlpha(attributes.value("alpha").toString());
    }
    return renderer;
}

static OsmSymbol* readLayerSymbol(QXmlStreamReader &reader)
{
    OsmSymbol *symbol = new OsmSymbol();
    QXmlStreamAttributes attributes = reader.attributes();
    if (attributes.hasAttribute("class"))
    {
        symbol->setSymbolClass(attributes.value("class").toString());
    }
    if (attributes.hasAttribute("pass"))
    {
        symbol->setPass(attributes.value("pass").toString());
    }
    return symbol;
}

static void readLayerSymbolProperty(QXmlStreamReader &reader, OsmSymbol *symbol)
{
    QXmlStreamAttributes attributes = reader.attributes();
    if (attributes.hasAttribute("k") && attributes.hasAttribute("v"))
    {
        QString key = attributes.value("k").toString();
        QString value = attributes.value("v").toString();
        symbol->setProperty(key, value);
    }
}

static void readRenderer(QXmlStreamReader &reader, QList<OsmLayer*> &layers)
{
    QMap<QString, OsmRenderer*> renderers;
    OsmRenderer *lastRenderer = NULL;
    OsmSymbol *lastSymbol = NULL;
    while (!reader.atEnd())
    {
        QXmlStreamReader::TokenType tokenType = reader.readNext();
        if (QXmlStreamReader::StartElement == tokenType
            && "rule" == reader.name())
        {
            OsmLayer *layer = readLayerRule(reader);
            layers.append(layer);
        }
        else if (QXmlStreamReader::StartElement == tokenType
            && "symbol" == reader.name())
        {
            OsmRenderer *renderer = readRenderer(reader);
            renderers.insert(renderer->name(), renderer);
            lastRenderer = renderer;
        }
        else if (QXmlStreamReader::StartElement == tokenType
            && "layer" == reader.name())
        {
            OsmSymbol *symbol = readLayerSymbol(reader);
            if (lastRenderer)
            {
                lastRenderer->addSymbol(symbol);
            }
            lastSymbol = symbol;
        }
        else if (QXmlStreamReader::StartElement == tokenType
            && "prop" == reader.name())
        {
            if (lastSymbol)
            {
                readLayerSymbolProperty(reader, lastSymbol);
            }
        }
    }

    int layerCount = layers.length();
    for (int layerIndex = 0; layerIndex < layerCount; layerIndex++)
    {
        OsmLayer *layer = layers.at(layerIndex);
        QString symbol = layer->symbol();
        if (renderers.contains(symbol))
        {
            OsmRenderer *renderer = renderers[symbol];
            layer->setRenderer(renderer);
        }
    }
}

static void writeLayers(QList<OsmLayer*> &layers, QString &outputPath)
{
    int layerCount = layers.length();
    for (int layerIndex = 0; layerIndex < layerCount; layerIndex++)
    {
        OsmLayer *layer = layers.at(layerIndex);
        QString layerName = layer->name();
        QFile layerFile(outputPath + QDir::separator() + layerName + ".lyr");
        if (layerFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream outputStream(&layerFile);
            outputStream << "name:" << layerName << endl;
            outputStream << "filter:" << layer->filter() << endl;
            if (!layer->minScale().isEmpty())
            {
                outputStream << "min-scale:" << layer->minScale() << endl;
            }
            if (!layer->maxScale().isEmpty())
            {
                outputStream << "max-scale:" << layer->maxScale() << endl;
            }
            OsmRenderer *renderer = layer->renderer();
            if (renderer)
            {
                outputStream << "renderer:" << renderer->symbolType() << endl;
                outputStream << "alpha:" << renderer->alpha() << endl;
                QList<OsmSymbol*> symbols = renderer->symbols();
                int symbolCount = symbols.length();
                for (int symbolIndex = 0; symbolIndex < symbolCount; symbolIndex++)
                {
                    OsmSymbol *symbol = symbols.at(symbolIndex);
                    outputStream << "\tsymbol-class:" << symbol->symbolClass() << endl;
                    outputStream << "\tpass:" << symbol->pass() << endl;
                    QMap<QString, QString> properties = symbol->properties();
                    QList<QString> keys = properties.keys();
                    int propertyCount = properties.size();
                    for (int propertyIndex = 0; propertyIndex < propertyCount; propertyIndex++)
                    {
                        QString key = keys.at(propertyIndex);
                        QString value = properties[key];
                        outputStream << "\t\t" << key << ":" << value << endl;
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QDir dataDir(QDir::homePath() + QDir::separator() + "Data" + QDir::separator());
    QStringList dataFiles = dataDir.entryList(QStringList() << "*.qml", QDir::Files);
    int fileCount = dataFiles.length();
    for (int fileIndex = 0; fileIndex < fileCount; fileIndex++)
    {
        QString fileName = dataFiles.at(fileIndex);
        QFile file(dataDir.absoluteFilePath(fileName));
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << fileName << " not found!" << endl;
            exit(0);
        }

        QList<OsmLayer*> layers;
        QXmlStreamReader reader(&file);
        while (!reader.atEnd())
        {
            while (reader.readNextStartElement())
            {
                if ("renderer-v2" == reader.name())
                {
                    readRenderer(reader, layers);
                }
            }
        }

        QString outputPath(QDir::homePath() + QDir::separator() + "Data");
        writeLayers(layers, outputPath);
        qDebug() << "Layers exported." << endl;
    }

    //return a.exec();
}
