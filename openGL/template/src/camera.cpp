/* Input class header file */
#include "camera.hpp"

/* Function bodies */

/* 
Returns the view matrix of current camera setUp
Arguments: -
Returns glm::mat4 View Matrix
*/
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

/*
Function updates vectors based on the input from keyboard
Arguments: direction (ENUM: FORWARD/BACKWARD/LEFT/RIGHT), deltaTime of frames
Returns: -
*/
void Camera::processKeyboardAction(camera::cameraMovement direction, float deltaTime)
{
    const float cameraSpeed = 2.5f * deltaTime;
    if(direction == camera::FORAWRD)
    {
        m_Position += cameraSpeed * m_Front;
    }
    
    if(direction == camera::BACKWARD)
    {
        m_Position -= cameraSpeed * m_Front;
    }

    if(direction == camera::LEFT)
    {
        m_Position -= m_Right * cameraSpeed;
    }

    if(direction == camera::RIGHT)
    {
        m_Position += m_Right * cameraSpeed;
    }
}

/*
Function updates vectors based on input from the mouse.
Arguments: xOffSet, yOffset, limitPitch - if to limit pitch to -90/90 deg
Returns: -
*/
void Camera::processMouseAction(float xOffset, float yOffset, bool limitPitch)
{
    xOffset*=m_MouseSensitivity;
    yOffset*=m_MouseSensitivity;

    m_Yaw+=xOffset;
    m_Pitch+=yOffset;

    if(m_Pitch > 89.0f)
    m_Pitch =  89.0f;
    if(m_Pitch < -89.0f)
    m_Pitch = -89.0f;

    updateCameraVectors();  //Update vectors with new pitch and yaw angles
}

/*
Function processes scroll action - Updates public zoom variable
Arguments: yOffset
Returns: -
*/
void Camera::processScrollAction(float yOffset)
{
    m_Zoom-= (float)yOffset;
    if(m_Zoom<1.0f)
        m_Zoom=1.0f;
    else if(m_Zoom >45.0f)
        m_Zoom=45.0f;
}
/*
Function updates Camera class member vector variables
Arguments: -
Returns: -
 */
void Camera::updateCameraVectors()
{
    //Recalculate front vector
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(direction);
    //Recalculate right and up vectors
    m_Right = glm::normalize(glm::cross(m_Front,m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right,m_Front));
}