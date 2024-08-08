#pragma once

#include "PointLight.h"

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants):
Light(colour),
m_position(position),
m_constants(constants)
{}

void PointLight::setLightUniforms(Shader* shader, string num) // put i
{
	shader->use();

	/*shader->setVec3("lights[0].constants", m_constants);
	shader->setVec3("lights[0].colour", m_colour);
	shader->setVec3("lights[0].position", m_position);*/

	str1.insert(7, num);
	str2.insert(7, num);
	str3.insert(7, num);
	shader->setVec3(str1, m_constants);
	shader->setVec3(str2, m_colour);
	shader->setVec3(str3, m_position);
}