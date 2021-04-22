#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from
// window-system specific input methods
enum class Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const glm::vec3 FRONT_DEFAULT = glm::vec3(0.0f, 0.0f, -1.0f);
constexpr float YAW_DEFAULT = -90.0f;
constexpr float PITCH_DEFAULT = 0.0f;
constexpr float SPEED_DEFAULT = 2.5f;
constexpr float SENSITIVITY_DEFAULT = 0.1f;
constexpr float ZOOM_DEFAULT = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles,
// Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // constructor with vectors
    Camera(const glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
        const float yaw = YAW_DEFAULT, const float pitch = PITCH_DEFAULT);

    // constructor with scalar values
    Camera(const float posX, const float posY, const float posZ, const float upX, const float upY, const float upZ, 
        const float yaw, const float pitch);

    float GetZoom() const;

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const;

    // processes input received from any keyboard-like input system. Accepts input parameter in the
    // form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(const Camera_Movement& direction, const float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x
    // and y direction.
    void ProcessMouseMovement(const float xoffset, const float yoffset, const GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical
    // wheel-axis
    void ProcessMouseScroll(const float yoffset);

    glm::vec3 GetPos() const { return m_Position; }

private:
    // camera Attributes
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;
    // euler Angles
    float m_Yaw;
    float m_Pitch;
    // camera options
    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;

    // calculates the front vector from the Camera's (updated) Euler Angles
    void UpdateCameraVectors();
};
#endif
