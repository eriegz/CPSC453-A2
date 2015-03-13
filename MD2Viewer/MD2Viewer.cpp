#include "MD2Viewer.h"
//#include "MD2Model/MD2Model.h"
//#include "ShaderLoader/ShaderLoader.h"

#include <iostream>
using namespace std;

MD2Viewer::MD2Viewer(){
    cout << "MD2Viewer::MD2Viewer() gets called." << endl;
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

static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";

void MD2Viewer::initialize(){
    cout << "MD2Viewer::initialize() gets called." << endl;
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

    //The following relative path names are so hideous b/c I don't know how to copy
    //my shaders into the .app build. Will fix this if I have time left.
    //m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "../../../../A2/shaders/interpColour.vs");
    //m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "../../../../A2/shaders/Phong.vs.glsl");
    //m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "../../../../A2/shaders/interpColour.fs");
    //m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "../../../../A2/shaders/Phong.fs.glsl");

    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");

    //Load our shaders
    //ShaderLoader();

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
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    /*
    cout << "MD2 file statistics:" << endl;
    cout << "   - myMD2Loader.num_frames = " << myMD2Loader.num_frames << endl;
    cout << "   - myMD2Loader.num_xyz = " << myMD2Loader.num_xyz << endl;
    cout << "   - myMD2Loader.num_tris = " << myMD2Loader.num_tris << endl;
    */

    //Code to create and display a tri-coloured triangle
    ///*
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

    m_program->release();

    m_frame++;
}
