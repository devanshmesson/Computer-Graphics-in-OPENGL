#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int x,y;
float major,minor;
void display(void)
{
 double I,compute;
 glClear (GL_COLOR_BUFFER_BIT);
 glColor3f (1.0, 1.0, 1.0);
 glBegin(GL_POINTS);
 glVertex2s(x,y);
 for(int i=0;i<=major;i+=1)
 {
 compute=sqrt(1-(i*i)/(major*major))*minor;
 int j=(int)(compute);
 glVertex2s(x+i,y+j);
 glVertex2s(x-i,y+j);
 glVertex2s(x-i,y-j);
 glVertex2s(x+i,y-j);
 }
 glColor3f (1.0, 0.0, 1.0);
 glEnd();
 glFlush();
 }
void init(void)
 {
 glClearColor (0.0, 0.0, 0.0, 0.0);
 glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
 }
int main(int argc, char** argv)
{
 printf("Center:\n");
 scanf("%d %d",&x,&y);
 printf("Major and Minor:\n");
 scanf("%f %f",&major,&minor);
 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize (500, 500);
 glutInitWindowPosition (100, 100);
 glutCreateWindow ("Ellipse");
 init();
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}
