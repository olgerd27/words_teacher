#include <algorithm>
#include "wordwt.h"

WordWT::WordWT(const std::string &word)
    : m_word(word)
{
}

void WordWT::addTranslation(const std::string &tr)
{
    m_translations.push_back(tr);
}

bool WordWT::isTranslation(const std::string &tr)
{
    return std::find(m_translations.begin(), m_translations.end(), tr) != 0;
}
