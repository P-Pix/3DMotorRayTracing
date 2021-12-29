#pragma once

#include <iostream>

namespace Structure {
    template<typename T>
    class Tab2D {
    private:
        void initTab(void) {
            this->m_Tab = new T *[this->m_Height];
            for (size_t i = 0; i < this->m_Height; i++) {
                this->m_Tab[i] = new T[this->m_Width];
            }
        }

    protected:
        size_t m_Width = 0;
        size_t m_Height = 0;
        T **m_Tab;

    public:
        Tab2D(void) {
            this->initTab();
        }

        Tab2D(size_t width, size_t height) {
            this->setSize(width, height);
        }

        ~Tab2D(void) {
        }

        void setHeight(size_t height) {
            this->m_Height = height;
            this->initTab();
        }

        void setWidth(size_t width) {
            this->m_Width = width;
            this->initTab();
        }

        void setSize(size_t width, size_t height) {
            this->m_Width = width;
            this->m_Height = height;
            this->initTab();
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
            if (x > this->getWidth() || y > this->getHeight()) {
                std::cout << "Error : Out of range" << std::endl;
                return;
            }
            this->m_Tab[y][x] = value;
        }

        T get(size_t x, size_t y) {
            if (x > this->getWidth() || y > this->getHeight()) {
                std::cout << "Error : Out of range" << std::endl;
                return 0;
            }
            return this->m_Tab[y][x];
        }

        size_t getWidth(void) {
            return this->m_Width;
        }

        size_t getHeight(void) {
            return this->m_Height;
        }
    };
}