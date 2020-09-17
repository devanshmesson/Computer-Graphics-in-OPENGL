    #include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glut.h>
	#include<math.h>
	#include<stdio.h>
	

	float x,y,Radius;
	float xx=0,yy=Radius;
	

	void display()
	{
	

	    glClear(GL_COLOR_BUFFER_BIT);
	    glLoadIdentity();
	    gluOrtho2D(-100,100,-100,100);
	    glColor3d(0,1,0);
	    glBegin(GL_POLYGON);
	    float d=1-Radius;
	

	    while(x<=y)
	    {
	      glVertex2f(xx+x,yy+y);
	      glVertex2f(xx-x,yy+y);
	      glVertex2f(xx+x,yy-y);
	      glVertex2f(xx-x,yy-y);
	

	      glVertex2f(xx+y,yy+x);
	      glVertex2f(xx-y,yy+x);
	      glVertex2f(xx+y,yy-x);
	      glVertex2f(xx-y,yy-x);
          
          if(d<0)
	      {
	        x++;
	        d+=(2*x)+2;
	      }
	      else
	      {
	          x++;
	          y--;
	          d+=2*(x-y)+1;
	      }
	

	    }
	    glEnd();
	    glutSwapBuffers();
	}
	
	int main(int argc,char **argv)
	{
	   printf("Enter Radius of the Circle\n");
	   scanf("%f",&Radius);
	   printf("Enter Coordinates of the Circle\n");
	   scanf("%f",&x);
	   scanf("%f",&y);
	  glutInit(&argc,argv);
	  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	  glutInitWindowPosition(100,200);
	  glutInitWindowSize(500,500);
	  glClearColor(1,1,1,1);
	  glutCreateWindow("Circle using Polar Coordinaates");
	  glutDisplayFunc(display);
	  glutMainLoop();
	}
