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
    explicit SettingsDialog(QSettings *settings, QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void slotSaveSettings();

private:
    void defineTextCodecs();
    void readSettings();

    Ui::SettingsDialog *ui;
    QSettings *m_settings;
};

#endif // SETTINGS_DIALOG_H
