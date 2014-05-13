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
* Modify Date:      2014-04-17                                                                      *
****************************************************************************************************/

#ifndef __DETECTIONALGS_H__
#define __DETECTIONALGS_H__

#include <cstring>
#include "opencv/cv.h"
#include "opencv/cvaux.h"
#include "opencv/highgui.h"
#include "VO_CVCommon.h"
#include "VO_AdditiveStrongerClassifier.h"



/** 
 * @author		JIA Pei
 * @brief		Object detection algorithms.
 */
class CDetectionAlgs
{
friend class CLocalizationAlgs;
protected:
	/** Detected face rectangles */
    std::vector<cv::Rect>   	m_vDetectedObjectRects;

	/** Detection Method */
	unsigned int				m_iDetectionMethod;
	
	/** Either load a cascade file for boosting, or a boostrap file for rtree */
    std::string					m_sFile2BLoad;

	/** bagging random forest classifier */
    cv::RTreeClassifier			m_rtreeClassifier;
	
	/** boosting cascade classifier */
    cv::CascadeClassifier		m_cascadeClassifier;

	/** Whether .... is detected */
    bool                        m_bObjectDetected;

	/** Initializationi */
    void						init(const std::string& str, unsigned int mtd);

public:
	/** Constructor */
    CDetectionAlgs(const std::string& str="", unsigned int mtd=VO_AdditiveStrongerClassifier::BOOSTING);

	/** Destructor */
	~CDetectionAlgs();

    /** Set configuration for detection algorithm */
    void						SetConfiguration(const std::string& str, unsigned int mtd)
	{
								this->m_iDetectionMethod		= mtd;
								switch(this->m_iDetectionMethod)
								{
									case VO_AdditiveStrongerClassifier::BAGGING:
									{
										if(str!="")				this->SetBaggingRTree(str);
									}
									break;
									case VO_AdditiveStrongerClassifier::BOOSTING:
									{
										if(str!="")				this->SetBoostingCascade(str);
									}
									default:
									break;
								}
	}
    /** Set bagging */
    void						SetBaggingRTree(const std::string& str)
	{
								this->m_sFile2BLoad			= str;
								this->m_rtreeClassifier.read( this->m_sFile2BLoad.c_str() );
	}
    /** Set boosting */
    void						SetBoostingCascade(const std::string& str)
	{
								this->m_sFile2BLoad			= str;
								this->m_cascadeClassifier.load( this->m_sFile2BLoad );
	}

    /** Do Detection */
    double						Detection(	const cv::Mat& img,
                                            const cv::Rect* confinedArea,
											const double scale = 1.0,
                                            cv::Size smallSize = cv::Size(FACESMALLESTSIZE, FACESMALLESTSIZE),
                                            cv::Size bigSize = cv::Size(FACEBIGGESTSIZE, FACEBIGGESTSIZE) );

    /** Start Bagging Detection */
    static double				BaggingDetection( 	const cv::RTreeClassifier& rtree,
                                                    const cv::Mat& img,
                                                    const cv::Rect* confinedArea,
                                                    std::vector<cv::Rect>& objs,
													const double scale = 1.0,
                                                    cv::Size smallSize = cv::Size(FACESMALLESTSIZE, FACESMALLESTSIZE),
                                                    cv::Size bigSize = cv::Size(FACEBIGGESTSIZE, FACEBIGGESTSIZE));

    /** Start Boosting Detection */
    static double				BoostingDetection( 	const cv::CascadeClassifier& cascade,
                                                    const cv::Mat& img,
                                                    const cv::Rect* confinedArea,
                                                    std::vector<cv::Rect>& objs,
													const double scale = 1.0,
                                                    cv::Size smallSize = cv::Size(FACESMALLESTSIZE, FACESMALLESTSIZE),
                                                    cv::Size bigSize = cv::Size(FACEBIGGESTSIZE, FACEBIGGESTSIZE));

	/** Draw all detected objects on the image */
    void                        VO_DrawDetection(cv::Mat& ioImg, cv::Scalar color = colors[6]);

	/** Is object detected? */
	bool						IsObjectDetected() const {return this->m_bObjectDetected; }
	
	/** Return detected face parts rectangles */
    std::vector<cv::Rect> 		GetDetectedObjectRects() const { return this->m_vDetectedObjectRects; }
};

#endif	// __DETECTIONALGS_H__
