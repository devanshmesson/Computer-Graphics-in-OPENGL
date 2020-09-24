#include <bits/stdc++.h>
#include <math.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;
int n,a,b,choice=1,maxy=INT_MIN,maxx=INT_MIN,minx=INT_MAX,miny=INT_MAX;
vector<pair<int,int>>v;

void init(){
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,640,0,480);
}

void boundaryfill(int x, int y, float* fillColor, float* boundaryColor)
{
    if(y>=minx && y<=maxy && x>=minx && x<=maxx)
    {
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    if((color[0]!=boundaryColor[0] || color[1]!=boundaryColor[1] || color[2]!=boundaryColor[2])&&(color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2]))
    {
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
        glFlush();
        if(choice==0)
        {
        boundaryfill(x+1,y,fillColor,boundaryColor);
        boundaryfill(x-1,y,fillColor,boundaryColor);
        boundaryfill(x,y+1,fillColor,boundaryColor);
        boundaryfill(x,y-1,fillColor,boundaryColor);
        }
        else if(choice==1)
        {
         boundaryfill(x+1,y,fillColor,boundaryColor);
         boundaryfill(x-1,y,fillColor,boundaryColor);
         boundaryfill(x,y+1,fillColor,boundaryColor);
         boundaryfill(x,y-1,fillColor,boundaryColor);

         boundaryfill(x+1,y+1,fillColor,boundaryColor);
         boundaryfill(x-1,y+1,fillColor,boundaryColor);
         boundaryfill(x-1,y-1,fillColor,boundaryColor);
         boundaryfill(x+1,y-1,fillColor,boundaryColor);
        }
    }
    }
}

void mouse(int btn, int state, int x, int y){
    y = 480-y;
    if(btn==GLUT_LEFT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
            float boundaryColor[] = {1,0,0};
            float color[] = {0,0,1};
            boundaryfill(x,y,color,boundaryColor);
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
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
    printf("Press 0 for 4-Connected\nPress 1 for 8-Connected:\n");
    scanf("%d",&choice);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Boundary Fill Algorith,");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
