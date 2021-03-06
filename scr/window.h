#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class Window;
}
class WordTeacher;
class WordWT;
class ResultsController;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();

signals:
    void sigFileNameIsSpecified(const QString &);
    void sigFileIsLoaded(bool);
    void sigNewWordAvailable(WordWT *);
    void sigNeedGetWord();
    void sigNeedDisplayWord(const QString &);
    void sigNeedCheckWord(const WordWT *, const QString &);
    void sigWordChecked(bool);
    void sigNeedDisplayAnswer(const WordWT *, const QString &);
    void sigStartExamination();
    void sigEndExamination(bool);
    void sigSetPBAnswerCaption(const QString &);

public slots:
    void slotSetTranslationAccuracy(bool);
    void slotShowWarning(const QString &title, const QString &msg);
    void slotShowCriticalError(const QString &title, const QString &msg);

private slots:
    void slotLoadData();
    void slotGetCurrentWord(WordWT *);
    void slotAnswerWord();
    void slotRestartExamination();
    void slotShowSettings();
    void slotAbout();

private:
    void readSettings();
    bool loadWords();
    void loadTestWords();
    void askNextWord();
    void closeEvent(QCloseEvent *);

    Ui::Window *ui;
    QSettings *m_settings;
    WordTeacher *m_teacher;
    ResultsController *m_resCtrl;
    WordWT *m_currentWord;
    bool m_needCheckAnswer;
    bool m_rightTranslation;
};

#endif // WINDOW_H
