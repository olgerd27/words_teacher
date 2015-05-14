#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void slotSaveSettings();

private:
    void setDefaultSettings();
    void readSettings();

    Ui::SettingsDialog *ui;
    QSettings *m_userSettings;
};

#endif // SETTINGS_DIALOG_H
