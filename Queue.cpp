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
    Node* prev = nullptr;
    Node* cur = m_head;
    while (cur != nullptr && cur->m_data.getPriority() >= req.getPriority()) {//пропускаем всех
        prev = cur;
        cur = cur->m_next;
    }
    if (prev == nullptr) {
        newNode->m_next = m_head;
        m_head = newNode;
        if (m_tail == nullptr) {
            m_tail = newNode;
        }
    }else if (cur == nullptr) {
        prev->m_next = newNode;
        m_tail = newNode;
    }else {
        newNode->m_next = cur;
        prev->m_next = newNode;
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
