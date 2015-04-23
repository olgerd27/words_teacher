#include <algorithm>

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
}

WordTeacher::~WordTeacher()
{
    std::for_each(m_vcblr.begin(), m_vcblr.end(), DeletePtrData());
}
