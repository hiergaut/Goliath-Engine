#ifndef ITEMMODELPACKAGE_H
#define ITEMMODELPACKAGE_H

#include <engine/scene/model/animation/Animation.h>
#include <engine/scene/model/Node.h>

class ItemModelPackage
{
public:
//    ItemModelPackage();
    ItemModelPackage(const Animation * animation);
    ItemModelPackage(const Node * node);


    template<class T>
    static void store(const T * animation, QStandardItem & itemModel) {
        ItemModelPackage * package = new ItemModelPackage(animation);
    //    qDebug() << "store package " << package;
        itemModel.setData(QVariant::fromValue((void*)package), Qt::UserRole);
    }

    static void click(const QVariant & variant);


private:
    enum Header {
        ANIMATION = 1,
        NODE,
    } header;

    const void * data;
//    std::vector<ItemModelPackage

};

#endif // ITEMMODELPACKAGE_H
