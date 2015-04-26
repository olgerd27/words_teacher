#include <QMessageBox>
#include <QDebug>

#include "window.h"
#include "ui_window.h"
#include "word_teacher.h"
#include "wordwt.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
    , m_teacher(new WordTeacher())
    , m_currentWord(0)
{
    ui->setupUi(this);

    WordWT *word = 0;

    word = new WordWT("aaa");
    word->addTranslation("AAA");
    m_teacher->addWord(word);

    word = new WordWT("bbb");
    word->addTranslation("BBB");
    m_teacher->addWord(word);

    word = new WordWT("ccc");
    word->addTranslation("CCC");
    m_teacher->addWord(word);

//    word = new WordWT("ddd");
//    word->addTranslation("DDD");
//    m_teacher->addWord(word);

//    while (word = m_teacher->getWord()) {
//        qDebug() << *word;
//    }

    /* Sig & Slots */
    connect(ui->m_pbLoad, SIGNAL(clicked()), this, SLOT(slotLoadData()));
    connect(this, SIGNAL(sigFileIsLoaded(bool)), ui->m_gbExamination, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(sigFileIsLoaded(bool)), ui->m_gbResults, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(sigDisplayWord(QString)), ui->m_lWordForTranslation, SLOT(setText(QString)));
    connect(ui->m_pbAbout, SIGNAL(clicked()), this, SLOT(slotAbout()));

    emit sigFileIsLoaded(false);
}

Window::~Window()
{
    delete ui;
    delete m_teacher;
}

void Window::slotLoadData()
{
    emit sigFileIsLoaded(true);
    askNextWord();
}

void Window::slotAbout()
{
    QMessageBox::about(this, tr("About"), tr("Mykolaiv, 2015"));
}

void Window::askNextWord()
{
    m_currentWord = m_teacher->getWord();
    if (!m_currentWord) {
        QMessageBox::StandardButton btn = QMessageBox::information(this, tr("All words was studied"),
            tr("There was the last word. Do you want to start examination again?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (btn & QMessageBox::Yes) {
            m_teacher->repeatVocabulary();
            m_currentWord = m_teacher->getWord();
        }
        return;
    }
    emit sigDisplayWord( m_currentWord->word(WordWT::GetWithRepeat).c_str() );
}
