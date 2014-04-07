// David Wu, 3/18/14
// Test program

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
#include <GLUT/glut.h>
#include <cmath>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
using namespace std;

float angle=0.0,deltaAngle = 0.0,r;
float x=0.0f,y=1.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
GLuint obj_displaylist;
int deltaMove = 0;

void orientMe(float ang) {

	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void moveMeFlat(int direction) {
	x = x + direction*(lx)*0.1;
	z = z + direction*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	r = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45,r,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		  	x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);
}

void drawObj() {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("Pikachu.obj",
		aiProcessPreset_TargetRealtime_Fast);

	if (!scene) {
		cout << "Error loading scene." << endl;
		exit(0);
	}

	aiMesh *mesh = scene->mMeshes[0];
	float *vertexArray = new float[mesh->mNumFaces*3*3];
	float *normalArray = new float[mesh->mNumFaces*3*3];
	float *uvArray = new float[mesh->mNumFaces*3*2];
	int numVerts = mesh->mNumFaces*3;

	cout << "Scene loaded." << endl;

	for (int i = 0; i < mesh->mNumFaces; ++i) {
		const aiFace& face = mesh->mFaces[i];
		for (int j = 0; j < 3; ++j) {
			aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
			memcpy(uvArray,&uv,sizeof(float)*2);
			uvArray+=2;

			aiVector3D normal = mesh->mNormals[face.mIndices[j]];
			memcpy(normalArray,&normal,sizeof(float)*3);
			normalArray+=3;
			 
			aiVector3D pos = mesh->mVertices[face.mIndices[j]];
			memcpy(vertexArray,&pos,sizeof(float)*3);
			vertexArray+=3;
		}
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	 
	glVertexPointer(3,GL_FLOAT,0,vertexArray);
	glNormalPointer(GL_FLOAT,0,normalArray);
	 
	glClientActiveTexture(GL_TEXTURE0_ARB);
	glTexCoordPointer(2,GL_FLOAT,0,uvArray);
	 
	glDrawArrays(GL_TRIANGLES,0,numVerts);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

GLuint createDL() {
	GLuint objDL = glGenLists(1);
	glNewList(objDL,GL_COMPILE);
	drawObj();
	glEndList();
	return objDL;
}

void initScene() {
	glEnable(GL_DEPTH_TEST);
	obj_displaylist = createDL();
}

void renderScene() {
	if (deltaMove)
		moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Draw ground

	/*glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();*/

	// Draw object
	glPushMatrix();
	glTranslatef(0,0,0);
	glCallList(obj_displaylist);
	glPopMatrix();

	glutSwapBuffers();
}

void pressKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT : 
			deltaAngle = -0.01f;break;
		case GLUT_KEY_RIGHT : 
			deltaAngle = 0.01f;break;
		case GLUT_KEY_UP : 
			deltaMove = 1;break;
		case GLUT_KEY_DOWN : 
			deltaMove = -1;break;
	}
}

void releaseKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT : 
		case GLUT_KEY_RIGHT : 
			deltaAngle = 0.0f;break;
		case GLUT_KEY_UP : 
		case GLUT_KEY_DOWN : 
			deltaMove = 0;break;
	}
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360);
	glutCreateWindow("OBJ Loader Test");

	initScene();
	
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutReshapeFunc(changeSize);

	glutMainLoop();

	return(0);
}