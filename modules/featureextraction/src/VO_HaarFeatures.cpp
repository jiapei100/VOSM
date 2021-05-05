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

#include "VO_HaarFeatures.h"


void VO_HaarFeatures::init( )
{
    VO_Features::init();
    this->m_iFeatureType    = HAAR;
}


void VO_HaarFeatures::WriteFeatures( cv::FileStorage &fs, const cv::Mat_<float>& featureMap ) const
{
    _writeFeatures( m_vAllFeatures, fs, featureMap );
}


void VO_HaarFeatures::ReadFeatures( const cv::FileStorage& fs, cv::Mat_<float>& featureMap )
{
    
}


/**
 * @brief      Generating all possible feature rectangles
 * @param      size    Input    -- the concerned size
 * @param      mode    Input    -- mode, BASIC, CORE or ALL
 * @return     void
 */
 void VO_HaarFeatures::VO_GenerateAllFeatureInfo(const cv::Size& size, unsigned int mode)
 {
    this->m_CVSize = size;
    
    int offset = this->m_CVSize.width + 1;            // integral image is (m_CVSize.height+1)*(m_CVSize.width+1)
    for( int x = 0; x < this->m_CVSize.width; x++ )
    {
        for( int y = 0; y < this->m_CVSize.height; y++ )
        {
            for( int dx = 1; dx <= this->m_CVSize.width; dx++ )
            {
                for( int dy = 1; dy <= this->m_CVSize.height; dy++ )
                {
                    // haar_x2
                    if ( (x+dx*2 <= this->m_CVSize.width) && (y+dy <= this->m_CVSize.height) )
                    {
                        m_vAllFeatures.push_back( Feature( offset, false,
                        x,    y, dx, dy, -1,
                        x+dx, y, dx, dy, +1 ) );
                    }
                    // haar_y2
                    if ( (x+dx <= this->m_CVSize.width) && (y+dy*2 <= this->m_CVSize.height) ) 
                    {
                        m_vAllFeatures.push_back( Feature( offset, false,
                        x, y,    dx, dy, -1,
                        x, y+dy, dx, dy, +1 ) );
                    }
                    // haar_x3
                    if ( (x+dx*3 <= this->m_CVSize.width) && (y+dy <= this->m_CVSize.height) )
                    {
                        m_vAllFeatures.push_back( Feature( offset, false,
                        x,    y, dx*3, dy, -1,
                        x+dx, y, dx  , dy, +3 ) );
                    }
                    // haar_y3
                    if ( (x+dx <= this->m_CVSize.width) && (y+dy*3 <= this->m_CVSize.height) )
                    {
                        m_vAllFeatures.push_back( Feature( offset, false,
                        x, y,    dx, dy*3, -1,
                        x, y+dy, dx, dy,   +3 ) );
                    }
                    if( mode != VO_HaarFeatures::BASIC )
                    {
                        // haar_x4
                        if ( (x+dx*4 <= this->m_CVSize.width) && (y+dy <= this->m_CVSize.height) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, false,
                            x,    y, dx*4, dy, -1,
                            x+dx, y, dx*2, dy, +2 ) );
                        }
                        // haar_y4
                        if ( (x+dx <= this->m_CVSize.width) && (y+dy*4 <= this->m_CVSize.height ) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, false,
                            x, y,    dx, dy*4, -1,
                            x, y+dy, dx, dy*2, +2 ) );
                        }
                    }
                    // x2_y2
                    if ( (x+dx*2 <= this->m_CVSize.width) && (y+dy*2 <= this->m_CVSize.height) ) 
                    {
                        m_vAllFeatures.push_back( Feature( offset, false,
                        x,    y,    dx*2, dy*2, -1,
                        x,    y,    dx,   dy,   +2,
                        x+dx, y+dy, dx,   dy,   +2 ) );
                    }
                    if (mode != VO_HaarFeatures::BASIC) 
                    {
                        // x3_y3
                        if ( (x+dx*3 <= this->m_CVSize.width) && (y+dy*3 <= this->m_CVSize.height) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, false,
                            x   , y   , dx*3, dy*3, -1,
                            x+dx, y+dy, dx  , dy  , +9) );
                        }
                    }
                    if (mode == VO_HaarFeatures::ALL) 
                    {
                        // tilted haar_x2
                        if ( (x+2*dx <= this->m_CVSize.width) && (y+2*dx+dy <= this->m_CVSize.height) && (x-dy>= 0) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, true,
                            x,       y, dx, dy, -1,
                            x+dx, y, dx, dy, +1 ) );
                        }
                        // tilted haar_y2
                        if ( (x+dx <= this->m_CVSize.width) && (y+dx+2*dy <= this->m_CVSize.height) && (x-2*dy>= 0) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, true,
                            x, y,      dx, dy, -1,
                            x, y+dy, dx, dy, +1 ) );
                        }
                        // tilted haar_x3
                        if ( (x+3*dx <= this->m_CVSize.width) && (y+3*dx+dy <= this->m_CVSize.height) && (x-dy>= 0) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, true,
                            x,    y, dx*3, dy, -1,
                            x+dx, y, dx,   dy, +3 ) );
                        }
                        // tilted haar_y3
                        if ( (x+dx <= this->m_CVSize.width) && (y+dx+3*dy <= this->m_CVSize.height) && (x-3*dy>= 0) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, true,
                            x, y,    dx, dy*3, -1,
                            x, y+dy, dx, dy,   +3 ) );
                        }
                        // tilted haar_x4
                        if ( (x+4*dx <= this->m_CVSize.width) && (y+4*dx+dy <= this->m_CVSize.height) && (x-dy>= 0) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, true,
                            x,    y, dx*4, dy, -1,
                            x+dx, y, dx*2, dy, +2 ) );
                        }
                        // tilted haar_y4
                        if ( (x+dx <= this->m_CVSize.width) && (y+dx+4*dy <= this->m_CVSize.height) && (x-4*dy>= 0) ) 
                        {
                            m_vAllFeatures.push_back( Feature( offset, true,
                            x, y,    dx, dy*4, -1,
                            x, y+dy, dx, dy*2, +2 ) );
                        }
                    }
                }
            }
        }
    }

    this->m_iMode             = mode;
    this->m_iNbOfFeatures     = this->m_vAllFeatures.size();
}
 

/**
 * @brief      Generating all features from the input image
 * @param      iImg     Input    -- the input image
 * @param      pt       Input    -- start point at the top left corner
 * @return     void
 */
void VO_HaarFeatures::VO_GenerateAllFeatures(const cv::Mat& iImg, cv::Point pt)
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

    // Calculate the integral image
    cv::integral(rectImg, this->m_MatIntegralImage, this->m_MatSquareImage, this->m_MatTiltedIntegralImage);

    this->m_MatFeatures = cv::Mat_<float>(1, this->m_iNbOfFeatures);
    for(unsigned int i = 0; i < this->m_iNbOfFeatures; i++)
    {
        this->m_MatFeatures(0, i)    =    this->m_vAllFeatures[i].calc(this->m_MatIntegralImage, this->m_MatTiltedIntegralImage);
    }
}


/** Default constructor */
VO_HaarFeatures::Feature::Feature()
{
    tilted = false;
    rect[0].r = rect[1].r = rect[2].r = cv::Rect(0,0,0,0);
    rect[0].weight = rect[1].weight = rect[2].weight = 0;
}


/**
* @brief   constructor to create all Haar features, Haar features an be computed from at most 3 rectangles.
* @param   offset     Input    -- width+1
* @param   _tilted    Input    -- wether the image is tilted or not
 */
VO_HaarFeatures::Feature::Feature( int offset, bool _tilted,
                                  int x0, int y0, int w0, int h0, float wt0,
                                  int x1, int y1, int w1, int h1, float wt1,
                                  int x2, int y2, int w2, int h2, float wt2 )
{
    tilted = _tilted;

    rect[0].r.x = x0;
    rect[0].r.y = y0;
    rect[0].r.width  = w0;
    rect[0].r.height = h0;
    rect[0].weight   = wt0;

    rect[1].r.x = x1;
    rect[1].r.y = y1;
    rect[1].r.width  = w1;
    rect[1].r.height = h1;
    rect[1].weight   = wt1;

    rect[2].r.x = x2;
    rect[2].r.y = y2;
    rect[2].r.width  = w2;
    rect[2].r.height = h2;
    rect[2].weight   = wt2;

    if( !tilted )
    {
        for( int j = 0; j < CV_HAAR_FEATURE_MAX; j++ )
        {
            if( rect[j].weight == 0.0F )
                break;
            CV_SUM_OFFSETS( fastRect[j].p0, fastRect[j].p1, fastRect[j].p2, fastRect[j].p3, rect[j].r, offset )
        }
    }
    else
    {
        for( int j = 0; j < CV_HAAR_FEATURE_MAX; j++ )
        {
            if( rect[j].weight == 0.0F )
                break;
            CV_TILTED_OFFSETS( fastRect[j].p0, fastRect[j].p1, fastRect[j].p2, fastRect[j].p3, rect[j].r, offset )
        }
    }
}


void VO_HaarFeatures::Feature::write( cv::FileStorage &fs ) const
{
    fs << CC_RECTS << "[";
    for( int ri = 0; ri < CV_HAAR_FEATURE_MAX && rect[ri].r.width != 0; ++ri )
    {
        fs << "[:" << rect[ri].r.x << rect[ri].r.y << 
            rect[ri].r.width << rect[ri].r.height << rect[ri].weight << "]";
    }
    fs << "]" << CC_TILTED << tilted;
}
