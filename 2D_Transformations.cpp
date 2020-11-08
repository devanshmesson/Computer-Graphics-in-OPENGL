#include<bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

int x,y,edges,choice,angle,direction;
int plot_x,plot_y;
vector<pair<int,int>>point;
int transX, transY,Sx,Sy,slope,c,shx,shy;
char reflex,shear;


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
void draw_rotated_polygon()
{
    /*
    Test case:
    100 0
    300 0
    200 100
    */
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.4, 0.75); //Blue color

    //Rotate every vertex of the figure
    for(auto z:point)
    {
      int x=z.first,y=z.second;

      if(direction==2)  //Clockwise direction
      {
        plot_x=x*cos(angle) + y*sin(angle);
        plot_y=x*sin(angle) + y*cos(angle);
      }
      else if(direction==1) //Anti-clockwise direction
      {
        plot_x=x*cos(angle) - y*sin(angle);
        plot_y=x*sin(angle) + y*cos(angle);
      }
      glVertex2f(plot_x,plot_y);

    }
  glEnd();

}

void draw_scaled_polygon()
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color

  //Scale every vertex of the figure
    for(auto z:point)
    {
      int x=z.first,y=z.second;
      glVertex2f(x*Sx,y*Sy);
    }

  glEnd();
}

void draw_reflected_about_axis_polygon()
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color
  //Reflect every vertex of the figure
    for(auto z:point)
    {
      int x=z.first,y=z.second;
      if(reflex=='x')glVertex2f(x,y*(-1));
      else if(reflex=='y')glVertex2f(x*(-1),y);
    }

  glEnd();
}

void draw_reflected_about_line_polygon()
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color
  //Reflect every vertex of the figure
    for(auto z:point)
    {
      int x=z.first,y=z.second;

      int m00=(1-slope*slope)/(1+slope*slope);
      int m01=(2*slope)/(1+slope*slope);
      int m02=((-2)*c*slope)/(1+(slope*slope));
      int m10=(2*slope)/(1+slope*slope);
	  int m11=((slope*slope)-1)/(1+(slope*slope));
	  int m12=(2*c)/(1+(slope*slope));

      plot_x=(x*m00)+(y*m01)+m02;
      plot_y=(x*m10)+(y*m11)+m12;

      glVertex2f(plot_x,plot_y);
    }

  glEnd();
}
void draw_sheared_polygon()
{
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.4, 0.75); //Blue color
  //Shear every vertex of the figure
    for(auto z:point)
    {
      int x=z.first,y=z.second;

      if(shear=='x')
      {
      plot_x=x+(y*shx);
      plot_y=y;
      }
      else if(shear=='y')
      {
        plot_x=x;
        plot_y=y+(shy*x);
      }

      glVertex2f(plot_x,plot_y);
    }
  glEnd();

}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 1, 1);
  draw_original_polygon();
  if(choice==1) draw_translated_polygon(transX, transY);
  else if(choice==2)draw_rotated_polygon();
  else if(choice==3)draw_scaled_polygon();
  else if(choice==4)draw_reflected_about_axis_polygon();
  else if(choice==5)draw_reflected_about_line_polygon();
  else if(choice==6)draw_sheared_polygon();
  glFlush();
}




int main(int argc, char** argv)
{
  cout<<"1.Translation"<<endl;
  cout<<"2.Rotation"<<endl;
  cout<<"3.Scaling"<<endl;
  cout<<"4.Reflection about x or y axis"<<endl;
  cout<<"5.Reflection about a line y=mx+c"<<endl;
  cout<<"6.Shearing"<<endl;
  cin>>choice;
  if(choice==1)
  {
      cout <<"Translation factor for X and Y: ";
      cin >> transX >> transY;
  }
  else if(choice==2)
  {
      cout<<"1.Anticlockwise"<<endl;
      cout<<"2.Clockwise"<<endl;
      cout<<"Enter Choice:";
      cin>>direction;
      cout<<endl;
      cout<<"Enter Rotation Angle:";
      cin>>angle;
      cout<<endl;
  }
  else if(choice==3)
  {
    cout<<"Scaling factor for x-axis:";
    cin>>Sx;
    cout<<endl;
    cout<<"Scaling factor for y-axis:";
    cin>>Sy;
    cout<<endl;
  }
  else if(choice==4)
  {
    cout<<"Press 'x' for Reflection about x-axis and Press 'y' for Reflection about y-axis "<<endl;
    cin>>reflex;
  }
  else if(choice==5)
  {
      cout<<"Enter value of slope"<<endl;
      cin>>slope;
      cout<<"Enter y-intercept"<<endl;
      cin>>c;
  }
  else if(choice==6)
  {
     cout<<"Press 'x' for shearing about x-axis and Press 'y' for shearing about y-axis "<<endl;
    cin>>shear;
    if(shear=='x')
    {
    cout<<"Shearing parameter towards X direction:";
    cin>>shx;
    }
    else if(shear=='y')
    {
    cout<<"Shearing parameter towards Y direction";
    cin>>shy;
    }
    cout<<endl;
  }

  cout <<"No of edges: ";
  cin >> edges;

  cout << "Coordinates of vertices: "<<endl;
  for (int i=0;i<edges;i++)
  {
    cin>>x>>y;
    point.push_back({x,y});
  }


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Translation");
  glutDisplayFunc(display);
  myInit();
  glutMainLoop();
}
