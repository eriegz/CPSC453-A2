Name: Evan Riegel
UCID: 00311775

— Notes: —

	This assignment is unfinished. I spoke to Mario and told him that despite roughly 20 hours of
	programming time, I have not been able to resolve multiple critical compatibility errors
	between Qt and various libraries including GLEW, GLFW, and OpenGL. Mario asked me to
	document these setbacks in my README file, which I have done below.

	Note that these are just the ones I could remember. I have spent the majority of my
	programming time googling errors and reading StackOverflow.

— Setbacks encountered in assignment 2: —

	[Format used: - Problem	• Solution, if any.]

	- Could not remote in to school computers to run tutorial 8 example code
		• NO RESOLUTION

	- Problems compiling & running tutorial 8 example code on home machine
		• installed GLEW
		• installed GLFW

	- Qt not recognizing shaders past version 1.20
		• Qt defaults to using legacy OpenGL profile. Need to use Core Profile.

	- Cannot set OpenGL profile to Core Profile (i.e.: version 3.3)
		• Use #include <QGLFormat>, create an instance of type QGLFormat, and use the 
		  setVersion(3, 3) call to set the version

	- Qt doesn’t recognize “#include <QGLFormat>”
		• Add “QT += opengl” to project file

	- Qt documentation recommends creating instance of object type “GLWidget” when it should
	  be “QGLWidget”.
		• Change to QGLWidget

	- After setting version number, “glGetString(GL_VERSION)” stopped responding
		• NO RESOLUTION

	- Qt creates object of type QOpenGLContext, defaults it to legacy OpenGL profile
		• NO RESOLUTION

— Functional accomplishments: —

	Re-structured an existing QApplication sample tutorial to form the basis for my MD2Viewer
	functionality and windowing.

	Re-factored the tutorial 8 Standalone example to be a class which provides shader loader
	functionality to the QApplication.

	Re-structured the MD2 file loader to be a class which provides functionality to the
	QApplication.

	Successfully loaded (but not compiled due to OpenGL default legacy profile) Assignment 2
	shaders as .vs.glsl and .fs.glsl files into the QApplication.

