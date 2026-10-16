#include "ServiceChannel.h"
#include <stdexcept>

ServiceChannel::ServiceChannel() : m_isBusy(false), m_serviceEndTime(0.0), m_currentRequest() {}
void ServiceChannel::takeRequest(const Request &req, double currentTime, double serviceDuration) {
    m_isBusy = true;
    m_currentRequest = req;
    m_serviceEndTime = currentTime + serviceDuration;
}
void ServiceChannel::update(double currentTime) {
    if (m_isBusy && currentTime >= m_serviceEndTime) {
        m_isBusy = false;
    }
}
bool ServiceChannel::isBusy() const {
    return m_isBusy;
}
const Request &ServiceChannel::getCurrentRequest() const {
    return m_currentRequest;
}


