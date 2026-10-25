#include "Queue.h"
#include <stdexcept>

Queue::Queue() : m_head(nullptr), m_tail(nullptr), m_size(0) {}
Queue::~Queue() {
    clear();
    }

void Queue::clear() {
    while (m_head != nullptr) {
        Node* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
    m_tail = nullptr;
    m_size = 0;
}

void Queue::push(const Request& req) {
    Node* newNode = new Node(req);

    if (isEmpty()) {
        m_head = newNode;
        m_tail = newNode;
    }else {
        m_tail->m_next = newNode;
        m_tail = newNode;
    }
    m_size++;
}

void Queue::pop() {
    if (isEmpty()) return;
    Node* temp = m_head;
    m_head = m_head->m_next;
    delete temp;
    m_size--;
    if (m_head == nullptr) {
        m_tail = nullptr;
    }
}
const Request& Queue::front() const {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    return m_head->m_data;
}
bool Queue::isEmpty() const {
    return m_size == 0;
}
size_t Queue::getSize() const {
    return m_size;
}
