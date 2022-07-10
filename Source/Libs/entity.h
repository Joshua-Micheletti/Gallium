#ifndef __ENTITY__
#define __ENTITY__

#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

typedef struct {
  glm::vec3 minX,
            maxX,
            minY,
            maxY,
            minZ,
            maxZ;

  glm::vec3 a,
            b,
            c,
            d,
            e,
            f,
            g,
            h;

  glm::vec3 XYZ,
            xyz;
} bounds_t;

class Entity {
  public:
    // constructor
    Entity(std::string);

  private:
    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<float> normals;

    unsigned int vertexBuffer;
    unsigned int texBuffer;
    unsigned int normalBuffer;
    unsigned int texture;

    string name;
    int shader;
    bool isUV;
    GLenum elements;
    GLenum textureType;

    glm::vec3 center;
    glm::vec3 worldPosition;
    glm::vec3 localCenter;

    glm::mat4 translation;
    glm::mat4 rotation;
    glm::mat4 scaleMatrix;
    glm::mat4 modelMatrix;
    glm::vec3 scaleFactor;
    float rotateFactorX;
    float rotateFactorY;
    float rotateFactorZ;

    bounds_t localBounds;
    bounds_t originalBounds;
    bounds_t worldBounds;
    bounds_t internalWorldBounds;
    bounds_t realBounds;
    float maxDistInt;
    float maxDistExt;
    float maxDist;
    bool toReflect;

  public:
    // get methods
    std::string getName();
    std::vector<float> getVertices();
    std::vector<float> getUVs();
    std::vector<float> getNormals();
    glm::vec3 getCenter();
    glm::vec3 getWorldPosition();
    glm::mat4 getModelMatrix();
    unsigned int getVertexBuffer();
    unsigned int getTexBuffer();
    unsigned int getNormalBuffer();
    int getShader();
    glm::vec3 getRotationFactor();
    glm::vec3 getScalingFactor();
    GLenum getElements();
    unsigned int getTexture();
    GLenum getTextureType();
    bounds_t getObjectBoundingBox(bool);
    glm::vec3 getLocalCenter();
    bounds_t getOriginalBounds();
    bounds_t getExternalAxisAlignedBoundingBox(bool);
    bounds_t getInternalAxisAlignedBoundingBox(bool);
    bounds_t getAxisAlignedBoundingBox(bool);
    float getInternalBoundingSphere(bool);
    float getExternalBoundingSphere(bool);
    float getBoundingSphere(bool);
    bool getToReflect();

    // set methods
    void load3DModel(string);
    void loadVertices(std::vector<float>);
    void loadUVs(std::vector<float>);
    void loadTexture(string);
    void loadCubemap(std::vector<std::string>);
    void placeAtCenter();
    void move(glm::vec3, glm::mat4);
    void scale(float);
    void setScale(glm::vec3);
    void rotate(float, float, float);
    void setRotation(float, float, float);
    void placeAt(glm::vec3, glm::mat4);
    void setShader(int);
    void setElements(GLenum);
    void setTextureType(GLenum);
    void setTexture(unsigned int);

    void setToReflect(bool);

  
  private:
    void calculateModel();
    void loadModel(string);
    void findCenter();
    void createBuffer(std::vector<float>, unsigned int *);

    void calculateObjectBoundingBox();
    void calculateExternalAxisAlignedBoundingBox();
    void calculateInternalAxisAlignedBoundingBox();
    void calculateAxisAlignedBoundingBox();
    void calculateInternalBoundingSphere();
    void calculateExternalBoundingSphere();
    void calculateBoundingSphere();
};

#endif
