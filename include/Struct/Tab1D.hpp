#pragma once

#include <iostream>

namespace Structure {
    template <typename T>
    class Tab1D {
    private:
        void initTab(void) {
            this->m_Tab = new T[m_Width];
        }

    protected:
        size_t m_Width = 0;
        T* m_Tab;

    public:
        Tab1D(void) {
            this->initTab();
        }

        Tab1D(size_t size) {
            this->m_Width = size;
            this->initTab();
        }

        Tab1D(const Tab1D& tab) {
            this->m_Width = tab.m_Width;
            this->m_Tab = new T[m_Width];
            for (size_t i = 0; i < m_Width; i++) {
                this->m_Tab[i] = tab.m_Tab[i];
            }
        }

        ~Tab1D(void) {
            this->deleteTab();
        }

        void deleteTab(void) {
            delete[] this->m_Tab;
        }

        void set(size_t index, T value) {
            if (index >= this->getWidth()) {
                std::cerr << "Error: index out of range" << std::endl;
                return;
            }
            this->m_Tab[index] = value;
        }

        void setWidth(size_t width) {
            this->m_Width = width;
            this->deleteTab();
            this->initTab();
        }

        T get(size_t index) {
            if (index >= this->getWidth()) {
                std::cerr << "Error: index out of range" << std::endl;
                return;
            }
            return this->m_Tab[index];
        }

        size_t getWidth(void) {
            return this->m_Width;
        }

        Tab1D& operator=(const Tab1D& tab) {
            if (this != &tab) {
                this->setWidth(tab.getWidth());
                this->deleteTab();
                this->initTab();
                for (size_t i = 0; i < this->getWidth(); i++) {
                    this->set(i, tab->get(i));
                }
            }
            return *this;
        }
    };
}