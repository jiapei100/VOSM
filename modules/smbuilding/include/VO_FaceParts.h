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


#ifndef __VO_FACEPARTS_H__
#define __VO_FACEPARTS_H__

#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "VO_FacePart.h"



/** 
 * @author		JIA Pei
 * @brief		Face Parts, pay attention to file "ShapeInfo.txt"
 */
class VO_FaceParts
{
friend std::ostream& operator<<(std::ostream& os, const VO_FaceParts& faceparts);
friend std::istream& operator>>(std::istream& is, VO_FaceParts& faceparts);
private:
    /** Chin indexes */
    VO_FacePart								m_vChin;

    /** LeftEyebrow indexes */
    VO_FacePart								m_vLeftEyebrow;

    /** RightEyebrow indexes */
    VO_FacePart								m_vRightEyebrow;

    /** LeftEye indexes */
    VO_FacePart								m_vLeftEye;

    /** RightEye indexes */
    VO_FacePart								m_vRightEye;

    /** Nose indexes */
    VO_FacePart								m_vNose;

    /** Nostril indexes */
    VO_FacePart								m_vNostril;

    /** Nose Tip indexes */
    VO_FacePart								m_vNoseTip;

    /** Lip outerline indexes */
    VO_FacePart								m_vLipOuterLine;

    /** Lip innerline indexes */
    VO_FacePart								m_vLipInnerLine;

    /** Lip upper outer bound indexes */
    VO_FacePart								m_vLipUpperOuterLine;

    /** Lip upper inner bound indexes */
    VO_FacePart								m_vLipUpperInnerLine;

    /** Lip downer outer bound indexes */
    VO_FacePart								m_vLipLowerOuterLine;

    /** Lip downer inner bound indexes */
    VO_FacePart								m_vLipLowerInnerLine;

    /** Left Side cv::Points indexes */
    VO_FacePart								m_vLeftSidePoints;

    /** Right Side cv::Points indexes */
    VO_FacePart								m_vRightSidePoints;

    /** Midline cv::Points indexes */
    VO_FacePart								m_vMidlinePoints;

    /** Eyes' Corners' cv::Points indexes */
    VO_FacePart								m_vEyeCornerPoints;

    /** Mouth Corners' cv::Points indexes */
    VO_FacePart								m_vMouthCornerPoints;

    /** Pitch Axis cv::Points indexes */
    VO_FacePart								m_vPitchAxisLinePoints;

    /** Left Iris indexes */
    VO_FacePart								m_vLeftIris;

    /** Right Iris indexes */
    VO_FacePart								m_vRightIris;

    /** Left Ear indexes */
    VO_FacePart								m_vLeftEar;

    /** Right Ear indexes */
    VO_FacePart								m_vRightEar;
	
	/** Triangles' indexes. NbOfTriangles*3*/
    std::vector< std::vector < unsigned int > > 	m_vvTriangleIndexes;


    /** Initialization */
    void									init()
    {
											this->m_vChin.clear();
											this->m_vLeftEyebrow.clear();
											this->m_vRightEyebrow.clear();
											this->m_vLeftEye.clear();
											this->m_vRightEye.clear();
											this->m_vNose.clear();
											this->m_vNostril.clear();
											this->m_vNoseTip.clear();
											this->m_vLipOuterLine.clear();
											this->m_vLipInnerLine.clear();
											this->m_vLipUpperOuterLine.clear();
											this->m_vLipUpperInnerLine.clear();
											this->m_vLipLowerOuterLine.clear();
											this->m_vLipLowerInnerLine.clear();
                                            this->m_vLeftSidePoints.clear();
                                            this->m_vRightSidePoints.clear();
                                            this->m_vMidlinePoints.clear();
                                            this->m_vEyeCornerPoints.clear();
                                            this->m_vMouthCornerPoints.clear();
                                            this->m_vPitchAxisLinePoints.clear();
											this->m_vLeftIris.clear();
											this->m_vRightIris.clear();
											this->m_vLeftEar.clear();
											this->m_vRightEar.clear();
											this->m_vvTriangleIndexes.clear();
    }

    /** copy all face parts */
    void									CopyData(const VO_FaceParts &iFaceParts)
    {
											this->m_vChin 					= iFaceParts.VO_GetOneFacePart(VO_FacePart::CHIN);
											this->m_vLeftEyebrow 			= iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTEYEBROW);
											this->m_vRightEyebrow			= iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTEYEBROW);
											this->m_vLeftEye 				= iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTEYE);
											this->m_vRightEye 				= iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTEYE);
											this->m_vNose 					= iFaceParts.VO_GetOneFacePart(VO_FacePart::NOSE);
											this->m_vNostril 				= iFaceParts.VO_GetOneFacePart(VO_FacePart::NOSTRIL);
											this->m_vNoseTip				= iFaceParts.VO_GetOneFacePart(VO_FacePart::NOSETIP);
											this->m_vLipOuterLine 			= iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPOUTERLINE);
											this->m_vLipInnerLine 			= iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPINNERLINE);
											this->m_vLipUpperOuterLine		= iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPUPPEROUTERLINE);
											this->m_vLipUpperInnerLine		= iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPUPPERINNERLINE);
											this->m_vLipLowerOuterLine		= iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPDOWNEROUTERLINE);
											this->m_vLipLowerInnerLine		= iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPDOWNERINNERLINE);
                                            this->m_vLeftSidePoints 		= iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTSIDEPOINTS);
                                            this->m_vRightSidePoints 		= iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTSIDEPOINTS);
                                            this->m_vMidlinePoints 			= iFaceParts.VO_GetOneFacePart(VO_FacePart::MIDLINEPOINTS);
                                            this->m_vEyeCornerPoints 		= iFaceParts.VO_GetOneFacePart(VO_FacePart::EYECORNERPOINTS);
                                            this->m_vMouthCornerPoints		= iFaceParts.VO_GetOneFacePart(VO_FacePart::MOUTHCORNERPOINTS);
                                            this->m_vPitchAxisLinePoints    = iFaceParts.VO_GetOneFacePart(VO_FacePart::PITCHAXISLINEPOINTS);
											this->m_vLeftIris 				= iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTIRIS);
											this->m_vRightIris 				= iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTIRIS);
											this->m_vLeftEar 				= iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTEAR);
											this->m_vRightEar 				= iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTEAR);
											this->m_vvTriangleIndexes		= iFaceParts.GetTriangleIndexes();
    }

public:
    /** Default constructor to create a VO_FaceParts object */
    VO_FaceParts() 							{ this->init(); }

    /** Copy constructor */
    VO_FaceParts( const VO_FaceParts &iFaceParts )	{ this->CopyData(iFaceParts); }

    /** Destructor */
    virtual ~VO_FaceParts() 				{ this->clear(); }

    /** operator= overloading, similar to copy constructor */
    VO_FaceParts&  operator=(const VO_FaceParts &iFaceParts)
    {
											this->CopyData(iFaceParts);
											return *this;
    }

    /** clear */
    void clear() 							{ this->init(); }

    /** Gets and Sets */
    VO_FacePart                                 VO_GetOneFacePart( unsigned int partIdx) const;
    void                                        VO_SetOneFacePart(const VO_FacePart& iFacePart);
    std::vector< std::vector < unsigned int > > GetTriangleIndexes() const {return this->m_vvTriangleIndexes;}
    void                                        SetTriangleIndexes(const std::vector< std::vector < unsigned int > >& iTriangleIndexes) { this->m_vvTriangleIndexes = iTriangleIndexes ;}
};

#endif      // __VO_FACEPARTS_H__

