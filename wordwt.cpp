#include <algorithm>
#include "wordwt.h"

WordWT::WordWT(const std::string &word)
    : m_word(word)
    , m_checksCount(0)
{
}

void WordWT::setWord(const std::string &word)
{
    m_word = word;
}

std::string WordWT::word(WordWT::getWordMode mode)
{
    if (mode == GetWithRepeat) ++m_checksCount;
    return m_word;
}

void WordWT::addTranslation(const std::string &tr)
{
    m_translations.push_back(tr);
}

//std::string WordWT::nextTranslation() const
//{
//    static int index = 0;
//    std::string res;
//    if (index >= m_translations.size())
//        index = 0;
//    else
//        res = m_translations.at(index);
//    ++index;
//    return res;
//}

bool WordWT::findTranslation(const std::string &tr) const
{
    return std::find(m_translations.begin(), m_translations.end(), tr) != m_translations.end();
}

int WordWT::repeatsCount() const
{
    return m_checksCount;
}

void WordWT::flush()
{
    m_checksCount = 0;
}

QDebug operator<<(QDebug qdbg, WordWT &w)
{
    for (WordWT::T_translations::const_iterator it = w.m_translations.begin(); it != w.m_translations.end(); ++it)
        qdbg << w.word().c_str() << ":" << (*it).c_str();
    return qdbg;
}