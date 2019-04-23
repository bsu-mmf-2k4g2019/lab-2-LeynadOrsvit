#ifndef WIDGET_H
#define WIDGET_H

#include <QtOpenGL>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget() override;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QOpenGLShaderProgram    m_prog_quads;
    QOpenGLShaderProgram    m_prog_triangle;
    QOpenGLShaderProgram    m_prog_star;
    GLuint                  m_vao_triangle_id;
    GLuint                  m_vao_quads_id;
    GLuint                  m_vao_star_id;
    GLint                   m_transform_uni_id;
    GLint                   m_triangle_color_id;
    QVector3D camera_pos;
    QVector3D camera_up;
    QVector3D camera_front;

};

#endif // WIDGET_H
