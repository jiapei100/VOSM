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

#include "VO_DirectFeatures.h"


/**
 * @brief Initialization
 */
void VO_DirectFeatures::init( )
{
    VO_Features::init();
    this->m_iFeatureType    = DIRECT;
}


void VO_DirectFeatures::WriteFeatures( cv::FileStorage &fs, const cv::Mat_<float>& featureMap ) const
{

}


void VO_DirectFeatures::ReadFeatures( const cv::FileStorage& fs, cv::Mat_<float>& featureMap )
{
    
}


/**
 * @brief      Generating all possible feature rectangles
 * @param      size     Input    -- the concerned size
 * @param      mode     Input    -- mode, for LBP, no use
 * @return     void
 */
 void VO_DirectFeatures::VO_GenerateAllFeatureInfo(const cv::Size& size, unsigned int mode)
 {
    this->m_CVSize             = size;
    this->m_iNbOfFeatures     = this->m_CVSize.width*this->m_CVSize.height;
}


/**
 * @brief      Generating all features within the specified rectangle from the input image
 * @param      iImg     Input    -- the input image
 * @param      pt       Input    -- start point at the top left corner
 * @return     void
 */
void VO_DirectFeatures::VO_GenerateAllFeatures(const cv::Mat& iImg, cv::Point pt)
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
    for(unsigned int i = 0; i < this->m_CVSize.height; i++)
    {
        for(unsigned int j = 0; j < this->m_CVSize.width; j++)
        {
            this->m_MatFeatures(0, i*this->m_CVSize.width+j)    =    (float)rectImg.at<uchar>(i, j);
        }
    }
}


