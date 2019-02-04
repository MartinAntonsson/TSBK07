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

#define near 1.0
#define far 30.0
#define right 0.5
#define left -0.5
#define top 0.5
#define bottom -0.5

// Globals
mat4 mtw, cam, proj, total;
vec3 p, l, v;

// Data would normally be read from files

GLint fps = 50;

GLfloat time;


	// Reference to shader program
GLuint program;

GLuint texMask;
GLuint texConc;

Model *mBunny;
Model *mCar;

void init(void)
	{
		mBunny = LoadModelPlus("bunnyplus.obj");
		mCar = LoadModelPlus("bilskiss.obj");

		dumpInfo();

		// GL inits
		glClearColor(0.1,0.1,0.0,1.0);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		printError("GL inits");

		// Load and compile shader
		program = loadShaders("lab2-7.vert", "lab2-7.frag");
		printError("init shader");

		// Upload geometry to the GPU:

		p = SetVector(0,5,5);
		l = SetVector(0,0,0);
		v = SetVector(0,1,0);
		cam = lookAtv(p, l, v);

		proj = frustum(left, right, bottom, top, near, far);

		LoadTGATextureSimple("maskros512.tga", &texMask);

		LoadTGATextureSimple("conc.tga", &texConc);

		// End of upload of geometry

		printError("init arrays");
	}


	void display(void)
	{
		printError("pre display");

		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		time = (GLfloat)glutGet(GLUT_ELAPSED_TIME)/1000;

		glBindTexture(GL_TEXTURE_2D, texMask);
		glUniform1i(glGetUniformLocation(program, "texUnit"), 0);
		mtw = T(2.0, 0.0, 0.0);
		total = Mult(proj, Mult(cam, Mult(Ry(time), mtw)));
		glUniformMatrix4fv(glGetUniformLocation(program, "mtw"), 1, GL_TRUE, mtw.m);
		glUniformMatrix4fv(glGetUniformLocation(program, "total"), 1, GL_TRUE, total.m);
		DrawModel(mBunny, program, "in_Position", "in_Normal", "inTexCoord");

		glBindTexture(GL_TEXTURE_2D, texConc);
		glUniform1i(glGetUniformLocation(program, "texUnit"), 0);
		mtw = T(-2.0, -0.6, 0.0);
		total = Mult(proj, Mult(cam, Mult(Ry(time), mtw)));
		glUniformMatrix4fv(glGetUniformLocation(program, "mtw"), 1, GL_TRUE, mtw.m);
		glUniformMatrix4fv(glGetUniformLocation(program, "total"), 1, GL_TRUE, total.m);
		DrawModel(mCar, program, "in_Position", "in_Normal", "inTexCoord");

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
