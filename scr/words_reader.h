#ifndef WORDS_READER_H
#define WORDS_READER_H

#include <QFile>

class WordWT;
class QTextStream;
class QSettings;

class WordsReader : public QFile
{
    Q_OBJECT
public:
    explicit WordsReader(const QString &filename, const QSettings *settings, QObject *parent = 0);
    ~WordsReader();
    WordWT * getWord();

signals:
    void sigWarningOccured(const QString &title, const QString &msg) const;
    void sigCriticalErrorOccured(const QString &title, const QString &msg) const;

private:
    WordWT * parseLine(const QString &strLine);
    void parseWord(const QString &line, QString &strTranslations, WordWT *word);
    void parseTranslations(const QString &strWord, const QString &strTranslations, WordWT *word);
    void criticalErrorOccured(const QString &msg);

    QTextStream *m_textStream;
    const QSettings *m_settings;
    int m_lineCount;
};

#endif // WORDS_READER_H
