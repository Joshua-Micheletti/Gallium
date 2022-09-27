#include "utils.h"

std::string strRed = "\033[0;31m";
std::string strGreen = "\033[0;32m";
std::string strBlue = "\033[0;34m";
std::string strNoColor = "\033[0m";

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

void readOBJ(std::string filepath, std::vector<float>& v, std::vector<float>& t, std::vector<float>& n) {
	FILE* model = fopen(filepath.c_str(), "r");

    if (model == NULL) {
		printf("COULD NOT LOAD MODEL\n");
        return;
	}

	char buffer[255];

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
	}

	for (int i = 0; i < faces.size(); i++) {
		v.push_back(vertices[(faces[i] - 1) * 3]);
		v.push_back(vertices[(faces[i] - 1) * 3 + 1]);
		v.push_back(vertices[(faces[i] - 1) * 3 + 2]);
		t.push_back(tex[(facesTex[i] - 1) * 2]);
		t.push_back(tex[(facesTex[i] - 1) * 2 + 1]);
		n.push_back(normals[(facesNormals[i] - 1) * 3]);
		n.push_back(normals[(facesNormals[i] - 1) * 3 + 1]);
		n.push_back(normals[(facesNormals[i] - 1) * 3 + 2]);
	}
}


