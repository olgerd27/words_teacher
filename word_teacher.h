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
    WordWT * getWord();
    bool isTranslation(const WordWT *word, const std::string &translation) const;

signals:
    void sigWordsQnttyDefined(int);

public slots:
    void slotDefineWordsQntty();
    void slotRestartTeaching();

private:
    bool wordIsStudied(WordWT *word);

    typedef std::vector<WordWT*> T_vocabulary;

    enum { maxRepeatsQuantity = 1 };

    T_vocabulary m_vcblr;
    T_vocabulary m_vcblr_copy;
};

#endif // WORD_TEACHER_H
