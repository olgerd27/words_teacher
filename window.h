#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

namespace Ui {
class Window;
}
class WordTeacher;
class WordWT;
class ResultsController;

/*
 * TODO: there are need to implement the Settings widget, that calls by clicking to the Settings push button.
 * Settings widget can to have:
 * - repeate word quantity;
 * - input files encoding: Linux - "UTF-8", Windows - "windows-1251", ...
 *   (this allow user to work with a text files, that saved in the another OS and encoding then current);
 * - symbol, separated word and translation words;
 * - symbol, separated translation words.
 */

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

public slots:
    void slotShowWarning(const QString &title, const QString &msg);

private slots:
    void slotLoadData();
    void slotGetCurrentWord(WordWT *);
    void slotAnswerWord();
    void slotRestartExamination();
    void slotAbout();

signals:
    void sigFileNameIsSpecified(const QString &);
    void sigFileIsLoaded(bool);
    void sigNeedGetWord();
    void sigNeedDisplayWord(const QString &);
    void sigWordChecked(bool);
    void sigNeedDisplayAnswer(const WordWT *, const QString &);
    void sigStartExamination();
    void sigEndExamination(bool);
    void sigSetPBAnswerCaption(const QString &);

private:
    bool loadWords();
    void addTestWords();
    void askNextWord();

    Ui::Window *ui;
    WordTeacher *m_teacher;
    WordWT *m_currentWord;
    ResultsController *m_resCtrl;
    bool m_applyPressed;
};

#endif // WINDOW_H
