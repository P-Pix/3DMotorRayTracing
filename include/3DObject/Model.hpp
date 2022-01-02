#pragma once

#include "Drawable.hpp"

namespace Object {
    class Model : public Object::Drawable {
    private:
    public:
        Model(void);
        Model(const Model&);
        Model(int x, int y, int z);
        ~Model(void);
    };
}