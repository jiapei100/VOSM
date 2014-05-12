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

#ifndef __VO_BOOSTINGSINGLEENSEMBLECLASSIFIER_H_
#define __VO_BOOSTINGSINGLEENSEMBLECLASSIFIER_H_


#include "opencv/ml.h"
#include "VO_WeakClassifier.h"


/** 
 * @author		JIA Pei
 * @brief		Boosting random forest classifier.
 * @note		FIXME
 */
class VO_BoostingSingleEnsembleClassifier : public CvBoost
{
protected:
	/** true positive requirement when training */
    float 								m_fMinTruePositive;

	/** false when training */
	float								m_fMaxWrongClassification;

public:
    /** Classifier type: discrete or real */
	enum {DISCRETE = 0, REAL = 1};
    /** Boosting optimization method: steepest descent, conjugate gradient, Newton Raphson */
	enum {STEEPESTDESCENT = 0, CONJUGATEGRADIENT = 1, NEWTONRAPHSON = 2};
	/** Margin1 -- e^{−yhf(x)}   Margin2 -- ln(1 + e^{−yhf(x))} */
	enum {MARGIN1 = 0, MARGIN2 =1};

	/** Constructor */
	explicit VO_BoostingSingleEnsembleClassifier(float minTurePositive = 0.95f, float maxWrongClassification = 0.5f)
	{
		this->m_fMinTruePositive 		= minTurePositive;
		this->m_fMaxWrongClassification = maxWrongClassification;
	}

	/** Destructor */
	virtual ~VO_BoostingSingleEnsembleClassifier() 	{}

	/** train */
//    virtual bool train( const CvFeatureEvaluator* _featureEvaluator,
//                        int _numSamples, int _precalcValBufSize, int _precalcIdxBufSize,
//                        const CvCascadeBoostParams& _params=CvCascadeBoostParams() );

	/** predict */
    virtual float predict( int sampleIdx, bool returnSum = false ) const;

    /** write features */
    void write( cv::FileStorage &fs, const cv::Mat& featureMap ) const;
//    bool read( const FileNode &node, const CvFeatureEvaluator* _featureEvaluator,
//               const CvCascadeBoostParams& _params );
    /** mark used features in map */
    void markUsedFeaturesInMap( cv::Mat& featureMap );
protected:
    /** set parameters */
    virtual bool set_params( const CvBoostParams& _params );
    /** update weights */
    virtual void update_weights( CvBoostTree* tree );
    /** Did we achieve the desired error? */
    virtual bool isErrDesired();
};

#endif	// __VO_BOOSTINGSINGLEENSEMBLECLASSIFIER_H_
