#pragma once

#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Light.h"
#include "Texture.h"
#include "Mesh.h"
const unsigned int sectorCount = 256;
const unsigned int stackCount = 256;
const float g = 0.0001;
class CelestialBody {
protected:
    std::string name;
    glm::vec3 origin;
    float radius;
    float mass;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    void makeVertices();
    Texture* tex;
    Mesh* mesh = new Mesh();
public:
    CelestialBody() {};
    ~CelestialBody() {};
    CelestialBody( std::string name, glm::vec3 origin, float radius, float mass, Texture* tex) :name(name), origin(origin), radius(radius), mass(mass), tex(tex) {};  
    std::string getName() const {
        return name;
    }
    Texture* getTex() { return tex; };
     void render() { mesh->RenderMesh(); };
    std::vector<float> getVertices() { return vertices; };
    std::vector<unsigned int> getIndices() { return indices; };
    void setName(const std::string& newName) {
        name = newName;
    }

    glm::vec3 getOrigin() const {
        return origin;
    }
    void setOrigin(const glm::vec3& newOrigin) {
        origin = newOrigin;
    }
    float getRadius() const {
        return radius;
    }
    void setRadius(float newRadius) {
        radius = newRadius;
    }
    float getMass() const {
        return mass;
    }
    void setMass(float newMass) {
        mass = newMass;
    }
};
class Planet : public CelestialBody {
public:
    float disToStar;
    glm::vec3 initVelocity;
    glm::vec3 currentVelocity;
    glm::vec3 currentOrigin;
    glm::mat4 model;
    std::vector<glm::vec3> orbit;
    Mesh* orbitMesh = new Mesh();
    unsigned int maxOrbitSize;
public:
    Planet( std::string name, glm::vec3 origin, float radius, float mass, float disToStar, glm::vec3 initVelocity, Texture* tex, unsigned int size) : CelestialBody(name, origin, radius, mass, tex), disToStar(disToStar), initVelocity(initVelocity), maxOrbitSize(size) {
        makeVertices();
        createModel(0.0f);
        currentOrigin = this->origin;
        currentVelocity = this->initVelocity;
        mesh->CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());
    }
    bool isEnter(glm::vec3 cameraPosition)
    {
        if (glm::distance(cameraPosition, currentOrigin) < radius) return true;
        return false;
    }
    void addPointOrbit() { 
        if (orbit.size() < maxOrbitSize)
        {
            orbit.push_back(currentOrigin);
            //std::cout << orbit.size() << std::endl;
            orbitMesh->createPointMesh(orbit);
           
        }
    };
    void createModel(float time);
    void addVelocity(glm::vec3 aVelocity) {
        currentVelocity += aVelocity;
    };
    void addMove(glm::vec3 move)
    {
        currentOrigin += move;
    }
    float getDistanceToStar() const {
        return disToStar;
    }
    void setDistanceToStar(float newDistance) {
        disToStar = newDistance;
    }
    glm::vec3 getInitialVelocity() const {
        return initVelocity;
    }
    void setInitialVelocity(glm::vec3 newVelocity) {
        initVelocity = newVelocity;
    }
    glm::vec3 getCurrentVelocity() const {
        return currentVelocity;
    }
    void setCurrentVelocity(glm::vec3 newVelocity) {
        currentVelocity = newVelocity;
    }
    glm::vec3 getCurrentOrigin() const {
        return currentOrigin;
    }
    void setCurrentOrigin(const glm::vec3& newOrigin) {
        currentOrigin = newOrigin;
    }
    glm::mat4 getModel() const {
        return model;
    }
    void setDefault() {
        currentOrigin = origin;
        currentVelocity = initVelocity;
        orbit.clear();
    }
    void renderOrbit() {
        orbitMesh->renderPoint();
    }
    
};
class Star : public CelestialBody {
protected:  
    glm::mat4 model;
public:
    Star( std::string name, glm::vec3 origin, float radius, float mass, Texture* tex) : CelestialBody(name,origin, radius, mass, tex) {
        makeVertices();
        createModel(0.0f);
        mesh->CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());
    };

    void createModel(float time);
    glm::mat4 getModel() const {
        return model;
    }
};