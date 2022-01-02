#pragma once

#include <iostream>
#include "Tab1D.hpp"

namespace Structure {
    template<typename T>
    class Tab2D : public Structure::Tab1D<T> {
    private:
        void initTab(void) {
            this->m_Tab = new Structure::Tab1D<T>*[this->getHeight()];
            for (size_t i = 0; i < this->getHeight(); i++) {
                this->set(i, new Structure::Tab1D<T>(this->m_Width));
            }
        }

    protected:
        size_t m_Height = 0;
        Structure::Tab1D<T> **m_Tab;

    public:
        Tab2D(void) {
            this->initTab();
        }

        Tab2D(size_t width, size_t height) {
            this->setSize(width, height);
        }

        ~Tab2D(void) {
            for (size_t i = 0; i < this->m_Height; i++) {
                delete this->m_Tab[i];
            }
            delete[] this->m_Tab;
        }

        void remake(void) {
            for (size_t i = 0; i < this->getHeight(); i++) {
                delete this->m_Tab[i];
            }
            delete[] this->m_Tab;
            this->initTab();
        }

        void setHeight(size_t height) {
            this->m_Height = height;
        }

        void setSize(size_t width, size_t height) {
            this->setWidth(width);
            this->m_Height = height;
        }

        void initPointer(void) {
            for (size_t i = 0; i < this->m_Height; i++) {
                for (size_t j = 0; j < this->m_Width; j++) {
                    this->m_Tab[i][j] = nullptr;
                }
            }
        }

        void initValue(void) {
            for (size_t i = 0; i < this->m_Height; i++) {
                for (size_t j = 0; j < this->m_Width; j++) {
                    this->m_Tab[i][j] = 0;
                }
            }
        }

        void initChar(void) {
            for (size_t i = 0; i < this->m_Height; i++) {
                for (size_t j = 0; j < this->m_Width; j++) {
                    this->m_Tab[i][j] = '\0';
                }
            }
        }

        void print(void) {
            for (size_t i = 0; i < this->m_Height; i++) {
                for (size_t j = 0; j < this->m_Width; j++) {
                    std::cout << this->m_Tab[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        void set(size_t x, size_t y, T value) {
            if (y >= this->getHeight()) {
                std::cout << "Error : Out of range" << std::endl;
                return;
            }
            this->m_Tab[y]->set(x, value);
        }

        void set(size_t y, Structure::Tab1D<T> *tab) {
            if (y >= this->getHeight()) {
                std::cout << "Error : Out of range" << std::endl;
                return;
            }
            this->m_Tab[y] = tab;
        }

        T get(size_t x, size_t y) {
            if (y >= this->getHeight()) {
                std::cout << "Error : Out of range" << std::endl;
                return 0;
            }
            return this->m_Tab[y]->get(x);
        }

        size_t getHeight(void) {
            return this->m_Height;
        }
    };
}