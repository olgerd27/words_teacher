#include <algorithm>
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

WordWT * WordTeacher::getWord()
{
    if (m_vcblr.empty()) return 0;
    WordWT *word = 0;
    do {
        if (m_vcblr.empty()) return 0;
        word = m_vcblr.at( rand() % m_vcblr.size() );
    } while (wordIsStudied(word));
    return word;
}

bool WordTeacher::wordIsStudied(WordWT *word)
{
    bool b = word->repeatsCount() >= maxRepeatsQuantity;
//    if (b) qDebug() << word->word(WordWT::getw_without_repeat).c_str() << " was studied";
    if (b) m_vcblr.erase( std::find(m_vcblr.begin(), m_vcblr.end(), word) ); // erase studied word from vocabulary
    return b;
}
