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
* Modify Date:      2014-04-15                                                                      *
****************************************************************************************************/


#ifndef __VO_FittingAAMInverseIA__
#define __VO_FittingAAMInverseIA__


#include "VO_CVCommon.h"
#include "VO_AAMInverseIA.h"
#include "VO_Fitting2DSM.h"


/** 
 * @author      JIA Pei
 * @brief       Inverse image alignment (IA) AAM fitting algorithms, 
 *              including IAIA and CMU ICIA.
 */
class VO_FittingAAMInverseIA : public VO_Fitting2DSM
{
private:
    /** For non-rigid transform */
    cv::Mat_<float>                 m_MatCurrentP;
    cv::Mat_<float>                 m_MatEstimatedP;
    cv::Mat_<float>                 m_MatDeltaP;                // 1*20
    
    /** For rigid transform */
    cv::Mat_<float>                 m_MatCurrentQ;
    cv::Mat_<float>                 m_MatEstimatedQ;
    cv::Mat_<float>                 m_MatDeltaQ;                // 1*4
    
    /** For both rigid and non-rigid transform */
    cv::Mat_<float>                 m_MatDeltaPQ;

    /** errors */
    float                           m_E;
    float                           m_E_previous;

    /** Initialization */
    void                            init();

    /** calculate the aligned modeled shape, from the trained appearance model */
    void                            VO_PParamQParam2ModelAlignedShape(  const cv::Mat_<float>& p,
                                                                        const cv::Mat_<float>& q,
                                                                        VO_Shape& oAlignedShape);

    /** calculate the real-size modeled shape, from the trained appearance model */
    void                            VO_PParamQParam2FittingShape(   const cv::Mat_<float>& p,
                                                                    const cv::Mat_<float>& q,
                                                                    VO_Shape& oShape,
                                                                    float& scale,
                                                                    std::vector<float>& rotateAngles,
                                                                    cv::Mat_<float>& matCOG,
                                                                    unsigned int mtd = VO_Fitting2DSM::USEGLOBALSHAPENORMALIZATION);

    /** The process of CMU Inverse Compositional. Developed by Yao Wei! */
    void                            VO_CMUInverseCompositional( const cv::Mat_<float>& matDeltaP,
                                                                const cv::Mat_<float>& matDeltaQ,
                                                                const VO_Shape& s,
                                                                VO_Shape& NewS);

public:
    /** The inverse Image Alignment AAM */
    VO_AAMInverseIA*                m_VOAAMInverseIA;

    /** Constructor */
    VO_FittingAAMInverseIA();

    /** Destructor */
    ~VO_FittingAAMInverseIA();

    /** Load ICIA AAM fitting training results */
    void                            VO_LoadParameters4Fitting(const std::string& fd);

    /** Start Inverse Additive Image Alignment fitting, for static images, recording all iterations of every single image */
    float                           VO_IAIAAAMFitting(const cv::Mat& iImg, std::vector<cv::Mat>& oImages, unsigned int epoch = EPOCH, bool record = false);

    /** Start Inverse Additive Image Alignment fitting, for dynamic image sequence */
    float                           VO_IAIAAAMFitting(const cv::Mat& iImg, VO_Shape& ioShape, cv::Mat& oImg, unsigned int epoch = EPOCH);

    /** Start CMU Inverse Compositional Image Alignment fitting, for static images, recording all iterations of every single image */
    float                           VO_ICIAAAMFitting(const cv::Mat& iImg, std::vector<cv::Mat>& oImages, unsigned int epoch = EPOCH, bool record = false);

    /** Start CMU Inverse Compositional Image Alignment fitting, for dynamic image sequence */
    float                           VO_ICIAAAMFitting(const cv::Mat& iImg, VO_Shape& ioShape, cv::Mat& oImg, unsigned int epoch = EPOCH);

};

#endif

