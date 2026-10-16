#ifndef SMO_NODE_H
#define SMO_NODE_H
#include "Request.h"

struct Node {
    Request m_data;
    Node* m_next;

    Node(const Request& req) : m_data(req), m_next(nullptr) {}
};

#endif //SMO_NODE_H