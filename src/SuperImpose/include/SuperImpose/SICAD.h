#ifndef SUPERIMPOSECAD_H
#define SUPERIMPOSECAD_H

#include "SuperImpose.h"

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Model.h"
#include "Shader.h"


class SICAD : public SuperImpose
{
public:
    typedef typename std::unordered_map<std::string, Model *> ObjModel;

private:
    enum MipMaps
    {
        NEAREST = 0,
        LINEAR  = 1
    };

    const std::string   log_ID_;
    
    GLFWwindow        * window_;

    bool                show_background_;
    bool                mesh_wires_;
    MipMaps             mesh_mmaps_;
    GLuint              texture_;
    GLuint              vao_;
    GLuint              ebo_;
    GLuint              vbo_;
    glm::mat4           root_to_ogl_;
    glm::mat4           back_proj_;
    glm::mat4           projection_;
    ObjModel            model_obj_;
    Shader            * shader_background_ = nullptr;
    Shader            * shader_cad_        = nullptr;

public:
    SICAD();

    virtual ~SICAD();

    bool Configure(GLFWwindow *& window, const ObjFileMap & obj2fil_map, const float EYE_FX, const float EYE_FY, const float EYE_CX, const float EYE_CY);

    bool Superimpose(const ObjPoseMap & obj2pos_map, const double * cam_x, const double * cam_o, cv::Mat & img);

    bool    getBackgroundOpt() const;
    void    setBackgroundOpt(bool show_background);

    bool    getWireframeOpt()  const;
    void    setWireframeOpt(bool mesh_wires);

    MipMaps getMipmapsOpt()    const;
};

#endif /* SUPERIMPOSECAD_H */
