#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, glm::vec3 dir, glm::vec2 radii):
	PointLight(colour, position,constants),
	m_direction(dir),
	m_radii(radii)
{}

void SpotLight::setLightUniforms(Shader* shader)
{
	shader->use();
	shader->setVec3("slightColour", m_colour); // sets the light colour
	shader->setVec3("slightPosition", m_position); // sets the position of the light
	shader->setVec3("sAttenuation", m_constants);
	shader->setVec3("sDirection", m_direction); // sets the direction of the light
	shader->setVec2("sRadii", m_constants);
}
