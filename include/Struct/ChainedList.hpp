#pragma once

#include <iostream>

namespace Structure {
    template<typename T>
    class ChainedList {
    private:
        T m_Data = nullptr;
        ChainedList<T> *m_Next = nullptr;

    public:
        ChainedList(void) {
        }

        ChainedList(T data) {
            this->set(data);
        }

        ChainedList(T data, ChainedList<T> *next) {
            this->set(data);
            this->set(next);
        }

        ~ChainedList(void) {
        }

        void set(T data) {
            this->m_Data = data;
        }

        void set(ChainedList<T> *list) {
            this->m_Next = list;
        }

        T getData(void) {
            return this->m_Data;
        }

        ChainedList<T> *getNext(void) {
            return this->m_Next;
        }

        void add(T data) {
            ChainedList<T> *list = new ChainedList<T>(data);
            this->add(list);
        }

        void add(ChainedList<T> *list) {
            if (this->m_Data == nullptr) {
                this->set(list->getData());
                return;
            }
            if (this->m_Next == nullptr) {
                this->set(list);
            } else {
                this->m_Next->add(list);
            }
        }
    };
}