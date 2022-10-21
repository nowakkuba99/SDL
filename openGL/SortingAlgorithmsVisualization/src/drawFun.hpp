#ifndef FFE8A2D8_8B35_42E8_9986_B1894C695901
#define FFE8A2D8_8B35_42E8_9986_B1894C695901
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include "settings.hpp"

namespace draw
{
    //const float constWidth = 2.0/50/2;
    /*Rectangle class*/
    class Rectangle
    {
    public:
        /* data */
        GLdouble x1, y1, x2, y2;
        GLint red = 169, green = 169, blue = 169;
    public:
        /* Constructors */
        Rectangle(GLdouble _x1, GLdouble _y1, GLdouble _x2,GLdouble _y2): x1(_x1), y1(_y1), x2(_x2), y2(_y2) {};
        Rectangle(GLdouble _x1, GLdouble height, GLdouble width);
        Rectangle(GLdouble _x1, GLdouble height);
        Rectangle(GLdouble _x1, GLdouble _y1, GLdouble _x2,GLdouble _y2, GLint r, GLint g, GLint b): x1(_x1), y1(_y1), x2(_x2), y2(_y2), red(r), green(g), blue(b) {};
        /* Destructor */ 
        ~Rectangle() {};

        /* Custom functions */
        void Draw();
        void ChangeSize(GLdouble _x1, GLdouble _y1, GLdouble _x2,GLdouble _y2);
        void Clear();
        void ChangeColor(GLint r, GLint g, GLint b)
        {
            red = r;
            green = g;
            blue = b;
        }
    };
    
    

    
    
}
#endif /* FFE8A2D8_8B35_42E8_9986_B1894C695901 */
