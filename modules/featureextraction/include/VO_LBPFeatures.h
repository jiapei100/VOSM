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
* Create Date:      2010-03-08                                                                      *
* Modify Date:      2014-04-15                                                                      *
****************************************************************************************************/


#ifndef _VO_LBPFEATURES_H_
#define _VO_LBPFEATURES_H_

#include "VO_Features.h"

#define CC_LBP  "LBP"
//#define CC_RECT "rect"

//#define LBPF_NAME "lbpFeatureParams"


/** 
 * @author      JIA Pei
 * @brief       LBP features.
 */
class VO_LBPFeatures : public VO_Features
{
protected:
    class Feature
    {
    public:
        Feature();
        Feature( int offset, int x, int y, int _block_w, int _block_h  ); 
        uchar   calc( const cv::Mat& _sum ) const;
        void    write( cv::FileStorage &fs ) const;

        cv::Rect    rect;
        int         p[16];
    };
    
    std::vector<Feature>        m_vAllFeatures;
    
    /** Initialization */
    void                        init();
    
public:
    /** default constructor */
    VO_LBPFeatures ()           {this->m_iFeatureType = LBP;}

    /** destructor */
    virtual ~VO_LBPFeatures()   {this->m_vAllFeatures.clear();}

    /** Generate all features with a specific mode */
    virtual void                VO_GenerateAllFeatureInfo(const cv::Size& size, unsigned int generatingMode = 0);
    virtual void                VO_GenerateAllFeatures(const cv::Mat& iImg, cv::Point pt = cv::Point(0,0));
    
    /** Read and write */
    virtual void                ReadFeatures( const cv::FileStorage& fs, cv::Mat_<float>& featureMap );
    virtual void                WriteFeatures( cv::FileStorage &fs, const cv::Mat_<float>& featureMap ) const;
};


/**
 * @brief            calculate one feature
 * @param            _sum            Input    -- integral image
 */
inline uchar VO_LBPFeatures::Feature::calc(const cv::Mat &_sum) const
{
    const int* sum = _sum.ptr<int>(0);
    int cval = sum[p[5]] - sum[p[6]] - sum[p[9]] + sum[p[10]];

    return (uchar)( (sum[p[0]] - sum[p[1]] - sum[p[4]] + sum[p[5]] >= cval ? 128 : 0) |   // 0
                    (sum[p[1]] - sum[p[2]] - sum[p[5]] + sum[p[6]] >= cval ? 64 : 0) |    // 1
                    (sum[p[2]] - sum[p[3]] - sum[p[6]] + sum[p[7]] >= cval ? 32 : 0) |    // 2
                    (sum[p[6]] - sum[p[7]] - sum[p[10]] + sum[p[11]] >= cval ? 16 : 0) |  // 5
                    (sum[p[10]] - sum[p[11]] - sum[p[14]] + sum[p[15]] >= cval ? 8 : 0) | // 8
                    (sum[p[9]] - sum[p[10]] - sum[p[13]] + sum[p[14]] >= cval ? 4 : 0) |  // 7
                    (sum[p[8]] - sum[p[9]] - sum[p[12]] + sum[p[13]] >= cval ? 2 : 0) |   // 6
                    (sum[p[4]] - sum[p[5]] - sum[p[8]] + sum[p[9]] >= cval ? 1 : 0));     // 3
}

#endif
