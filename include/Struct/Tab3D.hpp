#pragma once

#include "Tab2D.hpp"

namespace Structure {
    template <typename T>
    class Tab3D : public Structure::Tab2D<T> {
    private:
        void initTab(void) {
            this->m_Tab = new Structure::Tab2D<T>*[this->getDeep()];
            for (size_t i = 0; i < this->getDeep(); i++) {
                this->set(i, new Structure::Tab2D<T>(this->m_Width, this->m_Height));
            }
        }
    protected:
        size_t m_Deep = 0;
        Structure::Tab2D<T> **m_Tab;

    public:
        Tab3D(void) {
            this->initTab();
        }

        Tab3D(size_t width, size_t height, size_t deep) {
            this->setSize(width, height, deep);
            this->initTab();
        }

        ~Tab3D(void) {
            for (size_t i = 0; i < this->getDeep(); i++) {
                delete this->m_Tab[i];
            }
            delete[] this->m_Tab;
        }

        void remake(void) {
            for (size_t i = 0; i < this->getDeep(); i++) {
                delete this->m_Tab[i];
            }
            delete[] this->m_Tab;
            this->initTab();
        }

        void set(size_t x, size_t y, size_t z, T value) {
            this->m_Tab[z]->set(x, y, value);
        }

        void set(size_t z, Structure::Tab2D<T> *tab) {
            if (z >= this->getDeep()) {
                std::cerr << "Error: Tab3D::set(size_t z, Structure::Tab2D<T> *tab) - z >= this->getDeep()" << std::endl;
                return;
            }
            this->m_Tab[z] = tab;
        }

        void setSize(size_t width, size_t height, size_t deep) {
            this->m_Deep = deep;
            this->setHeight(height);
            this->setWidth(width);
        }

        T get(size_t x, size_t y, size_t z) {
            if (z >= this->getDeep()) {
                std::cerr << "Error: Tab3D::get(size_t x, size_t y, size_t z) - z >= this->m_Deep" << std::endl;
                return 0;
            }
            return this->m_Tab[z]->get(x, y);
        }

        size_t getDeep(void) {
            return this->m_Deep;
        }
    };
}