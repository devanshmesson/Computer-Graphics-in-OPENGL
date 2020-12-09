#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

GLfloat dim,num;
//Change the dimensions according to the input
//first dimension-num
//second dimension-dim
GLfloat Points[4][3];

void init()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &Points[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
}

void display(void)
{
   int i;
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.9, 0.3, 0.5);
   glBegin(GL_LINE_STRIP);
   for (i = 980; i <= 3000; i++) glEvalCoord1f((GLfloat) 900/i);
   glEnd();
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h) glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
   else glOrtho(-5.0*(GLfloat)w/(GLfloat)h,5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
   cout<<"Enter number of Dimentions:";
   cin>>dim;
   cout<<"Enter Number of points:";
   cin>>num;
   cout<<"\nEnter Points for Bezier curve:"<<endl;
   for(int i=0;i<num;i++)for(int j=0;j<dim;j++)cin>>Points[i][j];
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500,500);
   glutInitWindowPosition(100,100);
   glutCreateWindow ("Bezier Curve");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
