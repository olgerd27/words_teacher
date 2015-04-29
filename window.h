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
 * - symbol separated word and translation words;
 * - symbol separated translation words.
 */
class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void slotLoadData();
    void slotApplyWord();
    void slotDontKnowWord();
    void slotAbout();

signals:
    void sigFileNameIsSpecified(QString);
    void sigFileIsLoaded(bool);
    void sigNeedDisplayWord(QString);
    void sigWordChecked(bool);
    void sigWordDontChecked();
    void sigStartExamination();
    void sigEndExamination(bool);

private:
    bool loadWords();
    void addTestWords();
    void askNextWord();

    Ui::Window *ui;
    WordTeacher *m_teacher;
    WordWT *m_currentWord;
    ResultsController *m_resCtrl;
    bool m_examIsFinished;
};

#endif // WINDOW_H
