#pragma once

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 colour, glm::vec3 direction, float ambient) :
	Light(colour),
	m_direction(direction),
	m_ambientFactor(ambient)
{}

void DirectionalLight::setLightUniforms(Shader* shader)
{
	shader->use();
	shader->setVec3("lightDirection", m_direction); // sets the direction of the light
	shader->setVec3("lightColour", m_colour); // sets the colour of the light
	shader->setFloat("ambientFactor", m_ambientFactor); // sets the ambient of the light
}