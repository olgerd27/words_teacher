#ifndef RESULTS_CONTROLLER_H
#define RESULTS_CONTROLLER_H

#include <QObject>

class ResultsController : public QObject
{
    Q_OBJECT
public:
    explicit ResultsController(QObject *parent = 0);

signals:
    void sigUpdateWordsRemain(int);
    void sigUpdateWordsTransl(int);
    void sigUpdateMark(int);
    void sigUpdateConclusion(QString);

public slots:
    void slotSetWordsQuantity(int);
    void slotCalcResults(bool);
    void slotUpdateResults();
    void slotFlush();

private:
    enum conclusions {
        conc_Excellent,
        conc_Good,
        conc_NotBad,
        conc_Bad,
        conc_VeryBad,
        conc_Stupid,
        conc_NONE,
        conc_SIZE
    };

    void defineConclusion();

    int m_wordsRemaining;
    int m_wordsTeached;
    int m_wordsTranslated;
    int m_mark;
    conclusions m_currConcl;
    const char *m_conclusionsMess[conc_SIZE];
};

#endif // RESULTS_CONTROLLER_H
