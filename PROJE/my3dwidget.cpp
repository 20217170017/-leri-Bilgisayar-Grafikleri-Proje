#include "my3dwidget.h"
#include <QVBoxLayout>
#include <Qt3DExtras/Qt3DExtras>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>

My3DWidget::My3DWidget(QWidget *parent)
    : QWidget(parent)
{
    // Qt3D penceresi oluştur
    view = new Qt3DExtras::Qt3DWindow();
    auto *frameGraph = view->defaultFrameGraph();
    auto *forwardRenderer = qobject_cast<Qt3DExtras::QForwardRenderer *>(frameGraph);
    if (forwardRenderer) {
        forwardRenderer->setClearColor(QColor(QRgb(0x87CEEB))); // Gökyüzü mavisi
    }

    // Pencere için container oluştur
    container = QWidget::createWindowContainer(view);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(container);

    // Köpek kulübesi için kök varlık oluştur
    rootEntity = new Qt3DCore::QEntity();

    // Köpek kulübesi tabanı (dikdörtgen prizma)
    Qt3DCore::QEntity *baseEntity = new Qt3DCore::QEntity(rootEntity);

    // Dikdörtgen prizma mesh'i oluştur
    Qt3DExtras::QCuboidMesh *baseMesh = new Qt3DExtras::QCuboidMesh();
    baseMesh->setXExtent(4.0f); // X ekseninde genişlik
    baseMesh->setYExtent(2.0f); // Y ekseninde yükseklik
    baseMesh->setZExtent(3.0f); // Z ekseninde derinlik
    baseEntity->addComponent(baseMesh);

    // Dikdörtgen prizma konumunu ayarla
    Qt3DCore::QTransform *baseTransform = new Qt3DCore::QTransform();
    baseTransform->setTranslation(QVector3D(0.0f, 1.0f, 0.0f));
    baseEntity->addComponent(baseTransform);

    // Malzeme oluştur ve rengini ayarla
    Qt3DExtras::QPhongMaterial *baseMaterial = new Qt3DExtras::QPhongMaterial();
    baseMaterial->setDiffuse(QColor("#DAA520")); // Açık odunsu kahverengi
    baseEntity->addComponent(baseMaterial);

    // Köpek kulübesi çatısı (üçgen taban)
    Qt3DCore::QEntity *roofEntity = new Qt3DCore::QEntity(rootEntity);

    // Piramidin oluşturulması
    Qt3DCore::QEntity *pyramidEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QConeMesh *pyramidMesh = new Qt3DExtras::QConeMesh();
    pyramidMesh->setTopRadius(0.0f); // Piramidin üst yarıçapı (0 olacak, yani üçgen)
    pyramidMesh->setBottomRadius(2.0f); // Piramidin taban yarıçapı
    pyramidMesh->setLength(2.0f); // Piramidin yüksekliği
    pyramidMesh->setRings(100); // Piramidin kenar sayısı
    pyramidMesh->setBottomRadius(3.0f); // Alt yarıçapı (dikdörtgen prizma)
    pyramidEntity->addComponent(pyramidMesh);


    Qt3DCore::QTransform *pyramidTransform = new Qt3DCore::QTransform();
    pyramidTransform->setTranslation(QVector3D(0.0f, 3.0f, 0.0f)); // Piramidin konumu (dikdörtgen prizmanın üstünde)
    pyramidTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 0.0f)); // Piramidin dönüşü (isteğe bağlı)
    pyramidEntity->addComponent(pyramidTransform);

    Qt3DExtras::QPhongMaterial *pyramidMaterial = new Qt3DExtras::QPhongMaterial();
    pyramidMaterial->setDiffuse(QColor(QRgb(0xFFD700))); // Altın rengi
    pyramidEntity->addComponent(pyramidMaterial);

    // Köpek kulübesi için kapı (oval kapı)
    Qt3DCore::QEntity *doorEntity = new Qt3DCore::QEntity(rootEntity);

    // Oval kapı mesh'i oluştur
    Qt3DExtras::QCylinderMesh *doorMesh = new Qt3DExtras::QCylinderMesh();
    doorMesh->setRadius(0.7f); // Oval kapının yarıçapı (X ve Z eksenlerinde)
    doorMesh->setLength(0.2f); // Kapının kalınlığı (Y ekseninde)
    doorMesh->setRings(100); // Kapının kenar sayısı (dairesel çözünürlük)
    doorMesh->setSlices(20); // Kapının dilim sayısı (yönlü çözünürlük)
    doorEntity->addComponent(doorMesh);

    // Oval kapı konumunu ayarla
    Qt3DCore::QTransform *doorTransform = new Qt3DCore::QTransform();
    doorTransform->setTranslation(QVector3D(0.0f, 0.9f, 1.5f)); // Prizmanın yüzeyine göre konumu
    doorTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90.0f)); // Kapının dönüşü (isteğe bağlı)
    doorEntity->addComponent(doorTransform);

    // Kapı için malzeme oluştur
    Qt3DExtras::QPhongMaterial *doorMaterial = new Qt3DExtras::QPhongMaterial();
    doorMaterial->setDiffuse(Qt::white); // Diffuse (yayılan) rengi beyaz olarak ayarla
    doorEntity->addComponent(doorMaterial);



    // Kamera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 10, 10));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Kamera kontrolcüsü
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(camera);

    // Kök varlık ayarları
    view->setRootEntity(rootEntity);
}

My3DWidget::~My3DWidget()
{
}
