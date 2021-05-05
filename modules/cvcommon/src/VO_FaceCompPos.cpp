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

#include "VO_FaceCompPos.h"



/** default constructor */
VO_FaceCompPos::VO_FaceCompPos()
{
    this->m_sCorrespondingImageFile     = "";
    this->m_rectObject                  = cv::Rect(0, 0, 0, 0);
    this->m_rectLeftEye                 = cv::Rect(0, 0, 0, 0);
    this->m_rectRightEye                = cv::Rect(0, 0, 0, 0);
    this->m_rectNose                    = cv::Rect(0, 0, 0, 0);
    this->m_rectMouth                   = cv::Rect(0, 0, 0, 0);
}


/** a constructor */
VO_FaceCompPos::VO_FaceCompPos(
    const std::string& fn, 
    const cv::Rect* rectObj, 
    const cv::Rect* rectLeftEye, 
    const cv::Rect* rectRightEye, 
    const cv::Rect* rectNose, 
    const cv::Rect* rectMouth)
{
    this->m_sCorrespondingImageFile         = fn;
    this->m_rectObject                      = *rectObj;
    if(rectLeftEye) this->m_rectLeftEye     = *rectLeftEye;
    if(rectRightEye) this->m_rectRightEye   = *rectRightEye;
    if(rectNose) this->m_rectNose           = *rectNose;
    if(rectMouth) this->m_rectMouth         = *rectMouth;
}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Scale a face component
 * @param       nWidth    Input - width
 * @param       nHeight   Input - height
 * @return      void
*/
void VO_FaceCompPos::Scale(double nWidth, double nHeight)
{
    this->m_rectObject.x            *= nWidth;
    this->m_rectObject.y            *= nHeight;
    this->m_rectObject.width        *= nWidth;
    this->m_rectObject.height       *= nHeight;
    
    this->m_rectLeftEye.x           *= nWidth;
    this->m_rectLeftEye.y           *= nHeight;
    this->m_rectLeftEye.width       *= nWidth;
    this->m_rectLeftEye.height      *= nHeight;
    
    this->m_rectRightEye.x          *= nWidth;
    this->m_rectRightEye.y          *= nHeight;
    this->m_rectRightEye.width      *= nWidth;
    this->m_rectRightEye.height     *= nHeight;
    
    this->m_rectMouth.x             *= nWidth;
    this->m_rectMouth.y             *= nHeight;
    this->m_rectMouth.width         *= nWidth;
    this->m_rectMouth.height        *= nHeight;
    
    this->m_rectNose.x              *= nWidth;
    this->m_rectNose.y              *= nHeight;
    this->m_rectNose.width          *= nWidth;
    this->m_rectNose.height         *= nHeight;
}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Calculate centers of face components
 * @param       None
 * @return      std::vector<cv::Point2f>    5 centers
*/
std::vector<cv::Point2f> VO_FaceCompPos::VO_CalcFaceComponentsCenters() const
{
    std::vector<cv::Point2f> res;
    res.resize(5);
    
    res[0].x = this->m_rectObject.x + this->m_rectObject.width/2.0f;
    res[0].y = this->m_rectObject.y + this->m_rectObject.height/2.0f;

    res[1].x = this->m_rectLeftEye.x + this->m_rectLeftEye.width/2.0f;
    res[1].y = this->m_rectLeftEye.y + this->m_rectLeftEye.height/2.0f;

    res[2].x = this->m_rectRightEye.x + this->m_rectRightEye.width/2.0f;
    res[2].y = this->m_rectRightEye.y + this->m_rectRightEye.height/2.0f;

    res[3].x = this->m_rectNose.x + this->m_rectNose.width/2.0f;
    res[3].y = this->m_rectNose.y + this->m_rectNose.height/2.0f;

    res[4].x = this->m_rectMouth.x + this->m_rectMouth.width/2.0f;
    res[4].y = this->m_rectMouth.y + this->m_rectMouth.height/2.0f;
    
    return res;
}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Draw rects in a particular color on an image with
 * @param       oImg        -- output image
 * @param       color       -- input color
 * @return      void
*/
void VO_FaceCompPos::VO_DrawRects(cv::Mat& oImg, cv::Scalar color)
{
    cv::Point lefttop, rightbottom;
    
    // for the face
    lefttop.x = cvRound(this->m_rectObject.x);
    lefttop.y = cvRound(this->m_rectObject.y);
    rightbottom.x = cvRound(this->m_rectObject.x+this->m_rectObject.width);
    rightbottom.y = cvRound(this->m_rectObject.y+this->m_rectObject.height);
    cv::rectangle(oImg, lefttop, rightbottom, color, 2, 8, 0);
    
    // for the left eye
    lefttop.x = cvRound(this->m_rectLeftEye.x);
    lefttop.y = cvRound(this->m_rectLeftEye.y);
    rightbottom.x = cvRound(this->m_rectLeftEye.x+this->m_rectLeftEye.width);
    rightbottom.y = cvRound(this->m_rectLeftEye.y+this->m_rectLeftEye.height);
    cv::rectangle(oImg, lefttop, rightbottom, color, 1, 8, 0);
    
    // for the right eye
    lefttop.x = cvRound(this->m_rectRightEye.x);
    lefttop.y = cvRound(this->m_rectRightEye.y);
    rightbottom.x = cvRound(this->m_rectRightEye.x+this->m_rectRightEye.width);
    rightbottom.y = cvRound(this->m_rectRightEye.y+this->m_rectRightEye.height);
    cv::rectangle(oImg, lefttop, rightbottom, color, 1, 8, 0);
    
    // for the nose
    lefttop.x = cvRound(this->m_rectNose.x);
    lefttop.y = cvRound(this->m_rectNose.y);
    rightbottom.x = cvRound(this->m_rectNose.x+this->m_rectNose.width);
    rightbottom.y = cvRound(this->m_rectNose.y+this->m_rectNose.height);
    cv::rectangle(oImg, lefttop, rightbottom, color, 1, 8, 0);
    
    // for the mouth
    lefttop.x = cvRound(this->m_rectMouth.x);
    lefttop.y = cvRound(this->m_rectMouth.y);
    rightbottom.x = cvRound(this->m_rectMouth.x+this->m_rectMouth.width);
    rightbottom.y = cvRound(this->m_rectMouth.y+this->m_rectMouth.height);
    cv::rectangle(oImg, lefttop, rightbottom, color, 1, 8, 0);
}

