#include <string>
#include <vector>
#include <iostream>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Mesh.h"


class Model
{
public:
    Model(const std::string& filePath);
    ~Model();

    void Draw();

private:
    std::vector<Mesh*> meshes;

    void LoadModel(const std::string& filePath);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
};
