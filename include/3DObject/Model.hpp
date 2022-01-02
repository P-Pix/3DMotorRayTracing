#pragma once

#include "Drawable.hpp"
#include "../Struct/Tab3D.hpp"

namespace Object {
    class Model : public Object::Drawable {
    private:
        Structure::Tab3D<int> m_Model;
        void init(Object::Point3D<int> *position, SDL_Renderer *renderer);
    public:
        Model(void);
        Model(Object::Model *model);
        Model(int x, int y, int z);
        Model(int x, int y, int z, SDL_Renderer* renderer);
        ~Model(void);

        void draw(void);
    };
}