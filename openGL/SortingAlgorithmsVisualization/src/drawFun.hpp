#ifndef FFE8A2D8_8B35_42E8_9986_B1894C695901
#define FFE8A2D8_8B35_42E8_9986_B1894C695901
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

namespace draw
{
    /*Rectangle class*/
    class Rectangle
    {
    private:
        /* data */
        GLdouble x1, y1, x2, y2;
        GLint red = 100, green = 100, blue = 100;
    public:
        /* Constructors */
        Rectangle(GLdouble _x1, GLdouble _y1, GLdouble _x2,GLdouble _y2): x1(_x1), y1(_y1), x2(_x2), y2(_y2) {};
        Rectangle(GLdouble _x1, GLdouble height, GLdouble width);
        Rectangle(GLdouble _x1, GLdouble _y1, GLdouble _x2,GLdouble _y2, GLint r, GLint g, GLint b): x1(_x1), y1(_y1), x2(_x2), y2(_y2), red(r), green(g), blue(b) {};
        /* Destructor */ 
        ~Rectangle() {};

        /* Custom functions */
        void Draw();
        void ChangeSize(GLdouble _x1, GLdouble _y1, GLdouble _x2,GLdouble _y2);
    };
    
    

    
    
}
#endif /* FFE8A2D8_8B35_42E8_9986_B1894C695901 */