/*
Test Case1:
100 1 200 100
150 0 200 300

Test Case2:
100 0 200 100
10 10 170 120

Test Case3:
100 0 200 100
50 0 50 100
*/

#include <windows.h>
#include<GL/glut.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<iostream>
using namespace std;
//#define int float

int T=8,B=4,R=2,L=1,code1,code2;
float x1,y1,x2,y2,xmin,ymin,xmax,ymax;

int fetch(int x,int y)
{
  int ans=0;
  if(x<xmin)ans|=L;
  else if(x>xmax)ans|=R;

  if(y<ymin)ans|=B;
  else if(y>ymax)ans|=T;

  return ans;

}
void init(void)
{
    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);
}

void display()
{

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0,1.0,0.0);

   glBegin(GL_LINE_LOOP);
   glVertex2i(xmin,ymin);
   glVertex2i(xmin,ymax);
   glVertex2i(xmax,ymax);
   glVertex2i(xmax,ymin);
   glEnd();
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_LINES);
   glVertex2i(x1,y1);
   glVertex2i(x2,y2);
   glEnd();
   glFlush();
}


int main(int argc,char** argv)
{

    printf("Enter Coordinates of Clipping Window:");
    cin>>xmin>>ymin>>xmax>>ymax;
    printf("Enter coordinates of line:");
    cin>>x1>>y1>>x2>>y2;

    code1=fetch(x1,y1);
    code2=fetch(x2,y2);
    bool flag=0;
    while(1)
    {
        float slope=(float)(y2-y1)/(float)(x2-x1);

        if((code1 || code2)==0) //if both are inside the clipping window
        {
         cout<<"if((code1 || code2)==0)"<<endl;
         flag=1;
         break;
        }
        else if((code1 && code2)!=0) //both outside the window
        {
            cout<<"Line cant be clipped"<<endl;
            cout<<"(code1 && code2)="<<(code1 && code2)<<endl;
            break;
        }
        else
        {
            int x,y,found;
            if(code1!=0)found=code1;
            else if(code2!=0)found=code2;

            if(found & T)
            {
             x=x1+(ymax-y1)/slope;
             y=ymax;
            }
            else if(found & B)
            {
                x=x1+(ymin-y1)/slope;
                y=ymin;
            }
            else if(found & L)
            {
                x=xmin;
                y=y1+slope*(xmin-x1);
            }
             else if(found & R)
            {
                x=xmax;
                y=y1+slope*(xmax-x1);
            }
          if(found==code1)
          {
              x1=x;
              y1=y;
              code1=fetch(x,y);
          }
          else if(found==code2)
          {
              x2=x;
              y2=y;
              code2=fetch(x,y);
          }
         }
    }

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Cohen Sutherland");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
