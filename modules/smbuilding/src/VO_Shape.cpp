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


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "VO_Shape.h"
#include "VO_Triangle2DStructure.h"	// a must, compare to line 25-26 in VO_Shape.h
#include "VO_CVCommon.h"


std::ostream& operator<<(std::ostream& os, const VO_Shape& shape)
{
    os << shape.m_MatShape;
    return os;
}


std::istream& operator>>(std::istream& is, VO_Shape& shape)
{
    is >> shape.m_MatShape;
    return is;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator= overloading, similar to copy constructor
 * @param      	iShape	The input shape
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator=(const VO_Shape& iShape)
{
    this->CopyData (iShape);
    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator= overloading, similar to copy constructor
 * @param      	iShape	The input shape
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator=(const cv::Mat_<float>& iShape)
{
    iShape.copyTo(this->m_MatShape);
    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator= overloading, similar to copy constructor
 * @param      	value		assign all values in VO_Shape to value
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator=(float value)
{
    m_MatShape = value;
    return *this;
}


/**
  * @author     JIA Pei
  * @version    2010-02-07
  * @brief      operator+ overloading, shift one AAM shape by value
  * @param      value
  * @return     VO_Shape
*/
VO_Shape VO_Shape::operator+(float value)
{
    VO_Shape res(*this);
    res.m_MatShape += value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+= overloading, add value to this AAM shape
 * @param      	value
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator+=(float value)
{
    m_MatShape += value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+ overloading, add two AAM shape to one
 * @param      	iShape      the added AAM shape
 * @return     	VO_Shape
*/
VO_Shape VO_Shape::operator+(const VO_Shape& iShape)
{
    VO_Shape res(*this);
    res.m_MatShape += iShape.m_MatShape;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+= overloading, add the input AAM shape to this AAM shape
 * @param      	iShape      the added AAM shape
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator+=(const VO_Shape& iShape)
{
    this->m_MatShape += iShape.m_MatShape;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator- overloading, shift one AAM shape by -value
 * @param      	value
 * @return     	VO_Shape
*/
VO_Shape VO_Shape::operator-(float value)
{
    VO_Shape res(*this);
    res.m_MatShape -= value;
	
    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator-= overloading, subtract value from this AAM shape
 * @param      	value
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator-=(float value)
{
    this->m_MatShape -= value;

	return *this;
}


/**
  * @author     JIA Pei
  * @version    2010-02-07
  * @brief      operator- overloading, subtract one shape from another
  * @param      iShape      the subtracted AAM shape
  * @return     VO_Shape
*/
VO_Shape VO_Shape::operator-(const VO_Shape& iShape)
{
    VO_Shape res(*this);
    res.m_MatShape -= iShape.m_MatShape;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator-= overloading, subtract the input AAM shape from this AAM shape
 * @param      	iShape      the subtracted AAM shape
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator-=(const VO_Shape &iShape)
{
    this->m_MatShape -= iShape.m_MatShape;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, scale a shape with input float value
 * @param      	value      scale size
 * @return     	VO_Shape
*/
VO_Shape VO_Shape::operator*(float value)
{
    VO_Shape res(*this);
    res.m_MatShape *= value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator*= overloading, scale this shape with input float value
 * @param      	iShape      the subtracted AAM shape
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator*=(float value)
{
    this->m_MatShape *= value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, element-wise product of two AAM shapes
 * @param      	iShape      AAM shape to be dot producted
 * @return     	float       dot product
*/
VO_Shape VO_Shape::operator*(const VO_Shape& iShape)
{
	VO_Shape res(*this);
    res.m_MatShape = res.m_MatShape.mul(iShape.m_MatShape);

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, element-wise product of two AAM shapes
 * @param      	iShape      AAM shape to be dot producted
 * @return     	float       dot product
*/
VO_Shape& VO_Shape::operator*=(const VO_Shape& iShape)
{
    this->m_MatShape = this->m_MatShape.mul(iShape.m_MatShape);

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/ overloading, scale a shape
 * @param      	value      1.0/value = scale size
 * @return     	VO_Shape
*/
VO_Shape VO_Shape::operator/(float value)
{
    if( fabs(value) <= FLT_MIN )
    {
        std::cerr << "Divided by zero!" << std::endl;
        exit(EXIT_FAILURE);
    }

    VO_Shape res(*this);
    res.m_MatShape /= value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/= overloading, scale this shape with input float value
 * @param      	value      1.0/value = the scaled value
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator/=(float value)
{
    if( fabs(value) <= FLT_MIN )
    {
        std::cerr << "Divided by zero!" << std::endl;
        exit(EXIT_FAILURE);
    }

    this->m_MatShape /= value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/ overloading, scale a shape
 * @param      	iShape      for element-wise division
 * @return     	VO_Shape
*/
VO_Shape VO_Shape::operator/(const VO_Shape& iShape)
{
    for(unsigned int i = 0; i < iShape.m_MatShape.rows; i++)
	{
        for(unsigned int j = 0; j < iShape.m_MatShape.cols; j++)
		{
            if( fabs(iShape.m_MatShape(i,j)) <= FLT_MIN )
			{
                std::cerr << "Divided by zero!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

    VO_Shape res(*this);
    res.m_MatShape /= iShape.m_MatShape;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/= overloading, scale this shape with input float value
 * @param      	iShape      for element-wise division
 * @return     	VO_Shape&
*/
VO_Shape& VO_Shape::operator/=(const VO_Shape& iShape)
{
    for(unsigned int i = 0; i < iShape.m_MatShape.rows; i++)
	{
        for(unsigned int j = 0; j < iShape.m_MatShape.cols; j++)
		{
            if( fabs(iShape.m_MatShape(i,j)) <= FLT_MIN )
			{
                std::cerr << "Divided by zero!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

    this->m_MatShape /= iShape.m_MatShape;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator() overloading, obtain the shape value at row and col
 * @param      	row      input	- row index
 * @param      	col      input	- col index
 * @return     	float&
*/
float&  VO_Shape::operator() (unsigned row, unsigned col)
{
    if ( row >= m_MatShape.rows || col >= m_MatShape.cols )
        std::cerr << "cv::Matrix subscript out of bounds" << std::endl;
    return this->m_MatShape(row, col);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator() overloading, obtain the shape value at row and col
 * @param      	row      input	- row index
 * @param      	col      input	- col index
 * @return     	float&
*/
float  VO_Shape::operator() (unsigned row, unsigned col) const
{
    if ( row >= m_MatShape.rows || col >= m_MatShape.cols )
        std::cerr << "cv::Matrix subscript out of bounds" << std::endl;
    return this->m_MatShape(row, col);
}

	
/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, dot product of two AAM shapes
 * @param      	iShape      AAM shape to be dot producted
 * @return     	float       dot product
*/
float VO_Shape::dot(const VO_Shape& iShape)
{
    return this->m_MatShape.dot(iShape.m_MatShape);
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      resize the matrix
 * @param      rows
 * @param      cols
 * @return     void
*/
void VO_Shape::Resize(unsigned int rows, unsigned int cols)
{
    this->m_MatShape.release();
    this->m_MatShape = cv::Mat_<float>::zeros(rows, cols);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Calculates the Center Of Gravity of the shape
 * @return     	Nothing.
*/
cv::Mat_<float> VO_Shape::CenterOfGravity() const
{
    return this->Mean();
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      Centralize this shape.
 * @return     Nothing.
*/
void VO_Shape::Centralize( )
{
    cv::Mat_<float> center = this->CenterOfGravity();
    this->Translate(-center);
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      Translate this shape.
 * @param      x	X-translation.
 * @param      y	Y-translation.
 * @return     Nothing.
*/
void VO_Shape::Translate( const cv::Mat_<float>& translation )
{
    if (translation.rows != this->m_MatShape.rows )
    {
        std::cerr << "translation cv::Mat_ should have the same size as cv::Point dimention!" << std::endl;
        exit(EXIT_FAILURE);
    }
    for(unsigned int i = 0; i < this->m_MatShape.rows; i++)
        // modified by Pei JIA. 2014-05-08
        //this->m_MatShape.row(i) += translation(i,0);
    {
        for(unsigned int j = 0; j < this->m_MatShape.cols; j++)
        {
            this->m_MatShape.at<float>(i,j) += translation(i,0);
        }
    }
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Scale this shape.
 * @param      	s			Scale factor
 * @return     	void
*/
void VO_Shape::Scale( float s)
{
    this->m_MatShape *= s;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Scale this shape
 * @param		svec	-- input, scale factor
 * @return     	void
*/
void VO_Shape::Scale( const cv::Mat_<float>& svec)
{
    if (svec.rows != this->m_MatShape.rows )
    {
        std::cerr << "scale cv::Mat_ should have the same size as cv::Point dimention!";
        exit(EXIT_FAILURE);
    }
    for(unsigned int i = 0; i < this->m_MatShape.rows; i++)
        // modified by Pei JIA. 2014-05-08
        //this->m_MatShape.row(i) *= svec(i,0);
    {
        for(unsigned int j = 0; j < this->m_MatShape.cols; j++)
        {
            this->m_MatShape.at<float>(i,j) *= svec(i,0);
        }
    }
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Scale this shape in X direction
 * @return     	void
*/
void VO_Shape::ScaleX( float sX)
{
    this->m_MatShape.row(0) *= sX;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Scale this shape in Y direction
 * @return     	void
*/
void VO_Shape::ScaleY( float sY)
{
    this->m_MatShape.row(1) *= sY;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Scale this shape in Z direction
 * @return     	void
*/
void VO_Shape::ScaleZ( float sZ)
{
    this->m_MatShape.row(2) *= sZ;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Rotates the shape in 2-3D
 * @param      	angles		Rotation angle in radians
 * @return     	Nothing.
*/
void VO_Shape::Rotate( const std::vector<float>& angles)
{
    unsigned int shapeDim = this->m_MatShape.rows;
    unsigned int NbOfPoints = this->m_MatShape.cols;
    unsigned int angleDim = shapeDim == 2 ? 1 : 3;	// only 2D or 3D are considered
    if ( angleDim != angles.size() )
    {
        std::cerr << "Rotate angles should have the same dimension as point dimension" << std::endl;
        exit(EXIT_FAILURE);
    }
    switch(shapeDim)
    {
    case 3:
        {
            float x, y, z;

            // Assuming the angles are in radians.
            float cph = cos( angles[0] );
            float sph = sin( angles[0] );
            float cth = cos( angles[1] );
            float sth = sin( angles[1] );
            float cps = cos( angles[2] );
            float sps = sin( angles[2] );

            // set up rotation matrix
			// http://mathworld.wolfram.com/Rotationcv::Matrix.html
			// this is equal to
            /**
             * 1            0           0
             * 0            cos(ph)     sin(ph)
             * 0            -sin(ph)    cos(ph)
             *
             * cos(th)      0           -sin(th)
             * 0            1           0
             * sin(th)      0           cos(th)
             *
             * cos(ps)      sin(ps)     0
             * -sin(ps)     cos(ps)     0
             * 0            0           1
             */
            float c00 =  cth * cps;
            float c01 =  cth * sps;
            float c02 =  -sth;
            float c10 =  sph * sth * cps - cph * sps;
            float c11 =  sph * sth * sps + cph * cps;
            float c12 =  sph * cth;
            float c20 =  cph * sth * cps + sph * sps;
            float c21 =  cph * sth * sps - sph * cps;
            float c22 =  cph * cth;

            for(unsigned int i = 0; i < NbOfPoints; ++i)
            {
                x = this->m_MatShape(0, i);
                y = this->m_MatShape(1, i);
                z = this->m_MatShape(2, i);
                this->m_MatShape(0, i) =  c00*x+c01*y+c02*z;
                this->m_MatShape(1, i) =  c10*x+c11*y+c12*z;
                this->m_MatShape(2, i) =  c20*x+c21*y+c22*z;
            }
        }
    break;
    case 2:
    default:
        {
            float x, y;

            // set up rotation matrix
            float c00 =  cos( angles[0] );
            float c01 = -sin( angles[0] );
            float c10 =  sin( angles[0] );
            float c11 =  cos( angles[0] );

            for(unsigned int i = 0; i < NbOfPoints; i++)
            {
                x = this->m_MatShape(0, i);
                y = this->m_MatShape(1, i);
                this->m_MatShape(0, i) =  c00*x+c01*y;
                this->m_MatShape(1, i) =  c10*x+c11*y;
            }
        }
    break;
    }
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Normalize the shape by translating to its Center Of Gravity
                scaling by the reciprocal of the 2-norm
 * @return	    nothing
*/
void VO_Shape::Normalize()
{
    this->Centralize();

    float norm = this->GetShapeNorm();

    this->Scale( 1.0f/norm );
}


/**
 * @author   JIA Pei
 * @version  2010-02-07
 * @brief    Returns the 2-norm of this centralized shape
 * @return   The 2-norm of the shape after translating to origin
*/
float VO_Shape::GetCentralizedShapeSize() const
{
    VO_Shape tmp(*this);
    tmp.Centralize();
	
	return tmp.GetShapeNorm();
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      Get the norm of the shape
 * @return     float
*/
float VO_Shape::GetShapeNorm() const
{
    return (float) cv::norm(this->m_MatShape);
}


/**
 * @author		JIA Pei
 * @version		2010-02-07
 * @brief		Returns the rotation from this to ref (in radians).
                Get the rotation between two shapes by minimizing the sum of squared point distances,
                as described by Goodall (and Bookstein, Horn) using Singular Value Decomposition (SVD).

                Note that both shapes must be normalized with respect to scale and position beforehand.
                This could be done by using VO_Shape::Normalize().
 * @param      	ref         The reference shape.
 * @return	    The estimated angle, theta, between the two shapes.
*/
std::vector<float> VO_Shape::GetRotation( const VO_Shape& ref ) const
{
    std::vector<float> angles;
    assert( ref.m_MatShape.size() == this->m_MatShape.size() );

    cv::Mat_<float> res = ref.m_MatShape * this->m_MatShape.t();
//	cv::gemm(ref.m_MatShape, this->m_MatShape, 1.0, cv::Mat_<float>(), 0.0, res, GEMM_2_T);

	double det = cv::determinant( res );

    cv::SVD svd(res);
	
    if(det < 0.0f)
    {
        cv::Mat_<float> D = cv::Mat_<float>::eye(this->m_MatShape.rows, this->m_MatShape.rows);
    	D.at<float>(D.rows - 1, D.cols - 1) = -1.0;

//		cv::gemm(svd.u, D, 1.0, cv::Mat_<float>(), 0.0, res);
//		cv::gemm(res, svd.vt, 1.0, cv::Mat_<float>(), 0.0, res);
		res = svd.u * D * svd.vt;
    }
    else
    {
//		cv::gemm(svd.u, svd.vt, 1.0, cv::Mat_<float>(), 0.0, res);
		res = svd.u * svd.vt;
    }

    switch(this->m_MatShape.rows)
    {
    case 3:
        {
			angles.resize(3);
            // res now holds a normal 3x3 rotation matrix
			// http://mathworld.wolfram.com/Rotationcv::Matrix.html
            float sin_beta  = -res.at<float>(0, 2);
            float tan_alpha = res.at<float>(1, 2) / res.at<float>(2, 2);
            float tan_gamma = res.at<float>(0, 1) / res.at<float>(0, 0);

            angles[0] = (float)atan(tan_alpha);
            angles[1] = (float)asin(sin_beta);
            angles[2] = (float)atan(tan_gamma);
        }
        break;
    case 2:
    default:
        {
			angles.resize(1);
            // res now holds a normal 2*2 rotation matrix
            float cos_theta = res.at<float>(0, 0);
            float sin_theta = res.at<float>(1, 0);

            // cos_theta should be less than 1.0; but here, cos_theta is calculated by matrix computation,
            // in stead of by acos() function, so cos_theta might have some special values like cos_theta >= 1.0.
            if ( ( fabs(1.0-cos_theta) < FLT_EPSILON ) || cos_theta >= 1.0 )
            {
                // cos_theta = 1  =>  shapes are already aligned
                angles[0] = 0.0f;
            }
            else if ( fabs(cos_theta) < FLT_EPSILON )
            {
                // cos_theta = 0  =>  90 degrees rotation
                angles[0] = (float)(CV_PI/2.0);
            }
            // cos_theta should be bigger than -1.0; but here, cos_theta is calculated by  matrix computation,
            // in stead of by acos() function, so cos_theta might have some special values like cos_theta <= -1.0.
            else if ( ( fabs(1.0+cos_theta) < FLT_EPSILON ) || cos_theta <= -1.0 )
            {
                // cos_theta=-1  =>  180 degrees rotation
                angles[0] = (float)CV_PI;
            }
            else
            {
                // get the rotation in radians
                float a_cos = (float)acos( cos_theta );
                float a_sin = (float)asin( sin_theta );

                // http://en.wikipedia.org/wiki/Trigonometric_function
                if (a_sin<0)
                {
                    // lower half of the unit circle
                    angles[0] = -a_cos;
                }
                else
                {
                    // upper half of the unit circle
                    angles[0] = a_cos;
                }
            }
        }
        break;
    }

    return angles;
}


/**
 * @author	    JIA Pei
 * @version		2010-05-19
 * @brief		Ensure the shape is within the size
 * @param	    iSize	    		input parameter - the size
 * @return	    void
*/
void VO_Shape::ConstrainShapeInSize(const cv::Size& iSize)
{
    unsigned int NbOfPoints = this->GetNbOfPoints();
    for(unsigned int j = 0; j < NbOfPoints; j++)
	{
        if(this->m_MatShape(0, j) < FLT_MIN)
            this->m_MatShape(0, j) = 0.0f;
        else if(this->m_MatShape(0, j) > (iSize.width -1.0f) )
            this->m_MatShape(0, j) = iSize.width -1.0f;
			
        if(this->m_MatShape(1, j) < FLT_MIN)
            this->m_MatShape(1, j) = 0.0f;
        else if(this->m_MatShape(1, j) > (iSize.height -1.0f) )
            this->m_MatShape(1, j) = iSize.height -1.0f;
	}
}


/**
 * @author	    JIA Pei
 * @version		2010-05-19
 * @brief		Ensure the shape is within the image
 * @param	    iImg	    		input parameter - the image
 * @return	    void
*/
void VO_Shape::ConstrainShapeInImage(const cv::Mat& iImg)
{
    unsigned int NbOfPoints = this->GetNbOfPoints();
    for(unsigned int j = 0; j < NbOfPoints; j++)
	{
        if(this->m_MatShape(0, j) < FLT_MIN)
            this->m_MatShape(0, j) = 0.0f;
        else if(this->m_MatShape(0, j) >= (iImg.cols -1.0f - FLT_MIN) )
            this->m_MatShape(0, j) = iImg.cols -1.0f - 0.1f;
			
        if(this->m_MatShape(1, j) < FLT_MIN)
            this->m_MatShape(1, j) = 0.0f;
        else if(this->m_MatShape(1, j) > (iImg.rows -1.0f - FLT_MIN) )
            this->m_MatShape(1, j) = iImg.rows -1.0f - 0.1f;
	}
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Aligns this to 'ref' with respect to pose.
 * @param	    ref	    		input parameter - The reference shape
 * @param	    scale			output parameter - scale value, from this to ref
 * @param	    angles			output parameter - rotation angles, from this to ref
 * @param	    translation	    output parameter - translation in both X, Y directions, from this to ref
 * @return	    void
*/
void VO_Shape::AlignTo( const VO_Shape& ref, float* scale, std::vector<float>* angles, cv::Mat_<float>* translation )
{
    // make a copy of 'ref'
    VO_Shape refCpy( ref );
    cv::Mat_<float> center1, center2;

    // translate, move this and refCpy to origin
    center1 = this->CenterOfGravity( );
    this->Translate( -center1 );
    center2 = refCpy.CenterOfGravity( );
    refCpy.Translate( -center2 );
	if(translation) *translation = center2 - center1;

    // scale, using the 2-norm
    float this_size = this->GetShapeNorm();
    float ref_size = refCpy.GetShapeNorm();
	if(scale)
	{
		*scale = ref_size/this_size;
		this->Scale( *scale );
	}
	else
		this->Scale( ref_size/this_size );

    // align rotation between this and refCpy
    if(angles)
	{
		*angles = this->GetRotation( refCpy );
		this->Rotate( *angles );
	}
	else
		this->Rotate( this->GetRotation( refCpy ) );

    // translate this to ref origin
    this->Translate( center2 );
}


/**
 * @author	    JIA Pei
 * @version		2010-05-24
 * @brief		Affine transform of current shape
 * @param	    affineMat	    input parameter - matrix for affine transform
 * @return	    void
*/
void VO_Shape::Affine2D(const cv::Mat_<float>& affineMat)
{
    unsigned int NbOfPoints = this->m_MatShape.cols;
    cv::Mat_<float> tmp 		= cv::Mat_<float>::ones(3, NbOfPoints);
    cv::Mat roi 				= tmp(cv::Range(0, 2), cv::Range(0, NbOfPoints) );
    this->m_MatShape.copyTo(roi);
    this->m_MatShape = affineMat*tmp;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-24
 * @brief		Returns the transformation that aligns this to 'ref'
 * @param	    ref	    		input parameter - The reference shape
 * @param	    scale			output parameter - scale value, from this to ref
 * @param	    angles			output parameter - rotation angles, from this to ref
 * @param	    translation	    output parameter - translation in both X, Y directions, from this to ref
 * @return	    void
*/
void VO_Shape::AlignTransformation( const VO_Shape& ref, float& scale, std::vector<float>& angles, cv::Mat_<float>& translation ) const
{
    VO_Shape refCpy( ref );
    VO_Shape thisCpy( *this );     		// a must, we don't want to change "this" right now
    cv::Mat_<float> center1, center2;

    // move thisCpy and refCpy to origin
    center1 			= thisCpy.CenterOfGravity( );
    thisCpy.Translate( -center1 );
    center2 			= refCpy.CenterOfGravity( );
    refCpy.Translate( -center2 );
    translation 		= center2 - center1;

    // normalize scale, using the 2-norm
    float this_size    	= thisCpy.GetShapeNorm();
    float ref_size     	= refCpy.GetShapeNorm();
    scale              	= ref_size/this_size;
    thisCpy.Scale( scale );

    // align rotation between thisCpy and refCpy
    angles = thisCpy.GetRotation( refCpy );
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Proscrustes Analysis
 * @param	    ref	    		input parameter - The reference shape, a must!!!!!!!!!!
 * @param	    scale			output parameter - 2 norm of a shape
 * @param	    angles			output parameter - rotation angles, from this to ref
 * @param	    translation	    output parameter - translation in both X, Y directions
 * @return	    void
 * @note       	http://en.wikipedia.org/wiki/Procrustes_analysis
*/
void VO_Shape::ProcrustesAnalysis( const VO_Shape& ref, float &scale, std::vector<float>& angles, cv::Mat_<float>& translation )
{
    // move this to origin
    translation = this->CenterOfGravity( );
    this->Translate( -translation );

    // 2-norm = 1
    scale = this->GetShapeNorm();
    this->Scale( 1.0f/scale );

    // align rotation between this and ref
	VO_Shape refCpy( ref );
	cv::Mat_<float> center = refCpy.CenterOfGravity( );
    refCpy.Translate( -center );
	float norm = refCpy.GetShapeNorm();
    refCpy.Scale( 1.0f/norm );

	angles = this->GetRotation( refCpy );
    this->Rotate( angles );
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief	    Inverse Proscrustes Analysis
 * @param	    scale			input parameter - scale value
 * @param	    angles			input parameter - rotation angles, from ref to this
 * @param	    translation	    input parameter - translation in both X, Y directions
 * @return	    void
 * @note       	http://en.wikipedia.org/wiki/Procrustes_analysis
*/
void VO_Shape::InverseProcrustesAnalysis( const float& scale, const std::vector<float>& angles, const cv::Mat_<float>& translation )
{
    // rotation back
    this->Rotate(-angles);

    // 2-norm back
    this->Scale(scale);

    // COG back
    this->Translate(translation);
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief	    Global shape normalization -- refer to "AAM Revisited equation (42)"
 * @param		iShape		Input -- the input shape
 * @param		oShape		Output -- the output shape after global shape normalization
 * @param   	t         	Input -- parameters required for global shape normalization, rigid variance, refer to "AAM Revisited equation (42)"
 * @return		void
 * @note       	http://en.wikipedia.org/wiki/Procrustes_analysis
*/
void VO_Shape::GlobalShapeNormalization2D(const VO_Shape& iShape, VO_Shape& oShape, const cv::Mat_<float>& q)
{
    unsigned int NbOfPoints = iShape.GetNbOfPoints();
    float x, y;
	float a = q(0, 0) + 1;
	float b = q(0,1);
	float tx = q(0,2);
	float ty = q(0,3);

    for(unsigned int i = 0; i < NbOfPoints; ++i)
    {
		x = iShape(0,i);
		y = iShape(1,i);
        oShape(0, i) = a*x-b*y+tx;
		oShape(1, i) = b*x+a*y+ty;
    }
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief	    Global shape normalization -- refer to "AAM Revisited equation (42)"
 * @param   	t         	Input -- parameters required for global shape normalization, rigid variance, refer to "AAM Revisited equation (42)"
 * @return		void
 * @methods  - 1) three points' pairs are used to calculate affine transform
 *           - 2) use my own align transform - COG -> rotation -> scaling...
 *           - 3) SVD:  Y = AX
 *                x'     a00 a01 a02     x
 *               (y') = (a10 a11 a12) * (y) ,
 *                1      a20 a21 a22     1
 *               where  a00 = cos(theta), a01 = -sin(theta)
 *                      a10 = sin(theta), a11 = cons(theta)
 *                      a02 = tx, a12 = ty
 *                      a20 = a21 = 0; a22 = 1
 *            However, the above values are not guaranteed during calculation
 * @note       	http://en.wikipedia.org/wiki/Procrustes_analysis
 * @ref			AAM Revisited (42) (44) a=q0, b=q1, tx=q2, ty=q3
*/
void VO_Shape::GlobalShapeNormalization2D(const cv::Mat_<float>& q)
{
	VO_Shape tmp(*this);
    unsigned int NbOfPoints = this->m_MatShape.cols;
    float x, y;
	float a = q(0, 0) + 1;
	float b = q(0,1);
	float tx = q(0,2);
	float ty = q(0,3);
	
    for(unsigned int i = 0; i < NbOfPoints; ++i)
    {
		x = tmp(0,i);
		y = tmp(1,i);
        this->m_MatShape(0, i) = a*x-b*y+tx;
        this->m_MatShape(1, i) = b*x+a*y+ty;
    }
}


/**
 * @author	    JIA Pei
 * @version		2010-05-07
 * @brief	    Global shape normalization -- refer to "AAM Revisited equation (42)"
 * @param		scale			Input -- for scaling
 * @param		angles			Input -- for rotation
 * @param		translation		Input -- for translation
 * @return		void
*/
void VO_Shape::GlobalShapeNormalization2D(const VO_Shape& iShape, VO_Shape& oShape, float scale, const std::vector<float>& angles, const cv::Mat_<float>& translation)
{
	oShape.clone(iShape);
	oShape.GlobalShapeNormalization2D(scale, angles, translation);
}


/**
 * @author	    JIA Pei
 * @version		2010-05-07
 * @brief	    Global shape normalization -- refer to "AAM Revisited equation (42)"
 * @param		scale			Input -- for scaling
 * @param		angles			Input -- for rotation
 * @param		translation		Input -- for translation
 * @return		void
*/
void VO_Shape::GlobalShapeNormalization2D(float scale, const std::vector<float>& angles, const cv::Mat_<float>& translation)
{
	this->Scale(scale);
	this->Rotate( angles );
	this->Translate(translation);
}


/**
 * @author	    JIA Pei
 * @version		2010-05-07
 * @brief	    Similarity transform to Global shape normalization -- refer to "AAM Revisited equation (42) (44)"
				 Cootes' "Statistical Models of Appearance for Computer Vision" page 45
				 (s, theta, tx, ty) ->( sx, sy, tx, ty)
 * @param		scale			Input -- for scaling
 * @param		angles			Input -- for rotation, a 1*1 std::vector
 * @param		translation		Input -- for translation, a 2*1 column std::vector
 * @param		q				Output -- global shape normalization std::vector, a 1*4 row std::vector
 * @return		void
*/
void VO_Shape::SimilarityTrans2GlobalShapeNormalization(float scale,
                                                        const std::vector<float>& angles,
														const cv::Mat_<float>& translation,
														cv::Mat_<float>& q)
{
	q = cv::Mat_<float>::zeros(1,4);
	q(0,0) = scale*cos( angles[0] ) - 1.0f;
	q(0,1) = scale*sin( angles[0] );
	q(0,2) = translation(0,0);
	q(0,3) = translation(1,0);
}


/**
 * @author	    JIA Pei
 * @version		2010-05-07
 * @brief	    Global shape normalization 2 similarity transform -- refer to "AAM Revisited equation (42) (44)"
 * @param		scale			Input -- for scaling
 * @param		angles			Input -- for rotation
 * @param		translation		Input -- for translation
 * @param		q				Output -- global shape normalization std::vector, a 1*4 row std::vector
 * @return		void
*/
void  VO_Shape::GlobalShapeNormalization2SimilarityTrans(	const cv::Mat_<float>& q,
															float& scale,
                                                            std::vector<float>& angles,
															cv::Mat_<float>& translation )
{
	scale = sqrt ( (1.0f + q(0,0)) * (1.0f + q(0,0)) + q(0,1) * q(0,1) );		// scale
	angles.resize(1);
	angles[0] = (float) atan2( (float)q(0,1), (float)(1.0 + q(0,0)) );			// rotation
	translation = cv::Mat_<float>::zeros(2,1);
	translation(0,0) = q(0,2);
	translation(1,0) = q(0,3);
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate min value in all directions
 * @return	    min value in all directions
*/
cv::Mat_<float> VO_Shape::Min() const
{
    unsigned int NbOfDim = this->m_MatShape.rows;
	cv::Mat_<float> minVals = cv::Mat_<float>::zeros(NbOfDim, 1);
	double minVal = 0; 
	for(unsigned int i = 0; i < NbOfDim; i++)
	{
        cv::minMaxLoc(this->m_MatShape.row(i), &minVal, 0, 0, 0);
		minVals(i, 0) = minVal;
	}

    return minVals;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate min value in X direction
 * @return	    min value in X direction
*/
float VO_Shape::MinX() const
{
	double minVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(0);
	cv::minMaxLoc(oneRow, &minVal, 0, 0, 0);

    return minVal;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate min value in Y direction
 * @return	    min value in Y direction
*/
float VO_Shape::MinY() const
{
	double minVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(1);
	cv::minMaxLoc(oneRow, &minVal, 0, 0, 0);

    return minVal;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate min value in Z direction
 * @return	    min value in Y direction
*/
float VO_Shape::MinZ() const
{
	double minVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(2);
	cv::minMaxLoc(oneRow, &minVal, 0, 0, 0);

    return minVal;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate max value in all directions
 * @return	    max value in all directions
*/
cv::Mat_<float> VO_Shape::Max() const
{
    unsigned int NbOfDim = this->m_MatShape.rows;
	cv::Mat_<float> maxVals = cv::Mat_<float>::zeros(NbOfDim, 1);
	double maxVal = 0; 
	for(unsigned int i = 0; i < NbOfDim; i++)
	{
        cv::minMaxLoc(this->m_MatShape.row(i), 0, &maxVal, 0, 0);
		maxVals(i, 0) = maxVal;
	}

    return maxVals;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate max value in X direction
 * @return	    max value in X direction
*/
float VO_Shape::MaxX() const
{
	double maxVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(0);
	cv::minMaxLoc(oneRow, 0, &maxVal, 0, 0);

    return maxVal;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate max value in Y direction
 * @return	    max value in Y direction
*/
float VO_Shape::MaxY() const
{
	double maxVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(1);
	cv::minMaxLoc(oneRow, 0, &maxVal, 0, 0);

    return maxVal;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate max value in Z direction
 * @return	    max value in Y direction
*/
float VO_Shape::MaxZ() const
{
	double maxVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(2);
	cv::minMaxLoc(oneRow, 0, &maxVal, 0, 0);

    return maxVal;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate mean value in X direction
 * @return	    mean value in X direction
*/
cv::Mat_<float> VO_Shape::Mean() const
{
    unsigned int NbOfDim = this->m_MatShape.rows;
	cv::Mat_<float> meanVals = cv::Mat_<float>::zeros(NbOfDim, 1);
	for(unsigned int i = 0; i < NbOfDim; i++)
	{
        meanVals(i, 0) = cv::mean(this->m_MatShape.row(i)).val[0];
	}

    return meanVals;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate mean value in X direction
 * @return	    mean value in X direction
*/
float VO_Shape::MeanX() const
{
    return cv::mean(this->m_MatShape.row(0)).val[0];
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate mean value in Y direction
 * @return	    mean value in Y direction
*/
float VO_Shape::MeanY() const
{
    return cv::mean(this->m_MatShape.row(1)).val[0];
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate mean value in Z direction
 * @return	    mean value in Z direction
*/
float VO_Shape::MeanZ() const
{
    return cv::mean(this->m_MatShape.row(2)).val[0];
}




/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate max value in all directions
 * @return	    max value in all directions
*/
void VO_Shape::MinMaxX(double* minX, double* maxX) const
{
	double minVal = 0, maxVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(0);
	cv::minMaxLoc(oneRow, minX, maxX, 0, 0);
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate max value in all directions
 * @return	    max value in all directions
*/
void VO_Shape::MinMaxY(double* minY, double* maxY) const
{
	double minVal = 0, maxVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(1);
	cv::minMaxLoc(oneRow, minY, maxY, 0, 0);
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Calculate max value in all directions
 * @return	    max value in all directions
*/
void VO_Shape::MinMaxZ(double* minZ, double* maxZ) const
{
	double minVal = 0, maxVal = 0;
    cv::Mat_<float> oneRow = this->m_MatShape.row(2);
	cv::minMaxLoc(oneRow, minZ, maxZ, 0, 0);
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Get a subshape from shape
 * @param		iPtIdx -- indexes of point list
 * @return	    the subshape
*/
VO_Shape VO_Shape::GetSubShape(const std::vector<unsigned int>& iPtIdx) const
{
	unsigned int NbOfSub = iPtIdx.size();
    cv::Mat_<float> oShape = cv::Mat_<float>::zeros(this->m_MatShape.rows, NbOfSub);
	cv::Mat_<float> tmpCol;
	unsigned int count = 0;
	for(unsigned int i = 0; i < NbOfSub; i++)
	{
		tmpCol = oShape.col(count++);
        this->m_MatShape.col(iPtIdx[i]).copyTo(tmpCol);
	}
	return oShape;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Combine two shapes
 * @param		shape1 -- shape 1
 * @param		shape2 -- shape 2
 * @return	    the point
*/
VO_Shape VO_Shape::Combine2Shapes(const VO_Shape& shape1, const VO_Shape& shape2)
{
    unsigned int NbOfPoints1 = shape1.GetNbOfPoints();
    unsigned int NbOfPoints2 = shape2.GetNbOfPoints();
	unsigned int NbOfDim1 = shape1.GetNbOfDim();
	unsigned int NbOfDim2 = shape2.GetNbOfDim();
    if( (NbOfPoints1==0 && NbOfPoints2 == 0) || (NbOfDim1==0 && NbOfDim2==0) )
		return cv::Mat_<float>();

    if(NbOfPoints1!=0 && NbOfPoints2 != 0)
	{
		if(NbOfDim1 != NbOfDim2)
		{
            std::cerr <<"VO_Shape " << "The 2 shapes must have the same dim for combination" << std::endl;
			exit(1);
		}
	}

	unsigned int NbOfDim = NbOfDim1==0? NbOfDim2:NbOfDim1;
    unsigned int NbOfPoints = NbOfPoints1 + NbOfPoints2;
    cv::Mat_<float> res = cv::Mat_<float>::zeros(NbOfDim, NbOfPoints);

	for(unsigned int i = 0; i < NbOfDim; i++)
	{
        for(unsigned int j = 0; j < NbOfPoints1; j++)
		{
			res(i, j) = shape1(i,j);
		}
		
        for(unsigned int j = 0; j < NbOfPoints2; j++)
		{
            res(i, j+shape1.GetNbOfPoints() ) = shape2(i,j);
		}
	}

	return res;
}


/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Get a point in 2D
 * @param		idx -- indexes of point list
 * @return	    the point
*/
cv::Point2f VO_Shape::GetA2DPoint(unsigned int idx) const
{
	cv::Point2f res;
	unsigned int count = 0;
	switch(idx)
	{
		case LEFTMOST:
		{
			float xmin = FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(0, i) < xmin)
				{
                    xmin = m_MatShape(0, i);
					count = i;
				}
			}
		}
		break;
		case RIGHTMOST:
		{
			float xmax = -FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(0, i) > xmax)
				{
                    xmax = m_MatShape(0, i);
					count = i;
				}
			}
		}
		break;
		case TOPMOST:
		{
			float ymin = FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(1, i) < ymin)
				{
                    ymin = m_MatShape(1, i);
					count = i;
				}
			}
		}
		break;
		case BOTTOMMOST:
		{
			float ymax = -FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(1, i) > ymax)
				{
                    ymax = m_MatShape(1, i);
					count = i;
				}
			}
		}
		break;
		case CENTER:
		{
			cv::Mat_<float> mean = this->Mean();
			res.x = mean(0,0);
			res.y = mean(1,0);
			return res;
		}
		break;
		default:
		{
			count = idx;
		}
		break;
	}
	
    res.x = this->m_MatShape.col(count)(0,0);
    res.y = this->m_MatShape.col(count)(1,0);
	return res;
}
				

/**
 * @author	    JIA Pei
 * @version		2010-02-07
 * @brief		Get a point in 3D
 * @param		idx -- indexes of point list
 * @return	    cv::Point3f		the point
*/
cv::Point3f VO_Shape::GetA3DPoint(unsigned int idx) const
{
	cv::Point3f res;
	unsigned int count = 0;
	switch(idx)
	{
		case LEFTMOST:
		{
			float xmin = FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(0, i) < xmin)
				{
                    xmin = m_MatShape(0, i);
					count = i;
				}
			}
		}
		break;
		case RIGHTMOST:
		{
			float xmax = -FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(0, i) > xmax)
				{
                    xmax = m_MatShape(0, i);
					count = i;
				}
			}
		}
		break;
		case TOPMOST:
		{
			float ymin = FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(1, i) < ymin)
				{
                    ymin = m_MatShape(1, i);
					count = i;
				}
			}
		}
		break;
		case BOTTOMMOST:
		{
			float ymax = -FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(1, i) > ymax)
				{
                    ymax = m_MatShape(1, i);
					count = i;
				}
			}
		}
		break;
		case INNERMOST:
		{
			float zmin = FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(2, i) < zmin)
				{
                    zmin = m_MatShape(2, i);
					count = i;
				}
			}
		}
		break;
		case OUTERMOST:
		{
			float zmax = -FLT_MAX;
            for(unsigned int i = 0; i < m_MatShape.cols; i++)
			{
                if(m_MatShape(2, i) > zmax)
				{
                    zmax = m_MatShape(2, i);
					count = i;
				}
			}
		}
		break;
		case CENTER:
		{
			cv::Mat_<float> mean = this->Mean();
			res.x = mean(0,0);
			res.y = mean(1,0);
			res.z = mean(2,0);
			return res;
		}
		break;
		default:
		{
			count = idx;
		}
		break;
	}
	
    res.x = this->m_MatShape.col(count)(0,0);
    res.y = this->m_MatShape.col(count)(1,0);
    res.z = this->m_MatShape.col(count)(2,0);
	return res;
}


/**
* @author     	JIA Pei
* @version    	2010-09-17
* @brief      	HausDorff Distance between 2 shapes
* @param      	iShape     			input		the concerned point
*/
double VO_Shape::HausDorffDist(const VO_Shape& iShape)
{
    unsigned int NbOfPoints		= this->GetNbOfPoints();
	unsigned int NbOfDim		= this->GetNbOfDim();

	double maxDistanceAB		= DBL_MIN;
    for(unsigned int i = 0; i < NbOfPoints; ++i )
	{
		double minDistance		= DBL_MAX;
		double tempDistance		= 0.0;

        for(unsigned int j = 0; j < NbOfPoints; ++j )
		{
			tempDistance		= 0.0;

			for(unsigned int k = 0; k < NbOfDim; ++k )
			{
                tempDistance	+= pow( this->m_MatShape(k, i) - iShape.m_MatShape(k, j), 2.0f );
			}
			tempDistance		= sqrt(tempDistance);
			minDistance			= minDistance<tempDistance?minDistance:tempDistance;
		}
		maxDistanceAB			= maxDistanceAB>minDistance?maxDistanceAB:minDistance;
	}

	double maxDistanceBA		= DBL_MIN;
    for(unsigned int i = 0; i < NbOfPoints; ++i )
	{
		double minDistance		= DBL_MAX;
		double tempDistance		= 0.0;

        for(unsigned int j = 0; j < NbOfPoints; ++j )
		{
			tempDistance		= 0.0;

			for(unsigned int k = 0; k < NbOfDim; ++k )
			{
                tempDistance	+= pow( iShape.m_MatShape(k, i) - this->m_MatShape(k, j), 2.0f );
			}
			tempDistance		= sqrt(tempDistance);
			minDistance			= minDistance<tempDistance?minDistance:tempDistance;
		}
		maxDistanceBA			= maxDistanceBA>minDistance?maxDistanceBA:minDistance;
	}

	return maxDistanceAB>maxDistanceBA?maxDistanceAB:maxDistanceBA;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-17
 * @brief      	Judge whether one point is within a shape
 * @param      	pt        			input		the concerned point
 * @param		triangles			input		all triangles composing the shape
 * @param		int					return the index of triangle containing pt
*/
int VO_Shape::IsPointInShape(const cv::Point2f& pt, const std::vector<VO_Triangle2DStructure>& triangles) const
{
    std::vector<VO_Triangle2DStructure> shapeTriangles = this->GetTriangle2DStructure(triangles);
    return VO_Triangle2DStructure::IsPointInTriangles(pt, shapeTriangles);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-17
 * @brief      	Get VO_Triangle2DStructure specific for this shape
 * @param		triangles							Input		all triangles composing the shape
 * @return		std::vector<VO_Triangle2DStructure>		the index of triangle containing pt
*/
std::vector<VO_Triangle2DStructure> VO_Shape::GetTriangle2DStructure(const std::vector<VO_Triangle2DStructure> triangles) const
{
	unsigned int NbOfTriangles  = triangles.size();
    std::vector<VO_Triangle2DStructure> shapeTriangles = triangles;
    std::vector<unsigned int> vertexIdx;
	
	for(unsigned int i = 0; i < NbOfTriangles; ++i)
	{
		vertexIdx = triangles[i].GetVertexIndexes();
        shapeTriangles[i].m_MatShape(0,0) 	= this->m_MatShape(0, vertexIdx[0]);
        shapeTriangles[i].m_MatShape(1,0) 	= this->m_MatShape(1, vertexIdx[0]);
        shapeTriangles[i].m_MatShape(0,1) 	= this->m_MatShape(0, vertexIdx[1]);
        shapeTriangles[i].m_MatShape(1,1) 	= this->m_MatShape(1, vertexIdx[1]);
        shapeTriangles[i].m_MatShape(0,2) 	= this->m_MatShape(0, vertexIdx[2]);
        shapeTriangles[i].m_MatShape(1,2) 	= this->m_MatShape(1, vertexIdx[2]);
		// explained by JIA Pei, m_dD of shapeTriangles[i] is not calculated/required here in this function
	}
	return shapeTriangles;
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      Write shape into file "fn"
 * @param      fn			Output	- the file name
 * @param      shape       	Input	- save annotation data from shape data structure to file
*/
void VO_Shape::ExportShape(const std::string& fn, const VO_Shape& shape)
{
    std::fstream fp(fn.c_str(), std::ios::out);
    fp << shape << std::endl;
    fp.close();fp.clear();
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      Write shape into file "fn"
 * @param      fn        	Output	- the file name
 * @param      shapeMat		Input	- save annotation data from mat shape to file
*/
void VO_Shape::ExportShape(const std::string& fn, const cv::Mat_<float>& shapeMat)
{
    std::fstream fp(fn.c_str(), std::ios::out);
    fp << shapeMat << std::endl;
    fp.close();fp.clear();
}

