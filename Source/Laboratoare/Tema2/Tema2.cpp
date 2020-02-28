#include "Tema2.h"

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	srand(time(NULL));

	renderCameraTarget = false;

	camera = new MyCamera::Camera();
	camera->Set(glm::vec3(0, 1, 1.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	// Water cilinder
	{
		vector<VertexFormat> vertices;
		vector<unsigned short> indices;

		int circles = 20;
		int points = 360;

		glm::vec3 coordOffset = glm::vec3(0, 0, -circles * 0.1 * 0.5);

		for (int z = 0; z < circles; z++) {
			float zOffset = z * 0.1;

			for (int i = 0; i < points; i++) {
				float randomX = (rand() % 2000 - 1000) * 0.001;
				float randomY = (rand() % 500 - 250) * 0.01;

				glm::vec3 coord = glm::vec3(cos(i), sin(i), zOffset) + coordOffset;
				glm::vec3 color = glm::vec3(0);
				glm::vec3 normal = glm::vec3(randomX, randomY, 0);
				vertices.push_back(VertexFormat(coord, color, normal));
			}
		}


		for (int z = 0; z < circles; z++) {
			float zOffset = z * 0.1;


			for (int i = 1; i < points; i++) {
				indices.push_back(z * points + i);
				indices.push_back(z * points + i - 1);
				indices.push_back((z+1) * points + i - 1);
				
				indices.push_back(z * points + i);
				indices.push_back((z + 1) * points + i - 1);
				indices.push_back((z + 1) * points + i);
			}
		}

		CreateMesh("water", vertices, indices);
	}

	// Simple square
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0,  0),		glm::vec3(0)),
			VertexFormat(glm::vec3(1, 0,  0),		glm::vec3(0)),
			VertexFormat(glm::vec3(1, 1,  1),		glm::vec3(0)),
			VertexFormat(glm::vec3(0, 1,  0),		glm::vec3(0)),

		};

		vector<unsigned short> indices =
		{ 0, 1, 2,
			0, 2, 3};

		CreateMesh("square", vertices, indices);
	}

	// Simple cube mesh
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1),		glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, -1,  1),		glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(-1,  1,  1),		glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(1,  1,  1),		glm::vec3(0, 1, 0)),
			VertexFormat(glm::vec3(-1, -1, -1),		glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(1, -1, -1),		glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-1,  1, -1),		glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(1,  1, -1),		glm::vec3(0, 0, 1)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube", vertices, indices);
	}

	// Fuel
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1),		glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, -1,  1),		glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(-1,  1,  1),		glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(1,  1,  1),		glm::vec3(0, 1, 0)),
			VertexFormat(glm::vec3(-1, -1, -1),		glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(1, -1, -1),		glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-1,  1, -1),		glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(1,  1, -1),		glm::vec3(0, 0, 1)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube", vertices, indices);
	}

	// Plane mesh
	glm::vec3 xOffset = glm::vec3(-1.6, 0, 0);
	{
		glm::vec3 ofssetX = glm::vec3(0);

		// Body
		vector<VertexFormat> vertices;
		vector<unsigned short> indices;
		vector<VertexFormat> body_vertices
		{
			VertexFormat(glm::vec3(-0.5, -0.5,  0.5)	+ xOffset,	glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(	2, -1,  1)			+ xOffset,	glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-0.5,  0.5,  0.5)	+ xOffset,	glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(	2,  1,  1)			+ xOffset,	glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-0.5, -0.5, -0.5)	+ xOffset,	glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(	2, -1, -1)			+ xOffset,	glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-0.5,  0.5, -0.5)	+ xOffset,	glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(	2,  1, -1)			+ xOffset,	glm::vec3(1, 0, 0)),
		};

		vector<unsigned short> body_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		// Front
		vector<VertexFormat> front_vertices
		{
			VertexFormat(glm::vec3(	2, -1,  1) + xOffset,		glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(2.7, -1,  1) + xOffset,	glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(	2,  1,  1) + xOffset,		glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(2.7,  1,  1) + xOffset,	glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(	2, -1, -1) + xOffset,		glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(2.7, -1, -1) + xOffset,	glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(	2,  1, -1) + xOffset,		glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(2.7,  1, -1) + xOffset,	glm::vec3(1, 1, 0)),
		};

		vector<unsigned short> front_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < front_indices.size(); ++i)
			front_indices[i] += body_vertices.size() * 1;

		// Axle
		vector<VertexFormat> axle_vertices
		{
			VertexFormat(glm::vec3(2.7, -0.2,  0.2) + xOffset,	glm::vec3(1, 0.6, 0.1)),
			VertexFormat(glm::vec3(	3 , -0.2,  0.2) + xOffset,	glm::vec3(1, 0.6, 0.1)),
			VertexFormat(glm::vec3(2.7,  0.2,  0.2) + xOffset,	glm::vec3(1, 0.6, 0.1)),
			VertexFormat(glm::vec3( 3 ,  0.2,  0.2) + xOffset,	glm::vec3(1, 0.6, 0.1)),
			VertexFormat(glm::vec3(2.7, -0.2, -0.2) + xOffset,	glm::vec3(1, 0.6, 0.1)),
			VertexFormat(glm::vec3( 3 , -0.2, -0.2) + xOffset,	glm::vec3(1, 0.6, 0.1)),
			VertexFormat(glm::vec3(2.7,  0.2, -0.2) + xOffset,	glm::vec3(1, 0.6, 0.1)),
			VertexFormat(glm::vec3( 3 ,  0.2, -0.2) + xOffset,	glm::vec3(1, 0.6, 0.1)),
		};

		vector<unsigned short> axle_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < axle_indices.size(); ++i)
			axle_indices[i] += body_vertices.size() * 2;

		// Front Wings
		vector<VertexFormat> wings_vertices
		{
			VertexFormat(glm::vec3(0,	-0.05,  2) + xOffset,	glm::vec3(0.75)),
			VertexFormat(glm::vec3(1.5, -0.2,  2) + xOffset,	glm::vec3(0.9)),
			VertexFormat(glm::vec3(0,	0.05,   2) + xOffset,	glm::vec3(0.75)),
			VertexFormat(glm::vec3(1.5,  0.2,  2) + xOffset,	glm::vec3(0.9)),
			VertexFormat(glm::vec3(0,	-0.05, -2) + xOffset,	glm::vec3(0.75)),
			VertexFormat(glm::vec3(1.5, -0.2, -2) + xOffset,	glm::vec3(0.9)),
			VertexFormat(glm::vec3(0,	0.05,  -2) + xOffset,	glm::vec3(0.75)),
			VertexFormat(glm::vec3(1.5,  0.2, -2) + xOffset,	glm::vec3(0.9)),
		};

		vector<unsigned short> wings_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < wings_indices.size(); ++i)
			wings_indices[i] += body_vertices.size() * 3;

		// Back wing
		vector<VertexFormat> back_wing_vertices
		{
			VertexFormat(glm::vec3(-1,		0,  0.1)	+ xOffset,	glm::vec3(0.1)),
			VertexFormat(glm::vec3(-0.5,	0,  0.1)	+ xOffset,	glm::vec3(0.1)),
			VertexFormat(glm::vec3(-1,		1,  0.1)	+ xOffset,	glm::vec3(0.1)),
			VertexFormat(glm::vec3(-0.5,	1,  0.1)	+ xOffset,	glm::vec3(0.1)),
			VertexFormat(glm::vec3(-1,		0, -0.1)	+ xOffset,	glm::vec3(0.1)),
			VertexFormat(glm::vec3(-0.5,	0, -0.1)	+ xOffset,	glm::vec3(0.1)),
			VertexFormat(glm::vec3(-1,		1, -0.1)	+ xOffset,	glm::vec3(0.1)),
			VertexFormat(glm::vec3(-0.5,	1, -0.1)	+ xOffset,	glm::vec3(0.1)),
		};

		vector<unsigned short> back_wing_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < back_wing_indices.size(); ++i)
			back_wing_indices[i] += body_vertices.size() * 4;

		// Human body
		vector<VertexFormat> human_body_vertices
		{
			VertexFormat(glm::vec3(0,		0,		0.5) + xOffset,		glm::vec3(0.3, 0.2, 0.1)),
			VertexFormat(glm::vec3(1.5,		0,		0.5) + xOffset,		glm::vec3(0.3, 0.2, 0.1)),
			VertexFormat(glm::vec3(0,		1.2,	0.5) + xOffset,		glm::vec3(0.3, 0.2, 0.1)),
			VertexFormat(glm::vec3(1.5,		1.2,	0.5) + xOffset,		glm::vec3(0.3, 0.2, 0.1)),
			VertexFormat(glm::vec3(0,		0,		-0.5) + xOffset,	glm::vec3(0.3, 0.2, 0.1)),
			VertexFormat(glm::vec3(1.5,		0,		-0.5) + xOffset,	glm::vec3(0.3, 0.2, 0.1)),
			VertexFormat(glm::vec3(0,		1.2,	-0.5) + xOffset,	glm::vec3(0.3, 0.2, 0.1)),
			VertexFormat(glm::vec3(1.5,		1.2,	-0.5) + xOffset,	glm::vec3(0.3, 0.2, 0.1)),
		};

		vector<unsigned short> human_body_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < human_body_indices.size(); ++i)
			human_body_indices[i] += body_vertices.size() * 5;

		// Human head
		vector<VertexFormat> human_head_vertices
		{
			VertexFormat(glm::vec3(0.1,		1.2,	0.3) + xOffset,		glm::vec3(0.7, 1, 0.7)),
			VertexFormat(glm::vec3(1.3,		1.2,	0.3) + xOffset,		glm::vec3(0.7, 1, 0.7)),
			VertexFormat(glm::vec3(0.1,		1.8,	0.3) + xOffset,		glm::vec3(0.7, 1, 0.7)),
			VertexFormat(glm::vec3(1.3,		1.8,	0.3) + xOffset,		glm::vec3(0.7, 1, 0.7)),
			VertexFormat(glm::vec3(0.1,		1.2,	-0.3) + xOffset,	glm::vec3(0.7, 1, 0.7)),
			VertexFormat(glm::vec3(1.3,		1.2,	-0.3) + xOffset,	glm::vec3(0.7, 1, 0.7)),
			VertexFormat(glm::vec3(0.1,		1.8,	-0.3) + xOffset,	glm::vec3(0.7, 1, 0.7)),
			VertexFormat(glm::vec3(1.3,		1.8,	-0.3) + xOffset,	glm::vec3(0.7, 1, 0.7)),
		};

		vector<unsigned short> human_head_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < human_head_indices.size(); ++i)
			human_head_indices[i] += body_vertices.size() * 6;

		// Human hair
		vector<VertexFormat> human_hair_vertices
		{
			VertexFormat(glm::vec3(-0.1,		1.8,	0.5) + xOffset,		glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(1.35,		1.8,	0.5) + xOffset,		glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(-0.1,		1.9,	0.5) + xOffset,		glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(1.35,		1.9,	0.5) + xOffset,		glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(-0.1,		1.8,	-0.5) + xOffset,	glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(1.35,		1.8,	-0.5) + xOffset,	glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(-0.1,		1.9,	-0.5) + xOffset,	glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(1.35,		1.9,	-0.5) + xOffset,	glm::vec3(0.2, 0.1, 0)),
		};

		vector<unsigned short> human_hair_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < human_hair_indices.size(); ++i)
			human_hair_indices[i] += body_vertices.size() * 7;

		// Human back hair
		vector<VertexFormat> human_hair2_vertices
		{
			VertexFormat(glm::vec3(-0.1,	1.2,	0.5) + xOffset,		glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(0,		1.2,	0.5) + xOffset,		glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(-0.1,	1.8,	0.5) + xOffset,		glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(0,		1.8,	0.5) + xOffset,		glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(-0.1,	1.2,	-0.5) + xOffset,	glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(0,		1.2,	-0.5) + xOffset,	glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(-0.1,	1.8,	-0.5) + xOffset,	glm::vec3(0.2, 0.1, 0)),
			VertexFormat(glm::vec3(0,		1.8,	-0.5) + xOffset,	glm::vec3(0.2, 0.1, 0)),
		};

		vector<unsigned short> human_hair2_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < human_hair2_indices.size(); ++i)
			human_hair2_indices[i] += body_vertices.size() * 8;

		// Human eye 1
		vector<VertexFormat> human_eye1_vertices
		{
			VertexFormat(glm::vec3(1.2,		1.55,	-0.1) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.4,		1.55,	-0.1) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.2,		1.65,	-0.1) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.4,		1.65,	-0.1) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.2,		1.55,	-0.2) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.4,		1.55,	-0.2) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.2,		1.65,	-0.2) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.4,		1.65,	-0.2) + xOffset,		glm::vec3(0)),
		};

		vector<unsigned short> human_eye1_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < human_eye1_indices.size(); ++i)
			human_eye1_indices[i] += body_vertices.size() * 9;

		// Human eye 2
		vector<VertexFormat> human_eye2_vertices
		{
			VertexFormat(glm::vec3(1.2,		1.55,	0.1) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.4,		1.55,	0.1) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.2,		1.65,	0.1) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.4,		1.65,	0.1) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.2,		1.55,	0.2) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.4,		1.55,	0.2) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.2,		1.65,	0.2) + xOffset,		glm::vec3(0)),
			VertexFormat(glm::vec3(1.4,		1.65,	0.2) + xOffset,		glm::vec3(0)),
		};

		vector<unsigned short> human_eye2_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < human_eye2_indices.size(); ++i)
			human_eye2_indices[i] += body_vertices.size() * 10;

		// Human face
		vector<VertexFormat> human_face_vertices
		{
			VertexFormat(glm::vec3(1.2,		1.5,	0.35) + xOffset,	glm::vec3(1)),
			VertexFormat(glm::vec3(1.35,	1.5,	0.35) + xOffset,	glm::vec3(1)),
			VertexFormat(glm::vec3(1.2,		1.7,	0.35) + xOffset,	glm::vec3(1)),
			VertexFormat(glm::vec3(1.35,	1.7,	0.35) + xOffset,	glm::vec3(1)),
			VertexFormat(glm::vec3(1.2,		1.5,	-0.35) + xOffset,	glm::vec3(1)),
			VertexFormat(glm::vec3(1.35,	1.5,	-0.35) + xOffset,	glm::vec3(1)),
			VertexFormat(glm::vec3(1.2,		1.7,	-0.35) + xOffset,	glm::vec3(1)),
			VertexFormat(glm::vec3(1.35,	1.7,	-0.35) + xOffset,	glm::vec3(1)),
		};

		vector<unsigned short> human_face_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < human_face_indices.size(); ++i)
			human_face_indices[i] += body_vertices.size() * 11;




		vertices.insert(vertices.end(), body_vertices.begin(), body_vertices.end());
		indices.insert(indices.end(), body_indices.begin(), body_indices.end());

		vertices.insert(vertices.end(), front_vertices.begin(), front_vertices.end());
		indices.insert(indices.end(), front_indices.begin(), front_indices.end());

		vertices.insert(vertices.end(), axle_vertices.begin(), axle_vertices.end());
		indices.insert(indices.end(), axle_indices.begin(), axle_indices.end());

		vertices.insert(vertices.end(), wings_vertices.begin(), wings_vertices.end());
		indices.insert(indices.end(), wings_indices.begin(), wings_indices.end());

		vertices.insert(vertices.end(), back_wing_vertices.begin(), back_wing_vertices.end());
		indices.insert(indices.end(), back_wing_indices.begin(), back_wing_indices.end());

		vertices.insert(vertices.end(), human_body_vertices.begin(), human_body_vertices.end());
		indices.insert(indices.end(), human_body_indices.begin(), human_body_indices.end());

		vertices.insert(vertices.end(), human_head_vertices.begin(), human_head_vertices.end());
		indices.insert(indices.end(), human_head_indices.begin(), human_head_indices.end());

		vertices.insert(vertices.end(), human_hair_vertices.begin(), human_hair_vertices.end());
		indices.insert(indices.end(), human_hair_indices.begin(), human_hair_indices.end());

		vertices.insert(vertices.end(), human_hair2_vertices.begin(), human_hair2_vertices.end());
		indices.insert(indices.end(), human_hair2_indices.begin(), human_hair2_indices.end());

		vertices.insert(vertices.end(), human_eye1_vertices.begin(), human_eye1_vertices.end());
		indices.insert(indices.end(), human_eye1_indices.begin(), human_eye1_indices.end());

		vertices.insert(vertices.end(), human_eye2_vertices.begin(), human_eye2_vertices.end());
		indices.insert(indices.end(), human_eye2_indices.begin(), human_eye2_indices.end());

		vertices.insert(vertices.end(), human_face_vertices.begin(), human_face_vertices.end());
		indices.insert(indices.end(), human_face_indices.begin(), human_face_indices.end());


		CreateMesh("plane", vertices, indices);
	}

	// Propellers mesh
	{
		// Propeller 1
		vector<VertexFormat> vertices;
		vector<unsigned short> indices;
		vector<VertexFormat> prop1_vertices
		{
			VertexFormat(glm::vec3(	3,		-1.5,  0.2) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(	3.2,	-1.5,  0.2) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(	3,		 1.5,  0.2) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(	3.2,	 1.5,  0.2) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(	3,		-1.5, -0.2) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(	3.2,	-1.5, -0.2) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(	3,		 1.5, -0.2) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(	3.2,	 1.5, -0.2) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
		};

		vector<unsigned short> prop1_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		// Propeller 2
		vector<VertexFormat> prop2_vertices
		{
			VertexFormat(glm::vec3(3,		-0.2,  1.5) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(3.2,		-0.2,  1.5) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(3,		 0.2,  1.5) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(3.2,		 0.2,  1.5) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(3,		-0.2, -1.5) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(3.2,		-0.2, -1.5) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(3,		 0.2, -1.5) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
			VertexFormat(glm::vec3(3.2,		 0.2, -1.5) + xOffset,	glm::vec3(0.9, 0.5, 0.3)),
		};									

		vector<unsigned short> prop2_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < prop2_indices.size(); ++i)
			prop2_indices[i] += 8;

		// Cap
		vector<VertexFormat> cap_vertices
		{
			VertexFormat(glm::vec3(3.2,	-0.1,  0.1) + xOffset,	glm::vec3(0.3)),
			VertexFormat(glm::vec3(3.5,	-0.03,  0.03) + xOffset,	glm::vec3(0.7)),
			VertexFormat(glm::vec3(3.2,	 0.1,  0.1) + xOffset,	glm::vec3(0.3)),
			VertexFormat(glm::vec3(3.5,	 0.03,  0.03) + xOffset,	glm::vec3(0.7)),
			VertexFormat(glm::vec3(3.2,	-0.1, -0.1) + xOffset,	glm::vec3(0.3)),
			VertexFormat(glm::vec3(3.5,	-0.03, -0.03) + xOffset,	glm::vec3(0.7)),
			VertexFormat(glm::vec3(3.2,	 0.1, -0.1) + xOffset,	glm::vec3(0.3)),
			VertexFormat(glm::vec3(3.5,	 0.03, -0.03) + xOffset,	glm::vec3(0.7)),
		};

		vector<unsigned short> cap_indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		for (std::size_t i = 0; i < cap_indices.size(); ++i)
			cap_indices[i] += 16;


		vertices.insert(vertices.end(), prop1_vertices.begin(), prop1_vertices.end());
		indices.insert(indices.end(), prop1_indices.begin(), prop1_indices.end());

		vertices.insert(vertices.end(), prop2_vertices.begin(), prop2_vertices.end());
		indices.insert(indices.end(), prop2_indices.begin(), prop2_indices.end());

		vertices.insert(vertices.end(), cap_vertices.begin(), cap_vertices.end());
		indices.insert(indices.end(), cap_indices.begin(), cap_indices.end());

		CreateMesh("propellers", vertices, indices);
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	{
		Shader *shader = new Shader("WaterShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Water_VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Water_FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	
	{
		Shader *shader = new Shader("PlaneShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Plane_VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Plane_FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("CloudShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Clouds_VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Clouds_FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("ObjectShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Objects_VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Objects_FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("FuelShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Fuel_VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Fuel_FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Clouds
	for (int i = 0; i < numberOfClouds; i++) {
		Cloud* cloud = (Cloud*)malloc(sizeof(Cloud));
		if (!cloud) {
			cout << "Eroare alocare memorie" << endl;
			exit(-1);
		}

		cloud->speed = rand() % 2 + 2;
		cloud->angle = rand() % 360;
		cloud->scale = glm::vec3((rand() % 10 + 6) * 1.0f / 400.0f);

		float randomX = (rand() % 1000 + 1300) * 1.0f / 1000.0f;
		float randomZ = (rand() % 200 ) * -1.0f / 1000.0f;

		for (int j = 0; j < 4; j++) {
			if (j == 0) {cloud->miniCloud[j].coord = glm::vec3(randomX, 0, randomZ);}
			else {		cloud->miniCloud[j].coord = cloud->miniCloud[j-1].coord + cloud->scale * 0.3f;}

			cloud->miniCloud[j].color = glm::vec3(0.9);
			float brightness = (rand() % 200 - 20) * 1.0f / 1000.0f;
			cloud->miniCloud[j].color += glm::vec3(brightness);
			cloud->miniCloud[j].angle = rand() % 360;
			cloud->miniCloud[j].leftLimit = cloud->miniCloud[j].angle - 90;
			cloud->miniCloud[j].leftLimit = cloud->miniCloud[j].angle + 90;
			cloud->miniCloud[j].dir = rand() % 1;
		}

		clouds[i] = cloud;
	}

	// Asteroids
	for (int i = 0; i < numberOfAsteroids; i++) {
		Asteroid* asteroid = (Asteroid*)malloc(sizeof(Asteroid));
		if (!asteroid) {
			cout << "Eroare alocare memorie" << endl;
			exit(-1);
		}

		float brightness = (rand() % 400) * 1.0f / 1000.0f;
		float randomX = 1.5 + (rand() % 60) * 0.1f;
		float randomY = 1.2 + (rand() % 50) * 0.01f;

		asteroid->angle = 0;
		asteroid->color = glm::vec3(0.7, 0, 0);
		asteroid->color += glm::vec3(brightness);
		asteroid->coord = glm::vec3(randomX, randomY, 0);
		asteroid->dir = rand() % 1;
		asteroid->scale = (rand() % 30 + 50) * 1.0f / 1000.0f;
		asteroid->speed = 0.1 + (rand() % 5) * 0.01f;

		asteroids[i] = asteroid;
	}

	// Fuel
	for (int i = 0; i < numberOfFuels; i++) {
		FuelString* string = (FuelString*) malloc(sizeof(FuelString));
		if (!string) {
			cout << "Eroare alocare memorie" << endl;
			exit(-1);
		}

		string->scale = glm::vec3(0.07f);
		string->speed = 0.5 + (rand() % 10) * 0.05f;
		string->angle = rand() % 360;
		
		float randomX = 1.5 + (rand() % 60) * 0.1f;
		float randomY = 1.0 + (rand() % 50) * 0.01f;
		for (int j = 0; j < 6; j++) {
			if (j == 0) { string->miniFuels[j].coord = glm::vec3(randomX, randomY, -0.05); }
			else { string->miniFuels[j].coord = string->miniFuels[j - 1].coord; 
					string->miniFuels[j].coord.x += string->scale.x * 0.6f;
				}

			string->miniFuels[j].angle = rand() % 360;
			string->miniFuels[j].color = glm::vec3(0, 0.8, 0.8);
			string->miniFuels[j].dir = rand() % 1;
		}

		fuels[i] = string;
	}
}

void Tema2::FrameStart()
{
	if (pause) return;

	glClearColor(0, 0.9, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

bool Tema2::collide(float planeX, float planeY, Object obj) {
	if (obj == FUEL) {
		for (int i = 0; i < numberOfFuels; i++) {
			FuelString* string = fuels[i];

			float randomX = 1.5 + (rand() % 60) * 0.1f;
			float randomY = 1.0 + (rand() % 50) * 0.01f;
			for (int j = 0; j < 6; j++) {
				Fuel fuel = string->miniFuels[j];
				if (fuel.coord.y >= (planeY + (-1.5 * planeScale)) &&
					fuel.coord.y <= (planeY + (1.5 * planeScale)) &&
					fuel.coord.x <= (planeX + (2 * planeScale)) &&
					fuel.coord.x >= (planeX + (-2 * planeScale))) {

					if (j == 0) { string->miniFuels[j].coord.x = randomX; }
					else {
						string->miniFuels[j].coord = string->miniFuels[j - 1].coord;
						string->miniFuels[j].coord.x += string->scale.x * 0.6f;
					}
					return true;
				}


			}

			fuels[i] = string;
		}
	}

	if (obj == ASTEROID) {
		for (int i = 0; i < numberOfAsteroids; i++) {
			Asteroid* asteroid = asteroids[i];

			if (asteroid->coord.y >= (planeY + (-1.5 * planeScale)) &&
				asteroid->coord.y <= (planeY + (1.5 * planeScale)) &&
				asteroid->coord.x <= (planeX + (2 * planeScale)) && 
				asteroid->coord.x >= (planeX + (-2 * planeScale))) {

				asteroid->coord.x = 1.5 + (rand() % 60) * 0.1f;
				asteroid->coord.y = 1.2 + (rand() % 50) * 0.01f;
				asteroid->speed = 0.2 + (rand() % 5) * 0.01f;

				return true;
			}
		}
	}

	return false;
};

void Tema2::Update(float deltaTimeSeconds)
{
	if (pause) return;
	projectionMatrix = glm::perspective(RADIANS(fovAngle), window->props.aspectRatio, 0.01f, 200.0f);

	if (FPV) {
		glm::vec3 camPos = glm::vec3(planeX, planeY + 0.15, 0);
		camera->Set(camPos, glm::vec3(0, planeY, 0), glm::vec3(0, planeY, 0));
	}
	else {
		camera->Set(glm::vec3(0, 1, 1.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	}

	// Render lives
	{
		float offset = 0.2;
		float distX = 0.05;
		float distZ = 0.05;

		glm::vec3 firstPos;
		glm::vec3 secondPos;
		glm::vec3 thirdPos;

		firstPos = glm::vec3(-1.3, 1.7, 0);
		secondPos = firstPos + glm::vec3(offset, 0, 0);
		thirdPos = secondPos + glm::vec3(offset, 0, 0);
		distX = 0.05;
		distZ = 0;


		glm::mat4 modelMatrix;
		if (lives >= 1) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, firstPos);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(25), glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07, 0.15, 0.03));
			RenderSimpleMesh(meshes["sphere"], shaders["FuelShader"], modelMatrix, glm::vec3(1, 0, 0));
			
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, firstPos + glm::vec3(distX, 0, distZ));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-25), glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07, 0.15, 0.03));
			RenderSimpleMesh(meshes["sphere"], shaders["FuelShader"], modelMatrix, glm::vec3(1, 0, 0));
		}

		if (lives >= 2) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, secondPos);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(25), glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07, 0.15, 0.03));
			RenderSimpleMesh(meshes["sphere"], shaders["FuelShader"], modelMatrix, glm::vec3(1, 0, 0));
			
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, secondPos + glm::vec3(distX, 0, distZ));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-25), glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07, 0.15, 0.03));
			RenderSimpleMesh(meshes["sphere"], shaders["FuelShader"], modelMatrix, glm::vec3(1, 0, 0));
		}

		if (lives >= 3) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, thirdPos);
			modelMatrix = glm::rotate(modelMatrix, RADIANS(25), glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07, 0.15, 0.03));
			RenderSimpleMesh(meshes["sphere"], shaders["FuelShader"], modelMatrix, glm::vec3(1, 0, 0));
			
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, thirdPos + glm::vec3(distX, 0, distZ));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(-25), glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.07, 0.15, 0.03));
			RenderSimpleMesh(meshes["sphere"], shaders["FuelShader"], modelMatrix, glm::vec3(1, 0, 0));
		}

	}

	// Render FuelBar
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, fuelPos);
		modelMatrix = glm::scale(modelMatrix, blackScale);
		RenderSimpleMesh(meshes["square"], shaders["FuelShader"], modelMatrix, glm::vec3(0));

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, fuelPos + glm::vec3(0, 0, 0.01));
		modelMatrix = glm::scale(modelMatrix, fuelScale);
		RenderSimpleMesh(meshes["square"], shaders["FuelShader"], modelMatrix, glm::vec3(1 - fuel * 0.01, fuel * 0.01, 0));

		fuel -= (fuelConsumption + speedLevel) * deltaTimeSeconds;
		fuelScale.x = blackScale.x * fuel * 0.01;

		if (fuel <= 0) fuel = 0;
	}

	// Render Water
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(waterAngle), glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, waterScale);

		RenderSimpleMesh(meshes["water"], shaders["WaterShader"], modelMatrix, waterColor);

		waterAngle += deltaTimeSeconds * 30;
	}

	// Render Clouds
	{
		for (int i = 0; i < numberOfClouds; i++) {
			Cloud *cloud = clouds[i];

			for (int j = 0; j < 4; j++) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::rotate(modelMatrix, RADIANS(cloud->angle), glm::vec3(0, 0, 1));
				modelMatrix = glm::translate(modelMatrix, clouds[i]->miniCloud[j].coord);
				modelMatrix = glm::rotate(modelMatrix, RADIANS(clouds[i]->miniCloud[j].angle + 90), glm::vec3(0, 0, 1));
				modelMatrix = glm::scale(modelMatrix, cloud->scale);

				RenderSimpleMesh(meshes["cube"], shaders["CloudShader"], modelMatrix, cloud->miniCloud[j].color);

				cloud->angle += deltaTimeSeconds * cloud->speed;
			}

		}
	}

	// Render Asteroids
	{
		for (int i = 0; i < numberOfAsteroids; i++) {
			Asteroid *asteroid = asteroids[i];

			for (int j = 0; j < 4; j++) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, asteroid->coord);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(asteroid->scale));
				RenderSimpleMesh(meshes["sphere"], shaders["ObjectShader"], modelMatrix, asteroid->color);

				asteroid->coord.x -= deltaTimeSeconds * asteroid->speed + speedLevel * deltaTimeSeconds;

				if (asteroid->coord.x < -2.2f) {
					asteroid->coord.x = 1.5 + (rand() % 60) * 0.1f;
					asteroid->coord.y = 1.2 + (rand() % 50) * 0.01f;
				}
			}

		}
	}

	// Render Fuel
	{
		for (int i = 0; i < numberOfFuels; i++) {
			FuelString* string = fuels[i];

			for (int j = 0; j < 6; j++) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, string->miniFuels[j].coord);
				modelMatrix = glm::rotate(modelMatrix, RADIANS(string->miniFuels[j].angle), glm::vec3(1, 0, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(string->miniFuels[j].angle), glm::vec3(0, 1, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(string->miniFuels[j].angle), glm::vec3(0, 0, 1));
				modelMatrix = glm::scale(modelMatrix, string->scale);

				RenderSimpleMesh(meshes["teapot"], shaders["FuelShader"], modelMatrix, string->miniFuels[j].color);

				string->angle += deltaTimeSeconds * string->speed + speedLevel * deltaTimeSeconds;
				string->miniFuels[j].coord.x -= deltaTimeSeconds * string->speed;

				if (string->miniFuels[j].coord.x < -2.2f) {
					float randomX = 1.5 + (rand() % 60) * 0.1f;
					if (j == 0) { string->miniFuels[j].coord.x = randomX; }
					else {
						string->miniFuels[j].coord = string->miniFuels[j - 1].coord;
						string->miniFuels[j].coord.x += string->scale.x * 0.6f;
					}
				}
			}

		}
	}

	// Render plane
	{
		planeX += backingSpeed * deltaTimeSeconds;
		if (backingSpeed > 0) {
			backingSpeed += deltaTimeSeconds;
		}
		else {
			backingSpeed = 0;
		}

		if (planeX < -0.25) planeX += 0.1 * deltaTimeSeconds;
		glm::vec3 bodyCoord = glm::vec3(planeX + accX, planeY, 0);

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, bodyCoord);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(planeAngleZ), glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(planeAngleX), glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(planeScale));
		RenderSimpleMesh(meshes["plane"], shaders["PlaneShader"], modelMatrix);

		modelMatrix = glm::rotate(modelMatrix, RADIANS(propAngle), glm::vec3(1, 0, 0));
		RenderSimpleMesh(meshes["propellers"], shaders["PlaneShader"], modelMatrix);

		modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(1, 0, 0));
		RenderSimpleMesh(meshes["propellers"], shaders["PlaneShader"], modelMatrix);

		// verific daca s-au terminat vietile
		if (gameEnding) {
			// animatie de cadere

			if (planeY < 0.5) {
				cout << "Your score: " << (int)score << endl;
				exit(1);
			}


			if (propAngle > 0) { propAngle -= deltaTimeSeconds * propSpeed; }

			float fallingAngle = -70.0f;
			float fallingSpeed = 0.5;
			if (planeAngleZ < fallingAngle) planeAngleZ = fallingAngle;
			planeAngleX += deltaTimeSeconds * fallingSpeed * xDir * 1000;
			planeAngleZ -= deltaTimeSeconds * 80;
			planeY -= deltaTimeSeconds * fallingSpeed;
		}
		else {
			// functionarea normala
			propAngle += deltaTimeSeconds * propSpeed;

			if (accX > 0) { propAngle += accX * 50; }

			planeAngleX += deltaTimeSeconds * planeSpeed * xDir;

			if (planeAngleX > xTilt) { planeAngleX = xTilt; xDir *= -1; }
			if (planeAngleX < -xTilt) { planeAngleX = -xTilt; xDir *= -1; }


			planeAngleZ = planeY * 80 - 100;
			if (planeAngleZ > zTilt) { planeAngleZ = zTilt; }
			if (planeAngleZ < -zTilt) { planeAngleZ = -zTilt; }

			if (collide(planeX, planeY, FUEL)) {
				score += 1;
				fuel += fuelAddition;
				if (fuel > 100) fuel = 100;
			}

			if (collide(planeX, planeY, ASTEROID)) { 
				lives--; 
				backingSpeed = -5;
			}
			if (lives == 0 || planeY < 1.0 || fuel <= 0) { gameEnding = true; }

			score += deltaTimeSeconds;

			if ((int)score % 30 > 28 && !speedIncreased) {
				speedLevel += 5 * 0.01;
				speedIncreased = true;
			}

			if ((int)score % 30 == 0) {
				speedIncreased = false;
			}
			//cout << "Your score: " << (int)score << endl;

		}
	}

}



void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);
	CheckOpenGLError();
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	double time = Engine::GetElapsedTime();
	GLint loc_time = glGetUniformLocation(shader->program, "time");
	glUniform1f(loc_time, time);

	GLint loc_obj_color = glGetUniformLocation(shader->program, "object_color");
	glUniform3f(loc_obj_color, color.x, color.y, color.z);

	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Z)) {
			// TODO : translate the camera down
			fovAngle -= 20.0f * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_X)) {
			// TODO : translate the camera up
			fovAngle += 20.0f * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_1)) {
			left += 15.0f * deltaTime;
			right -= 15.0f * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_2)) {
			left -= 15.0f * deltaTime;
			right += 15.0f * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_3)) {
			top -= 15.0f * deltaTime;
			bottom += 15.0f * deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_4)) {
			top += 15.0f * deltaTime;
			bottom -= 15.0f * deltaTime;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_L)
	{
		gameEnding = true;
	}

	if (key == GLFW_KEY_P)
	{
		pause = true;
	}

	if (key == GLFW_KEY_C)
	{
		FPV = !FPV;
	}

}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	float sensivityOX = 0.002f;
	float sensivityOY = 0.002f;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{


		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			camera->RotateFirstPerson_OX(-deltaY * sensivityOY);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			camera->RotateThirdPerson_OX(deltaY * sensivityOY);
			camera->RotateThirdPerson_OY(deltaX * sensivityOX);
		}

	}
	else {
		if (!gameEnding) {
			planeY -= deltaY * sensivityOY;
			accX += deltaX * sensivityOX * 0.15;
		}
		
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
