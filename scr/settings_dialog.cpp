#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>

#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include "settings_names.h"

SettingsDialog::SettingsDialog(QSettings *settings, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
    , m_settings(settings)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(this, SIGNAL(accepted()), this, SLOT(slotSaveSettings()));

    defineTextCodecs();
    readSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
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
    ui->m_sbRepetitions->setValue( m_settings->value( InstSettingsNames.SSname(SettingsNames::SS_repetitions), 1 ).toInt() );
    ui->m_leSepWT->setText( m_settings->value( InstSettingsNames.SSname(SettingsNames::SS_sep_wt), "-" ).toString() );
    ui->m_leSepTT->setText( m_settings->value( InstSettingsNames.SSname(SettingsNames::SS_sep_tt), ",").toString() );

    // set a text codec
    QString currentCodec = m_settings->value( InstSettingsNames.SSname(SettingsNames::SS_codec),
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
    m_settings->setValue( InstSettingsNames.SSname(SettingsNames::SS_repetitions), ui->m_sbRepetitions->value() );
    m_settings->setValue( InstSettingsNames.SSname(SettingsNames::SS_codec), ui->m_cbFilesCodec->currentText() );
    m_settings->setValue( InstSettingsNames.SSname(SettingsNames::SS_sep_wt), ui->m_leSepWT->text() );
    m_settings->setValue( InstSettingsNames.SSname(SettingsNames::SS_sep_tt), ui->m_leSepTT->text() );
}
