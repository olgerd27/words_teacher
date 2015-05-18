#ifndef WORD_TEACHER_H
#define WORD_TEACHER_H

#include <QObject>
#include <vector>

class WordWT;
class QSettings;

class WordTeacher : public QObject
{
    Q_OBJECT
public:
    explicit WordTeacher(const QSettings *settings, QObject *parent = 0);
    ~WordTeacher();

signals:
    void sigWordSended(WordWT *);
    void sigWordsQnttyDefined(int);
    void sigTranslationWasChecked(bool) const;
    void sigDisplayAnswer(const QString &);

public slots:
    void slotAddWord(WordWT *);
    void slotClearWords();
    void slotRestartTeaching();
    void slotHasTranslation(const WordWT *word, const QString &translation) const;
    void slotGetWord();
    void slotGetTranslations(const WordWT *, const QString &);

private:
    bool wordIsStudied(WordWT *word);

    typedef std::vector<WordWT*> T_vocabulary;

    enum { defaultRepetitionsQuantity = 1 };

    const QSettings *m_settings;
    int m_repetitions;
    T_vocabulary m_vcblr;
    T_vocabulary m_vcblr_studied;
};

#endif // WORD_TEACHER_H
