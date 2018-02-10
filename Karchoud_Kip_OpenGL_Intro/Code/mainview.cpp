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
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //initalization of shapes/world
    vertex vertices[] = {
        {0.0f,1.0f,0.0f,1.0f,0.0f},
        {-1.0f,-1.0f,0.0f,0.0f,1.0f},
        {1.0f,-1.0f,1.0f,0.0f,0.0f}
    }; //our triangle

    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(vertex), vertices, GL_STATIC_DRAW); //set vertices as data of our vbo

    glEnableVertexAttribArray(0);   //Say we send data for postion 0 to shaders, (still to define what is data and match in shader)
    glEnableVertexAttribArray(1);   //Say we send data for postion 1 to shaders

    glVertexAttribPointer(0,2, GL_FLOAT, false, sizeof(vertex), 0);
    glVertexAttribPointer(1,3, GL_FLOAT, false, sizeof(vertex), (GLvoid*)(2*sizeof(GLfloat)));
}

void MainView::resizeGL(int newWidth, int newHeight) {

    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
}

void MainView::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
