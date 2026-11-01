#ifndef SMO_MAINWINDOW_H
#define SMO_MAINWINDOW_H

#include <random>
#include <vector>
#include <QSpinBox>
#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QFile>

#include "Queue.h"
#include "ServiceChannel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
    void onStartClicked();
    void onTimerStep();

    private:
    std:: mt19937 m_gen;
    QFile *m_logFile;
    QPushButton *m_startButton;
    QDoubleSpinBox *m_minArrival;
    QDoubleSpinBox *m_maxArrival;
    QDoubleSpinBox *m_minService;
    QDoubleSpinBox *m_maxService;
    QLabel *m_statusLabel;
    QSpinBox *m_channelBox;

    QTimer *m_timer;
    Queue m_queue;
    std::vector<ServiceChannel> m_channels;

    int m_requestId;
    int m_processedCount,
    m_takenCount;
    int m_channelCount;
    double m_currentTime,
    m_nextArrivalTime,
    m_minArrivalValue,
    m_maxArrivalValue,
    m_minServiceValue,
    m_maxServiceValue,
    m_totalWaitTime;
};
#endif //SMO_MAINWINDOW_H