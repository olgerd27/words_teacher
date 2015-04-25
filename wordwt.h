#ifndef WORDWT_H
#define WORDWT_H

#include <vector>
#include <string>
#include <iostream>
#include <QDebug>

/*
 * Word with translations
 */
class WordWT
{
public:
    enum getWordMode {
        getw_with_repeat,   /* word getting with increment repeating */
        getw_without_repeat /* word getting without increment repeating */
    };

    WordWT(const std::string &word);

    inline void setWord(const std::string &word) { m_word = word; }
    std::string word(WordWT::getWordMode mode = WordWT::getw_with_repeat);

    void addTranslation(const std::string &tr);
//    std::string nextTranslation() const;
    bool isTranslation(const std::string &tr);

    inline int repeatsCount() const { return m_checksCount; }

    friend QDebug & operator<<(QDebug &qdbg, WordWT &w);
    friend std::ostream & operator<<(std::ostream &os, WordWT &w);

private:
    typedef std::vector<std::string> T_translations;

    std::string m_word;
    T_translations m_translations;
    int m_checksCount;
};

#endif // WORDWT_H
