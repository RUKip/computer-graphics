#include "mainview.h"
#include "math.h"

#include <QDateTime>

void MainView::addShaders(){
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");
    shaderProgram->link();
    shaderProgram->bind();
}

MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

MainView::~MainView() {
    debugLogger->stopLogging();

    qDebug() << "MainView destructor";
}

void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ), this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    //initialization of buffers and shaders
    addShaders();
    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);

    //initalization of shapes/world
    vertex vertices[] = {{0.0f,1.0f,0.0f,0.0f,1.0f}, {0.0f,0.0f,1.0f,-1.0f,-1.0f}, {1.0f,0.0f,0.0f,1.0f,-1.0f}}; //our triangle, TODO: correct like this??
}

void MainView::resizeGL(int newWidth, int newHeight) {

    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
}

void MainView::paintGL() {

}

void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
