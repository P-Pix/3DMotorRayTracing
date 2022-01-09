#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace Object {
    class Color {
    private:
        SDL_Color m_Color = {0, 0, 0, 0};

        void init(const SDL_Color &color);

    public:
        Color(void);

        Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

        Color(const SDL_Color &color);

        ~Color(void);

        Uint8 getRed(void) const;

        Uint8 getGreen(void) const;

        Uint8 getBlue(void) const;

        Uint8 getAlpha(void) const;

        SDL_Color getSDLColor(void);

        float getRedF(void) const;

        float getGreenF(void) const;

        float getBlueF(void) const;

        float getAlphaF(void) const;

        void setRed(Uint8 red);

        void setGreen(Uint8 green);

        void setBlue(Uint8 blue);

        void setAlpha(Uint8 alpha);

        void setRedF(float red);

        void setGreenF(float green);

        void setBlueF(float blue);

        void setAlphaF(float alpha);

        void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

        void setColor(const SDL_Color &color);

        void setColor(float red, float green, float blue, float alpha = 1.0f);

        static Object::Color &lerp(const Object::Color &color1, const Object::Color &color2, float t);

        Object::Color operator+(const Object::Color &color) const;

        Object::Color operator-(const Object::Color &color) const;

        Object::Color operator*(const Object::Color &color) const;

        Object::Color operator/(const Object::Color &color) const;

        Object::Color operator*(float value) const;

        Object::Color operator/(float value) const;

        Object::Color &operator+=(const Object::Color &color);

        Object::Color &operator-=(const Object::Color &color);

        Object::Color &operator*=(const Object::Color &color);

        Object::Color &operator/=(const Object::Color &color);

        Object::Color &operator*=(float value);

        Object::Color &operator/=(float value);
    };

    static const Object::Color BLACK = Object::Color(0, 0, 0);
    static const Object::Color WHITE = Object::Color(255, 255, 255);
    static const Object::Color RED = Object::Color(255, 0, 0);
    static const Object::Color GREEN = Object::Color(0, 255, 0);
    static const Object::Color BLUE = Object::Color(0, 0, 255);
    static const Object::Color YELLOW = Object::Color(255, 255, 0);
    static const Object::Color CYAN = Object::Color(0, 255, 255);
    static const Object::Color MAGENTA = Object::Color(255, 0, 255);
    static const Object::Color TRANSPARENT = Object::Color(0, 0, 0, 0);
}