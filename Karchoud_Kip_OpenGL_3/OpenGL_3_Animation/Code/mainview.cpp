#include "mainview.h"
#include "math.h"

#include <QDateTime>
#define M_PI 3.141593

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
    glDeleteBuffers(1,&model1Vao);
    glDeleteBuffers(1,&model1Vbo);
    glDeleteBuffers(1,&tex1Coord);
    glDeleteBuffers(1,&tex1Data);
    glDeleteBuffers(1,&model2Vao);
    glDeleteBuffers(1,&model2Vbo);
    glDeleteBuffers(1,&tex2Coord);
    glDeleteBuffers(1,&tex2Data);
    glDeleteBuffers(1,&model3Vao);
    glDeleteBuffers(1,&model3Vbo);
    glDeleteBuffers(1,&tex3Coord);
    glDeleteBuffers(1,&tex3Data);
    free(model1);
    free(model2);
    free(model3);
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

    //choose shader, default is phong
    shadingMode = ShadingMode::PHONG;
    createPhongShaderProgram();

    //Initialze camera an world settings
    initWorld();

    createModelBuffersAndTextures();

    timer.start(1000.0 / 60.0);
}

//creates VAO and VBO buffers and binds them, assumes always uses a vertex with xyz and rgb
void MainView::createObjectBuffers(GLuint &vao, GLuint &vbo, GLuint &tex, Model* &model)
{
    model->unitize();
    vertex vertexData[model->getNumTriangles()*3];
    modelToVertices(model, vertexData);
    int numberOfVertices = model->getNumTriangles()*3;

    //create VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //create VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, numberOfVertices*sizeof(vertex), vertexData, GL_STATIC_DRAW); //set vertices as data of our vbo

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

    //set transformations each object
    transformationsObj1 = {0,0,-3.5,0,0,0};       //car
    transformationsObj2 = {0,0,-2.5,0,0,0};       //rocket
    transformationsObj3 = {0,0,-10,0,0,0};         //earth
    transformationsObj4 = {0,0,-5.5,0,0,0};         //earth.moon
    transformationsObj5 = {0,0,-7,0,0,0};
}


void MainView::createModelBuffersAndTextures(){
    //Generate model buffers
    //create car (from model)
    model1 = new Model(":/models/car.obj");
    createObjectBuffers(model1Vao, model1Vbo, tex1Coord, model1);

    //create rocket (from model)
    model2 = new Model(":/models/rocket.obj");
    createObjectBuffers(model2Vao, model2Vbo, tex2Coord, model2);

    //create planets (from model)
    model3 = new Model(":/models/sphere.obj");
    createObjectBuffers(model3Vao, model3Vbo, tex3Coord, model3);

    //Generate textures
    glGenTextures(1, &tex1Data);
    loadTexture(":/textures/car.png", tex1Data);

    glGenTextures(1, &tex2Data);
    loadTexture(":/textures/rocket.png", tex2Data);

    glGenTextures(1, &tex3Data);
    loadTexture(":/textures/earth.png", tex3Data);

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

    if(shadingMode != ShadingMode::CELL) shaderProgram.bind();

    cout << transformationsObj4.posX << "\n"; //test

    //Do transformations for each object
    doModelTransformations(obj1Transform, transformationsObj1, 0.4); //TODO: make world transform
    doModelTransformations(obj2Transform, transformationsObj2, 0.8);
    doModelTransformations(obj3Transform, transformationsObj3, 1.0);
    doModelTransformations(obj4Transform, transformationsObj4, 0.5);
    doModelTransformations(obj5Transform, transformationsObj5, 0.7);

    addRotationModel(transformationsObj1,0,0.8,0);    //car
    addRotationModel(transformationsObj2,0,0.9,0);  //rocket
    addRotationModel(transformationsObj3,0,1,0);    //earth
    addRotationModel(transformationsObj4,0,1.1,0);    //earth.moon
    addRotationModel(transformationsObj5,0,0.7,0);    //car 2

    moveObjects(transformationsObj1, 0.2, 0.0, 0.0, 1);
    moveObjects(transformationsObj2, 0.2, 0.0, 0.0, 1);
    moveObjects(transformationsObj3, 0.2, 0.0, 0.0, 1);
    moveObjects(transformationsObj4, 0.2, 0.0, 0.0, 1);
    moveObjects(transformationsObj5, 0.2, 0.0, 0.0, 1);


    //Choose shading mode
    switch(shadingMode){
        case ShadingMode::PHONG:
            uploadUniformPhong(obj1Transform);
            break;
        case ShadingMode::NORMAL:
            uploadUniformNormal();
            break;
        case ShadingMode::GOURAUD:
            uploadUniformGouraud();
            break;
        case ShadingMode::CELL:     //TODO: needs to be cleaned up and done properly, not only for one object
            {
                float originalScale = 4;
                setShadingMode(ShadingMode::SILHOUETTE);
                shaderProgram.bind();
                glCullFace(GL_FRONT);
                doModelTransformations(obj1Transform, transformationsObj1, originalScale + 0.1f); //should be a little more then normal one
                uploadUniformSilhouette();
                glBindVertexArray(model1Vao);
                glDrawArrays(GL_TRIANGLES, 0, model1->getNumTriangles()*3);
                shaderProgram.release();

                setShadingMode(ShadingMode::CELL);
                shaderProgram.bind();
                glCullFace(GL_BACK);
                doModelTransformations(obj1Transform, transformationsObj1, originalScale);
                uploadUniformCell();
                break;
            }
        default:
            qDebug() << "unknown shader setting <" << shadingMode << ">\n";
            uploadUniformPhong(obj1Transform);
            break;
    }

    // Draw object 1
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1Data);
    glUniform1i(texturePtr, 0);

    glBindVertexArray(model1Vao);
    glDrawArrays(GL_TRIANGLES, 0, model1->getNumTriangles()*3);


    // Draw object 2
    uploadUniformPhong(obj2Transform);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex2Data);
    glUniform1i(texturePtr, 0);

    glBindVertexArray(model2Vao);
    glDrawArrays(GL_TRIANGLES, 0, model2->getNumTriangles()*3);

    // Draw object 3
    uploadUniformPhong(obj3Transform);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex3Data);
    glUniform1i(texturePtr, 0);

    glBindVertexArray(model3Vao);
    glDrawArrays(GL_TRIANGLES, 0, model3->getNumTriangles()*3);

    //draw object 4
    uploadUniformPhong(obj4Transform);
    glDrawArrays(GL_TRIANGLES, 0, model3->getNumTriangles()*3);

    //draw object 5
    uploadUniformPhong(obj5Transform);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1Data);
    glUniform1i(texturePtr, 0);

    glBindVertexArray(model1Vao);
    glDrawArrays(GL_TRIANGLES, 0, model1->getNumTriangles()*3);

    shaderProgram.release();
}

void MainView::loadTexture(QString file, GLuint textureData){
    QImage image = *new QImage(file);
    QVector<quint8> data = imageToBytes(image);
    glBindTexture(GL_TEXTURE_2D, textureData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    //glGenerateMipmap(GL TEXTURE 2D) //use if we are gonna use a mipmap
}

void MainView::uploadUniformPhong(QMatrix4x4 objTransform){
    //set unifrom matrices normals
    QMatrix3x3 normalTransformation = objTransform.normalMatrix();

    glUniformMatrix3fv(modelNormalVert_Phong, 1, false, normalTransformation.data());
    glUniform3fv(material_Color_Phong, 1, materialColor);
    glUniform4fv(material_Components_Phong, 1, materialComponents);
    glUniform3fv(light_Color_Phong, 1, colorLight);
    glUniform3fv(light_Position_Phong, 1, positionLight);
    glUniformMatrix4fv(modelProjectionVert_Phong, 1, false, projectionModel.data());
    glUniformMatrix4fv(modelTransformVert_Phong, 1, false, objTransform.data());
}

void MainView::uploadUniformNormal(){
    QMatrix3x3 normalTransformation = obj1Transform.normalMatrix();
    glUniformMatrix3fv(modelNormalVert_Normal, 1, false, normalTransformation.data());
    glUniformMatrix4fv(modelProjectionVert_Normal, 1, false, projectionModel.data());
    glUniformMatrix4fv(modelTransformVert_Normal, 1, false, obj1Transform.data());
}

void MainView::uploadUniformGouraud(){
    QMatrix3x3 normalTransformation = obj1Transform.normalMatrix();
    glUniform3fv(material_Color_Gouraud, 1, materialColor);
    glUniform4fv(material_Components_Gouraud, 1, materialComponents);
    glUniform3fv(light_Color_Gouraud, 1, colorLight);
    glUniform3fv(light_Position_Gouraud, 1, positionLight);
    glUniformMatrix3fv(modelNormalVert_Gouraud, 1, false, normalTransformation.data());
    glUniformMatrix4fv(modelProjectionVert_Gouraud, 1, false, projectionModel.data());
    glUniformMatrix4fv(modelTransformVert_Gouraud, 1, false, obj1Transform.data());
}

void MainView::uploadUniformCell(){
    QMatrix3x3 normalTransformation = obj1Transform.normalMatrix();
    glUniform3fv(material_Color_Cell, 1, materialColor);
    glUniform4fv(material_Components_Cell, 1, materialComponents);
    glUniform3fv(light_Color_Cell, 1, colorLight);
    glUniform3fv(light_Position_Cell, 1, positionLight);
    glUniformMatrix3fv(modelNormalVert_Cell, 1, false, normalTransformation.data());
    glUniformMatrix4fv(modelProjectionVert_Cell, 1, false, projectionModel.data());
    glUniformMatrix4fv(modelTransformVert_Cell, 1, false, obj1Transform.data());
}

void MainView::uploadUniformSilhouette(){
    float silhouetteColor[3] = {0.0f,0.0f,0.0f};
    glUniform3fv(material_Color_Silhouette, 1, silhouetteColor);
    glUniformMatrix4fv(modelProjectionVert_Silhouette, 1, false, projectionModel.data());
    glUniformMatrix4fv(modelTransformVert_Silhouette, 1, false, obj1Transform.data());
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

void MainView::createCellShaderProgram()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_cell.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_cell.glsl");
    shaderProgram.link();

    modelTransformVert_Cell = shaderProgram.uniformLocation("modelTransform_Cell");
    modelProjectionVert_Cell = shaderProgram.uniformLocation("projectionTransform_Cell");
    modelNormalVert_Cell = shaderProgram.uniformLocation("normalTransform_Cell");
    material_Color_Cell = shaderProgram.uniformLocation("material_Color_Cell");
    material_Components_Cell = shaderProgram.uniformLocation("material_Components_Cell");
    light_Position_Cell = shaderProgram.uniformLocation("light_Position_Cell");
    light_Color_Cell = shaderProgram.uniformLocation("light_Color_Cell");
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

void MainView::createSilhouetteShaderProgram()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_silhouette.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_silhouette.glsl");
    shaderProgram.link();

    modelTransformVert_Silhouette = shaderProgram.uniformLocation("modelTransform_Silhouette");
    modelProjectionVert_Silhouette = shaderProgram.uniformLocation("projectionTransform_Silhouette");
    material_Color_Silhouette = shaderProgram.uniformLocation("material_Color_Silhouette");
}

//transformations on the objects in the world
void MainView::doModelTransformations(QMatrix4x4 &modelTransform, transformation modelTransformations, float scale)
{
    modelTransform.setToIdentity();
    modelTransform.translate(modelTransformations.posX, modelTransformations.posY, modelTransformations.posZ);
    modelTransform.scale(initScale*scale);
    modelTransform.rotate(modelTransformations.rotX, {1,0,0}); //x-axis rotation
    modelTransform.rotate(modelTransformations.rotY, {0,1,0}); //y-axis rotation
    modelTransform.rotate(modelTransformations.rotZ, {0,0,1}); //z-axis rotation
}

void MainView::addRotationModel(transformation &transformations,float rotationX, float rotationY, float rotationZ){
    transformations.rotX = std::fmod(transformations.rotX + rotationX,360);
    transformations.rotY = std::fmod(transformations.rotY + rotationY,360);
    transformations.rotZ = std::fmod(transformations.rotZ + rotationZ,360);
}

void MainView::moveObjects(transformation &modelTransformations, float moveX, float moveY, float moveZ, int scaleFactor){
    if(moveX > 0.001)
        modelTransformations.posX = scaleFactor*sin(((float)modelTransformations.posX/scaleFactor)*moveX*M_PI);
    if(moveY > 0.001)
        modelTransformations.posY = scaleFactor*sin((modelTransformations.posY/scaleFactor)*moveY*M_PI);
    if(moveZ > 0.001)
        modelTransformations.posZ = scaleFactor*sin((modelTransformations.posZ/scaleFactor)*moveZ*M_PI);
    //obj1Transform.translate(modelTransformations.posX, modelTransformations.posY, modelTransformations.posZ);
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
    case ShadingMode::CELL:
        createCellShaderProgram();
        break;
    case ShadingMode::SILHOUETTE:
        createSilhouetteShaderProgram();
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
