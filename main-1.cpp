/*
 * Teapot Checkers Texture mapping
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

unsigned char CHECKERS [4][4]={{000,255,000,255},
                               {255,000,255,000},
                               {000,255,000,255},
                               {255,000,255,000}
};
/* GLUT callback Handlers */

static void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-1,1,-1,1,-1,1);
    glViewport(0, 0, w, h);
    gluPerspective(45,w/(float)h,0.1,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*30.0;

    	// Reset transformations
	glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(	0.0f, 0.0f, 3.0f,
				0.0f, 0.0f,  0.0f,
				0.0f, 1.0f,  0.0f);
    //Enable depth test
    //glEnable(GL_DEPTH_TEST);
    //enables 2D texture mapping (meaning the image we pass in will will be 2D)
    //glEnable(GL_TEXTURE_2D);
    //tell OpenGL how to magnify texels by specifying a MAG filter.
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    //processes the CHECKERS image so that it renders with higher quality
    //(by building something called Mip Maps) and then it sends the image
    //over to the graphics card.
    //gluBuild2DMipmaps(GL_TEXTURE_2D,1,4,4,GL_LUMINANCE,GL_UNSIGNED_BYTE,CHECKERS);
    glPushMatrix();
        //glRotated(60,0,0,0);
        glRotated(a,0,1,0);
        //glutSolidSphere(0.5,16,16);
        glutSolidTeapot(0.5);
        //glutSolidTorus(0.2,0.8,16,16);
    glPopMatrix();



    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}



/* Program entry point */

int main(int ac, char *av[])
{
    glutInit(&ac, av);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Teapot Texture Lesson");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);


    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);

    glutMainLoop();

    return EXIT_SUCCESS;
}
