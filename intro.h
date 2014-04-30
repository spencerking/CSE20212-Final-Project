#ifdef __APPLE__
   #include <GLUT/glut.h>
   #include <OpenGL/gl.h>
   #include <soil.h>
#else
   #include <GL/glut.h>
   #include <GL/gl.h>
   #include <SOIL/soil.h>
#endif

class Intro {

   public:
	Intro(); //constructor
	void renderTitlescreen();

   private:
	GLfloat vertices[72];
	GLfloat texcoords[24];
	GLshort indices[36];
	GLuint tex_2d;
        float size; //size of cube
};
