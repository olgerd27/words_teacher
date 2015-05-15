#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>

#include <stdexcept>

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

    defineSettingsNames();
    defineTextCodecs();
    readSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
    delete m_userSettings;
}

void SettingsDialog::defineSettingsNames()
{
    m_settigsNames[SNI_repetitions] = "settings/repetitions_quantity";
    m_settigsNames[SNI_codec] = "settings/files_codec";
    m_settigsNames[SNI_sep_wt] = "settings/separator_wt";
    m_settigsNames[SNI_sep_tt] = "settings/separator_tt";
}

void SettingsDialog::defineTextCodecs()
{
    QList<QByteArray> byteListCodecs = QTextCodec::availableCodecs();
    qSort(byteListCodecs);
    foreach (QByteArray byteCodec, byteListCodecs) {
        ui->m_cbFilesCodec->addItem(byteCodec);
    }
}

void SettingsDialog::readSettings()
{
    ui->m_sbRepetitions->setValue( m_userSettings->value( m_settigsNames[SNI_repetitions], 1 ).toInt() );
    ui->m_leSepWT->setText( m_userSettings->value( m_settigsNames[SNI_sep_wt], "-" ).toString() );
    ui->m_leSepTT->setText( m_userSettings->value( m_settigsNames[SNI_sep_tt], ",").toString() );

    // set a text codec
    QString currentCodec = m_userSettings->value( m_settigsNames[SNI_codec],
                               QString(QTextCodec::codecForLocale()->name()) ).toString();
    int index = ui->m_cbFilesCodec->findText(currentCodec);
    if (index == -1) { // if no one codec was found (it's possible only by incredible reasons)
        QString defaultCodec = QTextCodec::codecForLocale()->name();
        QMessageBox::warning( this, tr("Invalid text codec"),
                              tr("Unknown readed from the application settings text codec: ") +
                              currentCodec + tr("\nPlease choose another text codec.\n") +
                              tr("For this OS default text codec is: ") + defaultCodec );
        index = ui->m_cbFilesCodec->findText(defaultCodec);
    }
    ui->m_cbFilesCodec->setCurrentIndex(index);
}

void SettingsDialog::slotSaveSettings()
{
    m_userSettings->setValue( m_settigsNames[SNI_repetitions], ui->m_sbRepetitions->value() );
    m_userSettings->setValue( m_settigsNames[SNI_codec], ui->m_cbFilesCodec->currentText() );
    m_userSettings->setValue( m_settigsNames[SNI_sep_wt], ui->m_leSepWT->text() );
    m_userSettings->setValue( m_settigsNames[SNI_sep_tt], ui->m_leSepTT->text() );
}

const char *SettingsDialog::settingsName(SettingsDialog::settingsNamesIndexes index)
{
    if (index < 0 || index >= SNI_SIZE)
        throw std::out_of_range( (tr("[SettingsDialog] Cannot pass a settings name -> bad index ") +
                 QString::number((int)index)).toStdString() );
    return m_settigsNames[index];
}
