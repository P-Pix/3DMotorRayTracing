#pragma once

#include "Drawable.hpp"

namespace Object {
    class Object : public Object::Drawable {
    private:
    public:
        Object(void);
        Object(const Object&);
        Object(int x, int y, int z);
        ~Object(void);
    };
}