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


#ifndef __VO_ASMLTCS_H__
#define __VO_ASMLTCS_H__


#include "VO_DiscreteWavelet.h"
#include "VO_AXM.h"
#include "VO_Features.h"


/** 
 * @author      JIA Pei
 * @brief       Local texture constrained ASM.
 * @note        Current VO_ASMLTCs only deal with 1 channel gray image
 */
class VO_ASMLTCs : public VO_AXM
{
friend class VO_Fitting2DSM;
friend class VO_FittingAAMBasic;
friend class VO_FittingAAMForwardIA;
friend class VO_FittingAAMInverseIA;
friend class VO_FittingASMLTCs;
friend class VO_FittingASMNDProfiles;
friend class VO_FittingAFM;
protected:
    /** Local texture constrained ASM, local features */
    VO_Features*                    m_pVOfeatures;

    /** Local texture constrained methods */
    unsigned int                    m_iLTCMethod;

    /** length of LTC std::vector in format of rr...rrgg...ggbb...bb . */
    unsigned int                    m_iNbOfLTC4PerPoint;

    /** All loaded LTCs in a std::vector format. m_iNbOfSamples*m_iNbOfPyramidLevels*(m_iNbOfcv::Points*m_iNbOfLTC4PerPoint) */
    std::vector< std::vector< cv::Mat_<float> > >    m_vvLTCs;

    /** All normalized LTCs in a std::vector format. m_iNbOfSamples*m_iNbOfPyramidLevels*(m_iNbOfcv::Points*m_iNbOfLTC4PerPoint) */
    std::vector< std::vector< cv::Mat_<float> > >    m_vvNormalizedLTCs;
    
    /** mean LTC for all concerned points. m_iNbOfPyramidLevels*m_iNbOfcv::Points*(1*m_iNbOfLTC4PerPoint) */
    std::vector< std::vector< cv::Mat_<float> > >    m_vvLTCMeans;
    
    /** LTC covariance for all concerned points. m_iNbOfPyramidLevels*m_iNbOfcv::Points*(m_iNbOfLTC4PerPoint*m_iNbOfLTC4PerPoint) */
    std::vector< std::vector< cv::Mat_<float> > >    m_vvCVMInverseOfLTCCov;

    /** image cv::Size for wavelet transform */
    cv::Size                         m_localImageSize;

    /** Initialization */
    void                             init();

public:
    /** Default constructor to create a VO_ASMLTCs object */
    VO_ASMLTCs();

    /** Destructor */
    virtual ~VO_ASMLTCs();

    /** Build ASMLTCs model */
    void                             VO_BuildASMLTCs (  const std::vector<std::string>& allLandmarkFiles4Training,
                                                        const std::vector<std::string>& allImgFiles4Training,
                                                        const std::string& shapeinfoFileName,
                                                        unsigned int database,
                                                        unsigned int channels = 1,
                                                        unsigned int levels = 4,
                                                        int trm = VO_Features::DIRECT,
                                                        float TPShape = 0.95f,
                                                        bool useKnownTriangles = false,
                                                        unsigned int ltcMtd = VO_Features::DIRECT,
                                                        cv::Size imgSize = cv::Size(16, 16) );

    /** wavelet localization */
    static cv::Rect                 VO_CalcImagePatchRect(const cv::Mat& iImg, const cv::Point2f& pt, cv::Size imgSize);

    /** Load Training data for LTC model */
    void                            VO_LoadLTCTrainingData();

    /** load LTC around 1 single point for 1 single channel */
    static void                     VO_LoadLTC4OneAnnotatedPoint(const cv::Mat& iImg,
                                                                    const VO_Shape& theShape,
                                                                    unsigned int ptIdx,
                                                                    cv::Size imgSize,
                                                                    VO_Features* vofeatures,
                                                                    int shiftX = 0,
                                                                    int shiftY = 0);

    /** calculate statistics */
    void                            VO_CalcStatistics4AllLTCs();

    /** Output one wavelet transformed image, for the purpose of demonstration */
    void                            VO_HardSaveWaveletSingleChannelImage(   const std::string& fn, 
                                                                            cv::Size imgSize,
                                                                            unsigned int displayMtd = STRETCH);

    /** Save ASM LTCs, to a specified folder */
    void                            VO_Save(const std::string& fd);

    /** Load all parameters */
    void                            VO_Load(const std::string& fd);

    /** Load parameters for fitting */
    void                            VO_LoadParameters4Fitting(const std::string& fd);
};

#endif  // __VO_ASMLTCS_H__

