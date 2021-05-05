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

#ifndef __VO_ELLIPSE_H__
#define __VO_ELLIPSE_H__

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "VO_Shape.h"
#include "VO_Common.h"



/** 
 * @author      JIA Pei
 * @brief       Ellipse - used to describe 2D Gaussian distribution.
 */
class VO_Ellipse
{
friend std::ostream& operator<<(std::ostream& os, const VO_Ellipse& ellipse);
friend std::istream& operator>>(std::istream& is, VO_Ellipse& ellipse);
protected:
    float                       m_fPhimin;              ///    Minimum angle (degrees)
    float                       m_fPhimax;              ///    Maximum angle (degrees)
    float                       m_fAxisXHalfLen;        ///    first radius
    float                       m_fAxisYHalfLen;        ///    second radius
    float                       m_fTheta;               ///    Rotation angle (degrees)
    cv::Point2f                 m_Center;               ///    ellipse center

    /** Copy an ellipse */
    void                        CopyData(const VO_Ellipse& ellipse)
    {
                                this->m_fPhimax         = ellipse.m_fPhimax;
                                this->m_fPhimin         = ellipse.m_fPhimin;
                                this->m_fAxisXHalfLen   = ellipse.m_fAxisXHalfLen;
                                this->m_fAxisYHalfLen   = ellipse.m_fAxisYHalfLen;
                                this->m_fTheta          = ellipse.m_fTheta;
                                this->m_Center.x        = ellipse.m_Center.x;
                                this->m_Center.y        = ellipse.m_Center.y;
    }

public:
    /** Default constructor to create a VO_Ellipse object */
    VO_Ellipse()
    {
        this->m_fPhimax         = 0.0f;
        this->m_fPhimin         = 0.0f;
        this->m_fAxisXHalfLen   = 0.0f;
        this->m_fAxisYHalfLen   = 0.0f;
        this->m_fTheta          = 0.0f;
        this->m_Center.x        = 0.0f;
        this->m_Center.y        = 0.0f;
    }

    /** copy constructor */
    VO_Ellipse(const VO_Ellipse& ellipse)
    {
        this->CopyData(ellipse);
    }

    /** Constructor to create a VO_Ellipse object with three coordinate vertexes in std::vector format */
    VO_Ellipse(cv::Point2f cog, float l, float s, float phimin = 0, float phimax = 360, float theta = 0)
    {
        this->m_fPhimin         = phimin;
        this->m_fPhimax         = phimax;
        this->m_fAxisXHalfLen   = l;
        this->m_fAxisYHalfLen   = s;
        this->m_fTheta          = theta;
        this->m_Center          = cog;
    }

    /** Destructor */
    virtual ~VO_Ellipse()    {}

    /** operator= overloading, similar to copy constructor */
    VO_Ellipse&                 operator=(const VO_Ellipse& ellipse);
    VO_Ellipse                  operator*(float value);
    VO_Ellipse&                 operator*=(float value);

    /** Translation */
    void                        Translate( const cv::Mat_<float>& translation );
    
    /** Scale the Position */
    void                        ScaleCenter(float value);
    
    /** Calculate area of ellipse */
    float                       CalcArea( ) const {return CV_PI*this->m_fAxisXHalfLen*this->m_fAxisYHalfLen;}

    /** Calculate perimeter of ellipse: L=2πb+4(a-b) */
    float                       CalcPerimeter( )
    {
                                float longAxis     =    this->GetLongAxis();
                                float shortAxis =     this->GetShortAxis();
                                return 2.0*CV_PI*shortAxis + 4.0*(longAxis - shortAxis);
    }

    /** Evaluate whether the point is within the ellipse */
    bool                        IsPointWithinEllipse(const cv::Point2f& pt, bool includeBoundary = true)
    {
        if(includeBoundary)
        {
            if( pow( ( pt.x * cos(this->m_fTheta) - pt.y * sin(this->m_fTheta) - this->m_Center.x ) / this->m_fAxisXHalfLen, 2.0f) +
                pow( ( pt.x * sin(this->m_fTheta) + pt.y * cos(this->m_fTheta) - this->m_Center.y ) / this->m_fAxisYHalfLen, 2.0f) <= 1.0 )
                return true;
            else
                return false;
        }
        else
        {
            if( pow( ( pt.x * cos(this->m_fTheta) - pt.y * sin(this->m_fTheta) - this->m_Center.x ) / this->m_fAxisXHalfLen, 2.0f) +
                pow( ( pt.x * sin(this->m_fTheta) + pt.y * cos(this->m_fTheta) - this->m_Center.y ) / this->m_fAxisYHalfLen, 2.0f) < 1.0 )
                return true;
            else
                return false;
        }
    }

    /** Evaluate whether the point is on the boundary of the ellipse */
    bool                        IsPointOnEllipseBoundary(const cv::Point2f& pt)
    {
        if( fabs( pow( ( pt.x * cos(this->m_fTheta) - pt.y * sin(this->m_fTheta) - this->m_Center.x ) / this->m_fAxisXHalfLen, 2.0f) +
                pow( ( pt.x * sin(this->m_fTheta) + pt.y * cos(this->m_fTheta) - this->m_Center.y ) / this->m_fAxisYHalfLen, 2.0f) - 1.0 ) < FLT_EPSILON )
            return true;
        else
            return false;
    }
    
    /** Find the upright bounding rectangle for an ellipse */
    cv::Rect                    CalcBoundingRect() const
    {
                                cv::Size2f size = cv::Size2f(this->m_fAxisXHalfLen*2.0, this->m_fAxisYHalfLen*2.0);
                                cv::RotatedRect rRect = cv::RotatedRect(this->m_Center, size, this->m_fTheta);
                                return rRect.boundingRect();
    }

    /** Find the nearest point on the boundary to the input point 
     * leave here, tough. needs optimization */
    cv::Point2f                 FindNearestPointOnBoundary(const cv::Point2f& pt);
    
    /** Find the intersect point on the boundary connecting from the COG and the input point */
    cv::Point2f                 FindIntersectPointOnBoundary(const cv::Point2f& pt);

    /** Obtain point list within the ellipse according to its range  */
    std::vector<cv::Point>      VO_PointsInEllipse( const VO_Ellipse& ellipse);
    
    /** Find bounding rectangle for multiple ellipses, this rectangle should cover all ellipses */
    static cv::Rect             VO_CalcBoundingRect4MultipleEllipses(const std::vector<VO_Ellipse>& ellipses);

    /** Gets and sets */
    float                       GetLongAxis() const
    {
        return                  this->m_fAxisXHalfLen >= this->m_fAxisYHalfLen ? 
                                this->m_fAxisXHalfLen : this->m_fAxisYHalfLen;
    }
    float                       GetShortAxis() const
    {
        return                  this->m_fAxisXHalfLen <= this->m_fAxisYHalfLen ? 
                                this->m_fAxisXHalfLen : this->m_fAxisYHalfLen;
    }
    cv::Point2f                 GetCOG() const {return this->m_Center;}
    float                       GetStartAngle() const {return this->m_fPhimin;}
    float                       GetEndAngle() const {return this->m_fPhimax;}
    float                       GetAxisXHalfLen() const {return this->m_fAxisXHalfLen;}
    float                       GetAxisYHalfLen() const {return this->m_fAxisYHalfLen;}
    float                       GetAngle() const {return this->m_fTheta;}
};

#endif  // __VO_ELLIPSE_H__

