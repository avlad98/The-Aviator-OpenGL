#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include "LabCamera.h"

enum Object { FUEL, ASTEROID };

typedef struct {
	glm::vec3 coord;
	glm::vec3 color;
	float angle;
	float leftLimit;
	float rightLimit;
	float dir;
}MiniCloud;

typedef struct {
	MiniCloud miniCloud[4];
	glm::vec3 scale;
	float angle;
	float speed;
}Cloud;

typedef struct {
	glm::vec3 coord;
	glm::vec3 color;
	float angle;
	float speed;
	float dir;
	float scale;
}Asteroid;

typedef struct {
	glm::vec3 coord;
	glm::vec3 color;
	float angle;
	float dir;
}Fuel;

typedef struct {
	Fuel miniFuels[6];
	glm::vec3 scale;
	float angle;
	float speed;
} FuelString;

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	bool collide(float planeX, float planeY, Object obj);
	void FrameEnd() override;

	void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color = glm::vec3(1));
	Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	inline glm::mat4 RotateOZ(float radians)
	{
		return glm::transpose(glm::mat4(
			1, 0, 0, 0,
			0, cos(radians), -sin(radians), 0,
			0, sin(radians), cos(radians), 0,
			0, 0, 0, 1
		));
	}

protected:
	MyCamera::Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	bool isOrtoActive = false;
	float left = -3.0f;
	float right = 3.0f;
	float top = 3.0f;
	float bottom = -3.0f;
	float fovAngle = 60.0f;


	glm::vec3 waterColor = glm::vec3(0, 0, 1);
	glm::vec3 waterScale = glm::vec3(0.9, 0.9, 5);
	float waterAngle = 0;
	float waterLevel = 1.25;

	float planeScale = 0.05;
	float planeY = 1.25;
	float planeX = -0.4;
	float accX = 0;
	float propSpeed = 500;
	float propAngle = 0;
	float planeAngleX = 0;
	float planeAngleZ = 0;
	float planeSpeed = 20;
	float xTilt = 15;
	float zTilt = 100;
	float xDir = 1;
	float zDir = 1;

	static const int numberOfClouds = 30;
	Cloud* clouds[numberOfClouds];

	static const int numberOfAsteroids = 5;
	Asteroid* asteroids[numberOfAsteroids];

	static const int numberOfFuels = 5;
	FuelString* fuels[numberOfFuels];

	bool gameEnding = false;
	bool pause = false;

	int lives = 3;
	float fuel = 100;
	float fuelConsumption = 10;
	float fuelAddition = 4;
	glm::vec3 fuelPos = glm::vec3(1.2, 1.7, 0);
	glm::vec3 blackScale = glm::vec3(0.2, 0.05, 0);
	glm::vec3 fuelScale = blackScale;

	float score = 0;
	float speedLevel = 0;
	bool speedIncreased = false;

	float backingSpeed = 0;

	bool FPV = false;

};
