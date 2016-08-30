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


#include "VO_WarpingPoint.h"


std::ostream& operator<<(std::ostream& os, const VO_WarpingPoint& warpingpoint)
{
    os << warpingpoint.m_iPointIndex << " "
        << warpingpoint.m_CVPosition.x << " "
        << warpingpoint.m_CVPosition.y << " "
        << warpingpoint.m_iTriangleIndex;

    return os;
}

std::istream& operator>>(std::istream& is, VO_WarpingPoint& warpingpoint)
{
    int tempint;
    CvPoint2D32f tempPoint;

    is >> tempint;
    warpingpoint.SetPointIndex(tempint);
    is >> tempPoint.x >> tempPoint.y;
    warpingpoint.SetPosition(tempPoint);
    is >> tempint;
    warpingpoint.SetTriangleIndex(tempint);
    
    return is;
}

/**
 * @author     JIA Pei
 * @version    2010-02-08
 * @brief      Calculate the first item of Jacobian
 * @return     void
 * @note       http://visionopen.com/cv/aam.php
*/
void VO_WarpingPoint::CalcJacobianOne()
{
    float x, y, x1, x2, x3, y1, y2, y3;
    this->m_Jacobian_One.resize(3);

    x = this->m_CVPosition.x;
    y = this->m_CVPosition.y;

    x1 = this->m_VOTriangle2DStructure.GetA2DPoint(0).x;
    x2 = this->m_VOTriangle2DStructure.GetA2DPoint(1).x;
    x3 = this->m_VOTriangle2DStructure.GetA2DPoint(2).x;
    y1 = this->m_VOTriangle2DStructure.GetA2DPoint(0).y;
    y2 = this->m_VOTriangle2DStructure.GetA2DPoint(1).y;
    y3 = this->m_VOTriangle2DStructure.GetA2DPoint(2).y;

    this->m_Jacobian_One[0] = y*x3-y3*x+x*y2-x2*y+x2*y3-x3*y2;
    this->m_Jacobian_One[1] = -y*x3+x1*y+x3*y1+y3*x-x1*y3-x*y1;
    this->m_Jacobian_One[2] = -x*y2+x*y1+x1*y2+x2*y-x2*y1-x1*y;

    // make sure m_Jacobian_One is bigger than 0
    for (unsigned int i = 0; i < this->m_Jacobian_One.size(); i++)
    {
        this->m_Jacobian_One[i] /= this->m_VOTriangle2DStructure.GetdD();
        if (this->m_Jacobian_One[i] < FLT_EPSILON)
            this->m_Jacobian_One[i] = 0.0;
    }
}


/**
 * @author         JIA Pei
 * @version        2010-02-08
 * @brief          Calculate the Jacobian matrix
 * @param          TruncatedAlignedShapesEigenVectors        Input    the input parameters
 * @return         void
*/
void VO_WarpingPoint::CalcJacobianMatrix4ShapeModel(const cv::Mat_<float>& TruncatedAlignedShapesEigenVectors)
{
    unsigned int NbOfShapesParameters = TruncatedAlignedShapesEigenVectors.rows;
    unsigned int NbOfShapePoints = TruncatedAlignedShapesEigenVectors.cols/2;
    // for a certain temppixeltriangle.m_CVPosition, the Jacobian[i] are different

    this->m_JacobianMatrix4ShapeModel.resize (2);
    this->m_JacobianMatrix4ShapeModel[0].resize(NbOfShapesParameters);
    this->m_JacobianMatrix4ShapeModel[1].resize(NbOfShapesParameters);

    for (unsigned int np = 0; np < NbOfShapesParameters; np++)
    {
        this->m_JacobianMatrix4ShapeModel[0][np] =
                this->m_Jacobian_One[0] * TruncatedAlignedShapesEigenVectors.at<float>( np, this->m_VOTriangle2DStructure.GetVertexIndex(0) )
              + this->m_Jacobian_One[1] * TruncatedAlignedShapesEigenVectors.at<float>( np, this->m_VOTriangle2DStructure.GetVertexIndex(1) )
              + this->m_Jacobian_One[2] * TruncatedAlignedShapesEigenVectors.at<float>( np, this->m_VOTriangle2DStructure.GetVertexIndex(2) );

        this->m_JacobianMatrix4ShapeModel[1][np] =
                this->m_Jacobian_One[0] * TruncatedAlignedShapesEigenVectors.at<float>( np, this->m_VOTriangle2DStructure.GetVertexIndex(0)+NbOfShapePoints )
              + this->m_Jacobian_One[1] * TruncatedAlignedShapesEigenVectors.at<float>( np, this->m_VOTriangle2DStructure.GetVertexIndex(1)+NbOfShapePoints )
              + this->m_Jacobian_One[2] * TruncatedAlignedShapesEigenVectors.at<float>( np, this->m_VOTriangle2DStructure.GetVertexIndex(2)+NbOfShapePoints );
    }
}


/**
 * @author         JIA Pei
 * @version        2010-02-08
 * @brief          Calculate the Jacobian matrix for global shape normalization
 * @param          SimilarityTransformMatrix
 * @return         void
*/
void VO_WarpingPoint::CalcJacobianMatrix4GlobalShapeNorm(const cv::Mat_<float>& SimilarityTransformMatrix)
{
    unsigned int NbOfSimilarityTransformParameters = SimilarityTransformMatrix.rows;
    unsigned int NbOfShapePoints = SimilarityTransformMatrix.cols/2;
    // for a certain temppixeltriangle.m_CVPosition, the Jacobian[i] are different

    this->m_JacobianMatrix4GlobalShapeNorm.resize (2);
    this->m_JacobianMatrix4GlobalShapeNorm[0].resize(NbOfSimilarityTransformParameters);
    this->m_JacobianMatrix4GlobalShapeNorm[1].resize(NbOfSimilarityTransformParameters);

    for (unsigned int np = 0; np < NbOfSimilarityTransformParameters; np++)
    {
        this->m_JacobianMatrix4GlobalShapeNorm[0][np] =
            this->m_Jacobian_One[0] * SimilarityTransformMatrix.at<float>(np, this->m_VOTriangle2DStructure.GetVertexIndex(0) )
          + this->m_Jacobian_One[1] * SimilarityTransformMatrix.at<float>(np, this->m_VOTriangle2DStructure.GetVertexIndex(1) )
          + this->m_Jacobian_One[2] * SimilarityTransformMatrix.at<float>(np, this->m_VOTriangle2DStructure.GetVertexIndex(2) );

        this->m_JacobianMatrix4GlobalShapeNorm[1][np] =
            this->m_Jacobian_One[0] * SimilarityTransformMatrix.at<float>(np, this->m_VOTriangle2DStructure.GetVertexIndex(0)+NbOfShapePoints )
          + this->m_Jacobian_One[1] * SimilarityTransformMatrix.at<float>(np, this->m_VOTriangle2DStructure.GetVertexIndex(1)+NbOfShapePoints )
          + this->m_Jacobian_One[2] * SimilarityTransformMatrix.at<float>(np, this->m_VOTriangle2DStructure.GetVertexIndex(2)+NbOfShapePoints );
    }
}


/**
 * @author     JIA Pei
 * @version    2010-02-08
 * @brief      Calculate the Steepest Descent Image (SDI)
 * @return     void
*/
void VO_WarpingPoint::CalcSteepestDescentImages4ShapeModel(unsigned int inChannels)
{
    this->m_SteepestDescentImages4ShapeModel.resize (inChannels);

    for (unsigned int i = 0; i < this->m_SteepestDescentImages4ShapeModel.size (); i++)
    {
        this->m_SteepestDescentImages4ShapeModel[i].resize (this->m_JacobianMatrix4ShapeModel[0].size ());
    }

    for (unsigned int i = 0; i < this->m_SteepestDescentImages4ShapeModel[0].size (); i++)
    {
        for (unsigned int k = 0; k < inChannels; k++)
        {
            this->m_SteepestDescentImages4ShapeModel[k][i] =
                this->m_Gradients[k][0] * this->m_JacobianMatrix4ShapeModel[0][i] +
                this->m_Gradients[k][1] * this->m_JacobianMatrix4ShapeModel[1][i];
        }
    }
}


/**
 * @author     JIA Pei
 * @version    2010-02-08
 * @brief      Calculate the Steepest Descent Image (SDI) for global shape normalization
 * @return     void
*/
void VO_WarpingPoint::CalcSteepestDescentImages4GlobalShapeNorm(unsigned int inChannels)
{
    this->m_SteepestDescentImages4GlobalShapeNorm.resize (inChannels);

    for (unsigned int i = 0; i < this->m_SteepestDescentImages4GlobalShapeNorm.size (); i++)
    {
        this->m_SteepestDescentImages4GlobalShapeNorm[i].resize (this->m_JacobianMatrix4GlobalShapeNorm[0].size ());
    }

    for (unsigned int i = 0; i < this->m_SteepestDescentImages4GlobalShapeNorm[0].size (); i++)
    {
        for (unsigned int k = 0; k < inChannels; k++)
        {
            this->m_SteepestDescentImages4GlobalShapeNorm[k][i] =
                this->m_Gradients[k][0] * this->m_JacobianMatrix4GlobalShapeNorm[0][i] +
                this->m_Gradients[k][1] * this->m_JacobianMatrix4GlobalShapeNorm[1][i];
        }
    }
}


/**
 * @author     JIA Pei
 * @version    2010-05-22
 * @brief      Static function to warp one single point
 * @return     void
*/
void VO_WarpingPoint::WarpOnePoint(const cv::Point2f& iPt,
                                   const VO_Triangle2DStructure& its,
                                   cv::Point2f& oPt,
                                   const cv::Point2f& ov1,
                                   const cv::Point2f& ov2,
                                   const cv::Point2f& ov3)
{
    cv::Point2f iv1 = its.GetA2DPoint(0);
    cv::Point2f iv2 = its.GetA2DPoint(1);
    cv::Point2f iv3 = its.GetA2DPoint(2);
    double c = 1.0/its.GetdD();

    double alpha = (iPt.y*iv3.x-iv3.y*iPt.x+iPt.x*iv2.y-iv2.x*iPt.y+iv2.x*iv3.y-iv3.x*iv2.y)*c;
    double belta  = (-iPt.y*iv3.x+iv1.x*iPt.y+iv3.x*iv1.y+iv3.y*iPt.x-iv1.x*iv3.y-iPt.x*iv1.y)*c;
    double gamma = 1.0 - alpha - belta; 

    oPt.x = alpha*ov1.x + belta*ov2.x + gamma*ov3.x;
    oPt.y = alpha*ov1.y + belta*ov2.y + gamma*ov3.y;
}

