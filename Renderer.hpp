#ifndef PROJECT_RENDERER_HPP
#define PROJECT_RENDERER_HPP

#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"




class Renderer {
private:

    unsigned long data_len;
    unsigned long sum_of_input_attributes;
    unsigned long num_of_input_attributes;


    GLuint VAO;
    int draw_type;
public:
    bool STATIC_DRAW;
    GLenum draw_mode;


private:
    void enableVA() const;
    void disableVA() const;


public:
    /**
     * Sends data to GPU.
     * @param points All data points organised AS SHOWN in 'static_positions'.
     * @param positions Shows how data points are organised by attribute.For example,
     *  (1,3) means first attribute has 1 dimension, second has 3.
     */
    void _setup_data(const std::vector<GLfloat>& points, const std::vector<int>& positions);

    /**
     * Draws ONE instance of each of n='count' points.
     * It also enables/disables each attribute for that data set.
     * @param mvp
     * @param count
     * @param current_shader
     * @param numOfInputAttributes
     */
    void _draw(const glm::mat4 &mvp, Shader &current_shader);

    Renderer(bool STATIC_DRAW = false,GLenum draw_mode = GL_POINTS);

    void render_static(Shader& shader,const std::vector<glm::mat4>& MVPs);

    /**
     * Render points in this manner:
     * for EVERY mvp in MVPs, _draw ALL points from 'data'
     * @param current_shader
     * @param positions Show how attributes are organised. For example,
     *  (1,3) means first attribute has 1 dimension, second has 3.
     * @param data data organised AS SHOWN in 'static_positions'
     * @param MVPs multiple MVP matrices,each represents instance of set of points
     */
    void render(Shader &current_shader, const std::vector<glm::mat4> &MVPs, const std::vector<int>& positions,
                const std::vector<GLfloat> &data );
};


#endif //PROJECT_RENDERER_HPP
