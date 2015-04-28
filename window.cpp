#include <QMessageBox>
#include <QDebug>

#include "window.h"
#include "ui_window.h"
#include "word_teacher.h"
#include "results_controller.h"
#include "wordwt.h"

/*
 * Window
 */
Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
    , m_teacher(new WordTeacher())
    , m_currentWord(0)
    , m_resCtrl(new ResultsController())
    , m_examIsFinished(false)
{
    ui->setupUi(this);

    /* Load data */
    connect(ui->m_pbLoad, SIGNAL(clicked()), this, SLOT(slotLoadData()));
    connect(this, SIGNAL(sigFileIsLoaded(bool)), ui->m_gbExamination, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(sigFileIsLoaded(bool)), ui->m_gbResults, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(sigStartExamination()), m_teacher, SLOT(slotDefineWordsQntty()));
    connect(this, SIGNAL(sigStartExamination()), m_resCtrl, SLOT(slotUpdateResults()));

    /* Examination */
    connect(this, SIGNAL(sigNeedDisplayWord(QString)), ui->m_lWordForTranslation, SLOT(setText(QString)));
    connect(this, SIGNAL(sigNeedDisplayWord(QString)), ui->m_leTranslation, SLOT(setFocus()));
    connect(ui->m_pbApply, SIGNAL(clicked()), this, SLOT(slotApplyWord()));
    connect(ui->m_pbDontKnow, SIGNAL(clicked()), this, SLOT(slotDontKnowWord()));
    connect(this, SIGNAL(sigEndExamination(bool)), ui->m_pbApply, SLOT(setDisabled(bool)));
    connect(this, SIGNAL(sigEndExamination(bool)), ui->m_pbDontKnow, SLOT(slotShowMaybeRestart(bool)));
    connect(this, SIGNAL(sigEndExamination(bool)), ui->m_lWordForTranslation, SLOT(clear()));
    connect(this, SIGNAL(sigEndExamination(bool)), ui->m_lAccuracyTranslation, SLOT(clear()));

    /* Results */
    connect(m_teacher, SIGNAL(sigWordsQnttyDefined(int)), m_resCtrl, SLOT(slotSetWordsQuantity(int)));

    connect(this, SIGNAL(sigWordChecked(bool)), m_resCtrl, SLOT(slotCalcResults(bool)));
    connect(this, SIGNAL(sigWordChecked(bool)), m_resCtrl, SLOT(slotUpdateResults()));
    connect(this, SIGNAL(sigWordChecked(bool)), ui->m_lAccuracyTranslation, SLOT(slotShowRight(bool)));

    connect(m_resCtrl, SIGNAL(sigUpdateWordsRemain(int)), ui->m_lRemainingW_data, SLOT(setNum(int)));
    connect(m_resCtrl, SIGNAL(sigUpdateWordsTransl(int)), ui->m_lTranslatedW_data, SLOT(setNum(int)));
    connect(m_resCtrl, SIGNAL(sigUpdateMark(int)), ui->m_lmark_data, SLOT(setNum(int)));
    connect(m_resCtrl, SIGNAL(sigUpdateConclusion(QString)), ui->m_lConclusion, SLOT(setText(QString)));
    connect(m_resCtrl, SIGNAL(sigResultsUpdated()), ui->m_leTranslation, SLOT(clear()));

    /* Others */
    connect(ui->m_pbAbout, SIGNAL(clicked()), this, SLOT(slotAbout()));

    emit sigFileIsLoaded(false);
}

Window::~Window()
{
    delete ui;
    delete m_teacher;
    delete m_resCtrl;
}

void Window::slotLoadData()
{
    WordWT *word = 0;

    word = new WordWT("I was kind of hoping");
    word->addTranslation("A");
    m_teacher->addWord(word);

    word = new WordWT("bbb");
    word->addTranslation("B");
    m_teacher->addWord(word);

    word = new WordWT("ccc");
    word->addTranslation("C");
    m_teacher->addWord(word);

//    word = new WordWT("ddd");
//    word->addTranslation("DDD");
//    m_teacher->addWord(word);

//    while (word = m_teacher->getWord()) {
//        qDebug() << *word;
//    }

    emit sigFileIsLoaded(true);
    emit sigStartExamination();
    askNextWord();
}

void Window::slotApplyWord()
{
    QString userTranslation = ui->m_leTranslation->text();
    emit sigWordChecked( m_teacher->isTranslation(m_currentWord, userTranslation.toStdString()) );
    askNextWord();
}

void Window::slotDontKnowWord()
{
    if (!m_examIsFinished) emit sigWordChecked(false);
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
        emit sigEndExamination(true);
        QMessageBox::StandardButton btn = QMessageBox::information(this, tr("All words was studied"),
            tr("There was the last word. Do you want to start examination again?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (btn & QMessageBox::Yes) {
            m_teacher->repeatVocabulary();
            emit sigEndExamination(false);
            emit sigStartExamination();
            m_examIsFinished = false;
            m_currentWord = m_teacher->getWord();
        }
        if (btn & QMessageBox::No) {
            m_examIsFinished = true;
            return;
        }
    }
    emit sigNeedDisplayWord( m_currentWord->word(WordWT::GetWithRepeat).c_str() );
}
