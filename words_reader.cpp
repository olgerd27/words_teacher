#include <QTextStream>
#include <stdexcept>
#include "words_reader.h"
#include "wordwt.h"
#include "settings_names.h"

WordsReader::WordsReader(const QString &filename, char sepWT, char sepTT, QObject *parent)
    : QFile(filename, parent)
    , m_sep_wt(sepWT)
    , m_sep_tt(sepTT)
    , m_lineCount(0)
{
    if (!open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error( (tr("Cannot open a file: ") + filename).toStdString() );
}

WordsReader::~WordsReader()
{
    close();
}

//#include <QTextCodec>
WordWT * WordsReader::getWord()
{
    static QTextStream stream(this);
//    if (m_lineCount == 0) {
//        qDebug() << "codec: " << stream.codec()->name();
//        stream.setCodec("windows-1251"); // set encoding
//    }
    m_lineCount++;
    return stream.atEnd() ? 0 : parseWordAndTranslations(stream.readLine());
}

WordWT * WordsReader::parseWordAndTranslations(const QString &line) const
{
    if (line.isEmpty()) {
        emit sigWarningOccured( tr("Parsing file line"),
                                tr("Empty readed line #") + QString::number(m_lineCount) );
        return 0;
    }

    QStringList word_trans = line.split(m_sep_wt);
    if (word_trans.size() > 2)
        throw std::runtime_error( (tr("To many the word-translations separators") + QString(" \"%1\" ").arg(m_sep_wt) +
                                   tr("in the file line") +
                                   QString(" #%2: %3").arg(m_lineCount).arg(line)).toStdString() );

    WordWT *word = new WordWT(word_trans.at(0));
    QStringList trans = word_trans.at(1).split(m_sep_tt);
    if (trans.size() == 0)
        throw std::runtime_error( (tr("No one translation was found in the file to the word: ") +
                                   word_trans.at(0)).toStdString() );

    foreach (const QString &trWord, trans) {
        word->addTranslation(trWord.trimmed());
    }
    return word;
}
