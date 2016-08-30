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


#ifndef __VO_AXM_H__
#define __VO_AXM_H__


#include <vector>
#include <deque>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "VO_TextureModel.h"



/** 
 * @author      JIA Pei
 * @brief       Generalized class for various models.
 */
class VO_AXM : public VO_TextureModel
{
friend class VO_Fitting2DSM;
friend class VO_FittingAAMBasic;
friend class VO_FittingAAMForwardIA;
friend class VO_FittingAAMInverseIA;
friend class VO_FittingASMLTCs;
friend class VO_FittingASMNDProfiles;
friend class VO_FittingAFM;
protected:
    /** Number of Levels */
    unsigned int                    m_iNbOfPyramidLevels;
    
    /** objective functions -- ASMNDProfile, ASMLTC, AAMBasic, AAMICIA, CLM, AFM, etc */
    unsigned int                    m_iMethod;
    
    /** Initialization */
    void                            init(unsigned int method = ASM_PROFILEND, unsigned int levels = 4)
    {
        this->m_iMethod             = method;
        this->m_iNbOfPyramidLevels  = levels;
    }

public:
    /** The following classification is correct. CLM belongs to AFM */
    enum {  ASM_PROFILEND = 1,
            ASM_LTC = 2,
            CLM = 8, AFM = 9,
            AAM_BASIC = 10, AAM_DIRECT=11, AAM_FAIA = 12, AAM_CMUICIA = 13, AAM_IAIA = 14,
            MM3D = 20, AAM3D  =21 };

    /** Default constructor to create a VO_AXM object */
    VO_AXM(unsigned int method = ASM_PROFILEND, unsigned int levels = 1)
    {
        this->init(method, levels);
    }

    /** Destructor */
    virtual ~VO_AXM() {}
    
    void                            SplitShapeTextureParams(const std::pair<VO_Shape, VO_Texture>& iPairShapeTexture, 
                                                            cv::Mat_<float>& oShapeParams, 
                                                            cv::Mat_<float>& oTextureParams );
    void                            CombineShapeTextureParams(  const cv::Mat_<float>& iShapeParams, 
                                                                const cv::Mat_<float>& iTextureParams,
                                                                std::pair<VO_Shape, VO_Texture>& oPairShapeTexture );
    
    /** Save ASM, to a specified folder */
    void                            VO_Save(const std::string& fd);

    /** Load all parameters */
    void                            VO_Load(const std::string& fd);

    /** Load parameters for fitting */
    void                            VO_LoadParameters4Fitting(const std::string& fd);
};

#endif  // __VO_AXM_H__

