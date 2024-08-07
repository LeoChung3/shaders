#include "Plane.h"

Plane::Plane(glm::vec3 col, float shine, float specStregnth):
	m_colour(col),
	m_shine(shine),
	m_specularStrength(specStregnth)
{
	makeVAO();
	resetTransform();
}

void Plane::setPlaneMaterialValues(Shader* shader)
{
	shader->use();
	shader->setVec3("PlaneColour", m_colour);
	shader->setFloat("Planeshine", m_shine);
	shader->setFloat("PlanespecStrength", m_specularStrength);
}

void Plane::rotate(float angle, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, (float)(angle), axis);
}

void Plane::scale(float scaleFactor, glm::vec3 axis)
{
	m_transform = glm::scale(m_transform, axis);

}

void Plane::translate(glm::vec3 translation)
{
	m_transform = glm::translate(m_transform, translation);
}

void Plane::makeVAO()
{
	glCreateBuffers(1, &m_VBO);
	glNamedBufferStorage(m_VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &m_EBO);
	glNamedBufferStorage(m_EBO, sizeof(unsigned int) * floorIndices.size(), floorIndices.data(), GL_DYNAMIC_STORAGE_BIT);


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
