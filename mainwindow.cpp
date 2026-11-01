#include "mainwindow.h"

#include <QHBoxLayout>
#include <QString>
#include <QFormLayout>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
m_requestId(1),
m_currentTime(0.0),
m_processedCount(0),
m_takenCount(0),
m_channelCount(0),
m_nextArrivalTime(0.0),
m_minArrivalValue(0.0), m_maxArrivalValue(0.0),
m_minServiceValue(0.0),m_maxServiceValue(0.0),
m_gen(std::random_device{}()),
m_totalWaitTime(0.0)
{
    m_startButton = new QPushButton("Старт симуляции", this);
    m_minArrival = new QDoubleSpinBox(this);
    m_maxArrival = new QDoubleSpinBox(this);
    m_maxService = new QDoubleSpinBox(this);
    m_minService = new QDoubleSpinBox(this);
    m_channelBox = new QSpinBox(this);

    m_minArrival ->setRange(0.1,60.0);
    m_minArrival ->setValue(1.0);
    m_maxArrival ->setRange(0.1,60.0);
    m_maxArrival ->setValue(3.0);
    m_minService ->setRange(0.1,60.0);
    m_minService ->setValue(1.0);
    m_maxService ->setRange(0.1,60.0);
    m_maxService ->setValue(4.0);
    m_channelBox ->setRange(1,60);
    m_channelBox ->setValue(1);

    m_statusLabel = new QLabel("Статус: ожидание запуска",this);
    m_timer = new QTimer(this);
    m_logFile = new QFile("simulation_log.txt",this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QFormLayout *paramsLayout = new QFormLayout();
    paramsLayout ->addRow("Число каналов", m_channelBox);
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
    m_takenCount = 0;
    m_totalWaitTime = 0.0;
    m_queue.clear();
    m_channelCount = m_channelBox ->value();
    m_channels.assign(m_channelCount,ServiceChannel());

    m_minArrivalValue = m_minArrival->value();
    m_maxArrivalValue = m_maxArrival->value();
    m_minServiceValue = m_minService->value();
    m_maxServiceValue = m_maxService->value();

    m_currentTime = 0;
    m_requestId = 1;

    std::uniform_real_distribution<double> dist(m_minArrivalValue, m_maxArrivalValue);
    double interval = dist(m_gen);
    m_nextArrivalTime = m_currentTime + interval;

    if (m_logFile -> isOpen()) {
        m_logFile -> close();
    }
    m_logFile -> open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream out(m_logFile);
    out << "---Старт симуляции---\n";
    out << "Интервал прихода: " << m_minArrivalValue << " - " << m_maxArrivalValue << " c\n";
    out << "Интервал обслуживания: " << m_minServiceValue << " - " << m_maxServiceValue << " с\n";

    m_timer->start(1000);
}
void MainWindow::onTimerStep() {
    m_currentTime += 1.0;

    for (ServiceChannel &ch : m_channels) {
        if (ch.update(m_currentTime)) {
            m_processedCount++;
        }
    }


    if (m_currentTime >= m_nextArrivalTime) {
        Request req(m_requestId++, m_currentTime);
        m_queue.push(req);
        std::uniform_real_distribution<double> dist(m_minArrivalValue, m_maxArrivalValue);
        double interval = dist(m_gen);
        m_nextArrivalTime = m_currentTime + interval;
    }

    if (!m_queue.isEmpty()) {
        int freeChannel = -1;//пока никого нет

        for (int i = 0; i < static_cast<int>(m_channels.size()); i++) {
            if (!m_channels[i].isBusy()) {
                freeChannel = i;
                break;
            }
        }
        if (freeChannel != -1) {
            Request req = m_queue.front();
            m_queue.pop();

            double wait = m_currentTime - req.getArrivalTime();
            m_totalWaitTime += wait;
            m_takenCount++;

            std::uniform_real_distribution<double> dist(m_minServiceValue, m_maxServiceValue);
            double duration = dist(m_gen);
            m_channels[freeChannel].takeRequest(req, m_currentTime,duration);
        }
    }

    int busy = 0;
    for (ServiceChannel &ch : m_channels) {
        if (ch.isBusy()) {
            busy++;
        }
    }

    double avgWait = (m_takenCount > 0) ? (m_totalWaitTime / m_takenCount) : 0.0;
    QString statusText = "Время: " + QString::number(m_currentTime) + " c | " +
        "Очередь: " + QString::number(m_queue.getSize()) + " | " +
        "Занято: " + QString::number(busy) + " из " + QString::number(m_channelCount) + " | " +
            "Обслужено: " + QString::number(m_processedCount) + " | Ср. ожидание: " +
                QString::number(avgWait, 'f',2) + " c";
    m_statusLabel->setText(statusText);
    if (m_logFile->isOpen()) {
        QTextStream out(m_logFile);
        out << statusText << "\n";
    }

}

