#include "Scene.h"
#include "Shader.h"
#include "DirectionalLight.h"
#include "Cube.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Plane.h"




class MyScene : public Scene {

public:
	MyScene(GLFWwindow* window, InputHandler* H);
	~MyScene() {};
	void update(float dt) override;

private:
	Shader* m_myShader;
	DirectionalLight* m_directionalLight;
	DirectionalLight* m_directionalLight2;
	Cube* m_cube;
	Cube* m_cube2;
	PointLight* m_PointLight;
	SpotLight* m_SpotLight;
	Plane* m_Plane;
	Plane* m_Plane2;

	void render();

};