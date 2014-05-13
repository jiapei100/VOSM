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

#include "VO_Algs_Evaluation.h"
#include "VO_CVCommon.h"

/**
 * @brief	to judge whether point "pt" is within rectangle "rect"
 * @param	pt		- input		the concerned point
 * @param	rect	- input		the concerned rectangle
 */
bool CEvaluationAlgs::IsPointInRect(const cv::Point2d& pt,
                                    const cv::Rect& rect)
{
	if(pt.x >= rect.x && pt.x < rect.x+rect.width &&
		pt.y >= rect.y && pt.y < rect.y+rect.height)
		return true;
	else
		return false;
}

/**
 * @param	detectedObjRect	- input		rectangle used to include detected object
 * @param	loadedObjRect	- input		rectangle used to include loaded annotated object (realistic object)
 * @param 	oar				- output	overlapped area ratio, overlapped area / entire area covered by two rectangles
 * @param	co				- output	center offset, the distance between two centers of detected object and loaded object
 */
void CEvaluationAlgs::StandardDetectionEvaluation(const cv::Rect& detectedObjRect,
                                                  const cv::Rect& loadedObjRect,
                                                  double& oar,
                                                  double& co)
{
	unsigned int LeftMost, TopMost, RightMost, BottomMost;
	LeftMost = (detectedObjRect.x < loadedObjRect.x) ? detectedObjRect.x : loadedObjRect.x;
	TopMost = (detectedObjRect.y < loadedObjRect.y) ? detectedObjRect.y : loadedObjRect.y;
	RightMost = (detectedObjRect.x + detectedObjRect.width > loadedObjRect.x + loadedObjRect.width) 
				? detectedObjRect.x + detectedObjRect.width : loadedObjRect.x + loadedObjRect.width;
	BottomMost = (detectedObjRect.y + detectedObjRect.height > loadedObjRect.y + loadedObjRect.height) 
				? detectedObjRect.y + detectedObjRect.height : loadedObjRect.y + loadedObjRect.height;

	unsigned int overlappedarea = 0;
	unsigned int entirearea = 0;
    cv::Point2d pt;
	bool isInFirst, isInSecond;
	for(unsigned int i = LeftMost; i < RightMost; ++i)
	{
		for(unsigned int j = TopMost; j < BottomMost; ++j)
		{
			pt.x = i;
			pt.y = j;
			if(CEvaluationAlgs::IsPointInRect(pt, detectedObjRect) )		isInFirst = true;
			else										isInFirst =  false;
			if(CEvaluationAlgs::IsPointInRect(pt, loadedObjRect) )		isInSecond = true;
			else										isInSecond = false;
			if(isInFirst || isInSecond)					entirearea++;
			if(isInFirst && isInSecond)					overlappedarea++;
		}
	}
	oar = (double)overlappedarea / (double)entirearea;
//	double detectedObjArea = detectedObjRect.width * detectedObjRect.height;
//	double loadedObjArea = loadedObjRect.width * loadedObjRect.height;
//	double overlappedArea = 0.0;
//	
//	// no overlap
//	if ( (detectedObjRect.x + detectedObjRect.width < loadedObjRect.x) ||
//		(detectedObjRect.y + detectedObjRect.height < loadedObjRect.y) || 
//		(loadedObjRect.x + loadedObjRect.width < detectedObjRect.x) ||
//		(loadedObjRect.y + loadedObjRect.height < detectedObjRect.y) )
//	{
//		oar = 0.0;
//	}
//	// detected within loaded
//	else if ( (detectedObjRect.x >= loadedObjRect.x) &&
//		(detectedObjRect.y >= loadedObjRect.y) && 
//		(detectedObjRect.x + detectedObjRect.width <= loadedObjRect.x + loadedObjRect.width) &&
//		(detectedObjRect.y + detectedObjRect.height <= loadedObjRect.y + loadedObjRect.height) )
//	{
//		overlappedArea = detectedObjArea;
//		oar = overlappedArea / loadedObjArea;
//	}
//	// loaded within detected
//	else if ( (loadedObjRect.x >= detectedObjRect.x) &&
//		(loadedObjRect.y >= detectedObjRect.y) && 
//		(loadedObjRect.x + loadedObjRect.width <= detectedObjRect.x + detectedObjRect.width) &&
//		(loadedObjRect.y + loadedObjRect.height <= detectedObjRect.y + detectedObjRect.height) )
//	{
//		overlappedArea = loadedObjArea;
//		oar = overlappedArea / detectedObjArea;
//	}
//	// partly 1
//	else
//	{
//		
//	}
//	
//	oar = overlappedArea / detectedObjArea;
	
	double xCenter_detected = (double)detectedObjRect.x + (double)detectedObjRect.width/2.0;
	double yCenter_detected = (double)detectedObjRect.y + (double)detectedObjRect.height/2.0;
	double xCenter_loaded 	= (double)loadedObjRect.x + (double)loadedObjRect.width/2.0;
	double yCenter_loaded 	= (double)loadedObjRect.y + (double)loadedObjRect.height/2.0;
	co  = sqrt ( pow( (xCenter_detected-xCenter_loaded), 2.0) + pow( (yCenter_detected-yCenter_loaded), 2.0) );
}


/**
 * @param	face			- input			detected face rectangle
 * @param	leftEyeCenter	- output		center of the left eye
 * @param	rightEyeCenter	- output		center of the right eye
 */
void CEvaluationAlgs::EstimateEyeCenters(const cv::Rect& face,
                                        cv::Point2d& leftEyeCenter,
                                        cv::Point2d& rightEyeCenter)
{
	leftEyeCenter.x 	= (double)face.width/20.0 + 9.0*(double)face.width/20.0*0.5+face.x;
	leftEyeCenter.y 	= (double)face.height/10.0 + (double)face.height/3.0*0.5+face.y;
	rightEyeCenter.x 	= (double)face.width/2.0 + 9.0*(double)face.width/20.0*0.5+face.x;
	rightEyeCenter.y 	= (double)face.height/10.0 + (double)face.height/3.0*0.5+face.y;
}


/**
 * @brief	Evaluation for all image files from an image sequence.
 * @param	detectedFaces		- input		a vector of detected faces
 * @param	leftEyeCenters		- input		a vector of detected left eye centers
 * @param	rightEyeCenters		- input		a vector of detected right eye centers
 * @return	a vector of dEyes	-- refer to Cristinacce paper
 */
std::vector<double> CEvaluationAlgs::CristinacceDEyes(  const std::vector<cv::Rect>& detectedFaces,
                                                        const std::vector<cv::Point2d>& leftEyeCenters,
                                                        const std::vector<cv::Point2d>& rightEyeCenters )
{
	assert(detectedFaces.size() == leftEyeCenters.size() );
	assert(detectedFaces.size() == rightEyeCenters.size() );

    cv::Point2d predictedLeftEyeCenter, predictedRightEyeCenter;
	unsigned int NbOfSamples = detectedFaces.size();
    std::vector<double> dEyes(NbOfSamples, 0.0);
	double dLeft, dRight, dLeftRight;
	for (unsigned int i = 0; i < NbOfSamples; i++)
	{
		// if undetected
		if(detectedFaces[i].x < 0 && detectedFaces[i].y < 0 &&
			detectedFaces[i].width < 0 && detectedFaces[i].height < 0)
		{
			dEyes[i] = DBL_MAX;
		}
		else
		{
            CEvaluationAlgs::EstimateEyeCenters(detectedFaces[i], predictedLeftEyeCenter, predictedRightEyeCenter);
			dLeft = sqrt ( pow( (predictedLeftEyeCenter.x - leftEyeCenters[i].x), 2.0)
				+ pow( (predictedLeftEyeCenter.y - leftEyeCenters[i].y), 2.0) );
			dRight = sqrt ( pow( (predictedRightEyeCenter.x - rightEyeCenters[i].x), 2.0)
				+ pow( (predictedRightEyeCenter.y - rightEyeCenters[i].y), 2.0) );
			dLeftRight = sqrt ( pow( (leftEyeCenters[i].x - rightEyeCenters[i].x), 2.0)
				+ pow( (leftEyeCenters[i].y - rightEyeCenters[i].y), 2.0) );
			dEyes[i] = (dLeft+dRight)/(2*dLeftRight);
		}
	}

	return dEyes;
}


/**
 * @param	dEyess		- input		a vector of dEyes, refer to Cristinacce paper
 * @param	wrongDet	- output	how many wrong detections
 * @param	mindEyes	- input		min dEyes
 * @param	maxdEyes	- input		max dEyes
 * @param	nb			- input		how many evaluation levels that is to be used
 */
std::vector<int> CEvaluationAlgs::DEyesEval(const std::vector<double>& dEyess,
                                            unsigned int& wrongDet,
                                            double mindEyes,
                                            double maxdEyes,
                                            unsigned int nb )
{
    std::vector<int> res(nb, 0);
	double interval = (maxdEyes-mindEyes)/(double)nb;
	double curdEye = 0.0;
	
	for(unsigned int i = 0; i < nb; i++)
	{
		curdEye = mindEyes + i*interval;
		for (unsigned int j = 0; j < dEyess.size(); j++)
		{
			if (dEyess[j] < curdEye)
			{
				res[i]++;
			}
		}
	}

	wrongDet = 0;
	for (unsigned int j = 0; j < dEyess.size(); j++)
	{
		if (dEyess[j] > maxdEyes)
		{
			wrongDet++;
		}
	}

	return res;
}


/**
 * @param	detectedFaceComp	- input		detected face components
 * @param	faceCompCenters		- input		loaded face compoenents' centers (realistic face information)
 * @return	a vector of MSEs
 */
std::vector<double>	CEvaluationAlgs::MSEFaceComp(const std::vector<cv::Rect>& detectedFaceComp,
                                                const std::vector<cv::Point2d>& faceCompCenters )
{
	assert(detectedFaceComp.size() == faceCompCenters.size() );
	unsigned int size = detectedFaceComp.size();
	double xCenter, yCenter;
    std::vector<double> mse(size, 0.0);

	for(unsigned int i = 0; i < size; i++)
	{
		xCenter = detectedFaceComp[i].x + (double)detectedFaceComp[i].width/2.0;
		yCenter = detectedFaceComp[i].y + (double)detectedFaceComp[i].height/2.0;
		mse[i]  = sqrt ( pow( (xCenter-faceCompCenters[i].x), 2.0) + pow( (yCenter-faceCompCenters[i].y), 2.0) );
	}

	return mse;
}

