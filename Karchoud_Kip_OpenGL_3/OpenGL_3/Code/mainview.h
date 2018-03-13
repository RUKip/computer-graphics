#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <memory>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaderProgram;

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD, CELL, SILHOUETTE
    };

    MainView(QWidget *parent = 0);
    ~MainView();
    //TODO: move structs to there own files
    struct vertex{
        GLfloat posX;
        GLfloat posY;
        GLfloat posZ;
        GLfloat colorR;
        GLfloat colorG;
        GLfloat colorB;
    };

    struct transformation{
        GLfloat posX;
        GLfloat posY;
        GLfloat posZ;
        GLfloat rotX;
        GLfloat rotY;
        GLfloat rotZ;
    };

    GLint texturePtr; //Texture ptr to uniform sampler2D texture;


    ShadingMode shadingMode;

    QMatrix4x4 projectionModel;

    float materialColor[3];
    float materialComponents[4];
    float colorLight[3];
    float positionLight[3];

    //All normal shading specific uniforms
    GLint modelTransformVert_Normal;
    GLint modelProjectionVert_Normal;
    GLint modelNormalVert_Normal;

    //All phong shading specific uniforms
    GLint modelTransformVert_Phong;
    GLint modelProjectionVert_Phong;
    GLint modelNormalVert_Phong;
    GLint light_Position_Phong;
    GLint light_Color_Phong;
    GLint material_Color_Phong;
    GLint material_Components_Phong;

    //All gourad shading specific uniforms
    GLint modelTransformVert_Gouraud;
    GLint modelProjectionVert_Gouraud;
    GLint modelNormalVert_Gouraud;
    GLint light_Position_Gouraud;
    GLint light_Color_Gouraud;
    GLint material_Color_Gouraud;
    GLint material_Components_Gouraud;

    //All cell shading specific uniforms
    GLint modelTransformVert_Cell;
    GLint modelProjectionVert_Cell;
    GLint modelNormalVert_Cell;
    GLint light_Position_Cell;
    GLint light_Color_Cell;
    GLint material_Color_Cell;
    GLint material_Components_Cell;

    //All silhouette shading specific uniforms (used in cell shading)
    GLint modelTransformVert_Silhouette;
    GLint modelProjectionVert_Silhouette;
    GLint material_Color_Silhouette;

    //World stuff
    float initScale;
    float worldRotationX;
    float worldRotationY;
    float worldRotationZ;

    //All transformations Vectors and model specific values
    //object 1
    QMatrix4x4 obj1Transform;
    transformation transformationsObj1;
    Model* model1;
    //GLuints
    GLuint model1Vao;
    GLuint model1Vbo;

    GLuint tex1Coord;    //Textures coordinates buffer
    GLuint tex1Data;     //Texture data

    //object 2
    QMatrix4x4 obj2Transform;
    transformation transformationsObj2;
    Model* model2;
    //GLuints
    GLuint model2Vao;
    GLuint model2Vbo;
    GLuint tex2Coord;    //Textures coordinates buffer
    GLuint tex2Data;     //Texture data

    //object 3
    QMatrix4x4 obj3Transform;
    transformation transformationsObj3;
    Model* model3;
    //GLuints
    GLuint model3Vao;
    GLuint model3Vbo;
    GLuint tex3Coord;    //Textures coordinates buffer
    GLuint tex3Data;     //Texture data

    //object 4
    QMatrix4x4 obj4Transform;
    transformation transformationsObj4;

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);
    void setRLight(int R);
    void setGLight(int G);
    void setBLight(int B);
    void setRMaterial(int R);
    void setGMaterial(int G);
    void setBMaterial(int B);
    void setKAmbient(int A);
    void setKDiffuse(int D);
    void setKSpecular(int S);
    void setKP(int P);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

private:
    void createNormalShaderProgram();
    void createGouraudShaderProgram();
    void createPhongShaderProgram();
    void createCellShaderProgram();
    void createSilhouetteShaderProgram();
    void initWorld();
    void doModelTransformations(QMatrix4x4 &obj1Transform, transformation translation, float scale);
    void modelToVertices(Model* model1, vertex* vertices);
    void createObjectBuffers(GLuint &vao, GLuint &vbo, GLuint &tex, Model* &model);
    void uploadUniformPhong();
    void uploadUniformNormal();
    void uploadUniformGouraud();
    void uploadUniformCell();
    void uploadUniformSilhouette();
    void loadTexture(QString file, GLuint texturepointer);
    void addRotationModel(transformation &transformations, float rotationX, float rotationY, float rotationZ);
    QVector<quint8> imageToBytes(QImage image);
    void createModelBuffersAndTextures();
};

#endif // MAINVIEW_H
