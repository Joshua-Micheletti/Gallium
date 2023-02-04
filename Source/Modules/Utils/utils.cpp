#include "utils.h"


#ifdef _WIN32
	std::string strRed = "[0;31m";
	std::string strGreen = "[0;32m";
	std::string strBlue = "[0;34m";
	std::string strYellow = "[0;33m";
	std::string strNoColor = "[0m";
#endif

#ifdef __unix__
	std::string strRed = "\033[0;31m";
	std::string strGreen = "\033[0;32m";
	std::string strBlue = "\033[0;34m";
	std::string strYellow = "\033[0;33m";
	std::string strNoColor = "\033[0m";
#endif



bool updateResolution = false;
bool updated = true;

int maxLength(std::vector<float> vector) {
    int maxLength = 0;

    // find max length
    for (int i = 0; i < vector.size(); i++) {
        std::string value = std::to_string(vector[i]);
        
        if (value.size() > maxLength) {
            maxLength = value.size();
        }
    }

    return(maxLength);
}

int countFaces(std::vector<float> vector) {
    if (vector.size() % 9 != 0 || vector.size() == 0) {
        printf("\033[0;31Vector format error\033[0m\n");
        return(-1);
    }

    return((int)(vector.size() / 9));
}

void createBuffer(std::vector<float> data, unsigned int* buffer) {
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, (*buffer));
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
}

void createIndexBuffer(std::vector<unsigned int> data, unsigned int* buffer) {
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*buffer));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
}

bool readOBJMesh(std::string filepath, std::vector<float>* v, std::vector<float>* t, std::vector<float>* n) {
	FILE* model = fopen(filepath.c_str(), "r");

    if (model == NULL) {
		printf("COULD NOT LOAD MODEL: %s\n", filepath.c_str());
        return(false);
	}

	char buffer[256];

	std::vector<float> vertices;
	std::vector<float> tex;
	std::vector<float> normals;
	std::vector<int> faces;
	std::vector<int> facesTex;
	std::vector<int> facesNormals;

	int readingVertex = 0;
	int readingFaces = 0;
	int readingTex = 0;
	int read = 0;
	int verticesNumber = 0;
	int readingNormals = 0;

	int i = 0;

	while (fscanf(model, "%s", buffer) != EOF) {
		if (!readingVertex && !readingFaces && !readingTex && !readingNormals) {
			if (buffer[0] == 'v' && buffer[1] == '\0') {
				readingVertex = 3;
				verticesNumber++;
			}
			else if (buffer[0] == 'v' && buffer[1] == 't') {
				readingTex = 2;
			}
			else if (buffer[0] == 'v' && buffer[1] == 'n') {
				readingNormals = 3;
			}
			else if (buffer[0] == 'f') {
				readingFaces = 3;
			}
		}

		else if (readingVertex) {
			vertices.push_back(atof(buffer));
			readingVertex--;
		}

		else if (readingTex) {
			tex.push_back(atof(buffer));
			readingTex--;
		}

		else if (readingNormals) {
			normals.push_back(atof(buffer));
			readingNormals--;
		}

		else if (readingFaces) {
			read = 2;
			// vertex
			faces.push_back(atoi(buffer));

			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] == '/' && buffer[i + 1] != '/' && buffer[i + 1] != '\0' && read > 0) {
					// uv
					if (read == 2) {
						facesTex.push_back(atoi(&buffer[i + 1]));
					}
					// normal
					else if (read == 1) {
						facesNormals.push_back(atoi(&buffer[i + 1]));
					}

					read--;
				}

				else if (buffer[i] == '/' && (buffer[i + 1] == '/' || buffer[i + 1] == '\0')) {
					read--;
				}
			}

			readingFaces--;
		}

		i++;
	}

	for (int i = 0; i < faces.size(); i++) {
		v->push_back(vertices[(faces[i] - 1) * 3]);
		v->push_back(vertices[(faces[i] - 1) * 3 + 1]);
		v->push_back(vertices[(faces[i] - 1) * 3 + 2]);
		if (facesTex.size() != 0) {
			t->push_back(tex[(facesTex[i] - 1) * 2]);
			t->push_back(tex[(facesTex[i] - 1) * 2 + 1]);
		}
		if (facesNormals.size() != 0) {
			n->push_back(normals[(facesNormals[i] - 1) * 3]);
			n->push_back(normals[(facesNormals[i] - 1) * 3 + 1]);
			n->push_back(normals[(facesNormals[i] - 1) * 3 + 2]);
		}
	}

	return(true);
}

bool readOBJ(std::string filepath, std::vector<std::vector<float>*>* v, std::vector<std::vector<float>*>* t, std::vector<std::vector<float>*>* n, std::vector<std::string>* m) {
	FILE* model = fopen(filepath.c_str(), "r");

    if (model == NULL) {
		printf("COULD NOT LOAD MODEL: %s\n", filepath.c_str());
        return(false);
	}

	char buffer[256];

	std::string tmpMaterial;
	std::vector<float> vertices;
	std::vector<float> tex;
	std::vector<float> normals;
	std::vector<int> faces;
	std::vector<int> facesTex;
	std::vector<int> facesNormals;

	int readingVertex = 0;
	int readingFaces = 0;
	int readingTex = 0;
	int readingMaterial = 0;
	int read = 0;
	int verticesNumber = 0;
	int readingNormals = 0;
	int newMesh = 0;
	bool firstMesh = true;

	int i = 0;

	if (v->size() == 0) {
		v->push_back(new std::vector<float>);
	}
	if (t->size() == 0) {
		t->push_back(new std::vector<float>);
	}
	if (n->size() == 0) {
		n->push_back(new std::vector<float>);
	}

	while (fscanf(model, "%s", buffer) != EOF) {
		if (!readingVertex && !readingFaces && !readingTex && !readingNormals && !readingMaterial) {
			if (buffer[0] == 'v' && buffer[1] == '\0') {
				readingVertex = 3;
				verticesNumber++;
			}
			else if (buffer[0] == 'v' && buffer[1] == 't') {
				readingTex = 2;
			}
			else if (buffer[0] == 'v' && buffer[1] == 'n') {
				readingNormals = 3;
			}
			else if (buffer[0] == 'f') {
				readingFaces = 3;
			}
			else if (strcmp(buffer, "usemtl") == 0) {
				readingMaterial = 1;

				if (!firstMesh) {
					newMesh = 1;
				}

				firstMesh = false;
			}
		}

		else if (readingVertex) {
			vertices.push_back(atof(buffer));
			readingVertex--;
		}

		else if (readingTex) {
			tex.push_back(atof(buffer));
			readingTex--;
		}

		else if (readingNormals) {
			normals.push_back(atof(buffer));
			readingNormals--;
		}

		else if (readingFaces) {
			read = 2;
			// vertex
			faces.push_back(atoi(buffer));

			for (int i = 0; buffer[i] != '\0'; i++) {
				if (buffer[i] == '/' && buffer[i + 1] != '/' && buffer[i + 1] != '\0' && read > 0) {
					// uv
					if (read == 2) {
						facesTex.push_back(atoi(&buffer[i + 1]));
					}
					// normal
					else if (read == 1) {
						facesNormals.push_back(atoi(&buffer[i + 1]));
					}

					read--;
				}

				else if (buffer[i] == '/' && (buffer[i + 1] == '/' || buffer[i + 1] == '\0')) {
					read--;
				}
			}

			readingFaces--;
		}

		else if (readingMaterial) {
			m->push_back(std::string(buffer));
			readingMaterial--;
		}

		if (newMesh) {
			for (int i = 0; i < faces.size(); i++) {
				(*v)[v->size() - 1]->push_back(vertices[(faces[i] - 1) * 3]);
				(*v)[v->size() - 1]->push_back(vertices[(faces[i] - 1) * 3 + 1]);
				(*v)[v->size() - 1]->push_back(vertices[(faces[i] - 1) * 3 + 2]);
				if (facesTex.size() != 0) {
					(*t)[t->size() - 1]->push_back(tex[(facesTex[i] - 1) * 2]);
					(*t)[t->size() - 1]->push_back(tex[(facesTex[i] - 1) * 2 + 1]);
				}
				if (facesNormals.size() != 0) {
					(*n)[n->size() - 1]->push_back(normals[(facesNormals[i] - 1) * 3]);
					(*n)[n->size() - 1]->push_back(normals[(facesNormals[i] - 1) * 3 + 1]);
					(*n)[n->size() - 1]->push_back(normals[(facesNormals[i] - 1) * 3 + 2]);
				}
			}

			faces.clear();
			facesTex.clear();
			facesNormals.clear();

			v->push_back(new std::vector<float>);
			t->push_back(new std::vector<float>);
			n->push_back(new std::vector<float>);

			newMesh--;
		}

		i++;
	}

	for (int i = 0; i < faces.size(); i++) {
		(*v)[v->size() - 1]->push_back(vertices[(faces[i] - 1) * 3]);
		(*v)[v->size() - 1]->push_back(vertices[(faces[i] - 1) * 3 + 1]);
		(*v)[v->size() - 1]->push_back(vertices[(faces[i] - 1) * 3 + 2]);
		if (facesTex.size() != 0) {
			(*t)[t->size() - 1]->push_back(tex[(facesTex[i] - 1) * 2]);
			(*t)[t->size() - 1]->push_back(tex[(facesTex[i] - 1) * 2 + 1]);
		}
		if (facesNormals.size() != 0) {
			(*n)[n->size() - 1]->push_back(normals[(facesNormals[i] - 1) * 3]);
			(*n)[n->size() - 1]->push_back(normals[(facesNormals[i] - 1) * 3 + 1]);
			(*n)[n->size() - 1]->push_back(normals[(facesNormals[i] - 1) * 3 + 2]);
		}
	}

	return(true);
}

bool readMTL(std::string filepath, std::vector<std::string> *names, std::vector<std::vector<float>*> *ambient, std::vector<std::vector<float>*> *diffuse, std::vector<std::vector<float>*> *specular, std::vector<float> *shininess) {
	FILE* material = fopen(filepath.c_str(), "r");

    if (material == NULL) {
		printf("COULD NOT LOAD MATERIAL: %s\n", filepath.c_str());
        return(false);
	}

	int readingAmbient = 0;
	int readingDiffuse = 0;
	int readingSpecular = 0;
	int readingShininess = 0;
	int readingMaterialName = 0;

	std::string namesBuffer;
	std::vector<float> ambientBuffer;
	std::vector<float> diffuseBuffer;
	std::vector<float> specularBuffer;
	float tmpShininess;

	bool firstMaterial = true;
	bool newMaterial = false;

	char buffer[256];

	if (ambient->size() == 0) {
		ambient->push_back(new std::vector<float>);
	}
	if (diffuse->size() == 0) {
		diffuse->push_back(new std::vector<float>);
	}
	if (specular->size() == 0) {
		specular->push_back(new std::vector<float>);
	}

	while (fscanf(material, "%s", buffer) != EOF) {
		if (!readingAmbient && !readingDiffuse && !readingSpecular && !readingShininess && !readingMaterialName) {
			if (buffer[0] == 'K' && buffer[1] == 'a') {
				readingAmbient = 3;
			}
			else if (buffer[0] == 'K' && buffer[1] == 'd') {
				readingDiffuse = 3;
			}
			else if (buffer[0] == 'K' && buffer[1] == 's') {
				readingSpecular = 3;
			}
			else if (buffer[0] == 'N' && buffer[1] == 's') {
				readingShininess = 1;
			}
			else if (strcmp(buffer, "newmtl") == 0) {
				readingMaterialName = 1;

				if (!firstMaterial) {
					newMaterial = true;
				}

				firstMaterial = false;
			}
		}

		else if (readingAmbient) {
			ambientBuffer.push_back(atof(buffer));
			readingAmbient--;
		}
		else if (readingDiffuse) {
			diffuseBuffer.push_back(atof(buffer));
			readingDiffuse--;
		}
		else if (readingSpecular) {
			specularBuffer.push_back(atof(buffer));
			readingSpecular--;
		}
		else if (readingShininess) {
			tmpShininess = atof(buffer);
			readingShininess--;
		}
		else if (readingMaterialName) {
			namesBuffer = std::string(buffer);
			readingMaterialName--;
		}

		if (newMaterial) {
			names->push_back(namesBuffer);

			for (int i = 0; i < ambientBuffer.size(); i++) {
				(*ambient)[ambient->size() - 1]->push_back(ambientBuffer[i]);
				(*diffuse)[diffuse->size() - 1]->push_back(diffuseBuffer[i]);
				(*specular)[specular->size() - 1]->push_back(specularBuffer[i]);
			}

			shininess->push_back(tmpShininess);

			ambientBuffer.clear();
			diffuseBuffer.clear();
			specularBuffer.clear();

			ambient->push_back(new std::vector<float>);
			diffuse->push_back(new std::vector<float>);
			specular->push_back(new std::vector<float>);

			newMaterial = false;
		}
	}

	names->push_back(namesBuffer);

	for (int i = 0; i < ambientBuffer.size(); i++) {
		(*ambient)[ambient->size() - 1]->push_back(ambientBuffer[i]);
		(*diffuse)[diffuse->size() - 1]->push_back(diffuseBuffer[i]);
		(*specular)[specular->size() - 1]->push_back(specularBuffer[i]);
	}

	shininess->push_back(tmpShininess);

	ambientBuffer.clear();
	diffuseBuffer.clear();
	specularBuffer.clear();

	ambient->push_back(new std::vector<float>);
	diffuse->push_back(new std::vector<float>);
	specular->push_back(new std::vector<float>);

	newMaterial = false;

	return(true);
}


void polarToCartesian(float r, float teta, float* x, float* y) {
	*x = r * cos(teta);
	*y = r * sin(teta);
}

int find(std::string s, std::vector<std::string> v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == s) {
			return(i);
		}
	}

	return(-1);
}

const char** stringVectorToCArray(std::vector<std::string> v) {
	int size = v.size();

	std::vector<const char*> charVector;

	for (int i = 0; i < v.size(); i++) {
		charVector.push_back(v[i].c_str());
		printf("%s\n", charVector.data()[i]);
	}

	return(charVector.data());
}

glm::vec3 averageVector3f(std::vector<float> vertices) {
	glm::vec3 average = glm::vec3(0);

	for (int i = 0; i < vertices.size(); i += 3) {
		average.x += vertices[i];
		average.y += vertices[i + 1];
		average.z += vertices[i + 2];
	}

	average.x /= (float)vertices.size() / 3.0f;
	average.y /= (float)vertices.size() / 3.0f;
	average.z /= (float)vertices.size() / 3.0f;

	return(average);
}

float maxDistanceVector3f(glm::vec3 center, std::vector<float> vertices) {
	float maxDistance = 0.0f;

	float distance;

	for (int i = 0; i < vertices.size(); i += 3) {
		distance = sqrt(pow(center.x - vertices[i], 2) + pow(center.y - vertices[i + 1], 2) + pow(center.z - vertices[i + 2], 2));
		if (distance > maxDistance) {
			maxDistance = distance;
		}
	}

	return(maxDistance);
}