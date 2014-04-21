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


#include "VO_LBPFeatures.h"


void VO_LBPFeatures::init( )
{
    VO_Features::init();
    this->m_iFeatureType    = LBP;
}


void VO_LBPFeatures::WriteFeatures( FileStorage &fs, const Mat_<float>& featureMap ) const
{
    _writeFeatures( m_vAllFeatures, fs, featureMap );
}


void VO_LBPFeatures::ReadFeatures( const FileStorage& fs, Mat_<float>& featureMap )
{
    
}


/**
 * @brief       Generating all possible feature rectangles
 * @param       size    Input    -- the concerned size
 * @param       mode    Input    -- mode, for LBP, no use
 * @return      void
 */
 void VO_LBPFeatures::VO_GenerateAllFeatureInfo(const Size& size, unsigned int mode)
 {
    this->m_CVSize = size;
    
    int offset = this->m_CVSize.width + 1;
    for( int x = 0; x < this->m_CVSize.width; x++ )
        for( int y = 0; y < this->m_CVSize.height; y++ )
            for( int w = 1; w <= this->m_CVSize.width / 3; w++ )
                for( int h = 1; h <= this->m_CVSize.height / 3; h++ )
                    if ( (x+3*w <= this->m_CVSize.width) && (y+3*h <= this->m_CVSize.height) )
                        this->m_vAllFeatures.push_back( Feature(offset, x, y, w, h ) );
    
    this->m_iNbOfFeatures     = this->m_vAllFeatures.size();
}


/**
 * @brief       Generating all features from the input image
 * @param       iImg    Input    -- the input image
 * @param       pt      Input    -- start point at the top left corner
 * @return      void
 */
void VO_LBPFeatures::VO_GenerateAllFeatures(const Mat& iImg, Point pt)
{
    if( this->m_CVSize.width > iImg.cols ||
        this->m_CVSize.height > iImg.rows ||
        pt.x <0 ||
        pt.y < 0 ||
        this->m_CVSize.width + pt.x > iImg.cols ||
        this->m_CVSize.height + pt.y > iImg.rows )
    {
        cerr << "Feature rectangles are out of the image" << endl;
    }

    Rect rect(pt.x, pt.y, this->m_CVSize.width, this->m_CVSize.height);
    Mat rectImg = iImg(rect);
    
    // Calculate the integral image
    cv::integral(rectImg, this->m_MatIntegralImage, this->m_MatSquareImage, this->m_MatTiltedIntegralImage);
    
    this->m_MatFeatures = Mat_<float>(1, this->m_iNbOfFeatures);
    for(unsigned int i = 0; i < this->m_iNbOfFeatures; i++)
    {
        this->m_MatFeatures(0, i)    =    (float) this->m_vAllFeatures[i].calc(this->m_MatIntegralImage);
    }
}


VO_LBPFeatures::Feature::Feature()
{
    rect = Rect(0, 0, 0, 0);
}


/**
 * @brief   constructor to create all LBP features
 * @param   offset  Input    -- width+1
 */
VO_LBPFeatures::Feature::Feature( int offset, int x, int y, int _blockWidth, int _blockHeight )
{
    Rect tr = rect = Rect(x, y, _blockWidth, _blockHeight);
    CV_SUM_OFFSETS( p[0], p[1], p[4], p[5], tr, offset )
    tr.x += 2*rect.width;
    CV_SUM_OFFSETS( p[2], p[3], p[6], p[7], tr, offset )
    tr.y +=2*rect.height;
    CV_SUM_OFFSETS( p[10], p[11], p[14], p[15], tr, offset )
    tr.x -= 2*rect.width;
    CV_SUM_OFFSETS( p[8], p[9], p[12], p[13], tr, offset )
}


void VO_LBPFeatures::Feature::write(FileStorage &fs) const
{
    fs << CC_RECT << "[:" << rect.x << rect.y << rect.width << rect.height << "]";
}
