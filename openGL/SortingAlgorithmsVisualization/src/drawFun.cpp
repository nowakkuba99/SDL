#include "drawFun.hpp"

/* ------------ Rectangle class Functions ------------ */
void draw::Rectangle::Draw()
{
    glColor3b(red,green,blue);
    glRectd(x1,y1,x2,y2);
}

void draw::Rectangle::ChangeSize(GLdouble _x1, GLdouble _y1, GLdouble _x2,GLdouble _y2)
{
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
}