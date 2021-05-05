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
* Copyright (C):    2006~2021 by JIA Pei, all rights reserved.                                      *
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
* Version:          0.4.0                                                                           *
* Author:           JIA Pei                                                                         *
* Contact:          jiapei@longervision.com                                                         *
* URL:              http://www.longervision.com                                                     *
* Create Date:      2010-11-04                                                                      *
* Modify Date:      2014-04-17                                                                      *
* Modify Date:      2021-05-04                                                                      *
****************************************************************************************************/

#include <string>
#include <sstream>
#include <fstream>

#include "boost/filesystem.hpp"

#include "VO_FittingAAMInverseIA.h"
#include "VO_AAMBasic.h"


/** Default Constructor */
VO_FittingAAMInverseIA::VO_FittingAAMInverseIA()
{
    this->init();
}

/** Destructor */
VO_FittingAAMInverseIA::~VO_FittingAAMInverseIA()
{
    if(this->m_VOAAMInverseIA)      delete this->m_VOAAMInverseIA; this->m_VOAAMInverseIA = NULL;
}

/** Initialization */
void VO_FittingAAMInverseIA::init()
{
    VO_Fitting2DSM::init();
    this->m_VOAAMInverseIA          = new VO_AAMInverseIA();
    this->m_E                       = 0.0f;
    this->m_E_previous              = 0.0f;
}


/**
 * @brief P/Q parameters to estimate the modelled aligned shape
 * @param p  -- input, a transform matrix
 * @param q  -- input, a transform matrix
 * @param oAlignedShape  -- output, the aligned shape
 */
void VO_FittingAAMInverseIA::VO_PParamQParam2ModelAlignedShape( const cv::Mat_<float>& p,
                                                                const cv::Mat_<float>& q,
                                                                VO_Shape& oAlignedShape)
{
    // generate shape and texture from p parameters
    this->m_VOAAMInverseIA->VO_SParamBackProjectToAlignedShape(p, oAlignedShape);
    VO_Shape::GlobalShapeNormalization2D(oAlignedShape, oAlignedShape, q);
}


/**
 * @brief P/Q parameters to estimate the modelled real size shape
 * @param p  -- input, a transform matrix
 * @param q  -- input, a transform matrix
 * @param oAlignedShape  -- output, the aligned shape
 * @param scale -- output, scaling
 * @param rotateAngles -- ouput, rotation
 * @param matCOG -- output, COG
 * @param mtd -- input, method to be used
 */
void VO_FittingAAMInverseIA::VO_PParamQParam2FittingShape(  const cv::Mat_<float>& p,
                                                            const cv::Mat_<float>& q,
                                                            VO_Shape& oShape,
                                                            float& scale,
                                                            std::vector<float>& rotateAngles,
                                                            cv::Mat_<float>& matCOG,
                                                            unsigned int mtd)
{
    switch(mtd)
    {
    case VO_Fitting2DSM::USEGLOBALSHAPENORMALIZATION:
        {
            this->VO_PParamQParam2ModelAlignedShape(p, q, this->m_VOModelAlignedShape);
            VO_Shape::GlobalShapeNormalization2D(this->m_VOModelAlignedShape, oShape, scale, -rotateAngles, matCOG);
        }
        break;
    case VO_Fitting2DSM::USESIMILARITYTRANSFORM:
    default:
        {
            this->m_VOAAMInverseIA->VO_SParamBackProjectToAlignedShape(p, this->m_VOModelAlignedShape);
            float updatescale = 1.0;
            std::vector<float> updateangles(1);
            cv::Mat_<float> updatetranslation = cv::Mat_<float>::zeros(2, 1);
            VO_Shape::GlobalShapeNormalization2SimilarityTrans(q, updatescale, updateangles, updatetranslation );
            scale *= updatescale;
            rotateAngles[0] = -rotateAngles[0]+updateangles[0];
            matCOG(0,0) += updatetranslation(0,0);
            matCOG(1,0) += updatetranslation(1,0);

            // shape adjustment by t parameters - pose transform
            VO_Shape::GlobalShapeNormalization2D(this->m_VOModelAlignedShape, oShape, scale, rotateAngles, matCOG);
        }
        break;
    }
}


/**
 * @author     JIA Pei
 * @version    2010-05-18
 * @brief      Load all AAM data from a specified folder for later fitting, to member variable m_VOAAMInverseIA
 * @param      fd         Input - the folder that AAM to be loaded from
*/
void VO_FittingAAMInverseIA::VO_LoadParameters4Fitting(const std::string& fd)
{
    this->m_VOAAMInverseIA->VO_LoadParameters4Fitting(fd);

    // VO_Fitting2DSM
    this->m_VOTemplateAlignedShape      = this->m_VOAAMInverseIA->m_VOAlignedMeanShape;
    this->m_VOTemplateNormalizedTexture = this->m_VOAAMInverseIA->m_VONormalizedMeanTexture;
    this->m_vTriangle2D                 = this->m_VOAAMInverseIA->m_vNormalizedTriangle2D;
    this->m_vShape2DInfo                = this->m_VOAAMInverseIA->m_vShape2DInfo;
    this->m_FaceParts                   = this->m_VOAAMInverseIA->m_FaceParts;
    this->m_vPointWarpInfo              = this->m_VOAAMInverseIA->m_vNormalizedPointWarpInfo;

    // VO_FittingAAMInverseIA
    this->m_MatCurrentP                 = cv::Mat_<float>::zeros(1, this->m_VOAAMInverseIA->m_iNbOfShapeEigens);
    this->m_MatEstimatedP               = cv::Mat_<float>::zeros(1, this->m_VOAAMInverseIA->m_iNbOfShapeEigens);
    this->m_MatDeltaP                   = cv::Mat_<float>::zeros(1, this->m_VOAAMInverseIA->m_iNbOfShapeEigens);
    this->m_MatCurrentQ                 = cv::Mat_<float>::zeros(1, 4);
    this->m_MatEstimatedQ               = cv::Mat_<float>::zeros(1, 4);
    this->m_MatDeltaQ                   = cv::Mat_<float>::zeros(1, 4);
    this->m_MatDeltaPQ                  = cv::Mat_<float>::zeros(1, this->m_VOAAMInverseIA->m_iNbOfShapeEigens+4);
}


/**
 * @author      JIA Pei
 * @version     2010-05-20
 * @brief       Additive ICIA AAM Fitting, for static images, so that we record the whole fitting process
 * @param       iImg            Input - image to be fitted
 * @param       oImages         Output - the fitted shape
 * @param       epoch           Input - the iteration epoch
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
float VO_FittingAAMInverseIA::VO_IAIAAAMFitting(const cv::Mat& iImg,
                                                std::vector<cv::Mat>& oImages,
                                                unsigned int epoch,
                                                bool record)
{
    this->m_VOEstimatedShape.clone(this->m_VOFittingShape);
double t = (double)cv::getTickCount();

    this->SetProcessingImage(iImg, this->m_VOAAMInverseIA);

    this->m_iIteration = 0;
if(record)
{
    cv::Mat temp0 = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, temp0);
    oImages.push_back(temp0);
}

    // Get m_MatModelAlignedShapeParam and m_fScale, m_vRotateAngles, m_MatCenterOfGravity
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain(this->m_VOFittingShape,
                                                                   this->m_MatCurrentP,
                                                                   this->m_fScale,
                                                                   this->m_vRotateAngles,
                                                                   this->m_MatCenterOfGravity);
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);
if(record)
{
    cv::Mat temp1 = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, temp1);
    oImages.push_back(temp1);
}

    // Set m_MatEstimatedP, m_MatDeltaP, m_MatCurrentQ, m_MatEstimatedQ, m_MatDeltaQ, m_MatDeltaPQ, etc.
    this->m_MatEstimatedP   = cv::Mat_<float>::zeros(this->m_MatEstimatedP.size());
    this->m_MatDeltaP       = cv::Mat_<float>::zeros(this->m_MatDeltaP.size());
    this->m_MatEstimatedQ   = cv::Mat_<float>::zeros(this->m_MatEstimatedQ.size());
    this->m_MatCurrentQ     = cv::Mat_<float>::zeros(this->m_MatCurrentQ.size());
    this->m_MatDeltaQ       = cv::Mat_<float>::zeros(this->m_MatDeltaQ.size());
    this->m_MatDeltaPQ      = cv::Mat_<float>::zeros(this->m_MatDeltaPQ.size());

    // Step (1) Warp I with W(x;p) followed by N(x;q) to compute I(N(W(x;p);q))
    this->VO_PParamQParam2FittingShape( this->m_MatCurrentP,
                                        this->m_MatCurrentQ,
                                        this->m_VOFittingShape,
                                        this->m_fScale,
                                        this->m_vRotateAngles,
                                        this->m_MatCenterOfGravity );
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);
if(record)
{
    cv::Mat temp2 = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, temp2);
    oImages.push_back(temp2);
}

    // Step (2) Compute the error image I(N(W(x;p);q))-A0(x)
    this->m_E_previous = this->m_E = this->VO_CalcErrorImage(this->m_ImageProcessing,
                                                            this->m_VOFittingShape,
                                                            this->m_VOTemplateNormalizedTexture,
                                                            this->m_VOTextureError);

    do
    {
        ++this->m_iIteration;
        float estScale = this->m_fScale;
        std::vector<float> estRotateAngles = this->m_vRotateAngles;
        cv::Mat_<float> estCOG = this->m_MatCenterOfGravity.clone();

        // Step (7) -- a bit modification
        cv::gemm(this->m_VOTextureError.GetTheTextureInARow(), this->m_VOAAMInverseIA->m_MatICIAPreMatrix, -1, cv::Mat(), 0, this->m_MatDeltaPQ, cv::GEMM_2_T);

        // Step (8) -- a bit modification. Get DeltaP DeltaQ respectively
        this->m_MatDeltaQ = this->m_MatDeltaPQ(cv::Rect( 0, 0, this->m_MatDeltaQ.cols, 1));
        this->m_MatDeltaP = this->m_MatDeltaPQ(cv::Rect( this->m_MatDeltaQ.cols, 0, this->m_MatDeltaP.cols, 1));

        // Step (9) -- Additive
        cv::add(this->m_MatCurrentQ, this->m_MatDeltaQ, this->m_MatEstimatedQ);
        cv::add(this->m_MatCurrentP, this->m_MatDeltaP, this->m_MatEstimatedP);

        this->m_VOAAMInverseIA->VO_ShapeParameterConstraint(this->m_MatEstimatedP);
        this->VO_PParamQParam2FittingShape( this->m_MatEstimatedP,
                                            this->m_MatEstimatedQ,
                                            this->m_VOEstimatedShape,
                                            estScale,
                                            estRotateAngles,
                                            estCOG );
        this->m_VOEstimatedShape.ConstrainShapeInImage(this->m_ImageProcessing);
        this->m_E = this->VO_CalcErrorImage(this->m_ImageProcessing,
                                            this->m_VOEstimatedShape,
                                            this->m_VOTemplateNormalizedTexture,
                                            this->m_VOEstimatedTextureError);

        if (this->m_E < this->m_E_previous)
        {
            // Unlike what's happening in Basic AAM, 
            // since m_fScale, m_vRotateAngles and m_MatCenterOfGravity have not been updated in ICIA,
            // m_MatCurrentT should not be assigned to 0 now!
//            this->m_MatCurrentQ = cv::Mat_<float>::zeros(this->m_MatCurrentQ.size());
            this->m_MatEstimatedQ.copyTo(this->m_MatCurrentQ);
            this->m_MatEstimatedP.copyTo(this->m_MatCurrentP);
            this->m_VOFittingShape.clone(this->m_VOEstimatedShape);
            this->m_VOTextureError.clone(this->m_VOEstimatedTextureError);
            this->m_E_previous = this->m_E;
if(record)
{
    cv::Mat temp = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, temp);
    oImages.push_back(temp);
}
        }
        else
            break;

    }while( ( fabs(this->m_E) > FLT_EPSILON ) && ( this->m_iIteration < epoch ) );

    // Recalculate all parameters finally, this is also optional.
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                    this->m_MatCurrentP,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity );
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    // Step (10) (Option step), Post-computation. Get m_MatModelNormalizedTextureParam
    VO_TextureModel::VO_LoadOneTextureFromShape(this->m_VOFittingShape,
                                                this->m_ImageProcessing,
                                                this->m_vTriangle2D,
                                                this->m_vPointWarpInfo,
                                                this->m_VOFittingTexture );
    // estimate the texture model parameters
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyTexture(this->m_VOFittingTexture, this->m_MatModelNormalizedTextureParam);

t = ((double)cv::getTickCount() -  t )/  (cv::getTickFrequency()*1000.);
std::cout << "IAIA AAM fitting time cost: " << t << " millisec" << std::endl;

    return t;
}


/**
 * @author      JIA Pei
 * @version     2010-05-20
 * @brief       Additive ICIA AAM Fitting, for dynamic image sequence
 * @param       iImg            Input - image to be fitted
 * @param       ioShape         Input and Output - the fitted shape
 * @param       oImg            Output - the fitted image
 * @param       epoch           Input - the iteration epoch
*/
float VO_FittingAAMInverseIA::VO_IAIAAAMFitting(const cv::Mat& iImg,
                                                VO_Shape& ioShape,
                                                cv::Mat& oImg,
                                                unsigned int epoch)
{
    this->m_VOFittingShape.clone(ioShape);
    this->m_VOEstimatedShape.clone(this->m_VOFittingShape);
double t = (double)cv::getTickCount();

    this->SetProcessingImage(iImg, this->m_VOAAMInverseIA);
    this->m_iIteration = 0;

    // Get m_MatModelAlignedShapeParam and m_fScale, m_vRotateAngles, m_MatCenterOfGravity
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                    this->m_MatCurrentP,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity);
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    // Set m_MatEstimatedP, m_MatDeltaP, m_MatCurrentQ, m_MatEstimatedQ, m_MatDeltaQ, m_MatDeltaPQ, etc.
    this->m_MatEstimatedP   = cv::Mat_<float>::zeros(this->m_MatEstimatedP.size());
    this->m_MatDeltaP       = cv::Mat_<float>::zeros(this->m_MatDeltaP.size());
    this->m_MatEstimatedQ   = cv::Mat_<float>::zeros(this->m_MatEstimatedQ.size());
    this->m_MatCurrentQ     = cv::Mat_<float>::zeros(this->m_MatCurrentQ.size());
    this->m_MatDeltaQ       = cv::Mat_<float>::zeros(this->m_MatDeltaQ.size());
    this->m_MatDeltaPQ      = cv::Mat_<float>::zeros(this->m_MatDeltaPQ.size());

    // Step (1) Warp I with W(x;p) followed by N(x;q) to compute I(N(W(x;p);q))
    this->VO_PParamQParam2FittingShape( this->m_MatCurrentP,
                                        this->m_MatCurrentQ,
                                        this->m_VOFittingShape,
                                        this->m_fScale,
                                        this->m_vRotateAngles,
                                        this->m_MatCenterOfGravity );
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    // Step (2) Compute the error image I(N(W(x;p);q))-A0(x)
    this->m_E_previous = this->m_E = this->VO_CalcErrorImage(   this->m_ImageProcessing,
                                                                this->m_VOFittingShape,
                                                                this->m_VOTemplateNormalizedTexture,
                                                                this->m_VOTextureError);

    do
    {
        ++this->m_iIteration;
        float estScale = this->m_fScale;
        std::vector<float> estRotateAngles = this->m_vRotateAngles;
        cv::Mat_<float> estCOG = this->m_MatCenterOfGravity.clone();

        // Step (7) -- a bit modification
        cv::gemm(this->m_VOTextureError.GetTheTextureInARow(), this->m_VOAAMInverseIA->m_MatICIAPreMatrix, -1, cv::Mat(), 0, this->m_MatDeltaPQ, cv::GEMM_2_T);

        // Step (8) -- a bit modification. Get DeltaP DeltaQ respectively
        this->m_MatDeltaQ = this->m_MatDeltaPQ(cv::Rect( 0, 0, this->m_MatDeltaQ.cols, 1));
        this->m_MatDeltaP = this->m_MatDeltaPQ(cv::Rect( this->m_MatDeltaQ.cols, 0, this->m_MatDeltaP.cols, 1));

        // Step (9) -- Additive
        cv::add(this->m_MatCurrentQ, this->m_MatDeltaQ, this->m_MatEstimatedQ);
        cv::add(this->m_MatCurrentP, this->m_MatDeltaP, this->m_MatEstimatedP);

        this->m_VOAAMInverseIA->VO_ShapeParameterConstraint(this->m_MatEstimatedP);
        this->VO_PParamQParam2FittingShape( this->m_MatEstimatedP,
                                            this->m_MatEstimatedQ,
                                            this->m_VOEstimatedShape,
                                            estScale,
                                            estRotateAngles,
                                            estCOG );
        this->m_VOEstimatedShape.ConstrainShapeInImage(this->m_ImageProcessing);
        this->m_E = this->VO_CalcErrorImage(this->m_ImageProcessing,
                                            this->m_VOEstimatedShape,
                                            this->m_VOTemplateNormalizedTexture,
                                            this->m_VOEstimatedTextureError);

        if (this->m_E < this->m_E_previous)
        {
            // Unlike what's happening in Basic AAM, 
            // since m_fScale, m_vRotateAngles and m_MatCenterOfGravity have not been updated in ICIA,
            // m_MatCurrentT should not be assigned to 0 now!
//            this->m_MatCurrentQ = cv::Mat_<float>::zeros(this->m_MatCurrentQ.size());
            this->m_MatEstimatedQ.copyTo(this->m_MatCurrentQ);
            this->m_MatEstimatedP.copyTo(this->m_MatCurrentP);
            this->m_VOFittingShape.clone(this->m_VOEstimatedShape);
            this->m_VOTextureError.clone(this->m_VOEstimatedTextureError);
            this->m_E_previous = this->m_E;
        }
        else
            break;

    }while( ( fabs(this->m_E) > FLT_EPSILON ) && ( this->m_iIteration < epoch ) );

    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, oImg);

    // Recalculate all parameters finally, this is also optional.
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                    this->m_MatCurrentP,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity );
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    // Step (10) (Option step), Post-computation. Get m_MatModelNormalizedTextureParam
    VO_TextureModel::VO_LoadOneTextureFromShape(this->m_VOFittingShape,
                                                this->m_ImageProcessing,
                                                this->m_vTriangle2D,
                                                this->m_vPointWarpInfo,
                                                this->m_VOFittingTexture );
    // estimate the texture model parameters
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyTexture(this->m_VOFittingTexture, this->m_MatModelNormalizedTextureParam);

    ioShape.clone(this->m_VOFittingShape);

t = ((double)cv::getTickCount() -  t )/  (cv::getTickFrequency()*1000.);
std::cout << "IAIA AAM fitting time cost: " << t << " millisec" << std::endl;
this->m_fFittingTime = t;

    return t;
}


/**
 * @author      JIA Pei
 * @version     2010-05-20
 * @brief       CMU ICIA AAM Fitting, for static images, so that we record the whole fitting process
 * @param       iImg            Input - image to be fitted
 * @param       oImages         Output - the fitted shape
 * @param       epoch           Input - the iteration epoch
*/
float VO_FittingAAMInverseIA::VO_ICIAAAMFitting(const cv::Mat& iImg,
                                                std::vector<cv::Mat>& oImages,
                                                unsigned int epoch,
                                                bool record)
{
    this->m_VOEstimatedShape.clone(this->m_VOFittingShape);
double t = (double)cv::getTickCount();

    this->SetProcessingImage(iImg, this->m_VOAAMInverseIA);
    this->m_iIteration = 0;

if(record)
{
    cv::Mat temp0 = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, temp0);
    oImages.push_back(temp0);
}

    // Get m_MatCurrentP and m_MatCurrentQ
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain(this->m_VOFittingShape,
                                                                   this->m_MatCurrentP,
                                                                   this->m_fScale,
                                                                   this->m_vRotateAngles,
                                                                   this->m_MatCenterOfGravity);
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);
if(record)
{
    cv::Mat temp1 = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, temp1);
    oImages.push_back(temp1);
}

    this->m_MatDeltaP        = cv::Mat_<float>::zeros(this->m_MatDeltaP.size());
    this->m_MatDeltaQ        = cv::Mat_<float>::zeros(this->m_MatDeltaQ.size());
    this->m_MatCurrentQ      = cv::Mat_<float>::zeros(this->m_MatCurrentQ.size());
    this->m_MatDeltaPQ       = cv::Mat_<float>::zeros(this->m_MatDeltaPQ.size());

    // Step (1) Warp I with W(x;p) followed by N(x;q) to compute I(N(W(x;p);q))
    this->VO_PParamQParam2FittingShape( this->m_MatCurrentP,
                                        this->m_MatCurrentQ,
                                        this->m_VOFittingShape,
                                        this->m_fScale,
                                        this->m_vRotateAngles,
                                        this->m_MatCenterOfGravity );
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);
if(record)
{
    cv::Mat temp2 = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, temp2);
    oImages.push_back(temp2);
}

    // Step (2) Compute the error image I(N(W(x;p);q))-A0(x)
    this->m_E_previous = this->m_E = this->VO_CalcErrorImage(this->m_ImageProcessing,
                                                            this->m_VOFittingShape,
                                                            this->m_VOTemplateNormalizedTexture,
                                                            this->m_VOTextureError);

    do
    {
        ++this->m_iIteration;

        // Step (7) -- a bit modification
        cv::gemm(this->m_VOTextureError.GetTheTextureInARow(), this->m_VOAAMInverseIA->m_MatICIAPreMatrix, -1, cv::Mat(), 0, this->m_MatDeltaPQ, cv::GEMM_2_T);

        // Step (8) -- a bit modification. Get DeltaP DeltaQ respectively
        this->m_MatDeltaQ = this->m_MatDeltaPQ(cv::Rect( 0, 0, this->m_MatDeltaQ.cols, 1));
        this->m_MatDeltaP = this->m_MatDeltaPQ(cv::Rect( this->m_MatDeltaQ.cols, 0, this->m_MatDeltaP.cols, 1));

        // Step (9) -- CMU Inverse Compositional
        this->VO_CMUInverseCompositional( this->m_MatDeltaP, this->m_MatDeltaQ, this->m_VOFittingShape, this->m_VOEstimatedShape );

        // Ensure Inverse Compositional still satisfies global shape constraints
        this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOEstimatedShape,
                                                                        this->m_MatEstimatedP,
                                                                        this->m_fScale,
                                                                        this->m_vRotateAngles,
                                                                        this->m_MatCenterOfGravity);
        this->m_VOEstimatedShape.ConstrainShapeInImage(this->m_ImageProcessing);

        this->m_E = this->VO_CalcErrorImage(this->m_ImageProcessing,
                                            this->m_VOEstimatedShape,
                                            this->m_VOTemplateNormalizedTexture,
                                            this->m_VOEstimatedTextureError);

        if (this->m_E < this->m_E_previous)
        {
            // Unlike what's happening in Basic AAM, 
            // since m_fScale, m_vRotateAngles and m_MatCenterOfGravity have not been updated in ICIA,
            // m_MatCurrentT should not be assigned to 0 now!
//            this->m_MatCurrentQ = cv::Mat_<float>::zeros(this->m_MatCurrentQ.size());
            this->m_VOFittingShape.clone(this->m_VOEstimatedShape);
            this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                            this->m_MatCurrentP,
                                                                            this->m_fScale,
                                                                            this->m_vRotateAngles,
                                                                            this->m_MatCenterOfGravity);
            this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);
            this->m_VOTextureError.clone(this->m_VOEstimatedTextureError);
            this->m_E_previous = this->m_E;
if(record)
{
    cv::Mat temp = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, temp);
    oImages.push_back(temp);
}
        }
        else
            break;

    }while( ( fabs(this->m_E) > FLT_EPSILON ) && ( this->m_iIteration < epoch ) );

    // Recalculate all parameters finally, this is also optional.
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                    this->m_MatCurrentP,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity );
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    // Step (10) (Option step), Post-computation. Get m_MatModelNormalizedTextureParam
    VO_TextureModel::VO_LoadOneTextureFromShape(this->m_VOFittingShape,
                                                this->m_ImageProcessing,
                                                this->m_vTriangle2D,
                                                this->m_vPointWarpInfo,
                                                this->m_VOFittingTexture );
    // estimate the texture model parameters
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyTexture(this->m_VOFittingTexture, this->m_MatModelNormalizedTextureParam);

t = ((double)cv::getTickCount() -  t )/  (cv::getTickFrequency()*1000.);
std::cout << "ICIA AAM fitting time cost: " << t << " millisec" << std::endl;

    return t;
}


/**
 * @author      JIA Pei
 * @version     2010-05-20
 * @brief       CMU ICIA AAM Fitting, for dynamic image sequence
 * @param       iImg            Input - image to be fitted
 * @param       ioShape         Input and Output - the fitted shape
 * @param       oImg            Output - the fitted image
 * @param       epoch           Input - the iteration epoch
*/
float VO_FittingAAMInverseIA::VO_ICIAAAMFitting(const cv::Mat& iImg,
                                                VO_Shape& ioShape,
                                                cv::Mat& oImg,
                                                unsigned int epoch)
{
    this->m_VOFittingShape.clone(ioShape);
    this->m_VOEstimatedShape.clone(this->m_VOFittingShape);
double t = (double)cv::getTickCount();

    this->SetProcessingImage(iImg, this->m_VOAAMInverseIA);
    this->m_iIteration = 0;

    // Get m_MatCurrentP and m_MatCurrentQ
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                    this->m_MatCurrentP,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity);
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    this->m_MatDeltaP       = cv::Mat_<float>::zeros(this->m_MatDeltaP.size());
    this->m_MatDeltaQ       = cv::Mat_<float>::zeros(this->m_MatDeltaQ.size());
    this->m_MatCurrentQ     = cv::Mat_<float>::zeros(this->m_MatCurrentQ.size());
    this->m_MatDeltaPQ      = cv::Mat_<float>::zeros(this->m_MatDeltaPQ.size());

    // Step (1) Warp I with W(x;p) followed by N(x;q) to compute I(N(W(x;p);q))
    this->VO_PParamQParam2FittingShape( this->m_MatCurrentP,
                                        this->m_MatCurrentQ,
                                        this->m_VOFittingShape,
                                        this->m_fScale,
                                        this->m_vRotateAngles,
                                        this->m_MatCenterOfGravity );
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    // Step (2) Compute the error image I(N(W(x;p);q))-A0(x)
    this->m_E_previous = this->m_E = this->VO_CalcErrorImage(this->m_ImageProcessing,
                                                            this->m_VOFittingShape,
                                                            this->m_VOTemplateNormalizedTexture,
                                                            this->m_VOTextureError);

    do
    {
        ++this->m_iIteration;

        // Step (7) -- a bit modification
        cv::gemm(this->m_VOTextureError.GetTheTextureInARow(), this->m_VOAAMInverseIA->m_MatICIAPreMatrix, -1, cv::Mat(), 0, this->m_MatDeltaPQ, cv::GEMM_2_T);

        // Step (8) -- a bit modification. Get DeltaP DeltaQ respectively
        this->m_MatDeltaQ = this->m_MatDeltaPQ(cv::Rect( 0, 0, this->m_MatDeltaQ.cols, 1));
        this->m_MatDeltaP = this->m_MatDeltaPQ(cv::Rect( this->m_MatDeltaQ.cols, 0, this->m_MatDeltaP.cols, 1));

        // Step (9) -- CMU Inverse Compositional
        this->VO_CMUInverseCompositional( this->m_MatDeltaP, this->m_MatDeltaQ, this->m_VOFittingShape, this->m_VOEstimatedShape );
        
        // Ensure Inverse Compositional still satisfies global shape constraints
        this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOEstimatedShape,
                                                                        this->m_MatEstimatedP,
                                                                        this->m_fScale,
                                                                        this->m_vRotateAngles,
                                                                        this->m_MatCenterOfGravity);
        this->m_VOEstimatedShape.ConstrainShapeInImage(this->m_ImageProcessing);

        this->m_E = this->VO_CalcErrorImage(this->m_ImageProcessing,
                                            this->m_VOEstimatedShape,
                                            this->m_VOTemplateNormalizedTexture,
                                            this->m_VOEstimatedTextureError);

        if (this->m_E < this->m_E_previous)
        {
            // Unlike what's happening in Basic AAM, 
            // since m_fScale, m_vRotateAngles and m_MatCenterOfGravity have not been updated in ICIA,
            // m_MatCurrentT should not be assigned to 0 now!
//            this->m_MatCurrentQ = cv::Mat_<float>::zeros(this->m_MatCurrentQ.size());
            this->m_VOFittingShape.clone(this->m_VOEstimatedShape);
            this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                            this->m_MatCurrentP,
                                                                            this->m_fScale,
                                                                            this->m_vRotateAngles,
                                                                            this->m_MatCenterOfGravity);
            this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);
            this->m_VOTextureError.clone(this->m_VOEstimatedTextureError);
            this->m_E_previous = this->m_E;

        }
        else
            break;

    }while( ( fabs(this->m_E) > FLT_EPSILON ) && ( this->m_iIteration < epoch ) );

    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOAAMInverseIA, oImg);

    // Recalculate all parameters finally, this is also optional.
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                    this->m_MatCurrentP,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity );

    // Step (10) (Option step), Post-computation. Get m_MatModelNormalizedTextureParam
    VO_TextureModel::VO_LoadOneTextureFromShape(this->m_VOFittingShape,
                                                this->m_ImageProcessing,
                                                this->m_vTriangle2D,
                                                this->m_vPointWarpInfo,
                                                this->m_VOFittingTexture );
    // estimate the texture model parameters
    this->m_VOAAMInverseIA->VO_CalcAllParams4AnyTexture(this->m_VOFittingTexture, this->m_MatModelNormalizedTextureParam);
    ioShape.clone(this->m_VOFittingShape);

t = ((double)cv::getTickCount() -  t )/  (cv::getTickFrequency()*1000.);
std::cout << "ICIA AAM fitting time cost: " << t << " millisec" << std::endl;
this->m_fFittingTime = t;

    return t;
}


/**
 * @author      Yao Wei
 * @brief       CMU Inverse Compositional !!
 * @param       - matDeltaP     Input -- deltap
 * @param       - matDeltaQ     Input -- deltaq
 * @param       - s             Input -- the shape
 * @param       - estShape      Output -- newly estimated shape by Inverse compositional
 */
void VO_FittingAAMInverseIA::VO_CMUInverseCompositional(const cv::Mat_<float>& matDeltaP,
                                                        const cv::Mat_<float>& matDeltaQ,
                                                        const VO_Shape& s,
                                                        VO_Shape& estShape)
{
    VO_Shape S0;
    this->VO_PParamQParam2ModelAlignedShape( matDeltaP, matDeltaQ, S0);
//    cvConvertScale(dpq, __inv_pq, -1);
//    __shape.CalcShape(__inv_pq, __update_s0);    // __update_s0 = N.W(s0, -delta_p, -delta_q)

    //Secondly: Composing the Incremental Warp with the Current Warp Estimate.
    cv::Point2f res, tmp;
    int count = 0;
    std::vector<unsigned int> vertexIdxes;

    for(unsigned int i = 0; i < this->m_VOAAMInverseIA->m_iNbOfPoints; i++)
    {
        res.x = 0.0;    res.y = 0.0;
        count = 0;
        //The only problem with this approach is which triangle do we use?
        //In general there will be several triangles that share the i-th vertex.
        for(unsigned j = 0; j < this->m_VOAAMInverseIA->m_iNbOfTriangles; j++)    // see Figure (11)
        {
            if ( this->m_vTriangle2D[j].HasNode(i) )
            {
                vertexIdxes = this->m_vTriangle2D[j].GetVertexIndexes();

                VO_WarpingPoint::WarpOnePoint(  S0.GetA2DPoint(i),
                                                this->m_vTriangle2D[j], 
                                                tmp,
                                                s.GetA2DPoint(vertexIdxes[0]),
                                                s.GetA2DPoint(vertexIdxes[1]),
                                                s.GetA2DPoint(vertexIdxes[2]) );
                res.x += tmp.x;
                res.y += tmp.y;
                count++;
            }
        }
        // average the result so as to smooth the warp at each vertex
        if(count == 0)
            std::cerr << "There must be something wrong when CMU Inverse Compositional !" << std::endl;
        res.x /= count;
        res.y /= count;
        estShape.SetA2DPoint(res, i);
    }
}

