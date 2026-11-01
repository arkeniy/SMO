#ifndef SMO_REQUEST_H
#define SMO_REQUEST_H
#include <ostream>

enum class Priority {Low, Medium, High};

class Request {
private:
    int m_id;
    double m_arrivalTime;
    Priority m_priority;

public:
    Request();
    Request(int id, double arrivalTime, Priority priority = Priority::Low);
    Request(const Request& other);
    ~Request();
    int getId()const;
    double getArrivalTime() const;
    Priority getPriority() const;
};

std::ostream& operator<<(std::ostream& os, const Request& req);

#endif //SMO_REQUEST_H