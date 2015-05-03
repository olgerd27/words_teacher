#ifndef REIMPLEMENTED_WIDGETS_H
#define REIMPLEMENTED_WIDGETS_H

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

/*
 * Label that shows its texts in the corresponding color
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
   void slotShowRightTranslation(bool b)
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
 * Push button with a changed text caption
 */
class PB_ChangedCaption : public QPushButton
{
    Q_OBJECT
public:
    PB_ChangedCaption(QWidget *parent)
        : QPushButton(parent)
    {
    }

public slots:
    void slotShowMaybeRestart(bool b)
    {
        b ? setText(tr("&Maybe restart?")) : setText(tr("&Don't know"));
    }
};

/*
 * Line edit with a different font for the Windows and Linux OS
 */
class LE_FontOS : public QLineEdit
{
    Q_OBJECT
public:
    LE_FontOS(QWidget *parent)
        : QLineEdit(parent)
    {
#if defined Q_OS_WIN // if there are Windows OS
        setFont(QFont("Courier New", 11, QFont::Normal));
#elif defined Q_OS_LINUX // if there are Linux OS
        setFont(QFont("Ubuntu Mono", 11, QFont::Normal));
#endif
    }
};

#endif // REIMPLEMENTED_WIDGETS_H
