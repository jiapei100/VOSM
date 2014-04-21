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
* Modify Date:      2014-04-15                                                                      *
****************************************************************************************************/

#include <string>
#include <sstream>
#include <fstream>

#include "boost/filesystem.hpp"

#include "VO_FittingASMLTCs.h"


/** Constructor */
VO_FittingASMLTCs::VO_FittingASMLTCs()
{
    this->init();
}


/** Destructor */
VO_FittingASMLTCs::~VO_FittingASMLTCs()
{
    if(this->m_VOASMLTC)    delete this->m_VOASMLTC; this->m_VOASMLTC = NULL;
}


/** Initialization */
void VO_FittingASMLTCs::init()
{
    VO_Fitting2DSM::init();
    this->m_VOASMLTC        = new VO_ASMLTCs();
    this->m_iFittingMethod  = VO_AXM::ASM_LTC;
}


/**
 * @author     JIA Pei
 * @version    2010-05-18
 * @brief      Load all AAM data from a specified folder for later fitting, to member variable m_VOASMLTC
 * @param      fd         Input - the folder that AAM to be loaded from
 */
void VO_FittingASMLTCs::VO_LoadParameters4Fitting(const string& fd)
{
    this->m_VOASMLTC->VO_LoadParameters4Fitting(fd);

    // VO_Fitting2DSM
    this->m_VOTemplateAlignedShape      = this->m_VOASMLTC->m_VOAlignedMeanShape;
    this->m_VOTemplateNormalizedTexture = this->m_VOASMLTC->m_VONormalizedMeanTexture;
    this->m_vTriangle2D                 = this->m_VOASMLTC->m_vNormalizedTriangle2D;
    this->m_vShape2DInfo                = this->m_VOASMLTC->m_vShape2DInfo;
    this->m_FaceParts                   = this->m_VOASMLTC->m_FaceParts;
    this->m_vPointWarpInfo              = this->m_VOASMLTC->m_vNormalizedPointWarpInfo;
}

/**
 * @author      JIA Pei
 * @version     2010-05-20
 * @brief       Additive ASM ND Profiles Fitting, for static images, so that we record the whole fitting process
 * @param       iImg            Input - image to be fitted
 * @param       oImages         Output - the fitting process
 * @param       trmethod        Input - texture representation method
 * @param       epoch           Input - the iteration epoch
 * @param       pyramidlevel    Input - pyramid level, 1, 2, 3 or 4 at most
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
float VO_FittingASMLTCs::VO_ASMLTCFitting(  const Mat& iImg,
                                            vector<Mat>& oImages,
                                            unsigned int trmethod,
                                            unsigned int epoch,
                                            unsigned int pyramidlevel,
                                            bool record)
{
double t = (double)cvGetTickCount();

    this->m_iNbOfPyramidLevels = pyramidlevel;
    this->SetProcessingImage(iImg, this->m_VOASMLTC);
    this->m_iIteration = 0;

if(record)
{
    Mat temp = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOASMLTC, temp);
    oImages.push_back(temp);
}

    // Get m_MatModelAlignedShapeParam and m_fScale, m_vRotateAngles, m_MatCenterOfGravity
    this->m_VOASMLTC->VO_CalcAllParams4AnyShapeWithConstrain(   this->m_VOFittingShape,
                                                                this->m_MatModelAlignedShapeParam,
                                                                this->m_fScale,
                                                                this->m_vRotateAngles,
                                                                this->m_MatCenterOfGravity );
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);
if(record)
{
    Mat temp1 = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOASMLTC, temp1);
    oImages.push_back(temp1);
}

    // Explained by YAO Wei, 2008-2-9.
    // Scale this->m_VOFittingShape, so face width is a constant StdFaceWidth.
    //this->m_fScale2 = this->m_VOASMLTC->m_VOReferenceShape.GetWidth() / this->m_VOFittingShape.GetWidth();
    this->m_fScale2 = this->m_VOASMLTC->m_VOReferenceShape.GetCentralizedShapeSize() / this->m_VOFittingShape.GetCentralizedShapeSize();
    this->m_VOFittingShape *= this->m_fScale2;

    int w = (int)(iImg.cols*this->m_fScale2);
    int h = (int)(iImg.rows*this->m_fScale2);
    Mat SearchImage = Mat(Size( w, h ), this->m_ImageProcessing.type(), this->m_ImageProcessing.channels());

    float PyrScale = pow(2.0f, (float) (this->m_iNbOfPyramidLevels-1.0f) );
    this->m_VOFittingShape /= PyrScale;

    const int nQualifyingDisplacements = (int)(this->m_VOASMLTC->m_iNbOfPoints * VO_Fitting2DSM::pClose);

    // for each level in the image pyramid
    for (int iLev = this->m_iNbOfPyramidLevels-1; iLev >= 0; iLev--)
    {
        // Set image roi, instead of cvCreateImage a new image to speed up
        Mat siROI = SearchImage(Rect(0, 0, (int)(w/PyrScale), (int)(h/PyrScale) ) );
        cv::resize(this->m_ImageProcessing, siROI, siROI.size());

if(record)
{
        Mat temp2 = Mat(iImg.size(), iImg.type(), iImg.channels());
        Mat temp2ROI = temp2(Range (0, (int)(iImg.rows/PyrScale) ), Range (0, (int)(iImg.cols/PyrScale) ) );
        cv::resize(iImg, temp2ROI, temp2ROI.size() );
        oImages.push_back(temp2);
        VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape / this->m_fScale2, this->m_VOASMLTC, temp2);
}

        this->m_VOEstimatedShape = this->m_VOFittingShape;
        this->PyramidFit(   this->m_VOEstimatedShape,
                            SearchImage,
                            oImages,
                            iLev,
                            VO_Fitting2DSM::pClose,
                            epoch,
                            record);
        this->m_VOFittingShape = this->m_VOEstimatedShape;

        if (iLev != 0)
        {
            PyrScale /= 2.0f;
            this->m_VOFittingShape *= 2.0f;
        }
    }

    // Explained by YAO Wei, 2008-02-09.
    // this->m_fScale2 back to original size
    this->m_VOFittingShape /= this->m_fScale2;

t = ((double)cvGetTickCount() -  t )/  (cvGetTickFrequency()*1000.);
printf("MRASM fitting time cost: %.2f millisec\n", t);

    return t;
}


/**
 * @author      JIA Pei
 * @version     2010-05-20
 * @brief       Additive LTC ASM Fitting, for dynamic image sequence
 * @param       iImg            Input - image to be fitted
 * @param       ioShape         Input and output - the shape
 * @param       oImg            Output - the fitted image
 * @param       trmethod        Input - texture representation method
 * @param       epoch           Input - the iteration epoch
 * @param       pyramidlevel    Input - pyramid level, 1, 2, 3 or 4 at most
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
float VO_FittingASMLTCs::VO_ASMLTCFitting(  const Mat& iImg,
                                            VO_Shape& ioShape,
                                            Mat& oImg,
                                            unsigned int trmethod,
                                            unsigned int epoch,
                                            unsigned int pyramidlevel)
{
    this->m_VOFittingShape.clone(ioShape);
double t = (double)cvGetTickCount();

    this->m_iNbOfPyramidLevels = pyramidlevel;
    this->SetProcessingImage(iImg, this->m_VOASMLTC);
    this->m_iIteration = 0;

    // Get m_MatModelAlignedShapeParam and m_fScale, m_vRotateAngles, m_MatCenterOfGravity
    this->m_VOASMLTC->VO_CalcAllParams4AnyShapeWithConstrain(   this->m_VOFittingShape,
                                                                this->m_MatModelAlignedShapeParam,
                                                                this->m_fScale,
                                                                this->m_vRotateAngles,
                                                                this->m_MatCenterOfGravity);
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    // Explained by YAO Wei, 2008-2-9.
    // Scale this->m_VOShape, so face width is a constant StdFaceWidth.
    //this->m_fScale2 = this->m_VOASMLTC->m_VOReferenceShape.GetWidth() / this->m_VOFittingShape.GetWidth();
    this->m_fScale2 = this->m_VOASMLTC->m_VOReferenceShape.GetCentralizedShapeSize() / this->m_VOFittingShape.GetCentralizedShapeSize();
    this->m_VOFittingShape *= this->m_fScale2;

    int w = (int)(iImg.cols*this->m_fScale2);
    int h = (int)(iImg.rows*this->m_fScale2);
    Mat SearchImage = Mat(Size( w, h ), this->m_ImageProcessing.type(), this->m_ImageProcessing.channels() );

    float PyrScale = pow(2.0f, (float) (this->m_iNbOfPyramidLevels-1.0f) );
    this->m_VOFittingShape /= PyrScale;

    const int nQualifyingDisplacements = (int)(this->m_VOASMLTC->m_iNbOfPoints * VO_Fitting2DSM::pClose);

    // for each level in the image pyramid
    for (int iLev = this->m_iNbOfPyramidLevels-1; iLev >= 0; iLev--)
    {
        // Set image roi, instead of cvCreateImage a new image to speed up
        Mat siROI = SearchImage(Rect(0, 0, (int)(w/PyrScale), (int)(h/PyrScale) ) );
        cv::resize(this->m_ImageProcessing, siROI, siROI.size());

        int nGoodLandmarks = 0;

        this->m_VOEstimatedShape = this->m_VOFittingShape;
        this->PyramidFit(   this->m_VOEstimatedShape,
                            SearchImage,
                            iLev,
                            VO_Fitting2DSM::pClose,
                            epoch);
        this->m_VOFittingShape = this->m_VOEstimatedShape;

        if (iLev != 0)
        {
            PyrScale /= 2.0f;
            this->m_VOFittingShape *= 2.0f;
        }
    }

    // Explained by YAO Wei, 2008-02-09.
    // this->m_fScale2 back to original size
    this->m_VOFittingShape /= this->m_fScale2;

    ioShape.clone(this->m_VOFittingShape);
    VO_Fitting2DSM::VO_DrawMesh(ioShape, this->m_VOASMLTC, oImg);

t = ((double)cvGetTickCount() -  t )/  (cvGetTickFrequency()*1000.);
printf("MRASM fitting time cost: %.2f millisec\n", t);
this->m_fFittingTime = t;

    return t;

}


/**
Find the best offset for one point
*/
float VO_FittingASMLTCs::VO_FindBestMatchingLTC(const VO_ASMLTCs* asmmodel,
                                                const Mat& iImg,
                                                const VO_Shape& iShape,
                                                const vector<VO_Shape2DInfo>& iShapeInfo,
                                                const Mat_<float>& iMean,
                                                const Mat_<float>& iCovInverse,
                                                unsigned int ptIdx,
                                                unsigned int offSetTolerance,
                                                Point2f& ioLocation,
                                                unsigned int LTCType)
{
    float BestFit = FLT_MAX;
    int nBestOffsetX = FLT_MAX, nBestOffsetY = FLT_MAX;    // might be + or -
    float Fit;
    float dist = 0.0f;
    ioLocation = iShape.GetA2DPoint ( ptIdx );
    float xx = ioLocation.x - (float)cvRound(ioLocation.x);
    float yy = ioLocation.y - (float)cvRound(ioLocation.y);

    Mat tmpFeatures;
    // Find the best in just one direction
    for (int x = -(int)offSetTolerance; x <= (int)offSetTolerance; ++x)
    {
        for (int y = -(int)offSetTolerance; y <= (int)offSetTolerance; ++y)
        {
            VO_ASMLTCs::VO_LoadLTC4OneAnnotatedPoint(   iImg,
                                                        iShape,
                                                        ptIdx,
                                                        asmmodel->m_localImageSize,
                                                        asmmodel->m_pVOfeatures,
                                                        x,
                                                        y);
            tmpFeatures = asmmodel->m_pVOfeatures->m_MatFeatures;
            cv::normalize(tmpFeatures, tmpFeatures);
            Fit = (float) cv::Mahalanobis(tmpFeatures, iMean, iCovInverse );

            if(Fit < BestFit)
            {
                nBestOffsetX = x;
                nBestOffsetY = y;
                dist = sqrt( pow( (double)(nBestOffsetX - xx), 2.0) + pow( (double)(nBestOffsetY - yy), 2.0) );
                BestFit = Fit;
            }
            else if( Fit == BestFit )    // pick up one closer to (0,0)
            {
                if( sqrt(pow( (double)x, 2.0 ) + pow( (double)y, 2.0 )) 
                    < sqrt(pow( (double)nBestOffsetX, 2.0 ) + pow( (double)nBestOffsetY, 2.0 )) )
                {
                    nBestOffsetX = x;
                    nBestOffsetY = y;
                    dist = sqrt( pow( (double)(nBestOffsetX - xx), 2.0) + pow( (double)(nBestOffsetY - yy), 2.0) );
                }
            }
        }
    }

    ioLocation.x += nBestOffsetX;
    ioLocation.y += nBestOffsetY;

    return dist;
}


int VO_FittingASMLTCs::UpdateShape(const VO_ASMLTCs* asmmodel,
                                   const Mat& iImg,
                                   VO_Shape& ioShape,
                                   const vector<VO_Shape2DInfo>& iShapeInfo,
                                   const vector< Mat_<float> >& iMeans,
                                   const vector< Mat_<float> >& iCovInverses,
                                   unsigned int offSetTolerance)
{
    int nGoodLandmarks = 0;
    float dist = 0.0f;
    unsigned int NbOfPoints     = ioShape.GetNbOfPoints();
    unsigned int NbOfShapeDim   = ioShape.GetNbOfDim();
    Point2f pt;


    // Take care of the  image patch first.
    for (unsigned int i = 0; i < NbOfPoints; i++)
    {
        dist = VO_FittingASMLTCs::VO_FindBestMatchingLTC(   asmmodel,
                                                            iImg,
                                                            ioShape,
                                                            iShapeInfo,
                                                            iMeans[i],
                                                            iCovInverses[i],
                                                            i,
                                                            offSetTolerance,
                                                            pt,
                                                            VO_Features::DIRECT);

        // set OutShape(iPoint) to best offset from current position
        // one dimensional profile: must move point along the whisker
        ioShape.SetA2DPoint(pt, i);

        //if (abs(nBestOffset[0]) <= offSetTolerance/2)
        if (fabs(dist) <= 1.41421357f)
            nGoodLandmarks++;
    }

    return nGoodLandmarks;
}


//-----------------------------------------------------------------------------
// Pyramid ASM Fitting Algorithm at certain level
//
// An iterative approach to improving the fit of the instance, this->m_VOShape, to an image
// proceeds as follows:
// 1. Examine a region of the image around each point Point-ith to find the best
// nearby match for the point Point'-ith.   ---> UpdateShape
// 2. Update the parameters(s, sigma, tx, ty; b) to best fit the new found points
// X.       ---> ConformShapeToModel
// 3. Repeat until convergence.
//
// For more details, ref to [Cootes & Taylor, 2004].
//-----------------------------------------------------------------------------
/**
 * @author      JIA Pei
 * @version     2010-05-20
 * @brief       Find the best offset for one point
 * @param       ioShape     Input and output - the input and output shape
 * @param       iImg        Input - image to be fitted
 * @param       oImages     Output - the output images
 * @param       iLev        Input - current pyramid level
 * @param       PClose      Input - percentage of converged points. Say, 0.9 means if 90% of the points
 *                                  are judged as converged, the iteration of this pyramid can stop
 * @param       epoch       Input - the maximum iteration times
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
void VO_FittingASMLTCs::PyramidFit( VO_Shape& ioShape,
                                    const Mat& iImg,
                                    vector<Mat>& oImages,
                                    unsigned int iLev,
                                    float PClose,
                                    unsigned int epoch,
                                    bool record)
{
    VO_Shape tempShape = ioShape;
    int nGoodLandmarks = 0;
    float PyrScale = pow(2.0f, (float) (iLev) );

    const int nQualifyingDisplacements = (int)(this->m_VOASMLTC->m_iNbOfPoints * PClose);

    for(unsigned int iter = 0; iter < epoch; iter++)
    {
        // estimate the best this->m_VOEstimatedShape by profile matching the landmarks in this->m_VOShape
        nGoodLandmarks = VO_FittingASMLTCs::UpdateShape(this->m_VOASMLTC,
                                                        iImg,
                                                        tempShape,
                                                        this->m_vShape2DInfo,
                                                        this->m_VOASMLTC->m_vvLTCMeans[iLev],
                                                        this->m_VOASMLTC->m_vvCVMInverseOfLTCCov[iLev],
                                                        3);

        // conform ioShape to the shape model
        this->m_VOASMLTC->VO_CalcAllParams4AnyShapeWithConstrain(   tempShape,
                                                                    this->m_MatModelAlignedShapeParam,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity );
        tempShape.ConstrainShapeInImage(iImg);

if(record)
{
    // If we get better fitting result, record this fitting result
    Mat temp3 = Mat(this->m_ImageInput.size(), this->m_ImageInput.type(), this->m_ImageInput.channels());
    Mat temp3ROI = temp3(Range (0, (int)(this->m_ImageInput.rows/PyrScale) ), Range (0, (int)(this->m_ImageInput.cols/PyrScale) ) );
    cv::resize(this->m_ImageInput, temp3ROI, temp3ROI.size());
    VO_Fitting2DSM::VO_DrawMesh(tempShape / this->m_fScale2, this->m_VOASMLTC, temp3);
    oImages.push_back(temp3);
}

        if(nGoodLandmarks > nQualifyingDisplacements)
            break;
    }

    ioShape=tempShape;

}


//-----------------------------------------------------------------------------
// Pyramid ASM Fitting Algorithm at certain level
//
// An iterative approach to improving the fit of the instance, this->m_VOShape, to an image
// proceeds as follows:
// 1. Examine a region of the image around each point Point-ith to find the best
// nearby match for the point Point'-ith.   ---> UpdateShape
// 2. Update the parameters(s, sigma, tx, ty; b) to best fit the new found points
// X.       ---> ConformShapeToModel
// 3. Repeat until convergence.
//
// For more details, ref to [Cootes & Taylor, 2004].
//-----------------------------------------------------------------------------
void VO_FittingASMLTCs::PyramidFit(VO_Shape& ioShape,
                                   const Mat& iImg,
                                   unsigned int iLev,
                                   float PClose,
                                   unsigned int epoch)
{
    VO_Shape tempShape = ioShape;
    int nGoodLandmarks = 0;
    float PyrScale = pow(2.0f, (float) (iLev-1.0f) );

    const int nQualifyingDisplacements = (int)(this->m_VOASMLTC->m_iNbOfPoints * PClose);

    for(unsigned int iter = 0; iter < epoch; iter++)
    {
        // estimate the best this->m_VOEstimatedShape by profile matching the landmarks in this->m_VOShape
        nGoodLandmarks = this->UpdateShape( this->m_VOASMLTC,
                                            iImg,
                                            ioShape,
                                            this->m_vShape2DInfo,
                                            this->m_VOASMLTC->m_vvLTCMeans[iLev],
                                            this->m_VOASMLTC->m_vvCVMInverseOfLTCCov[iLev],
                                            3);

        // conform ioShape to the shape model
        this->m_VOASMLTC->VO_CalcAllParams4AnyShapeWithConstrain(   tempShape,
                                                                    this->m_MatModelAlignedShapeParam,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity );
        tempShape.ConstrainShapeInImage(iImg);

        // the fitting result is good enough to stop the iteration
        if(nGoodLandmarks > nQualifyingDisplacements)
            break;
    }

    ioShape=this->m_VOEstimatedShape;

}

