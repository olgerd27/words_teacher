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
//    if (b) qDebug() << word->word(WordWT::GetWithoutRepeat).c_str() << " was studied";
    if (b) {
        m_vcblr_copy.push_back(word);
        m_vcblr.erase( std::find(m_vcblr.begin(), m_vcblr.end(), word) ); // erase studied word from vocabulary
    }
    return b;
}

bool WordTeacher::isTranslation(const WordWT *word, const std::string &translation) const
{
    return word->findTranslation(translation);
}

void flushWord(WordWT *w) { w->flush(); }

void WordTeacher::repeatVocabulary()
{
    /* Restart studying the words of current vocabulary */
    m_vcblr.assign(m_vcblr_copy.begin(), m_vcblr_copy.end());
    std::for_each(m_vcblr.begin(), m_vcblr.end(), flushWord);
    m_vcblr_copy.clear();
}

void WordTeacher::slotDefineWordsQntty()
{
    emit sigWordsQnttyDefined( m_vcblr.size() * maxRepeatsQuantity );
}

