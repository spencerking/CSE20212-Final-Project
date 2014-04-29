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
	void initTitlescreen();
	void renderTitlescreen();
	void loadTitleImage();
	//void bindTexture();

   private:
	GLfloat vertices[24];
	GLfloat texcoords[24];
	GLuint tex_2d;
};
