#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include <windows.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <assimp/Importer.hpp>
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Universe.h"
#include "Model.h"
#include "Celestial.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;
Texture* EarthV = new Texture("Textures/earth.jpg");
Texture* SunV = new Texture("Textures/sun.jpg");
Texture* MercuryV= new Texture("Textures/mercury.jpg");
Texture* UranusV = new Texture("Textures/uranus.jpg");
Texture* JupiterV = new Texture("Textures/jupiter.jpg");
Texture* MarsV = new Texture("Textures/mars.jpg");
Texture* VenusV = new Texture("Textures/Venus.jpg");
Texture* SaturnV = new Texture("Textures/saturn.jpg");
Texture* SkyV = new Texture("Textures/sky_box.jpg");
Texture* MoonV = new Texture("Textures/moon.jpg");
Texture* NeptuneV = new Texture("Textures/neptune.jpg");
Texture* SkyBox = new Texture("Textures/sky_box.jpg");
Universe MilkyWay;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";
static const char* vShader1 = "Shaders/point.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";
static const char* fShader1 = "Shaders/point.frag";



void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
	//Shader* shader2 = new Shader();
	//shader2->CreateFromFiles(vShader1, fShader1);
	//shaderList.push_back(*shader2);
}
void addPlanet()
{
	std::string PlanetName[] = {"Sun", "Earth", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune","SkyBox"};
	// ten, goc, r, trong luong, distance, velo
	Planet* Earth = new Planet(PlanetName[1], glm::vec3(28.0f, 0.0f, 0.0f), 1.8f, 424.0f, 68.37f, glm::vec3(0.0f,0.0f,9.1600),EarthV,9000);
	Planet* Mercury = new Planet(PlanetName[2], glm::vec3(18.0f, 0.0f, 0.0f), 1.0f, 73.14f, 17.37f, glm::vec3(0.0f, 0.0f, 11.9901f), MercuryV,7000);
	Planet* Venus = new Planet(PlanetName[3], glm::vec3(23.0f, 0.0f, 0.0f), 1.0f, 445.0f, 32.4f, glm::vec3(0.0f, 0.0f, 17.9448f), VenusV,6000);
	Planet* Mars = new Planet(PlanetName[4], glm::vec3(33.0f, 0.0f, 0.0f), 1.8f, 183.0f, 44.88f, glm::vec3(0.0f, 0.0f, 9.94f), MarsV, 9000);
	Planet* Jupiter = new Planet(PlanetName[5], glm::vec3(50.0f, 0.0f, 0.0f), 5.0f, 89982.0f, 233.55f, glm::vec3(0.0f, 0.0f, 52.3224f),JupiterV, 3500);
	Planet* Saturn = new Planet(PlanetName[6], glm::vec3(65.0f, 0.0f, 0.0f), 3.5f, 40200.0f, 429.9f, glm::vec3(0.0f, 0.0f, 21.5902f), SaturnV, 7000);
	Planet* Uranus = new Planet(PlanetName[7], glm::vec3(80.0f, 0.0f, 0.0f), 2.0f,24200.0f , 861.6f, glm::vec3(0.0f, 0.0f, 9.2401), UranusV,12500);
	Planet* Neptune = new Planet(PlanetName[8], glm::vec3(90.0f, 0.0f, 0.0f), 1.6f, 21230.0, 1348.5f, glm::vec3(0.0f, 0.0f, 5.8850), NeptuneV, 16000);
	Star* Sun = new Star(PlanetName[0], glm::vec3(0.0f, 0.0f, 0.0f), 7.0f, 330000.0f,SunV);
	Star* Sky = new Star(PlanetName[9], glm::vec3(0.0f), 250.0f, 0.0f, SkyBox);
	MilkyWay.addBody(Earth);
	MilkyWay.addBody(Mercury);
	MilkyWay.addBody(Venus);
	MilkyWay.addBody(Mars);
	MilkyWay.addBody(Jupiter);
	MilkyWay.addBody(Saturn);
	MilkyWay.addBody(Uranus);
	MilkyWay.addBody(Neptune);
	MilkyWay.setStar(Sun);
	MilkyWay.setSky(Sky);
}
int main() 
{
	mainWindow = Window(1920, 1600);
	mainWindow.Initialise();

	addPlanet();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 50.0f, 0.5f);

	EarthV->LoadTexture();
	SunV->LoadTexture();
	MercuryV->LoadTexture();
	UranusV->LoadTexture();
	JupiterV->LoadTexture();
	 MarsV->LoadTexture();
	 VenusV->LoadTexture();
	 SaturnV->LoadTexture();
	 SkyV->LoadTexture();
	 MoonV->LoadTexture();
	 NeptuneV->LoadTexture();
	 SkyBox->LoadTexture();
	DirectionalLight dLight(1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f);
	PointLight pLight(0.5f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f);
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDiffuseIntensity = 0, uniformLightPosition = 0, uniformLightConstant = 0, uniformLightLinear = 0 , uniformLightQuadratic = 0, uniformLightDirection = 0, uniformCameraPos = 0, uniformSpecularIntensity = 0;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	float* ambient = dLight.getAmbientIntensity();
	float rotation = 0.0f;
	bool showOrbit = true;
	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;
		rotation += 0.05;
		// Get + Handle User Input
		glfwPollEvents();
		
		camera.keyControl(mainWindow.getsKeys(), deltaTime, ambient );
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		int state = glfwGetKey(mainWindow.getWindows(), GLFW_KEY_Z);
		if (state == GLFW_PRESS)
		{
			for (unsigned int i = 0; i < MilkyWay.planetList.size(); i++)
			{
				MilkyWay.planetList[i]->setDefault();
			}
		}
		int state2 = glfwGetKey(mainWindow.getWindows(), GLFW_KEY_C);
		if (state2 == GLFW_PRESS)
		{
			if (showOrbit) showOrbit = false;
			else showOrbit = true;
		}
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformLightDirection = shaderList[0].GetLightDirectionLocation();
		uniformLightPosition = shaderList[0].GetLightPositionLocation();
		uniformLightConstant = shaderList[0].GetLightConstantLocation();
		uniformLightLinear = shaderList[0].GetLightLinearLocation();
		uniformLightQuadratic = shaderList[0].GetLightQuadraticLocation();
		//pLight.UsePointLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformSpecularIntensity, uniformLightPosition, uniformLightConstant, uniformLightLinear, uniformLightQuadratic);
		dLight.UseDirLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformSpecularIntensity,uniformLightDirection);
		glm::vec3 cameraPos = camera.getPosition();
		uniformCameraPos = shaderList[0].GetCameraLocalPos();
		glUniform3f(uniformCameraPos, cameraPos.x, cameraPos.y, cameraPos.z);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glm::mat4 model(1.0f);
		for (unsigned int i = 0; i < MilkyWay.planetList.size(); i++)
		{
			MilkyWay.planetList[i]->createModel(deltaTime);
			model = MilkyWay.planetList[i]->getModel();
			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.5f, 0.5f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			MilkyWay.planetList[i]->getTex()->UseTexture();
			MilkyWay.planetList[i]->render();
			if (MilkyWay.planetList[i]->isEnter(cameraPos))
			{

				while (!mainWindow.getShouldClose() )
				{
					GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
					deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
					lastTime = now;
					// Get + Handle User Input
					glfwPollEvents();
					rotation += 0.025f;
					camera.keyControl(mainWindow.getsKeys(), deltaTime, ambient);
					camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
					// Clear the window
					glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					int state1 = glfwGetKey(mainWindow.getWindows(), GLFW_KEY_X);
					if (state1 == GLFW_PRESS)
					{
						break;
					}
					shaderList[0].UseShader();
					uniformModel = shaderList[0].GetModelLocation();
					uniformProjection = shaderList[0].GetProjectionLocation();
					uniformView = shaderList[0].GetViewLocation();
					uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
					uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
					uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();
					uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
					uniformLightDirection = shaderList[0].GetLightDirectionLocation();
					uniformLightPosition = shaderList[0].GetLightPositionLocation();
					uniformLightConstant = shaderList[0].GetLightConstantLocation();
					uniformLightLinear = shaderList[0].GetLightLinearLocation();
					uniformLightQuadratic = shaderList[0].GetLightQuadraticLocation();
					dLight.UseDirLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformSpecularIntensity, uniformLightDirection);
					glm::vec3 cameraPos = camera.getPosition();
					uniformCameraPos = shaderList[0].GetCameraLocalPos();
					glUniform3f(uniformCameraPos, cameraPos.x, cameraPos.y, cameraPos.z);
					glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
					glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
					glm::mat4 model(1.0f);
					model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.5f, 0.5f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

					MilkyWay.planetList[i]->getTex()->UseTexture();
					MilkyWay.planetList[i]->render();
					model = glm::mat4(1.0f);
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					MilkyWay.skyBox->getTex()->UseTexture();
					MilkyWay.skyBox->render();
					glUseProgram(0);
					mainWindow.swapBuffers();
					
				}
			}
		}
			
			MilkyWay.star->createModel(deltaTime);
			model = MilkyWay.star->getModel();
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			MilkyWay.skyBox->getTex()->UseTexture();
			MilkyWay.skyBox->render();
			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.5f, 0.5f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			
			MilkyWay.star->getTex()->UseTexture();
			MilkyWay.star->render();
			model = glm::mat4(1.0f);
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			for (unsigned int i = 0; i < MilkyWay.planetList.size(); i++)
			{
				if (showOrbit) MilkyWay.planetList[i]->renderOrbit();
			}

			MilkyWay.updateVelocity(deltaTime);
			MilkyWay.updatePosition(deltaTime);
			//Sleep(100);	
			
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}