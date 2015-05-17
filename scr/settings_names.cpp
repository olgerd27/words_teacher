#include <QObject>
//#include <QString>
#include <stdexcept>
#include "settings_names.h"

SettingsNames::SettingsNames()
{
    initSSnames();
    initMWSnames();
}

void SettingsNames::initSSnames()
{
    m_ssNames[SS_repetitions] = "settings/repetitions_quantity";
    m_ssNames[SS_codec] = "settings/files_codec";
    m_ssNames[SS_sep_wt] = "settings/separator_wt";
    m_ssNames[SS_sep_tt] = "settings/separator_tt";
}

void SettingsNames::initMWSnames()
{
    m_mwsNames[MWS_winSize] = "mainwindow/size";
    m_mwsNames[MWS_winPos] = "mainwindow/position";
}

const char * SettingsNames::SSname(SettingsNames::settingsSection index)
{
    if (index < 0 || index >= SS_SIZE)
        throw std::out_of_range(
                (QObject::tr("[SettingsNames] Cannot pass a settings name in Settings section -> bad index ") +
                 QString::number((int)index)).toStdString() );
    return m_ssNames[index];
}

const char * SettingsNames::MWSname(SettingsNames::mainwindowSection index)
{
    if (index < 0 || index >= MWS_SIZE)
        throw std::out_of_range(
                (QObject::tr("[SettingsNames] Cannot pass a settings name in MainWindow section -> bad index ") +
                 QString::number((int)index)).toStdString() );
    return m_mwsNames[index];
}
