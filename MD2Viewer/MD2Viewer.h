#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

#include <QtCore/qmath.h>
#include <QtCore/QCoreApplication>

#include "OpenGLWindow/OpenGLWindow.h"
#include "ShaderLoader/ShaderLoader.h"
//#include "MD2Model/MD2Model.h"

class MD2Viewer : public OpenGLWindow{
public:
    MD2Viewer();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:
    GLuint loadShader(GLenum type, const char *source);

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;

    //MD2Model myMD2Model;
    //ShaderLoader myShaderLoader;
};
