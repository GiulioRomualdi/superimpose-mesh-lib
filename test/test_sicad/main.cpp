#include <cmath>
#include <exception>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <SuperimposeMesh/SICAD.h>


int main()
{
    std::string log_ID = "[Test - SICAD]";
    std::cout << log_ID << "This test checks whether the present machine can render properly using OpenGL." << std::endl;
    std::cout << log_ID << "A single mesh will be rendered on 1 viewport." << std::endl;

    SICAD::ModelPathContainer obj;
    obj.emplace("alien", "./Space_Invader.obj");

    const unsigned int cam_width_  = 320;
    const unsigned int cam_height_ = 240;
    const float        cam_fx_     = 257.34;
    const float        cam_cx_     = 160;
    const float        cam_fy_     = 120;
    const float        cam_cy_     = 257.34;

    SICAD* si_cad;
    try
    {
        si_cad = new SICAD(obj,
                           cam_width_, cam_height_, cam_fx_, cam_fy_, cam_cx_, cam_cy_,
                           1,
                           ".",
                           true);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << log_ID << "Caught error:" << std::endl << e.what();
        return EXIT_FAILURE;
    }

    Superimpose::ModelPose obj_pose(7);
    obj_pose[0] = 0;
    obj_pose[1] = 0;
    obj_pose[2] = 0;
    obj_pose[3] = 1;
    obj_pose[4] = 0;
    obj_pose[5] = 0;
    obj_pose[6] = 0;

    Superimpose::ModelPoseContainer objpose_map;
    objpose_map.emplace("alien", obj_pose);

    std::vector<Superimpose::ModelPoseContainer> objposes;
    objposes.push_back(objpose_map);

    double cam_x[] = {0.0, 0.1, 0.1};
    double cam_o[] = {1.0,   0,   0, 0};


    cv::Mat img_1;
    si_cad->superimpose(objpose_map, cam_x, cam_o, img_1);
    cv::imwrite("./Space_Invader_1.jpg", img_1);


    cv::Mat img_2;
    si_cad->superimpose(objposes, cam_x, cam_o, img_2);
    cv::imwrite("./Space_Invader_2.jpg", img_2);


    delete si_cad;

    return EXIT_SUCCESS;
}
