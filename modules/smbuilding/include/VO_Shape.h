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


#ifndef __VO_SHAPE_H__
#define __VO_SHAPE_H__


#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"

//#include "VO_Triangle2DStructure.h"	// always bear in mind, this is absolutely wrong!!
class VO_Triangle2DStructure;



/** 
 * @author		JIA Pei
 * @brief		Generalized class for shape.
 */
class VO_Shape
{
friend class VO_ShapeModel;
friend class VO_TextureModel;
friend class VO_AAMBasic;
friend class VO_AAMForwardIA;
friend class VO_AAMInverseIA;
friend class VO_AFM;
friend class VO_ASMLTCs;
friend class VO_ASMNDProfiles;
friend class VO_AXM;
friend std::ostream& operator<<(std::ostream& os, const VO_Shape& shape);
friend std::istream& operator>>(std::istream& is, VO_Shape& shape);
protected:
	/** Every VO_Shape is corresponding to an annotation file */
    std::string						m_sAnnotationFileName;
	 
    /** the shape model, NbOfDim * NbOfAnnotatedPoints */
    cv::Mat_<float>        			m_MatShape;

    /** whether this point in 3D coordinates is able to be seen on 2D screen - dealing with occlusion. NbOfAnnotatedPoints */
    std::vector<bool>       		m_MatSeeable;

    void                        	CopyData(const VO_Shape& iShape)
    {
									// copy cv::Mat_ data (i.e. the point coordinates)
									iShape.m_MatShape.copyTo(this->m_MatShape);
									if(iShape.m_MatSeeable.size() > 0)
										this->m_MatSeeable = iShape.m_MatSeeable;
    }

public:
	enum { LEFTMOST	= -1, RIGHTMOST	= -2, TOPMOST = -3, BOTTOMMOST = -4,
			CENTER = -5, OUTERMOST = -6, INNERMOST = -7};

	/** Default constructor */
	VO_Shape(unsigned int dim = 0, unsigned int pts = 0) {this->m_MatShape.zeros(dim, pts);}
	
    /** Copy constructor */
    VO_Shape(const VO_Shape& iShape) {this->CopyData(iShape);}

    /** Constructor to create a VO_Shape object with a cv::Mat_ of float values */
    VO_Shape(const cv::Mat_<float>& iShape) {iShape.copyTo(this->m_MatShape);}
	VO_Shape(const cv::Mat_<float>& iShape, unsigned int dim) {this->SetTheShape(iShape, dim);}
    VO_Shape(const std::vector<cv::Point2f>& iShape)
	{
        unsigned int NbOfPoints	= iShape.size();
        this->m_MatShape	= cv::Mat_<float>::zeros(2, NbOfPoints);
        for(unsigned int j = 0; j < NbOfPoints; ++j)
		{
			this->m_MatShape(0,j)	= iShape[j].x;
			this->m_MatShape(1,j)	= iShape[j].y;
		}
	}
    VO_Shape(const std::vector<cv::Point3f>& iShape)
	{
        unsigned int NbOfPoints	= iShape.size();
        this->m_MatShape	= cv::Mat_<float>::zeros(3, NbOfPoints);
        for(unsigned int j = 0; j < NbOfPoints; ++j)
		{
			
			this->m_MatShape(0,j)	= iShape[j].x;
			this->m_MatShape(1,j)	= iShape[j].y;
			this->m_MatShape(2,j)	= iShape[j].z;
		}
	}

    /** Destructor */
    virtual ~VO_Shape() 			{this->m_MatShape.release(); this->m_MatSeeable.clear();}
	
	/** Clone */
	void							clone(const VO_Shape& iShape) {this->CopyData(iShape);}

    // operators
    VO_Shape&                		operator=(const VO_Shape& iShape);
	VO_Shape&                		operator=(const cv::Mat_<float>& iShape);
    VO_Shape&                		operator=(float value);
    VO_Shape                 		operator+(float value);
    VO_Shape&                		operator+=(float value);
    VO_Shape                 		operator+(const VO_Shape& iShape);
    VO_Shape&                		operator+=(const VO_Shape& iShape);
    VO_Shape                 		operator-(float value);
    VO_Shape&                		operator-=(float value);
    VO_Shape                 		operator-(const VO_Shape& iShape);
    VO_Shape&                		operator-=(const VO_Shape& iShape);
    VO_Shape                 		operator*(float value);
    VO_Shape&                		operator*=(float value);
    VO_Shape                    	operator*(const VO_Shape& iShape);
	VO_Shape&                   	operator*=(const VO_Shape& iShape);
    VO_Shape                 		operator/(float value);
    VO_Shape&                		operator/=(float value);
	VO_Shape                    	operator/(const VO_Shape& iShape);
	VO_Shape&                   	operator/=(const VO_Shape& iShape);
    cv::Mat_<float>        			operator[](unsigned int idx) { return this->m_MatShape.col(idx); }
	float& 							operator() (unsigned row, unsigned col);
	float  							operator() (unsigned row, unsigned col) const;
	float							dot(const VO_Shape& iShape);

	void							Resize(unsigned int rows, unsigned int cols);
    cv::Mat_<float>               	CenterOfGravity() const;
    // Transformations
    void                        	Centralize();
    void                        	Translate( const cv::Mat_<float>& translation );
    void                        	Scale( float s);
    void                        	Scale( const cv::Mat_<float>& svec);
	void                        	ScaleX( float sX);
	void                        	ScaleY( float sY);
	void                        	ScaleZ( float sZ);
    void                        	Rotate( const std::vector<float>& angles);
    void                       		Normalize();
	void							Transform(const cv::Mat_<float>& t);
    void							Transform(float scale, std::vector<float> rotateAngles, cv::Mat_<float> translation);
    float                       	GetCentralizedShapeSize() const;
    float                       	GetShapeNorm() const;
	/** This function is still to be evaluated !! */
    std::vector<float>              GetRotation( const VO_Shape& ref ) const;

	void							ConstrainShapeInSize(const cv::Size& isize);
	void							ConstrainShapeInImage(const cv::Mat& iImg);

    // Align the shapes with respect to position, scale and orientation.
    void                        	AlignTo( const VO_Shape& ref, float* scale = NULL, std::vector<float>* angles = NULL, cv::Mat_<float>* translation = NULL);
	void							Affine2D(const cv::Mat_<float>& affineMat);
    void                        	AlignTransformation( const VO_Shape& ref, float& scale, std::vector<float>& angles, cv::Mat_<float>& translation ) const;
    void                        	ProcrustesAnalysis( const VO_Shape& ref, float& norm, std::vector<float>& angles, cv::Mat_<float>& translation );
    void                        	InverseProcrustesAnalysis( const float& norm, const std::vector<float>& angles, const cv::Mat_<float>& translation );
	static void						GlobalShapeNormalization2D(const VO_Shape& iShape, VO_Shape& oShape, const cv::Mat_<float>& q);
	void							GlobalShapeNormalization2D(const cv::Mat_<float>& q);
    static void						GlobalShapeNormalization2D(const VO_Shape& iShape, VO_Shape& oShape, float scale, const std::vector<float>& angles, const cv::Mat_<float>& translation);
    void							GlobalShapeNormalization2D(float scale, const std::vector<float>& angles, const cv::Mat_<float>& translation);
    static void						SimilarityTrans2GlobalShapeNormalization(float scale, const std::vector<float>& angles, const cv::Mat_<float>& translation, cv::Mat_<float>& q);
    static void						GlobalShapeNormalization2SimilarityTrans(const cv::Mat_<float>& q, float& scale, std::vector<float>& angles, cv::Mat_<float>& translation );

    cv::Mat_<float>					Min() const;
    float                       	MinX() const;
    float                       	MinY() const;
    float                       	MinZ() const;
    cv::Mat_<float>					Max() const;
    float                       	MaxX() const;
    float                       	MaxY() const;
    float                       	MaxZ() const;
    cv::Mat_<float>					Mean() const;
    float							MeanX() const;
    float							MeanY() const;
    float							MeanZ() const;
	void                       		MinMaxX(double* minX, double* maxX) const;
	void                       		MinMaxY(double* minY, double* maxY) const;
	void                       		MinMaxZ(double* minZ, double* maxZ) const;
    cv::Point						GetLeftTop() const {cv::Point res; res.x = MinX(); res.y = MinY(); return res;}
    cv::Point						GetRightBottom() const {cv::Point res; res.x = MaxX(); res.y = MaxY(); return res;}
    cv::Point						GetLeftBottom() const {cv::Point res; res.x = MinX(); res.y = MaxY(); return res;}
    cv::Point                       GetRightTop() const {cv::Point res; res.x = MaxX(); res.y = MinY(); return res;}
//	cv::Rect_<float>					GetShapecv::Rect() const {cv::cv::Rect_<float> res; res.x = MinX(); res.y = MinY(); res.width = GetWidth(); res.height = GetHeight(); return res;}
    cv::Rect_<float>				GetShapeRect() const
	{
									double minX, maxX, minY, maxY;
									cv::minMaxLoc(this->m_MatShape.row(0), &minX, &maxX, 0, 0);
									cv::minMaxLoc(this->m_MatShape.row(1), &minY, &maxY, 0, 0);
                                    cv::Rect_<float> res;
									res.x = (float)minX;
									res.y = (float)minY;
									res.width = (float)(maxX - minX);
									res.height = (float)(maxY - minY);
									return res;
	}
    cv::Rect						GetShapeBoundRect() const
	{								
									double minX, maxX, minY, maxY;
									cv::minMaxLoc(this->m_MatShape.row(0), &minX, &maxX, 0, 0);
									cv::minMaxLoc(this->m_MatShape.row(1), &minY, &maxY, 0, 0);
                                    cv::Rect res;
									res.x = floor(minX); 
									res.y = floor(minY); 
									res.width = ceil(maxX) - res.x ; 
									res.height = ceil(maxY) - res.y;
									return res;
	}
    cv::Mat                         ToPointList() const
    {
									cv::Mat res(1, m_MatShape.cols, CV_32FC2);
									for(unsigned int i = 0; i < m_MatShape.cols; ++i)
									{
                                        res.at<cv::Point2f>(0, i) 	= cv::Point2f(m_MatShape(0, i), m_MatShape(1, i));
									}
									return res;
    }

	double							HausDorffDist(const VO_Shape& iShape);
	
	/** Is the current point "pt" in current shape? */
    int								IsPointInShape(const cv::Point2f& pt, const std::vector<VO_Triangle2DStructure>& triangles) const;
	
	/** Get VO_Triangle2DStructure specific for this VO_Shape */
    std::vector<VO_Triangle2DStructure> 	GetTriangle2DStructure(const std::vector<VO_Triangle2DStructure> triangles) const;

    /** Get shape width */
    float                       	GetWidth() const { return this->MaxX() - this->MinX(); }

    /** Get shape height */
    float                       	GetHeight() const { return this->MaxY() - this->MinY(); }

    /** Get shape height */
    float                      	 	GetDepth() const { return this->MaxZ() - this->MinZ(); }

    /** Get area (number of pixels) inside the shape */
    unsigned int					GetArea() const;

    /** Get shape dimension */
    unsigned int                	GetNbOfDim() const { return this->m_MatShape.rows; }

    /** Get Number of points */
    unsigned int                	GetNbOfPoints() const { return this->m_MatShape.cols; }

    /** Get the shape cv::Mat_ */
    cv::Mat_<float>        			GetTheShape() const { return this->m_MatShape; }
	
	/** Get a shape */
	float							GetAShape(unsigned int idx) const 
	{
									unsigned int row = idx / this->m_MatShape.cols;
									unsigned int col = idx % this->m_MatShape.cols;
									return this->m_MatShape(row, col);
	}
	float							GetAShape(unsigned int row, unsigned int col) const 
	{
									return this->m_MatShape(row, col);
	}
	
	/** Get the shape cv::Mat_ in a row, x1x2x3...y1y2y3...z1z2z3... */
    cv::Mat_<float>        			GetTheShapeInARow() const
	{
									return this->m_MatShape.reshape(1);
	}

	/** Get a single col in cv::Mat_<float> */
    cv::Mat_<float>        			GetACol(unsigned int idx) const {return this->m_MatShape.col(idx);}
	
	/** Get a 2D point */
    cv::Point2f        				GetA2DPoint(unsigned int idx) const;
	
	/** Get a 3D point */
    cv::Point3f        				GetA3DPoint(unsigned int idx) const;
	
	/** Seeable point list */
    std::vector<bool>       		GetSeeable() const { return this->m_MatSeeable; }

    /** Get a sub shape from shape */
    VO_Shape						GetSubShape(const std::vector<unsigned int>& iPtIdx) const;
	
	/** Combine two shapes */
	static VO_Shape					Combine2Shapes(const VO_Shape& shape1, const VO_Shape& shape2);
	
	/** Set a 2D point */
    void        					SetA2DPoint(const cv::Point2f& pt, unsigned int idx)
	{
									assert (m_MatShape.rows == 2);
									this->m_MatShape(0, idx) = pt.x;
									this->m_MatShape(1, idx) = pt.y;
	}

	/** Set a 3D point */
    void        					SetA3DPoint(const cv::Point3f& pt, unsigned int idx)
	{
									assert (m_MatShape.rows == 3);
									this->m_MatShape(0, idx) = pt.x;
									this->m_MatShape(1, idx) = pt.y;
									this->m_MatShape(2, idx) = pt.z;
	}

    /** Set The shape */
    void                        	SetTheShape(const cv::Mat_<float>& iShape) { iShape.copyTo(this->m_MatShape); }

	/** Set The shape in ND. iShape is of size 1*cols */
    void                        	SetTheShape(const cv::Mat_<float>& iShape, unsigned int dim)
	{
                                    if(dim <= 0) std::cerr << "dim must be natural integer, namely, >= 1" << std::endl;
									assert (iShape.rows == 1 && iShape.cols%dim == 0);
                                    this->m_MatShape = iShape.reshape(iShape.cols/dim, dim);
	}
	/** Set a specific shape at some position */
	void							SetAShape(float iS, unsigned int row, unsigned int col)
	{
									this->m_MatShape(row, col) = iS;
	}

    /** Set seeable */
    void                        	SetSeeable(const std::vector<bool>& iSeeable) { this->m_MatSeeable = iSeeable; }
	
	/** Set Annotation file name */
    void 							SetAnnotationFileName(const std::string& fn) { this->m_sAnnotationFileName = fn; }
	
	/** Export shape coordinates sequentially */
    static void                 	ExportShape(const std::string& fn, const VO_Shape& shape);
    static void                 	ExportShape(const std::string& fn, const cv::Mat_<float>& shapeMat);
};

#endif  // __VO_SHAPE_H__

