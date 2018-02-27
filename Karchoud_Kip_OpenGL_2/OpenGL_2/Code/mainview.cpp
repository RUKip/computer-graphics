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
    glDeleteBuffers(1,&sphereVao);
    glDeleteBuffers(1,&sphereVbo);
    free(sphereModel);
    qDebug() << "MainView destructor";
}

QVector<MainView::vertex> MainView::givePyramidData(){
    QVector<vertex> pyramid = {
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
    return pyramid;
}

QVector<MainView::vertex> MainView::giveCubeData(){
     QVector<vertex> cube = {
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
    return cube;
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

    //Selecting shader
    switch (shadingMode) {
    case 0:
        createPhongShaderProgram();
        break;
    case 1:
        createNormalShaderProgram();
        break;
    case 2:
        createGouraudShaderProgram();
        break;
    default:
        qDebug() << "unknown shader setting <" << shadingMode << ">\n";
        break;
    }

    //Initialze camera an world settings
    initWorld();

     QVector<vertex> pyramid = givePyramidData();

    //creates objects below
     QVector<vertex> cube = giveCubeData();

    //create sphere (from model)
    sphereModel = new Model(":/models/cat.obj");
    vertex sphere[sphereModel->getNumTriangles()*3];
    modelToVertices(sphereModel, sphere);
    createObjectBuffers(sphereVao, sphereVbo, sphere, sphereModel->getNumTriangles()*3);
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

void MainView::createNormalShaderProgram()
{
    // Create shader program
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_normal.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_normal.glsl");
    shaderProgram.link();

    modelTransformVert_Normal = shaderProgram.uniformLocation("modelTransform");
    modelProjectionVert_Normal = shaderProgram.uniformLocation("projectionTransform");
    modelNormalVert_Normal = shaderProgram.uniformLocation("normalTransform");
}

void MainView::createGouraudShaderProgram()
{
    // Create shader program
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_gouraud.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_gouraud.glsl");
    shaderProgram.link();

    modelTransformVert_Gouraud = shaderProgram.uniformLocation("modelTransform_Gouraud");
    modelProjectionVert_Gouraud = shaderProgram.uniformLocation("projectionTransform_Gouraud");
    modelNormalVert_Gouraud = shaderProgram.uniformLocation("normalTransform_Gouraud");
}

void MainView::createPhongShaderProgram()
{
    // Create shader program
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_phong.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_phong.glsl");
    shaderProgram.link();

    modelTransformVert_Phong = shaderProgram.uniformLocation("modelTransform_Phong");
    modelProjectionVert_Phong = shaderProgram.uniformLocation("projectionTransform_Phong");
    modelNormalVert_Phong = shaderProgram.uniformLocation("normalTransform_Phong");
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
    QVector<QVector3D> modelVertices = model->getVertices();
    QVector<QVector3D> modelNormals = model->getNormals();
    for(int i=0; i<(model->getNumTriangles()*3); i++){
        QVector3D singleVertex = modelVertices[i];
        QVector3D normals = modelNormals[i];
        vertices[i] = {singleVertex.x(), singleVertex.y(), singleVertex.z(), normals.x(), normals.y(), normals.z()};
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

    doModelTransformations(modelTransformSphere, {0,0,-10}, 4);



    switch(shadingMode){
        case 0:
            uploadUniformPhong();
            break;
        case 1:
            uploadUniformNormal();
            break;
        case 2:
            uploadUniformGouraud();
            break;
        default:
            qDebug() << "unknown shader setting <" << shadingMode << ">\n";
            break;
    }

    // Draw here sphere
    glBindVertexArray(sphereVao);
    glDrawArrays(GL_TRIANGLES, 0, sphereModel->getNumTriangles()*3);

    shaderProgram.release();
}

void MainView::uploadUniformPhong(){
    QMatrix3x3 normalTransformation = modelTransformSphere.normalMatrix();
    glUniformMatrix3fv(modelNormalVert_Phong, 1, false, normalTransformation.data());

    //set uniform matrices projection
    glUniformMatrix4fv(modelProjectionVert_Phong, 1, false, projectionModel.data());

    //set uniform matrices shaders
    glUniformMatrix4fv(modelTransformVert_Phong, 1, false, modelTransformSphere.data());
}

void MainView::uploadUniformNormal(){
    QMatrix3x3 normalTransformation = modelTransformSphere.normalMatrix();
    glUniformMatrix3fv(modelNormalVert_Normal, 1, false, normalTransformation.data());

    //set uniform matrices projection
    glUniformMatrix4fv(modelProjectionVert_Normal, 1, false, projectionModel.data());

    //set uniform matrices shaders
    glUniformMatrix4fv(modelTransformVert_Normal, 1, false, modelTransformSphere.data());
}

void MainView::uploadUniformGouraud(){
    QMatrix3x3 normalTransformation = modelTransformSphere.normalMatrix();
    glUniformMatrix3fv(modelNormalVert_Gouraud, 1, false, normalTransformation.data());

    //set uniform matrices projection
    glUniformMatrix4fv(modelProjectionVert_Gouraud, 1, false, projectionModel.data());

    //set uniform matrices shaders
    glUniformMatrix4fv(modelTransformVert_Gouraud, 1, false, modelTransformSphere.data());
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
    projectionModel.perspective(60.0f, ((float) newWidth/newHeight), 0.1f, 1000.0f);
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
    shadingMode = shading;
    shaderProgram.removeAllShaders();
    shaderProgram.release();
    //Selecting shader
    switch (shadingMode) {
    case 0:
        createPhongShaderProgram();
        break;
    case 1:
        createNormalShaderProgram();
        break;
    case 2:
        createGouraudShaderProgram();
        break;
    default:
        qDebug() << "unknown shader setting <" << shadingMode << ">\n";
        break;
    }

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
