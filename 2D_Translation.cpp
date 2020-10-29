#include<bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

int x,y,edges;
vector<pair<int,int>>point;
int transX, transY;


void draw_original_polygon()  //Drawing Original Polygon
{
  glBegin(GL_POLYGON);
  glColor3f(0.5, 0.0, 0.1); //Maroonish_red colour
  for (int i = 0; i < edges; i++)
  {
    glVertex2i(point[i].first, point[i].second);
  }
  glEnd();
}

void draw_translated_polygon(int x, int y) //Drawing translated polygon
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color
  for (int i = 0; i < edges; i++)
  {
    glVertex2i(point[i].first + x, point[i].second + y);
  }
  glEnd();
}

void myInit(void)
{
  glClearColor(0, 0,0,0);
  glColor3f(1,1,1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-500,500,-500,500);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 1, 1);
  draw_original_polygon();
  draw_translated_polygon(transX, transY);
  glFlush();
}

int main(int argc, char** argv)
{
  cout <<"No of edges: ";
  cin >> edges;

  cout << "Coordinates of vertices: "<<endl;
  for (int i=0;i<edges;i++)
  {
    cin>>x>>y;
    point.push_back({x,y});
  }

  cout <<"Translation factor for X and Y: ";
  cin >> transX >> transY;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Translation");
  glutDisplayFunc(display);
  myInit();
  glutMainLoop();
}
