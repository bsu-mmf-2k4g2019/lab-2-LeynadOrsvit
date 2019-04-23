#include "glwidget.h"

#include <QTime>
#include <QImage>
#include <iostream>

static const char *vertexShaderSource_quads =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aCol;\n"
    "out vec3 color;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transform * vec4(aPos, 1.0);\n"
    "    color = aCol;\n"
    "}\n\0";

static const char *fragmentShaderSource_quads =
    "#version 330 core\n"
    "in vec3 color;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(color, 1.0f);\n"
    "}\n\0";

static const char *vertexShaderSource_triangle =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aCol;\n"
    "out vec3 color;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transform * vec4(aPos, 1.0);\n"
    "    color = aCol;\n"
    "}\n\0";

static const char *fragmentShaderSource_triangle =
    "#version 330 core\n"
    "in vec3 color;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(color, 1.0f);\n"
    "}\n\0";

static const char *vertexShaderSource_star =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aCol;\n"
    "out vec3 color;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transform * vec4(aPos, 1.0);\n"
    "    color = aCol;\n"
    "}\n\0";

static const char *fragmentShaderSource_star =
    "#version 330 core\n"
    "in vec3 color;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(color, 1.0f);\n"
    "}\n\0";

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , camera_up(0.0f, 1.0f, 0.0f)
    , camera_front(0.0f, 0.0f, -1.0f)
{
}

GLWidget::~GLWidget()
{
}

void GLWidget::timerEvent(QTimerEvent *event)
{
    update();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    float cameraSpeed = 0.30f; // adjust accordingly
    if (event->key() == Qt::Key_W)
        camera_pos += cameraSpeed * camera_front;
    if (event->key() == Qt::Key_S)
        camera_pos -= cameraSpeed * camera_front;
    if (event->key() == Qt::Key_A)
        camera_pos -= QVector3D::crossProduct(camera_front, camera_up).normalized() * cameraSpeed;
    if (event->key() == Qt::Key_D)
        camera_pos += QVector3D::crossProduct(camera_front, camera_up).normalized() * cameraSpeed;
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    // Create VAO & VBO, bind it to current GL_ARRAY_BUFFER and load vertices into it
    GLfloat vertices_quads[] = {
        // Vertices        // Colors
        /*0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.0f, 0.5f, 1.0f, 0.0f, 0.0f,

        0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f,  0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.0f, 0.5f, 1.0f, 0.0f, 0.0f,

        0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f,*/

        0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

        0.0f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.0f, 0.5f, 1.0f, 0.0f, 0.0f,

        0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

    };

    GLfloat vertices_triangle[] = {

        0.0f, 0.0f,-0.5f,  1.0f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.0f,  0.0f, 1.0f, 1.0f,

        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f,-0.5f,  0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f,

        -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,-0.5f, 1.0f, 0.0f, 0.5f,
    };

    GLfloat vertices_star[] = {
        -0.5f, 0.0f,0.0f,  1.0f, 0.5f, 0.0f,
        -0.15f, 0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.0f, 0.2f,  0.0f, 1.0f, 0.5f,

        -0.15f, 0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.0f,  1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        -0.5f, 0.0f,0.0f,  1.0f, 0.5f, 0.0f,
        -0.15f, 0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.0f,-0.2f,  0.0f, 1.0f, 0.5f,

        -0.15f, 0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.0f,  1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,-0.2f,  0.0f, 1.0f, 0.5f,

        0.0f, 0.5f, 0.0f,  1.0f, 0.5f, 0.0f,
        0.15f, 0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        0.15f, 0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        0.0f, 0.5f, 0.0f,  1.0f, 0.5f, 0.0f,
        0.15f, 0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.0f,-0.2f,  0.0f, 1.0f, 0.5f,

        0.15f, 0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,-0.2f,  0.0f, 1.0f, 0.5f,

        0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f,
        0.15f, -0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        0.15f, -0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f,
        0.15f, -0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        0.15f, -0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        0.0f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,
        -0.15f, -0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        -0.15f, -0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        -0.5f, 0.0f, 0.0f,  1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,0.2f,  0.0f, 1.0f, 0.5f,

        0.0f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,
        -0.15f, -0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        0.0f, 0.0f,-0.2f,  0.0f, 1.0f, 0.5f,

        -0.15f, -0.15f,0.0f,  0.0f, 0.5f, 0.5f,
        -0.5f, 0.0f, 0.0f,  1.0f, 0.5f, 0.0f,
        0.0f, 0.0f,-0.2f,  0.0f, 1.0f, 0.5f,
    };

     GLuint indices_quads[] = {
         0, 1, 2, 3,
         4, 5, 6, 7,
         8, 9, 10, 11,
         12, 13, 14, 15,
         16, 17, 18, 19,
         20, 21, 22, 23
     };

     GLuint indices_triangle[] = {
         0, 1, 2,
         3, 4, 5,
         6, 7, 8,
         9, 10, 11,
     };

     GLuint indices_star[] = {
         0, 1, 2,
         3, 4, 5,
         6, 7, 8,
         9, 10, 11,
         12, 13, 14,
         15, 16, 17,
         18, 19, 20,
         21, 22, 23,
         24, 25, 26,
         27, 28, 29,
         30, 31, 32,
         33, 34, 35,
         36, 37, 38,
         39, 40, 41,
         42, 43, 44,
         45, 46, 47,
     };

    GLuint VBO;
    GLuint EBO;

    // Create VAO id
    glGenVertexArrays(1, &m_vao_quads_id);
    glGenVertexArrays(1, &m_vao_triangle_id);
    glGenVertexArrays(1, &m_vao_star_id);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(m_vao_quads_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_quads), vertices_quads, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_quads), indices_quads, GL_STATIC_DRAW);
    // Configure how OpenGL will interpret the VBO data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
   // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    glBindVertexArray(0); // Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind current VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind current EBO


    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(m_vao_triangle_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_triangle), indices_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    glBindVertexArray(0); // Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind current VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind current EBO

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(m_vao_star_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_star), vertices_star, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_star), indices_star, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    glBindVertexArray(0); // Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind current VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind current EBO*/

    // Prepare shader programm
    m_prog_quads.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource_quads);
    m_prog_quads.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource_quads);
    m_prog_quads.link();

    m_prog_triangle.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource_triangle);
    m_prog_triangle.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource_triangle);
    m_prog_triangle.link();

    m_prog_star.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource_star);
    m_prog_star.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource_star);
    m_prog_star.link();


    // Obtain uniform ids
    m_transform_uni_id = m_prog_triangle.uniformLocation("transform");
    //m_triangle_color_id = m_prog_triangle.uniformLocation("color");
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    QTime cur_t = QTime::currentTime();
    double angle = (cur_t.second() * 1000 + cur_t.msec()) * 360.0 * 15 / 60000.0;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 trans;
    QMatrix4x4 view;
    trans.rotate(angle, QVector3D(0.1f, 0.3f, 0.5f));
    view.lookAt(camera_pos, camera_pos + camera_front, camera_up);

    glBindVertexArray(m_vao_quads_id);
    m_prog_quads.bind();
    trans.translate(QVector3D( 0.7f,  0.0f, 0.0f));
    m_prog_quads.setUniformValue("transform", trans);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);


    glBindVertexArray(m_vao_triangle_id);
    m_prog_triangle.bind();
    trans.translate(QVector3D( 0.0f,  0.7f, 0.0f));
    m_prog_triangle.setUniformValue("transform", trans);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glBindVertexArray(m_vao_star_id);
    m_prog_star.bind();
    trans.translate(QVector3D( 0.0f,  0.0f, 0.7f));
    m_prog_star.setUniformValue("transform", trans);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);
}
