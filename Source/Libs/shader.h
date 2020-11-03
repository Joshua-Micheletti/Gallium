#ifndef __SHADER__
#define __SHADER__

#include <vector>

typedef struct {
  unsigned int id;
  char *type;
  char *name;
} uniform_t;

class Shader {
  public:
    Shader(char *);

    unsigned int getID();
    std::vector<uniform_t> getUniformBuffer();
    std::vector<char *> getLayoutBuffer();
    char *getName();
    int getLayouts();
    void loadShader(char *, char *);

  private:
    unsigned int id;
    std::vector<uniform_t> uniformBuffer;
    std::vector<char *> layoutBuffer;
    char *name;


    unsigned int compileShader(const char *, const char *);
    void findUniformAndLayouts(char *);
};

#endif
