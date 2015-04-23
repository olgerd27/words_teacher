#include <algorithm>
#include "wordwt.h"

WordWT::WordWT(const std::string &word)
    : m_word(word)
    , m_repeatsCount(0)
{
}

void WordWT::addTranslation(const std::string &tr)
{
    m_translations.push_back(tr);
}

bool WordWT::isTranslation(const std::string &tr)
{
    bool b = std::find(m_translations.begin(), m_translations.end(), tr) != m_translations.end();
    if (b) m_repeatsCount++;
    return b;
}
