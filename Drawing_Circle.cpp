#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>

float Radius;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);
    glColor3d(0,1,0);
    glBegin(GL_POLYGON);
    for(int i=1;i<=360;i++)
    {
        float theta=i*(3.141/180);
        float x=Radius*cos(theta);
        float y=Radius*sin(theta);
        glVertex2d(x,y);
    }
    glEnd();
    glutSwapBuffers();
}

int main(int argc,char **argv)
{
   printf("Enter Radius of the Circle\n");
   scanf("%f",&Radius);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(100,200);
  glutInitWindowSize(500,500);
  glClearColor(1,1,1,1);
  glutCreateWindow("Circle using Polar Coordinaates");
  glutDisplayFunc(display);
  glutMainLoop();
}
