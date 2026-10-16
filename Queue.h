#ifndef SMO_QUEUE_H
#define SMO_QUEUE_H

#include "Node.h"
#include <cstddef>
#include <stdexcept>

class Queue {
private:
    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    Queue();
    ~Queue();

    void push(const Request& req);
    void pop();

    const Request& front() const;

    bool isEmpty() const;
    size_t getSize() const;
};

#endif //SMO_QUEUE_H