#ifndef ITEMMODELPACKAGE_H
#define ITEMMODELPACKAGE_H

#include <engine/scene/animation/Animation.h>

class ItemModelPackage
{
public:
    ItemModelPackage();
    ItemModelPackage(const Animation * animation);


    static void store(const Animation * animation, QStandardItem & itemModel);

    static void click(const QVariant & variant);


private:
    enum Header {
        ANIMATION = 1
    } header;

    const void * data;
//    std::vector<ItemModelPackage

};

#endif // ITEMMODELPACKAGE_H
