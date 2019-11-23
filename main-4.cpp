/*
 * Texture mapping with RGBA Checkers Texture
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];


void makeCheckImage(void)
{
   int i, j, c;

    //Generating Checker Patterm
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

void init(void)
{
   glEnable(GL_DEPTH_TEST);

   makeCheckImage();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
                checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                checkImage);
   //gluBuild2DMipmaps(GL_TEXTURE_2D,1,checkImageWidth,checkImageHeight,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);

}

float angle = 0.10f;

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();

   gluLookAt(	0.0f, 0.0f,  5.0f,
				0.0f, 0.0f,  0.0f,
				0.0f, 1.0f,  0.0f);

   glEnable(GL_TEXTURE_2D);

   glRotatef(angle, 0.0f, 1.0f, 0.0f);

   glBegin(GL_QUADS);
       glTexCoord2f(0, 0); glVertex3f(-2.0, -1.0, 0.0);
       glTexCoord2f(0, 5); glVertex3f(-2.0, 1.0, 0.0);
       glTexCoord2f(5, 5); glVertex3f(0.0, 1.0, 0.0);
       glTexCoord2f(5, 0); glVertex3f(0.0, -1.0, 0.0);

       //glTexCoord2f(0, 0); glVertex3f(-2.0, -1.0, 0.0);
       //glTexCoord2f(0, 1); glVertex3f(-2.0, 1.0, 0.0);
       //glTexCoord2f(1, 1); glVertex3f(0.0, 1.0, 0.0);
       //glTexCoord2f(1, 0); glVertex3f(0.0, -1.0, 0.0);

       glTexCoord2f(0.2, 0.2); glVertex3f(1.0, -1.0, 0.0);
       glTexCoord2f(0.2, 0.8); glVertex3f(1.0, 1.0, 0.0);
       glTexCoord2f(0.8, 0.8); glVertex3f(2.41421, 1.0, -1.41421);
       glTexCoord2f(0.8, 0.2); glVertex3f(2.41421, -1.0, -1.41421);
   glEnd();

   glutSolidTeapot(1);
   //glutSolidTorus(1,2,16,16);

   // Initialization
    GLUquadricObj *quadric;
    quadric=gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricOrientation(quadric,GLU_INSIDE);

    // Render
    glPushMatrix();
    glTranslated(0,0,-3);
    gluSphere(quadric,1,16,16);
    //// gluCylinder (or cone),gluDisk,gluPartialDisk

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    angle+=0.05f;

	glutSwapBuffers();
}

void reshape(int w, int h)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(display);
   glutMainLoop();
   return 0;
}
