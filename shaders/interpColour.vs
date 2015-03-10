// The ShadedIdentity Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
//#version 410

//in vec4 vColor;
//in vec4 vVertex;

//out vec4 vVaryingColor;

//void main(void){
//	vVaryingColor = vColor;
//	gl_Position = vVertex;
//}

attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
uniform highp mat4 matrix;

void main() {
    col = colAttr;
    gl_Position = matrix * posAttr;
}
