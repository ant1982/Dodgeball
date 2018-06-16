#include "Camera.h"
#include "Constants.h"
#include <math.h>
#include "../gl/glut.h"
#include <iostream>
using namespace::std;

static Camera* instance = 0;
static float moveSpeed = 1.0f;
static float lookSpeed = 0.1f;


Camera::Camera()
{

}

Camera:: ~Camera()
{


}

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}
	return instance;
}

void Camera::Update(float deltaTime, SDL_Event e)
{
	//forward vector : spherical coordinates to Cartesian coordinates
	//converstion (also known as the look direction)
	forward = Vector3D(
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch * cos(yaw)));

	//right vector
	right = Vector3D(sin(yaw - 3.14f / 2.0f),
		0,
		cos(yaw - 3.14f / 2.0f));

	//up vector : perpendicular to both foward and right, calculate using
	//dot product
	up = Vector3D((right.y * forward.z) - (right.z*forward.y),
		(right.z*forward.x) - (right.x*forward.z),
		(right.x*forward.y) - (right.y*forward.x));

	//event handler
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{

		//case SDLK_w:
		//	position += forward * moveSpeed;			
		//	break;

		//case SDLK_s:
		//	position -= forward * moveSpeed;
		//	break;

		//case SDLK_d:
		//	position += right * moveSpeed;
		//	break;
		//case SDLK_a:
		//	position -= right * moveSpeed;
		//	break;

		//case SDLK_UP:
		//	pitch -= lookSpeed;
		//	break;

		//case SDLK_DOWN:
		//	pitch += lookSpeed;
		//	break;

		//case SDLK_LEFT:					
		//	yaw -= lookSpeed;
		//	break;

		//case SDLK_RIGHT:
		//	yaw += lookSpeed;
		//	break;

		case SDLK_k:
				cout << pitch;
				cout << yaw << endl;
				cout << "X position is: " << position.x << endl;
				cout << "Y position is: " << position.y << endl;
				cout << "Z position is: " << position.z << endl;
				break;
			
		default:
			break;

		}
	}
	//if (pitch > 90)
	//{
	//	pitch = 90;
	//}
	//if (pitch < -90)
	//{
	//	pitch = -90;
	//}

	//glRotatef(-yaw, 0.0, 1.0, 0.0);
}

void Camera::Render()
{
	Vector3D lookatPos = position + forward; // make sure were always looking at the
											 //point infront of the camera
	/*lookatPos.y - rotation;*/
	glLoadIdentity();
	/*glTranslatef(position.x, position.y,position.z);*/
	/*glRotatef(-yaw, 0, 1, 0);*/	
	gluLookAt(position.x, position.y, position.z, lookatPos.x, lookatPos.y, lookatPos.z, up.x, up.y, up.z);	
	/*forward = lookatPos;*/
	
}

void Camera::RotateCamera(float axis, float angleAmount) {

	float radian = (yaw + angleAmount) * 3.14f/180;
	position.x -= sin(radian) * axis;
	position.z -= cos(radian) * axis;
}