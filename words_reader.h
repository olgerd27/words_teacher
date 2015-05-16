#ifndef WORDS_READER_H
#define WORDS_READER_H

#include <QFile>
class WordWT;

class WordsReader : public QFile
{
    Q_OBJECT
public:
    explicit WordsReader(const QString &filename, char sepWT, char sepTT, QObject *parent = 0);
    ~WordsReader();
    WordWT * getWord();

signals:
    void sigWarningOccured(const QString &title, const QString &msg) const;

private:
    WordWT * parseWordAndTranslations(const QString &line) const;

    const char m_sep_wt, m_sep_tt;
    int m_lineCount;
};

#endif // WORDS_READER_H
