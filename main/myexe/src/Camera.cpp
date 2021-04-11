#include "../include/Camera.hpp"

Camera::Camera(const glm::vec3 position, const glm::vec3 up, const float yaw, const float pitch)
    : m_Position(position)
    , m_Front(FRONT_DEFAULT)
    , m_WorldUp(up)
    , m_Yaw (yaw)
    , m_Pitch (pitch)
    , m_MovementSpeed(SPEED_DEFAULT)
    , m_MouseSensitivity(SENSITIVITY_DEFAULT)
    , m_Zoom(ZOOM_DEFAULT)
{
    UpdateCameraVectors();
}

Camera::Camera(const float posX, const float posY, const float posZ, const float upX, const float upY, const float upZ, 
    const float yaw, const float pitch)
    : m_Position(glm::vec3(posX, posY, posZ))
    , m_Front(FRONT_DEFAULT)
    , m_WorldUp(glm::vec3(upX, upY, upZ))
    , m_Yaw(yaw)
    , m_Pitch(pitch)
    , m_MovementSpeed(SPEED_DEFAULT)
    , m_MouseSensitivity(SENSITIVITY_DEFAULT)
    , m_Zoom(ZOOM_DEFAULT)
{
    UpdateCameraVectors();
}

float Camera::GetZoom() const
{
    return m_Zoom;
}

glm::mat4 Camera::GetViewMatrix() const
{ 
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up); 
}

void Camera::ProcessKeyboard(const Camera_Movement& direction, const float deltaTime)
{
    const float velocity = m_MovementSpeed * deltaTime;
    switch (direction)
    {
        case Camera_Movement::FORWARD: 
        {
            m_Position += m_Front * velocity;
            break;
        }
        case Camera_Movement::BACKWARD:
        {
            m_Position -= m_Front * velocity;
            break;
        }
        case Camera_Movement::LEFT:
        {
            m_Position -= m_Right * velocity;
            break;
        }
        case Camera_Movement::RIGHT: 
        {
            m_Position += m_Right * velocity;
            break;
        } 
    }
}

void Camera::ProcessMouseMovement(const float xoffset, const float yoffset, const GLboolean constrainPitch)
{
    m_Yaw += (xoffset * m_MouseSensitivity);
    m_Yaw = glm::mod(m_Yaw, 360.0f);
    m_Pitch += (yoffset * m_MouseSensitivity);

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_Pitch > 89.0f) m_Pitch = 89.0f;
        if (m_Pitch < -89.0f) m_Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(const float yoffset)
{
    m_Zoom -= yoffset;
    if (m_Zoom < 1.0f)
    {
        m_Zoom = 1.0f;
    }
    if (m_Zoom > 45.0f)
    {
        m_Zoom = 45.0f;
    }
}

void Camera::UpdateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    m_Right = glm::normalize(glm::cross( m_Front, m_WorldUp)); // normalize the vectors, because their length gets closer to 0 the more
                                                               // you look up or down which results in slower movement.
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}