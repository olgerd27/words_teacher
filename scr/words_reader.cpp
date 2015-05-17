#include <QTextStream>
#include <QSettings>

#include <stdexcept>

#include "words_reader.h"
#include "wordwt.h"
#include "settings_names.h"

WordsReader::WordsReader(const QString &filename, QSettings *settings, QObject *parent)
    : QFile(filename, parent)
    , m_textStream(new QTextStream(this))
    , m_settings(settings)
    , m_lineCount(0)
{
    if (!open(QIODevice::ReadOnly | QIODevice::Text))
        criticalErrorOccured( tr("Cannot open a file") + ": " + filename );
    m_textStream->setCodec( m_settings->value( InstSettingsNames.SSname(SettingsNames::SS_codec), "UTF-8" )
                            .toByteArray().constData() );
}

WordsReader::~WordsReader()
{
    close();
    delete m_textStream;
}

WordWT * WordsReader::getWord()
{
    m_lineCount++;
    return m_textStream->atEnd() ? 0 : parseLine(m_textStream->readLine());
}

WordWT * WordsReader::parseLine(const QString &strLine)
{
    if (strLine.isEmpty()) {
        emit sigWarningOccured( tr("File loading - parsing file line"),
                                tr("Empty readed line #") + QString::number(m_lineCount) );
        return 0;
    }

    WordWT *word = new WordWT;
    QString strTranslations;
    parseWord(strLine, strTranslations, word);
    parseTranslations(word->word(WordWT::GetWithoutRepeat), strTranslations, word);
    return word;
}

void WordsReader::parseWord(const QString &line, QString &strTranslations, WordWT *word)
{
    /* extracting word */
    QString sep_wt = m_settings->value( InstSettingsNames.SSname(SettingsNames::SS_sep_wt), '-' ).toString();
    QStringList word_trans = line.split(sep_wt);
    if (word_trans.size() > 2) {
        criticalErrorOccured( tr("To many word-translations separators") + QString(" \"%1\" ").arg(sep_wt) +
                              tr("in the file line") + QString(" #%1:\n\"%2\"").arg(m_lineCount).arg(line) );
    }
    if (word_trans.size() == 1) {
        criticalErrorOccured( tr("Cannot extract word and translation(-s) from the file line") +
                              QString(" #%1:\n\"%2\"\n").arg(m_lineCount).arg(line) +
                              tr("Invalid separator: ") + sep_wt + "\n\n" +
                              tr("Please set another Word-Translations separator in the Settings and try to load the file again.") );
    }
    word->setWord(word_trans.at(0));
    strTranslations = word_trans.at(1);
}

void WordsReader::parseTranslations(const QString &strWord, const QString &strTranslations, WordWT *word)
{
    /* extracting translations */
    QString sep_tt = m_settings->value( InstSettingsNames.SSname(SettingsNames::SS_sep_tt), ',' ).toString();
    // TODO: think how to implement criteria of absence the separator sep_tt in the file line (-s)
//    if (!strTranslations.contains(sep_tt)) {
//        criticalErrorOccured( tr("Cannot extract translation(-s) for the word") + " \"" + strWord + "\" " +
//                              tr("from the file line") + QString(" #%1:\n\"%2\"\n\n").arg(m_lineCount).arg(strTranslations) +
//                              tr("Please correct the Translations separator in the file and (or) in the application Settings") +
//                              " " + tr("and load the file again.") );
//    }
    QStringList trans = strTranslations.split(sep_tt);
    if (trans.size() == 1 && trans.at(0).trimmed().size() == 0) {
        criticalErrorOccured( tr("No one translation(-s) was found for the word") + ":\n\"" + strWord + "\"\n" +
                              tr("in the file line") + QString(" #%1:\n\n").arg(m_lineCount) +
                              tr("Add translation(-s) in the file to current word and load the file again.") );
    }
    foreach (const QString &trWord, trans) {
        word->addTranslation(trWord.trimmed()); // save translations
    }
}

void WordsReader::criticalErrorOccured(const QString &msg)
{
    close();
    emit sigCriticalErrorOccured( tr("File loading error"), msg );
}
