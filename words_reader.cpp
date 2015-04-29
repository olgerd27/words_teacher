#include <stdexcept>
#include "words_reader.h"
#include "wordwt.h"

WordsReader::WordsReader(const QString &filename, char sepWT, char sepT, QObject *parent)
    : QFile(filename, parent)
    , m_sep_wt(sepWT)
    , m_sep_t(sepT)
    , m_lineCount(0)
{
    if (!open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error( (tr("Cannot open a file: ") + filename).toStdString() );
}

WordsReader::~WordsReader()
{
    close();
}

WordWT * WordsReader::getWord()
{
    ++m_lineCount;
    return atEnd() ? 0 : parseWordAndTranslations(readLine());
}

WordWT * WordsReader::parseWordAndTranslations(const QByteArray &line) const
{
    QList<QByteArray> word_trans = line.split(m_sep_wt);
    if (word_trans.size() > 2)
        throw std::runtime_error( (tr("Unexpected quantity of separators") + QString(" \"%1\" ").arg(m_sep_wt) +
                                   tr("in the file line") + QString(" #%2: %3").arg(m_lineCount).arg(line.constData())).toStdString() );

    WordWT *word = new WordWT(word_trans.at(0).constData());
    QList<QByteArray> trans = word_trans.at(1).split(m_sep_t);
    if (trans.size() == 0)
        throw std::runtime_error( (tr("No one translation was found in the file to the: ") + word_trans.at(0)).toStdString() );
    foreach (QString tr, trans) {
        word->addTranslation(tr.trimmed().toStdString());
    }
    return word;
}
