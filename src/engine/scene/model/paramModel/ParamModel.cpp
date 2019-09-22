#include "ParamModel.h"
//#include <session/Session.h>

//ParamModel::ParamModel(ParamModel::Type type)
//    : Model(glm::mat4(1.0f), Model::Type::PARAM)
//    , m_type(type)
//{
//}

//ParamModel::ParamModel(std::ifstream& file)
//    : Model(file)
//{
//    m_type = static_cast<Type>(Session::loadEnum(file));
//}
//#include "curve/BSplineCurve.h"
//#include "surface/BSplineSurface.h"

//void ParamModel::save(std::ofstream& file)
//{
//    Model::save(file);

//    Session::saveEnum(m_type, file);
//}

//ParamModel* ParamModel::load(std::ifstream& file)
//{

//    Type type = static_cast<Type>(Session::loadEnum(file));
//    switch (type) {
//    case BSPLINE_CURVE:
//        return new BSplineCurve(file);
//        break;

//    case BSPLINE_SURFACE:
//        break;
//    }
//}
