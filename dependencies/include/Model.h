#include <shader.h>
#include <Mesh.h>
#include <vector>

#include <stb_image.h>

// Installed using homebrew, (brew install assimp)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model 
{
    public:
        // model data
        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded; 
        std::string directory;
        bool gammaCorrection;

        Model(std::string const &path, bool gamma = false) : gammaCorrection(gamma)
        {
            loadModel(path);
        }
        // Invokes draw method on each mesh
        void Draw(Shader &shader);	
    private:

        unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);
        void loadModel(std::string const &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
};