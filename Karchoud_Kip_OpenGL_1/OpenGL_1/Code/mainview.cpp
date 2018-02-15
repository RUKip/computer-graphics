#include "mainview.h"
#include "math.h"

#include <QDateTime>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    debugLogger->stopLogging();
    glDeleteVertexArrays(1, &cubeVao);
    glDeleteBuffers(1, &cubeVbo);
    glDeleteVertexArrays(1, &pyVao);
    glDeleteBuffers(1, &pyVbo);
    qDebug() << "MainView destructor";
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
             this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    createShaderProgram();

    //set scales and rotation variables of the world
    initScale = 1.0f;
    worldRotationX = 0;
    worldRotationY = 0;
    worldRotationZ = 0;

    vertex pyramid[] = {
        //front sideGL_CW
        {1.0f, -1.0f, 1.0f, 0.0f, 0.5f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f},
        {-1.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f},


        //left side
        {-1.0f, -1.0f, 1.0f, 0.9f, 0.4f, 1.0f},
        {0.0f, 1.0f, 0.0f, 0.0f, 0.3f, 1.0f},
        {0.0f, -1.0f, -1.0f, 0.3f, 0.2f, 1.0f},

        //right side
        {0.0f, -1.0f, -1.0f, 0.1f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 0.1f, 0.2f, 0.7f},
        {1.0f, -1.0f, 1.0f, 0.2f, 1.0f, 0.3f},

        //bottom side
        {1.0f, -1.0f, 1.0f, 0.9f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, -1.0f, -1.0f, 1.0f, 0.3f, 1.0f}
    };
    //creates objects below //TODO: misses bottom vertices, fix
    vertex cube[] = {
        //front square
        {1.0f,-1.0f,1.0f,0.4f,1.0f,0.5f},
        {-1.0f,1.0f,1.0f,0.2f,1.0f,0.0f},
        {-1.0f,-1.0f,1.0f,0.3f,1.0f,0.9f},

        {-1.0f,1.0f,1.0f,0.5f,0.1f,1.0f},
        {1.0f,-1.0f,1.0f,0.1f,0.2f,1.0f},
        {1.0f,1.0f,1.0f,0.2f,0.1f,1.0f},

        //left side square
        {-1.0f,1.0f,-1.0f,3.0f,1.0f,0.0f},
        {-1.0f,-1.0f,1.0f,1.0f,1.0f,0.4f},
        {-1.0f,1.0f,1.0f,8.0f,1.0f,0.0f},

        {-1.0f,-1.0f,-1.0f,1.0f,0.1f,0.4f},
        {-1.0f,-1.0f,1.0f,1.0f,0.8f,0.2f},
        {-1.0f,1.0f,-1.0f,1.0f,0.0f,0.2f},

        //top square
        {-1.0f,1.0f,-1.0f,0.1f,0.5f,1.0f},
        {-1.0f,1.0f,1.0f,0.7f,0.6f,1.0f},
        {1.0f,1.0f,1.0f,0.2f,0.7f,1.0f},

        {-1.0f,1.0f,-1.0f,0.3f,1.0f,0.5f},
        {1.0f,1.0f,1.0f,0.3f,1.0f,0.1f},
        {1.0f,1.0f,-1.0f,0.9f,1.0f,0.0f},

        //bottom square
        {-1.0f,-1.0f,1.0f,0.5f,1.0f,0.3f},
        {-1.0f,-1.0f,-1.0f,0.3f,1.0f,0.5f},
        {1.0f,-1.0f,-1.0f,0.5f,1.0f,0.5f},

        {-1.0f,-1.0f,1.0f,0.2f,1.0f,0.5f},
        {1.0f,-1.0f,-1.0f,0.6f,1.0f,0.0f},
        {1.0f,-1.0f,1.0f,0.3f,1.0f,0.8f},

        //right square
        {1.0f,1.0f,1.0f,0.9f,1.0f,0.3f},
        {1.0f,-1.0f,1.0f,0.9f,1.0f,0.9f},
        {1.0f,-1.0f,-1.0f,0.2f,1.0f,0.9f},

        {1.0f,1.0f,-1.0f,1.0f,1.0f,0.9f},
        {1.0f,1.0f,1.0f,1.0f,1.0f,0.1f},
        {1.0f,-1.0f,-1.0f,1.0f,1.0f,0.3f},

        //back square
        {1.0f,1.0f,-1.0f,0.6f,0.8f,0.1},
        {1.0f,-1.0f,-1.0f,0.6f,0.7f,0.2f},
        {-1.0f,-1.0f,-1.0f,0.6f,0.6f,0.3f},

        {1.0f,1.0f,-1.0f,0.2f,0.1f,1.0f},
        {-1.0f,-1.0f,-1.0f,0.6f,0.1f,1.0f},
        {-1.0f,1.0f,-1.0f,0.2f,0.9f,1.0f},
    };

    //create projection matrices
    projectionModel.setToIdentity();
    projectionModel.perspective(60, 1, 0.1, 1000);

    //create cube
    //create VAO
    glGenVertexArrays(1, &cubeVao);
    glBindVertexArray(cubeVao);

    //create VB
    glGenBuffers(1, &cubeVbo);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);

    glBufferData(GL_ARRAY_BUFFER, 6*6*sizeof(vertex), cube, GL_STATIC_DRAW); //set vertices as data of our vbo

    glEnableVertexAttribArray(0);   //Say we send data for postion 0(coordinates) to shaders, (still to define what is data and match in shader)
    glEnableVertexAttribArray(1);   //Say we send data for postion 1(colors) to shaders

    glVertexAttribPointer(0,3, GL_FLOAT, false, sizeof(vertex), 0);
    glVertexAttribPointer(1,3, GL_FLOAT, false, sizeof(vertex), (GLvoid*)(3*sizeof(GLfloat)));

    //create pyramid
    glGenVertexArrays(1, &pyVao);
    glBindVertexArray(pyVao);

    glGenBuffers(1, &pyVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pyVbo);

    glBufferData(GL_ARRAY_BUFFER, 3*4*sizeof(vertex), pyramid, GL_STATIC_DRAW); //set vertices as data of our vbo

    glEnableVertexAttribArray(0);   //Say we send data for postion 0(coordinates) to shaders, (still to define what is data and match in shader)
    glEnableVertexAttribArray(1);   //Say we send data for postion 1(colors) to shaders

    glVertexAttribPointer(0,3, GL_FLOAT, false, sizeof(vertex), 0);
    glVertexAttribPointer(1,3, GL_FLOAT, false, sizeof(vertex), (GLvoid*)(3*sizeof(GLfloat)));
}

void MainView::createShaderProgram()
{
    // Create shader program
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader.glsl");
    shaderProgram.link();

    modelTransformVert = shaderProgram.uniformLocation("modelTransform");
    modelProjectionVert = shaderProgram.uniformLocation("projectionTransform");
}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.bind();

    modelTransformCube.setToIdentity();
    modelTransformPy.setToIdentity();
    modelTransformCube.translate(2,0,-6);
    modelTransformPy.translate(-2,0,-6);
    modelTransformCube.scale(initScale);
    modelTransformPy.scale(initScale);
    modelTransformCube.rotate(worldRotationX, {1,0,0});
    modelTransformCube.rotate(worldRotationY, {0,1,0});
    modelTransformCube.rotate(worldRotationZ, {0,0,1});
    modelTransformPy.rotate(worldRotationX, {1,0,0});
    modelTransformPy.rotate(worldRotationY, {0,1,0});
    modelTransformPy.rotate(worldRotationZ, {0,0,1});


    //set uniform matrices projection
    glUniformMatrix4fv(modelProjectionVert, 1, false, projectionModel.data());

    //set uniform matrices shaders (cube)
    glUniformMatrix4fv(modelTransformVert, 1, false, modelTransformCube.data());

    // Draw here cube
    glBindVertexArray(cubeVao);
    glDrawArrays(GL_TRIANGLES, 0, 6*6);

    //set uniform matrices shaders (pyrmamide)
    glUniformMatrix4fv(modelTransformVert, 1, false, modelTransformPy.data());

    // Draw here pyramide
    glBindVertexArray(pyVao);
    glDrawArrays(GL_TRIANGLES, 0, 3*4);


    shaderProgram.release();
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) 
{
//    Q_UNUSED(newWidth)
//    Q_UNUSED(newHeight)
    projectionModel.setToIdentity();
    projectionModel.perspective(60, newWidth/newHeight, 0.1, 1000);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
//    Q_UNIMPLEMENTED();
    worldRotationX = rotateX;
    worldRotationY = rotateY;
    worldRotationZ = rotateZ;
    update();
}

void MainView::setScale(int scale)
{
    qDebug() << "Scale changed to " << scale;
    //Q_UNIMPLEMENTED();
    //min 1, max 200
    initScale = ((float) scale/100);
    update();
}

void MainView::setShadingMode(ShadingMode shading)
{
    qDebug() << "Changed shading to" << shading;
    Q_UNIMPLEMENTED();
}

// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
