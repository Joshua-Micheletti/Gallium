#include "model.h"

Model::Model() {
    printf("created model\n");
}

void Model::loadModel(std::string filepath) {
	FILE* model = fopen(filepath.c_str(), "r");

    if (model == NULL) {
		printf("COULD NOT LOAD MODEL\n");
        return;
	}

    this->source = filepath;

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
		Model::vertices.push_back(vertices[(faces[i] - 1) * 3]);
		Model::vertices.push_back(vertices[(faces[i] - 1) * 3 + 1]);
		Model::vertices.push_back(vertices[(faces[i] - 1) * 3 + 2]);
		Model::uvs.push_back(tex[(facesTex[i] - 1) * 2]);
		Model::uvs.push_back(-tex[(facesTex[i] - 1) * 2 + 1]);
		Model::normals.push_back(normals[(facesNormals[i] - 1) * 3]);
		Model::normals.push_back(normals[(facesNormals[i] - 1) * 3 + 1]);
		Model::normals.push_back(normals[(facesNormals[i] - 1) * 3 + 2]);
	}
}


std::vector<float> Model::getVertices() {
    return(this->vertices);
}

std::vector<float> Model::getUVs() {
    return(this->uvs);
}

std::vector<float> Model::getNormals() {
    return(this->normals);
}


void Model::printVertices() {
    int length = maxLength(this->vertices);

    printf("\nVertices:\n");
    for (int i = 0; i < this->vertices.size(); i++) {
        std::string vertexValue = std::to_string(this->vertices[i]);
        for (int j = vertexValue.size(); j < length; j++) {
            vertexValue.insert(0, 1, ' ');
        }

        if (i % 9 == 0) {
            printf("Face %d:\n", (int)(i / 9));
        }
        if (i % 3 == 2) {
            printf("\033[0;34mZ\033[0m = %s\n", vertexValue.c_str());
        } else {
            printf("%s = %s ", i % 3 == 0 ? "\033[0;31mX\033[0m" : "\033[0;32mY\033[0m", vertexValue.c_str());
        }

        if (i % 9 == 8) {
            printf("\n");
        }
    }
}

void Model::printUVs() {
    int length = maxLength(this->uvs);

    printf("\nUVs: \n");
    for (int i = 0; i < this->uvs.size(); i++) {
        std::string uvValue = std::to_string(this->uvs[i]);
        for (int j = uvValue.size(); j < length; j++) {
            uvValue.insert(0, 1, ' ');
        }

        if (i % 6 == 0) {
            printf("Face %d:\n", (int)(i / 6));
        }
        if (i % 2 == 1) {
            printf("\033[0;32mV\033[0m = %s\n", uvValue.c_str());
        } else {
            printf("\033[0;31mU\033[0m = %s ", uvValue.c_str());
        }

        if (i % 6 == 5) {
            printf("\n");
        }
    }
}

void Model::printNormals() {
    int length = maxLength(this->normals);

    printf("\nNormals: \n");
    for (int i = 0; i < this->normals.size(); i++) {
        std::string normalValue = std::to_string(this->normals[i]);
        for (int j = normalValue.size(); j < length; j++) {
            normalValue.insert(0, 1, ' ');
        }
        if (i % 9 == 0) {
            printf("Face %d:\n", (int)(i / 9));
        }
        if (i % 3 == 2) {
            printf("\033[0;34mZ\033[0m = %s\n", normalValue.c_str());
        } else {
            printf("%s = %s ", i % 3 == 0 ? "\033[0;31mX\033[0m" : "\033[0;32mY\033[0m", normalValue.c_str());
        }

        if (i % 9 == 8) {
            printf("\n");
        }
    }
}

void Model::printFull() {
    this->printVertices();
    this->printUVs();
    this->printNormals();
    this->print();
}

void Model::printFace(int face) {
    if (face < 0 || face > countFaces(this->vertices)) {
        printf("%sInvalid face, model has %d faces%s\n", strRed.c_str(), countFaces(this->vertices), strNoColor.c_str());
        return;
    }

    int vLength = maxLength(this->vertices);
    int uLength = maxLength(this->uvs);
    int nLength = maxLength(this->normals);

    int length = vLength > uLength ? vLength : uLength;
    length = nLength > length ? nLength : length;

    printf("Face %d:\n", face);
    printf("Vertices: \n");
    for (int i = face * 9; i < (face + 1) * 9; i++) {
        std::string value = std::to_string(this->vertices[i]);
        for (int j = value.size(); j < length; j++) {
            value.insert(0, 1, ' ');
        }
        if (i % 3 == 2) {
            printf("%sZ%s = %s\n", strBlue.c_str(), strNoColor.c_str(), value.c_str());
        } else {
            printf("%s%c%s = %s ", i % 3 == 0 ? strRed.c_str() : strGreen.c_str(), i % 3 == 0 ? 'X' : 'Y', strNoColor.c_str(), value.c_str());
        }
    }

    printf("\nUVs: \n");
    for (int i = face * 6; i < (face + 1) * 6; i++) {
        std::string value = std::to_string(this->uvs[i]);
        for (int j = value.size(); j < length; j++) {
            value.insert(0, 1, ' ');
        }
        if (i % 2 == 1) {
            printf("%sV%s = %s\n", strGreen.c_str(), strNoColor.c_str(), value.c_str());
        } else {
            printf("%sU%s = %s ", strRed.c_str(), strNoColor.c_str(), value.c_str());
        }
    }

    printf("\nNormals:\n");
    for (int i = face * 9; i < (face + 1) * 9; i++) {
        std::string value = std::to_string(this->normals[i]);
        for (int j = value.size(); j < length; j++) {
            value.insert(0, 1, ' ');
        }
        if (i % 3 == 2) {
            printf("%sZ%s = %s\n", strBlue.c_str(), strNoColor.c_str(), value.c_str());
        } else {
            printf("%s%c%s = %s ", i % 3 == 0 ? strRed.c_str() : strGreen.c_str(), i % 3 == 0 ? 'X' : 'Y', strNoColor.c_str(), value.c_str());
        }
    }
}

void Model::print() {
    printf("\nModel Print:\nSource = %s\nVertices = %d\nUVs = %d\nFaces = %d\n",
            this->source.c_str(),
            (int)(this->vertices.size() / 3),
            (int)(this->uvs.size() / 2),
            (int)(this->vertices.size() / 9));
}


