#include "my3dwidget.h"
#include <QVBoxLayout>
#include <Qt3DExtras/Qt3DExtras>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DRender/QTexture>
#include <Qt3DExtras/QTextureMaterial>
#include <Qt3DExtras/QDiffuseMapMaterial>

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

    // Kök varlık için transform oluştur
    rootTransform = new Qt3DCore::QTransform();
    rootEntity->addComponent(rootTransform);

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

    // Doku malzemesi oluştur
    Qt3DExtras::QDiffuseMapMaterial *baseMaterial = new Qt3DExtras::QDiffuseMapMaterial();
    Qt3DRender::QTextureLoader *textureLoader = new Qt3DRender::QTextureLoader();
    textureLoader->setSource(QUrl::fromLocalFile(":/jpg/resources/wood_texture.jpg"));
    baseMaterial->setDiffuse(textureLoader);
    baseEntity->addComponent(baseMaterial);

    // Çatı
    Qt3DCore::QEntity *roofEntity = new Qt3DCore::QEntity(rootEntity);

    // Çatı mesh'i oluştur
    Qt3DExtras::QConeMesh *roofMesh = new Qt3DExtras::QConeMesh();
    roofMesh->setTopRadius(0.0f); // Piramidin üst yarıçapı (0 olacak, yani üçgen)
    roofMesh->setBottomRadius(3.0f); // Piramidin taban yarıçapı, artırıldı
    roofMesh->setLength(3.0f); // Piramidin yüksekliği, artırıldı
    roofMesh->setRings(100); // Piramidin kenar sayısı
    roofEntity->addComponent(roofMesh);

    // Çatı konumunu ayarla
    Qt3DCore::QTransform *roofTransform = new Qt3DCore::QTransform();
    roofTransform->setTranslation(QVector3D(0.0f, 3.5f, 0.0f)); // Piramidin konumu (dikdörtgen prizmanın üstünde)
    roofEntity->addComponent(roofTransform);

    // Çatı malzemesi oluştur
    Qt3DExtras::QDiffuseMapMaterial *roofMaterial = new Qt3DExtras::QDiffuseMapMaterial();
    Qt3DRender::QTextureLoader *roofTextureLoader = new Qt3DRender::QTextureLoader();
    roofTextureLoader->setSource(QUrl::fromLocalFile(":/jpg/resources/roof_texture.jpg"));
    roofMaterial->setDiffuse(roofTextureLoader);
    roofEntity->addComponent(roofMaterial);

    // Kapı (dikdörtgen prizma)
    Qt3DCore::QEntity *doorEntity = new Qt3DCore::QEntity(rootEntity);

    // Dikdörtgen prizma mesh'i oluştur
    Qt3DExtras::QCuboidMesh *doorMesh = new Qt3DExtras::QCuboidMesh();
    doorMesh->setXExtent(1.0f); // Genişlik
    doorMesh->setYExtent(1.0f); // Yükseklik, yarıya düşürüldü
    doorMesh->setZExtent(0.2f); // Kalınlık
    doorEntity->addComponent(doorMesh);

    // Dikdörtgen prizma konumunu ayarla
    Qt3DCore::QTransform *doorTransform = new Qt3DCore::QTransform();
    doorTransform->setTranslation(QVector3D(0.0f, 0.5f, 1.5f)); // Y konumu, yüksekliğe göre ayarlandı
    doorEntity->addComponent(doorTransform);

    // Kapı malzemesi oluştur
    Qt3DExtras::QDiffuseMapMaterial *doorMaterial = new Qt3DExtras::QDiffuseMapMaterial();
    Qt3DRender::QTextureLoader *doorTextureLoader = new Qt3DRender::QTextureLoader();
    doorTextureLoader->setSource(QUrl::fromLocalFile(":/jpg/resources/door_texture.jpg"));
    doorMaterial->setDiffuse(doorTextureLoader);

    // Kapıya malzeme ekle
    doorEntity->addComponent(doorMaterial);

    // Kapının üstüne tabela ekle
    Qt3DCore::QEntity *signEntity = new Qt3DCore::QEntity(rootEntity);

    // Tabela için dikdörtgen prizma oluştur
    Qt3DExtras::QCuboidMesh *signMesh = new Qt3DExtras::QCuboidMesh();
    signMesh->setXExtent(1.5f); // Genişlik
    signMesh->setYExtent(0.5f); // Yükseklik
    signMesh->setZExtent(0.2f); // Kalınlık
    signEntity->addComponent(signMesh);

    // Tabela konumunu ayarla
    Qt3DCore::QTransform *signTransform = new Qt3DCore::QTransform();
    signTransform->setTranslation(QVector3D(0.0f, 1.55f, 1.5f)); // Yükseklik ve konumu kapının hemen üstüne ayarla
    signEntity->addComponent(signTransform);

    // Tabela malzemesi oluştur
    Qt3DExtras::QDiffuseMapMaterial *signMaterial = new Qt3DExtras::QDiffuseMapMaterial();
    Qt3DRender::QTextureLoader *signTextureLoader = new Qt3DRender::QTextureLoader();
    signTextureLoader->setSource(QUrl::fromLocalFile(":/jpg/resources/doghouse.jpg"));
    signMaterial->setDiffuse(signTextureLoader);

    // Tabelaya malzeme ekle
    signEntity->addComponent(signMaterial);

    // Kamera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 3, 10));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Kamera kontrolcüsü
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(camera);

    // Işık ekle
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    light->setWorldDirection(QVector3D(-1, -1, -1));
    lightEntity->addComponent(light);

    // Kök varlık ayarları
    view->setRootEntity(rootEntity);

    // Animasyon için timer oluştur
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, [=]() {
        static float angle = 0.0f;
        angle += 0.1f; // Dönme hızı (daha yavaş için daha küçük bir değer kullanabilirsiniz)
        if (angle >= 360.0f) angle = 0.0f;
        rootTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), angle));
    });
    animationTimer->start(16); // Timer 60 FPS için 16ms aralıklarla çalışacak
}

My3DWidget::~My3DWidget()
{
}
