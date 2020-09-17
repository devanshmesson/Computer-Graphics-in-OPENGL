#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#define float int
int xx,yy,Radius;



void display()
{
    int x=0,y=Radius;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);
    glColor3d(1,1,1);
    glBegin(GL_POLYGON);

    int distance=3-2*Radius;

      glVertex2f(xx+x,yy+y);
      glVertex2f(xx-x,yy+y);
      glVertex2f(xx+x,yy-y);
      glVertex2f(xx-x,yy-y);
      glVertex2f(xx+y,yy+x);
      glVertex2f(xx-y,yy+x);
      glVertex2f(xx+y,yy-x);
      glVertex2f(xx-y,yy-x);

    while(y>=x)
    {
        x++;
        if(distance>0)
        {
            y--;
            distance+=4*(x-y)+10;
        }
        else distance+=4*x+6;

      glVertex2f(xx+x,yy+y);
      glVertex2f(xx-x,yy+y);
      glVertex2f(xx+x,yy-y);
      glVertex2f(xx-x,yy-y);
      glVertex2f(xx+y,yy+x);
      glVertex2f(xx-y,yy+x);
      glVertex2f(xx+y,yy-x);
      glVertex2f(xx-y,yy-x);
    }
    glEnd();
    glutSwapBuffers();

}


int main(int argc,char **argv)
{
   printf("Enter Radius of the Circle\n");
   scanf("%d",&Radius);
   printf("Enter Coordinates of the Circle\n");
   scanf("%d",&xx);
   scanf("%d",&yy);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(100,200);
  glutInitWindowSize(500,500);
  glClearColor(1,1,1,1);
  glutCreateWindow("Circle using Polar Coordinaates");
  glutDisplayFunc(display);
  glutMainLoop();
}
