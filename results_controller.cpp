#include "results_controller.h"

ResultsController::ResultsController(QObject *parent)
    : QObject(parent)
    , m_wordsRemaining(0)
    , m_wordsTeached(0)
    , m_wordsTranslated(0)
    , m_mark(0)
    , m_currConcl(conc_NONE)
{
    m_conclusionsMess[conc_Excellent] = tr("Excellent!");
    m_conclusionsMess[conc_VeryGood] = tr("Very Good");
    m_conclusionsMess[conc_Good] = tr("Good");
    m_conclusionsMess[conc_Normal] = tr("Normal");
    m_conclusionsMess[conc_Bad] = tr("Bad");
    m_conclusionsMess[conc_VeryBad] = tr("Very Bad");
    m_conclusionsMess[conc_Stupid] = tr("You're Stupid");
    m_conclusionsMess[conc_VeryStupid] = tr("Baby, you're really Stupid!");
    m_conclusionsMess[conc_NONE] = "";
}

void ResultsController::slotSetWordsQuantity(int quantity)
{
    m_wordsRemaining = quantity;
    m_wordsTeached = m_wordsTranslated = m_mark = 0;
    m_currConcl = conc_NONE;
}

void ResultsController::slotCalcResults(bool rightAnswer)
{
    // calculate results
    --m_wordsRemaining;
    ++m_wordsTeached;
    if (rightAnswer) ++m_wordsTranslated;
    m_mark = m_wordsTranslated * 1. / m_wordsTeached * 100;
    defineConclusion();
}

void ResultsController::slotUpdateResults()
{
    // send to visualization
    emit sigUpdateWordsRemain( m_wordsRemaining );
    emit sigUpdateWordsTransl( m_wordsTranslated );
    emit sigUpdateMark( m_mark );
    emit sigUpdateConclusion( m_conclusionsMess[m_currConcl] );
    emit sigResultsUpdated();
}

void ResultsController::slotFlush()
{
    m_wordsRemaining = m_wordsTranslated = m_mark = 0;
    m_currConcl = conc_NONE;
}

void ResultsController::defineConclusion()
{
    if      (m_mark == 100) m_currConcl = conc_Excellent;
    else if (m_mark >= 90)  m_currConcl = conc_VeryGood;
    else if (m_mark >= 75)  m_currConcl = conc_Good;
    else if (m_mark >= 60)  m_currConcl = conc_Normal;
    else if (m_mark >= 45)  m_currConcl = conc_Bad;
    else if (m_mark >= 30)  m_currConcl = conc_VeryBad;
    else if (m_mark >= 10)  m_currConcl = conc_Stupid;
    else if (m_mark < 10)   m_currConcl = conc_VeryStupid;
}
