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

#include "VO_FittingASMNDProfiles.h"


/** Constructor */
VO_FittingASMNDProfiles::VO_FittingASMNDProfiles()
{
    this->init();
}


/** Destructor */
VO_FittingASMNDProfiles::~VO_FittingASMNDProfiles()
{
    if(this->m_VOASMNDProfile)  delete this->m_VOASMNDProfile; this->m_VOASMNDProfile = NULL;
}


/** Initialization */
void VO_FittingASMNDProfiles::init()
{
    VO_Fitting2DSM::init();
    this->m_VOASMNDProfile      = new VO_ASMNDProfiles();
    this->m_iFittingMethod      = VO_AXM::ASM_PROFILEND;
}


/**
 * @author     JIA Pei
 * @version    2010-05-18
 * @brief      Load all AAM data from a specified folder for later fitting, to member variable m_VOASMNDProfile
 * @param      fd         Input - the folder that AAM to be loaded from
*/
void VO_FittingASMNDProfiles::VO_LoadParameters4Fitting(const std::string& fd)
{
    this->m_VOASMNDProfile->VO_LoadParameters4Fitting(fd);

    // VO_Fitting2DSM
    this->m_VOTemplateAlignedShape          = this->m_VOASMNDProfile->m_VOAlignedMeanShape;
    //    this->m_VOTemplateNormalizedTexture   = this->m_VOASMNDProfile->m_VONormalizedMeanTexture;
    this->m_vTriangle2D                     = this->m_VOASMNDProfile->m_vNormalizedTriangle2D;
    this->m_vShape2DInfo                    = this->m_VOASMNDProfile->m_vShape2DInfo;
    this->m_FaceParts                       = this->m_VOASMNDProfile->m_FaceParts;
    //    this->m_vPointWarpInfo                = this->m_VOASMNDProfile->m_vNormalizedPointWarpInfo;
}


/**
 * @author      JIA Pei, YAO Wei
 * @version     2010-05-20
 * @brief       Additive ASM ND Profiles Fitting, for static images, so that we record the whole fitting process
 * @param       iImg            Input - image to be fitted
 * @param       oImages         Output - the fitting process
 * @param       dim             Input - profile dimension, 1, 2, 4 or 8
 * @param       epoch           Input - the iteration epoch
 * @param       pyramidlevel    Input - pyramid level, 1, 2, 3 or 4 at most
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
float VO_FittingASMNDProfiles::VO_ASMNDProfileFitting(  const cv::Mat& iImg,
                                                        std::vector<cv::Mat>& oImages,
                                                        unsigned int epoch,
                                                        unsigned int pyramidlevel,
                                                        unsigned int dim,
                                                        bool record)
{
double t = (double)cv::getTickCount();

    this->m_iNbOfPyramidLevels = pyramidlevel;
    this->SetProcessingImage(iImg, this->m_VOASMNDProfile);
    this->m_iIteration = 0;

if(record)
{
    cv::Mat temp = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOASMNDProfile, temp);
    oImages.push_back(temp);
}

    // Get m_MatModelAlignedShapeParam and m_fScale, m_vRotateAngles, m_MatCenterOfGravity
    this->m_VOASMNDProfile->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                    this->m_MatModelAlignedShapeParam,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity);
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);
if(record)
{
    cv::Mat temp1 = iImg.clone();
    VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape, this->m_VOASMNDProfile, temp1);
    oImages.push_back(temp1);
}

    // Explained by YAO Wei, 2008-2-9.
    // Scale this->m_VOFittingShape, so face width is a constant StdFaceWidth.
    //this->m_fScale2 = this->m_VOASMNDProfile->m_VOReferenceShape.GetWidth() / this->m_VOFittingShape.GetWidth();
    this->m_fScale2 = this->m_VOASMNDProfile->m_VOReferenceShape.GetCentralizedShapeSize() / this->m_VOFittingShape.GetCentralizedShapeSize();
    this->m_VOFittingShape *= this->m_fScale2;

    int w = (int)(iImg.cols*this->m_fScale2);
    int h = (int)(iImg.rows*this->m_fScale2);
    cv::Mat SearchImage = cv::Mat(cv::Size( w, h ), this->m_ImageProcessing.type(), this->m_ImageProcessing.channels() );

    float PyrScale = pow(2.0f, (float) (this->m_iNbOfPyramidLevels-1.0f) );
    this->m_VOFittingShape /= PyrScale;

    const int nQualifyingDisplacements = (int)(this->m_VOASMNDProfile->m_iNbOfPoints * VO_Fitting2DSM::pClose);

    // for each level in the image pyramid
    for (int iLev = this->m_iNbOfPyramidLevels-1; iLev >= 0; iLev--)
    {
        // Set image roi, instead of cvCreateImage a new image to speed up
        cv::Mat siROI = SearchImage(cv::Rect(0, 0, (int)(w/PyrScale), (int)(h/PyrScale) ) );
        cv::resize(this->m_ImageProcessing, siROI, siROI.size());

if(record)
{
        cv::Mat temp2 = cv::Mat(iImg.size(), iImg.type(), iImg.channels());
        cv::Mat temp2ROI = temp2(cv::Range (0, (int)(iImg.rows/PyrScale) ), cv::Range (0, (int)(iImg.cols/PyrScale) ) );
        cv::resize(iImg, temp2ROI, temp2ROI.size() );
        oImages.push_back(temp2);
        VO_Fitting2DSM::VO_DrawMesh(this->m_VOFittingShape / this->m_fScale2, this->m_VOASMNDProfile, temp2);
}

        this->m_VOEstimatedShape = this->m_VOFittingShape;
        this->PyramidFit(   this->m_VOEstimatedShape,
                            SearchImage,
                            oImages,
                            iLev,
                            VO_Fitting2DSM::pClose,
                            epoch,
                            dim,
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

t = ((double)cv::getTickCount() -  t )/  (cv::getTickFrequency()*1000.);
printf("MRASM fitting time cost: %.2f millisec\n", t);

    return t;
}


/**
 * @author      JIA Pei, YAO Wei
 * @version     2010-05-20
 * @brief       Additive ASM ND Profiles Fitting, for dynamic image sequence
 * @param       iImg            Input - image to be fitted
 * @param       ioShape         Input and output - the shape
 * @param       oImg            Output - the fitted image
 * @param       dim             Input - profile dimension, 1, 2, 4 or 8
 * @param       epoch           Input - the iteration epoch
 * @param       pyramidlevel    Input - pyramid level, 1, 2, 3 or 4 at most
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
float VO_FittingASMNDProfiles::VO_ASMNDProfileFitting(  const cv::Mat& iImg,
                                                        VO_Shape& ioShape,
                                                        cv::Mat& oImg,
                                                        unsigned int epoch,
                                                        unsigned int pyramidlevel,
                                                        unsigned int dim)
{
    this->m_VOFittingShape.clone(ioShape);
double t = (double)cv::getTickCount();

    this->m_iNbOfPyramidLevels = pyramidlevel;
    this->SetProcessingImage(iImg, this->m_VOASMNDProfile);
    this->m_iIteration = 0;

    // Get m_MatModelAlignedShapeParam and m_fScale, m_vRotateAngles, m_MatCenterOfGravity
    this->m_VOASMNDProfile->VO_CalcAllParams4AnyShapeWithConstrain( this->m_VOFittingShape,
                                                                    this->m_MatModelAlignedShapeParam,
                                                                    this->m_fScale,
                                                                    this->m_vRotateAngles,
                                                                    this->m_MatCenterOfGravity);
    this->m_VOFittingShape.ConstrainShapeInImage(this->m_ImageProcessing);

    // Explained by YAO Wei, 2008-2-9.
    // Scale this->m_VOFittingShape, so face width is a constant StdFaceWidth.
    //this->m_fScale2 = this->m_VOASMNDProfile->m_VOReferenceShape.GetWidth() / this->m_VOFittingShape.GetWidth();
    this->m_fScale2 = this->m_VOASMNDProfile->m_VOReferenceShape.GetCentralizedShapeSize() / this->m_VOFittingShape.GetCentralizedShapeSize();
    this->m_VOFittingShape *= this->m_fScale2;

    int w = (int)(iImg.cols*this->m_fScale2);
    int h = (int)(iImg.rows*this->m_fScale2);
    cv::Mat SearchImage = cv::Mat(cv::Size( w, h ), this->m_ImageProcessing.type(), this->m_ImageProcessing.channels() );

    float PyrScale = pow(2.0f, (float) (this->m_iNbOfPyramidLevels-1.0f) );
    this->m_VOFittingShape /= PyrScale;

    const int nQualifyingDisplacements = (int)(this->m_VOASMNDProfile->m_iNbOfPoints * VO_Fitting2DSM::pClose);

    // for each level in the image pyramid
    for (int iLev = this->m_iNbOfPyramidLevels-1; iLev >= 0; iLev--)
    {
        // Set image roi, instead of cvCreateImage a new image to speed up
        cv::Mat siROI = SearchImage(cv::Rect(0, 0, (int)(w/PyrScale), (int)(h/PyrScale) ) );
        cv::resize(this->m_ImageProcessing, siROI, siROI.size());

        this->m_VOEstimatedShape = this->m_VOFittingShape;
        this->PyramidFit(   this->m_VOEstimatedShape,
                            SearchImage,
                            iLev,
                            VO_Fitting2DSM::pClose,
                            epoch,
                            dim);
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
    VO_Fitting2DSM::VO_DrawMesh(ioShape, this->m_VOASMNDProfile, oImg);

t = ((double)cv::getTickCount() -  t )/  (cv::getTickFrequency()*1000.);
printf("MRASM fitting time cost: %.2f millisec\n", t);
this->m_fFittingTime = t;

    return t;
}


/**
 * @author      JIA Pei, YAO Wei
 * @version     2010-05-20
 * @brief       Find the best offset for one point
 * @param       iImg            Input - image to be fitted
 * @param       iShape          Input - the input shape
 * @param       iShapeInfo      Input - the shape information
 * @param       iMean           Input - mean profile
 * @param       iCovInverse     Input - covariance inverse
 * @param       ptIdx           Input - point index
 * @param       ProfileLength   Input - number of profiles per pixel, number of pixel for a single profile * dim of profiles
 * @param       offSetTolerance Input - offset tolerance, which is used to determine whether this point is converged or not
 * @param       DeltaX          Output - update in X direction
 * @param       DeltaY          Output - update in Y direction
 * @param       dim             Input - profile dim
 * @return      int             return the offset of the best fit from the profile center
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
int VO_FittingASMNDProfiles::VO_FindBestMatchingProfile1D(  const cv::Mat& iImg,
                                                            const cv::Point2f& ThisPoint,
                                                            const cv::Mat_<float>& iMean,
                                                            const cv::Mat_<float>& iCovInverse,
                                                            unsigned int ProfileLength,
                                                            unsigned int offSetTolerance,
                                                            float& DeltaX,
                                                            float& DeltaY)
{
    float BestFit = FLT_MAX;
    int nBestOffset = 0;    // might be + or -
    float Fit;

    VO_Profile tempProfile;
    // Do one dim a time.
    VO_Profile::VO_Get1DProfileInMat4OneLandmark (  iImg,
                                                    ThisPoint,
                                                    tempProfile,
                                                    DeltaX,
                                                    DeltaY,
                                                    ProfileLength+2*offSetTolerance);
    VO_Profile tempSubProfile;

    // Find the best in just one direction
    for (int i = -(int)offSetTolerance; i <= (int)offSetTolerance; ++i)
    {
        tempSubProfile = tempProfile.GetSubProfile(i + offSetTolerance, ProfileLength, 0);
        tempSubProfile.Normalize();

        Fit = (float) cv::Mahalanobis(tempSubProfile.m_MatProf, iMean, iCovInverse );

        // Explained by YAO Wei, 2008-2-9.
        // Test for a new best fit. We test using "<=" instead of just "<"
        // so if there is an exact match then ixBest=0 i.e. no change.
//                if((i <= 0 ) ? Fit <= BestFit:  Fit < BestFit)
        if(Fit < BestFit)
        {
            nBestOffset = i;
            BestFit = Fit;
        }
    }

    // Find the additional best in the 2nd direction

    return nBestOffset;
}


/**
 * @author      YAO Wei, JIA Pei
 * @version     2010-05-20
 * @brief       Find the best offset for one point
 * @param       asmmodel        Input - the ASM model
 * @param       iImg            Input - image to be fitted
 * @param       ioShape         Input and output - the input and output shape
 * @param       iShapeInfo      Input - the shape information
 * @param       iMean           Input - mean profile
 * @param       iCovInverse     Input - covariance inverse
 * @param       Lev             Input - current pyramid level
 * @param       offSetTolerance Input - offset tolerance, which is used to determine whether this point is convergede or not
 * @param       profdim         Input - specify the dimension that is going to be used when updating shape.
 *                              Sometimes, the trained data is of 4D profiles, but the user may only use 1D to test.
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
int VO_FittingASMNDProfiles::UpdateShape(   const VO_ASMNDProfiles* asmmodel,
                                            const cv::Mat& iImg,
                                            VO_Shape& ioShape,
                                            const std::vector<VO_Shape2DInfo>& iShapeInfo,
                                            const std::vector< VO_Profile >& iMean,
                                            const std::vector< std::vector< cv::Mat_<float> > >& iCovInverse,
                                            unsigned int offSetTolerance,
                                            unsigned int profdim)
{
    int nGoodLandmarks = 0;
    std::vector<int> nBestOffset(profdim, 0);
    unsigned int NbOfPoints     = ioShape.GetNbOfPoints();
    unsigned int NbOfShapeDim   = ioShape.GetNbOfDim();
    unsigned int ProfileLength    = iMean[0].GetProfileLength();
    //std::vector<float> dists(NbOfPoints, 0.0f);
    cv::Point2f pt;

    // Take care of the 1st direction first.
    for (unsigned int i = 0; i < NbOfPoints; i++)
    {
        /////////////////////////////////////////////////////////////////////////////
        ///Calculate profile norm direction//////////////////////////////////////////
        /** Here, this is not compatible with 3D */
        cv::Point2f PrevPoint = ioShape.GetA2DPoint ( iShapeInfo[i].GetFrom() );
        cv::Point2f ThisPoint = ioShape.GetA2DPoint ( i );
        cv::Point2f NextPoint = ioShape.GetA2DPoint ( iShapeInfo[i].GetTo() );

        float deltaX, deltaY;
        float normX, normY;
        float sqrtsum;
        float bestXOffset, bestYOffset;

        // left side (connected from side)
        deltaX = ThisPoint.x - PrevPoint.x;
        deltaY = ThisPoint.y - PrevPoint.y;
        sqrtsum = sqrt ( deltaX*deltaX + deltaY*deltaY );
        if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
        deltaX /= sqrtsum; deltaY /= sqrtsum;         // Normalize
        // Firstly, normX normY record left side norm.
        normX = -deltaY;
        normY = deltaX;

        // right side (connected to side)
        deltaX = NextPoint.x - ThisPoint.x;
        deltaY = NextPoint.y - ThisPoint.y;
        sqrtsum = sqrt ( deltaX*deltaX + deltaY*deltaY );
        if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
        deltaX /= sqrtsum; deltaY /= sqrtsum;         // Normalize
        // Secondly, normX normY will average both left side and right side norm.
        normX += -deltaY;
        normY += deltaX;

        // Average left right side
        sqrtsum = sqrt ( normX*normX + normY*normY );
        if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
        normX /= sqrtsum;
        normY /= sqrtsum;                             // Final Normalize
        /////////////////////////////////////////////////////////////////////////////

        nBestOffset[0] = VO_FittingASMNDProfiles::VO_FindBestMatchingProfile1D( iImg,
                                                                                ThisPoint,
                                                                                iMean[i].Get1DimProfile(0),
                                                                                iCovInverse[i][0],
                                                                                ProfileLength,
                                                                                offSetTolerance,
                                                                                normX,
                                                                                normY);

        // set OutShape(iPoint) to best offset from current position
        // one dimensional profile: must move point along the whisker
        bestXOffset = nBestOffset[0] * normX;
        bestYOffset = nBestOffset[0] * normY;
        pt.x = ThisPoint.x + bestXOffset;
        pt.y = ThisPoint.y + bestYOffset;
        ioShape.SetA2DPoint(pt, i);
        //dists[i] = sqrt( pow( (double)bestXOffset, 2.0) + pow( (double)bestYOffset, 2.0) );

        //if (abs(nBestOffset[0]) <= offSetTolerance/2)
        if(profdim == 1)
        {
            if (abs(nBestOffset[0]) <= 1)
                nGoodLandmarks++;
        }
    }
    
    // Originality from JIA Pei!! Now, take care of the 2nd direction now.
    if(profdim == 2)
    {
        for (unsigned int i = 0; i < NbOfPoints; i++)
        {
            /////////////////////////////////////////////////////////////////////////////
            ///Calculate profile norm direction//////////////////////////////////////////
            /** Here, this is not compatible with 3D */
            cv::Point2f PrevPoint = ioShape.GetA2DPoint ( iShapeInfo[i].GetFrom() );
            cv::Point2f ThisPoint = ioShape.GetA2DPoint ( i );
            cv::Point2f NextPoint = ioShape.GetA2DPoint ( iShapeInfo[i].GetTo() );

            float deltaX, deltaY;
            float normX, normY;
            float tangentX, tangentY;
            float sqrtsum;
            float bestXOffset, bestYOffset;

            // left side (connected from side)
            deltaX = ThisPoint.x - PrevPoint.x;
            deltaY = ThisPoint.y - PrevPoint.y;
            sqrtsum = sqrt ( deltaX*deltaX + deltaY*deltaY );
            if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
            deltaX /= sqrtsum; deltaY /= sqrtsum;         // Normalize
            // Firstly, normX normY record left side norm.
            normX = -deltaY;
            normY = deltaX;

            // right side (connected to side)
            deltaX = NextPoint.x - ThisPoint.x;
            deltaY = NextPoint.y - ThisPoint.y;
            sqrtsum = sqrt ( deltaX*deltaX + deltaY*deltaY );
            if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
            deltaX /= sqrtsum; deltaY /= sqrtsum;         // Normalize
            // Secondly, normX normY will average both left side and right side norm.
            normX += -deltaY;
            normY += deltaX;

            // Average left right side
            sqrtsum = sqrt ( normX*normX + normY*normY );
            if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
            normX /= sqrtsum;
            normY /= sqrtsum;                             // Final Normalize
            tangentX     =     -normY;
            tangentY    =    normX;                        // Final tangent
            /////////////////////////////////////////////////////////////////////////////

            nBestOffset[1] = VO_FittingASMNDProfiles::VO_FindBestMatchingProfile1D( iImg,
                                                                                    ThisPoint,
                                                                                    iMean[i].Get1DimProfile(1),
                                                                                    iCovInverse[i][1],
                                                                                    ProfileLength,
                                                                                    1,    // in tangent direction, offset = 1
                                                                                    tangentX,
                                                                                    tangentY);

            // set OutShape(iPoint) to best offset from current position
            // one dimensional profile: must move point along the whisker
            bestXOffset = nBestOffset[1] * tangentX;
            bestYOffset = nBestOffset[1] * tangentY;
            pt.x = ThisPoint.x + bestXOffset;
            pt.y = ThisPoint.y + bestYOffset;
            ioShape.SetA2DPoint(pt, i);
            //dists[i] += sqrt( pow((double)bestXOffset, 2.0) + pow((double)bestYOffset, 2.0) );

            //if (abs(nBestOffset) <= offSetTolerance/2)
            if (abs(nBestOffset[0]) <= 1 && abs(nBestOffset[1]) <= 1)
                nGoodLandmarks++;
        }
    }

    return nGoodLandmarks;
}


//-----------------------------------------------------------------------------
// Pyramid ASM Fitting Algorithm at certain level
//
// An iterative approach to improving the fit of the instance, this->m_VOFittingShape, to an image
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
 * @author      YAO Wei, JIA Pei
 * @version     2010-05-20
 * @brief       Find the best offset for one point
 * @param       ioShape     Input and output - the input and output shape
 * @param       iImg        Input - image to be fitted
 * @param       oImages     Output - the output images
 * @param       iLev        Input - current pyramid level
 * @param       PClose      Input - percentage of converged points. Say, 0.9 means if 90% of the points
 *                                  are judged as converged, the iteration of this pyramid can stop
 * @param       epoch       Input - the maximum iteration times
 * @param       profdim     Input - dimension used during fitting. For example, the trained data could be 4D, but the user may only use 1D
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
void VO_FittingASMNDProfiles::PyramidFit(   VO_Shape& ioShape,
                                            const cv::Mat& iImg,
                                            std::vector<cv::Mat>& oImages,
                                            unsigned int iLev,
                                            float PClose,
                                            unsigned int epoch,
                                            unsigned int profdim,
                                            bool record)
{
    VO_Shape tempShape = ioShape;
    int nGoodLandmarks = 0;
    float PyrScale = pow(2.0f, (float) (iLev) );

    const int nQualifyingDisplacements = (int)(this->m_VOASMNDProfile->m_iNbOfPoints * PClose);

    for(unsigned int iter = 0; iter < epoch; iter++)
    {
        this->m_iIteration++;
        // estimate the best ioShape by profile matching the landmarks in this->m_VOFittingShape
        nGoodLandmarks = VO_FittingASMNDProfiles::UpdateShape(  this->m_VOASMNDProfile,
                                                                iImg,
                                                                tempShape,
                                                                this->m_vShape2DInfo,
                                                                this->m_VOASMNDProfile->m_vvMeanNormalizedProfile[iLev],
                                                                this->m_VOASMNDProfile->m_vvvCVMInverseOfSg[iLev],
                                                                3,
                                                                profdim);

        // conform ioShape to the shape model
        this->m_VOASMNDProfile->VO_CalcAllParams4AnyShapeWithConstrain( tempShape,
                                                                        this->m_MatModelAlignedShapeParam,
                                                                        this->m_fScale,
                                                                        this->m_vRotateAngles,
                                                                        this->m_MatCenterOfGravity );
        tempShape.ConstrainShapeInImage(iImg);

if(record)
{
        // If we get better fitting result, record this fitting result
        cv::Mat temp3 = cv::Mat(this->m_ImageInput.size(), this->m_ImageInput.type(), this->m_ImageInput.channels());
        cv::Mat temp3ROI = temp3(cv::Range (0, (int)(this->m_ImageInput.rows/PyrScale) ), cv::Range (0, (int)(this->m_ImageInput.cols/PyrScale) ) );
        cv::resize(this->m_ImageInput, temp3ROI, temp3ROI.size());
        VO_Fitting2DSM::VO_DrawMesh(tempShape / this->m_fScale2, this->m_VOASMNDProfile, temp3);
        oImages.push_back(temp3);
}

        // the fitting result is good enough to stop the iteration
        if(nGoodLandmarks > nQualifyingDisplacements)
            break;
    }
    ioShape = tempShape;
}


/**
 * @author      YAO Wei, JIA Pei
 * @version     2010-05-20
 * @brief       Find the best offset for one point
 * @param       iImg        Input - image to be fitted
 * @param       ioShape     Input and output - the input and output shape
 * @param       iShapeInfo  Input - the shape information
 * @param       iLev        Input - current pyramid level
 * @param       PClose      Input - percentage of converged points. Say, 0.9 means if 90% of the points
 *                                  are judged as converged, the iteration of this pyramid can stop
 * @param       epoch       Input - the maximum iteration times
 * @param       profdim     Input - dimension used during fitting. For example, the trained data could be 4D, but the user may only use 1D
 * @note        Refer to "AAM Revisited, page 34, figure 13", particularly, those steps.
*/
void VO_FittingASMNDProfiles::PyramidFit(   VO_Shape& ioShape,
                                            const cv::Mat& iImg,
                                            unsigned int iLev,
                                            float PClose,
                                            unsigned int epoch,
                                            unsigned int profdim)
{
    VO_Shape tempShape = ioShape;
    int nGoodLandmarks = 0;
    float PyrScale = pow(2.0f, (float) (iLev-1.0f) );

    const int nQualifyingDisplacements = (int)(this->m_VOASMNDProfile->m_iNbOfPoints * PClose);

    for(unsigned int iter = 0; iter < epoch; iter++)
    {
        this->m_iIteration++;
        // estimate the best ioShape by profile matching the landmarks in this->m_VOFittingShape
        nGoodLandmarks = VO_FittingASMNDProfiles::UpdateShape(  this->m_VOASMNDProfile,
                                                                iImg,
                                                                tempShape,
                                                                this->m_vShape2DInfo,
                                                                this->m_VOASMNDProfile->m_vvMeanNormalizedProfile[iLev],
                                                                this->m_VOASMNDProfile->m_vvvCVMInverseOfSg[iLev],
                                                                3,
                                                                profdim);

        // conform ioShape to the shape model
        this->m_VOASMNDProfile->VO_CalcAllParams4AnyShapeWithConstrain( tempShape,
                                                                        this->m_MatModelAlignedShapeParam,
                                                                        this->m_fScale,
                                                                        this->m_vRotateAngles,
                                                                        this->m_MatCenterOfGravity );
        tempShape.ConstrainShapeInImage(iImg);

        // the fitting result is good enough to stop the iteration
        if(nGoodLandmarks > nQualifyingDisplacements)
            break;
    }
    ioShape = tempShape;
}

