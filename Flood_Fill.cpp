#include <bits/stdc++.h>
#include <math.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

int n,a,b,choice=1,maxy=INT_MIN,maxx=INT_MIN,minx=INT_MAX,miny=INT_MAX;
float oldColor[3]={1,1,1};
float newColor[3]={1,0,0};
vector<pair<int,int>>v;



void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,640,0,480);
}

void floodfill(int x, int y, float oldColor[], float newColor[]) //Flood Fill Algorithm
{
    if(y>=minx && y<=maxy && x>=minx && x<=maxx)
    {

    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color); //Checking the colour of the present pixel

    int flag=1;
    for(int i=0;i<3;i++)
    {
        if(color[i]!=oldColor[i]){flag=0;break;} //if(present pixel colour == oldcolour)then colour present pixel with newcolor
    }
        if(flag==1)
        {
        glColor3f(newColor[0],newColor[1],newColor[2]);//colouring the pixel
        glBegin(GL_POINTS);
        glVertex2i(x,y); //plotting that coloured pixel
        glEnd();
        glFlush();
        if(choice==0)
        {
         floodfill(x+1,y,oldColor,newColor);
         floodfill(x-1,y,oldColor,newColor);
         floodfill(x,y+1,oldColor,newColor);
         floodfill(x,y-1,oldColor,newColor);
        }
        else if(choice==1)
        {
         floodfill(x+1,y,oldColor,newColor);
         floodfill(x-1,y,oldColor,newColor);
         floodfill(x,y+1,oldColor,newColor);
         floodfill(x,y-1,oldColor,newColor);

         floodfill(x+1,y+1,oldColor,newColor);
         floodfill(x-1,y+1,oldColor,newColor);
         floodfill(x-1,y-1,oldColor,newColor);
         floodfill(x+1,y-1,oldColor,newColor);
        }

        }
    }
    }


void mouse(int btn, int state, int x, int y) //starting the algorithm from the point
                                             //on which the mouse is clicked
{
    y = 480-y;
    if(btn==GLUT_LEFT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
            floodfill(x,y,oldColor,newColor);
        }
    }
}

void display()  //Drawing the Polygon
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    printf("Enter the Coordinates:");
    for(int i=0;i<n;i++)
    {
        glVertex2i(v[i].first,v[i].second);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    printf("Enter Number of Coordinates for the Polygon:");
    scanf("%d",&n);
    printf("Enter the Coordinates:");
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        v.push_back({a,b});
        if(maxy<b)maxy=b;
        if(maxx<a)maxx=a;
        if(miny>b)miny=b;
        if(minx>a)minx=a;
    }
    printf("Press 0 for 4-Connected\n Press 1 for 8-Connected");
    scanf("%d",&choice);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Flood Fill Algorithm");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
