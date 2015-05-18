#include <algorithm>
#include "wordwt.h"

/*
 * WordWT
 */
WordWT::WordWT()
    : m_checksCount(0)
{
}

WordWT::WordWT(const WordWT::T_word &word)
    : m_word(word)
    , m_checksCount(0)
{
}

void WordWT::setWord(const WordWT::T_word &word)
{
    m_word = word;
}

WordWT::T_word WordWT::word(WordWT::getWordMode mode)
{
    if (mode == GetWithRepeat) ++m_checksCount;
    return m_word;
}

void WordWT::addTranslation(const WordWT::T_word &tr)
{
    m_translations.push_back(tr);
}

bool WordWT::isTranslation(const WordWT::T_word &tr) const
{
    return std::find_if(m_translations.begin(), m_translations.end(), LowerComparer(tr)) != m_translations.end();
}

int WordWT::repetitionsCount() const
{
    return m_checksCount;
}

void WordWT::flush()
{
    m_checksCount = 0;
}

QDebug operator<<(QDebug qdbg, WordWT &w)
{
    for (WordWT::T_arrTransls::const_iterator it = w.m_translations.begin(); it != w.m_translations.end(); ++it)
        qdbg << w.word(WordWT::GetWithoutRepeat) << ":" << *it;
    return qdbg;
}

/*
 * WordWT::LowerCompare
 */
WordWT::LowerComparer::LowerComparer(const WordWT::T_word &tr)
    : m_tr(tr)
{
}

template<typename T>
bool compareLower(T t1, T t2)
{
    return ::tolower(t1) == ::tolower(t2);
}

template<> bool compareLower<QChar>(QChar ch1, QChar ch2)
{
    return ch1.toLower() == ch2.toLower();
}

bool WordWT::LowerComparer::operator()(const WordWT::T_word &tr) const
{
    return (tr.size() == m_tr.size()) && ( std::equal(tr.begin(), tr.end(), m_tr.begin(), compareLower<WordWT::T_word::value_type>) );
}
