#include <QTextCodec>
#include <QDebug>
#include "settings_dialog.h"
#include "ui_settings_dialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
    , m_userSettings(new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                   qApp->organizationName(), qApp->applicationName()))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(this, SIGNAL(accepted()), this, SLOT(slotSaveSettings()));
    readSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
    delete m_userSettings;
}

void SettingsDialog::readSettings()
{
    ui->m_cbFilesEncoding->addItem( m_userSettings->value("settings/files_encoding",
                                    QString(QTextCodec::codecForLocale()->name())).toString() );
    ui->m_leSepWT->setText( m_userSettings->value("settings/sep_wt", "-").toString() );
    ui->m_leSepTT->setText( m_userSettings->value("settings/sep_tt", ",").toString() );
}

void SettingsDialog::setDefaultSettings()
{
//    m_settings->beginGroup("settings");
    m_userSettings->setValue("settings/files_encoding", QString(QTextCodec::codecForLocale()->name()));
    m_userSettings->setValue("settings/sep_wt", '-');
    m_userSettings->setValue("settings/sep_tt", ',');
//    m_settings->endGroup();
}

void SettingsDialog::slotSaveSettings()
{
//    m_settings->beginGroup("settings");
    m_userSettings->setValue("settings/files_encoding", ui->m_cbFilesEncoding->currentText());
    m_userSettings->setValue("settings/sep_wt", ui->m_leSepWT->text());
    m_userSettings->setValue("settings/sep_tt", ui->m_leSepTT->text());
//    m_settings->endGroup();
}
