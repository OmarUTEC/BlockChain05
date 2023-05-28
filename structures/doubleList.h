#ifndef EVALUATEEXPRESSION_ROCKYOU_DOUBLE_H
#define EVALUATEEXPRESSION_ROCKYOU_DOUBLE_H

// codigo de la tarea anterior hecha por nosotros

#include <iostream>
#include "list.h"

template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node *next;
        Node *prev;

        Node() : data(T()), next(nullptr), prev(nullptr) {}

        explicit Node(T value) : data(value), next(nullptr), prev(nullptr) {}

        void killSelf() {
            if (prev) {
                prev->next = next;
            }
            if (next) {
                next->prev = prev;
            }
            delete this;
        }
    };

private:
    Node *head;
    Node *tail;
    int nodes;

public:
    DoubleList() : List<T>(), head(nullptr), tail(nullptr), nodes(0) {}

    ~DoubleList() {
        clear();
    }

    T front() {
       if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T back() {
      if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    void push_front(T data) {
        Node *new_node = new Node(data);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        ++nodes;
    }

    void push_back(T data) {
        Node *new_node = new Node(data);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        ++nodes;
    }

    T pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        T data = head->data;
        Node *temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        --nodes;
        delete temp;
        return data;
    }

    T pop_back() {
        if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        T data = tail->data;
        Node *temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        --nodes;
        delete temp;
        return data;
    }

    T insert(T data, int pos) {
        if (pos < 0 || pos > nodes) {
            throw std::out_of_range("Invalid position");
        }
        if (pos == 0) {
            push_front(data);
            return data;
        }
        if (pos == nodes) {
            push_back(data);
            return data;
        }
        Node *current = head;
        int current_pos = 0;
        while (current_pos < pos) {
            current = current->next;
            ++current_pos;
        }
        Node *new_node = new Node(data);
        new_node->prev = current->prev;
        new_node->next = current;
        current->prev->next = new_node;
        current->prev = new_node;
        ++nodes;
        return data;
    }

    bool remove(int pos) {
        if (pos < 0 || pos >= nodes) {
            return false;
        }

        Node *temp = head;

        if (pos == 0) {
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
        } else if (pos == nodes - 1) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        nodes--;
        return true;
    }

    T &operator[](int pos) {
        Node *current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->data;
    }

    bool is_empty() {
        return (head == nullptr && tail == nullptr);
    }

    int size() {
        return nodes;
    }

    void clear() {
        while (!is_empty()) {
            pop_front();
        }
    }

    void sort() {
        for (int i = 0; i < nodes - 1; i++) {
            Node *current = head;
            for (int j = 0; j < nodes - 1 - i; j++) {
                if (current->data > current->next->data) {
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                }
                current = current->next;
            }
        }
    }

    bool is_sorted() {
        Node *current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->data > current->next->data) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    void reverse() {
        Node *current = head;
        Node *temp = nullptr;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    std::string name() {
        return "DoubleList";
    }

    Node<T> *begin() {
        return head;
    }

    Node<T> *end() {
        return tail;
    }
};

#endif