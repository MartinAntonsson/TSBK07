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

#define near 10.0
#define far 300.0
#define right 5
#define left -5
#define top 5
#define bottom -5

// Globals
mat4 mtw, cam, proj, total;
vec3 p, l, v;

// Data would normally be read from files

GLint fps = 50;
GLfloat pi = 3.14159265359;

GLint viewWidth = 10, viewHeight = 10;
int centerX = 5, centerY = 10;
int tempX, tempY;

GLfloat time;


	// Reference to shader program
GLuint program;

GLuint texGrass;
GLuint texDirt;

Model *mBlade;
Model *mBalc;
Model *mRoof;
Model *mWalls;

void init(void)
	{
		mBlade = LoadModelPlus("windmill/blade.obj");
		mBalc = LoadModelPlus("windmill/windmill-balcony.obj");
		mRoof = LoadModelPlus("windmill/windmill-roof.obj");
		mWalls = LoadModelPlus("windmill/windmill-walls.obj");

		dumpInfo();

		// GL inits
		glClearColor(0.1,0.1,0.0,1.0);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		printError("GL inits");

		// Load and compile shader
		program = loadShaders("lab3-2.vert", "lab3-2.frag");
		printError("init shader");

		// Upload geometry to the GPU:

		LoadTGATextureSimple("grass.tga", &texGrass);

		LoadTGATextureSimple("dirt.tga", &texDirt);

		// End of upload of geometry

		printError("init arrays");
	}


	void display(void)
	{
		printError("pre display");

		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		p = SetVector(tempX,15,0);
		l = SetVector(4.5,9.2,0);
		v = SetVector(0,1,0);
		cam = lookAtv(p, l, v);

		proj = frustum(left, right, bottom, top, near, far);


		time = (GLfloat)glutGet(GLUT_ELAPSED_TIME)/1000;

		glBindTexture(GL_TEXTURE_2D, texGrass);
		glUniform1i(glGetUniformLocation(program, "texUnit"), 0);
		mtw = T(4.5, 9.2, 0.0);
		total = Mult(proj, Mult(cam, Mult(Ry(time*0.1), Mult(mtw, Rx(time+0)))));
		glUniformMatrix4fv(glGetUniformLocation(program, "mtw"), 1, GL_TRUE, mtw.m);
		glUniformMatrix4fv(glGetUniformLocation(program, "total"), 1, GL_TRUE, total.m);
		DrawModel(mBlade, program, "in_Position", "in_Normal", "inTexCoord");

		total = Mult(proj, Mult(cam, Mult(Ry(time*0.1), Mult(mtw, Rx(time + pi/2)))));
		glUniformMatrix4fv(glGetUniformLocation(program, "mtw"), 1, GL_TRUE, mtw.m);
		glUniformMatrix4fv(glGetUniformLocation(program, "total"), 1, GL_TRUE, total.m);
		DrawModel(mBlade, program, "in_Position", "in_Normal", "inTexCoord");

		total = Mult(proj, Mult(cam, Mult(Ry(time*0.1), Mult(mtw, Rx(time + pi)))));
		glUniformMatrix4fv(glGetUniformLocation(program, "mtw"), 1, GL_TRUE, mtw.m);
		glUniformMatrix4fv(glGetUniformLocation(program, "total"), 1, GL_TRUE, total.m);
		DrawModel(mBlade, program, "in_Position", "in_Normal", "inTexCoord");

		total = Mult(proj, Mult(cam, Mult(Ry(time*0.1), Mult(mtw, Rx(time + 3*pi/2)))));
		glUniformMatrix4fv(glGetUniformLocation(program, "mtw"), 1, GL_TRUE, mtw.m);
		glUniformMatrix4fv(glGetUniformLocation(program, "total"), 1, GL_TRUE, total.m);
		DrawModel(mBlade, program, "in_Position", "in_Normal", "inTexCoord");


		glBindTexture(GL_TEXTURE_2D, texDirt);
		glUniform1i(glGetUniformLocation(program, "texUnit"), 0);
		mtw = T(0.0, 0.0, 0.0);
		total = Mult(proj, Mult(cam, Mult(Ry(time*0.1), mtw)));
		glUniformMatrix4fv(glGetUniformLocation(program, "mtw"), 1, GL_TRUE, mtw.m);
		glUniformMatrix4fv(glGetUniformLocation(program, "total"), 1, GL_TRUE, total.m);
		DrawModel(mBalc, program, "in_Position", "in_Normal", "inTexCoord");
		DrawModel(mRoof, program, "in_Position", "in_Normal", "inTexCoord");
		DrawModel(mWalls, program, "in_Position", "in_Normal", "inTexCoord");

		printError("display");

		glutSwapBuffers();
	}

	void OnTimer(int value)
	{
		glutPostRedisplay();
		glutTimerFunc(1000/fps, &OnTimer, value);
	}

	void handlerFunc(int x, int y)
	{
		tempX = x;
		tempY = y;

		glutPostRedisplay();
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
		glutPassiveMotionFunc(handlerFunc);
		glutMainLoop();
		return 0;
	}
