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
private:
    typedef QString T_word;
    typedef std::vector<T_word> T_arrTransls;

public:
    enum getWordMode {
        GetWithRepeat,   /* word getting with increment repeating */
        GetWithoutRepeat /* word getting without increment repeating */
    };

    WordWT();
    WordWT(const T_word &word);

    void setWord(const T_word &word);
    T_word word(WordWT::getWordMode mode = WordWT::GetWithRepeat);

    void addTranslation(const T_word &tr);
    bool isTranslation(const T_word &tr) const;

    int repeatsCount() const;
    void flush();

    friend class WordTeacher;
    friend QDebug operator<<(QDebug qdbg, WordWT &w);

private:
    /* LowerComparer */
    class LowerComparer
    {
    public:
        LowerComparer(const T_word &tr);
        bool operator()(const T_word &tr) const;

    private:
        T_word m_tr;
    };

    T_word m_word;
    T_arrTransls m_translations;
    int m_checksCount;
};

#endif // WORDWT_H
