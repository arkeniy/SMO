#ifndef SMO_REQUEST_H
#define SMO_REQUEST_H
#include <ostream>

class Request {
private:
    int m_id;
    double m_arrivalTime;

public:
    Request();
    Request(int id, double arrivalTime);
    Request(const Request& other);
    ~Request();
    int getId()const;
    double getArrivalTime() const;
};

std::ostream& operator<<(std::ostream& os, const Request& req);

#endif //SMO_REQUEST_H