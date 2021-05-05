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
* Copyright (C):    2006~2021 by JIA Pei, all rights reserved.                                      *
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
* Version:          0.4.0                                                                           *
* Author:           JIA Pei                                                                         *
* Contact:          jiapei@longervision.com                                                         *
* URL:              http://www.longervision.com                                                     *
* Create Date:      2010-11-04                                                                      *
* Modify Date:      2014-04-17                                                                      *
* Modify Date:      2021-05-04                                                                      *
****************************************************************************************************/

#ifndef __VO_ALGS_EVALUATION_H__
#define __VO_ALGS_EVALUATION_H__

#include <vector>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>

/** 
 * @author      JIA Pei
 * @brief       Some concerned evaluation algorithms to evaluate 
 *              the detection performance or the fitting performance.
 */
class CEvaluationAlgs
{
public:
    enum {CRISTINACCEDEYES = 1};
    
    /** Constructor */
    CEvaluationAlgs(unsigned int mtd=CEvaluationAlgs::CRISTINACCEDEYES);

    /** Destructor */
    virtual ~CEvaluationAlgs();
    
    /** Is a point in a rect? */
    static bool                 IsPointInRect(const cv::Point2d& pt, const cv::Rect& rect);

    /** A standard way to evaluate detection result. */
    static void                 StandardDetectionEvaluation(const cv::Rect& detectedObjRect,
                                                            const cv::Rect& loadedObjRect,
                                                            double& oar,
                                                            double& co);

    /** Estimate 2 eye centers. */
    static void                 EstimateEyeCenters( const cv::Rect& face,
                                                    cv::Point2d& leftEyeCenter,
                                                    cv::Point2d& rightEyeCenter);

    /** Cristinacce Distance to evaluate the eye detection accuracy. */
    static std::vector<double>  CristinacceDEyes(const std::vector<cv::Rect>& detectedFaces,
                                                 const std::vector<cv::Point2d>& leftEyeCenters,
                                                 const std::vector<cv::Point2d>& rightEyeCenters );

    /** DEyes - Refer to Cristinacce's paper  */
    static std::vector<int>     DEyesEval(const std::vector<double>& dEyess,
                                          unsigned int& dEyeWrong,
                                          double mindEyes = 0.0,
                                          double maxdEyes = 0.5,
                                          unsigned int nb = 100 );

    /** Cristinacce Distance to evaluate the eye detection accuracy. */
    static std::vector<double>  MSEFaceComp(const std::vector<cv::Rect>& detectedFaceComp,
                                            const std::vector<cv::Point2d>& faceCompCenters );
    
};

#endif  // __VO_ALGS_EVALUATION_H__

