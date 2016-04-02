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

#ifndef __FACEDETECTIONALGS_H__
#define __FACEDETECTIONALGS_H__

#include <cstring>
#include "VO_CVCommon.h"
#include "VO_FaceCompPos.h"
#include "VO_Algs_Detection.h"




/** 
 * @author		JIA Pei
 * @brief		Face detection algorithms.
 */
class CFaceDetectionAlgs : public CDetectionAlgs
{
private:
	/** Original detected face rectangle */
    std::vector<cv::Rect> 		m_vDetectedFaceRects;

    /** Detected face type - 0 - no face detected; 1 - frontal; 2 - left; 3 - right */
    unsigned int                m_iFaceType;

    /** Whether .... is detected */
    bool                        m_bFaceDetected;
    bool                        m_bLeftEyeDetected;
    bool                        m_bRightEyeDetected;
    bool                        m_bNoseDetected;
    bool                        m_bMouthDetected;

	/** Possible windows for further face parts detection */
    cv::Rect					m_CVLeftEyePossibleWindow;
    cv::Rect					m_CVRightEyePossibleWindow;
    cv::Rect					m_CVNosePossibleWindow;
    cv::Rect					m_CVMouthPossibleWindow;
    cv::Rect					m_CVNoseCentralArea;

    /** Detected windows for respective face parts */
	VO_FaceCompPos				m_VOFaceComponents0;	// not translated back to the whole image yet
	VO_FaceCompPos				m_VOFaceComponents;
    cv::Rect					m_CVDetectedFaceWindow2SM;
    cv::Mat						m_CVDetectedFaceImagePatch2SM;

    /** Detected Key Points */
    cv::Point2f					m_CVDetectedCenterOfGravity;
    cv::Point2f                	m_CVDetectedLeftEyeLeftCorner;
    cv::Point2f                	m_CVDetectedLeftEyeRightCorner;
    cv::Point2f					m_CVDetectedLeftEyeCenter;
    cv::Point2f                	m_CVDetectedRightEyeLeftCorner;
    cv::Point2f                	m_CVDetectedRightEyeRightCorner;
    cv::Point2f					m_CVDetectedRightEyeCenter;
    cv::Point2f                	m_CVDetectedNoseTip;
    cv::Point2f					m_CVDetectedNostrilLeft;
    cv::Point2f					m_CVDetectedNostrilRight;
    cv::Point2f                	m_CVDetectedNoseCenter;
    cv::Point2f                	m_CVDetectedMouthLeftCorner;
    cv::Point2f                	m_CVDetectedMouthRightCorner;
    cv::Point2f                	m_CVDetectedMouthCenter;

    /** configuration file to be loaded */
    std::string					m_sFile2BLoadFrontalFace;
    std::string					m_sFile2BLoadProfileFace;
    std::string					m_sFile2BLoadEyes;
    std::string					m_sFile2BLoadLeftEye;
    std::string					m_sFile2BLoadRightEye;
    std::string					m_sFile2BLoadNose;
    std::string					m_sFile2BLoadMouth;
    std::string					m_sFile2BLoadMouthBeard;

    /** Loaded classifiers */
    cv::CascadeClassifier		m_cascadeClassifierFrontalFace;
    cv::CascadeClassifier		m_cascadeClassifierProfileFace;
    cv::CascadeClassifier		m_cascadeClassifierEyes;
    cv::CascadeClassifier    	m_cascadeClassifierLeftEye;
    cv::CascadeClassifier    	m_cascadeClassifierRightEye;
    cv::CascadeClassifier    	m_cascadeClassifierNose;
    cv::CascadeClassifier    	m_cascadeClassifierMouth;
    cv::CascadeClassifier    	m_cascadeClassifierMouthBeard;
    cv::ml::RTrees*			m_rtreeClassifierFrontalFace;
    cv::ml::RTrees*			m_rtreeClassifierProfileFace;
    cv::ml::RTrees*			m_rtreeClassifierEyes;
    cv::ml::RTrees*			m_rtreeClassifierLeftEye;
    cv::ml::RTrees*			m_rtreeClassifierRightEye;
    cv::ml::RTrees*			m_rtreeClassifierNose;
    cv::ml::RTrees*			m_rtreeClassifierMouth;
    cv::ml::RTrees*	    	m_rtreeClassifierMouthBeard;

	/** Initialization */
    void                        init(const std::string& str, unsigned int mtd);

public:
	/** frontal face, left profile face, right profile face, etc. */
	enum {FRONTAL = 0, LEFTPROFILE = 1, RIGHTPROFILE = 2, UPPROFILE = 3, DOWNPROFILE = 4, ALL = 9};

	/** face directions */
	enum {UNDETECTED = -1, DIR_DOWNFRONTAL = 0, DIR_DOWNLEFT = 1, DIR_DOWNRIGHT = 2,
							DIR_UPFRONTAL = 3, DIR_UPLEFT = 4, DIR_UPRIGHT = 5,
							DIR_FRONTAL = 6, DIR_LEFT = 7, DIR_RIGHT = 8};

	/** Constructor */
    CFaceDetectionAlgs(const std::string& str="", unsigned int mtd=VO_AdditiveStrongerClassifier::BOOSTING);

	/** Destructor */
	~CFaceDetectionAlgs();

	/** set detection configurations */
    void						SetConfiguration(	const std::string& strfrontalface="",
                                                    const std::string& strprofileface="",
                                                    const std::string& strlefteye="",
                                                    const std::string& strrighteye="",
                                                    const std::string& strnose="",
                                                    const std::string& strmouth="",
													unsigned int mtd = VO_AdditiveStrongerClassifier::BOOSTING,
													unsigned int facetype = FRONTAL);

	/** only two main methods are adopted here, random forest or boosting cascade. Every detected face will be recorded */
    double						FaceDetection(	const cv::Mat& img,
                                                const cv::Rect* confinedArea = NULL,
												const double scale = 1.0,
                                                cv::Size smallSize = cv::Size(FACESMALLESTSIZE, FACESMALLESTSIZE),
                                                cv::Size bigSize = cv::Size(FACEBIGGESTSIZE, FACEBIGGESTSIZE));

	/** only a single face will be recorded */
    double						FullFaceDetection ( const cv::Mat& iImg,
                                                    const cv::Rect* confinedArea = NULL,
													bool lefteye = true,
													bool righteye = true,
													bool nose = true,
													bool mouth = true,
													const double scale = 1.0,
                                                    cv::Size smallSize = cv::Size(FACESMALLESTSIZE, FACESMALLESTSIZE),
                                                    cv::Size bigSize = cv::Size(FACEBIGGESTSIZE, FACEBIGGESTSIZE) );

	/** detect face components */
    double						VO_FaceComponentsDetection(	const cv::Mat& iImg,
															int faceOrient = FRONTAL,
															bool lefteye = true,
															bool righteye = true,
															bool nose = true,
															bool mouth = true);

	/** Detect one specific face part */
    bool                 		VO_FacePartDetection( 	const cv::Mat& iImg,
                                                        const cv::Rect& iWindow,
                                                        cv::Rect& oWindow,
														unsigned int facepart);

	/** Estimate face directions just based */
	int							VO_DetectFaceDirection(int faceOrient = FRONTAL);
	static int					VO_DetectFaceDirection(const VO_FaceCompPos& facecomponents,
                                                        const cv::Rect& possiblenose,
                                                        const cv::Rect& nosecentralarea);

	/** Draw the detected face details */
    void                        VO_DrawDetection(	cv::Mat& ioImg,
													bool face = true,  
													bool lefteye = false, 
													bool righteye = false, 
													bool nose = false, 
													bool mouth = false,
                                                    cv::Scalar color = colors[0]);

	/** 0 - no face detected; 1 - frontal; 2 - left; 3 - right */
	unsigned int				GetFaceType() const {return this->m_iFaceType;}

	/** Calculate face key points by detected face components */
	void						CalcFaceKeyPoints();

	/** Return detected face key point */
    cv::Point2f					GetDetectedFaceKeyPoint(unsigned int ptType) const;

	/** Is face parts detected */
	bool						IsFaceDetected() const {return this->m_bFaceDetected; }
	bool						IsLeftEyeDetected() const {return this->m_bLeftEyeDetected; }
	bool						IsRightEyeDetected() const {return this->m_bRightEyeDetected; }
	bool						IsNoseDetected() const {return this->m_bNoseDetected; }
	bool						IsMouthDetected() const {return this->m_bMouthDetected; }

	/** Return detected face parts rectangles */
    std::vector<cv::Rect> 		GetDetectedFaceRects() const {return this->m_vDetectedFaceRects; }
	VO_FaceCompPos				GetFaceComponents() const { return this->m_VOFaceComponents; }
    cv::Rect					GetDetectedFaceWindow() const { return this->m_VOFaceComponents.m_rectObject; }
    cv::Rect					GetDetectedFaceWindow2SM() const { return this->m_CVDetectedFaceWindow2SM; }
    cv::Rect					GetDetectedLeftEyeWindow() const { return this->m_VOFaceComponents.m_rectLeftEye; }
    cv::Rect					GetDetectedRightEyeWindow() const { return this->m_VOFaceComponents.m_rectRightEye; }
    cv::Rect					GetDetectedNoseWindow() const { return this->m_VOFaceComponents.m_rectNose; }
    cv::Rect					GetDetectedMouthWindow() const { return this->m_VOFaceComponents.m_rectMouth; }

	/** Reasonably adjust detected face rectangle to AAM rectangle */
    static cv::Rect				VO_FaceRectFromDetection2SM(const cv::Size& imgSize, const cv::Rect& iFaceRect);

	/** Reasonably set respective window for various face parts */
    static cv::Rect				VO_SetDetectedFacePartsPossibleWindow(	int imgWidth,
																		int imgHeight,
																		unsigned int facepart,
																		unsigned int dir = FRONTAL);
};

#endif	// __FACEDETECTIONALGS_H__
