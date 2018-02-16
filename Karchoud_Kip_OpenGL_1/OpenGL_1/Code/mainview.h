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
    GLuint cubeVbo;
    GLuint pyVbo;
    GLuint cubeVao;
    GLuint pyVao;
    GLuint sphereVao;
    GLuint sphereVbo;

    QMatrix4x4 modelTransformPy;
    QMatrix4x4 modelTransformCube;
    QMatrix4x4 modelTransformSphere;
    QMatrix4x4 projectionModel;

    GLint modelTransformVert;
    GLint modelProjectionVert;

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
    void createShaderProgram();
    void initWorld();
    void doModelTransformations();
    void modelToVertices(Model* model, vertex* vertices);
    void createObjectBuffers(GLuint &vao, GLuint &vbo, vertex* model, int numberOfVertices);
};

#endif // MAINVIEW_H
