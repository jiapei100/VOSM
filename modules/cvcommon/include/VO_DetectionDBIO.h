/****************************************************************************************************
*                                                                                                   *
*                   IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.               *
*                                                                                                   *
*   By downloading, copying, installing or using the software you agree to this license.            *
*   If you do not agree to this license, do not download, install, copy or use the software.        *
*                                                                                                   *
*                                   License Agreement                                               *
*                           For Vision Open Statistical Models                                      *
*                                                                                                   *
* Copyright (C):    2006~2014 by JIA Pei, all rights reserved.                                      *
*                                                                                                   *
*                   VOSM is free software under the terms of the GNU Lesser General Public License  *
*                   (GNU LGPL) as published by the Free Software Foundation; either version 3.0 of  *
*                   the License, or (at your option) any later version.                             *
*                   You can use it, modify it, redistribute it, etc; and redistribution and use in  *
*                   source and binary forms, with or without modification, are permitted provided   *
*                   that the following conditions are met:                                          *
*                                                                                                   *
*                   a) Redistribution's of source code must retain this whole paragraph of          *
*                   copyright notice, including this list of conditions and all the following       *
*                   contents in this copyright paragraph.                                           *
*                                                                                                   *
*                   b) Redistribution's in binary form must reproduce this whole paragraph of       *
*                   copyright notice, including this list of conditions and all the following       *
*                   contents in this copyright paragraph, and/or other materials provided with      *
*                   the distribution.                                                               *
*                                                                                                   *
*                   c) The name of the copyright holders may not be used to endorse or promote      *
*                   products derived from this software without specific prior written permission.  *
*                                                                                                   *
*                   Any publications based on this code must cite the following five papers,        *
*                   technic reports and on-line materials.                                          *
*                                                                                                   *
*                   1) P. JIA, 2D Statistical Models, Technical Report of Vision Open Working       *
*                   Group, 2st Edition, Oct 21, 2010.                                               *
*                   http://www.visionopen.com/members/jiapei/publications/pei_sm2dreport2010.pdf    *
*                                                                                                   *
*                   2) P. JIA. Audio-visual based HMI for an Intelligent Wheelchair.                *
*                   PhD thesis, University of Essex, 2010.                                          *
*                   http://www.visionopen.com/members/jiapei/publications/pei_thesischapter34.pdf   *
*                                                                                                   *
*                   3) T. Cootes and C. Taylor. Statistical models of appearance for computer       *
*                   vision. Technical report, Imaging Science and Biomedical Engineering,           *
*                   University of Manchester, March 8 2004.                                         *
*                                                                                                   *
*                   4) I. Matthews and S. Baker. Active appearance models revisited.                *
*                   International Journal of Computer Vision, 60(2):135–164, November 2004.         *
*                                                                                                   *
*                   5) M. B. Stegmann, Active Appearance Models: Theory, Extensions and Cases,      *
*                   http://www2.imm.dtu.dk/~aam/main/, 2000.                                        *
*                                                                                                   *
*                                                                                                   *
* Version:          0.3.4                                                                           *
* Author:           JIA Pei                                                                         *
* Contact:          jp4work@gmail.com                                                               *
* URL:              http://www.visionopen.com                                                       *
* Create Date:      2010-02-06                                                                      *
* Modify Date:      2014-04-16                                                                      *
****************************************************************************************************/


#ifndef __VO_DETECTIONDBIO_H__
#define __VO_DETECTIONDBIO_H__


#include <iostream>
#include <fstream>

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "VO_CVCommon.h"
//#include "yaml.h"
#include "VO_FaceCompPos.h"




struct PUTYMLRect {
    std::string sx;
    int x;
    std::string sy;
    int y;
    std::string swidth;
    int width;
    std::string sheight;
    int height;
};

struct PUTYMLdoc {
    std::string name;
    PUTYMLRect rect;
};



//void operator >> (const YAML::Node& node, std::vector<cv::Rect>& onePUTYML) {
//    onePUTYML.resize(5);
//    YAML::Node& face = node["Face"];
//    node["Face"] >> onePUTYML[0];
//    node["Left eye"] >> onePUTYML[1];
//    node["Right eye"] >> onePUTYML[2];
//    node["Lips"] >> onePUTYML[3];
//    node["Nose"] >> onePUTYML[4];
//}


/** 
 * @author      JIA Pei
 * @brief       IO to read/write 2D object region files, 
 *              specifically for face database PUT.
 */
class CDetectionDBIO
{
public:
    /** databases for object detection,
    * multiview face -- PUT, CASPEALR1
    * pedestrian -- MITCBCL, INRIAPerson
    * car -- MITCAR, INRIACar */
    enum DB{PUT = 0, CASPEALR1 = 1, MITCBCL = 2, 
            INRIAPerson = 3, MITCAR = 4, INRIACar = 5};

    /** for CASPEALR1, down, middle, up are separated */
    enum DMU{ DOWN = 0, MIDDLE = 1, UP = 2};

    /** Constructor */
    CDetectionDBIO() {}

    /** Destructor */
    ~CDetectionDBIO() {}

    /** Read all files from PUT face database for MVFD training */
    static void        ReadAllFilesFromPUT4MVFD(
                            const std::string& dir_path,
                            std::vector<VO_FaceCompPos>& faceComps);

    /** Read a single file from PUT face database for MVFD training */
    static void        ReadOneFileFromPUT4MVFD(
                            const std::string& filename,
                            VO_FaceCompPos& oFaceComps);

    /** Read all files from CAS-PEAL-R1 face database for MVFD training */
    static void        ReadAllFilesFromCASPEALR14MVFD(
                            const std::string& dir_path,
                            std::vector< std::vector<VO_FaceCompPos> >& faceComps);

    /** Read a single file from CAS-PEAL-R1 face database for MVFD training */
    static void        ReadOneFileFromCASPEALR14MVFD( 
                            const std::string& filename,
                            std::vector<VO_FaceCompPos>& oFaceComps);

    /** Analyze POSE filenames in CAS-PEAL-R1 face database for MVFD training */
    static void        AnalyzeFileNameFromCASPEALR14MVFD( 
                            const std::string& filename,
                            int& dmu,
                            int& degrees);

    /** Roughly estimate the face rectangle and eye rectangle of 
    CAS-PEAL-R1 face database for MVFD training */
    static void        EstimateRects4MVFD(
                            const cv::Point& leftEyeCenter,
                            const cv::Point& rightEyeCenter,
                            int dmu,
                            int degrees,
                            cv::Rect& faceRect,
                            cv::Rect& leftEyeRect,
                            cv::Rect& rightEyeRect,
                            cv::Rect& mouthRect,
                            cv::Rect& noseRect);

    /** Load Training data for shape model */
    static void        VO_LoadFaceCompTrainingData(
                            const std::vector<std::string>& allFaceCompFiles4Training,
                            unsigned int database,
                            std::vector<VO_FaceCompPos>& faceComps);
    static void        VO_LoadFaceCompTrainingData(
                            const std::vector<std::string>& allFaceCompFiles4Training,
                            unsigned int database,
                            std::vector<cv::Rect>& objRects);
};

#endif    // __VO_DETECTIONDBIO_H__

