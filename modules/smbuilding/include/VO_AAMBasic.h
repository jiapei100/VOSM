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


#ifndef __VO_APPEARANCEMODEL_H__
#define __VO_APPEARANCEMODEL_H__


#include "VO_AXM.h"



/** 
 * @author		JIA Pei
 * @brief		Concatenated appearance Model -- a direct combination of shape model and texture model.
 * @ref			http://www2.imm.dtu.dk/~aam/main/
 */
class VO_AAMBasic : public VO_AXM
{
friend class VO_Fitting2DSM;
friend class VO_FittingAAMBasic;
friend class VO_FittingAAMForwardIA;
friend class VO_FittingAAMInverseIA;
friend class VO_FittingASMLTCs;
friend class VO_FittingASMNDProfiles;
friend class VO_FittingAFM;
protected:
	/** PCA transform for appearance, including eigenstd::vectors, eigenvalues, and mean */
    cv::PCA							m_PCAAppearance;

    /** Shape weights, for scaling to texture scale. 15*15 */
    cv::Mat_<float>                 m_MatWeightsScaleShape2Texture;

	/** Original appearance project to truncated space. For IMM, 60*12 */
    cv::Mat_<float>                 m_MatAppearanceProject2Truncated;

    /** The shape part of the appearance model eigenstd::vectors, 12*15, refer to equation (5.7)
	 * Cootes "Statistical Model of Appearance for Computer Vision" */
    cv::Mat_<float>                 m_MatPcs;

    /** The texture part of the appearance model eigenstd::vectors, 12*36, refer to equation (5.7)
	 * Cootes "Statistical Model of Appearance for Computer Vision" */
    cv::Mat_<float>                 m_MatPcg;

    /** For shape, 116*12, refer to equation (5.9)
	 * Cootes "Statistical Model of Appearance for Computer Vision" */
    cv::Mat_<float>                 m_MatQs;

    /** For texture, 80259*12, refer to equation (5.9)
	 * Cootes "Statistical Model of Appearance for Computer Vision" */
    cv::Mat_<float>                 m_MatQg;

    /** In face, m_MatRc and m_MatRt are just the Hessian Matrics!!! */
    /** For shape, 12*80259, Multivariate Linear Regression Matrix, refer to Stegmann's AAM-API Equation (7.4) */
    cv::Mat_<float>                 m_MatRc;

    /** For shape, 4*80259, Multivariate Linear Regression Matrix, refer to Stegmann's AAM-API Equation (7.4) */
    /** JIA Pei declare that this variable is absolutely useless, and if using it, it makes everything unreasonable and illogical */
    cv::Mat_<float>                 m_MatRt;

    /** Totally, n=m(4(k+4))=60*(4*(12+4))=3840 displacements. 4*12 */
    std::vector< cv::Mat_<float> > 	m_vvCDisps;

    /** Totally, n=m(4(k+4))=60*(4*(12+4))=3840 displacements. 4*4, refer to AAM-API page 3 of 10 */
    std::vector< cv::Mat_<float> > 	m_vvPoseDisps;

    /** Stegmann: Gradient Matrix 80259*12 */
    cv::Mat_<float>                 m_MatCParamGradientMatrix;

    /** Stegmann: Pose Gradient Matrix 80259*4 we may ignore this */
    cv::Mat_<float>                 m_MatPoseGradientMatrix;

    /** Number of Appearance m_iNbOfAppearance = m_iNbOfShapeEigens + m_iNbOfTextureEigens. For IMM: 15+36=51 */
    unsigned int                    m_iNbOfAppearance;

	/** Most possible appearance model eigens before PCA. For IMM: min (51, 60) = 51 */
    unsigned int                	m_iNbOfEigenAppearanceAtMost;

    /** Number of appearance model eigens. For IMM: 12 */
    unsigned int                    m_iNbOfAppearanceEigens;

    /** Truncate Percentage for appearance PCA. Normally, 0.95 */
    float                           m_fTruncatedPercent_Appearance;

    /** Initialization */
    void                            init();

public:
    /** Default constructor to create a VO_AAMBasic object */
    VO_AAMBasic();

    /** Destructor */
    virtual ~VO_AAMBasic();

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////Regression//////////////////////////////////////////////
	/** Unfinished yet.... */
    /** Off-line build prediction matrix for fitting. */
    /** Please refer to http://www2.imm.dtu.dk/~aam/main/node16.html; revised from AAM-API */
    void                            VO_CalcRegressionMatrices();

    /** Carry out C displacement experiments */
    void                            VO_DoCParamExperiments();

    /** Carry out pose displacement experiments */
    void                            VO_DoPoseExperiments();

    /** Carry out multi variate linear regression experiments */
    void                            VO_DoRegression();
	////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////
	//////Gradient -- This is what's happening in Stegmann's code///////////////////////////////
    /** Build gradient matrices */
    void                            VO_CalcGradientMatrices();

    /** Build gradient matrices in terms of C parameters */
    void                            VO_EstCParamGradientMatrix(cv::Mat_<float>& oCParamGM);

    /** Build gradient matrices in terms of pose */
    void                            VO_EstPoseGradientMatrix(cv::Mat_<float>& oPoseGM);
	////////////////////////////////////////////////////////////////////////////////////////////
	
	/** Appearance parameters constraints */
    void							VO_AppearanceParameterConstraint(cv::Mat_<float>& ioC, float nSigma = 4.0f);

	/** Shape and texture project to shape parameters and texture parameters, and then concatenated */
    void							VO_ShapeTexture2Appearance( VO_Shape iShape, VO_Texture iTexture, cv::Mat_<float>& app ) const;
	
	/** Appearance projected to appearance parameters */
    void   	                		VO_AppearanceProjectToCParam(const cv::Mat_<float>& app, cv::Mat_<float>& outC) const;

    /** Shape parameters and texture parameters projected to concatenated parameters */
    void                            VO_SParamTParamProjectToCParam(const cv::Mat_<float>& inS, const cv::Mat_<float>& inT, cv::Mat_<float>& outC) const;

	/** Appearance parameters back projected to appearance */
    void   	                		VO_CParamBackProjectToAppearance(const cv::Mat_<float>& inC, cv::Mat_<float>& app) const;
	
    /** Concatenated parameters back projected to shape parameters and texture parameters */
    void                            VO_CParamBackProjectToSParamTParam(const cv::Mat_<float>& inC, cv::Mat_<float>& outS, cv::Mat_<float>& outT) const;

    /** Concatenated parameters back projected to aligned shape */
    void                            VO_CParamBackProjectToAlignedShape(const cv::Mat_<float>& inC, VO_Shape& oShape, int dim = 2) const;

    /** Concatenated parameters back projected to normalized texture */
    void                            VO_CParamBackProjectToNormalizedTexture(const cv::Mat_<float>& inC, VO_Texture& oTexture, int tr = 3) const;

	/** Build displacement sets */
    void                            VO_CreateDisplacementSets();

    /** Build displacement sets for C parameters */
    static std::vector< cv::Mat_<float> >   VO_CalcCParamDisplacementVectors(const std::vector<float>& vStdDisp, const cv::Mat_<float>& cVectors);

    /** Build displacement sets for Pose parameters */
    static std::vector< cv::Mat_<float> >   VO_CalcPoseDisplacementVectors( const std::vector<float> &vScaleDisp, const std::vector<float>& vRotDisp, const std::vector<float>& vXDisp, const std::vector<float>& vYDisp);

	/** Build Appearance model */
    void                            VO_BuildAppearanceModel(const std::vector<std::string>& allLandmarkFiles4Training,
															const std::vector<std::string>& allImgFiles4Training,
															const std::string& shapeinfoFileName,
															unsigned int database,
															unsigned int channels = 3,
															unsigned int levels = 1,
															int trm = VO_Features::DIRECT,
															float TPShape = 0.95f,
															float TPTexture = 0.95f,
															float TPConcatenated = 0.95f,
															bool useKnownTriangles = false);

    /** Save Appearance Model, to a specified folder */
    void                            VO_Save(const std::string& fd);

    /** Load all parameters */
    void                            VO_Load(const std::string& fd);

    /** Load Parameters for fitting */
    void                            VO_LoadParameters4Fitting(const std::string& fd);

    /** Gets and Sets */
    cv::Mat_<float>                 GetAppearanceMean() const {return this->m_PCAAppearance.mean;}
    cv::Mat_<float>                 GetAppearanceEigenValues() const {return this->m_PCAAppearance.eigenvalues;}
    cv::Mat_<float>                 GetAppearanceEigenVectors() const {return this->m_PCAAppearance.eigenvectors;}
    cv::Mat_<float>                 GetWeightsScaleShape2Texture() const {return this->m_MatWeightsScaleShape2Texture;}
    cv::Mat_<float>					GetAppearanceProject2Truncated() const {return this->m_MatAppearanceProject2Truncated;}
    cv::Mat_<float>                 GetPcs() const {return this->m_MatPcs;}
    cv::Mat_<float>                 GetPcg() const {return this->m_MatPcg;}
    cv::Mat_<float>                 GetQs() const {return this->m_MatQs;}
    cv::Mat_<float>                 GetQg() const {return this->m_MatQg;}
    cv::Mat_<float>                 GetRc() const {return this->m_MatRc;}
    cv::Mat_<float>                 GetRt() const {return this->m_MatRt;}
    std::vector< cv::Mat_<float> >  GetCDisps() const {return this->m_vvCDisps;}
    std::vector< cv::Mat_<float> >  GetPoseDisps() const {return this->m_vvPoseDisps;}
    cv::Mat_<float>                 GetCParamGradientMatrix() const {return this->m_MatCParamGradientMatrix;}
    cv::Mat_<float>                 GetPoseGradientMatrix() const {return this->m_MatPoseGradientMatrix;}
    unsigned int                    GetNbOfAppearance() const {return this->m_iNbOfAppearance;}
	unsigned int                    GetNbOfEigenAppearanceAtMost() const {return this->m_iNbOfEigenAppearanceAtMost;}
    unsigned int                    GetNbOfAppearanceEigens() const {return this->m_iNbOfAppearanceEigens;}
    float                           GetTruncatedPercent_Concatenated() const {return this->m_fTruncatedPercent_Appearance;}

//    void                            SetWeightsScaleShape2Texture(const cv::Mat_<float>& inWeightsScaleShape2Texture)
//                                    {inWeightsScaleShape2Texture.copyTo(this->m_MatWeightsScaleShape2Texture);}
//    void                            SetPcs(const cv::Mat_<float>& inPcs) {inPcs.copyTo(this->m_MatPcs);}
//    void                            SetPcg(const cv::Mat_<float>& inPcg) {inPcg.copyTo(this->m_MatPcg);}
//    void                            SetQs(const cv::Mat_<float>& inQs) {inQs.copyTo(this->m_MatQs);}
//    void                            SetQg(const cv::Mat_<float>& inQg) {inQg.copyTo(this->m_MatQg);}
//    void                            SetRc(const cv::Mat_<float>& inRc) {inRc.copyTo(this->m_MatRc);}
//    void                            SetRt(const cv::Mat_<float>& inRt) {inRt.copyTo(this->m_MatRt);}
//    void                            SetCDisps(const std::vector<std::vector<float> >& inCDisps) {this->m_vvCDisps = inCDisps;}
//    void                            SetPoseDisps(const std::vector<std::vector<float> >& inPoseDisps) {this->m_vvPoseDisps = inPoseDisps;}
//    void                            SetCParamGradientMatrix(const cv::Mat_<float>& inCParamGradientMatrix)
//                                    {inCParamGradientMatrix.copyTo(this->m_MatCParamGradientMatrix);}
//    void                            SetPoseParamGradientMatrix(const cv::Mat_<float>& inPoseGradientMatrix)
//                                    {inPoseGradientMatrix.copyTo(this->m_MatPoseGradientMatrix);}
//    void                            SetNbOfConcatenated(unsigned int inNbOfConcatenated) {this->m_iNbOfAppearance = inNbOfConcatenated;}
//    void                            SetTruncatedPercent_Concatenated(float inTruncatedPercent_Concatenated) 
//                                    {this->m_fTruncatedPercent_Appearance = inTruncatedPercent_Concatenated;}
 };


#endif // __VO_APPEARANCEMODEL_H__

