#include "Request.h"

Request::Request(): m_id(0), m_arrivalTime(0.0) {}
Request::Request(int id, double arrivalTime): m_id(id), m_arrivalTime(arrivalTime) {}
Request::Request(const Request& other): Request(other.m_id, other.m_arrivalTime) {}
Request::~Request(){}
int Request::getId() const {
    return m_id;
}
double Request::getArrivalTime() const {
    return m_arrivalTime;
}
std ::ostream& operator << (std::ostream& os, const Request& req) {
    os << "Заявка №" << req.getId();
    return os;
}

