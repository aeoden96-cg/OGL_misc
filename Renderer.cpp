#include <numeric>
#include "Renderer.hpp"

Renderer::Renderer(bool STATIC_DRAW,GLenum draw_mode):
STATIC_DRAW(STATIC_DRAW),
draw_type(STATIC_DRAW?GL_STATIC_DRAW:GL_DYNAMIC_DRAW),
VAO(0),
draw_mode(draw_mode)
{

}

void Renderer::enableVA(unsigned int numOfInputAttributes) {
    for (int i=0;i<numOfInputAttributes ; i++)
        glEnableVertexAttribArray(i);
}

void Renderer::disableVA(unsigned int numOfInputAttributes) {
    for (int i=0;i<numOfInputAttributes ; i++)
        glDisableVertexAttribArray(i);
}

void Renderer::_draw(
        const glm::mat4 &mvp,
        unsigned int count,
        Shader &current_shader,
        unsigned int numOfInputAttributes) {
    enableVA(numOfInputAttributes);

    current_shader.setMat4("MVP" ,&mvp[0][0]);

    if(!current_shader.isUsingTess())
        glDrawArrays(draw_mode,0,(int)count);
    else{
        glPatchParameteri(GL_PATCH_VERTICES,1);
        glDrawArrays(GL_PATCHES,0,(int)count);
    }

    disableVA(numOfInputAttributes);
}

void Renderer::_setup_data(
        const std::vector<GLfloat> &points,
        const std::vector<int> &positions) {

    if(STATIC_DRAW){
        this->positions = positions;
        this->NUM_OF_POINTS = points.size();
    }


    unsigned short W = std::accumulate(positions.begin(), positions.end(), 0);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (unsigned)(sizeof(GLfloat) * points.size()), &points[0], draw_type);
    int i=0;
    unsigned short formerAttribs=0;
    for (auto& currentAttrib : positions)
    {
        glVertexAttribPointer(
                i,                                              //i.th attribute
                currentAttrib,                                  //num of dimensions for ith attrib
                GL_FLOAT,
                GL_FALSE,
                (int)(sizeof(GLfloat)*W),                            //width of one row
                (const GLvoid *)(sizeof(GLfloat) * formerAttribs)   //offset
        );
        formerAttribs+=currentAttrib;
        i++;
    }
}

void Renderer::render(
        Shader &current_shader,
        std::vector<int> positions,
        const std::vector<GLfloat> &data,
        std::vector<glm::mat4> &MVPs) {

    current_shader.use();

    if (!STATIC_DRAW)
        Renderer::_setup_data(data, positions);
    else
        glBindVertexArray(VAO);

    int sum = std::accumulate(positions.begin(), positions.end(), 0);

    for (const auto& mvp: MVPs){
        Renderer::_draw(mvp,
                        data.size() / sum,   // = num of points to be rendered
                        current_shader,
                        positions.size());
    }


}

void Renderer::setup_data(const std::vector<GLfloat> &points, const std::vector<int> &positions) {
    assert(STATIC_DRAW); // data setups automatically if rendering is set to dynamic

    _setup_data(points,positions);
}

