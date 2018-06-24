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
* Create Date:      2010-11-04                                                                      *
* Modify Date:      2014-04-17                                                                      *
****************************************************************************************************/

#ifndef __VO_ALGS_RECOGNITION_H__
#define __VO_ALGS_RECOGNITION_H__

#include <cstring>
#include "VO_CVCommon.h"
#include "VO_AdditiveStrongerClassifier.h"
#include "VO_Algs_FaceDetection.h"
#include "VO_Algs_Tracking.h"
#include "VO_FaceParts.h"
#include "VO_Shape2DInfo.h"
#include "VO_Shape.h"

#define FOCAL_LENGTH 10000000000



/** 
 * @author      JIA Pei
 * @brief       Recognition algorithms.
 */
class CRecognitionAlgs
{
protected:

    void                        init();
public:
    enum {MAHALANOBISVOTING = 0, SVM = 1};
    
    /** Constructor */
    CRecognitionAlgs();

    /** Destructor */
    virtual ~CRecognitionAlgs();

    /** Global Texture Constraint using Probability image, basically an evaluation method for current fitting effect */
    static bool                 EvaluateFaceTrackedByProbabilityImage(  CTrackingAlgs* trackalg,
                                                                        const cv::Mat& iImg,
                                                                        const VO_Shape& iShape,
                                                                        cv::Size smallSize = cv::Size(FACESMALLESTSIZE, FACESMALLESTSIZE),
                                                                        cv::Size bigSize = cv::Size(FACEBIGGESTSIZE, FACEBIGGESTSIZE) );

    /** An evaluation method for current fitting effect, basic on face components detection */
    static bool                 EvaluateFaceTrackedByCascadeDetection(  const CFaceDetectionAlgs* fd,
                                                                        const cv::Mat& iImg,
                                                                        const VO_Shape& iShape,
                                                                        const std::vector<VO_Shape2DInfo>& iShapeInfo,
                                                                        const VO_FaceParts& iFaceParts);

    /** Calculate shape distance */
    static float                ShapeDistance(const VO_Shape& shape1, const VO_Shape& shape2);

    /** Calculate fitting effect for static images */
    static bool                 CalcFittingEffect4StaticImage(  const cv::Mat_<float>& avgSParam,
                                                                const cv::Mat_<float>& icovSParam,
                                                                const cv::Mat_<float>& avgTParam,
                                                                const cv::Mat_<float>& icovTParam,
                                                                const cv::Mat_<float>& iSParams,
                                                                const cv::Mat_<float>& iTParams,
                                                                const cv::Mat_<float>& ShapeDistMean,
                                                                const cv::Mat_<float>& ShapeDistStddev,
                                                                const cv::Mat_<float>& TextureDistMean,
                                                                const cv::Mat_<float>& TextureDistStddev,
                                                                float& sDist,
                                                                float& tDist,
                                                                bool WeakFitting = true );

    /** Calculate fitting effect for dynamic images sequence */
    static bool                 CalcFittingEffect4ImageSequence(const cv::Mat_<float>& avgSParam,
                                                                const cv::Mat_<float>& icovSParam,
                                                                const cv::Mat_<float>& avgTParam,
                                                                const cv::Mat_<float>& icovTParam,
                                                                const cv::Mat_<float>& iSParams,
                                                                const cv::Mat_<float>& iTParams,
                                                                const cv::Mat_<float>& ShapeDistMean,
                                                                const cv::Mat_<float>& ShapeDistStddev,
                                                                const cv::Mat_<float>& TextureDistMean,
                                                                const cv::Mat_<float>& TextureDistStddev,
                                                                bool WeakFitting = true );

    /** Calculate face fitting effect */
    static void                 CalcShapeFittingEffect( const VO_Shape& refShape,
                                                        const VO_Shape& fittedShape,
                                                        float& deviation,
                                                        std::vector<float>& ptErrorFreq,
                                                        unsigned int nb = 20);

    /** Save shape recognition results */
    static void                 SaveShapeRecogResults(  const std::string& fd,
                                                        const std::string& fnIdx,
                                                        float deviation,
                                                        std::vector<float>& ptErrorFreq);

    /** Calculate face absolute orientations */
//    static std::vector<float>   CalcAbsoluteOrientations(   const VO_Shape& iShape2D,
//                                                            const VO_Shape& iShape3D,
//                                                            VO_Shape& oShape2D);

    /** Recognize face roll angle */
    static float                CalcFaceRoll(const std::vector<float>& iLine);

    /** Recognize face yaw angle */
    static float                CalcFaceYaw(const std::vector<float>& iLine, const VO_Shape& iShape, const VO_FaceParts& iFaceParts);

    /** Recognize face pitch angle */
    static float                CalcFacePitch(const VO_Shape& iShape, const VO_FaceParts& iFaceParts);

    /** Recognize face angles using 2D model */
    static void                 CalcFittedFaceAngle2D(std::vector<float>& angles, const VO_Shape& iShape, const VO_FaceParts& iFaceParts);

    /** Recognize face angles using 3D model */
    static void                 CalcFittedFaceAngle3D(std::vector<float>& angles, const VO_Shape& iShape, const VO_FaceParts& iFaceParts);

};

#endif  // __VO_ALGS_RECOGNITION_H__
