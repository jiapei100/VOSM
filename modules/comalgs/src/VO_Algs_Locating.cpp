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

#include "VO_Algs_Locating.h"



/** Initialization */
void CLocatingAlgs::init(const std::string& str, unsigned int detectionMtd, unsigned int trackingMtd)
{
	this->m_detectionAlgs.SetConfiguration(str, detectionMtd);
	this->m_trackingAlgs.SetConfiguration(trackingMtd);
	this->m_bObjectLocalized 	= false;
}
	
	
/** CLocatingAlgs constructor */
CLocatingAlgs::CLocatingAlgs(const std::string& str, unsigned int detectionMtd, unsigned int trackingMtd)
{
	init(str, detectionMtd, trackingMtd);
}

/** CLocatingAlgs destructor */
CLocatingAlgs::~CLocatingAlgs()
{

}

/** 
 * @author     	JIA Pei
 * @version    	2009-10-04
 * @brief      	Object Locating
 * @param      	img     		Input - image to be searched within
 * @param		objPos			Output - localized objects' positions
 * @return		localization time cost
*/
double CLocatingAlgs::Locating(	const cv::Mat& img,
                                cv::Size smallSize,
                                cv::Size bigSize)
{
    return ( CLocatingAlgs::Locating(   img,
                                        this->m_detectionAlgs,
                                        this->m_trackingAlgs,
                                        this->m_bObjectLocalized,
                                        this->m_CVLocalizedObjectRect,
                                        smallSize,
                                        bigSize) );
}


/** 
 * @author     	JIA Pei
 * @version    	2009-10-04
 * @brief      	Object Detection
 * @param      	img     		Input - image to be searched within
 * @param      	detectAlg		Input - detection algorithm
 * @param		trackAlg		Input - tracking algorithm
 * @param      	detectionMtd	Input - detection method
 * @param		trackingMtd		Input - tracking method
 * @param		isTracked		Output - is the object tracked?
 * @param		objPos			Output - objects' positions
 * @param		smallSize		Input - detected object should be bigger than smallsize
 * @param		bigSize			Input - detected object should be smaller than bigSize
 * @return		localization time cost
*/
double CLocatingAlgs::Locating(	const cv::Mat& img,
                                CDetectionAlgs& detectAlg,
                                CTrackingAlgs& trackAlg,
                                bool& isLocalized,
                                cv::Rect& objPos,
                                const cv::Size& smallSize,
                                const cv::Size& bigSize)
{
	double res = (double)cvGetTickCount();
	double scale = 1.0;

	// only detection is used
    if ( trackAlg.GetTrackingMethod() == CTrackingAlgs::NONE )
	{
		detectAlg.Detection(img,
							NULL,
							scale,
							smallSize,
							bigSize);
		if( detectAlg.IsObjectDetected() )
		{
			isLocalized = true;
			objPos = detectAlg.GetDetectedObjectRects()[0];
		}
	}
	// tracking is used
	else
	{
		// not localized yet
		if( !isLocalized || (objPos.x < 0 && objPos.y < 0 && objPos.width < 0 && objPos.height < 0) )
		{
			detectAlg.Detection(img,
								NULL,
								scale,
								smallSize,
								bigSize);
			if( detectAlg.IsObjectDetected() )
			{
				isLocalized = true;
				objPos = detectAlg.GetDetectedObjectRects()[0];
				trackAlg.UpdateTracker(img, objPos);
			}
		}
		// keep tracking now
		else
		{
			trackAlg.Tracking( 	img,
								objPos,
								smallSize,
								bigSize);
			isLocalized = trackAlg.IsObjectTracked();
		}
	}

	res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
	return res;
}


/**
 * @brief Draw a rectangle which locates the conerned object
 * @param ioImg
 * @param color
 */
void CLocatingAlgs::VO_DrawLocating(cv::Mat& ioImg, cv::Scalar color)
{
    cv::Rect curRect;
    cv::Point lefttop, rightbottom;

    if ( this->m_bObjectLocalized )
    {
		curRect = this->m_CVLocalizedObjectRect;
		lefttop.x = cvRound(curRect.x);
		lefttop.y = cvRound(curRect.y);
		rightbottom.x = cvRound((curRect.x+curRect.width));
		rightbottom.y = cvRound((curRect.y+curRect.height));
		cv::rectangle(ioImg, lefttop, rightbottom,	color, 2, 8, 0);
    }
}

