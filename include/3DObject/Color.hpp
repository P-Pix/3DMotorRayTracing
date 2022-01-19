#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace Object {
    class Color {
    private:
        SDL_Color m_Color = {0, 0, 0, 0};

        /**
         * @brief Set the color to the attribut m_Color
         *
         * @param color pointer to the color
         * @require color != nullptr
         * @ensure m_Color == *color
         */
        void init(const SDL_Color &color);

    public:
        /**
         * @brief Construct a new Color object
         *
         * @ensure m_Color == {0, 0, 0, 0}
         */
        Color(void);

        /**
         * @brief Construct a new Color object
         *
         * @param red Uint8 value
         * @param green Uint8 value
         * @param blue Uint8 value
         * @param alpha Uint8 value
         * @require red >= 0 && red <= 255
         * @require green >= 0 && green <= 255
         * @require blue >= 0 && blue <= 255
         * @require alpha >= 0 && alpha <= 255
         * @ensure call the init function
         */
        Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

        /**
         * @brief Construct a new Color object
         * @param color pointer to SDL_Color
         * @require color != nullptr
         * @ensure call the init function
         */
        Color(const SDL_Color &color);

        /**
         * @brief Destroy the Color object
         */
        ~Color(void);

        /**
         * @brief Get the red color
         * @return The red color between 0 and 255
         */
        Uint8 getRed(void) const;

        /**
         * @brief Get the green color
         * @return The green color between 0 and 255
         */
        Uint8 getGreen(void) const;

        /**
         * @brief Get the blue color
         * @return The blue color between 0 and 255
         */
        Uint8 getBlue(void) const;

        /**
         * @brief Get the alpha color
         * @return The alpha color between 0 and 255
         */
        Uint8 getAlpha(void) const;

        /**
         * @brief Get the SDL Color
         * @return The SDL Color
         */
        SDL_Color getSDLColor(void);

        /**
         * @brief Get the color as a float
         * @return The red color as a float between 0.0 and 1.0
         */
        float getRedF(void) const;

        /**
         * @brief Get the color as a float
         * @return The green color as a float between 0.0 and 1.0
         */
        float getGreenF(void) const;

        /**
         * @brief Get the color as a float
         * @return The blue color as a float between 0.0 and 1.0
         */
        float getBlueF(void) const;

        /**
         * @brief Get the color as a float
         * @return The alpha color as a float between 0.0 and 1.0
         */
        float getAlphaF(void) const;

        /**
         * @brief Set the red color
         * @param red Uint8 value
         * @require red >= 0 && red <= 255
         * @ensure m_Color.r == red
         */
        void setRed(Uint8 red);

        /**
         * @brief Set the green color
         * @param green Uint8 value
         * @require green >= 0 && green <= 255
         * @ensure m_Color.g == green
         */
        void setGreen(Uint8 green);

        /**
         * @brief Set the blue color
         * @param blue Uint8 value
         * @require blue >= 0 && blue <= 255
         * @ensure m_Color.b == blue
         */
        void setBlue(Uint8 blue);

        /**
         * @brief Set the alpha color
         * @param alpha Uint8 value
         * @require alpha >= 0 && alpha <= 255
         * @ensure m_Color.a == alpha
         */
        void setAlpha(Uint8 alpha);

        /**
         * @brief Set the red color
         * @param red float value
         * @require red >= 0.0 && red <= 1.0
         * @ensure m_Color.r == red * 255
         */
        void setRedF(float red);

        /**
         * @brief Set the green color
         * @param green float value
         * @require green >= 0.0 && green <= 1.0
         * @ensure m_Color.g == green * 255
         */
        void setGreenF(float green);

        /**
         * @brief Set the blue color
         * @param blue float value
         * @require blue >= 0.0 && blue <= 1.0
         * @ensure m_Color.b == blue * 255
         */
        void setBlueF(float blue);

        /**
         * @brief Set the alpha color
         * @param alpha float value
         * @require alpha >= 0.0 && alpha <= 1.0
         * @ensure m_Color.a == alpha * 255
         */
        void setAlphaF(float alpha);

        /**
        * @brief Set the color
        * @param red Uint8 value
        * @param green Uint8 value
        * @param blue Uint8 value
        * @param alpha Uint8 value
        * @require red >= 0 && red <= 255
        * @require green >= 0 && green <= 255
        * @require blue >= 0 && blue <= 255
        * @require alpha >= 0 && alpha <= 255
        * @ensure m_Color.r == red && m_Color.g == green && m_Color.b == blue && m_Color.a == alpha
        */
        void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

        /**
         * @brief Set the color
         * @param color pointer to a SDL_Color
         * @require color != nullptr
         * @ensure m_Color == *color
         */
        void setColor(const SDL_Color &color);

        /**
         * @brief Set the color
         * @param red float value
         * @param green float value
         * @param blue float value
         * @param alpha float value
         * @require red >= 0.0 && red <= 1.0
         * @require green >= 0.0 && green <= 1.0
         * @require blue >= 0.0 && blue <= 1.0
         * @require alpha >= 0.0 && alpha <= 1.0
         * @ensure m_Color.r == red * 255 && m_Color.g == green * 255 && m_Color.b == blue * 255 && m_Color.a == alpha * 255
         */
        void setColor(float red, float green, float blue, float alpha = 1.0f);

        /**
         * @brief Create a color instance from
         * @param color1 Color Object pointer
         * @param color2 Color Object pointer
         * @param t float multiplication factor
         * @require color1 != nullptr
         * @require color2 != nullptr
         * @ensure Vectorized color
         * @return new Color instance
         */
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