#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

namespace Ui {
class Window;
}
class WordTeacher;
class WordWT;

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void slotLoadData();
    void slotAbout();

signals:
    void sigFileIsLoaded(bool);
    void sigDisplayWord(QString);

private:
    void askNextWord();

    Ui::Window *ui;
    WordTeacher *m_teacher;
    WordWT *m_currentWord;
};

#endif // WINDOW_H
