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

#include <iostream>
#include <cstdio>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "VO_Algs_Detection.h"


/** 
 * @author     	JIA Pei
 * @version    	2010-02-01
 * @brief       Initialization
 * @param		str			Input - the trained .xml file name
 * @param		mtd			Input - detection method, here, for additive model, boosting or bagging
 * @return		void
*/
void CDetectionAlgs::init(const std::string& str, unsigned int mtd)
{
	this->SetConfiguration(str, mtd);
	this->m_vDetectedObjectRects.clear();
	this->m_bObjectDetected = false;
}


/** CDetectionAlgs constructor */
CDetectionAlgs::CDetectionAlgs(const std::string& str, unsigned int mtd)
{
	this->init(str, mtd);
}


/** CDetectionAlgs destructor */
CDetectionAlgs::~CDetectionAlgs()
{
	
}


/** 
 * @author     	JIA Pei
 * @version    	2009-10-04
 * @brief      	Object Detection
 * @param      	iImg     		Input - image to be searched within
 * @param		confinedArea	Input - only detecting the object within this confined area
 * @param		objs			Output - detected objects
 * @param      	scale			Input - scalar for img scaling
 * @param		smallSize		Input - detected object should be bigger than smallsize
 * @param		bigSize			Input - detected object should be smaller than bigSize
 * @return		detection time cost
*/
double CDetectionAlgs::Detection(const cv::Mat& iImg,
                                    const cv::Rect* confinedArea,
									const double scale,
                                    cv::Size smallSize,
                                    cv::Size bigSize)
{
	double res = (double)cvGetTickCount();
	
	switch(this->m_iDetectionMethod)
	{
		case VO_AdditiveStrongerClassifier::BAGGING:
			CDetectionAlgs::BaggingDetection( this->m_rtreeClassifier,
											iImg,
											confinedArea,
											this->m_vDetectedObjectRects,
											scale,
											smallSize,
											bigSize);
		break;
		case VO_AdditiveStrongerClassifier::BOOSTING:
			CDetectionAlgs::BoostingDetection( this->m_cascadeClassifier,
											iImg,
											confinedArea,
											this->m_vDetectedObjectRects,
											scale,
											smallSize,
											bigSize);
		break;
	}
	
	if(this->m_vDetectedObjectRects.size() >= 1)
		this->m_bObjectDetected	= true;
	else
		this->m_bObjectDetected	= false;

	res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
	return res;
}


/**
 * @author		JIA Pei
 * @version		2009-10-04
 * @brief      	Boosting based Object Detection
 * @param	 	cascade			Input - cascade classifier to be used
 * @param      	img     		Input - image to be searched within
 * @param		confinedArea	Input - only detecting the object within this confined area
 * @param		objs			Output - detected objects
 * @param      	scale			Input - scalar for img scaling
 * @param		smallSize		Input - detected object should be bigger than smallsize
 * @param		bigSize			Input - detected object should be smaller than bigSize
 * @return		detection time cost
*/
double CDetectionAlgs::BoostingDetection( const cv::CascadeClassifier& cascade,
                                        const cv::Mat& img,
                                        const cv::Rect* confinedArea,
                                        std::vector<cv::Rect>& objs,
										const double scale,
                                        cv::Size smallSize,
                                        cv::Size bigSize)
{
	double res = (double)cvGetTickCount();
	objs.clear();
    cv::Mat confinedImg;
	if(confinedArea)
		confinedImg = img(*confinedArea);
	else
		confinedImg = img;

    cv::Mat gray, smallImg( cvRound (confinedImg.rows/scale), cvRound(confinedImg.cols/scale), CV_8UC1 );

	if(confinedImg.channels() == 3)
        cv::cvtColor( confinedImg, gray, CV_BGR2GRAY );
	else
		gray = confinedImg;
    cv::resize( gray, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR );
    cv::equalizeHist( smallImg, smallImg );

	/////////////////detection/////////////////////////////////////////
	//t = (double)cvGetTickCount();
    const_cast<cv::CascadeClassifier&>(cascade).detectMultiScale( smallImg, objs,
															1.1, 2, 0
															//|CascadeClassifier::DO_CANNY_PRUNING
															//|CascadeClassifier::FIND_BIGGEST_OBJECT
															//|CascadeClassifier::DO_ROUGH_SEARCH
                                                            //|CascadeClassifier::SCALE_IMAGE,
                                                            |CV_HAAR_SCALE_IMAGE,
															smallSize);
															//Size(40, 40) );
	///////////////////////sort///////////////////////////////////////
	if (objs.size() > 0)
	{
        qsort( (void *)&(objs[0]), objs.size(), sizeof(cv::Size), cvSizeCompare );
		// re-position
		if (confinedArea)
		{
			for (int i = 0; i < objs.size(); ++i)
			{
				objs[i].x = objs[i].x*scale+confinedArea->x;
				objs[i].y = objs[i].y*scale+confinedArea->y;
			}
		}
		else
		{
			for (int i = 0; i < objs.size(); ++i)
			{
				objs[i].x = objs[i].x*scale;
				objs[i].y = objs[i].y*scale;
			}
		}
			
		/////////scale back and erase too small or too big objs////////////
		int qs = 0;						// qualified start
		int qe = objs.size();			//qualified end
		int i = 0;
		for ( i = 0; i < objs.size(); ++i)
		{
			objs[i].width *= scale;
			objs[i].height *= scale;
			if(objs[i].width > bigSize.width)
			{
				++qs;
				continue;
			}
			else if(objs[i].width < smallSize.width)
			{
				qe = i;
				break;
			}
		}
		// erase the last ones first -- smaller ones
		objs.erase (objs.begin() + qe, objs.end());
		// then, erase the first ones -- bigger ones
		objs.erase (objs.begin(), objs.begin() + qs);
	}

	res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
	return res;
}


/**
 * @author		JIA Pei
 * @version		2009-10-04
 * @brief      	Bagging based Object Detection
 * @param	 	rtree			Input - random tree classifier to be used
 * @param      	img     		Input - image to be searched within
 * @param		confinedArea	Input - only detecting the object within this confined area
 * @param		objs			Output - detected objects
 * @param      	scale			Input - scalar for img scaling
 * @param		smallSize		Input - detected object should be bigger than smallsize
 * @param		bigSize			Input - detected object should be smaller than bigSize
 * @return		detection time cost
*/
double CDetectionAlgs::BaggingDetection( const cv::RTreeClassifier& rtree,
                                        const cv::Mat& img,
                                        const cv::Rect* confinedArea,
                                        std::vector<cv::Rect>& objs,
										const double scale,
                                        cv::Size smallSize,
                                        cv::Size bigSize)
{
	double res = (double)cvGetTickCount();

	res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
	return res;
}


/**
 * @brief Draw detected rectangles on an image
 * @param ioImg -- input output image after being drawn on
 * @param color -- the color
 */
void CDetectionAlgs::VO_DrawDetection(cv::Mat& ioImg, cv::Scalar color)
{
	unsigned int NbOfDetectedObjs = this->m_vDetectedObjectRects.size();

    cv::Rect curRect;
    cv::Point lefttop, rightbottom;

    if ( NbOfDetectedObjs > 0 )
    {
		for(unsigned int i = 0; i < NbOfDetectedObjs; ++i)
		{
			curRect = this->m_vDetectedObjectRects[i];
			lefttop.x = cvRound(curRect.x);
			lefttop.y = cvRound(curRect.y);
			rightbottom.x = cvRound((curRect.x+curRect.width));
			rightbottom.y = cvRound((curRect.y+curRect.height));
			cv::rectangle(ioImg, lefttop, rightbottom,	color, 2, 8, 0);
		}
    }
}

