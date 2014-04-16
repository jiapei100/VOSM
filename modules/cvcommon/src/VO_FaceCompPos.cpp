/****************************************************************************
*                                                                           *
*   IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.       *
*                                                                           *
*   By downloading, copying, installing or using the software you agree to  *
*   this license. If you do not agree to this license, do not download,     *
*   install, copy or use the software.                                      *
*                                                                           *
*                           License Agreement                               *
*                   For Vision Open Statistical Models                      *
*                                                                           *
*   Copyright (C):      2006~2012 by JIA Pei, all rights reserved.          *
*                                                                           *
*   VOSM is free software under the terms of the GNU Lesser General Public  *
*   License (GNU LGPL) as published by the Free Software Foundation; either *
*   version 3.0 of the License, or (at your option) any later version.      *
*   You can use it, modify it, redistribute it, etc; and redistribution and *
*   use in source and binary forms, with or without modification, are       *
*   permitted provided that the following conditions are met:               *
*                                                                           *
*   a) Redistribution's of source code must retain this whole paragraph of  *
*   copyright notice, including this list of conditions and all the         *
*   following contents in this  copyright paragraph.                        *
*                                                                           *
*   b) Redistribution's in binary form must reproduce this whole paragraph  *
*   of copyright notice, including this list of conditions and all the      *
*   following contents in this copyright paragraph, and/or other materials  *
*   provided with the distribution.                                         *
*                                                                           *
*   c) The name of the copyright holders may not be used to endorse or      *
*   promote products derived from this software without specific prior      *
*   written permission.                                                     *
*                                                                           *
*   Any publications based on this code must cite the following five papers,*
*   technical reports and on-line materials.                                *
*   1) P. JIA, 2D Statistical Models, Technical Report of Vision Open       *
*   Working Group, 2st Edition, October 21, 2010.                           *
*   http://www.visionopen.com/members/jiapei/publications/pei_sm2dreport2010.pdf*
*   2) P. JIA. Audio-visual based HMI for an Intelligent Wheelchair.        *
*   PhD thesis, University of Essex, February, 2011.                        *
*   http://www.visionopen.com/members/jiapei/publications/pei_phdthesis2010.pdf*
*   3) T. Cootes and C. Taylor. Statistical models of appearance for        *
*   computer vision. Technical report, Imaging Science and Biomedical       *
*   Engineering, University of Manchester, March 8, 2004.                   *
*   http://www.isbe.man.ac.uk/~bim/Models/app_models.pdf                    *
*   4) I. Matthews and S. Baker. Active appearance models revisited.        *
*   International Journal of Computer Vision, 60(2):135--164, November 2004.*
*   http://www.ri.cmu.edu/pub_files/pub4/matthews_iain_2004_2/matthews_iain_2004_2.pdf*
*   5) M. B. Stegmann, Active Appearance Models: Theory, Extensions and     *
*   Cases, 2000.                                                            *
*   http://www2.imm.dtu.dk/~aam/main/                                       *
*                                                                           *
* Version:          0.4                                                     *
* Author:           JIA Pei                                                 *
* Contact:          jp4work@gmail.com                                       *
* URL:              http://www.visionopen.com                               *
* Create Date:      2010-02-11                                              *
* Revise Date:      2012-03-22                                              *
*****************************************************************************/


#include "VO_FaceCompPos.h"



VO_FaceCompPos::VO_FaceCompPos()
{
    this->m_sCorrespondingImageFile     = "";
    this->m_rectObject                  = Rect(0, 0, 0, 0);
    this->m_rectLeftEye                 = Rect(0, 0, 0, 0);
    this->m_rectRightEye                = Rect(0, 0, 0, 0);
    this->m_rectNose                    = Rect(0, 0, 0, 0);
    this->m_rectMouth                   = Rect(0, 0, 0, 0);
}


VO_FaceCompPos::VO_FaceCompPos(
    const string& fn, 
    const Rect* rectObj, 
    const Rect* rectLeftEye, 
    const Rect* rectRightEye, 
    const Rect* rectNose, 
    const Rect* rectMouth)
{
    this->m_sCorrespondingImageFile         = fn;
    this->m_rectObject                      = *rectObj;
    if(rectLeftEye) this->m_rectLeftEye     = *rectLeftEye;
    if(rectRightEye) this->m_rectRightEye   = *rectRightEye;
    if(rectNose) this->m_rectNose           = *rectNose;
    if(rectMouth) this->m_rectMouth         = *rectMouth;
}


VO_FaceCompPos::~VO_FaceCompPos()
{
    
}


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


vector<Point2f> VO_FaceCompPos::VO_CalcFaceComponentsCenters() const
{
    vector<Point2f> res;
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


void VO_FaceCompPos::VO_DrawRects(Mat& oImg, Scalar color)
{
    Point lefttop, rightbottom;
    
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

