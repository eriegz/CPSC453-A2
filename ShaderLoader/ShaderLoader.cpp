#include "ShaderLoader.h"

ShaderLoader::ShaderLoader(){
    cout << "ShaderLoader::ShaderLoader() is called." << endl;
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
      exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Anti-aliasing - This will have smooth polygon edges
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(800, 800, "VBO and shader example", NULL, NULL);
    if (!window){
        if(myShaderProgram ) {
          glDeleteProgram(myShaderProgram);
          glDeleteVertexArraysAPPLE(1, myVAO);
        }
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Inform OpenGL we're working with the new version
    /*
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK){
        cout << "glewInit() failed." << endl;
        exit(EXIT_FAILURE);
    }
    */

    // These two lines will print out the version of OpenGL and GLSL
    // that are being used so that problems due to version differences
    // can easily be identified.
    printf( "OpenGL version: %s\n", (const char*)glGetString(GL_VERSION) );
    printf( "GLSL version: %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Do any necessary initializations (enabling buffers, setting up
    // shaders, geometry etc., before entering the main loop.)
    // This is done by calling the function setupRenderingContext().
    setupRenderingContext();
    if( myShaderProgram ) {
      while (!glfwWindowShouldClose(window)){
          int width, height;
          glfwGetFramebufferSize(window, &width, &height);
          glViewport(0, 0, width, height);

          renderScene();

          // Note that buffer swapping and polling for events is done here
          // so please don't do it in the function used to draw the scene.
          glfwSwapBuffers(window);
          glfwPollEvents();
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool ShaderLoader::loadShaderFile(const char *filename, GLuint shader) {
  GLint shaderLength = 0;
  FILE *fp;

  // Open the shader file
  fp = fopen(filename, "r");
  if(fp != NULL) {
    // See how long the file is
    while (fgetc(fp) != EOF)
      shaderLength++;

    // Go back to beginning of file
    rewind(fp);

    // Read the whole file in
    fread(shaderText, 1, shaderLength, fp);

    // Make sure it is null terminated and close the file
    shaderText[shaderLength] = '\0';
    fclose(fp);
  }
  else {
    return false;
  }

  // Load the string into the shader object
  GLchar* fsStringPtr[1];
  fsStringPtr[0] = (GLchar *)((const char*)shaderText);
  glShaderSource(shader, 1, (const GLchar **)fsStringPtr, NULL );

  return true;
}

// Called to draw scene
void ShaderLoader::renderScene() {
    cout << "ShaderLoader::renderScene() is called." << endl;
  // Clear the window and the depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(myShaderProgram);

  // Note that this version of the draw command uses the
  // bound index buffer to get the vertex coordinates.
  glDrawElements( GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);
}

// This function does any needed initialization on the rendering
// context.
void ShaderLoader::setupRenderingContext() {
  // Background
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
  glEnable(GL_DEPTH_TEST);

  // First setup the shaders
  //Now, let's setup the shaders
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  myShaderProgram = (GLuint)NULL;
  GLint testVal;

  //if( !loadShaderFile("../../../../A2/shaders/Phong.vs.glsl", vertShader) ) {
  if( !loadShaderFile("../../../../A2/shaders/interpColour.vs", vertShader) ) {
    glDeleteShader( vertShader );
    glDeleteShader( fragShader );
    cout << "The shader 'interpColour.vs' could not be found." << endl;
  }
  //if( !loadShaderFile("../../../../A2/shaders/Phong.fs.glsl", fragShader) ) {
  if( !loadShaderFile("../../../../A2/shaders/interpColour.fs", fragShader) ) {
    glDeleteShader( vertShader );
    glDeleteShader( fragShader );
    cout << "The shader 'interpColour.fs' could not be found." << endl;
  }

  glCompileShader(vertShader);
  glCompileShader(fragShader);

  // Check for any error generated during shader compilation
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &testVal);
  if( testVal == GL_FALSE ) {
    char source[8192];
    char infoLog[8192];
    glGetShaderSource( vertShader, 8192, NULL, source );
    glGetShaderInfoLog( vertShader, 8192, NULL, infoLog);
    //cout << "The shader: " << endl << (const char*)source << endl << " failed to compile:" << endl;
    cout << "============= Vertex shader compilation failed ===============" << endl;
    fprintf( stderr, "%s\n", infoLog);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
  }
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &testVal);
  if( testVal == GL_FALSE ) {
    char source[8192];
    char infoLog[8192];
    glGetShaderSource( fragShader, 8192, NULL, source);
    glGetShaderInfoLog( fragShader, 8192, NULL, infoLog);
    //cout << "The shader: " << endl << (const char*)source << endl << " failed to compile:" << endl;
    cout << "============= Fragment shader compilation failed ===============" << endl;
    fprintf( stderr, "%s\n", infoLog);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
  }

  // Create the shader program and bind locations for the vertex
  // attributes before linking. The linking process can also generate errors
  myShaderProgram = glCreateProgram();
  glAttachShader(myShaderProgram, vertShader);
  glAttachShader(myShaderProgram, fragShader);

  glBindAttribLocation( myShaderProgram, VERTEX_DATA, "vVertex" );
  glBindAttribLocation( myShaderProgram, VERTEX_COLOUR, "vColor" );

  glLinkProgram( myShaderProgram );
  glDeleteShader( vertShader );
  glDeleteShader( fragShader );
  glGetProgramiv( myShaderProgram, GL_LINK_STATUS, &testVal );
  if( testVal == GL_FALSE ) {
    char infoLog[1024];
    glGetProgramInfoLog( myShaderProgram, 1024, NULL, infoLog);
    cout << "The shader program" << "(interpColour.vs + interpColour.fs) failed to link:"
         << endl << (const char*)infoLog << endl;
    glDeleteProgram(myShaderProgram);
    myShaderProgram = (GLuint)NULL;
  }

  // Now setup the geometry in a vertex buffer object.
  // Setup the vertex state array object. All subsequent buffers will
  // be bound to it.
  glGenVertexArrays(1, myVAO);
  glBindVertexArray(myVAO[0]);

  glGenBuffers(1, &myVBO);
  glBindBuffer( GL_ARRAY_BUFFER, myVBO );

  // Allocate space and load vertex data into the buffer.
  // We are using one VBO for all the data. For this demo, we won't be
  // making use of the normals but the code below shown how we might
  // store them in the VBO.
  glBufferData(GL_ARRAY_BUFFER, sizeof(tetVertices) +
               sizeof(tetColours) + sizeof(tetNormals), NULL,
               GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tetVertices),
                  tetVertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(tetVertices),
                  sizeof(tetColours), tetColours);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(tetVertices) +
                  sizeof(tetColours), sizeof(tetNormals),
                  tetNormals);

  // Load face indices into the index buffer
  glGenBuffers(1, &myIndexBuffer );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, myIndexBuffer );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(tetFaceIndices), tetFaceIndices, GL_STATIC_DRAW );

  // Now we'll use the attribute locations to map our vertex data (in
  // the VBO) to the shader
  glEnableVertexAttribArray( VERTEX_DATA );
  glVertexAttribPointer( VERTEX_DATA, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) 0 );
  glEnableVertexAttribArray( VERTEX_COLOUR );
  glVertexAttribPointer( VERTEX_COLOUR, 4, GL_FLOAT, GL_FALSE, 0,
                         (const GLvoid*)(sizeof(tetVertices)));
}

// Keyboard callback function.
void ShaderLoader::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

// Error callback function
void ShaderLoader::error_callback(int error, const char* description){
  fputs(description, stderr);
}

void ShaderLoader::ChangeSize(int w, int h) {
  // Set Viewport to window dimensions
  glViewport(0, 0, w, h);
}
