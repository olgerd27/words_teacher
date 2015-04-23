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

private:
    typedef std::vector<WordWT*> T_vocabulary;

    T_vocabulary m_vcblr;
};

#endif // WORD_TEACHER_H
