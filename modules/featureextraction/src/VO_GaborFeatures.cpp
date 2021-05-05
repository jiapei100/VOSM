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

#include "VO_GaborFeatures.h"


void VO_GaborFeatures::init( )
{
    VO_Features::init();
    this->m_iFeatureType    = GABOR;
}


void VO_GaborFeatures::WriteFeatures( cv::FileStorage &fs, const cv::Mat_<float>& featureMap ) const
{
    _writeFeatures( m_vAllFeatures, fs, featureMap );
}


void VO_GaborFeatures::ReadFeatures( const cv::FileStorage& fs, cv::Mat_<float>& featureMap )
{

}


/**
 * @brief      Generating all possible feature rectangles
 * @param      size     Input    -- the concerned size
 * @param      mode     Input    -- mode, for LBP, no use
 * @return     void
 */
 void VO_GaborFeatures::VO_GenerateAllFeatureInfo(const cv::Size& size, unsigned int mode)
 {
    this->m_CVSize = size;
    int NbOfTheta = mode == ALL ? DIRTHETA : UNDIRTHETA;

    const unsigned int nstds    = 4;
    float sigma_x, sigma_y, lambda, theta, gamma;
    int xmax, ymax;
    int offset = this->m_CVSize.width + 1;
    for( int x = 0; x < this->m_CVSize.width; x++ )
    {
        for( int y = 0; y < this->m_CVSize.height; y++ )
        {
//            for(int nstds = 1; nstds <= NBOFSTDS; nstds++)
//            {
                for(int nlambda = 0; nlambda < NBOFLAMBDA; nlambda++)
                {
                    for(int ntheta = 0; ntheta < NbOfTheta; ntheta++)
                    {
                        for(int psi = 0; psi <=0; psi++)
                        {
                            for(int sigma = 1; sigma <= SIGMA; sigma++)
                            {
                                for(int ngamma = 0; ngamma < NBOFGAMMA; ngamma++)
                                {
                                    lambda = pow(2.0, (double)(nlambda-NBOFLAMBDA/2.0));
                                    gamma = pow(2.0, (double)(ngamma-NBOFGAMMA/2.0));
                                    theta = 2.0f*CV_PI*(float)ntheta/(float)NbOfTheta;
                                    sigma_x = (float)sigma;
                                    sigma_y = (float)sigma/(float)gamma;
                                    xmax = ceil( std::max(1.0, std::max(fabs((float)nstds*sigma_x*cos((float)theta)),fabs((float)nstds*sigma_y*sin((float)theta))) ) );
                                    ymax = ceil( std::max(1.0, std::max(fabs((float)nstds*sigma_x*sin((float)theta)),fabs((float)nstds*sigma_y*cos((float)theta))) ) );

                                    if( (x+2*xmax+1 <= m_CVSize.width) && (y+2*ymax+1 <= this->m_CVSize.height) )
                                        this->m_vAllFeatures.push_back( Feature(offset, x, y, true,
                                                                        nstds,
                                                                        lambda,
                                                                        theta,
                                                                        psi,
                                                                        sigma,
                                                                        gamma) );
                                }
                            }
                        }
                    }
                }
//            }
        }
    }

    this->m_iMode             = mode;
    this->m_iNbOfFeatures     = this->m_vAllFeatures.size();
}


/**
 * @brief       Generating all features within the specified rectangle from the input image
 * @param       iImg    Input    -- the input image
 * @param       pt      Input    -- start point at the top left corner
 * @return      void
 */
void VO_GaborFeatures::VO_GenerateAllFeatures(const cv::Mat& iImg, cv::Point pt)
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
    cv::Mat_<float> rectImg = iImg(rect);


    this->m_MatFeatures = cv::Mat_<float>(1, this->m_iNbOfFeatures);
    for(unsigned int i = 0; i < this->m_iNbOfFeatures; i++)
    {
        if(this->m_vAllFeatures[i].isFiltering)
            this->m_MatFeatures(0, i)    =    m_vAllFeatures[i].filter(rectImg);
        else
            this->m_vAllFeatures[i].calc(rectImg);
    }
}


/** Default constructor */
VO_GaborFeatures::Feature::Feature()
{
    isFiltering = true;
    rect = cv::Rect(0, 0, 0, 0);
}


/**
 * @brief   constructor to create all LBP features
 * @param   offset      Input    -- width+1
 */
VO_GaborFeatures::Feature::Feature( int offset,
                                    int x,
                                    int y,
                                    bool filtering,
                                    unsigned int nstds,
                                    float lambda,
                                    float theta,
                                    float psi,
                                    float sigma,
                                    float gamma)
{
    isFiltering = filtering;
    gabor.VO_PrepareGaborKernel(nstds,
                                lambda,
                                theta,
                                psi,
                                sigma,
                                gamma);
    rect.x = x;
    rect.y = y;
    rect.width = gabor.GetWindowFunc()->GetWindowSize().width;
    rect.height = gabor.GetWindowFunc()->GetWindowSize().width;
}


void VO_GaborFeatures::Feature::write(cv::FileStorage &fs) const
{
    fs << CC_RECT << "[:" << rect.x << rect.y << rect.width << rect.height << "]";
}
