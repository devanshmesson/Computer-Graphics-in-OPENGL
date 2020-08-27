#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>

int abs(int n)
{
 if(n<0)return (n*(-1));
}
void display()
{
  float x1=2,y1=3;
  float x2=8,y2=10;
  float m=(y2-y1)/(x2-x1);
  float steps;
  if(abs(y2-y1)>=abs(x2-x1))steps=abs(y2-y1);
  else steps=abs(x2-x1);

  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-10,10,-10,10);
  

  float xincrease=(x2-x1)/steps;
  float yincrease=(y2-y1)/steps;

  glBegin(GL_POINTS);
  bool flag=0;
  float x=2,y=3;
  for(int i=0;i<=steps;i++)
  {
      if(flag)
      {
        x+=xincrease;
        y+=yincrease;
      }
      flag=1;
      glVertex2f(x,y);
  }
  glEnd();
  glFlush();

}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Experiment 3 Question 2");
    glutDisplayFunc(display);
    glutMainLoop();
}
