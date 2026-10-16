#ifndef SMO_SERVICECHANNEL_H
#define SMO_SERVICECHANNEL_H

#include "Request.h"

class ServiceChannel {
private:
    bool m_isBusy;
    double m_serviceEndTime;
    Request m_currentRequest;

public:
    ServiceChannel();
    void takeRequest(const Request& req, double currentTime, double serviceDuration);
    void update(double currentTime);
    bool isBusy() const;
    const Request& getCurrentRequest() const;

};

#endif //SMO_SERVICECHANNEL_H