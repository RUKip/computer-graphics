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
    glDeleteBuffers(1,&sphereVao);
    glDeleteBuffers(1,&sphereVbo);
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

    //Initialze camera an world settings
    initWorld();

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
    //creates objects below
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

    //create sphere (from model)
    sphereModel = new Model(":/models/cat.obj");
    vertex sphere[sphereModel->getNumTriangles()*3];
    modelToVertices(sphereModel, sphere);
    createObjectBuffers(sphereVao, sphereVbo, sphere, sphereModel->getNumTriangles()*3);

    //create cube
    createObjectBuffers(cubeVao, cubeVbo, cube, 6*6);

    //create pyramid
    createObjectBuffers(pyVao, pyVbo, pyramid, 3*4);
}

//creates VAO and VBO buffers and binds them, assumes always uses a vertex with xyz and rgb
void MainView::createObjectBuffers(GLuint &vao, GLuint &vbo, vertex* model, int numberOfVertices)
{
    //create VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //create VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, numberOfVertices*sizeof(vertex), model, GL_STATIC_DRAW); //set vertices as data of our vbo

    glEnableVertexAttribArray(0);   //Say we send data for postion 0(coordinates) to shaders, (still to define what is data and match in shader)
    glEnableVertexAttribArray(1);   //Say we send data for postion 1(colors) to shaders

    //give the size and location of the different attributes in the VBO
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

//initialize rotation and scale variables and set initial projection
void MainView::initWorld()
{
    initScale = 1.0f;
    worldRotationX = 0;
    worldRotationY = 0;
    worldRotationZ = 0;

    //create projection matrices
    projectionModel.setToIdentity();
    projectionModel.perspective(60, 1, 0.1, 1000);

}

void MainView::modelToVertices(Model* model, vertex* vertices)
{
    QVector<QVector3D> sphereVertices = model->getVertices();
    for(int i=0; i<(model->getNumTriangles()*3); i++){\
        GLfloat randomColorR = ((float) rand() / RAND_MAX);
        GLfloat randomColorG = ((float) rand() / RAND_MAX);
        GLfloat randomColorB = ((float) rand() / RAND_MAX);
        QVector3D singleVertex = sphereVertices[i];
        vertices[i] = {singleVertex.x(), singleVertex.y(), singleVertex.z(), randomColorR, randomColorG, randomColorB};
    }
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

    doModelTransformations(modelTransformCube, {2,0,-6}, 1);
    doModelTransformations(modelTransformPy, {-2,0,-6}, 1);
    doModelTransformations(modelTransformSphere, {0,0,-10}, 1);

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

    //set uniform matrices shaders (sphere)
    glUniformMatrix4fv(modelTransformVert, 1, false, modelTransformSphere.data());

    // Draw here sphere
    glBindVertexArray(sphereVao);
    glDrawArrays(GL_TRIANGLES, 0, sphereModel->getNumTriangles()*3);

    shaderProgram.release();
}

//transformations on the objects in the world
void MainView::doModelTransformations(QMatrix4x4 &modelTransform, QVector3D translation, float scale)
{
    modelTransform.setToIdentity();
    modelTransform.translate(translation.x(), translation.y(), translation.z());
    modelTransform.scale(initScale*scale);
    modelTransform.rotate(worldRotationX, {1,0,0}); //x-axis rotation
    modelTransform.rotate(worldRotationY, {0,1,0}); //y-axis rotation
    modelTransform.rotate(worldRotationZ, {0,0,1}); //z-axis rotation
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
