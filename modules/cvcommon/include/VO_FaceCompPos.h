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

#ifndef  __VO_FACECOMPPOS_H__
#define  __VO_FACECOMPPOS_H__

#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "VO_CVCommon.h"


/** 
 * @author      JIA Pei
 * @brief       Define some face components' positions, 
 *              which are described as rectangles.
 */
class VO_FaceCompPos
{
friend class CDetectionDBIO;
friend class CFaceDetectionAlgs;
protected:
    /** Every VO_FaceCompPos is corresponding to one face image */
    std::string     m_sCorrespondingImageFile;

    /** The object's location, including face location */
    cv::Rect        m_rectObject;

    /** Left eye's location*/
    cv::Rect        m_rectLeftEye;

    /** Right eye's location*/
    cv::Rect        m_rectRightEye;
    
    /** Nose's location*/
    cv::Rect        m_rectNose;
    
    /** Mouth's location*/
    cv::Rect        m_rectMouth;

public:
    /** Default constructor */
    VO_FaceCompPos();

    /** Constructor */
    VO_FaceCompPos( const std::string& fn,
                    const cv::Rect* rectObj,
                    const cv::Rect* rectLeftEye = NULL,
                    const cv::Rect* rectRightEye = NULL,
                    const cv::Rect* rectNose = NULL,
                    const cv::Rect* rectMouth = NULL );

    /** Destructor */
    virtual ~VO_FaceCompPos() {}
    
    void            Scale(double nWidth, double nHeight);
    
    /** Calculate face components' centers */
    std::vector<cv::Point2f> VO_CalcFaceComponentsCenters() const;
    
    /** Draw all rectangles */
    void            VO_DrawRects(cv::Mat& oImg, cv::Scalar color = colors[8]);

    /** Gets and Sets */
    std::string     GetImageFileName() const {return this->m_sCorrespondingImageFile;}
    cv::Rect        GetObjectRect() const {return this->m_rectObject;}
    cv::Rect        GetLeftEyeRect() const {return this->m_rectLeftEye;}
    cv::Rect        GetRightEyeRect() const {return this->m_rectRightEye;}
    cv::Rect        GetMouthRect() const {return this->m_rectMouth;}
    cv::Rect        GetNoseRect() const {return this->m_rectNose;}

    void            SetImageFileName(const std::string& fn) {this->m_sCorrespondingImageFile = fn;}
    void            SetObjectRect(const cv::Rect& iRect) {this->m_rectObject = iRect;}
    void            SetLeftEyeRect(const cv::Rect& iRect) {this->m_rectLeftEye = iRect;}
    void            SetRightEyeRect(const cv::Rect& iRect) {this->m_rectRightEye = iRect;}
    void            SetMouthRect(const cv::Rect& iRect) {this->m_rectMouth = iRect;}
    void            SetNoseRect(const cv::Rect& iRect) {this->m_rectNose = iRect;}

};

#endif  // __VO_FACECOMPPOS_H__

