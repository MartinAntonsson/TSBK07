// Lab 1-2.
// This is the same as the first simple example in the course book,
// but with a few error checks.
// Remember to copy your file to a new on appropriate places during the lab so you keep old results.
// Note that the files "lab1-2.frag", "lab1-2.vert" are required.

// Should work as is on Linux and Mac. MS Windows needs GLEW or glee.
// See separate Visual Studio version of my demos.
#ifdef __APPLE__
#include <OpenGL/gl3.h>
// Linking hint for Lightweight IDE
// uses framework Cocoa
#endif
#include "MicroGlut.h"
#include "GL_utilities.h"
#include <math.h>

// Globals
// Data would normally be read from files
GLfloat vertices[] =
{
-1.0f,-1.0f,-1.0f, // triangle 1 : begin
-1.0f,-1.0f, 1.0f,
-1.0f, 1.0f, 1.0f, // triangle 1 : end
1.0f, 1.0f,-1.0f, // triangle 2 : begin
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f,-1.0f, // triangle 2 : end
1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
1.0f,-1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
1.0f,-1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f, 1.0f,
1.0f,-1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
1.0f,-1.0f, 1.0f
};

GLuint color[] =
{
	0.0,0.0,1.0,0.8,
	1.0,0.0,0.0,0.8,
	0.0,1.0,0.0,0.8
};

GLfloat myMatrix[] =
{
	1.0f,0.0f,0.0f, 0.0f,
	0.0f,1.0f,0.0f, 0.0f,
	0.0f,0.0f,1.0f, 0.0f,
	0.0f,0.0f,0.0f, 1.0f
};

GLfloat angle = 0.1f;

GLint fps = 50;

	// vertex array object
unsigned int vertexArrayObjID;

	// Reference to shader program
GLuint program;

void init(void)
	{
		// vertex buffer object, used for uploading the geometry
		unsigned int vertexBufferObjID;
		unsigned int colorBufferObjID;

		dumpInfo();

		// GL inits
		glClearColor(1.0,0.2,0.5,0);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		printError("GL inits");

		// Load and compile shader
		program = loadShaders("lab1-5.vert", "lab1-5.frag");
		printError("init shader");

		// Upload geometry to the GPU:

		// Allocate and activate Vertex Array Object
		glGenVertexArrays(1, &vertexArrayObjID);
		glBindVertexArray(vertexArrayObjID);
		// Allocate Vertex Buffer Objects
		glGenBuffers(1, &vertexBufferObjID);
		//glGenBuffers(1, &colorBufferObjID);

		// VBO for vertex data
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
		glBufferData(GL_ARRAY_BUFFER, 12*9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

		// End of upload of geometry

		// VBO for vertex data
		//glBindBuffer(GL_ARRAY_BUFFER, colorBufferObjID);
		//glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLuint), color, GL_STATIC_DRAW);
		//glVertexAttribPointer(glGetAttribLocation(program, "color"), 4, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(glGetAttribLocation(program, "color"));


		// End of upload of geometry

		printError("init arrays");
	}


	void display(void)
	{
		printError("pre display");

		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		//angle += 0.01f;
		angle = (GLfloat)glutGet(GLUT_ELAPSED_TIME)/1000;

		myMatrix[0] = (GLfloat)cos(angle);
		myMatrix[1] = -(GLfloat)sin(angle);
		myMatrix[4] = (GLfloat)sin(angle);
		myMatrix[5] = (GLfloat)cos(angle);
		myMatrix[6] = -(GLfloat)sin(angle);
		myMatrix[9] = (GLfloat)sin(angle);
		myMatrix[10] = (GLfloat)cos(angle);
		myMatrix[3] = (GLfloat)sin(angle)/2;
		myMatrix[7] = (GLfloat)cos(angle)/2;
		//myMatrix[11] = (GLfloat)cos(angle)/2;

		glUniformMatrix4fv(glGetUniformLocation(program, "myMatrix"), 1, GL_TRUE, myMatrix);

		glBindVertexArray(vertexArrayObjID);	// Select VAO
		glDrawArrays(GL_TRIANGLES, 0, 12*3);	// draw object

		printError("display");

		glutSwapBuffers();
	}

	void OnTimer(int value)
	{
		glutPostRedisplay();
		glutTimerFunc(1000/fps, &OnTimer, value);
	}

	int main(int argc, char *argv[])
	{
		glutInit(&argc, argv);
		glutInitContextVersion(3, 2);
		glutCreateWindow ("GL3 white triangle example");
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutDisplayFunc(display);
		glutTimerFunc(1000/fps, &OnTimer, 0);
		init ();
		glutMainLoop();
		return 0;
	}
