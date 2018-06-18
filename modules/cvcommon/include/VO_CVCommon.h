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
* Create Date:      2010-02-06                                                                      *
* Modify Date:      2014-04-16                                                                      *
****************************************************************************************************/


#ifndef __VO_CVCOMMON_H__
#define __VO_CVCOMMON_H__



#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "VO_Common.h"
#include "VO_BoostCommon.h"


#define THUMBNAIL_SIZE_WIDTH    120
#define THUMBNAIL_SIZE_HEIGHT   90

//RGB-> YUV
#define MY(a,b,c) (( a*  0.2989  + b*0.5866  + c*  0.1145))
#define MU(a,b,c) (( a*(-0.1688) + b*(-0.3312) + c*  0.5000 + 128))
#define MV(a,b,c) (( a* 0.5000 + b*(-0.4184) + c*(-0.0816) + 128))
// decision 
#define DY(a,b,c) (MY(a,b,c) > 255 ? 255 : (MY(a,b,c) < 0 ? 0 : MY(a,b,c)))
#define DU(a,b,c) (MU(a,b,c) > 255 ? 255 : (MU(a,b,c) < 0 ? 0 : MU(a,b,c)))
#define DV(a,b,c) (MV(a,b,c) > 255 ? 255 : (MV(a,b,c) < 0 ? 0 : MV(a,b,c)))


static cv::Scalar colors[] =
{
    cv::Scalar(0,0,255),        // red
    cv::Scalar(255,0,0),        // blue
    cv::Scalar(0,255,0),        // green
    cv::Scalar(0,255,255),      // yellow
    cv::Scalar(255,255,0),      // cyan
    cv::Scalar(255,0,255),      // magenta
    cv::Scalar(0,0,0),          // black
    cv::Scalar(255,255,255),    // white
    cv::Scalar(0,128,255),      //
    cv::Scalar(255,128,0),      //
    cv::Scalar(0,255,128)       //
};


static void RGB2YUV(unsigned char *RGB, 
                    unsigned char *YUV[], 
                    unsigned int WIDTH, 
                    unsigned int HEIGHT)
{
    unsigned int i,x,y,j;
    unsigned char *Y = NULL;
    unsigned char *U = NULL;
    unsigned char *V = NULL;
    int uindex=0,vindex=0;
    Y = YUV[0];
    U = YUV[2];
    V = YUV[1];
    for(y=0; y < HEIGHT; y++)
    {
        for(x=0; x < WIDTH; x++)
        {
            //j is the image index
            j = y*WIDTH + x;
            //iis j's first address
            i = j*3;
            Y[j] = (unsigned char)(DY(RGB[i], RGB[i+1], RGB[i+2]));
            if(y%2 == 0)
            {
                if (x%2==1)
                {
                    U[uindex++] = (unsigned char)(DU(RGB[i], RGB[i+1], RGB[i+2]));
                }
            }
            else
            {
                if (x%2==1)
                {
                    V[vindex++] = (unsigned char)(DV(RGB[i], RGB[i+1], RGB[i+2]));
                }
            }
        }
    }
}


static void produceAllThumbnails(   const std::vector<cv::Mat>& mats, 
                                    const std::vector<std::string>& fns, 
                                    int width = 160, 
                                    int height = 90)
{
    assert( mats.size() == fns.size() );
    int nbOfMats = mats.size();
    if(nbOfMats != 0)
    {
        int type = mats[0].type();
        for (int i = 0; i < nbOfMats; i++)
        {
            cv::Mat mat = cv::Mat( height, width, type );
            cv::resize( mats[i], mat, mat.size(), 0, 0, cv::INTER_LINEAR );
            cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
            cv::imwrite(fns[i], mat);
        }
    }
}


//////////////////////////////////////////////////////////////////////////

static const int MAG_THRESHOLD = 25;
static const int MAG_AREA = 5;

static int get_integral(const cv::Mat &_integral_image, const cv::Point &_pt1, const cv::Point &_pt2)
{
    CV_Assert(_pt1.x < _integral_image.cols && _pt1.x >= 0 && _pt1.y >= 0 && _pt1.y < _integral_image.rows);
    CV_Assert(_pt2.x < _integral_image.cols && _pt2.x >= 0 && _pt2.y >= 0 && _pt2.y < _integral_image.rows);
    CV_Assert(_integral_image.type() == CV_32S);
    return _integral_image.at<int>(_pt1.y, _pt1.x) + 
        _integral_image.at<int>(_pt2.y, _pt2.x) -
        _integral_image.at<int>(_pt1.y, _pt2.x) -
        _integral_image.at<int>(_pt2.y, _pt1.x);
}

static const cv::Rect crop_font_roi(const cv::Mat &_image,
	const cv::Point &_left_point, const cv::Point &_right_point)
{
    CV_Assert(_left_point.x >= 0 && _left_point.x < _image.cols &&
        _left_point.y >= 0 && _left_point.y < _image.rows);
    CV_Assert(_right_point.x >= 0 && _right_point.x < _image.cols &&
        _right_point.y >= 0 && _right_point.y < _image.rows);
    cv::Point left_point = _left_point;
    cv::Point right_point = _right_point;
    if (left_point.x > right_point.x)
    {
        std::swap(left_point, right_point);
    }
    // fix line
    cv::Point fix_l_point;
    cv::Point fix_r_point;
    //fix_l_point.y = std::max(_left_point.y, _right_point.y);
    fix_l_point.y = left_point.y > right_point.y ? left_point.y : right_point.y;
    fix_l_point.x = left_point.x;
    fix_r_point.y = fix_l_point.y;
    fix_r_point.x = right_point.x;

    // processing image
    cv::Mat gray_image;
    if (_image.channels() == 3) cvtColor(_image, gray_image, cv::COLOR_BGR2GRAY);
    else gray_image = _image;

    // blur image
    cv::Mat blur_image;
    cv::medianBlur(gray_image, blur_image, 5);
    cv::Mat bi_mag_image = cv::Mat::zeros(blur_image.rows, blur_image.cols, CV_8UC1);

    for (int r = 1; r < blur_image.rows - 1; r++) {
        for (int c = 1; c < blur_image.cols - 1; c++) {
            int ix = abs((int)blur_image.at<uchar>(r, c + 1) - (int)blur_image.at<uchar>(r, c - 1));
            int iy = abs((int)blur_image.at<uchar>(r + 1, c) - (int)blur_image.at<uchar>(r - 1, c));
            int mag = ix*ix + iy*iy;
            bi_mag_image.at<uchar>(r, c) = mag > MAG_THRESHOLD ? 1 : 0;
        } 
    }

    cv::Mat integral_image = cv::Mat(blur_image.rows+1, blur_image.cols+1, CV_32SC1);
    cv::integral(bi_mag_image, integral_image);

    int sum = get_integral(integral_image, cv::Point(fix_l_point.x, fix_l_point.y), 
        cv::Point(fix_r_point.x, fix_r_point.y+1));

    int bottom_y = -1;
    int upper_y = -1;
    if (sum >= MAG_AREA)
    {
        for (int r = fix_l_point.y; r < _image.rows - 2; r++)
        {
            int sum1 = get_integral(integral_image, cv::Point(fix_l_point.x, r), 
                cv::Point(fix_r_point.x, r+1));
            int sum2 = get_integral(integral_image, cv::Point(fix_l_point.x, r+1), 
                cv::Point(fix_r_point.x, r+2));
            if (sum1 < MAG_AREA && sum2 < MAG_AREA)
            {
                bottom_y = r + 1;
                break;
            }
        }
        for (int r = fix_l_point.y; r >= 2; r--)
        {
            int sum1 = get_integral(integral_image, cv::Point(fix_l_point.x, r-1), 
                cv::Point(fix_r_point.x, r));
            int sum2 = get_integral(integral_image, cv::Point(fix_l_point.x, r-2), 
                cv::Point(fix_r_point.x, r-1));
            if (sum1 < MAG_AREA && sum2 < MAG_AREA)
            {
                upper_y = r - 1;
                break;
            }
        }
    }
    else
    {
        for (int r = fix_l_point.y; r >= 2; r--)
        {
            int sum1 = get_integral(integral_image, cv::Point(fix_l_point.x, r-1), 
                cv::Point(fix_r_point.x, r));
            int sum2 = get_integral(integral_image, cv::Point(fix_l_point.x, r-2), 
                cv::Point(fix_r_point.x, r-1));
            if (sum1 >= MAG_AREA && sum2 >= MAG_AREA)
            {
                bottom_y = r + 1;
                break;
            }
        }
        for (int r = bottom_y - 2; r >= 2; r--)
        {
            int sum1 = get_integral(integral_image, cv::Point(fix_l_point.x, r-1), 
                cv::Point(fix_r_point.x, r));
            int sum2 = get_integral(integral_image, cv::Point(fix_l_point.x, r-2), 
                cv::Point(fix_r_point.x, r-1));
            if (sum1 < MAG_AREA && sum2 < MAG_AREA)
            {
                upper_y = r - 1;
                break;
            }
        }
    }

    // up and button done
    int left_x = -1;
    int right_x = -1;

    sum = get_integral(integral_image, cv::Point(fix_l_point.x, upper_y), 
        cv::Point(fix_l_point.x+1, bottom_y));
    if (sum >= MAG_AREA)
    {
        for (int c = fix_l_point.x; c >= 2; c--)
        {
            int sum1 = get_integral(integral_image, cv::Point(c-1, upper_y), 
                cv::Point(c, bottom_y));
            int sum2 = get_integral(integral_image, cv::Point(c-2, upper_y), 
                cv::Point(c-1, bottom_y));
            if (sum1 < MAG_AREA && sum2 < MAG_AREA)
            {
                left_x = c - 1;
                break;
            }
        }
    }
    else
    {
        for (int c = fix_l_point.x; c < fix_r_point.x - 2; c++)
        {
            int sum1 = get_integral(integral_image, cv::Point(c, upper_y), 
                cv::Point(c+1, bottom_y));
            int sum2 = get_integral(integral_image, cv::Point(c+1, upper_y), 
                cv::Point(c+2, bottom_y));
            if (sum1 >= MAG_AREA && sum2 >= MAG_AREA)
            {
                left_x = c;
                break;
            }
        }
    }

    sum = get_integral(integral_image, cv::Point(fix_r_point.x, upper_y), 
        cv::Point(fix_r_point.x+1, bottom_y));
    if (sum >= MAG_AREA)
    {
        for (int c = fix_r_point.x; c < _image.cols - 2; c++)
        {
            int sum1 = get_integral(integral_image, cv::Point(c, upper_y), 
                cv::Point(c+1, bottom_y));
            int sum2 = get_integral(integral_image, cv::Point(c+1, upper_y), 
                cv::Point(c+2, bottom_y));
            if (sum1 < MAG_AREA && sum2 < MAG_AREA)
            {
                right_x = c + 2;
                break;
            }
        }
    }
    else
    {
        for (int c = fix_r_point.x; c >= fix_l_point.x; c--)
        {
            int sum1 = get_integral(integral_image, cv::Point(c-1, upper_y), 
                cv::Point(c, bottom_y));
            int sum2 = get_integral(integral_image, cv::Point(c-2, upper_y), 
                cv::Point(c-1, bottom_y));
            if (sum1 < MAG_AREA && sum2 < MAG_AREA)
            {
                right_x = c;
                break;
            }
        }
    }
    return cv::Rect(left_x, upper_y, right_x-left_x+1, bottom_y-upper_y+1);
}
//////////////////////////////////////////////////////////////////////////


/** output every element of a cv::Mat */
static std::ostream& operator<< ( std::ostream& os, const cv::Mat& mat )
{
    unsigned int channels = mat.channels();
    unsigned int depth = mat.depth();
    if (!(channels == 1 || channels == 3))
    {
        std::cerr << "Cannot deal with images with nChannels != 1 or 3." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if(channels == 1)
    {
        switch( depth )
        {
            case CV_8U:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<unsigned char>(i, j) << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_8S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<char>(i, j) << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_16U:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<unsigned short>(i, j) << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_16S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<short>(i, j) << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_32S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<int>(i, j) << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_32F:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<float>(i, j) << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_64F:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<double>(i, j) << " ";
                    }
                    os << std::endl;
                }
            }
            break;
        }
    }
    else if (channels == 3)
    {
        switch( depth )
        {
            case CV_8U:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<cv::Vec3b>(i, j)[0] << " "
                            << mat.at<cv::Vec3b>(i, j)[1] << " "
                            << mat.at<cv::Vec3b>(i, j)[2] << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_16S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<cv::Vec3s>(i, j)[0] << " "
                            << mat.at<cv::Vec3s>(i, j)[1] << " "
                            << mat.at<cv::Vec3s>(i, j)[2] << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_32S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<cv::Vec3i>(i, j)[0] << " "
                            << mat.at<cv::Vec3i>(i, j)[1] << " "
                            << mat.at<cv::Vec3i>(i, j)[2] << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_32F:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<cv::Vec3f>(i, j)[0] << " "
                            << mat.at<cv::Vec3f>(i, j)[1] << " "
                            << mat.at<cv::Vec3f>(i, j)[2] << " ";
                    }
                    os << std::endl;
                }
            }
            break;
            case CV_64F:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        os << mat.at<cv::Vec3d>(i, j)[0] << " "
                            << mat.at<cv::Vec3d>(i, j)[1] << " "
                            << mat.at<cv::Vec3d>(i, j)[2] << " ";
                    }
                    os << std::endl;
                }
            }
            break;
        }
    }

    return os;
}


/** input every element to a cv::Mat */
static std::istream& operator>> ( std::istream& is, cv::Mat& mat )
{
    unsigned int channels = mat.channels();
    unsigned int depth = mat.depth();
    if (!(channels == 1 || channels == 3))
    {
        std::cerr << "Cannot deal with images with nChannels != 1 or 3." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if(channels == 1)
    {
        switch( depth )
        {
            case CV_8U:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<unsigned char>(i, j);
                    }
                }
            }
            break;
            case CV_8S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<char>(i, j);
                    }
                }
            }
            break;
            case CV_16U:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<unsigned short>(i, j);
                    }
                }
            }
            break;
            case CV_16S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<short>(i, j);
                    }
                }
            }
            break;
            case CV_32S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<int>(i, j);
                    }
                }
            }
            break;
            case CV_32F:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<float>(i, j);
                    }
                }
            }
            break;
            case CV_64F:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<double>(i, j);
                    }
                }
            }
            break;
        }
    }
    
    else if (channels == 3)
    {
        switch( mat.depth() )
        {
            case CV_8U:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<cv::Vec3b>(i, j)[0]
                            >> mat.at<cv::Vec3b>(i, j)[1]
                            >> mat.at<cv::Vec3b>(i, j)[2];
                    }
                }
            }
            break;
            case CV_16S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<cv::Vec3s>(i, j)[0]
                            >> mat.at<cv::Vec3s>(i, j)[1]
                            >> mat.at<cv::Vec3s>(i, j)[2];
                    }
                }
            }
            break;
            case CV_32S:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<cv::Vec3i>(i, j)[0]
                            >> mat.at<cv::Vec3i>(i, j)[1]
                            >> mat.at<cv::Vec3i>(i, j)[2];
                    }
                }
            }
            break;
            case CV_32F:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<cv::Vec3f>(i, j)[0]
                            >> mat.at<cv::Vec3f>(i, j)[1]
                            >> mat.at<cv::Vec3f>(i, j)[2];
                    }
                }
            }
            break;
            case CV_64F:
            {
                for ( unsigned int i = 0; i < mat.rows; i++ )
                {
                    for ( unsigned int j = 0; j < mat.cols; j++ )
                    {
                        is >> mat.at<cv::Vec3d>(i, j)[0]
                            >> mat.at<cv::Vec3d>(i, j)[1]
                            >> mat.at<cv::Vec3d>(i, j)[2];
                    }
                }
            }
            break;
        }
    }

    return is;
}


/** output every element of a cv::Mat_<T> */
template <class T>
static std::ostream& operator<< ( std::ostream& os, const cv::Mat_<T>& mat )
{
    for ( unsigned int i = 0; i < mat.rows; i++ )
    {
        for ( unsigned int j = 0; j < mat.cols; j++ )
        {
            os << mat(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}


/** input every element to a cv::Mat_<T> */
template <class T>
static std::istream& operator>> ( std::istream& is, cv::Mat_<T>& mat )
{
    for ( unsigned int i = 0; i < mat.rows; i++ )
    {
        for ( unsigned int j = 0; j < mat.cols; j++ )
        {
            is >> mat(i, j);
        }
    }
    return is;
}


/** output a cv::Rect */
static std::ostream& operator<< ( std::ostream& os, const cv::Rect& rect )
{
    os << rect.x << " " << rect.y << " " << 
            rect.width << " " << rect.height << std::endl;
    return os;
}


/** output a cv::Point */
static std::ostream& operator<< ( std::ostream &os, const cv::Point& pt )
{
    os << pt.x << " " << pt.y << std::endl;
    return os;
}

/** output a cv::Point2f */
static std::ostream& operator<< ( std::ostream &os, const cv::Point2f& pt )
{
    os << pt.x << " " << pt.y << std::endl;
    return os;
}



/** Size compare */
static int cvSizeCompare( const void *arg1, const void *arg2 )
{
    return ( (*(cv::Size*)arg1).width * (*(cv::Size*)arg1).height -
            (*(cv::Size*)arg2).width * (*(cv::Size*)arg2).height );
}


/** cv::Rect compare */
static int cvRectCompare( const void *arg1, const void *arg2 )
{
    return ( (*(cv::Size*)arg1).width * (*(cv::Size*)arg1).height -
            (*(cv::Size*)arg2).width * (*(cv::Size*)arg2).height );
}



/** Image clamp */
template<class T>
static void clamp ( const cv::Mat& iImg, cv::Mat& oImg, T low, T up )
{
    if(low < up)
    {
        std::cerr << "lower bound is smaller than upper bound!" << std::endl;
        exit(1);
    }
    
    unsigned int NbOfDepth = iImg.depth();
    unsigned int NbOfChannels = iImg.channels();
    
    if(NbOfChannels == 1)
    {
        switch(NbOfDepth)
        {
            case CV_8U:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        if( iImg.at<uchar>(y,x) < (uchar) low )
                            oImg.at<uchar>(y,x) = (uchar) low;
                        else if( iImg.at<uchar>(y,x) > (uchar) up )
                            oImg.at<uchar>(y,x) = (uchar) up;
                        else
                            oImg.at<uchar>(y,x) = iImg.at<uchar>(y,x);
                    }
                }
            }
            break;
            case CV_8S:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        if( iImg.at<char>(y,x) < (char) low )
                            oImg.at<char>(y,x) = (char) low;
                        else if( iImg.at<char>(y,x) > (char) up )
                            oImg.at<char>(y,x) = (char) up;
                        else
                            oImg.at<char>(y,x) = iImg.at<char>(y,x);
                    }
                }
            }
            break;
            case CV_16U:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        if( iImg.at<unsigned short>(y,x) < (unsigned short) low )
                            oImg.at<unsigned short>(y,x) = (unsigned short) low;
                        else if( iImg.at<unsigned short>(y,x) > (unsigned short) up )
                            oImg.at<unsigned short>(y,x) = (unsigned short) up;
                        else
                            oImg.at<unsigned short>(y,x) = iImg.at<unsigned short>(y,x);
                    }
                }
            }
            break;
            case CV_16S:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        if( iImg.at<short>(y,x) < (short) low )
                            oImg.at<short>(y,x) = (short) low;
                        else if( iImg.at<short>(y,x) > (short) up )
                            oImg.at<short>(y,x) = (short) up;
                        else
                            oImg.at<short>(y,x) = iImg.at<short>(y,x);
                    }
                }
            }
            break;    
            case CV_32S:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        if( iImg.at<int>(y,x) < (int) low )
                            oImg.at<int>(y,x) = (int) low;
                        else if( iImg.at<int>(y,x) > (int) up )
                            oImg.at<int>(y,x) = (int) up;
                        else
                            oImg.at<int>(y,x) = iImg.at<int>(y,x);
                    }
                }
            }
            break;
            case CV_32F:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        if( iImg.at<float>(y,x) < (float) low )
                            oImg.at<float>(y,x) = (float) low;
                        else if( iImg.at<float>(y,x) > (float) up )
                            oImg.at<float>(y,x) = (float) up;
                        else
                            oImg.at<float>(y,x) = iImg.at<float>(y,x);
                    }
                }
            }
            break;
            case CV_64F:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        if( iImg.at<double>(y,x) < (double) low )
                            oImg.at<double>(y,x) = (double) low;
                        else if( iImg.at<double>(y,x) > (double) up )
                            oImg.at<double>(y,x) = (double) up;
                        else
                            oImg.at<double>(y,x) = iImg.at<double>(y,x);
                    }
                }
            }
            break;
            default:
            break;
        }
    }
    else if(NbOfChannels == 3)
    {
        for(unsigned int chan = 0; chan < NbOfChannels; chan++)
        {
            switch(NbOfDepth)
            {
                case CV_8U:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            if( iImg.at<cv::Vec3b>(y,x)[chan] < (uchar) low )
                                oImg.at<cv::Vec3b>(y,x)[chan] = (uchar) low;
                            else if( iImg.at<cv::Vec3b>(y,x)[chan] > (uchar) up )
                                oImg.at<cv::Vec3b>(y,x)[chan] = (uchar) up;
                            else
                                oImg.at<cv::Vec3b>(y,x)[chan] = iImg.at<cv::Vec3b>(y,x)[chan];
                        }
                    }
                }
                break;
                //case CV_8S:
                //    {
                //        for(unsigned int x = 0; x < iImg.rows; x++)
                //        {
                //            for(unsigned int y = 0; y < iImg.cols; y++)
                //            {
                //                if( iImg.at<cv::Vec3s>(y,x)[chan] < (char) low )
                //                    oImg.at<cv::Vec3s>(y,x)[chan] = (char) low;
                //                else if( iImg.at<cv::Vec3s>(y,x)[chan] > (char) up )
                //                    oImg.at<cv::Vec3s>(y,x)[chan] = (char) up;
                //                else
                //                    oImg.at<cv::Vec3s>(y,x)[chan] = iImg.at<cv::Vec3s>(y,x)[chan];
                //            }
                //        }
                //    }
                //    break;
                case CV_16U:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            if( iImg.at<cv::Vec3w>(y,x)[chan] < (unsigned short) low )
                                oImg.at<cv::Vec3w>(y,x)[chan] = (unsigned short) low;
                            else if( iImg.at<cv::Vec3w>(y,x)[chan] > (unsigned short) up )
                                oImg.at<cv::Vec3w>(y,x)[chan] = (unsigned short) up;
                            else
                                oImg.at<cv::Vec3w>(y,x)[chan] = iImg.at<cv::Vec3w>(y,x)[chan];
                        }
                    }
                }
                break;
                case CV_16S:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            if( iImg.at<cv::Vec3s>(y,x)[chan] < (short) low )
                                oImg.at<cv::Vec3s>(y,x)[chan] = (short) low;
                            else if( iImg.at<cv::Vec3s>(y,x)[chan] > (short) up )
                                oImg.at<cv::Vec3s>(y,x)[chan] = (short) up;
                            else
                                oImg.at<cv::Vec3s>(y,x)[chan] = iImg.at<cv::Vec3s>(y,x)[chan];
                        }
                    }
                }
                break;    
                case CV_32S:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            if( iImg.at<cv::Vec3i>(y,x)[chan] < (int) low )
                                oImg.at<cv::Vec3i>(y,x)[chan] = (int) low;
                            else if( iImg.at<cv::Vec3i>(y,x)[chan] > (int) up )
                                oImg.at<cv::Vec3i>(y,x)[chan] = (int) up;
                            else
                                oImg.at<cv::Vec3i>(y,x)[chan] = iImg.at<cv::Vec3i>(y,x)[chan];
                        }
                    }
                }
                break;
                case CV_32F:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            if( iImg.at<cv::Vec3f>(y,x)[chan] < (float) low )
                                oImg.at<cv::Vec3f>(y,x)[chan] = (float) low;
                            else if( iImg.at<cv::Vec3f>(y,x)[chan] > (float) up )
                                oImg.at<cv::Vec3f>(y,x)[chan] = (float) up;
                            else
                                oImg.at<cv::Vec3f>(y,x)[chan] = iImg.at<cv::Vec3f>(y,x)[chan];
                        }
                    }
                }
                break;
                case CV_64F:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            if( iImg.at<cv::Vec3d>(y,x)[chan] < (double) low )
                                oImg.at<cv::Vec3d>(y,x)[chan] = (double) low;
                            else if( iImg.at<cv::Vec3d>(y,x)[chan] > (double) up )
                                oImg.at<cv::Vec3d>(y,x)[chan] = (double) up;
                            else
                                oImg.at<cv::Vec3d>(y,x)[chan] = iImg.at<cv::Vec3d>(y,x)[chan];
                        }
                    }
                }
                break;
                default:
                break;
            }
        }
    }
}


/** Image strech */
template<class T>
static void strech ( const cv::Mat& iImg, cv::Mat& oImg, T low, T up )
{
    if(low < up)
    {
        std::cerr << "lower bound is smaller than upper bound!" << std::endl;
        exit(1);
    }

    unsigned int NbOfDepth = iImg.depth();
    unsigned int NbOfChannels = iImg.channels();
    
    if(NbOfChannels == 1)
    {
        double minVal = 0.0, maxVal = 0.0, diff = 0.0, temp = 0.0;
        cv::minMaxLoc(iImg, &minVal, &maxVal);
        diff = maxVal - minVal;
        
        if(diff <= FLT_EPSILON)
        {
            oImg = cv::Mat::zeros(iImg.size(), iImg.type());
            return;
        }

        switch(NbOfDepth)
        {
            case CV_8U:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        temp = (double)iImg.at<uchar>(y,x);
                        oImg.at<uchar>(y,x) = (uchar)( (temp - minVal)/
                            diff*(double)(up-low)+(double)low );
                    }
                }
            }
            break;
            case CV_8S:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        temp = (double)iImg.at<char>(y,x);
                        oImg.at<char>(y,x) = (char)( (temp - minVal)/
                            diff*(double)(up-low)+(double)low );
                    }
                }
            }
            break;
            case CV_16U:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        temp = (double)iImg.at<unsigned short>(y,x);
                        oImg.at<unsigned short>(y,x) = 
                            (unsigned short)( (temp - minVal)/
                            diff*(double)(up-low)+(double)low );
                    }
                }
            }
            break;
            case CV_16S:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        temp = (double)iImg.at<short>(y,x);
                        oImg.at<short>(y,x) = (short)( (temp - minVal)/diff
                            *(double)(up-low)+(double)low );
                    }
                }
            }
            break;    
            case CV_32S:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        temp = (double)iImg.at<int>(y,x);
                        oImg.at<int>(y,x) = (int)( (temp - minVal)/diff
                            *(double)(up-low)+(double)low );
                    }
                }
            }
            break;
            case CV_32F:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        temp = (double)iImg.at<float>(y,x);
                        oImg.at<float>(y,x) = (float)( (temp - minVal)/diff
                            *(double)(up-low)+(double)low );
                    }
                }
            }
            break;
            case CV_64F:
            {
                for(unsigned int x = 0; x < iImg.rows; x++)
                {
                    for(unsigned int y = 0; y < iImg.cols; y++)
                    {
                        temp = (double)iImg.at<double>(y,x);
                        oImg.at<double>(y,x) = (double)( (temp - minVal)/diff
                            *(double)(up-low)+(double)low );
                    }
                }
            }
            break;
            default:
            break;
        }
    }
    else if(NbOfChannels == 3)
    {
        double  minVal_b = 0.0, maxVal_b = 0.0, 
                minVal_g = 0.0, maxVal_g = 0.0, 
                minVal_r = 0.0, maxVal_r = 0.0, 
                minVal = 0.0, maxVal = 0.0,
                diff = 0.0, temp = 0.0;
        std::vector<cv::Mat> bgr;
        cv::split(iImg, bgr);

        cv::minMaxLoc(bgr[0], &minVal_b, &maxVal_b);
        cv::minMaxLoc(bgr[1], &minVal_g, &maxVal_g);
        cv::minMaxLoc(bgr[2], &minVal_r, &maxVal_r);
        minVal = cv::min(cv::min(minVal_b, minVal_g), minVal_r);
        maxVal = cv::max(cv::max(maxVal_b, maxVal_g), maxVal_r);
        diff = maxVal - minVal;
        
        if(diff <= FLT_EPSILON)
        {
            oImg = cv::Mat::zeros(iImg.size(), iImg.type());
            return;
        }
        
        for(unsigned int chan = 0; chan < NbOfChannels; chan++)
        {
            switch(NbOfDepth)
            {
                case CV_8U:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            temp = (double)iImg.at<cv::Vec3b>(y,x)[chan];
                            oImg.at<cv::Vec3b>(y,x)[chan] = (uchar)( (temp - minVal)
                                /diff*(double)(up-low)+(double)low );
                        }
                    }
                }
                break;
//                case CV_8S:
//                {
//                    for(unsigned int x = 0; x < iImg.rows; x++)
//                    {
//                        for(unsigned int y = 0; y < iImg.cols; y++)
//                        {
//                            if( iImg.at<cv::Vec3s>(y,x)[chan] < (char) low )
//                                oImg.at<cv::Vec3s>(y,x)[chan] = (char) low;
//                            else if( iImg.at<cv::Vec3s>(y,x)[chan] > (char) up )
//                                oImg.at<cv::Vec3s>(y,x)[chan] = (char) up;
//                            else
//                                oImg.at<cv::Vec3s>(y,x)[chan] = iImg.at<cv::Vec3s>(y,x)[chan];
//                        }
//                    }
//                }
//                break;
                case CV_16U:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            temp = (double)iImg.at<cv::Vec3w>(y,x)[chan];
                            oImg.at<cv::Vec3w>(y,x)[chan] = 
                                (unsigned short)( (temp - minVal)/diff
                                *(double)(up-low)+(double)low );
                        }
                    }
                }
                break;
                case CV_16S:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            temp = (double)iImg.at<cv::Vec3s>(y,x)[chan];
                            oImg.at<cv::Vec3s>(y,x)[chan] = 
                                (short)( (temp - minVal)/diff
                                *(double)(up-low)+(double)low );
                        }
                    }
                }
                break;    
                case CV_32S:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            temp = (double)iImg.at<cv::Vec3i>(y,x)[chan];
                            oImg.at<cv::Vec3i>(y,x)[chan] = 
                                (int)( (temp - minVal)/diff
                                *(double)(up-low)+(double)low );
                        }
                    }
                }
                break;
                case CV_32F:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            temp = (double)iImg.at<cv::Vec3f>(y,x)[chan];
                            oImg.at<cv::Vec3f>(y,x)[chan] = 
                                (float)( (temp - minVal)/diff
                                *(double)(up-low)+(double)low );
                        }
                    }
                }
                break;
                case CV_64F:
                {
                    for(unsigned int x = 0; x < iImg.rows; x++)
                    {
                        for(unsigned int y = 0; y < iImg.cols; y++)
                        {
                            temp = (double)iImg.at<cv::Vec3d>(y,x)[chan];
                            oImg.at<cv::Vec3d>(y,x)[chan] = 
                                (double)( (temp - minVal)/diff
                                *(double)(up-low)+(double)low );
                        }
                    }
                }
                break;
                default:
                break;
            }
        }
    }
}


/** cv::Point2f division */
template<class T>
static cv::Point2f operator / ( const cv::Point2f& pt, T t)
{
    if (fabs((float)t) < FLT_MIN)
    {
        std::cerr << "divided by zero" << std::endl;
        exit(0);
    }
    cv::Point2f res;
    res.x = pt.x / t;
    res.y = pt.y / t;
    return res;
}


/** cv::Point2f add */
static cv::Point2f operator+ ( const cv::Point2f& pt1, const cv::Point2f& pt2 )
{
    cv::Point2f res;
    res.x = pt1.x + pt2.x;
    res.y = pt1.y + pt2.y;
    return res;
}


/** cv::Point2f subtraction */
static cv::Point2f operator- ( const cv::Point2f& pt1, const cv::Point2f& pt2 )
{
    cv::Point2f res;
    res.x = pt1.x - pt2.x;
    res.y = pt1.y - pt2.y;
    return res;
}


/** cv::Point2f multiplication */
template <class T>
static cv::Rect operator* ( const cv::Rect& rect1, T value )
{
    cv::Rect res;
    res.x = rect1.x * value;
    res.y = rect1.y * value;
    res.width = rect1.width * value;
    res.height = rect1.height * value;
    return res;
}


/**
 * @author      JIA Pei
 * @version     2016-08-28
 * @brief       bilinear interpolation for RGB image
 * @param       img     Input   - gray image
 * @param       pt      Input   - point in float
 * @return      float   Output  - bilinear interpolation
*/
static float getGraySubpix(const cv::Mat& img, const cv::Point2f& pt)
{
    if(img.empty())
    {
        std::cout << "img is empty. " << std::endl;
        exit(EXIT_FAILURE);
    }
    
    unsigned int channels = img.channels();
    unsigned int depth = img.depth();
    if (!(channels == 1))
    {
        std::cerr << "Gray image must be of channels==1." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    int x = (int)pt.x;
    int y = (int)pt.y;

    int x0 = cv::borderInterpolate(x,   img.cols, cv::BORDER_REFLECT_101);
    int x1 = cv::borderInterpolate(x+1, img.cols, cv::BORDER_REFLECT_101);
    int y0 = cv::borderInterpolate(y,   img.rows, cv::BORDER_REFLECT_101);
    int y1 = cv::borderInterpolate(y+1, img.rows, cv::BORDER_REFLECT_101);

    float a = pt.x - (float)x;
    float c = pt.y - (float)y;
    
    float gray = (float)((img.at<uchar>(y0, x0) * (1.f - a) + img.at<uchar>(y0, x1) * a) * (1.f - c)
                       + (img.at<uchar>(y1, x0) * (1.f - a) + img.at<uchar>(y1, x1) * a) * c);
    
    return gray;
}

/**
 * @author      JIA Pei
 * @version     2016-08-28
 * @brief       bilinear interpolation for RGB image
 * @param       img                 Input   - color image
 * @param       pt                  Input   - point in float
 * @return      std::vector<float>  Output  - bilinear interpolation
*/
static std::vector<float> getColorSubpix(const cv::Mat& img, const cv::Point2f& pt)
{
    if(img.empty())
    {
        std::cout << "img is empty. " << std::endl;
        exit(EXIT_FAILURE);
    }
    
    unsigned int channels = img.channels();
    unsigned int depth = img.depth();
    if (!(channels == 3))
    {
        std::cerr << "Color image must be of channels==3." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    int x = (int)pt.x;
    int y = (int)pt.y;

    int x0 = cv::borderInterpolate(x,   img.cols, cv::BORDER_REFLECT_101);
    int x1 = cv::borderInterpolate(x+1, img.cols, cv::BORDER_REFLECT_101);
    int y0 = cv::borderInterpolate(y,   img.rows, cv::BORDER_REFLECT_101);
    int y1 = cv::borderInterpolate(y+1, img.rows, cv::BORDER_REFLECT_101);

    float a = pt.x - (float)x;
    float c = pt.y - (float)y;
    
    std::vector<float> res(3);
    res[0] = (float)((img.at<cv::Vec3b>(y0, x0)[0] * (1.f - a) + img.at<cv::Vec3b>(y0, x1)[0] * a) * (1.f - c)
                   + (img.at<cv::Vec3b>(y1, x0)[0] * (1.f - a) + img.at<cv::Vec3b>(y1, x1)[0] * a) * c);
    res[1] = (float)((img.at<cv::Vec3b>(y0, x0)[1] * (1.f - a) + img.at<cv::Vec3b>(y0, x1)[1] * a) * (1.f - c)
                   + (img.at<cv::Vec3b>(y1, x0)[1] * (1.f - a) + img.at<cv::Vec3b>(y1, x1)[1] * a) * c);
    res[2] = (float)((img.at<cv::Vec3b>(y0, x0)[2] * (1.f - a) + img.at<cv::Vec3b>(y0, x1)[2] * a) * (1.f - c)
                   + (img.at<cv::Vec3b>(y1, x0)[2] * (1.f - a) + img.at<cv::Vec3b>(y1, x1)[2] * a) * c);

    return res;
}


/**
 * @Ref    http://www.newton.dep.anl.gov/newton/askasci/1995/math/MATH061.HTM
 *        abs(Ar + Bs + C)/sqrt(A^2 + B^2)
*/
static float cvDistFromAPoint2ALine2D(  const cv::Point2f& pt,
                                        const std::vector<float>& lp)
{
    return ( fabs(lp[0]*pt.x+lp[1]*pt.y+lp[2]) / 
        sqrt(lp[0]*lp[0]+lp[1]*lp[1]) );
}


/**
* @brief    Save all images in sequence in a specific folder
* @param    imgs        -- Input        the source images
* @param    fdname      -- Input        the specific folder
* @ref      OpenCV 2.x documentation
 */
static void SaveSequentialImagesInFolder(   const std::vector<cv::Mat>& imgs,
                                            const std::string& fdname)
{
    if (!boost::filesystem::is_directory(fdname) )
        boost::filesystem::create_directory( fdname );

    std::stringstream ssi;
    std::string stri;
    std::string filename;
    unsigned int NbOfImages = imgs.size();
    for(unsigned int i = 0; i < NbOfImages; i++)
    {
        ssi << i;
        ssi >> stri;
        if(stri.length() == 1)
            filename = fdname + "/0" + stri + ".jpg";
        else if(stri.length() == 2)
            filename = fdname + "/" + stri + ".jpg";
        cv::imwrite(filename.c_str(), imgs[i] );
        ssi.clear();
    }
}


/**
 * @brief    convolve using DFT.
 * @param    A    -- Input    the source image
 * @param    B    -- Input    the filtering template
 * @param    C    -- Output    the convoluted image, must of the same size as A
 * @ref      OpenCV 2.x documentation
 */
static void convolveDFT(const cv::Mat& A, const cv::Mat& B, cv::Mat& C)
{
    // reallocate the output array if needed
    //    cv::Mat C(A.rows + B.rows - 1, A.cols + B.cols - 1, A.type());
    cv::Size dftSize;
    // compute the size of DFT transform
    dftSize.width = cv::getOptimalDFTSize(A.cols + B.cols - 1);
    dftSize.height = cv::getOptimalDFTSize(A.rows + B.rows - 1);
    // allocate temporary buffers and initialize them with 0’s
    cv::Mat tempA(dftSize, A.type(), cv::Scalar::all(0));
    cv::Mat tempB(dftSize, B.type(), cv::Scalar::all(0));
    // copy A and B to the top-left corners of tempA and tempB, respectively
    cv::Mat roiA(tempA, cv::Rect(0,0,A.cols,A.rows));
    A.copyTo(roiA);
    cv::Mat roiB(tempB, cv::Rect(0,0,B.cols,B.rows));
    B.copyTo(roiB);
    // now transform the padded A & B in-place;
    // use "nonzeroRows" hint for faster processing
    cv::dft(tempA, tempA, 0, A.rows);
    cv::dft(tempB, tempB, 0, B.rows);
    // multiply the spectrums;
    // the function handles packed spectrum representations well
    cv::mulSpectrums(tempA, tempB, tempA, 0);
    // transform the product back from the frequency domain.
    // Even though all the result rows will be non-zero,
    // we need only the first C.rows of them, and thus we
    // pass nonzeroRows == C.rows
    cv::dft(tempA, tempA, cv::DFT_INVERSE + cv::DFT_SCALE, A.rows + B.rows - 1);
    // now copy the result back to C.
    //    tempA(cv::Rect(0, 0, C.cols, C.rows)).copyTo(C);
    tempA(cv::Rect(B.cols/2, B.rows/2, A.cols, A.rows)).copyTo(C);
    // all the temporary buffers will be deallocated automatically
}



#ifdef _WIN32
// Here, fs must have been opened for writing already.
// Explained by Pei JIA
static void writeSkeletonData(const NUI_SKELETON_FRAME& skeleton, std::fstream& fs)
{
    fs << skeleton.liTimeStamp.QuadPart << " "
        << skeleton.dwFrameNumber << " "
        << skeleton.dwFlags << " "
        << skeleton.vFloorClipPlane.x << " "
        << skeleton.vFloorClipPlane.y << " "
        << skeleton.vFloorClipPlane.z << " "
        << skeleton.vFloorClipPlane.w << " "
        << skeleton.vNormalToGravity.x << " "
        << skeleton.vNormalToGravity.y << " "
        << skeleton.vNormalToGravity.z << " "
        << skeleton.vNormalToGravity.w << std::endl;
    for (int i = 0; i < NUI_SKELETON_COUNT; i++)
    {
        fs << skeleton.SkeletonData[i].eTrackingState << " "
            << skeleton.SkeletonData[i].dwTrackingID << " "
            << skeleton.SkeletonData[i].dwEnrollmentIndex << " "
            << skeleton.SkeletonData[i].dwUserIndex << " "
            << skeleton.SkeletonData[i].Position.x << " "
            << skeleton.SkeletonData[i].Position.y << " "
            << skeleton.SkeletonData[i].Position.z << " "
            << skeleton.SkeletonData[i].Position.w << " " << std::endl;
        
        for(int j = 0; j < 20; j++)
        {
            fs << skeleton.SkeletonData[i].SkeletonPositions[j].x << " "
                << skeleton.SkeletonData[i].SkeletonPositions[j].y << " "
                << skeleton.SkeletonData[i].SkeletonPositions[j].z << " "
                << skeleton.SkeletonData[i].SkeletonPositions[j].w << " ";
        }

        for(int j = 0; j < 20; j++)
        {
            fs << skeleton.SkeletonData[i].eSkeletonPositionTrackingState[j] << " ";
        }

        fs << skeleton.SkeletonData[i].dwQualityFlags << " ";
    }

    fs << std::endl;
}

// Here, fs must have been opened for reading already.
// Explained by Pei JIA
static void readSkeletonData(std::fstream& fs, NUI_SKELETON_FRAME& skeleton)
{
    fs >> skeleton.liTimeStamp.QuadPart
        >> skeleton.dwFrameNumber
        >> skeleton.dwFlags
        >> skeleton.vFloorClipPlane.x
        >> skeleton.vFloorClipPlane.y
        >> skeleton.vFloorClipPlane.z
        >> skeleton.vFloorClipPlane.w
        >> skeleton.vNormalToGravity.x
        >> skeleton.vNormalToGravity.y
        >> skeleton.vNormalToGravity.z
        >> skeleton.vNormalToGravity.w;
    for (int i = 0; i < NUI_SKELETON_COUNT; i++)
    {
        int tmpTrackingState;
        fs >> tmpTrackingState;
        skeleton.SkeletonData[i].eTrackingState = (NUI_SKELETON_TRACKING_STATE)tmpTrackingState;
        fs	>> skeleton.SkeletonData[i].dwTrackingID
            >> skeleton.SkeletonData[i].dwEnrollmentIndex
            >> skeleton.SkeletonData[i].dwUserIndex
            >> skeleton.SkeletonData[i].Position.x
            >> skeleton.SkeletonData[i].Position.y
            >> skeleton.SkeletonData[i].Position.z
            >> skeleton.SkeletonData[i].Position.w;

        for(int j = 0; j < 20; j++)
        {
            fs >> skeleton.SkeletonData[i].SkeletonPositions[j].x
                >> skeleton.SkeletonData[i].SkeletonPositions[j].y
                >> skeleton.SkeletonData[i].SkeletonPositions[j].z
                >> skeleton.SkeletonData[i].SkeletonPositions[j].w;
        }

        for(int j = 0; j < 20; j++)
        {
            int tmpSkeletonPositionTrackingState;
            fs >> tmpSkeletonPositionTrackingState;
            skeleton.SkeletonData[i].eSkeletonPositionTrackingState[j] = NUI_SKELETON_POSITION_TRACKING_STATE(tmpSkeletonPositionTrackingState);
        }

        fs >> skeleton.SkeletonData[i].dwQualityFlags;
    }
}
#endif


#endif  // __VO_CVCOMMON_H__

