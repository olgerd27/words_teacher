#ifndef WORDWT_H
#define WORDWT_H

#include <vector>
#include <QDebug>

class WordTeacher;

/*
 * Word with translations
 */
class WordWT
{
public:
    typedef QString T_word;
    typedef std::vector<T_word> T_arrTransls;

    enum getWordMode {
        GetWithRepeat,   /* word getting with increment repeating */
        GetWithoutRepeat /* word getting without increment repeating */
    };

    WordWT();
    WordWT(const WordWT::T_word &word);

    void setWord(const WordWT::T_word &word);
    WordWT::T_word word(WordWT::getWordMode mode = WordWT::GetWithRepeat);

    void addTranslation(const WordWT::T_word &tr);
    bool isTranslation(const WordWT::T_word &tr) const;

    int repetitionsCount() const;
    void flush();

    friend class WordTeacher;
    friend QDebug operator<<(QDebug qdbg, WordWT &w);

private:
    /* LowerComparer */
    class LowerComparer
    {
    public:
        LowerComparer(const WordWT::T_word &tr);
        bool operator()(const WordWT::T_word &tr) const;

    private:
        WordWT::T_word m_tr;
    };

    WordWT::T_word m_word;
    T_arrTransls m_translations;
    int m_checksCount;
};

#endif // WORDWT_H
