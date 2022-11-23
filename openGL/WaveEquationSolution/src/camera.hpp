#ifndef CAMERA_H
#define CAMERA_H

/* Include openGL math functions */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Other includes */
#include <vector>

/* Variables */
namespace camera
{
    // Enum to store camera movement options
    enum cameraMovement {
        FORAWRD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    // Default camera values
    const float c_YAW         = -90.0f;
    const float c_PITCH       =  0.0f;
    const float c_SPEED       =  2.5f;
    const float c_SENSITIVITY =  0.1f;
    const float c_ZOOM        =  45.0f;
}
/* Camera Class */
class Camera
{
public:
    /* Variables */

    //Camera attributes
    glm::vec3 m_Position;       //m_VarName -> Member variable | s_VarName -> Static | c_VarName -> Const
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;
    //Euler angles
    float m_Yaw;
    float m_Pitch;
    //Movement settings
    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;

    /* Constructors */
    //Constructor with vectors and default values
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),float yaw = camera::c_YAW, float pitch = camera::c_PITCH): m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(camera::c_SPEED), m_MouseSensitivity(camera::c_SENSITIVITY), m_Zoom(camera::c_ZOOM)
    {
        m_Position = position;
        m_WorldUp = worldUp;
        m_Yaw = yaw; 
        m_Pitch = pitch;
        updateCameraVectors();
    }
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(camera::c_SPEED), m_MouseSensitivity(camera::c_SENSITIVITY), m_Zoom(camera::c_ZOOM)
    {
        m_Position = glm::vec3(posX, posY, posZ);
        m_WorldUp = glm::vec3(upX, upY, upZ);
        m_Yaw = yaw;
        m_Pitch = pitch;
        updateCameraVectors();
    }

    /* Function Definitions */
    //Return the view matrix
    glm::mat4 getViewMatrix();  
    //Updates vectors based on the input from keyboard
    void processKeyboardAction(camera::cameraMovement direction, float deltaTime);  
    //Updates vectors based oninput from the mouse
    void processMouseAction(float xOffset, float yOffset, bool limitPitch = true);
    //Process scroll action
    void processScrollAction(float yOffset);
private:
    //Function to update camera vectors after changes by user
    void updateCameraVectors();

};


#endif /* CAMERA_H */
