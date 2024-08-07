#include "myScene.h"
#include "Shader.h"

// can toggle off an on the lights with numbers 1 to 6
// can move camera direction with arrow keys

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\VShader.glsl", "..\\Shaders\\FShader.glsl");

	m_directionalLight = new DirectionalLight(glm::vec3(1.0f,1.0f,1.0f), // colour
											  glm::vec3(-1.0f, 0.0f, 0.0f), // direction
											  0.01); // ambient
	m_directionalLight->setLightUniforms(m_myShader);


	m_PointLight = new PointLight(glm::vec3(1.0, 0.0, 0.0), // colour
								  glm::vec3(0.0, 0.0, 2.0), // position
								  glm::vec3(1.0, 0.22, 0.02)); // constants
	m_PointLight->setLightUniforms(m_myShader);


	m_SpotLight = new SpotLight(glm::vec3(0.0, 1.0, 0.0), // colour
								glm::vec3(0.0, 0.0, 0.0), // position
								glm::vec3(1.0, 0.22, 0.02), // constants
								glm::vec3(0.0, 0.0, 0.0), // direction
								glm::vec2(glm::cos(glm::radians(17.5f)), glm::cos(glm::radians(19.5f))));
	m_SpotLight->setLightUniforms(m_myShader);


	m_Plane = new Plane(glm::vec3(1.0, 1.0, 1.0), //colour
								  4, // shine
								  0.5f); // spec
	m_Plane->setPlaneMaterialValues(m_myShader);

	m_Plane2 = new Plane(glm::vec3(1.0, 1.0, 1.0), //colour
								   4, // shine
								   0.5f); // spec
	m_Plane2->setPlaneMaterialValues(m_myShader);


	m_cube = new Cube(glm::vec3(1.0, 1.0, 1.0), 4, 0.5f);
	m_cube2 = new Cube(glm::vec3(0.38, 0.38, 0.38), 4, 0.5f);

};

void MyScene::update(float dt) {
	m_camera->update(dt);
	render();
}

void MyScene::render() {
	m_myShader->use();

	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());


	m_myShader->setVec3("slightPosition", m_camera->getPosition()); // sets the position of the spotlight to the camera
	m_myShader->setVec3("sDirection", m_camera->getFront()); // sets the direction of the spotlight to the facing front of the camera

	m_myShader->setBool("D_light", m_camera->getD()); // gives the frag the bool of the directional light
	m_myShader->setBool("P_light", m_camera->getP()); // gives the frag the bool of the positional light
	m_myShader->setBool("S_light", m_camera->getS()); // gives the frag the bool of the spot light


	glBindVertexArray(m_cube->getVAO());
	m_cube->setCubeMaterialValues(m_myShader);
	m_cube->scale(2.0, glm::vec3(3.0, 3.0, 3.0)); // scales cube by 3
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTransform();

	m_cube2->setCubeMaterialValues(m_myShader);
	m_cube2->translate(glm::vec3(10.0, 5.0, 3.0)); // translates cube -7 on y and 3 on z
	m_cube2->scale(2.0, glm::vec3(5.0, 5.0, 5.0)); // scales cube by 3
	m_cube2->rotate(0.01, glm::vec3(1.0, 0.0, 1.0)); // rotates cube on x and z axis
	m_cube2->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube2->resetTransform();


	glBindVertexArray(m_Plane->getVAO());
	m_Plane->translate(glm::vec3(0.0, 7.0, 0.0));
	m_Plane->scale(2.0, glm::vec3(5.0, 5.0, 5.0));
	m_Plane->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_Plane->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_Plane->resetTransform();

	m_Plane2->translate(glm::vec3(0.0, 0.0, -7.0));
	m_Plane2->rotate(1.57, glm::vec3(1.0, 0.0, 0.0));
	m_Plane2->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_Plane->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_Plane2->resetTransform();

}