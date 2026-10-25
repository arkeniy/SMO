#include "mainwindow.h"

#include <QHBoxLayout>
#include <QString>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
m_requestId(1),
m_currentTime(0.0),
m_processedCount(0),
m_arrivalInterval(0.0),
m_nextArrivalTime(0.0),
m_minArrivalValue(0.0), m_maxArrivalValue(0.0),
m_minServiceValue(0.0),m_maxServiceValue(0.0){
    m_startButton = new QPushButton("Старт симуляции", this);
    m_minArrival = new QDoubleSpinBox(this);
    m_maxArrival = new QDoubleSpinBox(this);
    m_maxService = new QDoubleSpinBox(this);
    m_minService = new QDoubleSpinBox(this);

    m_minArrival ->setRange(0.1,60.0);
    m_minArrival ->setValue(1.0);
    m_maxArrival ->setRange(0.1,60.0);
    m_maxArrival ->setValue(1.0);
    m_minService ->setRange(0.1,60.0);
    m_minService ->setValue(1.0);
    m_maxService ->setRange(0.1,60.0);
    m_maxService ->setValue(1.0);


    m_statusLabel = new QLabel("Статус: ожидание запуска",this);
    m_timer = new QTimer(this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QFormLayout *paramsLayout = new QFormLayout();
    paramsLayout ->addRow("Мин. интервал прихода", m_minArrival);
    paramsLayout ->addRow("Макс. интервал прихода", m_maxArrival);
    paramsLayout ->addRow("Мин. интервал обслуживания", m_minService);
    paramsLayout ->addRow("Макс. интервал обслуживания", m_maxService);

    mainLayout->addLayout(paramsLayout);
    mainLayout->addWidget(m_startButton);
    mainLayout->addWidget(m_statusLabel);
    setCentralWidget(centralWidget);

    connect(m_startButton, &QPushButton::clicked,this,&MainWindow::onStartClicked);
    connect(m_timer, &QTimer::timeout,this,&MainWindow::onTimerStep);
}

MainWindow::~MainWindow(){}

void MainWindow::onStartClicked() {
    m_processedCount = 0;
    m_queue.clear();
    m_channel = ServiceChannel();

    m_minArrivalValue = m_minArrival->value();
    m_maxArrivalValue = m_maxArrival->value();
    m_minServiceValue = m_minService->value();
    m_maxServiceValue = m_maxService->value();

    m_currentTime = 0;
    m_requestId = 1;
    m_timer->start(500);
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

