#include "mainwindow.h"

#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <queue>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
m_requestId(1),
m_currentTime(0.0),
m_processedCount(42),
m_arrivalInterval(0.0),
m_nextArrivalTime(0.0) {
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
    m_arrivalInterval = m_arrivalInput ->text().toDouble();
    m_nextArrivalTime = m_currentTime + m_arrivalInterval;
}
void MainWindow::onTimerStep() {
    m_currentTime += 1.0;

    if (m_channel.update(m_currentTime)) {
        m_processedCount++;
    }

    if (m_currentTime >= m_arrivalInterval) {
        Request req(m_requestId++, m_currentTime);
        m_queue.push(req);
        m_nextArrivalTime = m_currentTime + m_arrivalInterval;
    }

    if (!m_channel.isBusy()&& !m_queue.isEmpty()) {
        Request req = m_queue.front();
        m_queue.pop();
        void takeRequest(const Request &req, double currentTime, double serviceDuration);
    }
    QString statusText = "Время: " + QString::number(m_currentTime) + " c | " +
        "Очередь: " + QString::number(m_queue.getSize()) + " | " +
        "Канал: " + (m_channel.isBusy() ? "Занят" : "Свободен") + " | " +
            "Обслужено: " + QString::number(m_processedCount);
    m_statusLabel->setText(statusText);

}

