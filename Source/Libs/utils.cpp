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