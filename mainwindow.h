#ifndef SMO_MAINWINDOW_H
#define SMO_MAINWINDOW_H

#include <random>
#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>

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
    QPushButton *m_startButton;
    QDoubleSpinBox *m_minArrival;
    QDoubleSpinBox *m_maxArrival;
    QDoubleSpinBox *m_minService;
    QDoubleSpinBox *m_maxService;
    QLabel *m_statusLabel;

    QTimer *m_timer;
    Queue m_queue;
    ServiceChannel m_channel;

    int m_requestId;
    int m_processedCount;
    double m_currentTime,
    m_arrivalInterval,
    m_nextArrivalTime,
    m_minArrivalValue,
    m_maxArrivalValue,
    m_minServiceValue,
    m_maxServiceValue;
};
#endif //SMO_MAINWINDOW_H