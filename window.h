#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

namespace Ui {
class Window;
}

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

private:
    Ui::Window *ui;

};

#endif // WINDOW_H
