#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

// Constants to help with location bindings
#define VERTEX_DATA 0
#define VERTEX_COLOUR 1
#define VERTEX_NORMAL 2
#define VERTEX_INDICES 3

class ShaderLoader{
public:
    ShaderLoader();
    bool openShaderFile(const char*, GLuint);
    void renderScene();
    void initShaders();
    static void key_callback(GLFWwindow*, int, int, int, int);
    static void error_callback(int, const char*);
    void ChangeSize(int, int);

private:
    // VAO and VBO to handle vertex state and data
    GLuint myVAO[1];
    GLuint myVBO;
    GLuint myIndexBuffer;

    // shader program to use
    GLuint myShaderProgram;

    GLubyte shaderText[8192];

    // Geometry for the simple scene - a tetrahedron with some vertex
    // attributes and a list of faces specifying connectivity
    const GLfloat tetVertices[16] = {
        0.0f, 0.0f, -0.75f, 1.0f,
        0.0f, 0.75f, 0.0f, 1.0f,
        -0.75f, -0.75f, 0.0f, 1.0f,
        0.75f, -0.75f, 0.0f, 1.0f
    };
    const GLushort tetFaceIndices[12] = {
        0,1,2,
        0,1,3,
        1,2,3,
        0,2,3
    };
    const GLfloat tetColours[16] = {
        1.0f,1.0f,1.0f,1.0f,
        1.0f,0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f
    };
    const GLfloat tetNormals[12] = {
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f,
        -0.707107f, -0.707107f, 0.0f,
        0.707107f, -0.707107f, 0.0f
    };
};

#endif //SHADER_LOADER_H
