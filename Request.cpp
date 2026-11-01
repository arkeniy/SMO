#include <string>
#include "Request.h"

namespace {
    std::string priorityName(Priority p) {
        switch (p) {
            case Priority::High: return "высокий";
            case Priority::Medium: return "средний";
            case Priority::Low: return "низкий";
        }
        return "?";//значение которого нет среди трёх
    }
}

Request::Request(): m_id(0), m_arrivalTime(0.0), m_priority(Priority::Low) {}
Request::Request(int id, double arrivalTime, Priority priority)
: m_id(id), m_arrivalTime(arrivalTime), m_priority(priority) {}
Request::Request(const Request& other): Request(other.m_id, other.m_arrivalTime, other.m_priority) {}
Request::~Request(){}
int Request::getId() const {
    return m_id;
}
double Request::getArrivalTime() const {
    return m_arrivalTime;
}
Priority Request::getPriority() const {
    return m_priority;
}
std ::ostream& operator << (std::ostream& os, const Request& req) {
    os << "Заявка №" << req.getId() << " (" << priorityName(req.getPriority()) << ")";
    return os;
}

