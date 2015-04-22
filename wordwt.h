#ifndef WORDWT_H
#define WORDWT_H

#include <vector>
#include <string>

/*
 * Word with translations
 */
class WordWT
{
public:
    WordWT(const std::string &word);

    inline void setWord(const std::string &word) { m_word = word; }
    inline std::string word() const { return m_word; }

    void addTranslation(const std::string &tr);
    bool isTranslation(const std::string &tr);

private:
    typedef std::vector<std::string> T_translations;

    std::string m_word;
    T_translations m_translations;
};

#endif // WORDWT_H
