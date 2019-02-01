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
#include "loadobj.h"
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
unsigned int bunnyVertexArrayObjID;

	// Reference to shader program
GLuint program;

Model *m;

void init(void)
	{
		m = LoadModel("bunny.obj");
		// vertex buffer object, used for uploading the geometry
		unsigned int bunnyVertexBufferObjID;
		unsigned int bunnyIndexBufferObjID;
		unsigned int bunnyNormalBufferObjID;


		dumpInfo();

		// GL inits
		glClearColor(1.0,0.2,0.5,0);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		printError("GL inits");

		// Load and compile shader
		program = loadShaders("lab1-6.vert", "lab1-6.frag");
		printError("init shader");

		// Upload geometry to the GPU:

		// Allocate and activate Vertex Array Object
		glGenVertexArrays(1, &bunnyVertexArrayObjID);
		glGenBuffers(1, &bunnyVertexBufferObjID);
		glGenBuffers(1, &bunnyIndexBufferObjID);
		glGenBuffers(1, &bunnyNormalBufferObjID);
		glBindVertexArray(bunnyVertexArrayObjID);

		// VBO for vertex data
		glBindBuffer(GL_ARRAY_BUFFER, bunnyVertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, m->numVertices*3*sizeof(GLfloat), m->vertexArray, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

		// VBO for normal data
    glBindBuffer(GL_ARRAY_BUFFER, bunnyNormalBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, m->numVertices*3*sizeof(GLfloat), m->normalArray, GL_STATIC_DRAW);
    glVertexAttribPointer(glGetAttribLocation(program, "in_Normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(program, "in_Normal"));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bunnyIndexBufferObjID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->numIndices*sizeof(GLuint), m->indexArray, GL_STATIC_DRAW);

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

		//myMatrix[0] = (GLfloat)cos(angle);
		//myMatrix[1] = -(GLfloat)sin(angle);
		//myMatrix[4] = (GLfloat)sin(angle);
		myMatrix[5] = (GLfloat)cos(angle);
		myMatrix[6] = -(GLfloat)sin(angle);
		myMatrix[9] = (GLfloat)sin(angle);
		myMatrix[10] = (GLfloat)cos(angle);
		myMatrix[3] = (GLfloat)sin(angle)/2;
		myMatrix[7] = (GLfloat)cos(angle)/2;
		myMatrix[11] = (GLfloat)cos(angle)/2;

		glUniformMatrix4fv(glGetUniformLocation(program, "myMatrix"), 1, GL_TRUE, myMatrix);

		glBindVertexArray(bunnyVertexArrayObjID);    // Select VAO
		glDrawElements(GL_TRIANGLES, m->numIndices, GL_UNSIGNED_INT, 0L);

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
