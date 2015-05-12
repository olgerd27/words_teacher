#ifndef WORD_TEACHER_H
#define WORD_TEACHER_H

#include <QObject>
#include <vector>

class WordWT;

class WordTeacher : public QObject
{
    Q_OBJECT
public:
    explicit WordTeacher(QObject *parent = 0);
    ~WordTeacher();

    void addWord(WordWT *word);
    bool hasTranslation(const WordWT *word, const QString &translation) const;

signals:
    void sigWordSended(WordWT *);
    void sigWordsQnttyDefined(int);
    void sigDisplayAnswer(const QString &);

public slots:
    void slotClearWords();
    void slotGetWord();
    void slotRestartTeaching();
    void slotDefineWordsQntty();
    void slotGetTranslations(const WordWT *, const QString &);

private:
    bool wordIsStudied(WordWT *word);

    typedef std::vector<WordWT*> T_vocabulary;

    enum { maxRepeatsQuantity = 1 };

    T_vocabulary m_vcblr;
    T_vocabulary m_vcblr_studied;
};

#endif // WORD_TEACHER_H
