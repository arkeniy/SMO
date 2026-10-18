#ifndef SMO_MAINWINDOW_H
#define SMO_MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>
#include <Qlabel>

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
    QPushButton *m_startButton;
    QLineEdit *m_arrivalInput;
    QLabel *m_statusLabel;

    QTimer *m_timer;
    Queue m_queue;
    ServiceChannel m_channel;

    int m_requestId;
    double m_currentTime;
};
#endif //SMO_MAINWINDOW_H