#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include<bits/stdc++.h>
using namespace std;

struct coordinate
{
    float x,y;
} window[4],out_vertex[4],in_vertex[4];
int Nout;

void draw_polygon(coordinate point[],int n)
{
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++)glVertex2f(point[i].x,point[i].y);
    glEnd();
}

bool insideVer(coordinate point)
{
        if((point.x>=window[0].x)&&(point.x<=window[2].x))
        {
         if((point.y>=window[0].y)&&(point.y<=window[2].y))return true;
        }
        return false;
}

void add_vertex(coordinate point)
{
    out_vertex[Nout]=point;
    Nout=Nout+1;
}

coordinate intersection_point(coordinate update,coordinate point,int edge)
{
    coordinate intersecting_point;
    float slope;
    if(window[edge].x==window[(edge+1)%4].x)
    {
        //Vertical rectangular line
        slope=(point.y-update.y)/(point.x-update.x);
        intersecting_point.x=window[edge].x;
        intersecting_point.y=intersecting_point.x*slope+update.y;
    }
    else
    {
        //Horizontal rectangular Line
        slope=(point.y-update.y)/(point.x-update.x);
        intersecting_point.y=window[edge].y;
        intersecting_point.x=(intersecting_point.y-update.y)/slope;
    }
    return intersecting_point;
}

void Sutherland_Hodgman(coordinate in_vertex[],int Nin)
{
    coordinate update,point,interSec;
    for(int i=0;i<4;i++)
    {
        Nout=0;
        update=in_vertex[Nin-1];
        for(int j=0;j<Nin;j++)
        {
            point=in_vertex[j];
            if(insideVer(point)==true)
            {
                if(insideVer(update)==true)add_vertex(point);
                else
                {
                    interSec=intersection_point(update,point,i);
                    add_vertex(interSec);
                    add_vertex(point);
                }
            }
            else
            {
                if(insideVer(update)==true)
                {
                    interSec=intersection_point(update,point,i);
                    add_vertex(interSec);
                }
            }
            update=point;
        }
        in_vertex=out_vertex;
        Nin=Nout;
    }
    draw_polygon(out_vertex,4);
}

void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,100.0,0.0,100.0,0.0,100.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
void display(void)
{
    init();
    glColor3f(0.7f,0.0f,0.3f);
    draw_polygon(window,4);
    glColor3f(0.1f,0.7f,0.0f);
    draw_polygon(in_vertex,4);
    glColor3f(0,0,0);
    Sutherland_Hodgman(in_vertex,4);
    glFlush();
}
/*
Window:
20 10
20 80
80 80
80 10

Window to be clipped:
10 40
10 60
60 60
60 40
*/
int main(int argc,char *argv[])
{
    cout<<"Enter coordinates for rectangular clipping window"<<endl;
    for(int i=0;i<4;i++)cin>>window[i].x>>window[i].y;

    cout<<"Enter coordinates for rectangular window to be clipped"<<endl;
    for(int i=0;i<4;i++)cin>>in_vertex[i].x>>in_vertex[i].y;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Sutherland_Hodgman");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
