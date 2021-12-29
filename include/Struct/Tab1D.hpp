#pragma once

#include <iostream>

namespace Structure {
    template <typename T>
    class Tab1D {
    protected:
        size_t m_Size = 0;
        T* m_Tab;

    public:
        Tab1D(void) {

        }
        Tab1D(size_t size) {
            this->m_Size = size;
            this->m_Tab = new T[m_Size];
        }
        Tab1D(const Tab1D& tab) {
            this->m_Size = tab.m_Size;
            this->m_Tab = new T[m_Size];
            for (size_t i = 0; i < m_Size; i++) {
                this->m_Tab[i] = tab.m_Tab[i];
            }
        }
        ~Tab1D(void) {
            delete[] this->m_Tab;
        }

        T& operator[](size_t index) {
            return this->m_Tab[index];
        }
        const T& operator[](size_t index) const {
            return this->m_Tab[index];
        }

        Tab1D& operator=(const Tab1D& tab) {
            if (this != &tab) {
                this->m_Size = tab.m_Size;
                delete[] this->m_Tab;
                this->m_Tab = new T[m_Size];
                for (size_t i = 0; i < m_Size; i++) {
                    this->m_Tab[i] = tab.m_Tab[i];
                }
            }
            return *this;
        }

        size_t size(void) const {
            return this->m_Size;
        }
    };
}