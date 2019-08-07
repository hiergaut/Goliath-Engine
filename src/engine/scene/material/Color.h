#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>
#include <iostream>
#include <QColor>

struct Color {
    glm::vec3 color;
    enum Etype {
        AMBIENT = 0,
        DIFFUSE,
        SPECULAR,
        size
    } type;

    //    operator const char*() const
    //    {
    //        switch (type) {
    //        case type::DIFFUSE:
    //            return "color_diffuse";

    //        case type::SPECULAR:
    //            return "color_specular";

    //        case type::AMBIENT:
    //            return "color_ambient";

    //        }
    //    }

    const char* to_string() const
    {
//        Q_ASSERT(DIFFUSE <= type && type <= SPECULAR);
        switch (type) {
        case Etype::AMBIENT:
            return "ambient";

        case Etype::DIFFUSE:
            return "diffuse";

        case Etype::SPECULAR:
            return "specular";


        default:
            throw std::out_of_range("no color type");
        }
    }

    operator QColor() const
    {
        return QColor(color.x * 255.0f, color.y * 255.0f, color.z * 255.0f);
    }

    operator glm::vec3() const
    {
        return color;
    }

    void operator=(glm::vec3&& vec3)
    {
        color = vec3;
    }
    //    operator glm::vec3() {
    //        return color;
    //    }
};

#endif // COLOR_H
