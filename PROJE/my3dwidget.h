#ifndef MY3DWIDGET_H
#define MY3DWIDGET_H

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>



class My3DWidget : public QWidget
{
    Q_OBJECT

public:
    explicit My3DWidget(QWidget *parent = nullptr);
    ~My3DWidget();

private:
    QWidget *container;
    Qt3DExtras::Qt3DWindow *view;
    Qt3DCore::QEntity *rootEntity;
};

#endif // MY3DWIDGET_H
