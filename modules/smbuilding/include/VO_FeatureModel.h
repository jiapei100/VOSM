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


#ifndef __VO_FEATUREMODEL_H__
#define __VO_FEATUREMODEL_H__


#include <vector>

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "VO_AXM.h"



/** 
 * @author		JIA Pei
 * @brief		Statistical fature model
 */
class VO_FeatureModel : public VO_AXM
{
friend class VO_Fitting2DSM;
friend class VO_FittingAAMBasic;
friend class VO_FittingAAMForwardIA;
friend class VO_FittingAAMInverseIA;
friend class VO_FittingASMLTCs;
friend class VO_FittingASMNDProfiles;
protected:
	/** PCA transform for appearance, including eigenstd::vectors, eigenvalues, and mean */
    cv::PCA							m_PCAFeatures;

	/** Features matrix. m_iNbOfSamples*m_iNbOfTotalFeatures */
    cv::Mat_<float>                 m_MatFeatures;

	/** Number of features -- a) 2D shape, 2 features b) rgb textures, 3 features c) something more */
	unsigned int					m_iNbOfTotalFeatures;

	/** Most possible feature eigens before PCA. For IMM: min (90396, 240) = 240 */
    unsigned int                	m_iNbOfEigenFeatureAtMost;

	/** Number of feature model eigens. For IMM: 127 */
    unsigned int               	 	m_iNbOfFeatureEigens;

	/** Truncate Percentage for feature model PCA. Normally, 0.95 */
    float                       	m_fTruncatedPercent_Feature;

	/** All loaded features in a std::vector format. For IMM, 240*m_iNbOfTotalFeatures */
    std::vector< cv::Mat_<float> >  m_vFeatures;

    /** All normalized features in a std::vector format. For IMM, 240*m_iNbOfTotalFeatures */
    std::vector< cv::Mat_<float> >  m_vNormalizedFeatures;

    /** Initialization */
    void                            init();

public:
    /** Default constructor to create a VO_FeatureModel object */
    VO_FeatureModel();

    /** Destructor */
    virtual ~VO_FeatureModel();

	/** Load features for one face */
	static bool						VO_LoadFeatures4OneFace(const VO_Shape& iShape, 
                                                            const cv::Mat& img,
															const std::vector<VO_Triangle2DStructure>& templateTriangles,
                                                            const std::vector<VO_WarpingPoint>& warpInfo,
                                                            cv::Mat_<float>& oFeature,
															int trm);

	/** Load Training data for feature model */
	bool							VO_LoadFeatureTrainingData( const std::vector<std::string>& allLandmarkFiles4Training,
																const std::vector<std::string>& allImgFiles4Training,
																const std::string& shapeinfoFileName, 
																unsigned int database,
																unsigned int channels);

    /** Build Feature Model */
    void                            VO_BuildFeatureModel(	const std::vector<std::string>& allLandmarkFiles4Training,
															const std::vector<std::string>& allImgFiles4Training,
															const std::string& shapeinfoFileName, 
															unsigned int database,
															unsigned int channels = 3,
															int trm = VO_Features::DIRECT, 
															float TPShape = 0.95f, 
															float TPTexture = 0.95f, 
															bool useKnownTriangles = false);

    /** Save Feature Model, to a specified folder */
    void                            VO_Save(const std::string& fd);

    /** Load all parameters */
    void                            VO_Load(const std::string& fd);

    /** Load Parameters for fitting */
    void                            VO_LoadParameters4Fitting(const std::string& fd);
 };


#endif // __VO_FEATUREMODEL_H__

