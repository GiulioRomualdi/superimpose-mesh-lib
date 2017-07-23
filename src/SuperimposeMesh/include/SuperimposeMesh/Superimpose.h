#ifndef SUPERIMPOSEHAND_H
#define SUPERIMPOSEHAND_H

#include <string>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>

#include <opencv2/core/core.hpp>


class Superimpose
{
public:
    typedef typename std::unordered_map<std::string, std::string> ObjFileMap;
    typedef typename std::pair<std::string, std::string>          ObjFilePair;
    typedef typename std::vector<double>                          ObjPose;
    typedef typename std::multimap<std::string, ObjPose>          ObjPoseMap;
    typedef typename std::pair<std::string, ObjPose>              ObjPosePair;

    virtual ~Superimpose() { };

    virtual bool superimpose(const ObjPoseMap& objpos_map, const double* cam_x, const double* cam_o, cv::Mat& img) = 0;
};

#endif /* SUPERIMPOSEHAND_H */
