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

#include <string>
#include <sstream>
#include <fstream>

#include "boost/filesystem.hpp"

#include "VO_FittingAAMForwardIA.h"


/** Constructor */
VO_FittingAAMForwardIA::VO_FittingAAMForwardIA()
{
    this->init();
}

/** Destructor */
VO_FittingAAMForwardIA::~VO_FittingAAMForwardIA()
{
    if(this->m_VOAAMForwardIA)      delete this->m_VOAAMForwardIA; this->m_VOAAMForwardIA = NULL;
}


/** Initialization */
void VO_FittingAAMForwardIA::init()
{
    VO_Fitting2DSM::init();
    this->m_VOAAMForwardIA          = new VO_AAMForwardIA();

    std::string fn = "/home/jiapei/Desktop/forwardiaaamtime.txt";
}


/**
 * @author     JIA Pei
 * @version    2010-05-18
 * @brief      Load all AAM data from a specified folder for later fitting, to member variable m_VOAAMForwardIA
 * @param      fd         Input - the folder that AAM to be loaded from
*/
void VO_FittingAAMForwardIA::VO_LoadParameters4Fitting(const std::string& fd)
{
    this->m_VOAAMForwardIA->VO_LoadParameters4Fitting(fd);
    
    // VO_Fitting2DSM
    this->m_VOTemplateAlignedShape          = this->m_VOAAMForwardIA->m_VOAlignedMeanShape;
    this->m_VOTemplateNormalizedTexture     = this->m_VOAAMForwardIA->m_VONormalizedMeanTexture;
    this->m_vTriangle2D                     = this->m_VOAAMForwardIA->m_vNormalizedTriangle2D;
    this->m_vShape2DInfo                    = this->m_VOAAMForwardIA->m_vShape2DInfo;
    this->m_FaceParts                       = this->m_VOAAMForwardIA->m_FaceParts;
    this->m_vPointWarpInfo                  = this->m_VOAAMForwardIA->m_vNormalizedPointWarpInfo;

    // VO_FittingAAMForwardIA
}


/**
 * @brief FAIA AAM Fitting, for static image sequences
 * @param iImg
 * @param oImages
 * @param epoch
 * @param record
 * @return
 */
float VO_FittingAAMForwardIA::VO_FAIAAAMFitting(const cv::Mat& iImg,
                                                std::vector<cv::Mat>& oImages,
                                                unsigned int epoch,
                                                bool record)
{
double t = (double)cvGetTickCount();

t = ((double)cvGetTickCount() -  t )/  (cvGetTickFrequency()*1000.);
std::cout << "FAIA time cost: " << t << " millisec" << std::endl;

    return t;
}


/**
 * @brief VO_FAIA AAM Fitting, for dyanmic video
 * @param iImg
 * @param ioShape
 * @param oImg
 * @param epoch
 * @return
 */
float VO_FittingAAMForwardIA::VO_FAIAAAMFitting(const cv::Mat& iImg,
                                                VO_Shape& ioShape,
                                                cv::Mat& oImg,
                                                unsigned int epoch)
{
double t = (double)cvGetTickCount();

t = ((double)cvGetTickCount() -  t )/  (cvGetTickFrequency()*1000.);
std::cout << "FAIA fitting time cost: " << t << " millisec" << std::endl;
this->m_fFittingTime = t;

    return t;
}

