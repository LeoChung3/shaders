#include "Cube.h"

Cube::Cube(glm::vec3 col, float shine, float specStregnth):
	m_colour(col),
	m_shine(shine),
	m_specularStrength(specStregnth)
{
	makeVAO();
	resetTransform();
}

Cube::~Cube()
{
}

void Cube::setCubeMaterialValues(Shader* shader)
{
	shader->use();
	shader->setVec3("cubeColour", m_colour); //sets the cube colour in the frag shader
	shader->setFloat("shine", m_shine); // sets the shine in the frag shader
	shader->setFloat("specStrength", m_specularStrength); // sets the spec stregnth in the frag shader


}

void Cube::rotate(float angle, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, (float)(glfwGetTime() * 0.5), axis); // rotates the cube on the axis its given
}

void Cube::scale(float scaleFactor, glm::vec3 axis)
{
	m_transform = glm::scale(m_transform, axis); // scales the cube by the axis its given
}

void Cube::translate(glm::vec3 translation)
{
	m_transform = glm::translate(m_transform, translation); // translates the cube by how ever much its given in a vec 3
}

void Cube::makeVAO()
{

	glCreateBuffers(1, &m_VBO);
	glNamedBufferStorage(m_VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &m_EBO);
	glNamedBufferStorage(m_EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &m_VAO);
	glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(float) * 6);
	glVertexArrayElementBuffer(m_VAO, m_EBO);

	glEnableVertexArrayAttrib(m_VAO, 0);
	glEnableVertexArrayAttrib(m_VAO, 1);


	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(m_VAO, 0, 0);
	glVertexArrayAttribBinding(m_VAO, 1, 0);

}