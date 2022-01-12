#include <numeric>
#include "Renderer.hpp"

Renderer::Renderer(bool STATIC_DRAW,GLenum draw_mode):
STATIC_DRAW(STATIC_DRAW),
draw_type(STATIC_DRAW?GL_STATIC_DRAW:GL_DYNAMIC_DRAW),
VAO(0),
draw_mode(draw_mode)
{

}

void Renderer::enableVA() const {
    for (int i=0;i<this->num_of_input_attributes ; i++)
        glEnableVertexAttribArray(i);
}

void Renderer::disableVA() const {
    for (int i=0;i<this->num_of_input_attributes ; i++)
        glDisableVertexAttribArray(i);
}

void Renderer::_draw(const glm::mat4 &mvp, Shader &current_shader) {

    unsigned int count = this->data_len / this->sum_of_input_attributes;

    enableVA();

    current_shader.setMat4("MVP" ,&mvp[0][0]);

    if(!current_shader.isUsingTess())
        glDrawArrays(draw_mode,0,(int)count);
    else{
        glPatchParameteri(GL_PATCH_VERTICES,1);
        glDrawArrays(GL_PATCHES,0,(int)count);
    }

    disableVA();
}

void Renderer::_setup_data(
        const std::vector<GLfloat> &points,
        const std::vector<int> &positions) {

    this->data_len = points.size();

    this->sum_of_input_attributes = std::accumulate(positions.begin(), positions.end(), 0);
    this->num_of_input_attributes = positions.size();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (unsigned)(sizeof(GLfloat) * this->data_len ), &points[0], draw_type);
    int i=0;
    unsigned short formerAttribs=0;
    for (auto& currentAttrib : positions)
    {
        glVertexAttribPointer(
                i,                                                  //i.th attribute
                currentAttrib,                                      //num of dimensions for ith attrib
                GL_FLOAT,
                GL_FALSE,
                (int)(sizeof(GLfloat)* this->sum_of_input_attributes ),        //width of one row
                (const GLvoid *)(sizeof(GLfloat) * formerAttribs)   //offset
        );
        formerAttribs+=currentAttrib;
        i++;
    }
}

void Renderer::render_static(Shader& shader,const std::vector<glm::mat4>& MVPs){
    assert(STATIC_DRAW);
    this->render(shader,MVPs,{},std::vector<GLfloat>());
}

void Renderer::render(Shader &current_shader, const std::vector<glm::mat4> &MVPs, const std::vector<int>& positions,
                      const std::vector<GLfloat> &data ) {

    current_shader.use();

    if (!STATIC_DRAW)
        Renderer::_setup_data(data, positions);
    else
        glBindVertexArray(VAO);

    for (const auto& mvp: MVPs){
        Renderer::_draw(mvp,current_shader);
    }


}



