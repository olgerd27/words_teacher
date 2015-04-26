#include "results_controller.h"

ResultsController::ResultsController(QObject *parent)
    : QObject(parent)
    , m_wordsRemaining(0)
    , m_wordsTeached(0)
    , m_wordsTranslated(0)
    , m_mark(0)
    , m_currConcl(conc_NONE)
{
    m_conclusionsMess[conc_Excellent] = "Excellent!";
    m_conclusionsMess[conc_Good] = "Good";
    m_conclusionsMess[conc_NotBad] = "Not Bad";
    m_conclusionsMess[conc_Bad] = "Bad";
    m_conclusionsMess[conc_VeryBad] = "Very Bad";
    m_conclusionsMess[conc_Stupid] = "You're stupid!";
    m_conclusionsMess[conc_NONE] = "";
}

void ResultsController::slotSetWordsQuantity(int quantity)
{
    m_wordsRemaining = quantity;
    m_wordsTeached = m_wordsTranslated = m_mark = 0;
    m_currConcl = conc_NONE;
}

void ResultsController::slotUpdateResults(bool rightAnswer)
{
    // calculate results
    --m_wordsRemaining;
    ++m_wordsTeached;
    if (rightAnswer) ++m_wordsTranslated;
    m_mark = m_wordsTranslated * 1. / m_wordsTeached * 100;
    defineConclusion();

    // send to visualization
    emit sigUpdateWordsRemain( m_wordsRemaining );
    emit sigUpdateWordsTransl( m_wordsTranslated );
    emit sigUpdateMark( m_mark );
    emit sigUpdateConclusion( m_conclusionsMess[m_currConcl] );
}

void ResultsController::slotFlush()
{
    m_wordsRemaining = m_wordsTranslated = m_mark = 0;
    m_currConcl = conc_NONE;
}

void ResultsController::defineConclusion()
{
    if (m_mark >= 95)
        m_currConcl = conc_Excellent;
    else if (m_mark >= 80)
        m_currConcl = conc_Good;
    else if (m_mark >= 65)
        m_currConcl = conc_NotBad;
    else if (m_mark >= 40)
        m_currConcl = conc_Bad;
    else if (m_mark >= 25)
        m_currConcl = conc_VeryBad;
    else if (m_mark >= 5)
        m_currConcl = conc_Stupid;
}
