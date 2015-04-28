#ifndef REIMPLEMENTED_WIDGETS_H
#define REIMPLEMENTED_WIDGETS_H

#include <QLabel>
#include <QPushButton>

/*
 * Lbl_AccuracyTranslation
 */
class Lbl_AccuracyTranslation : public QLabel
{
    Q_OBJECT
public:
    Lbl_AccuracyTranslation(QWidget *parent)
        : QLabel(parent)
    {
        m_timerID = startTimer(10); // timer initialization
    }

protected:
    virtual void timerEvent(QTimerEvent *)
    {
        setText("");
    }

public slots:
   void slotShowRight(bool b)
   {
       QString text = b ? tr("Right") : tr("Wrong");
       QString color = b ? "green" : "red";
       setText(QString("<FONT COLOR=%1><CENTER> %2</CENTER></FONT>").arg(color).arg(text));
       killTimer(m_timerID);
       m_timerID = startTimer(2000);
   }

private:
   int m_timerID;
};

/*
 * PB_Dontknow_Next
 */
class PB_Dontknow_Next : public QPushButton
{
    Q_OBJECT
public:
    PB_Dontknow_Next(QWidget *parent)
        : QPushButton(parent)
    {
    }

public slots:
    void slotShowMaybeRestart(bool b)
    {
        b ? setText(tr("&Maybe restart?")) : setText(tr("&Don't know"));
    }
};

#endif // REIMPLEMENTED_WIDGETS_H
