#ifndef __MODEL__
#define __MODEL__

#include <string>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Utils/utils.h"

#include "Texture/RenderTexture.h"
#include "Mesh/Mesh.h"

// structure containing all the info for all the components of the model
typedef struct {
    std::string mesh = "ME_Default";
    std::string shader = "S_Default";
    std::string material = "MA_Default";
    RenderTexture texture;
    glm::mat4 translation = glm::mat4(1);
    glm::mat4 rotation = glm::mat4(1);
    glm::mat4 scale = glm::mat4(1);
} component_t;


// class that represents a model to be rendered
class Model {
    public:
        // CONSTRUCTOR
        Model();
        // DESTRUCTOR
        virtual ~Model();

        // getter for drawing mode
        GLenum drawingMode();
        // setter for drawing mode
        Model* drawingMode(GLenum);

        // getter for all the components in the model
        std::vector<component_t*> components();
        // getter for the component at the specified index
        component_t* component(int);
        // setter for all the components in the model
        Model* components(std::vector<component_t*>);

        // setter for the meshes in the model
        Model* meshes(std::vector<std::string>);
        // setter for the first mesh in the model
        Model* mesh(std::string);

        // getter for the first material in the model
        std::string material();
        // setter for the first material in the model
        Model* material(std::string);

        // getter for the first texture in the model
        std::string texture();
        // setter for the first texture in the model
        Model* texture(std::string);

        // setter for the first shader in the model
        Model* shader(std::string);
        // replace all the shaders in the model with one shader
        std::vector<std::string> shaders(std::string);
        // replace all the shaders in the model with a list of shaders
        std::vector<std::string> shaders(std::vector<std::string>);


        // translate the model
        Model* translate(glm::vec3);
        // rotate the model
        Model* rotate(glm::vec3);
        // scale the model
        Model* scale(glm::vec3);
        // calculate the model matrix
        glm::mat4 modelMatrix();
        Model* modelMatrix(float *);

        // get the model position
        glm::vec3 position();
        // set the model position
        Model* position(glm::vec3);

        glm::vec3 rotation();
        Model* rotation(glm::vec3);

        glm::vec3 scale();

        std::string source();
        Model* source(std::string);

        Model* center(glm::vec3);
        glm::vec3 center();

        Model* radius(float);
        float radius();

        Model* print();


    private:
        std::string m_source;
        // turn it into a map eventually
        // list of all the components in the model
        std::vector<component_t*> m_components;

        // model matrix (S * R * T)
        glm::mat4 m_modelMatrix;
        // translation matrix
        glm::mat4 m_translationMatrix;
        // rotation matrix
        glm::mat4 m_rotationMatrix;
        // scale matrix
        glm::mat4 m_scaleMatrix;
        // position vector
        glm::vec3 m_position;
        // rotation vector
        glm::vec3 m_rotation;
        // scale vector
        glm::vec3 m_scale;

        glm::vec3 m_center;
        float m_radius;

        // drawing mode for rendering (GL_TRIANGLES, GL_LINES...)
        GLenum m_drawingMode;
};

#endif