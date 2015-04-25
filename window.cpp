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

    word = new WordWT("ddd");
    word->addTranslation("DDD");
    m_teacher->addWord(word);

    try {
        while (word = m_teacher->getWord()) {
//            qDebug() << *word; // FIXME: compile error, fix it
            std::cout << *word;
        }
    }
    catch(const std::exception &ex) {
        qDebug() << "--!Error: " << ex.what();
    }

    /* Sig & Slots */
    connect(ui->m_pbLoad, SIGNAL(clicked()), this, SLOT(slotLoadData()));
    connect(this, SIGNAL(sigFileIsLoaded(bool)), ui->m_gbExamination, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(sigFileIsLoaded(bool)), ui->m_gbResults, SLOT(setEnabled(bool)));
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
}

void Window::slotAbout()
{
    QMessageBox::about(this, tr("About"), tr("Mykolaiv, 2015"));
}

void Window::askNextWord()
{
//    emit sigDisplayWord(  );
}
