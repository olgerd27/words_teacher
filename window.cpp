#include <QMessageBox>

#include "window.h"
#include "ui_window.h"
#include "word_teacher.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
    , m_teacher(new WordTeacher())
{
    ui->setupUi(this);

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
