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


#ifndef __VO_WARPINGPOINT_H__
#define __VO_WARPINGPOINT_H__


#include <iostream>
#include <vector>

#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "VO_Triangle2DStructure.h"



/** 
 * @author		JIA Pei
 * @brief		Define every single warping point used in building statistical texture model
 */
class VO_WarpingPoint
{
friend class VO_ShapeModel;
friend class VO_TextureModel;
friend std::ostream& operator<<(std::ostream& os, const VO_WarpingPoint& warpingpoint);
friend std::istream& operator>>(std::istream& is, VO_WarpingPoint& warpingpoint);
private:

    /** Warping point coordinates */
    cv::Point2f							m_CVPosition;

    /** Which triangle is this point in, in the AAM model triangle std::vector? */
    unsigned int                		m_iTriangleIndex;

    /** What's the position in the AAM model template face point std::vector? */
    unsigned int                		m_iPointIndex;

    /** The triangle that this warping point belong to */
    VO_Triangle2DStructure      		m_VOTriangle2DStructure;

    /** Gradients in 3 channels (blue, green, red) for this warping point */
    std::vector< std::vector<float> >   m_Gradients;

    /** The Jacobian - 1st part , refer to http://www.visionopen.com/cv/aam.php */
    std::vector<float>               	m_Jacobian_One;

    /** The Jacobian Matrix in terms of shape parameters 2*15 */
    std::vector<std::vector<float> >    m_JacobianMatrix4ShapeModel;

    /** The Jacobian Matrix in terms of global shape normalizing transform 2*4 */
    std::vector<std::vector<float> >    m_JacobianMatrix4GlobalShapeNorm;

    /** Steepest Descent Images 3 (blue, green, red) * 15 (p parameters). */
    std::vector< std::vector<float> >	m_SteepestDescentImages4ShapeModel;

    /** Steepest Descent Images for Global Shape Transform 3 (blue, green, red) * 4. */
    std::vector< std::vector<float> >	m_SteepestDescentImages4GlobalShapeNorm;

public:
    /** Default constructor to create a VO_WarpingPoint object */
    VO_WarpingPoint()
    {
        this->m_CVPosition                              = cv::Point2f(0.0, 0.0);
        this->m_iTriangleIndex                          = 0;
        this->m_iPointIndex                             = 0;
        //this->m_VOTriangle2DStructure;
		this->m_Gradients.clear();
        this->m_Jacobian_One.clear();
        this->m_JacobianMatrix4ShapeModel.clear();
        this->m_JacobianMatrix4GlobalShapeNorm.clear();
        this->m_SteepestDescentImages4ShapeModel.clear();
        this->m_SteepestDescentImages4GlobalShapeNorm.clear();
    }

    /** Copy constructor */
    VO_WarpingPoint( const VO_WarpingPoint &t )
    {
        this->m_CVPosition                              = t.GetPosition();
        this->m_iTriangleIndex                          = t.GetTriangleIndex();
        this->m_iPointIndex                             = t.GetPointIndex();
        this->m_VOTriangle2DStructure                   = t.GetAAMTriangle2d();
        this->CalcJacobianOne ();
        this->m_JacobianMatrix4ShapeModel            	= t.GetJacobianMatrix();
        this->m_JacobianMatrix4GlobalShapeNorm          = t.GetJacobianMatrix4GlobalShapeNorm();
        this->m_Gradients                               = t.GetGradients();
        this->m_SteepestDescentImages4ShapeModel     	= t.GetSteepestDescentImages4ShapeModel();
        this->m_SteepestDescentImages4GlobalShapeNorm   = t.GetSteepestDescentImages4GlobalShapeNorm();
    }

    /** Destructor */
    virtual ~VO_WarpingPoint() {}

    /** Calculate Jacobian first part for later Jacobian matrix calculation */
    void                                CalcJacobianOne();

    /** Calculate Jacobian matrix for later Steepest Descent Image Calculation */
    void                                CalcJacobianMatrix4ShapeModel(const cv::Mat_<float>& TruncatedAlignedShapesEigenVectors);

    /** Calculate Jacobian matrix for global shape normalization for later Steepest Descent Image Calculation */
    void                                CalcJacobianMatrix4GlobalShapeNorm(const cv::Mat_<float>& SimilarityTransformMatrix);

    /** Calculate Steepest Descent Image */
    void                                CalcSteepestDescentImages4ShapeModel(unsigned int inChannels);

    /** Calculate Steepest Descent Image Calculation for global shape normalization */
    void                                CalcSteepestDescentImages4GlobalShapeNorm(unsigned int inChannels);

	/** A static function for general point warping */
    static void                         WarpOnePoint(const cv::Point2f& iPt,
                                                     const VO_Triangle2DStructure& its,
                                                     cv::Point2f& oPt,
                                                     const cv::Point2f& ov1,
                                                     const cv::Point2f& ov2,
                                                     const cv::Point2f& ov3);

    /** Get this warping point coordinates */
    cv::Point2f                         GetPosition() const {return this->m_CVPosition;}

    /** Get this warping point triangle index in AAM model triangle std::vector */
    int                                 GetTriangleIndex() const {return this->m_iTriangleIndex;}

    /** Get this warping point index in AAM model point std::vector */
    int                                 GetPointIndex() const {return this->m_iPointIndex;}

    /** Get the triangle that this warping point belong to */
    VO_Triangle2DStructure              GetAAMTriangle2d() const {return this->m_VOTriangle2DStructure;}

    /** Get Jacobian one 1*3 std::vector - alpha, beta, gamma */
    std::vector<float>                  GetJacobianOne() const { return this->m_Jacobian_One;}

    /** Get Jacobian matrix of this warping point */
    std::vector<std::vector<float> >    GetJacobianMatrix() const { return this->m_JacobianMatrix4ShapeModel;}

    /** Get Jacobian matrix for global shape normalization of this warping point */
    std::vector<std::vector<float> >    GetJacobianMatrix4GlobalShapeNorm() const { return this->m_JacobianMatrix4GlobalShapeNorm;}

    /** Get gradients for this warping point */
    std::vector< std::vector<float> >	GetGradients() const {return this->m_Gradients;}

    /** Get steepest descent image for this warping point */
    std::vector< std::vector<float> >	GetSteepestDescentImages4ShapeModel() const {return this->m_SteepestDescentImages4ShapeModel;}

    /** Get steepest descent image for global shape normalization for this warping point */
    std::vector< std::vector<float> >	GetSteepestDescentImages4GlobalShapeNorm() const { return this->m_SteepestDescentImages4GlobalShapeNorm;}


    /** Set this warping point coordinates */
    void    		            	SetPosition(cv::Point2f iPoint) {this->m_CVPosition = iPoint;}
	void    		            	SetPosition(float x, float y) {this->m_CVPosition = cv::Point2f(x, y);}

    /** Set this warping point triangle index in AAM model triangle std::vector */
    void    		            	SetTriangleIndex(unsigned int iTriangleIndex) {this->m_iTriangleIndex = iTriangleIndex;}

    /** Set this warping point index in AAM model point std::vector */
    void    		            	SetPointIndex(unsigned int iPointIndex) {this->m_iPointIndex = iPointIndex;}

    /** Set 3 vertexes of the triangle that this point belong to, with input in format of a std::vector of points */
    void                        	SetTriangle2DStructure(const std::vector<cv::Point2f>& inVertexes, const std::vector<unsigned int>& iIndexes)
    {
									assert(inVertexes.size() == 3);
									this->m_VOTriangle2DStructure = VO_Triangle2DStructure(inVertexes, iIndexes);
    }

    /** Set the triangle that this point belong to */
    void                            SetTriangle2DStructure(const VO_Triangle2DStructure& inAAMTriangle2d)
    {
                                    this->m_VOTriangle2DStructure = inAAMTriangle2d;
    }

    /** Set Jacobian one 1*3 std::vector - alpha, beta, gamma */
    void                            SetJacobianOne(const std::vector<float>& iJO) { this->m_Jacobian_One = iJO;}

    /** Set Jacobian matrix for this warping point */
    void	                    	SetJacobianMatrix(const std::vector<std::vector<float> > & iJM) { this->m_JacobianMatrix4ShapeModel = iJM;}

    /** Set Jacobian matrix for global shape normalization for this warping point */
    void	                    	SetJacobianMatrix4GlobalShapeNorm(const std::vector< std::vector<float> >& iJM4GlobalShapeNorm) { this->m_JacobianMatrix4GlobalShapeNorm = iJM4GlobalShapeNorm;}

    /** Set gradients for this warping point */
    void                        	SetGradients(const std::vector< std::vector<float> >& iGradients) { this->m_Gradients = iGradients;}

    /** Set steepest descent image for this warping point */
    void	                    	SetSteepestDescentImages(const std::vector< std::vector<float> >& iSDI) { this->m_SteepestDescentImages4ShapeModel = iSDI;}

    /** Set steepest descent image for global shape normalization for this warping point */
    void	                    	SetSteepestDescentImages4GlobalShapeNorm(const std::vector< std::vector<float> >& iSDI4GlobalShapeNorm) { this->m_SteepestDescentImages4GlobalShapeNorm = iSDI4GlobalShapeNorm;}

};

#endif	// __VO_WARPINGPOINT_H__

