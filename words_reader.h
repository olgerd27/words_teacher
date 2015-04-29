#ifndef WORDS_READER_H
#define WORDS_READER_H

#include <QFile>
class WordWT;

class WordsReader : public QFile
{
    Q_OBJECT
public:
    explicit WordsReader(const QString &filename, char sepWT, char sepT, QObject *parent = 0);
    ~WordsReader();
    WordWT * getWord();

private:
    WordWT * parseWordAndTranslations(const QByteArray &line) const;

    const char m_sep_wt, m_sep_t;
    int m_lineCount;
};

#endif // WORDS_READER_H
