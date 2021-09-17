#include "MovablePerspCamera.hpp"

#include "Input.hpp"

MovablePerspCamera::MovablePerspCamera(float fov, float aspectRatio, float near, float far)
    :m_currentRotation(Quaternion::identity()), m_xAngle(0.0f), m_yAngle(0.0f)
{
	m_projection = Mat4x4::perspective(fov, aspectRatio, near, far);
}

Mat4x4 MovablePerspCamera::getMatrix() const
{
    //return m_projection * Mat4x4::lookAt(m_position, m_position - getFront(), Vector3(0.0f, 1.0f, 0.0f));
    return m_projection * getInvTransform();
}

void MovablePerspCamera::update(float dTime)
{
    float cameraSpeed = 10.0f * dTime;
    float cameraRotationSpeed = 0.8f * dTime;

    Vector2 mouseMovement = Input::getMouseMovement();
    m_yAngle -= mouseMovement.x * cameraRotationSpeed;
    m_xAngle += mouseMovement.y * cameraRotationSpeed;

    float maxAngle = 88.0f / 180.0f * 3.1415f;
    if (m_xAngle > maxAngle)
        m_xAngle = maxAngle;
    if (m_xAngle < -maxAngle)
        m_xAngle = -maxAngle;

    Quaternion destRotation = Quaternion::identity();
    destRotation *= Quaternion(Vector3(0.0f, 1.0f, 0.0f), m_yAngle);
    
    Vector3 right = -destRotation.rotate(Vector3(1.0f, 0.0f, 0.0f));
    Vector3 front = -destRotation.rotate(Vector3(0.0f, 0.0f, 1.0f));

    if (Input::isButtonPressed(KEY::W))
        move(front * cameraSpeed);
    if (Input::isButtonPressed(KEY::S))
        move(-front * cameraSpeed);
    if (Input::isButtonPressed(KEY::A))
        move(right * cameraSpeed);
    if (Input::isButtonPressed(KEY::D))
        move(-right * cameraSpeed);
    if (Input::isButtonPressed(KEY::SPACE))
        move(Vector3(0.0f, cameraSpeed, 0.0f));
    if (Input::isButtonPressed(KEY::LSHIFT))
        move(Vector3(0.0f, -cameraSpeed, 0.0f));

    destRotation *= Quaternion(Vector3(1.0f, 0.0f, 0.0f), m_xAngle);

    m_currentRotation = m_currentRotation.lerp(destRotation, 0.8f);

    setRotation(m_currentRotation);
}
