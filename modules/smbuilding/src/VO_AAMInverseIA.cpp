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
#include <sstream>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>

#include "VO_AAMInverseIA.h"
#include "VO_CVCommon.h"


VO_AAMInverseIA::VO_AAMInverseIA()
{
    this->init();
}

/** Initialization */
void VO_AAMInverseIA::init()
{
    this->m_iMethod = VO_AXM::AAM_IAIA;        // AAM_CMUICIA
}


VO_AAMInverseIA::~VO_AAMInverseIA()
{

}


/**
 * @author      JIA Pei
 * @version     2010-04-03
 * @brief       Calculate Gradients for template face, both in X and Y directions
 * @return      void
*/
void VO_AAMInverseIA::VO_CalcTemplateFaceGradients ()
{
    std::vector< std::vector<int> >     tblr;
    tblr.resize(this->m_iNbOfPixels);

    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)
    {
        tblr[i].resize(4);
        for (unsigned int j = 0; j < 4; j++)
        {
            tblr[i][j] = -1;
        }
    }


    float xPos, yPos;
    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)     // 30132
    {
        // x refer to column; while y refer to row.
        xPos        = this->m_vTemplatePointWarpInfo[i].GetPosition().x;
        yPos        = this->m_vTemplatePointWarpInfo[i].GetPosition().y;

        // Start searching for the top bottom left right point index in this->m_vNormalizedPointWarpInfo

        for (unsigned int j = 0; j < this->m_iNbOfPixels; j++)     // 30132
        {
            // left
            if ( fabs( this->m_vTemplatePointWarpInfo[j].GetPosition().x - (xPos - 1.) ) < FLT_EPSILON &&
                fabs( this->m_vTemplatePointWarpInfo[j].GetPosition().y - yPos ) < FLT_EPSILON  )
            {
                tblr[i][0] = j;
            }

            // right
            if ( fabs(this->m_vTemplatePointWarpInfo[j].GetPosition().x - (xPos + 1.) ) < FLT_EPSILON &&
                fabs(this->m_vTemplatePointWarpInfo[j].GetPosition().y - yPos ) < FLT_EPSILON )
            {
                tblr[i][1] = j;
            }

            // top
            if ( fabs(this->m_vTemplatePointWarpInfo[j].GetPosition().x - xPos ) < FLT_EPSILON &&
                fabs(this->m_vTemplatePointWarpInfo[j].GetPosition().y - (yPos - 1.) ) < FLT_EPSILON )
            {
                tblr[i][2] = j;
            }

            // bottom
            if ( fabs(this->m_vTemplatePointWarpInfo[j].GetPosition().x - xPos ) < FLT_EPSILON &&
                fabs(this->m_vTemplatePointWarpInfo[j].GetPosition().y - (yPos + 1.) ) < FLT_EPSILON )
            {
                tblr[i][3] = j;
            }
        }
    }

    std::vector< std::vector <float> > tempGradients, tempNormalizedGradients;
    tempGradients.resize(this->m_iNbOfChannels);
    tempNormalizedGradients.resize(this->m_iNbOfChannels);
    for (unsigned int m = 0; m < this->m_iNbOfChannels; m++)
    {
        tempGradients[m].resize(2);
        tempNormalizedGradients[m].resize(2);
    }

    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)     // 30132
    {
        for (unsigned int m = 0; m < this->m_iNbOfChannels; m++)
        {
            tempGradients[m][0] = 0.0f;
            tempGradients[m][1] = 0.0f;
            tempNormalizedGradients[m][0] = 0.0f;
            tempNormalizedGradients[m][1] = 0.0f;
        }
        //////////////////////////////////////////////////////////////////////////

        // noted by JIA Pei, it is obvious that for the current point this->m_vNormalizedPointWarpInfo[i]
        // it can't be both at the top and at the bottom; also, it can't be both at the left and the right
        // So, tblr[0] and tblr[1] shouldn't be the same point; tblr[2] and tblr[3] shouldn't be the same point
        // let's simply add an assert here
        //assert(tblr[i][0] ^ tblr[i][1]);
        //assert(tblr[i][2] ^ tblr[i][3]);
        //////////////////////////////////////////////////////////////////////////
        // Noted by JIA Pei, we always assume the face is lighter than the background
        // Calculate the gradient
        // Have to allocate the space first, this should be changed in future

        // Explained by JIA Pei... At the very beginning, set all the gradients that can be calculated first.
        // 2.0 / this->m_fAverageShapeSize very important here. Can't use 2.0 directly!!!
        // neither the leftmost nor the rightmost
        if ( (tblr[i][0] != -1) && (tblr[i][1] != -1) )
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                tempGradients[k][0] = (this->m_VOReferenceTexture.GetATexture(k, tblr[i][1]) -
                    this->m_VOReferenceTexture.GetATexture(k, tblr[i][0]) )/2.0f;
                tempNormalizedGradients[k][0] =
                    ( this->m_VONormalizedMeanTexture.GetATexture(k, tblr[i][1]) -
                    this->m_VONormalizedMeanTexture.GetATexture(k, tblr[i][0]) ) /
                    (this->m_vNormalizedPointWarpInfo[tblr[i][1]].GetPosition().x -
                    this->m_vNormalizedPointWarpInfo[tblr[i][0]].GetPosition().x );
            }
        }

        if ( (tblr[i][2] != -1) && (tblr[i][3] != -1) )
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                tempGradients[k][1] = (this->m_VOReferenceTexture.GetATexture(k, tblr[i][3]) -
                    this->m_VOReferenceTexture.GetATexture(k, tblr[i][2]) )/2.0f;
                tempNormalizedGradients[k][1] =
                    ( this->m_VONormalizedMeanTexture.GetATexture(k, tblr[i][3]) -
                    this->m_VONormalizedMeanTexture.GetATexture(k, tblr[i][2]) ) /
                    (this->m_vNormalizedPointWarpInfo[tblr[i][3]].GetPosition().y -
                    this->m_vNormalizedPointWarpInfo[tblr[i][2]].GetPosition().y );
            }
        }

        this->m_vTemplatePointWarpInfo[i].SetGradients (tempGradients);
        this->m_vNormalizedPointWarpInfo[i].SetGradients (tempNormalizedGradients);
    }

    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)     // 30132
    {
        for (unsigned int m = 0; m < this->m_iNbOfChannels; m++)
        {
            tempGradients[m][0] = 0.0f;
            tempGradients[m][1] = 0.0f;
            tempNormalizedGradients[m][0] = 0.0f;
            tempNormalizedGradients[m][1] = 0.0f;
        }

        // leftmost, not rightmost
        if (tblr[i][0] == -1 && tblr[i][1] != -1)
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                tempGradients[k][0] = this->m_vTemplatePointWarpInfo[ tblr[i][1] ].GetGradients()[k][0];
                tempNormalizedGradients[k][0] = this->m_vNormalizedPointWarpInfo[ tblr[i][1] ].GetGradients()[k][0];
            }
            this->m_vTemplatePointWarpInfo[i].SetGradients (tempGradients);
            this->m_vNormalizedPointWarpInfo[i].SetGradients (tempNormalizedGradients);
            tblr[i][0] = -2;
        }
        // rightmost, not leftmost
        else if (tblr[i][1] == -1 && tblr[i][0] != -1)
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                tempGradients[k][0] = this->m_vTemplatePointWarpInfo[ tblr[i][0] ].GetGradients()[k][0];
                tempNormalizedGradients[k][0] = this->m_vNormalizedPointWarpInfo[ tblr[i][0] ].GetGradients()[k][0];
            }
            this->m_vTemplatePointWarpInfo[i].SetGradients (tempGradients);
            this->m_vNormalizedPointWarpInfo[i].SetGradients (tempNormalizedGradients);
            tblr[i][1] = -2;
        }
        else  if (tblr[i][1] == -1 && tblr[i][0] == -1) // leftmost and rightmost at the same time
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                tempGradients[k][0] = 0;
                tempNormalizedGradients[k][0] = 0;
            }
            this->m_vTemplatePointWarpInfo[i].SetGradients (tempGradients);
            this->m_vNormalizedPointWarpInfo[i].SetGradients (tempNormalizedGradients);
            tblr[i][0] = -2;
            tblr[i][1] = -2;
        }

        // topmost, not bottommost
        if (tblr[i][2] == -1 && tblr[i][3] != -1)
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                tempGradients[k][1] = this->m_vTemplatePointWarpInfo[ tblr[i][3] ].GetGradients()[k][1];
                tempNormalizedGradients[k][1] = this->m_vNormalizedPointWarpInfo[ tblr[i][3] ].GetGradients()[k][1];
            }
            this->m_vTemplatePointWarpInfo[i].SetGradients (tempGradients);
            this->m_vNormalizedPointWarpInfo[i].SetGradients (tempNormalizedGradients);
            tblr[i][2] = -2;
        }
        // bottommost, not topmost
        else if (tblr[i][3] == -1 && tblr[i][2] != -1)
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                tempGradients[k][1] = this->m_vTemplatePointWarpInfo[ tblr[i][2] ].GetGradients()[k][1];
                tempNormalizedGradients[k][1] = this->m_vNormalizedPointWarpInfo[ tblr[i][2] ].GetGradients()[k][1];
            }
            this->m_vTemplatePointWarpInfo[i].SetGradients (tempGradients);
            this->m_vNormalizedPointWarpInfo[i].SetGradients (tempNormalizedGradients);
            tblr[i][3] = -2;
        }
        else if (tblr[i][3] == -1 && tblr[i][2] == -1)  // topmost and bottommost at the same time
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                tempGradients[k][1] = 0;
                tempNormalizedGradients[k][1] = 0;
            }
            this->m_vTemplatePointWarpInfo[i].SetGradients (tempGradients);
            this->m_vNormalizedPointWarpInfo[i].SetGradients (tempNormalizedGradients);
            tblr[i][2] = -2;
            tblr[i][3] = -2;
        }
    }


    cv::Mat_<float> templateGradientX     = cv::Mat_<float>::zeros( this->m_iNbOfChannels, this->m_iNbOfPixels );
    cv::Mat_<float> templateGradientY     = cv::Mat_<float>::zeros( this->m_iNbOfChannels, this->m_iNbOfPixels );
    VO_Texture templateTextureInstanceX, templateTextureInstanceY, templateTextureInstance;

    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)
    {
        for (unsigned int j = 0; j < this->m_iNbOfChannels; j++)
        {
            templateGradientX(j, i) = this->m_vTemplatePointWarpInfo[i].GetGradients()[j][0] + AVERAGEFACETEXTURE;
            templateGradientY(j, i) = this->m_vTemplatePointWarpInfo[i].GetGradients()[j][1] + AVERAGEFACETEXTURE;
        }
    }
    templateTextureInstanceX.SetTheTexture(templateGradientX);
    templateTextureInstanceY.SetTheTexture(templateGradientY);
    templateTextureInstanceX.Clamp(0.0f, 255.0f);
    templateTextureInstanceY.Clamp(0.0f, 255.0f);
    templateTextureInstance = m_VOReferenceTexture;

    VO_TextureModel::VO_PutOneTextureToTemplateShape(templateTextureInstanceX, this->m_vTemplateTriangle2D, this->m_IplImageTempFaceX);
    VO_TextureModel::VO_PutOneTextureToTemplateShape(templateTextureInstanceY, this->m_vTemplateTriangle2D, this->m_IplImageTempFaceY);
    VO_TextureModel::VO_PutOneTextureToTemplateShape(templateTextureInstance, this->m_vTemplateTriangle2D, this->m_IplImageTempFace);
    
}


/**
 * @author      JIA Pei
 * @version     2010-04-03
 * @brief       Calculate steepest descent image for template face
 * @return      void
*/
void VO_AAMInverseIA::VO_CalcSDI()
{
    // AAM Revisited equation (42)
    // calculate the m_MatSimilarityTransform (for Global Shape Normalizing Transform)
    this->m_MatSimilarityTransform = cv::Mat_<float>::zeros(4, this->m_iNbOfShapes);
    for (unsigned int i = 0; i < this->m_iNbOfPoints; i++)
    {
        this->m_MatSimilarityTransform(0, i)                         = this->m_PCAAlignedShape.mean.at<float>(0, i);
        this->m_MatSimilarityTransform(0, i+this->m_iNbOfPoints)     = this->m_PCAAlignedShape.mean.at<float>(0, i+this->m_iNbOfPoints);
        this->m_MatSimilarityTransform(1, i)                         = -this->m_PCAAlignedShape.mean.at<float>(0, i+this->m_iNbOfPoints);
        this->m_MatSimilarityTransform(1, i+this->m_iNbOfPoints)     = this->m_PCAAlignedShape.mean.at<float>(0, i);
        this->m_MatSimilarityTransform(2, i)                         = 1.0f;
        this->m_MatSimilarityTransform(2, i+this->m_iNbOfPoints)     = 0.0f;
        this->m_MatSimilarityTransform(3, i)                         = 0.0f;
        this->m_MatSimilarityTransform(3, i+this->m_iNbOfPoints)     = 1.0f;
//        this->m_MatSimilarityTransform(2, i) = 1.0f/sqrt((float)this->m_iNbOfPoints);
//        this->m_MatSimilarityTransform(3, i+this->m_iNbOfPoints) = 1.0f/sqrt((float)this->m_iNbOfPoints);
    }

    // AAM Revisited, before (50)
    // "evaluating the Jacobian at p = 0, q = 0."
    // Explained by JIA Pei. The above citation means, when calculating the Jacobian 
    // partial(N)/partial(q) and partial(W)/partial(q), p=q=0 requires 
    // m_vNormalizedPointWarpInfo, rather than m_vTemplatePointWarpInfo
    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)
    {
        this->m_vNormalizedPointWarpInfo[i].CalcJacobianOne();
        this->m_vNormalizedPointWarpInfo[i].CalcJacobianMatrix4ShapeModel(this->m_PCAAlignedShape.eigenvectors);
        this->m_vNormalizedPointWarpInfo[i].CalcJacobianMatrix4GlobalShapeNorm(this->m_MatSimilarityTransform);
        this->m_vNormalizedPointWarpInfo[i].CalcSteepestDescentImages4ShapeModel (this->m_iNbOfChannels);
        this->m_vNormalizedPointWarpInfo[i].CalcSteepestDescentImages4GlobalShapeNorm (this->m_iNbOfChannels);
    }

    this->m_MatSteepestDescentImages4ShapeModel = cv::Mat_<float>::zeros(this->m_iNbOfTextures, this->m_iNbOfShapeEigens);
    this->m_MatSteepestDescentImages4GlobalShapeNormalization = cv::Mat_<float>::zeros(this->m_iNbOfTextures, 4);

    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)
    {
        for (unsigned int j = 0; j < this->m_iNbOfShapeEigens; j++)
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                this->m_MatSteepestDescentImages4ShapeModel(this->m_iNbOfChannels * i + k, j)
                = this->m_vNormalizedPointWarpInfo[i].GetSteepestDescentImages4ShapeModel()[k][j];
            }
        }
    }

    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            for (unsigned int k = 0; k < this->m_iNbOfChannels; k++)
            {
                this->m_MatSteepestDescentImages4GlobalShapeNormalization(this->m_iNbOfChannels * i + k, j)
                = this->m_vNormalizedPointWarpInfo[i].GetSteepestDescentImages4GlobalShapeNorm()[k][j];
            }
        }
    }
}


/**
 * @author      JIA Pei
 * @version     2010-04-03
 * @brief       Calculate modified steepest descent image for template face - project out appearance variation
 * @return      void
*/
void VO_AAMInverseIA::VO_CalcModifiedSDI()
{
    //project out appearance variation i.e. modify the steepest descent image
    this->m_MatSteepestDescentImages = cv::Mat_<float>::zeros(this->m_iNbOfTextures, this->m_iNbOfShapeEigens+4);
    this->m_MatModifiedSteepestDescentImages = cv::Mat_<float>::zeros(this->m_iNbOfTextures, this->m_iNbOfShapeEigens+4);

    for (unsigned int i = 0; i < this->m_iNbOfTextures; i++)
    {
        // AAM Revisited (63)
        for (unsigned int j = 0; j < 4; j++)
        {
            this->m_MatSteepestDescentImages(i, j) = this->m_MatSteepestDescentImages4GlobalShapeNormalization(i, j);
        }
        // AAM Revisited (64)
        for (unsigned int j = 0; j < this->m_iNbOfShapeEigens; j++)
        {
            this->m_MatSteepestDescentImages(i, 4+j) = this->m_MatSteepestDescentImages4ShapeModel(i, j);
        }
    }

    cv::Mat_<float> oneCol                 = cv::Mat_<float>::zeros(this->m_iNbOfTextures, 1);
    cv::Mat_<float> spanedsum             = cv::Mat_<float>::zeros(this->m_iNbOfTextures, 1);
    cv::Mat_<float> modifiedoneCol         = cv::Mat_<float>::zeros(this->m_iNbOfTextures, 1);
    cv::Mat_<float> oneSpanRowTranspose = cv::Mat_<float>::zeros(this->m_iNbOfTextures, 1);

    for (unsigned int i = 0; i < this->m_MatSteepestDescentImages.cols; i++)
    {
        spanedsum = cv::Mat_<float>::zeros(this->m_iNbOfTextures, 1);
        oneCol = this->m_MatSteepestDescentImages.col(i);
        for (unsigned int j = 0; j < this->m_iNbOfTextureEigens; j++)
        {
            oneSpanRowTranspose = this->m_PCANormalizedTexture.eigenvectors.row(j).t();
            double weight = oneSpanRowTranspose.dot(oneCol);

            // dst(I)=src1(I)*alpha+src2(I)*beta+gamma
            cv::addWeighted( spanedsum, 1.0, oneSpanRowTranspose, weight, 0.0, spanedsum );
        }

        cv::subtract(oneCol, spanedsum, modifiedoneCol);
        cv::Mat_<float> tmpCol = this->m_MatModifiedSteepestDescentImages.col(i);
        modifiedoneCol.copyTo(tmpCol);
    }
}


/**
 * @author      JIA Pei
 * @version     2010-04-03
 * @brief       Calculate inverse Hessian matrix for template face
 * @return      void
*/
void VO_AAMInverseIA::VO_CalcInverseHessian()
{
    // HessianMatrix to zeros
    cv::Mat_<float> HessianMatrix = cv::Mat_<float>::zeros ( this->m_iNbOfShapeEigens+4, this->m_iNbOfShapeEigens+4);

    cv::gemm(this->m_MatModifiedSteepestDescentImages, this->m_MatModifiedSteepestDescentImages, 1, cv::Mat(), 0, HessianMatrix, cv::GEMM_1_T);

    cv::invert( HessianMatrix, this->m_MatHessianMatrixInverse, CV_SVD );
}


/**
 * @author      JIA Pei
 * @version     2010-04-03
 * @brief       Calculate Hessian matrix * MSDI^T
 * @return      void
*/
void VO_AAMInverseIA::VO_CalcICIAPreMatrix()
{
    cv::gemm(this->m_MatHessianMatrixInverse, this->m_MatModifiedSteepestDescentImages, 1, cv::Mat(), 0, this->m_MatICIAPreMatrix, cv::GEMM_2_T);
}


/**
 * @author      IA Pei
 * @version     2010-04-03
 * @brief       ICIA AAM
 * @param       allLandmarkFiles4Training   Input - all training landmark files
 * @param       allImgFiles4Training        Input - all training image files
 * @param       shapeinfoFileName           Input - shape info file
 * @param       database                    Input - which database is it?
 * @param       levels                      Input - multiscale levels
 * @param       channels                    Input - How many channels are to be used?
 * @param       trm                         Input - texture representation method
 * @param       TPShape                     Input - truncated percentage for shape model
 * @param       TPTexture                   Input - truncated percentage for texture model
 * @param       useKnownTriangles           Input - use known triangle structures??
 * @return      void
 * @note        Using "float* oProf" is much much faster than using "VO_Profile& oProf" or "std::vector<float>"
 */
 void VO_AAMInverseIA::VO_BuildAAMICIA(const std::vector<std::string>& allLandmarkFiles4Training,
                                    const std::vector<std::string>& allImgFiles4Training,
                                    const std::string& shapeinfoFileName,
                                    unsigned int database,
                                    unsigned int channels,
                                    unsigned int levels,
                                    int trm,
                                    float TPShape,
                                    float TPTexture,
                                    bool useKnownTriangles)
{
    this->VO_BuildTextureModel( allLandmarkFiles4Training,
                                allImgFiles4Training,
                                shapeinfoFileName,
                                database,
                                channels,
                                trm,
                                TPShape,
                                TPTexture,
                                useKnownTriangles);
    this->m_iNbOfPyramidLevels                  = levels;
    this->VO_CalcTemplateFaceGradients();
    this->VO_CalcSDI();
    this->VO_CalcModifiedSDI();
    this->VO_CalcInverseHessian();
    this->VO_CalcICIAPreMatrix();
}


/**
 * @author      JIA Pei
 * @version     2010-04-03
 * @brief       Save AAMICIA to a specified folder
 * @param       fn      Input - the folder that AAMICIA to be saved to
*/
void VO_AAMInverseIA::VO_Save(const std::string& fd)
{
    VO_AXM::VO_Save(fd);

    std::string fn = fd+"/AAMICIA";
    if (!boost::filesystem::is_directory(fn) )
        boost::filesystem::create_directory( fn );

    std::fstream fp;
    std::string tempfn;

    // m_IplImageTempFaceX
    tempfn = fn + "/m_IplImageTempFaceX.jpg";
    cv::imwrite(tempfn.c_str(), this->m_IplImageTempFaceX);

    // m_IplImageTempFaceY
    tempfn = fn + "/m_IplImageTempFaceY.jpg";
    cv::imwrite(tempfn.c_str(), this->m_IplImageTempFaceY);

    // m_IplImageTempFace
    tempfn = fn + "/m_IplImageTempFace.jpg";
    cv::imwrite(tempfn.c_str(), this->m_IplImageTempFace);

    // m_MatSimilarityTransform
    tempfn = fn + "/m_MatSimilarityTransform" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_MatSimilarityTransform" << std::endl;
    fp << this->m_MatSimilarityTransform;
    fp.close();fp.clear();

    // m_MatSteepestDescentImages4ShapeModel
    tempfn = fn + "/m_MatSteepestDescentImages4ShapeModel" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_MatSteepestDescentImages4ShapeModel" << std::endl;
    fp << this->m_MatSteepestDescentImages4ShapeModel;
    fp.close();fp.clear();

    // m_MatSteepestDescentImages4GlobalShapeNormalization
    tempfn = fn + "/m_MatSteepestDescentImages4GlobalShapeNormalization" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_MatSteepestDescentImages4GlobalShapeNormalization" << std::endl;
    fp << this->m_MatSteepestDescentImages4GlobalShapeNormalization;
    fp.close();fp.clear();

    // m_MatSteepestDescentImages
    tempfn = fn + "/m_MatSteepestDescentImages" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_MatSteepestDescentImages" << std::endl;
    fp << this->m_MatSteepestDescentImages;
    fp.close();fp.clear();

    // m_MatModifiedSteepestDescentImages
    tempfn = fn + "/m_MatModifiedSteepestDescentImages" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_MatModifiedSteepestDescentImages" << std::endl;
    fp << this->m_MatModifiedSteepestDescentImages;
    fp.close();fp.clear();

    // m_MatHessianMatrixInverse
    tempfn = fn + "/m_MatHessianMatrixInverse" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_MatHessianMatrixInverse" << std::endl;
    fp << this->m_MatHessianMatrixInverse;
    fp.close();fp.clear();

    // m_MatICIAPreMatrix
    tempfn = fn + "/m_MatICIAPreMatrix" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_MatICIAPreMatrix" << std::endl;
    fp << this->m_MatICIAPreMatrix;
    fp.close();fp.clear();

}


/**
 * @author     JIA Pei
 * @version    2010-04-03
 * @brief      Load all AAMICIA data from a specified folder
 * @param      fd         Input - the folder that AAMICIA to be loaded from
*/
void VO_AAMInverseIA ::VO_Load(const std::string& fd)
{
    VO_AXM::VO_Load(fd);

    std::string fn = fd+"/AAMICIA";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "AAMICIA subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::fstream fp;
    std::string tempfn;
    std::string temp;

    //// AAMICIA
    //tempfn = fn + "/AAMICIA" + ".txt";
    //fp.open(tempfn.c_str (), std::ios::in);
    //fp.close();fp.clear();

    // m_MatSimilarityTransform
    tempfn = fn + "/m_MatSimilarityTransform" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatSimilarityTransform
    fp >> this->m_MatSimilarityTransform;
    fp.close();fp.clear();

    // m_MatSteepestDescentImages4ShapeModel
    tempfn = fn + "/m_MatSteepestDescentImages4ShapeModel" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatSteepestDescentImages4ShapeModel
    fp >> this->m_MatSteepestDescentImages4ShapeModel;
    fp.close();fp.clear();

    // m_MatSteepestDescentImages4GlobalShapeNormalization
    tempfn = fn + "/m_MatSteepestDescentImages4GlobalShapeNormalization" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatSteepestDescentImages4GlobalShapeNormalization
    fp >> this->m_MatSteepestDescentImages4GlobalShapeNormalization;
    fp.close();fp.clear();

    // m_MatSteepestDescentImages
    tempfn = fn + "/m_MatSteepestDescentImages" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatSteepestDescentImages
    fp >> this->m_MatSteepestDescentImages;
    fp.close();fp.clear();

    // m_MatModifiedSteepestDescentImages
    tempfn = fn + "/m_MatModifiedSteepestDescentImages" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatModifiedSteepestDescentImages
    fp >> this->m_MatModifiedSteepestDescentImages;
    fp.close();fp.clear();

    // m_MatHessianMatrixInverse
    tempfn = fn + "/m_MatHessianMatrixInverse" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatHessianMatrixInverse
    fp >> this->m_MatHessianMatrixInverse;
    fp.close();fp.clear();

    // m_MatICIAPreMatrix
    tempfn = fn + "/m_MatICIAPreMatrix" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatICIAPreMatrix
    fp >> this->m_MatICIAPreMatrix;
    fp.close();fp.clear();

}


/**
 * @author      JIA Pei
 * @version     2010-04-03
 * @brief       Load all AAMICIA data from a specified folder
 * @param       fd      Input - the folder that AAMICIA to be loaded from
*/
void VO_AAMInverseIA ::VO_LoadParameters4Fitting(const std::string& fd)
{
    VO_AXM::VO_LoadParameters4Fitting(fd);

    std::string fn = fd+"/AAMICIA";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "AAMICIA subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::fstream fp;
    std::string tempfn;
    std::string temp;

    // m_MatICIAPreMatrix
    this->m_MatICIAPreMatrix = cv::Mat_<float>::zeros(this->m_iNbOfShapeEigens+4, this->m_iNbOfTextures);
    tempfn = fn + "/m_MatICIAPreMatrix" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatICIAPreMatrix
    fp >> this->m_MatICIAPreMatrix;
    fp.close();fp.clear();

    // m_MatSimilarityTransform
    this->m_MatSimilarityTransform = cv::Mat_<float>::zeros(4, this->m_iNbOfShapes);
    tempfn = fn + "/m_MatSimilarityTransform" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;            // m_MatSimilarityTransform
    fp >> this->m_MatSimilarityTransform;
    fp.close();fp.clear();

}

