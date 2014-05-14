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
#include <algorithm>
#include <numeric>

#include "VO_Texture.h"
#include "VO_CVCommon.h"


std::ostream& operator<<(std::ostream& os, const VO_Texture& texture)
{
    os << texture.m_MatTexture;
    return os;
}


std::istream& operator>>(std::istream &is, VO_Texture& texture)
{
    is >> texture.m_MatTexture;
    return is;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator= overloading, similar to copy constructor
 * @param      	iTexture		The input texture
 * @return     	VO_Texture&
 */
VO_Texture& VO_Texture::operator=(const VO_Texture& iTexture)
{
    this->CopyData (iTexture);
    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator= overloading, similar to copy constructor
 * @param      	iTexture		The input texture
 * @return     	VO_Texture&
 */
VO_Texture& VO_Texture::operator=(const cv::Mat_<float>& iTexture)
{
    iTexture.copyTo(m_MatTexture);
    return *this;
}


/**
 * @author    	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator= overloading, similar to copy constructor
 * @param      	value	assign all values in VO_Texture to value
 * @return     	VO_Texture&
 */
VO_Texture& VO_Texture::operator=(float value)
{
    m_MatTexture = value;
    return *this;
}


/**
 * @author     	JIA Pei
 * @version   	2010-02-07
 * @brief     	operator+ overloading, shift one AAM texture by value
 * @param     	value
 * @return    	VO_Texture
 */
VO_Texture VO_Texture::operator+(float value)
{
    VO_Texture res(*this);
    res.m_MatTexture += value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+= overloading, add value to this AAM texture 
 * @param      	value
 * @return     	VO_Texture&
*/
VO_Texture& VO_Texture::operator+=(float value)
{
    m_MatTexture += value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+ overloading, add two AAM texture to one 
 * @param      	iTexture      		the added AAM texture
 * @return     	VO_Texture
*/
VO_Texture VO_Texture::operator+(const VO_Texture &iTexture)
{
    VO_Texture res(*this);
    res.m_MatTexture += iTexture.m_MatTexture;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+= overloading, add the input AAM texture to this AAM texture
 * @param      	iTexture      	the added AAM texture
 * @return     	VO_Texture&
*/
VO_Texture& VO_Texture::operator+=(const VO_Texture &iTexture)
{
    this->m_MatTexture += iTexture.m_MatTexture;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator- overloading, shift one AAM texture by -value
 * @param      	value
 * @return     	VO_Texture
*/
VO_Texture VO_Texture::operator-(float value)
{
    VO_Texture res(*this);
    res.m_MatTexture -= value;
	
    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator-= overloading, subtract value from this AAM texture 
 * @param      	value
 * @return     	VO_Texture&
*/
VO_Texture& VO_Texture::operator-=(float value)
{
    this->m_MatTexture -= value;

	return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator- overloading, subtract one texture from another
 * @param      	iTexture      	the subtracted AAM texture
 * @return     	VO_Texture
*/
VO_Texture VO_Texture::operator-(const VO_Texture &iTexture)
{
    VO_Texture res(*this);
    res.m_MatTexture -= iTexture.m_MatTexture;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator-= overloading, subtract the input AAM texture from this AAM texture
 * @param      	iTexture      	the subtracted AAM texture
 * @return     	VO_Texture&
*/
VO_Texture& VO_Texture::operator-=(const VO_Texture &iTexture)
{
    this->m_MatTexture -= iTexture.m_MatTexture;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, scale one texture by value
 * @param      	value      		scale size
 * @return     	VO_Texture
*/
VO_Texture VO_Texture::operator*(float value)
{
    VO_Texture res(*this);
    res.m_MatTexture *= value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator-= overloading, scale this AAM texture by value
 * @param      	value      		scale size
 * @return     	VO_Texture&
*/
VO_Texture& VO_Texture::operator*=(float value)
{
    this->m_MatTexture *= value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, scale one texture by value
 * @param      	value      		scale size
 * @return     	VO_Texture
*/
VO_Texture VO_Texture::operator*(const VO_Texture& iTexture)
{
	VO_Texture res(*this);
    res.m_MatTexture = res.m_MatTexture.mul(iTexture.m_MatTexture);

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator-= overloading, scale this AAM texture by value
 * @param      	value      		scale size
 * @return     	VO_Texture&
*/
VO_Texture& VO_Texture::operator*=(const VO_Texture& iTexture)
{
    this->m_MatTexture = this->m_MatTexture.mul(iTexture.m_MatTexture);

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/ overloading, scale a texture
 * @param      	value      		1.0/value = scale size
 * @return     	VO_Texture
*/
VO_Texture VO_Texture::operator/(float value)
{
    if( fabs(value) <= FLT_MIN )
    {
        std::cerr << "Divided by zero!" << std::endl;
        exit(EXIT_FAILURE);
    }

    VO_Texture res(*this);
    res.m_MatTexture /= value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/= overloading, scale this texture with input float value
 * @param      	value      		1.0/value = the scaled value
 * @return     	VO_Texture&
*/
VO_Texture& VO_Texture::operator/=(float value)
{
    if( fabs(value) <= FLT_MIN )
    {
        std::cerr << "Divided by zero!" << std::endl;
        exit(EXIT_FAILURE);
    }

    this->m_MatTexture /= value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-06
 * @brief      	operator/ overloading, scale a shape
 * @param      	iTexture      	for element-wise division
 * @return     	VO_Texture
*/
VO_Texture VO_Texture::operator/(const VO_Texture& iTexture)
{
    for(unsigned int i = 0; i < iTexture.m_MatTexture.rows; i++)
	{
        for(unsigned int j = 0; j < iTexture.m_MatTexture.cols; j++)
		{
            if( fabs(iTexture.m_MatTexture(i,j)) <= FLT_MIN )
			{
                std::cerr << "Divided by zero!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

    VO_Texture res(*this);
    res.m_MatTexture /= iTexture.m_MatTexture;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-06
 * @brief      	operator/= overloading, scale this shape with input float value
 * @param      	iTexture      	for element-wise division
 * @return     	VO_Texture&
*/
VO_Texture& VO_Texture::operator/=(const VO_Texture& iTexture)
{
    for(unsigned int i = 0; i < iTexture.m_MatTexture.rows; i++)
	{
        for(unsigned int j = 0; j < iTexture.m_MatTexture.cols; j++)
		{
            if( fabs(iTexture.m_MatTexture(i,j)) <= FLT_MIN )
			{
                std::cerr << "Divided by zero!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

    this->m_MatTexture /= iTexture.m_MatTexture;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator() overloading, obtain the texture value at row and col
 * @param      	row      	input	- row index
 * @param      	col      	input	- col index
 * @return     	float&
*/
float&  VO_Texture::operator() (unsigned row, unsigned col)
{
    if ( row >= m_MatTexture.rows || col >= m_MatTexture.cols )
        std::cerr << "cv::Matrix subscript out of bounds" << std::endl;
    return this->m_MatTexture(row, col);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator() overloading, obtain the texture value at row and col
 * @param      	row      	input	- row index
 * @param      	col      	input	- col index
 * @return     	float&
*/
float  VO_Texture::operator() (unsigned row, unsigned col) const
{
    if ( row >= m_MatTexture.rows || col >= m_MatTexture.cols )
        std::cerr << "cv::Matrix subscript out of bounds" << std::endl;
    return this->m_MatTexture(row, col);
}
	

/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, dot product of two AAM textures
 * @param      	iTexture     	AAM texture to be dot producted
 * @return     	float       	dot product
*/
float VO_Texture::dot(const VO_Texture& iTexture)
{
    return this->m_MatTexture.dot(iTexture.m_MatTexture);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	resize the matrix
 * @param      	rows
 * @param      	cols
 * @return     	void
*/
void VO_Texture::Resize(unsigned int rows, unsigned int cols)
{
    this->m_MatTexture.release();
    this->m_MatTexture = cv::Mat_<float>::zeros(rows, cols);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-20
 * @brief      	centralize the texture, average to 0
 * @param      	none
 * @return     	void
*/
void VO_Texture::Centralize()
{
    float avg = cv::mean(this->m_MatTexture).val[0];
    this->m_MatTexture -= avg;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	scale 
 * @param      	s      scale this AAM texture by s
 * @return     	VO_Texture
 */
void VO_Texture::Scale( float s)
{
    this->m_MatTexture *= s;
}


/**
 * @author     	JIA Pei
 * @version    	2010-04-07
 * @brief      	shift 
 * @param      	s      shift this AAM texture by s
 * @return     	VO_Texture
 */
void VO_Texture::Shift( float s)
{
    this->m_MatTexture += s;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Normalize this AAM texture
 * @return     	void
*/
void VO_Texture::Normalize()
{
	this->Centralize();
	
    float norm = this->GetTextureNorm();

    this->Scale( 1.0f/norm );
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	calculate 2-norm of AAM texture
 * @return     	2-norm of AAM texture
*/
float VO_Texture::GetStandardizedTextureNorm() const
{
	VO_Texture tmp(*this);
    tmp.Centralize();
	
	return tmp.GetTextureNorm();
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	calculate 2-norm of AAM texture
 * @return     	2-norm of AAM texture
*/
float VO_Texture::GetTextureNorm() const
{
    return norm(this->m_MatTexture);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Clamp the texture, constrain between infimum and supremum
 * @param 		inf			Input	-- infimum
 * @param		sup			Input	-- supremum
 * @return     	void
*/
void VO_Texture::Clamp(float inf, float sup)
{
    for(unsigned int i = 0; i < m_MatTexture.rows; ++i)
	{
        for(unsigned int j = 0; j < m_MatTexture.cols; ++j)
		{
            if( m_MatTexture(i, j) < inf)
                m_MatTexture(i, j) = inf;
            else if (m_MatTexture(i, j) > sup)
                m_MatTexture(i, j) = sup;
		}			
	}
}

