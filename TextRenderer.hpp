#ifndef PROJECT_TEXTRENDERER_H
#define PROJECT_TEXTRENDERER_H

#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};



class TextRenderer {

    bool STATIC_DRAW;
    GLuint VAO,VBO;
    int draw_type;
    Shader& text_shader;

    std::map<GLchar, Character> Characters;

    void enableVA() const;
    void disableVA() const;
public:
    explicit TextRenderer(Shader& shader,bool STATIC_DRAW = false);
    int _setup_data(const std::string& filepath);
    void _draw(const glm::mat4 &mvp, Shader &current_shader);
    void render_static(Shader& shader,const std::vector<glm::mat4>& MVPs);
    void render(const std::string& text, float x, float y, float scale,const glm::vec3& color);


};


#endif //PROJECT_TEXTRENDERER_H
