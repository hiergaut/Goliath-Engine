#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>
#include <iostream>
#include <QColor>

#include <session/Session.h>

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
    void load(std::ifstream & file) {
//        color = Session::load<glm::vec3>(file);
        Session::load(color, file);
//        Session::load(static_cast<int*>(&type), file));
        type = Etype(Session::loadEnum(file));
    }

    void save(std::ofstream & file) const {
        Session::save(color, file);
        Session::saveEnum(static_cast<int>(type), file);
    }

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

    void operator=(const glm::vec3 & vec3) {
        color = vec3;
    }
    //    operator glm::vec3() {
    //        return color;
    //    }
};

#endif // COLOR_H
