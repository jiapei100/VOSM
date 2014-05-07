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
*                   4) I. cv::Matthews and S. Baker. Active appearance models revisited.                *
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


#include "VO_Profile.h"
#include "VO_CVCommon.h"


ostream& operator<<(ostream& os, const VO_Profile& profile)
{
    os << profile.m_MatProf;
    return os;
}


istream& operator>>(istream &is, VO_Profile& profile)
{
    is >> profile.m_MatProf;
    return is;
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      operator= overloading, similar to copy constructor
 * @param      iProfile			The input profile
 * @return     VO_Profile&
*/
VO_Profile& VO_Profile::operator=(const VO_Profile& iProfile)
{
    this->CopyData (iProfile);
    return *this;
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      operator= overloading, similar to copy constructor
 * @param      iProfile			The input profile
 * @return     VO_Profile&
*/
VO_Profile& VO_Profile::operator=(const cv::Mat_<float>& iProfile)
{
    iProfile.copyTo(m_MatProf);
    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator= overloading, similar to copy constructor
 * @param      	value			assign all values in VO_Profile to value
 * @return     	VO_Profile&
*/
VO_Profile& VO_Profile::operator=(float value)
{
    m_MatProf = value;
    return *this;
}


/**
  * @author     JIA Pei
  * @version    2010-02-07
  * @brief      operator+ overloading, shift one AAM shape by value
  * @param      value
  * @return     VO_Profile
*/
VO_Profile VO_Profile::operator+(float value)
{
    VO_Profile res(*this);
    res.m_MatProf += value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+= overloading, add value to this profile
 * @param      	value
 * @return    	VO_Profile&
*/
VO_Profile& VO_Profile::operator+=(float value)
{
    m_MatProf += value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+ overloading, add two profiles to one
 * @param      	iProfile      the added profile
 * @return     	VO_Profile
*/
VO_Profile VO_Profile::operator+(const VO_Profile& iProfile)
{
    VO_Profile res(*this);
    res.m_MatProf += iProfile.m_MatProf;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator+= overloading, add the input profile to this profile
 * @param      	iProfile      the added profile
 * @return     	VO_Profile&
*/
VO_Profile& VO_Profile::operator+=(const VO_Profile& iProfile)
{
    this->m_MatProf += iProfile.m_MatProf;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator- overloading, shift one profile by -value
 * @param      	value
 * @return     	VO_Profile
*/
VO_Profile VO_Profile::operator-(float value)
{
    VO_Profile res(*this);
    res.m_MatProf -= value;
	
    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator-= overloading, subtract value from this profile
 * @param      	value
 * @return     	VO_Profile&
*/
VO_Profile& VO_Profile::operator-=(float value)
{
    this->m_MatProf -= value;

	return *this;
}


/**
  * @author     JIA Pei
  * @version    2010-02-07
  * @brief      operator- overloading, subtract one profile from another
  * @param      iProfile      the subtracted profile
  * @return     VO_Profile
*/
VO_Profile VO_Profile::operator-(const VO_Profile& iProfile)
{
    VO_Profile res(*this);
    res.m_MatProf -= iProfile.m_MatProf;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator-= overloading, subtract the input profile from this profile
 * @param      	iProfile      the subtracted profile
 * @return     	VO_Profile&
*/
VO_Profile& VO_Profile::operator-=(const VO_Profile& iProfile)
{
    this->m_MatProf -= iProfile.m_MatProf;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, scale a profile with input float value
 * @param      	value      scale size
 * @return     	VO_Profile
*/
VO_Profile VO_Profile::operator*(float value)
{
    VO_Profile res(*this);
    res.m_MatProf *= value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator*= overloading, scale this profile with input float value
 * @param      	value
 * @return     	VO_Profile&
*/
VO_Profile& VO_Profile::operator*=(float value)
{
    this->m_MatProf *= value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, element-wise product of two profiles
 * @param      	iProfile    profile to be dot producted
 * @return     	float       dot product
*/
VO_Profile VO_Profile::operator*(const VO_Profile& iProfile)
{
	VO_Profile res(*this);
    res.m_MatProf = res.m_MatProf.mul(iProfile.m_MatProf);

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, element-wise product of two profiles
 * @param      	iProfile    profile to be dot producted
 * @return     	float       dot product
*/
VO_Profile& VO_Profile::operator*=(const VO_Profile& iProfile)
{
    this->m_MatProf = this->m_MatProf.mul(iProfile.m_MatProf);

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/ overloading, scale a profile
 * @param      	value      1.0/value = scale size
 * @return     	VO_Profile
*/
VO_Profile VO_Profile::operator/(float value)
{
    if( fabs(value) <= FLT_MIN )
    {
        std::cerr << "Divided by zero!" << std::endl;
        exit(EXIT_FAILURE);
    }

    VO_Profile res(*this);
    res.m_MatProf /= value;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/= overloading, scale this profile with input float value
 * @param      	value      1.0/value = the scaled value
 * @return     	VO_Profile&
*/
VO_Profile& VO_Profile::operator/=(float value)
{
    if( fabs(value) <= FLT_MIN )
    {
        std::cerr << "Divided by zero!" << std::endl;
        exit(EXIT_FAILURE);
    }

    this->m_MatProf /= value;

    return *this;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/ overloading, scale a profile
 * @param      	iProfile      for element-wise division
 * @return     	VO_Profile
*/
VO_Profile VO_Profile::operator/(const VO_Profile& iProfile)
{
    for(unsigned int i = 0; i < iProfile.m_MatProf.rows; i++)
	{
        for(unsigned int j = 0; j < iProfile.m_MatProf.cols; j++)
		{
            if( fabs(iProfile.m_MatProf(i,j)) <= FLT_MIN )
			{
                std::cerr << "Divided by zero!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

    VO_Profile res(*this);
    res.m_MatProf /= iProfile.m_MatProf;

    return res;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator/= overloading, scale this profile with input float value
 * @param      	iProfile      for element-wise division
 * @return     	VO_Profile&
*/
VO_Profile& VO_Profile::operator/=(const VO_Profile& iProfile)
{
    for(unsigned int i = 0; i < iProfile.m_MatProf.rows; i++)
	{
        for(unsigned int j = 0; j < iProfile.m_MatProf.cols; j++)
		{
            if( fabs(iProfile.m_MatProf(i,j)) <= FLT_MIN )
			{
                std::cerr << "Divided by zero!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

    this->m_MatProf /= iProfile.m_MatProf;

    return *this;
}



/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator() overloading, obtain the profile value at row and col
 * @param      	row      input	- row index
 * @param      	col      input	- col index
 * @return     	float&
*/
float&  VO_Profile::operator() (unsigned row, unsigned col)
{
    if ( row >= m_MatProf.rows || col >= m_MatProf.cols )
        std::cerr << "cv::Matrix subscript out of bounds" << std::endl;
    return m_MatProf.at<float>(row, col);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator() overloading, obtain the profile value at row and col
 * @param      	row      input	- row index
 * @param      	col      input	- col index
 * @return     	float&
*/
float  VO_Profile::operator() (unsigned row, unsigned col) const
{
    if ( row >= m_MatProf.rows || col >= m_MatProf.cols )
        std::cerr << "cv::Matrix subscript out of bounds" << std::endl;
    return m_MatProf.at<float>(row, col);
}
	

/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	operator* overloading, dot product of two profiles
 * @param      	iProfile    profile to be dot producted
 * @return     	float       dot product
*/
float VO_Profile::dot(const VO_Profile& iProfile)
{
    return this->m_MatProf.dot(iProfile.m_MatProf);
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      resize the matrix
 * @param      length		Input, profile length
 * @param      dim			Input, profile dim
 * @return     void
*/
void VO_Profile::Resize(unsigned int length, unsigned int dim)
{
    this->m_MatProf.release();
    this->m_MatProf = cv::Mat_<float>::zeros(length, dim);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Get a subprofile in 1 dimension, length*1
 * @param		start 			Input		start from which index
 * @param		length			Input		how long will the subprofile be
 * @return		cv::Mat_<float>		the subprofile
 */ 
cv::Mat_<float> VO_Profile::GetSubProfile(int start, unsigned int length, unsigned int dimIdx) const
{
    if(start+length > this->m_MatProf.rows)
        std::cerr << "VO_Profile  start+length is bigger than m_MatProf.rows" << std::endl;

	cv::Mat_<float> oProfile = cv::Mat_<float>::zeros(length, 1);
	for(unsigned int i = 0; i < length; i++)
	{
        oProfile(i, 0) = this->m_MatProf(i+start, dimIdx);
	}

	return oProfile;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief		Set 1 dimension Profile
 * @param		iOneDimProf 	Input		1D column std::vector, length*1
 * @return		void
 */ 
void VO_Profile::Set1DimProfile(const cv::Mat_<float>& iOneDimProf, unsigned int idx)
{
    unsigned int NbOfDim = this->m_MatProf.cols;
    unsigned int NbOfLength = this->m_MatProf.rows;
	if(idx >= NbOfDim)
	{
        std::cerr << "idx shouldn't be bigger than the dim of m_MatProf!" << std::endl;
		exit(1);
	}
	if(iOneDimProf.rows != NbOfLength)
	{
        std::cerr << "input profile length should be equal to the length of m_MatProf!" << std::endl;
		exit(1);
	}
	for(unsigned int i = 0; i < NbOfLength; i++)
	{
        this->m_MatProf(i, idx) = iOneDimProf(i, 0);
	}
}

void VO_Profile::Set1DimProfile(const VO_Profile& iOneDimProf, unsigned int idx)
{
    this->Set1DimProfile(iOneDimProf.m_MatProf, idx);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-22
 * @brief		Get ND profiles for a single landmark
 * @param		iImg 					Input	-- the input image
 * @param		ThisPoint				Input	-- the concerned point
 * @param		oProf 					Output	-- output profile in column format
 * @param		deltaX					Input	-- deltaX in some direction
 * @param		deltaY					Input	-- deltaY in some direction
 * @param		ProfileLength	Input	-- how many elements for a single profile
 * @return		void
 * @note		Using "float* oProf" is much much faster than using "VO_Profile& oProf" or "std::vector<float>"
 */
void VO_Profile::VO_Get1DProfileInMat4OneLandmark (	const cv::Mat& iImg,
                                                    const cv::Point2f& ThisPoint,
													VO_Profile& oProf,
													float deltaX, 
													float deltaY,
													unsigned int ProfileLength)
{
//static cv::Mat oImg(iImg);
//cv::Point pt1, pt2;
//int rgb = 255;
//Scalar profileColor = Scalar(rgb,rgb,rgb);
//unsigned int TheColor = 0;
	oProf = cv::Mat_<float>::zeros(ProfileLength, 1);
	
	unsigned int width 		= iImg.cols;
	unsigned int height 	= iImg.rows;
	unsigned int channels	= iImg.channels();
	
	// Emphasized by JIA Pei. k shouldn't be unsigned int in this function
	int k 					= (ProfileLength-1)/2;
    cv::Point2f normalPoint;
	
    normalPoint.x 			= ThisPoint.x + ( -k-1 ) * deltaX;
    normalPoint.y 			= ThisPoint.y + ( -k-1 ) * deltaY;

//pt1 = normalPoint;
//cv::line( tempImg, pt1, pt1, colors[TheColor%8], 5, 0, 0 );
//if(ptIdx == 84 || ptIdx == 85 || ptIdx == 86 )
//{
//cv::line( oImg, pt1, pt1, colors[TheColor%8], 5, 0, 0 );
//}

	// make sure the point is within the image, otherwise, you can't extract the pixel RGB texture
    if(normalPoint.x < FLT_EPSILON)
        normalPoint.x = 0.0f;
    else if (normalPoint.x - width + 1.0f > FLT_EPSILON)
        normalPoint.x = 2*width - 2.0f - normalPoint.x;

    if(normalPoint.y < FLT_EPSILON)
        normalPoint.y = 0.0f;
    else if(normalPoint.y - height + 1.0f > FLT_EPSILON)
        normalPoint.y = 2*height - 2.0f - normalPoint.y;

	if(channels == 1)
	{
		float gray_prev 	= 0.0f;
		float gray_curr 	= 0.0f;

        VO_TextureModel::VO_CalcSubPixelTexture ( normalPoint.x, normalPoint.y, iImg, &gray_prev );

		for (int i = -k; i <= k; ++i)
		{
//pt1 = normalPoint;
            normalPoint.x = ThisPoint.x + i * deltaX;
            normalPoint.y = ThisPoint.y + i * deltaY;
//pt2 = normalPoint;

//{
//rgb = int ( 255.0/(float)ProfileLength*(float)TheColor );
//profileColor = Scalar(rgb,rgb,rgb);
//cv::line( oImg, pt1, pt2, profileColor, 2, 0, 0 );
//++TheColor;
//}

			// make sure the point is within the image, otherwise, you can't extract the pixel RGB texture
            if(normalPoint.x < FLT_EPSILON)
                normalPoint.x = 0.0f;
            else if (normalPoint.x - width + 1.0f > FLT_EPSILON)
                normalPoint.x = 2*width - 2.0f - normalPoint.x;

            if(normalPoint.y < FLT_EPSILON)
                normalPoint.y = 0.0f;
            else if(normalPoint.y - height + 1.0f > FLT_EPSILON)
                normalPoint.y = 2*height - 2.0f - normalPoint.y;

            VO_TextureModel::VO_CalcSubPixelTexture ( normalPoint.x, normalPoint.y, iImg, &gray_curr );

            oProf.m_MatProf(i+k, 0) = gray_curr - gray_prev;
			gray_prev = gray_curr;
		}
	}
	else if (channels == 3)
	{
		cv::Mat grayImg;
		cv::cvtColor(iImg, grayImg, CV_BGR2GRAY);
		float gray_prev 	= 0.0f;
		float gray_curr 	= 0.0f;

        VO_TextureModel::VO_CalcSubPixelTexture ( normalPoint.x, normalPoint.y, grayImg, &gray_prev );

		for (int i = -k; i <= k; ++i)
		{
//pt1 = normalPoint;
            normalPoint.x = ThisPoint.x + i * deltaX;
            normalPoint.y = ThisPoint.y + i * deltaY;
//pt2 = normalPoint;

//{
//rgb = int ( 255.0/(float)ProfileLength*(float)TheColor );
//profileColor = Scalar(rgb,rgb,rgb);
//cv::line( oImg, pt1, pt2, profileColor, 2, 0, 0 );
//++TheColor;
//}

			// make sure the point is within the image, otherwise, you can't extract the pixel RGB texture
            if(normalPoint.x < FLT_EPSILON)
                normalPoint.x = 0.0f;
            else if (normalPoint.x - width + 1.0f > FLT_EPSILON)
                normalPoint.x = 2*width - 2.0f - normalPoint.x;

            if(normalPoint.y < FLT_EPSILON)
                normalPoint.y = 0.0f;
            else if(normalPoint.y - height + 1.0f > FLT_EPSILON)
                normalPoint.y = 2*height - 2.0f - normalPoint.y;

            VO_TextureModel::VO_CalcSubPixelTexture ( normalPoint.x, normalPoint.y, grayImg, &gray_curr );

            oProf.m_MatProf(i+k, 0) = gray_curr - gray_prev;
			gray_prev = gray_curr;
		}
////////////////////////////////////////////////////////////////////////////////////////////
// The following is dealing with 3 channels
//		float b_prev = 0.0f, g_prev = 0.0f, r_prev = 0.0f;
//		float b_curr = 0.0f, g_curr = 0.0f, r_curr = 0.0f;
//
//		VO_TextureModel::VO_CalcSubPixelTexture ( normalPoint.x, normalPoint.y, iImg, &b_prev, & g_prev, &r_prev );
//
//		for (int i = -k; i <= k; ++i)
//		{
////pt1 = normalPoint;
//			normalPoint.x = ThisPoint.x + i * deltaX;
//			normalPoint.y = ThisPoint.y + i * deltaY;
////pt2 = normalPoint;
//
////{
////rgb = int ( 255.0/(float)ProfileLength*(float)TheColor );
////profileColor = Scalar(rgb,rgb,rgb);
////cv::line( oImg, pt1, pt2, profileColor, 2, 0, 0 );
////++TheColor;
////}
//
		//// make sure the point is within the image, otherwise, you can't extract the pixel RGB texture
        //if(normalPoint.x < FLT_EPSILON)
        //	normalPoint.x = 0.0f;
        //else if (normalPoint.x - width + 1.0f > FLT_EPSILON)
        //	normalPoint.x = 2*width - 2.0f - normalPoint.x;

        //if(normalPoint.y < FLT_EPSILON)
        //	normalPoint.y = 0.0f;
        //else if(normalPoint.y - height + 1.0f > FLT_EPSILON)
        //	normalPoint.y = 2*height - 2.0f - normalPoint.y;
//
//			VO_TextureModel::VO_CalcSubPixelTexture ( normalPoint.x, normalPoint.y, iImg, &b_curr, &g_curr, &r_curr );
//
//			oProf(3*(i+k)+0, 0) = b_curr - b_prev;
//			oProf(3*(i+k)+1, 0) = g_curr - g_prev;
//			oProf(3*(i+k)+2, 0) = r_curr - r_prev;
//			b_prev = b_curr;
//			g_prev = g_curr;
//			r_prev = r_curr;
//		}
////////////////////////////////////////////////////////////////////////////////////////////
	}
	else
	{
        std::cerr << "VO_Profile: image channels error!" << std::endl;
		exit(1);
	}

//cv::imwrite("test.jpg", oImg);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-22
 * @brief		Get ND profiles for a single landmark
 * @param		iImg 					Input	-- the input image
 * @param		iShape					Input	-- the training shape
 * @param		iShapeInfo				Input	-- shape info
 * @param		ptIdx					Input	-- the landmark index
 * @param		oProf 					Output	-- output profile
 * @param		dim						Input	-- 1D, 2D, 4D?
 * @param		ProfileLength	Input	-- how many elements for a single profile, already multiply by 3 if iImg is of 3 channels
 * @param		pDeltaX					Output	-- deltaX in normal direction
 * @param		pDeltaY					Output	-- deltaY in normal direction
 * @return		void
 * @note		Using "float* oProf" is much much faster than using "VO_Profile& oProf" or "std::vector<float>"
 */
void VO_Profile::VO_GetNDProfiles4OneLandmark (	const cv::Mat& iImg,
												const VO_Shape& iShape,
                                                const std::vector<VO_Shape2DInfo>& iShapeInfo,
												unsigned int ptIdx,
												VO_Profile& oProf,
												unsigned int dim,
												unsigned int ProfileLength,
												float* pDeltaX,
												float* pDeltaY)
{
	oProf = cv::Mat_<float>::zeros( ProfileLength, dim );

    /** Here, this is not compatible with 3D */
    cv::Point2f PrevPoint = iShape.GetA2DPoint ( iShapeInfo[ptIdx].GetFrom() );
    cv::Point2f ThisPoint = iShape.GetA2DPoint ( ptIdx );
    cv::Point2f NextPoint = iShape.GetA2DPoint ( iShapeInfo[ptIdx].GetTo() );

    float deltaX, deltaY;
    float normX, normY;
    float sqrtsum;

    // left side (connected from side)
    deltaX = ThisPoint.x - PrevPoint.x;
    deltaY = ThisPoint.y - PrevPoint.y;
    sqrtsum = sqrt ( deltaX*deltaX + deltaY*deltaY );
    if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
    deltaX /= sqrtsum; deltaY /= sqrtsum; 		// Normalize
	// Firstly, normX normY record left side norm.
    normX = -deltaY;
    normY = deltaX;

    // right side (connected to side)
    deltaX = NextPoint.x - ThisPoint.x;
    deltaY = NextPoint.y - ThisPoint.y;
    sqrtsum = sqrt ( deltaX*deltaX + deltaY*deltaY );
    if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
    deltaX /= sqrtsum; deltaY /= sqrtsum; 		// Normalize
	// Secondly, normX normY will average both left side and right side norm.
    normX += -deltaY;
    normY += deltaX;

    // Average left right side
    sqrtsum = sqrt ( normX*normX + normY*normY );
    if ( sqrtsum < FLT_EPSILON ) sqrtsum = 1.0f;
    normX /= sqrtsum;
    normY /= sqrtsum; 							// Final Normalize

	//////////////////////////////////////////////////////////////////////////////
	// For the 1st dimension -- ASM_PROFILE1D
    // terrific - speed up always. Explained by JIA Pei, coded by Yao Wei.
	VO_Profile tmpCol;
	switch(dim)
	{
		case 2:
		{
			float tangentX 	= 	-normY;
			float tangentY	=	normX;

            VO_Profile::VO_Get1DProfileInMat4OneLandmark (iImg,
                                                        ThisPoint,
														tmpCol, 
														normX, 
														normY, 
														ProfileLength);
			oProf.Set1DimProfile(tmpCol, 0 );
            VO_Profile::VO_Get1DProfileInMat4OneLandmark (iImg,
                                                        ThisPoint,
														tmpCol, 
														tangentX, 
														tangentY, 
														ProfileLength);
			oProf.Set1DimProfile(tmpCol, 1 );
		}
		break;
		case 4:
		{
			float tangentX 	= 	-normY;
			float tangentY	=	normX;
			float tmp45X 	= 	0.707106781*normX-0.707106781*normY;
			float tmp45Y	=	0.707106781*normX+0.707106781*normY;
			float tmp135X 	= 	-0.707106781*normX-0.707106781*normY;
			float tmp135Y	=	0.707106781*normX-0.707106781*normY;
			
            VO_Profile::VO_Get1DProfileInMat4OneLandmark (iImg,
                                                        ThisPoint,
														tmpCol,
														normX,
														normY,
														ProfileLength);
			oProf.Set1DimProfile(tmpCol, 0 );
            VO_Profile::VO_Get1DProfileInMat4OneLandmark (iImg,
                                                        ThisPoint,
														tmpCol,
														tangentX,
														tangentY,
														ProfileLength);
			oProf.Set1DimProfile(tmpCol, 1 );
            VO_Profile::VO_Get1DProfileInMat4OneLandmark (iImg,
                                                        ThisPoint,
														tmpCol,
														tmp45X,
														tmp45Y,
														ProfileLength);
			oProf.Set1DimProfile(tmpCol, 2 );
            VO_Profile::VO_Get1DProfileInMat4OneLandmark (iImg,
                                                        ThisPoint,
														tmpCol,
														tmp135X,
														tmp135Y,
														ProfileLength);
			oProf.Set1DimProfile(tmpCol, 3 );
		}
		break;
		case 1:
		default:
		{
            VO_Profile::VO_Get1DProfileInMat4OneLandmark (iImg,
                                                        ThisPoint,
														tmpCol,
														normX,
														normY,
														ProfileLength);
			oProf.Set1DimProfile(tmpCol, 0 );
		}
		break;
	}
	//////////////////////////////////////////////////////////////////////////////

    if(pDeltaX)     *pDeltaX = normX;
    if(pDeltaY)     *pDeltaY = normY;
}


/**
 * @brief		Normalization for every dim
 * 				1D normalization - refer to Cootes "Statistical Models of Appearance for Computer Vision" page 38, (7.1)
 * @note		It's not a direct normalization over all elements in the matrix, it's basically column-wise normalization
*/
void VO_Profile::Normalize()
{
    for(unsigned int i = 0; i < this->m_MatProf.cols; i++)
	{
        cv::Mat oneCol = this->m_MatProf.col(i);
		cv::normalize( oneCol, oneCol);
	}
}

