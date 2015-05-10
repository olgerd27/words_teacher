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
    std::for_each(m_vcblr.begin(), m_vcblr.end(), DeletePtrData());
}

void WordTeacher::addWord(WordWT *word)
{
    if (word) m_vcblr.push_back(word);
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
        m_vcblr_copy.push_back(word); // copying the word, that can to use when user will want to restart words teaching
        m_vcblr.erase( std::find(m_vcblr.begin(), m_vcblr.end(), word) ); // erase studied word from vocabulary
    }
    return b;
}

bool WordTeacher::hasTranslation(const WordWT *word, const QString &translation) const
{
    return word->isTranslation(translation);
}

void flushWord(WordWT *w) { w->flush(); }

void WordTeacher::slotRestartTeaching()
{
    /* Restart studying the words of the current vocabulary */
    if (!m_vcblr_copy.empty()) {
        std::copy(m_vcblr_copy.begin(), m_vcblr_copy.end(), std::back_inserter(m_vcblr));
        m_vcblr_copy.clear();
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
