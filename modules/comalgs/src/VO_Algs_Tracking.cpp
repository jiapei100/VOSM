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

#include "VO_Algs_Tracking.h"


//int CTrackingAlgs::histSize[] = {hbins, sbins};               // histSize
int CTrackingAlgs::histSize[] = {hbins};                        // histSize
float CTrackingAlgs::hranges[] = { 0, 180 };                    // hue varies from 0 to 179, see cvtColor
float CTrackingAlgs::sranges[] = { 0, 256 };                    // saturation varies from 0 (black-gray-white) to 255 (pure spectrum color)
//const float* CTrackingAlgs::ranges[] = { hranges, sranges };  // ranges
const float* CTrackingAlgs::ranges[] = { hranges };             // ranges
int CTrackingAlgs::channels[] = {0};

/** 
 * @author      JIA Pei
 * @version     2010-02-01
 * @brief       Initialization
 * @param       mtd     Input - detection method, here, for additive model, boosting or bagging
 * @return      void
*/
void CTrackingAlgs::init(unsigned int trackingmtd, unsigned int trackermtd)
{
    this->SetConfiguration(trackingmtd, trackermtd);
    this->m_bTrackerInitialized = false;
    this->m_bObjectTracked        = false;
}


/** CTrackingAlgs constructor */
CTrackingAlgs::CTrackingAlgs(unsigned int trackingmtd, unsigned int trackermtd)
{
    this->init(trackingmtd, trackermtd);
}


/** CTrackingAlgs destructor */
CTrackingAlgs::~CTrackingAlgs()
{

}


/**
 * @brief   Update the Tracker
 * @param   img
 * @param   obj
 * @return  void
 */
void CTrackingAlgs::UpdateTracker(const cv::Mat& img, const cv::Rect& obj)
{
    switch(this->m_iTrackingMethod)
    {
    case CAMSHIFT:
        {
            this->m_bTrackerInitialized = CTrackingAlgs::CamshiftUpdateTracker(img, obj, this->m_hist);
        }
        break;
    case KALMANFILTER:
        {
        }
        break;
    case PARTICLEFILTER:
        {
        }
        break;
    case ASMAAM:
        {
        }
        break;
    case NONE:
    default:
        {
            this->m_bTrackerInitialized =  false;
        }
        break;
    }
}


/**
 * @brief   Is Camshift Tracker updated or not?
 * @param   img
 * @param   obj
 * @param   hist
 * @return  bool, whether Camshift tracker has been updated or not
 */
bool CTrackingAlgs::CamshiftUpdateTracker(  const cv::Mat& img,
                                            const cv::Rect& obj,
                                            cv::MatND& hist)
{
    cv::Mat hsv, hue, mask, backproject;
    cv::cvtColor( img, hsv, CV_BGR2HSV );
    
    int _vmin = CTrackingAlgs::vmin, _vmax = CTrackingAlgs::vmax;

    cv::inRange( hsv, cv::Scalar(0,CTrackingAlgs::smin,MIN(_vmin,_vmax),0),
                cv::Scalar(180,256,MAX(_vmin,_vmax),0), mask );
    std::vector<cv::Mat> vhsv(3);
    cv::split( hsv, vhsv );
    vhsv[0].copyTo(hue);
    
    double max_val = 0.f;
    cv::Mat roi     = hue(  cv::Range(obj.y, obj.y+obj.height),
                            cv::Range(obj.x, obj.x+obj.width) );
    cv::Mat roi_mask= mask( cv::Range(obj.y, obj.y+obj.height),
                            cv::Range(obj.x, obj.x+obj.width) );
    cv::calcHist(   &roi, 1, CTrackingAlgs::channels, roi_mask,
                    hist, 1, CTrackingAlgs::histSize, CTrackingAlgs::ranges,
                    true, // the histogram is uniform
                    false );
    cv::minMaxLoc(hist, 0, &max_val, 0, 0);
    hist.convertTo(hist, hist.type(), (max_val ? 255. / max_val : 0.), 0);

    return true;
}


/** 
 * @author      JIA Pei
 * @version     2009-10-04
 * @brief       Object Tracking
 * @param       img         Input - image to be searched within
 * @param       objs        Input - object to be tracked
 * @param       smallSize   Input - smallSize
 * @param       bigSize     Input - bigSize
 * @return      detection time cost
*/
double CTrackingAlgs::Tracking(const cv::Mat& img,
                               cv::Rect& obj,
                               cv::Size smallSize,
                               cv::Size bigSize)
{
    double res = (double)cvGetTickCount();

    if(this->m_bTrackerInitialized)
    {
        switch(this->m_iTrackingMethod)
        {
        case CAMSHIFT:
            {
                CTrackingAlgs::CamshiftTracking(img,
                                                this->m_hist,
                                                obj,
                                                this->m_bObjectTracked,
                                                smallSize,
                                                bigSize);
                this->m_CVTrackedObjectRect = obj;
            }
            break;
        case KALMANFILTER:
            {
                CTrackingAlgs::KalmanTracking(  img,
                                                obj,
                                                this->m_bObjectTracked,
                                                smallSize,
                                                bigSize);
                this->m_CVTrackedObjectRect = obj;
            }
            break;
        case PARTICLEFILTER:
            {
                CTrackingAlgs::ParticleFilterTracking(  img,
                                                        obj,
                                                        this->m_bObjectTracked,
                                                        smallSize,
                                                        bigSize);
                this->m_CVTrackedObjectRect = obj;
            }
            break;
        case ASMAAM:
            {
                CTrackingAlgs::ASMAAMTracking(  img,
                                                obj,
                                                this->m_bObjectTracked,
                                                smallSize,
                                                bigSize);
                this->m_CVTrackedObjectRect = obj;
            }
            break;
        case NONE:
        default:
            {
                this->m_bObjectTracked         = false;
                this->m_bTrackerInitialized    = false;
            }
            break;
        }
    }
    else
    {
        this->UpdateTracker(img, obj);
    }

    res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
    return res;
}


/** 
 * @author      JIA Pei
 * @version     2010-02-02
 * @brief       Camshift Tracking
 * @param       img             Input - image to be searched within
 * @param       objs            Input - object to be tracked
 * @param       isTracked       output - is this objs tracked?
 * @param       smallSize       Input - the smallest possible object size
 * @param       bigSize         Input - the biggest possible object size
 * @return      detection time cost
*/
double CTrackingAlgs::CamshiftTracking( const cv::Mat& img,
                                        cv::MatND& hist,
                                        cv::Rect& obj,
                                        bool& isTracked,
                                        cv::Size smallSize,
                                        cv::Size bigSize)
{
    double res = (double)cvGetTickCount();

    if(obj.x <= 0)    obj.x = 0;
    if(obj.y <= 0)    obj.y = 0;
    if(obj.x + obj.width > img.cols) obj.width = img.cols - obj.x;
    if(obj.y + obj.height > img.rows) obj.height = img.rows - obj.y;

    cv::Rect trackwindow = obj;
    cv::Mat hsv, hue, mask, backproject;
    cv::cvtColor( img, hsv, CV_BGR2HSV );

    int _vmin = CTrackingAlgs::vmin, _vmax = CTrackingAlgs::vmax;

    cv::inRange( hsv, cv::Scalar(0,CTrackingAlgs::smin,MIN(_vmin,_vmax),0),
                cv::Scalar(180,256,MAX(_vmin,_vmax),0), mask );
    std::vector<cv::Mat> vhsv(3);
    cv::split( hsv, vhsv );
    vhsv[0].copyTo(hue);
            
    cv::calcBackProject( &hue, 1, CTrackingAlgs::channels, hist, backproject, CTrackingAlgs::ranges);
    cv::bitwise_and( backproject, mask, backproject );
    cv::RotatedRect trackbox = cv::CamShift( backproject, trackwindow, cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS, 10, 1) );
    obj = trackwindow;

//        cv::ellipse(img, trackbox, CV_RGB(255,0,0), 3, CV_AA);

    cv::Point pt1 = cv::Point( (int)(obj.x), (int)(obj.y) );
    cv::Point pt2 = cv::Point( (int)(obj.x + obj.width),
                                (int)(obj.y + obj.height) );

    // Judge whether it is losing the object or not...
    if(obj.width >= bigSize.width || obj.height >= bigSize.height
        || obj.width <= smallSize.width || obj.height <= smallSize.height
        || pt1.x < FRAMEEDGE || pt1.y < FRAMEEDGE
        || (pt2.x > (img.cols - FRAMEEDGE)) || (pt2.y > (img.rows - FRAMEEDGE)))
    {
        isTracked = false;
        obj.x = obj.y = obj.width = obj.height = -1;
    }
    else
        isTracked = true;

    res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
    return res;
}


/**
 * @brief   Tracking by Kalman filter
 * @param   img
 * @param   obj
 * @param   isTracked
 * @param   smallSize
 * @param   bigSize
 * @return  tracking time
 */
double CTrackingAlgs::KalmanTracking(const cv::Mat& img,
                                    cv::Rect& obj,
                                    bool& isTracked,
                                    cv::Size smallSize,
                                    cv::Size bigSize)
{
    double res = (double)cvGetTickCount();
    
    res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
    return res;
}


/**
 * @brief   Tracking by particle filter
 * @param   img
 * @param   obj
 * @param   isTracked
 * @param   smallSize
 * @param   bigSize
 * @return  tracking time
 */
double CTrackingAlgs::ParticleFilterTracking(const cv::Mat& img,
                                            cv::Rect& obj,
                                            bool& isTracked,
                                            cv::Size smallSize,
                                            cv::Size bigSize)
{
    double res = (double)cvGetTickCount();
    
    res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
    return res;
}


/**
 * @brief   Tracking by ASM/AAM
 * @param   img
 * @param   obj
 * @param   isTracked
 * @param   smallSize
 * @param   bigSize
 * @return  tracking time
 */
double CTrackingAlgs::ASMAAMTracking(const cv::Mat& img,
                                    cv::Rect& obj,
                                    bool& isTracked,
                                    cv::Size smallSize,
                                    cv::Size bigSize)
{
    double res = (double)cvGetTickCount();
    
    res = ((double)cvGetTickCount() - res) / ((double)cvGetTickFrequency()*1000.);
    return res;
}


/**
 * @brief   Draw tracking results
 * @param   ioImg -- input, output, the image to be drawn onto
 * @param   color -- the color
 */
void CTrackingAlgs::VO_DrawTracking(cv::Mat& ioImg, cv::Scalar color)
{
    cv::Rect curRect;
    cv::Point lefttop, rightbottom;

    if ( this->m_bObjectTracked )
    {
        curRect = this->m_CVTrackedObjectRect;
        lefttop.x = cvRound(curRect.x);
        lefttop.y = cvRound(curRect.y);
        rightbottom.x = cvRound((curRect.x+curRect.width));
        rightbottom.y = cvRound((curRect.y+curRect.height));
        cv::rectangle(ioImg, lefttop, rightbottom, color, 2, 8, 0);
    }
}

