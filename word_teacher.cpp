#include <algorithm>
#include <iterator>
#include <ctime>

#include "word_teacher.h"
#include "wordwt.h"

struct DeletePtrData
{
    template<typename T>
    void operator()(T *ptr)
    {
        delete ptr;
    }
};

/*
 * WordTeacher
 */
WordTeacher::WordTeacher(QObject *parent)
    : QObject(parent)
{
    srand(time(0));
}

WordTeacher::~WordTeacher()
{
    slotClearWords();
}

void WordTeacher::addWord(WordWT *word)
{
    if (word) m_vcblr.push_back(word);
}

bool WordTeacher::hasTranslation(const WordWT *word, const QString &translation) const
{
    return word->isTranslation(translation);
}

void WordTeacher::slotClearWords()
{
    if (m_vcblr.empty() && m_vcblr_studied.empty()) return;

    /* clear vocabulary with not studied words */
    std::for_each(m_vcblr.begin(), m_vcblr.end(), DeletePtrData());
    m_vcblr.clear();
    T_vocabulary(m_vcblr).swap(m_vcblr);

    /* clear vocabulary with already studied words */
    std::for_each(m_vcblr_studied.begin(), m_vcblr_studied.end(), DeletePtrData());
    m_vcblr_studied.clear();
    T_vocabulary(m_vcblr_studied).swap(m_vcblr_studied);
}

void WordTeacher::slotGetWord()
{
    WordWT *word = 0;
    do {
        if (m_vcblr.empty()) {
            emit sigWordSended(0);
            return;
        }
        word = m_vcblr.at( rand() % m_vcblr.size() );
    } while (wordIsStudied(word));
    emit sigWordSended(word);
}

bool WordTeacher::wordIsStudied(WordWT *word)
{
    bool b = word->repeatsCount() >= maxRepeatsQuantity;
    if (b) {
        m_vcblr_studied.push_back(word); // copying the word, that can to use when user will want to restart words teaching
        m_vcblr.erase( std::find(m_vcblr.begin(), m_vcblr.end(), word) ); // erase studied word from vocabulary
    }
    return b;
}

void flushWord(WordWT *w) { w->flush(); }

void WordTeacher::slotRestartTeaching()
{
    /* Restart studying the words of the current vocabulary */
    if (!m_vcblr_studied.empty()) {
        std::copy(m_vcblr_studied.begin(), m_vcblr_studied.end(), std::back_inserter(m_vcblr));
        m_vcblr_studied.clear();
    }
    std::for_each(m_vcblr.begin(), m_vcblr.end(), flushWord);
}

void WordTeacher::slotDefineWordsQntty()
{
    emit sigWordsQnttyDefined( m_vcblr.size() * maxRepeatsQuantity );
}

void WordTeacher::slotGetTranslations(const WordWT *wwt, const QString &userTranslation)
{
    QString res;
    WordWT::LowerComparer comp(userTranslation);
    const WordWT::T_arrTransls &C_translations = wwt->m_translations;
    WordWT::T_arrTransls::const_iterator cit;
    for (cit = C_translations.begin(); cit != C_translations.end(); ++cit) {
        res += (comp(*cit)) ? QString("<b><u>%1</u></b>").arg(*cit) : *cit;
        res += (cit != C_translations.end() - 1) ? ";   " : "";
    }
    emit sigDisplayAnswer(res);
}
