#include "Light.h"

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
}
void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
}

Light::~Light()
{

}
DirectionalLight::DirectionalLight()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 1.0f;
	specularIntensity = 1.0f;
	localDirection = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));

}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
	specularIntensity = sIntensity;
	localDirection = glm::normalize(glm::vec3(-1.0, 0.0f, 0.0f));

}

void DirectionalLight::UseDirLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,GLfloat diffuseIntensityLocation, GLfloat specularIntensityLocation, GLfloat lightDirectionLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform3f(lightDirectionLocation,localDirection.x, localDirection.y, localDirection.y);
}
void DirectionalLight::print()
{
	std:: cout << colour.x << " " << colour.y << " " << colour.z <<std::endl;
	std::cout << ambientIntensity << " " << diffuseIntensity << std::endl;
	std::cout << localDirection.x << " " << localDirection.y << " " << localDirection.z << std::endl;
}
;

PointLight::PointLight()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 1.0f;
	specularIntensity = 1.0f;
	position = {4.0f,4.0f,4.0f};
	constant = 1.0f;
	linear = 1.0f;
	quadratic = 1.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
	specularIntensity = sIntensity;
	position = { 4.0f,4.0f,4.0f };
	constant = 1.0f;
	linear = 1.0f;
	quadratic = 1.0f;
}

void PointLight::UsePointLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat specularIntensityLocation, GLfloat lightPositionLocation, GLfloat lightConstantLocation, GLfloat lightLinearLocation, GLfloat lightQuadraticLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform3f(lightPositionLocation, position.x, position.y, position.y);
	glUniform1f(lightConstantLocation, constant);
	glUniform1f(lightLinearLocation, linear);
	glUniform1f(lightQuadraticLocation, quadratic);
}
