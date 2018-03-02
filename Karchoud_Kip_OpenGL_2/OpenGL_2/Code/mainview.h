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
        PHONG = 0, NORMAL, GOURAUD
    };

    MainView(QWidget *parent = 0);
    ~MainView();
    struct vertex{
        GLfloat posX;
        GLfloat posY;
        GLfloat posZ;
        GLfloat colorR;
        GLfloat colorG;
        GLfloat colorB;
    };
    GLuint sphereVao;
    GLuint sphereVbo;

    ShadingMode shadingMode;

    QMatrix4x4 modelTransformSphere; //TODO: add to a struct?
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

    Model* sphereModel;


    //Texture mapping
    GLuint texture;


    float initScale;
    float worldRotationX;
    float worldRotationY;
    float worldRotationZ;

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
    void initWorld();
    void doModelTransformations(QMatrix4x4 &modelTransform, QVector3D translation, float scale);
    void modelToVertices(Model* model, vertex* vertices);
    void createObjectBuffers(GLuint &vao, GLuint &vbo, vertex* model, int numberOfVertices);
    QVector<vertex> giveCubeData();
    QVector<vertex> givePyramidData();
    void uploadUniformPhong();
    void uploadUniformNormal();
    void uploadUniformGouraud();
    //QVector<quint8> imagesToBytes(QImage image);
};

#endif // MAINVIEW_H
