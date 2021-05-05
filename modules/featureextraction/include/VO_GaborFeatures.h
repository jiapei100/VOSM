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

#ifndef _VO_GABORFEATURES_H_
#define _VO_GABORFEATURES_H_

#include "VO_Features.h"
#include "VO_Gabor.h"

#define CC_RECTS        "rects"
#define CC_TILTED       "tilted"


#define NBOFLAMBDA      3
#define UNDIRTHETA      4
#define DIRTHETA        8
#define SIGMA           4
#define NBOFGAMMA       3


//#define HFP_NAME "gaborFeatureParams"


/** 
 * @author          JIA Pei
 * @brief           Gabor features.
 */
class VO_GaborFeatures : public VO_Features
{
protected:
    /** which Haar mode is to be used? ISOTROPY, ANISOTROPY or ALL? */
    unsigned int        m_iMode;

    class Feature
    {
    public:
        Feature();
        Feature(int offset,
                int x,
                int y,
                bool filtering,
                unsigned int nstds,
                float lambda,
                float theta,
                float psi,
                float sigma,
                float gamma  ); 
        float           filter( const cv::Mat_<float>& iImg );
        void            calc( const cv::Mat_<float>& iImg );
        void            write( cv::FileStorage &fs ) const;

        bool            isFiltering;
        cv::Rect        rect;
        VO_Gabor        gabor;
        cv::Mat_<float> freqs;
    };

    std::vector<Feature> m_vAllFeatures;

    /** Initialization */
    void                init();

public:
    /* 0 - ISOTROPY
    *  1 - ANISOTROPY
    *  2 - ALL   = including 45 degrees */
    enum { ISOTROPY = 0, ANISOTROPY = 1, ALL = 2 };

    /** default constructor */
    VO_GaborFeatures ()         {this->m_iFeatureType = GABOR;}

    /** destructor */
    virtual ~VO_GaborFeatures () {this->m_vAllFeatures.clear();}

    /** Generate all features with a specific mode */
    virtual void                VO_GenerateAllFeatureInfo(const cv::Size& size, unsigned int generatingMode = ISOTROPY);
    virtual void                VO_GenerateAllFeatures(const cv::Mat& iImg, cv::Point pt = cv::Point(0,0));

    /** Read and write */
    virtual void                ReadFeatures( const cv::FileStorage& fs, cv::Mat_<float>& featureMap );
    virtual void                WriteFeatures( cv::FileStorage& fs, const cv::Mat_<float>& featureMap ) const;
};


/**
 * @brief   Gabor filtering
 * @param   iImg    Input    -- input image
 */
inline float VO_GaborFeatures::Feature::filter( const cv::Mat_<float>& iImg )
{
    return gabor.VO_GaborFiltering(iImg);
}


/**
 * @brief   calculate one feature
 * @param   iImg    Input    -- input image
 */
inline void VO_GaborFeatures::Feature::calc(const cv::Mat_<float>& iImg)
{
    gabor.VO_ForwardTransform(iImg, freqs);
}

#endif      // _VO_GABORFEATURES_H_

