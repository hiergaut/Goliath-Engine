#include "ItemModelPackage.h"
#include <QDebug>

ItemModelPackage::ItemModelPackage()
{

}

ItemModelPackage::ItemModelPackage(const Animation *animation)
    : header(ANIMATION)
    , data(animation)
{


}

void ItemModelPackage::store(const Animation  *animation, QStandardItem &itemModel)
{
    ItemModelPackage * package = new ItemModelPackage(animation);
//    qDebug() << "store package " << package;
    itemModel.setData(QVariant::fromValue((void*)package), Qt::UserRole);

//    qDebug() << "package after variant" << itemModel.data(Qt::UserRole).value<void*>();
//    ItemModelPackage * packageTest = static_cast<ItemModelPackage*>(itemModel.data(Qt::UserRole).data());
//    qDebug() << "packageTest " << packageTest;
//    qDebug();
}

void ItemModelPackage::click(const QVariant &variant)
{
    void * package = variant.value<void*>();

    if (package == nullptr)
        return;

    ItemModelPackage * p = static_cast<ItemModelPackage*>(package);
//    ItemModelPackage * p = variant.value<ItemModelPackage*>();
//    qDebug() << p << p->header << p->data;
//    qDebug() << "unpack package " << p << "header" << p->header << "data" << p->data;

    switch (p->header) {
        case ANIMATION:
            const Animation * a = static_cast<const Animation*>(p->data);
//            qDebug() << "load animation " << a;
            a->onClick();
        break;

    }

}
