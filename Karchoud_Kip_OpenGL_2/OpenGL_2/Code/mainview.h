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

    GLint modelTransformVert_Normal;
    GLint modelProjectionVert_Normal;
    GLint modelNormalVert_Normal;

    GLint modelTransformVert_Phong;
    GLint modelProjectionVert_Phong;
    GLint modelNormalVert_Phong;

    GLint modelTransformVert_Gouraud;
    GLint modelProjectionVert_Gouraud;
    GLint modelNormalVert_Gouraud;

    Model* sphereModel;

    float initScale;
    float worldRotationX;
    float worldRotationY;
    float worldRotationZ;

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);

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
};

#endif // MAINVIEW_H
