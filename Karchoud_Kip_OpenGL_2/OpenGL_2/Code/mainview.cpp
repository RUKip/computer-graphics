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
    glDeleteBuffers(1,&texCoord);
    glDeleteBuffers(1,&texData);

    free(model);
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

    //choose shader, default is phong
    shadingMode = ShadingMode::PHONG;
    createPhongShaderProgram();

    //Initialze camera an world settings
    initWorld();

     QVector<vertex> pyramid = givePyramidData();

    //creates objects below
     QVector<vertex> cube = giveCubeData();

    //create sphere (from model)
    model = new Model(":/models/cat.obj");
    vertex sphere[model->getNumTriangles()*3];
    modelToVertices(model, sphere);
    createObjectBuffers(sphereVao, sphereVbo, texCoord, sphere, model->getNumTriangles()*3); //TODO: change so the vertex* is replaced by the a Model
    loadTexture(":/textures/cat_diff.png", texData); //not working correctly yet, crashes program
}

//creates VAO and VBO buffers and binds them, assumes always uses a vertex with xyz and rgb
void MainView::createObjectBuffers(GLuint &vao, GLuint &vbo, GLuint &tex, vertex* modelData, int numberOfVertices)
{
    //create VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //create VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, numberOfVertices*sizeof(vertex), modelData, GL_STATIC_DRAW); //set vertices as data of our vbo

    glEnableVertexAttribArray(0);   //Say we send data for postion 0(coordinates) to shaders, (still to define what is data and match in shader)
    glEnableVertexAttribArray(1);   //Say we send data for postion 1(colors) to shaders

    //give the size and location of the different attributes in the VBO
    glVertexAttribPointer(0,3, GL_FLOAT, false, sizeof(vertex), 0);
    glVertexAttribPointer(1,3, GL_FLOAT, false, sizeof(vertex), (GLvoid*)(3*sizeof(GLfloat)));

    //Bind texture coordinates
    glGenBuffers(1, &tex);
    glBindBuffer(GL_ARRAY_BUFFER, tex);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2, GL_FLOAT, false, 0, 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numberOfVertices*2, model->getTextureCoords().data(), GL_DYNAMIC_DRAW);

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

    //TODO: Now we have some random value for light position here
    positionLight[0] = 2.0f;
    positionLight[1] = 10.0f;
    positionLight[2] = 1.0f;

    colorLight[0] = 1.0f;
    colorLight[1] = 1.0f;
    colorLight[2] = 1.0f;

    materialColor[0] = 1.0f;
    materialColor[1] = 1.0f;
    materialColor[2] = 1.0f;

    materialComponents[0] = 0.2f;
    materialComponents[1] = 1.0f;
    materialComponents[2] = 0.0f;
    materialComponents[3] = 1.0f;
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
        case ShadingMode::PHONG:
            uploadUniformPhong();
            break;
        case ShadingMode::NORMAL:
            uploadUniformNormal();
            break;
        case ShadingMode::GOURAUD:
            uploadUniformGouraud();
            break;
        default:
            qDebug() << "unknown shader setting <" << shadingMode << ">\n";
            uploadUniformPhong();
            break;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texData);
    glUniform1i(texturePtr, 0);

    // Draw
    glBindVertexArray(sphereVao);
    glDrawArrays(GL_TRIANGLES, 0, model->getNumTriangles()*3);

    shaderProgram.release();
}

void MainView::loadTexture(QString file, GLuint textureData){
    QImage image = *new QImage(file);
    QVector<quint8> data = imageToBytes(image);
    glGenTextures(1, &textureData);
    glBindTexture(GL_TEXTURE_2D, textureData); //TODO: GL_texture_2D?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //What param is the best?
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    //glGenerateMipmap(GL TEXTURE 2D) //use if we are gonna use a mipmap
}

void MainView::uploadUniformPhong(){
    //set unifrom matrices normals
    QMatrix3x3 normalTransformation = modelTransformSphere.normalMatrix();

    glUniformMatrix3fv(modelNormalVert_Phong, 1, false, normalTransformation.data());
    glUniform3fv(material_Color_Phong, 1, materialColor);
    glUniform4fv(material_Components_Phong, 1, materialComponents);
    glUniform3fv(light_Color_Phong, 1, colorLight);
    glUniform3fv(light_Position_Phong, 1, positionLight);
    glUniformMatrix4fv(modelProjectionVert_Phong, 1, false, projectionModel.data());
    glUniformMatrix4fv(modelTransformVert_Phong, 1, false, modelTransformSphere.data());
}

void MainView::uploadUniformNormal(){
    QMatrix3x3 normalTransformation = modelTransformSphere.normalMatrix();
    glUniformMatrix3fv(modelNormalVert_Normal, 1, false, normalTransformation.data());
    glUniformMatrix4fv(modelProjectionVert_Normal, 1, false, projectionModel.data());
    glUniformMatrix4fv(modelTransformVert_Normal, 1, false, modelTransformSphere.data());
}

void MainView::uploadUniformGouraud(){
    QMatrix3x3 normalTransformation = modelTransformSphere.normalMatrix();
    glUniform3fv(material_Color_Gouraud, 1, materialColor);
    glUniform4fv(material_Components_Gouraud, 1, materialComponents);
    glUniform3fv(light_Color_Gouraud, 1, colorLight);
    glUniform3fv(light_Position_Gouraud, 1, positionLight);
    glUniformMatrix3fv(modelNormalVert_Gouraud, 1, false, normalTransformation.data());
    glUniformMatrix4fv(modelProjectionVert_Gouraud, 1, false, projectionModel.data());
    glUniformMatrix4fv(modelTransformVert_Gouraud, 1, false, modelTransformSphere.data());
}

void MainView::createNormalShaderProgram()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_normal.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_normal.glsl");
    shaderProgram.link();

    modelTransformVert_Normal = shaderProgram.uniformLocation("modelTransform_Normal");
    modelProjectionVert_Normal = shaderProgram.uniformLocation("projectionTransform_Normal");
    modelNormalVert_Normal = shaderProgram.uniformLocation("normalTransform_Normal");
}

void MainView::createGouraudShaderProgram()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_gouraud.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_gouraud.glsl");
    shaderProgram.link();

    modelTransformVert_Gouraud = shaderProgram.uniformLocation("modelTransform_Gouraud");
    modelProjectionVert_Gouraud = shaderProgram.uniformLocation("projectionTransform_Gouraud");
    modelNormalVert_Gouraud = shaderProgram.uniformLocation("normalTransform_Gouraud");
    material_Color_Gouraud = shaderProgram.uniformLocation("material_Color_Gouraud");
    material_Components_Gouraud = shaderProgram.uniformLocation("material_Components_Gouraud");
    light_Position_Gouraud = shaderProgram.uniformLocation("light_Position_Gouraud");
    light_Color_Gouraud = shaderProgram.uniformLocation("light_Color_Gouraud");
    texturePtr = shaderProgram.uniformLocation("texture");
}

void MainView::createPhongShaderProgram()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_phong.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_phong.glsl");
    shaderProgram.link();

    modelTransformVert_Phong = shaderProgram.uniformLocation("modelTransform_Phong");
    modelProjectionVert_Phong = shaderProgram.uniformLocation("projectionTransform_Phong");
    modelNormalVert_Phong = shaderProgram.uniformLocation("normalTransform_Phong");
    material_Color_Phong = shaderProgram.uniformLocation("material_Color_Phong");
    material_Components_Phong = shaderProgram.uniformLocation("material_Components_Phong");
    light_Position_Phong = shaderProgram.uniformLocation("light_Position_Phong");
    light_Color_Phong = shaderProgram.uniformLocation("light_Color_Phong");
    texturePtr = shaderProgram.uniformLocation("texture");
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
    projectionModel.setToIdentity();
    projectionModel.perspective(60.0f, ((float) newWidth/newHeight), 0.1f, 1000.0f);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
    worldRotationX = rotateX;
    worldRotationY = rotateY;
    worldRotationZ = rotateZ;
    update();
}

void MainView::setScale(int scale)
{
    qDebug() << "Scale changed to " << scale;
    //min 1, max 200
    initScale = ((float) scale/100);
    update();
}

//Color light
void MainView::setRLight(int R)
{
    colorLight[0] = ((float)R/255);
    update();
    qDebug() << "Light changed to (" << colorLight[0] << "," << colorLight[1] << "," << colorLight[2] << ")";
}
void MainView::setGLight(int G)
{
    colorLight[1] = ((float)G/255);
    update();
    qDebug() << "Light changed to (" << colorLight[0] << "," << colorLight[1] << "," << colorLight[2] << ")";
}
void MainView::setBLight(int B)
{
    colorLight[2] = ((float)B/255);
    update();
    qDebug() << "Light changed to (" << colorLight[0] << "," << colorLight[1] << "," << colorLight[2] << ")";
}

//Color material
void MainView::setRMaterial(int R)
{
    materialColor[0] = ((float)R/255);
    update();
    qDebug() << "Material changed to (" << materialColor[0] << "," << materialColor[1] << "," << materialColor[2] << ")";
}
void MainView::setGMaterial(int G)
{
    materialColor[1] = ((float)G/255);
    update();
    qDebug() << "Material changed to (" << materialColor[0] << "," << materialColor[1] << "," << materialColor[2] << ")";
}
void MainView::setBMaterial(int B)
{
    materialColor[2] = ((float)B/255);
    update();
    qDebug() << "Material changed to (" << materialColor[0] << "," << materialColor[1] << "," << materialColor[2] << ")";
}

void MainView::setKAmbient(int A)
{
    materialComponents[0]=((float)A/200);
    update();
    qDebug() << "Material component changed to (" << materialComponents[0] << "," << materialComponents[1] << "," << materialComponents[2] << "," << materialComponents[3] <<")";
}

void MainView::setKDiffuse(int D)
{
    materialComponents[1]=((float)D/200);
    update();
    qDebug() << "Material component changed to (" << materialComponents[0] << "," << materialComponents[1] << "," << materialComponents[2] << "," << materialComponents[3] <<")";
}

void MainView::setKSpecular(int S)
{
    materialComponents[2]=((float)S/200);
    update();
    qDebug() << "Material component changed to (" << materialComponents[0] << "," << materialComponents[1] << "," << materialComponents[2] << "," << materialComponents[3] <<")";
}

void MainView::setKP(int P)
{
    materialComponents[3] = P;
    update();
    qDebug() << "Material component changed to (" << materialComponents[0] << "," << materialComponents[1] << "," << materialComponents[2] << "," << materialComponents[3] <<")";
}


void MainView::setShadingMode(ShadingMode shading)
{
    shadingMode = shading;
    shaderProgram.removeAllShaders();
    shaderProgram.release();
    //Selecting shader
    switch (shadingMode) {
    case ShadingMode::PHONG:
        createPhongShaderProgram();
        break;
    case ShadingMode::NORMAL:
        createNormalShaderProgram();
        break;
    case ShadingMode::GOURAUD:
        createGouraudShaderProgram();
        break;
    default:
        qDebug() << "unknown shader setting <" << shadingMode << ">\n";
        createPhongShaderProgram();
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
