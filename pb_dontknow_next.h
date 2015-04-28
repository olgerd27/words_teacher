#ifndef PB_DONTKNOW_NEXT_H
#define PB_DONTKNOW_NEXT_H

#include <QPushButton>

class PB_Dontknow_Next : public QPushButton
{
    Q_OBJECT
public:
    PB_Dontknow_Next(QWidget *parent)
        : QPushButton(parent)
    {}

public slots:
    void slotSwitchText(bool b)
    {
        b ? setText(tr("&Maybe restart?")) : setText(tr("&Don't know"));
    }
};

#endif // PB_DONTKNOW_NEXT_H
