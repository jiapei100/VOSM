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


#ifndef __VO_TRIANGLE2D_H__
#define __VO_TRIANGLE2D_H__

#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "VO_Shape.h"
#include "VO_Common.h"


/** 
 * @author		JIA Pei
 * @brief		A shape specifically to describe a 2D triangle. 
 */
class VO_Triangle2D : public VO_Shape
{
protected:
    /** Cached denominator for later Jacobian calculation */
    float						m_dD;

    /** private function to calculate cached denominator */
    float 						Calc_dD()
    {
								if(this->m_MatShape.cols != 3)
                                    std::cerr << "This is not a triangle!" << std::endl
                                        << "Please ensure the shape has 3 columns" << std::endl;
								if(this->m_MatShape.rows != 2)
                                    std::cerr << "This triangle is not in 2D!" << std::endl;

								float x1, x2, x3, y1, y2, y3;
	
								x1 = this->m_MatShape(0,0);
								x2 = this->m_MatShape(0,1);
								x3 = this->m_MatShape(0,2);
								y1 = this->m_MatShape(1,0);
								y2 = this->m_MatShape(1,1);
								y3 = this->m_MatShape(1,2);
	
								return (+x2*y3-x2*y1-x1*y3-x3*y2+x3*y1+x1*y2);
    }

public:
	enum { COUNTER_CLOCKWISE = 0, CLOCKWISE = 1};

    /** Default constructor to create a VO_Triangle2D object */
    VO_Triangle2D() 			{this->m_MatShape = cv::Mat_<float>::zeros(2,3); this->m_dD = 0.0f;}

    /** Constructor to create a VO_Triangle2D object with three coordinate vertexes in std::vector format */
    VO_Triangle2D(const std::vector<cv::Point2f>& iVertexes):VO_Shape(iVertexes)
    {
								if(this->m_MatShape.cols !=3)
                                    std::cerr << "This is not a triangle!" << std::endl;
								if(this->m_MatShape.rows !=2)
                                    std::cerr << "This triangle is not 2D!" << std::endl;
								this->m_dD 			= this->Calc_dD ();
	}
	
	/** Constructor to create a VO_Triangle2D object with three coordinate vertexes in Mat_<float> format */
    VO_Triangle2D(const cv::Mat_<float>& iVertexes):VO_Shape(iVertexes)
    {
								if(this->m_MatShape.cols !=3)
                                    std::cerr << "This is not a triangle!" << std::endl;
								if(this->m_MatShape.rows !=2)
                                    std::cerr << "This triangle is not 2D!" << std::endl;
								this->m_dD	= this->Calc_dD ();
	}

    /** Destructor */
	virtual ~VO_Triangle2D()	{}
	
    /** operator= overloading, similar to copy constructor */
    VO_Triangle2D&      		operator=(const VO_Triangle2D& s)
    {
								this->CopyData(s);
								this->m_dD	= s.GetdD();
								return (*this);
    }

	/** whether the triangle vertexes are list in clockwise or counter-clockwise */
	int 						determinant( )
	{
								float determ = (this->m_MatShape(0,1) - this->m_MatShape(0,0)) 
											* (this->m_MatShape(1,2) - this->m_MatShape(1,0)) 
											- (this->m_MatShape(0,2) - this->m_MatShape(0,0)) 
											* (this->m_MatShape(1,1) - this->m_MatShape(1,0));
								if (determ <= 0.0)
									return COUNTER_CLOCKWISE;
								else
									return CLOCKWISE;
	}

    /** Get cached denominator of this triangle */
    float                   	GetdD() const { return this->m_dD;}

    /** Set cached denominator for this triangle */
    void                    	SetdD(float idD) { this->m_dD = idD;}
};

#endif  // __VO_TRIANGLE2D_H__

