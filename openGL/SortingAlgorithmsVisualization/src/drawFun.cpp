#include "drawFun.hpp"
#include <iostream>
/* ------------ Rectangle class Functions ------------ */
void draw::Rectangle::Draw()
{
    glColor3d(red*(0.0039),green*(0.0039),blue*(0.0039));
    glRectd(x1,y1,x2,y2);
}

void draw::Rectangle::Clear()
{
    glColor3d(0,0,0);
    glRectd(x1,y1,x2,y2);
}

void draw::Rectangle::ChangeSize(GLdouble _x1, GLdouble _y1, GLdouble _x2,GLdouble _y2)
{
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
}

draw::Rectangle::Rectangle(GLdouble _x1, GLdouble height, GLdouble width)
{
    x1 = _x1;
    x2 = _x1 + width;
    y1 = -1;
    y2 = height;
    std::cout<<x1<<" "<<x2<<" "<<y1<<" "<<y2;
}

draw::Rectangle::Rectangle(GLdouble _x1, GLdouble height)
{
    x1 = _x1;
    x2 = _x1 + sett::constWidth;
    y1 = -1;
    y2 = height;
}