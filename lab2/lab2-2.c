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
#include "VectorUtils3.h"
#include "loadobj.h"
#include <math.h>

// Globals
mat4 RotationY;
// Data would normally be read from files

GLint fps = 50;

GLfloat time;

	// vertex array object
unsigned int bunnyVertexArrayObjID;

	// Reference to shader program
GLuint program;

GLuint tex;

Model *m;

void init(void)
	{
		m = LoadModel("bunnyplus.obj");
		LoadTGATextureSimple("maskros512.tga", &tex);
		// vertex buffer object, used for uploading the geometry
		unsigned int bunnyVertexBufferObjID;
		unsigned int bunnyIndexBufferObjID;
		unsigned int bunnyNormalBufferObjID;
		unsigned int bunnyTexCoordBufferObjID;

		dumpInfo();

		// GL inits
		glClearColor(0.0,0.0,0.0,0);
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		printError("GL inits");

		// Load and compile shader
		program = loadShaders("lab2-2.vert", "lab2-2.frag");
		printError("init shader");



		// Upload geometry to the GPU:

		// Allocate and activate Vertex Array Object
		glGenVertexArrays(1, &bunnyVertexArrayObjID);
		glGenBuffers(1, &bunnyVertexBufferObjID);
		glGenBuffers(1, &bunnyIndexBufferObjID);
		glGenBuffers(1, &bunnyNormalBufferObjID);
		glGenBuffers(1, &bunnyTexCoordBufferObjID);
		glBindVertexArray(bunnyVertexArrayObjID);

		glBindTexture(GL_TEXTURE_2D, tex);

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

		if (m->texCoordArray != NULL)
    {
        glBindBuffer(GL_ARRAY_BUFFER, bunnyTexCoordBufferObjID);
        glBufferData(GL_ARRAY_BUFFER, m->numVertices*2*sizeof(GLfloat), m->texCoordArray, GL_STATIC_DRAW);
        glVertexAttribPointer(glGetAttribLocation(program, "inTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(glGetAttribLocation(program, "inTexCoord"));
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bunnyIndexBufferObjID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->numIndices*sizeof(GLuint), m->indexArray, GL_STATIC_DRAW);

		glUniform1i(glGetUniformLocation(program, "texUnit"), 0);

		// End of upload of geometry

		printError("init arrays");
	}


	void display(void)
	{
		printError("pre display");

		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(bunnyVertexArrayObjID);    // Select VAO
		glDrawElements(GL_TRIANGLES, m->numIndices, GL_UNSIGNED_INT, 0L);

		time = (GLfloat)glutGet(GLUT_ELAPSED_TIME)/1000;
		RotationY = Ry(time);
		glUniformMatrix4fv(glGetUniformLocation(program, "RotationY"), 1, GL_TRUE, RotationY.m);
		glUniform1f(glGetUniformLocation(program, "time"), time);

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
		glutCreateWindow ("GL3 LAB 2");
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutDisplayFunc(display);
		glutTimerFunc(1000/fps, &OnTimer, 0);
		init ();
		glutMainLoop();
		return 0;
	}
