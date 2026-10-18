#include "mainwindow.h"

#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_requestId(1), m_currentTime(0.0) {
    m_startButton = new QPushButton("Старт симуляции", this);
    m_arrivalInput = new QLineEdit(this);
    m_arrivalInput->setPlaceholderText("Интервал прихода (сек)");

    m_statusLabel = new QLabel("Статус: ожидание запуска",this);
    m_timer = new QTimer(this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    mainLayout->addWidget(m_arrivalInput);
    mainLayout->addWidget(m_startButton);
    mainLayout->addWidget(m_statusLabel);
    setCentralWidget(centralWidget);

    connect(m_startButton, &QPushButton::clicked,this,&MainWindow::onStartClicked);
    connect(m_timer, &QTimer::timeout,this,&MainWindow::onTimerStep);
}

MainWindow::~MainWindow(){}

void MainWindow::onStartClicked() {
    double arrivalInterval = m_arrivalInput ->text().toDouble();
    m_currentTime = 0;
    m_requestId = 1;
    m_timer->start(500);
}
void MainWindow::onTimerStep() {
    m_currentTime += 1.0;
    m_channel.update(m_currentTime);
    m_statusLabel->setText(QString::number(m_currentTime));
}

