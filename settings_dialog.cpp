#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
