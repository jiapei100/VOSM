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


#ifndef __VO_FittingASMNDProfiles__
#define __VO_FittingASMNDProfiles__

#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "VO_CVCommon.h"
#include "VO_ASMNDProfiles.h"
#include "VO_Fitting2DSM.h"



/** 
 * @author      JIA Pei
 * @brief       1D and 2D Profile ASM fitting algorithms.
 */
class VO_FittingASMNDProfiles : public VO_Fitting2DSM
{
private:
    /** scale between original input image and search image */
    float                   m_fScale2;

    /** Initialization */
    void                    init();

public:
    /** The NDProfile ASM model */
    VO_ASMNDProfiles*       m_VOASMNDProfile;

    /** constructor */
    VO_FittingASMNDProfiles();

    /** destructor */
    ~VO_FittingASMNDProfiles();

    /** Find the best matching by 1D Profile ASM, in a single level */
    static int              VO_FindBestMatchingProfile1D(   const cv::Mat& iImg,
                                                            const cv::Point2f& ThisPoint,
                                                            const cv::Mat_<float>& iMean,
                                                            const cv::Mat_<float>& iCovInverse,
                                                            unsigned int ProfileLength,
                                                            unsigned int offSetTolerance,
                                                            float& DeltaX,
                                                            float& DeltaY);

    /** Update shape, in a single iteration */
    static int              UpdateShape(    const VO_ASMNDProfiles* asmmodel,
                                            const cv::Mat& iImg,
                                            VO_Shape& ioShape,
                                            const std::vector<VO_Shape2DInfo>& iShapeInfo,
                                            const std::vector< VO_Profile >& iMean,
                                            const std::vector< std::vector< cv::Mat_<float> > >& iCovInverse,
                                            unsigned int offSetTolerance,
                                            unsigned int profdim = 2);

    /** Pyramid Fitting */
    void                    PyramidFit( VO_Shape& ioShape,
                                        const cv::Mat& iImg,
                                        std::vector<cv::Mat>& oImages,
                                        unsigned int iLev,
                                        float PClose = 0.90f,
                                        unsigned int epoch = VO_Fitting2DSM::EPOCH,
                                        unsigned int profdim = 2,
                                        bool record = false);

    /** Pyramid Fitting */
    void                    PyramidFit( VO_Shape& ioShape,
                                        const cv::Mat& iImg,
                                        unsigned int iLev,
                                        float PClose = 0.90f,
                                        unsigned int epoch = VO_Fitting2DSM::EPOCH,
                                        unsigned int profdim = 2);

    /** Load ASM fitting training results */
    void                    VO_LoadParameters4Fitting(const std::string& fd);

    /** Start ASM ND Profile fitting, for static images, recording all iterations of every single image */
    float                   VO_ASMNDProfileFitting( const cv::Mat& iImg,
                                                    std::vector<cv::Mat>& oImages,
                                                    unsigned int epoch = VO_Fitting2DSM::EPOCH,
                                                    unsigned int pyramidlevel = 4,
                                                    unsigned int profdim = 2,
                                                    bool record = false);

    /** Start ASM ND Profile fitting, for dynamic image sequence */
    float                   VO_ASMNDProfileFitting( const cv::Mat& iImg,
                                                    VO_Shape& ioShape,
                                                    cv::Mat& oImg,
                                                    unsigned int epoch = 4,
                                                    unsigned int pyramidlevel = 4,
                                                    unsigned int profdim = 2);
};

#endif  // __VO_FittingASMNDProfiles__

