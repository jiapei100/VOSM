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
#include "VO_Algs_Classification.h"


/** 
 * @author     	JIA Pei
 * @version    	2010-02-01
 * @brief       Initialization
 * @param		mtd			Input - detection method, here, for additive model, boosting or bagging
 * @return		void
*/
void CClassificationAlgs::init(unsigned int mtd)
{
    this->m_CVDtree = NULL;
    this->m_CVBoost = NULL;
    this->m_CVRTrees = NULL;
    this->m_CVSVM = NULL;
	this->m_iClassificationMethod = mtd;
}


/** CClassificationAlgs constructor */
CClassificationAlgs::CClassificationAlgs(unsigned int mtd)
{
	this->init(mtd);
}


/** CClassificationAlgs destructor */
CClassificationAlgs::~CClassificationAlgs()
{
	
}


/** set configuration */
void CClassificationAlgs::SetConfiguration(const std::string& trainedclassifier, unsigned int mtd)
{
	this->m_iClassificationMethod	= mtd;
	this->Load(trainedclassifier);
}


/** 
 * @author     	JIA Pei
 * @version    	2009-10-04
 * @brief      	Training
 * @param      	data     		Input - input data
 * @param		categories		Input - column vector
 * @return		classification time cost
*/
void CClassificationAlgs::Training(const cv::Mat_<float>& data, const cv::Mat_<int>& categories)
{
	unsigned int NbOfSamples = data.rows;
    std::set<int> ClassSet;
	for(int i = 0; i < categories.rows; i++)
	{
		ClassSet.insert(categories(i, 0));
	}
	this->m_iNbOfCategories = ClassSet.size();
	
	switch(this->m_iClassificationMethod)
	{
		case CClassificationAlgs::DecisionTree:
            this->m_CVDtree->setMaxDepth(INT_MAX);
            this->m_CVDtree->setMinSampleCount(2);
            this->m_CVDtree->setRegressionAccuracy(0);
            this->m_CVDtree->setUseSurrogates(false);
            this->m_CVDtree->setMaxCategories(this->m_iNbOfCategories);
            this->m_CVDtree->setCVFolds(0);
            this->m_CVDtree->setUse1SERule(false);
            this->m_CVDtree->setTruncatePrunedTree(false);
            this->m_CVDtree->setPriors(cv::Mat());
            this->m_CVDtree->train( cv::ml::TrainData::create(  data,
                                    cv::ml::ROW_SAMPLE,
                                    categories) );
		break;
		case CClassificationAlgs::Boost:
            this->m_CVBoost->setBoostType(cv::ml::Boost::DISCRETE);
            this->m_CVBoost->setWeakCount(50);
            this->m_CVBoost->setWeightTrimRate(0.95);
            this->m_CVBoost->setMaxDepth(INT_MAX);
            this->m_CVBoost->setUseSurrogates(false);
            this->m_CVBoost->setPriors(cv::Mat());
            this->m_CVBoost->train( cv::ml::TrainData::create(  data,
                        cv::ml::ROW_SAMPLE,
                        categories));
		break;
		case CClassificationAlgs::RandomForest:
            this->m_CVRTrees->setMaxDepth(INT_MAX);
            this->m_CVRTrees->setMinSampleCount(2);
            this->m_CVRTrees->setRegressionAccuracy(0);
            this->m_CVRTrees->setUseSurrogates(false);
            this->m_CVRTrees->setMaxCategories(this->m_iNbOfCategories);
            this->m_CVRTrees->setPriors(cv::Mat());
            this->m_CVRTrees->setCalculateVarImportance(true);
            this->m_CVRTrees->setActiveVarCount(0);
            this->m_CVRTrees->setTermCriteria(  cv::TermCriteria(cv::TermCriteria::MAX_ITER,
                                                100,
                                                0));
            this->m_CVRTrees->train(cv::ml::TrainData::create(  data,
                                    cv::ml::ROW_SAMPLE,
                                    categories));
		break;
//		case CClassificationAlgs::ExtremeRandomForest:
//			this->m_CVERTrees->train(data,
//									CV_ROW_SAMPLE,
//									categories,
//                                    cv::Mat(),
//                                    cv::Mat(),
//                                    cv::Mat(),
//                                    cv::Mat(),
//									CvRTParams( INT_MAX, 2, 0, false, this->m_iNbOfCategories, 0, true, 0, 100, 0, CV_TERMCRIT_ITER ) );
//		break;
		case CClassificationAlgs::SVM:
            this->m_CVSVM->setType(cv::ml::SVM::C_SVC);
            this->m_CVSVM->setKernel(cv::ml::SVM::RBF);
            this->m_CVSVM->setDegree(0);
            this->m_CVSVM->setGamma(1);
            this->m_CVSVM->setCoef0(0);
            this->m_CVSVM->setC(1);
            this->m_CVSVM->setNu(0);
            this->m_CVSVM->setP(0);
            this->m_CVSVM->setClassWeights(cv::Mat());
            this->m_CVSVM->setTermCriteria( cv::TermCriteria(cv::TermCriteria::MAX_ITER,
                                            1000,
                                            1E-6));
            this->m_CVSVM->train(cv::ml::TrainData::create(  data,
                                    cv::ml::ROW_SAMPLE,
                                    categories));
		break;
	}
}


/** 
 * @author     	JIA Pei
 * @version    	2009-10-04
 * @brief      	classification
 * @param      	data     		Input - input data
 * @return		classification time cost
*/
int CClassificationAlgs::Classification(const cv::Mat_<float>& sample )
{
	int res = -1;
	switch(this->m_iClassificationMethod)
	{
		case CClassificationAlgs::DecisionTree:
		{
			res = (int) this->m_CVDtree->predict( sample );
		}
		break;
		case CClassificationAlgs::Boost:
		{
			res = (int) this->m_CVBoost->predict( sample );
		}
		break;
		case CClassificationAlgs::RandomForest:
		{
			res = (int) this->m_CVRTrees->predict( sample );
		}
		break;
//		case CClassificationAlgs::ExtremeRandomForest:
//		{
//			res = (int) this->m_CVERTrees->predict( sample );
//		}
//		break;
		case CClassificationAlgs::SVM:
		default:
		{
			res = (int) this->m_CVSVM->predict( sample );
		}
		break;
	}

	return res;
}


/** 
 * @author     	JIA Pei
 * @version    	2009-10-04
 * @brief      	Save Classifier
 * @param      	fn     			Input - file to save
 * @return		void
*/
void CClassificationAlgs::Save(const std::string& fn ) const
{
	switch(this->m_iClassificationMethod)
	{
		case CClassificationAlgs::DecisionTree:
		{
			this->m_CVDtree->save(fn.c_str());
		}
		break;
		case CClassificationAlgs::Boost:
		{
			this->m_CVBoost->save(fn.c_str());
		}
		break;
		case CClassificationAlgs::RandomForest:
		{
			this->m_CVRTrees->save(fn.c_str());
		}
		break;
//		case CClassificationAlgs::ExtremeRandomForest:
//		{
//			this->m_CVERTrees.save(fn.c_str());
//		}
//		break;
		case CClassificationAlgs::SVM:
		default:
		{
			this->m_CVSVM->save(fn.c_str());
		}
		break;
	}
}


/** 
 * @author     	JIA Pei
 * @version    	2009-10-04
 * @brief      	Load Classifier
 * @param      	fn     			Input - file to save
 * @return		void
 * @note		You have to specify m_iClassificationMethod first
*/
void CClassificationAlgs::Load(const std::string& fn)
{
	switch(this->m_iClassificationMethod)
	{
		case CClassificationAlgs::DecisionTree:
		{
			this->m_CVDtree = cv::ml::StatModel::load<cv::ml::DTrees>(fn.c_str());
		}
		break;
		case CClassificationAlgs::Boost:
		{
            this->m_CVBoost = cv::ml::StatModel::load<cv::ml::Boost>(fn.c_str());
		}
		break;
		case CClassificationAlgs::RandomForest:
		{
			this->m_CVRTrees = cv::ml::StatModel::load<cv::ml::RTrees>(fn.c_str());
		}
		break;
//		case CClassificationAlgs::ExtremeRandomForest:
//		{
//			this->m_CVERTrees->load(fn.c_str());
//		}
		break;
		case CClassificationAlgs::SVM:
		{
                        this->m_CVSVM = cv::ml::StatModel::load<cv::ml::SVM>(fn.c_str());
		}
		case CClassificationAlgs::NONE:
		default:
		break;
	}
}

