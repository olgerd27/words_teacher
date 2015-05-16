#ifndef SETTINGS_NAMES_H
#define SETTINGS_NAMES_H

class SettingsNames
{
public:
    enum settingsSection {
        SS_repetitions = 0,
        SS_codec,
        SS_sep_wt,
        SS_sep_tt,
        SS_SIZE
    };

    enum mainwindowSection {
        MWS_winSize = 0,
        MWS_winPos,
        MWS_SIZE
    };

    static SettingsNames & getInstance()
    {
        static SettingsNames singleInstance;
        return singleInstance;
    }

    const char * SSname(SettingsNames::settingsSection index);
    const char * MWSname(SettingsNames::mainwindowSection index);

private:
    SettingsNames();
    void initSSnames();
    void initMWSnames();

    /* Hided */
    SettingsNames(const SettingsNames &);
    SettingsNames & operator=(const SettingsNames &);

    const char *m_ssNames[SS_SIZE];
    const char *m_mwsNames[MWS_SIZE];
};

#define InstSettingsNames SettingsNames::getInstance()

#endif // SETTINGS_NAMES_H
