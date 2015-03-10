#include "MD2Viewer.h"
#include "MD2Loader/MD2Loader.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

#include <iostream>
using namespace std;

MD2Viewer::MD2Viewer(){
    m_program = 0;
    m_frame = 0;
}

/*
GLuint MD2Viewer::loadShader(GLenum type, const char *source){
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
}*/

void MD2Viewer::initialize(){
    cout << "MD2Viewer::initialize() gets called." << endl;
    m_program = new QOpenGLShaderProgram(this);
    //The following relative path names are so hideous b/c I don't know how to copy
    //my shaders into the .app build. Will fix this if I have time left.
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "../../../../A2/shaders/interpColour.vs");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "../../../../A2/shaders/interpColour.fs");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");

    //Load our MD2 file
    //myMD2Loader.LoadModel("../../../../A2/3D_MD2_Models/invader/tris.md2");
}

void MD2Viewer::render(){
    cout << "MD2Viewer::render() gets called." << endl;
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    /*
    cout << "MD2 file statistics:" << endl;
    cout << "   - myMD2Loader.num_frames = " << myMD2Loader.num_frames << endl;
    cout << "   - myMD2Loader.num_xyz = " << myMD2Loader.num_xyz << endl;
    cout << "   - myMD2Loader.num_tris = " << myMD2Loader.num_tris << endl;
    */

    //Code to create and display a tri-coloured triangle
    /*
    GLfloat vertices[] = {
        0.0f, 0.707f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    */

    m_program->release();

    m_frame++;
}
