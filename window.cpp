#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include  <stdexcept>

#include "window.h"
#include "ui_window.h"
#include "word_teacher.h"
#include "results_controller.h"
#include "wordwt.h"
#include "words_reader.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
    , m_teacher(new WordTeacher())
    , m_currentWord(0)
    , m_resCtrl(new ResultsController())
    , m_applyPressed(true)
{
    ui->setupUi(this);

    /* Load data */
    connect(ui->m_pbLoad, SIGNAL(clicked()), this, SLOT(slotLoadData()));
    connect(this, SIGNAL(sigFileNameIsSpecified(QString)), ui->m_leFileName, SLOT(setText(QString)));
    connect(this, SIGNAL(sigFileIsLoaded(bool)), ui->m_gbExamination, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(sigFileIsLoaded(bool)), ui->m_gbResults, SLOT(setEnabled(bool)));

    /* Examination */
    connect(this, SIGNAL(sigNeedDisplayWord(QString)), ui->m_lRightWrong, SLOT(clear()));
    connect(this, SIGNAL(sigNeedDisplayWord(QString)), ui->m_lAnswerRight, SLOT(clear()));
    connect(this, SIGNAL(sigNeedDisplayWord(QString)), ui->m_lWordForTranslation, SLOT(setText(QString)));
    connect(this, SIGNAL(sigNeedDisplayWord(QString)), ui->m_leYourTranslation, SLOT(setFocus()));
    connect(this, SIGNAL(sigNeedDisplayWord(QString)), ui->m_leYourTranslation, SLOT(clear()));
    connect(ui->m_leYourTranslation, SIGNAL(returnPressed()), this, SLOT(slotApplyWord()));
    connect(ui->m_pbAnswerNext, SIGNAL(clicked()), this, SLOT(slotApplyWord()));
    connect(ui->m_pbRestart, SIGNAL(clicked()), this, SLOT(slotRestartExamination()));

    /* Switching caption on the push button */
    connect(this, SIGNAL(sigSetPBAnswerCaption(QString)), ui->m_pbAnswerNext, SLOT(slotSetCaption(QString)));

    /* Start Examination */
    connect(this, SIGNAL(sigStartExamination()), m_teacher, SLOT(slotRestartTeaching()));
    connect(this, SIGNAL(sigStartExamination()), m_teacher, SLOT(slotDefineWordsQntty()));
    connect(this, SIGNAL(sigStartExamination()), m_resCtrl, SLOT(slotUpdateResults()));

    /* Display answer */
    connect(this, SIGNAL(sigNeedDisplayAnswer(const WordWT*,QString)),
            m_teacher, SLOT(slotGetTranslations(const WordWT*,QString)));
    connect(m_teacher, SIGNAL(sigDisplayAnswer(QString)), ui->m_lAnswerRight, SLOT(setText(QString)));
    connect(this, SIGNAL(sigWordChecked(bool)), ui->m_lRightWrong, SLOT(slotShowRightWrong(bool)));
    connect(this, SIGNAL(sigWordChecked(bool)), ui->m_pbAnswerNext, SLOT(setFocus()));

    connect(this, SIGNAL(sigEndExamination(bool)), ui->m_pbAnswerNext, SLOT(setDisabled(bool)));
    connect(this, SIGNAL(sigEndExamination(bool)), ui->m_leYourTranslation, SLOT(setDisabled(bool)));
    connect(this, SIGNAL(sigEndExamination(bool)), ui->m_pbRestart, SLOT(setFocus()));
    connect(this, SIGNAL(sigEndExamination(bool)), ui->m_lWordForTranslation, SLOT(clear()));

    /* Results */
    connect(m_teacher, SIGNAL(sigWordsQnttyDefined(int)), m_resCtrl, SLOT(slotSetWordsQuantity(int)));

    connect(this, SIGNAL(sigWordChecked(bool)), m_resCtrl, SLOT(slotCalcResults(bool)));
    connect(this, SIGNAL(sigWordChecked(bool)), m_resCtrl, SLOT(slotUpdateResults()));

    connect(m_resCtrl, SIGNAL(sigUpdateWordsRemain(int)), ui->m_lRemainingW_data, SLOT(setNum(int)));
    connect(m_resCtrl, SIGNAL(sigUpdateWordsTransl(int)), ui->m_lTranslatedW_data, SLOT(setNum(int)));
    connect(m_resCtrl, SIGNAL(sigUpdateMark(int)), ui->m_lmark_data, SLOT(setNum(int)));
    connect(m_resCtrl, SIGNAL(sigUpdateConclusion(QString)), ui->m_lConclusion, SLOT(setText(QString)));

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
    // FIXME: need to delete here a previous loaded data
    try {
//        addTestWords();
        if (!loadWords()) return;
    }
    catch (std::runtime_error &ex) {
        QMessageBox::critical(this, tr("Error load words"), ex.what());
        return;
    }
    catch (...) {
        QMessageBox::critical(this, tr("Error load words"), tr("Undefined error occured"));
        return;
    }

    emit sigFileIsLoaded(true);
    emit sigStartExamination();
    askNextWord();
}

bool Window::loadWords()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Load words from a file"), "",
                                                    tr("Words (*.txt *.trsl)"));
    if (filename.isEmpty()) return false;
    emit sigFileNameIsSpecified(filename);

    WordsReader reader(filename, '-', ',');
    connect(&reader, SIGNAL(sigWarningOccured(QString, QString)), this, SLOT(slotShowWarning(QString, QString)));
    WordWT *word = 0;
    while ( (word = reader.getWord()) != 0 )
        m_teacher->addWord(word);
    return true;
}

void Window::addTestWords()
{
    WordWT *word = 0;

    word = new WordWT("One");
    word->addTranslation("1");
    m_teacher->addWord(word);

    word = new WordWT("Two");
    word->addTranslation("2");
    m_teacher->addWord(word);

    word = new WordWT("Three");
    word->addTranslation("3");
    m_teacher->addWord(word);

//    while (word = m_teacher->getWord()) {
//        qDebug() << *word;
//    }
}

void Window::slotApplyWord()
{
    if (!m_currentWord) return;
    if (m_applyPressed) {
        QString userTranslation = ui->m_leYourTranslation->text();
        emit sigWordChecked( m_teacher->isTranslation(m_currentWord, userTranslation.toStdString()) );
        emit sigNeedDisplayAnswer(m_currentWord, userTranslation); // cause the display translation answer in the window
        emit sigSetPBAnswerCaption(  tr("&Next word") );
    }
    else {
        emit sigSetPBAnswerCaption(  tr("&Answer") );
        askNextWord();
    }
    m_applyPressed = !m_applyPressed;
}

void Window::slotRestartExamination()
{
    emit sigEndExamination(false);
    emit sigStartExamination();
    askNextWord();
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
            emit sigEndExamination(false);
            emit sigStartExamination();
            m_currentWord = m_teacher->getWord();
        }
        if (btn & QMessageBox::No) return;
    }
    emit sigNeedDisplayWord( m_currentWord->word(WordWT::GetWithRepeat).c_str() );
}

void Window::slotShowWarning(const QString &title, const QString &msg)
{
    QMessageBox::warning(this, title, msg);
}

void Window::slotAbout()
{

    QString text = QString("The <b>") + windowTitle() + "</b> application.<br>"
                "The app helps to study any language words and its translations.<br><br>"
                "© M.O.I. Mykolaiv, Ukraine - 2015.";
    QMessageBox::about(this, tr("About"), tr(text.toUtf8()));
}
