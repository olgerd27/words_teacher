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
    enum settingsNamesIndexes {
        SNI_repetitions = 0,
        SNI_codec,
        SNI_sep_wt,
        SNI_sep_tt,
        SNI_SIZE
    };

    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    const char * settingsName(SettingsDialog::settingsNamesIndexes index);

private slots:
    void slotSaveSettings();

private:
    void defineSettingsNames();
    void defineTextCodecs();
    void readSettings();

    Ui::SettingsDialog *ui;
    QSettings *m_userSettings;
    const char *m_settigsNames[SNI_SIZE];
};

#endif // SETTINGS_DIALOG_H
