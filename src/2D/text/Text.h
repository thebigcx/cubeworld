#pragma once

#include "Font.h"
#include "../Transformable.h"

class Text : public Transformable
{
    public:
        Text(Font& p_font);

        void setColor(const glm::vec3& color);

        void setString(const std::string& string);

        void setFont(Font& font);

        glm::vec3 getColor() { return m_color; };
        std::string getString() { return m_string; };
        Font* getFont() { return m_pFont; };

    private:
        Font* m_pFont;

        std::string m_string = "";

        glm::vec3 m_color;
};