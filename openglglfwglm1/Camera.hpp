#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSETIVITY = 0.1f;
const float ZOOM = 45.0f;



class Camera
{
public:

	enum class Camera_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		SPACE
	};


	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	glm::vec3 SpaceUP;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensetivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch=PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensetivity(SENSETIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	Camera(float posX, float PosY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensetivity(SENSETIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, PosY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		SpaceUP = glm::vec3(posX, PosY, posZ);
		Yaw = yaw;
		updateCameraVectors();
	}
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
private:
	void updateCameraVectors();
};
#endif // !CAMERA_HPP



