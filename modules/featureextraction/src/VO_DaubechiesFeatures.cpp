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


#include "VO_DaubechiesFeatures.h"


void VO_DaubechiesFeatures::init( )
{
    VO_Features::init();
    this->m_iFeatureType    = DAUBECHIES;
}


void VO_DaubechiesFeatures::WriteFeatures( cv::FileStorage &fs, const cv::Mat_<float>& featureMap ) const
{
    _writeFeatures( m_vAllFeatures, fs, featureMap );
}


void VO_DaubechiesFeatures::ReadFeatures( const cv::FileStorage& fs, cv::Mat_<float>& featureMap )
{
    
}


/**
* @brief   Generating all possible feature rectangles
* @param   size    Input    -- the concerned size
* @param   mode    Input    -- mode, for LBP, no use
* @return  void
 */
 void VO_DaubechiesFeatures::VO_GenerateAllFeatureInfo(const cv::Size& size, unsigned int mode)
 {
    this->m_CVSize = size;
    
    int offset = this->m_CVSize.width + 1;
    for( int x = 0; x < this->m_CVSize.width; x++ )
    {
        for( int y = 0; y < this->m_CVSize.height; y++ )
        {
            
        }
    }
    this->m_iNbOfFeatures   = this->m_vAllFeatures.size();
}


/**
* @brief   Generating all features within the specified rectangle from the input image
* @param   iImg     Input    -- the input image
* @param   *rect    Input    -- the concerned rectangle
* @param   mode     Input    -- mode, BASIC, CORE or ALL
* @return  void
 */
void VO_DaubechiesFeatures::VO_GenerateAllFeatures(const cv::Mat& iImg, cv::Point pt)
{
    if( this->m_CVSize.width > iImg.cols || 
        this->m_CVSize.height > iImg.rows || 
        pt.x <0 || 
        pt.y < 0 || 
        this->m_CVSize.width + pt.x > iImg.cols || 
        this->m_CVSize.height + pt.y > iImg.rows )
    {
        std::cerr << "Feature rectangles are out of the image" << std::endl;
    }

    cv::Rect rect(pt.x, pt.y, this->m_CVSize.width, this->m_CVSize.height);
    cv::Mat rectImg = iImg(rect);
    
    this->m_MatFeatures = cv::Mat_<float>(1, this->m_iNbOfFeatures);
    for(unsigned int i = 0; i < this->m_iNbOfFeatures; i++)
    {

    }
}


/** Default constructor */
VO_DaubechiesFeatures::Feature::Feature()
{
    rect = cvRect(0, 0, 0, 0);
}


/**
 * @brief   constructor to create all LBP features
 * @param   offset  Input    -- width+1
 */
VO_DaubechiesFeatures::Feature::Feature( int offset, int x, int y, int _blockWidth, int _blockHeight )
{
    cv::Rect tr = rect = cv::Rect(x, y, _blockWidth, _blockHeight);
}


void VO_DaubechiesFeatures::Feature::write(cv::FileStorage &fs) const
{
    fs << CC_RECT << "[:" << rect.x << rect.y << rect.width << rect.height << "]";
}

