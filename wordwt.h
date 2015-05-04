#ifndef WORDWT_H
#define WORDWT_H

#include <vector>
#include <string>
#include <QDebug>

class WordTeacher;

/*
 * Word with translations
 */
class WordWT
{
public:
    enum getWordMode {
        GetWithRepeat,   /* word getting with increment repeating */
        GetWithoutRepeat /* word getting without increment repeating */
    };

    WordWT(const std::string &word);

    void setWord(const std::string &word);
    std::string word(WordWT::getWordMode mode = WordWT::GetWithRepeat);

    void addTranslation(const std::string &tr);
    bool isTranslation(const std::string &tr) const;

    int repeatsCount() const;
    void flush();

    friend class WordTeacher;
    friend QDebug operator<<(QDebug qdbg, WordWT &w);

private:
    typedef std::vector<std::string> T_translations;

    std::string m_word;
    T_translations m_translations;
    int m_checksCount;
};

#endif // WORDWT_H
