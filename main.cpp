#include <iostream>
#include <fstream>
#include <windows.h>
#include <random>
#include "Request.h"
#include "Queue.h"
#include "ServiceChannel.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::ofstream logFile("simulation_log.txt");
    if (logFile.is_open()) {
        logFile << "--- Старт симуляции ---\n";
    }

    ServiceChannel channel;

    double currentTime = 0.0;
    double maxSimulationTime = 5.0;
    double timeStep = 1.0;

    int nextRequestId = 1;
    double totalWaitTime = 0.0;
    int processedCount = 0;
    Queue q;

    double minArrival = 0.0, maxArrival = 0.0;
    cout <<"Введите мин. и макс. интервал прихода заявок (через пробел): ";
    cin >> minArrival >> maxArrival;
    if (logFile.is_open()) {
        logFile <<"Интервал прихода заявок: от " << minArrival << " до " << maxArrival << " сек.\n";
    }

    double minService, maxService;
    cout <<"Введите мин. и макс. интервал длительности обслуживания заявки (через пробел): ";
    cin >> minService >> maxService;
    if (logFile.is_open()) {
        logFile <<"Интервал длительности обслуживания заявки: от " << minService << " до " << maxService << " сек. \n";
    }

    cout << "--- Старт симуляции ---" << endl;

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> arrivalDist(minArrival, maxArrival);
    std::uniform_real_distribution<double> serviceDist(minService, maxService);
    double nextArrivalTime = arrivalDist(gen);

    while (currentTime < maxSimulationTime) {
        currentTime += timeStep;
        cout << "-тактовая секунда: " << currentTime << endl;
        if (logFile.is_open()) {
            logFile << "-тактовая секунда: " << currentTime << "\n";
        }
        cout << "Заявок в очереди: " << q.getSize() << "\n";
        cout << "Статус канала: " << (channel.isBusy() ? "Занят" : "Свободен")<< endl;
        cout << "Обслужено клиентов: " << processedCount << endl;
        if (logFile.is_open()) {
            logFile << "Заявок в очереди:" << q.getSize() <<"\n";
            logFile << "Статус канала: " << (channel.isBusy() ? "Занят" : "Свободен")<< "\n";
            logFile << "Обслужено клиентов: " << processedCount << "\n";
        }

        channel.update(currentTime);

        if (currentTime >= nextArrivalTime) {
            Request req(nextRequestId++, currentTime);
            q.push(req);
            nextArrivalTime = currentTime + arrivalDist(gen);
            cout << "Поступила новая заявка в очередь!" << endl;
            if (logFile.is_open()) {
                logFile << "Поступила новая заявка в очередь!\n";
            }
        }

        if (!channel.isBusy() && !q.isEmpty()) {
            Request req = q.front();

            double currentServiceTime = serviceDist(gen);
            channel.takeRequest(req, currentTime, currentServiceTime);

            double waitTime = currentTime - req.getArrivalTime();
            totalWaitTime += waitTime;
            processedCount++;
            q.pop();

            cout << "Канал взял заявку из очереди!" << endl;
            cout << "Канал взял " << req << ". Время ожидания: " << waitTime << " сек." << endl;

            if (logFile.is_open()) {
                logFile << "Канал взял заявку из очереди!\n";
                logFile << "Канал взял " << req << ". Время ожидания: " << waitTime << " сек.\n";
            }
        }
    }

    if (processedCount > 0) {
        double avgWaitTime = totalWaitTime / processedCount;
        cout << "Среднее время ожидания: " << avgWaitTime << " сек." << endl;
        if (logFile.is_open()) {
            logFile << "Среднее время ожидания: " << avgWaitTime << " сек.\n";
        }
    }

    cout << "\n--- Конец симуляции ---\n" << "Лог симуляции успешно сохранен в файл 'simulation_log.txt'" << endl;
    return 0;
}