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


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <boost/filesystem.hpp>

// Explained by JIA Pei. 2009-07-31. #include <windows.h> is a must for <GL/gl.h> and <GL.glu.h>
//#ifdef _WIN32
//#include <windows.h>
//#endif
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/freeglut.h>

#include "VO_TextureModel.h"
#include "VO_CVCommon.h"


/** Default Constructor */
VO_TextureModel::VO_TextureModel()
{
    this->init();
}


/** Initialization */
void VO_TextureModel::init()
{
    this->m_iTextureRepresentationMethod        = VO_Features::DIRECT;
    this->m_iNbOfTextureRepresentations         = 0;
    this->m_iNbOfChannels                       = 1;
    this->m_iNbOfPixels                         = 0;
    this->m_iNbOfTextures                       = 0;
    this->m_iNbOfEigenTexturesAtMost            = 0;
    this->m_iNbOfTextureEigens                  = 0;
    this->m_fAverageTextureStandardDeviation    = 0.0f;
    this->m_fTruncatedPercent_Texture           = 0.95f;
    this->m_vTextures.clear();
    this->m_vNormalizedTextures.clear();
    this->m_vTemplatePointWarpInfo.clear();
    this->m_vNormalizedPointWarpInfo.clear();
}


VO_TextureModel::~VO_TextureModel()
{
    this->m_vTextures.clear();
    this->m_vNormalizedTextures.clear();
    this->m_vTemplatePointWarpInfo.clear();
    this->m_vNormalizedPointWarpInfo.clear();
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Calculate point warping information
 * @param          triangles           Input - a std::vector of all triangles
 * @param          ch                  Input - convex hull
 * @param          warpInfo            Input - information of a std::vector of warping points
 * @return         unsigned int        points (actually pixels) inside the template face
 * @note           Obviously, triangles and ch contain duplicated information
*/
unsigned int VO_TextureModel::VO_CalcPointWarpingInfo(const std::vector <VO_Triangle2DStructure>& templateTriangles, std::vector<VO_WarpingPoint>& warpInfo)
{
    unsigned int NbOfPixels     = 0;

    cv::Rect rect                   = VO_TextureModel::VO_CalcBoundingRectFromTriangles(templateTriangles);

    for (unsigned int i = 0; i < rect.height; i++)
    {
        for (unsigned int j = 0; j < rect.width; j++)
        {
            // JIA Pei. 2006-11-25. You will see the following (int) is very important
            // without (int), the result here is not correct at all!!
            cv::Point2f pt = cv::Point2f((float)j, (float)i);

            int k = VO_Triangle2DStructure::IsPointInTriangles(pt,templateTriangles);
            if(k>=0)
            {
                VO_WarpingPoint tempPixelTriangle;

                // necessary for all methods
                tempPixelTriangle.SetPosition(pt);
                tempPixelTriangle.SetTriangleIndex(k);
                tempPixelTriangle.SetPointIndex(NbOfPixels);
                tempPixelTriangle.SetTriangle2DStructure(templateTriangles[k] );

                // Very important!! Note by JIA Pei, push_back cannot perform on 2-D std::vectors
                warpInfo.push_back (tempPixelTriangle);

                NbOfPixels ++;
            }
        }
    }

    return NbOfPixels;
}


/**
 * @author         JIA Pei, YAO Wei
 * @version        2010-02-10
 * @brief          Load one VO_Texture from an image based on VO_Shape
 * @param          iShape                  Input     - the shape
 * @param          img                     Input     - image
 * @param          templateTriangles       Input     - the composed face template triangles
 * @param          warpInfo                Input     - warping information for all pixels in template face
 * @param          oTexture                Output     - the extracted texture
 * @param          trm                     Input     - texture representation method
 * @return         bool                    loading succeed or not?
*/
bool VO_TextureModel::VO_LoadOneTextureFromShape(const VO_Shape& iShape, 
                                                const cv::Mat& img,
                                                const std::vector<VO_Triangle2DStructure>& templateTriangles,
                                                const std::vector<VO_WarpingPoint>& warpInfo,
                                                VO_Texture& oTexture, 
                                                int trm)
{
    std::ofstream fs;
    fs.open("loadTextureTime.txt", std::ios::app);

double time0 = (double)cvGetTickCount();

    // make sure all shape points are inside the image
    if ( !VO_ShapeModel::VO_IsShapeInsideImage(iShape, img) )
    {
        std::cout << "The shape goes out of the image" << std::endl;
        std::cout << "Shape =" << iShape << std::endl;
        std::cout << "cols=" << img.cols << " rows=" << img.rows << std::endl;

        return false;
    }


    unsigned int NbOfShapeDim           = iShape.GetNbOfDim();
    unsigned int NbOfPixels             = warpInfo.size();
    unsigned int NbOfChannels           = img.channels();
    unsigned int NbOfTextures           = NbOfPixels*NbOfChannels;
    unsigned int NbOfTriangles          = templateTriangles.size();
    oTexture.m_MatTexture               = cv::Mat_<float>::zeros(NbOfChannels, NbOfPixels);

    cv::Point2f src[3], dst[3];
    std::vector< cv::Mat_<float> > matWarping;
    matWarping.resize(NbOfTriangles);


    // calculate all the mapping (for speeding up) 95 mapping totally
    for (unsigned int j = 0; j < NbOfTriangles; j++ )
    {
        // Get the affine transformation for each triangle pair.
        src[0] = templateTriangles[j].GetA2DPoint(0);
        src[1] = templateTriangles[j].GetA2DPoint(1);
        src[2] = templateTriangles[j].GetA2DPoint(2);

        dst[0] = iShape.GetA2DPoint(templateTriangles[j].m_vVertexIndexes[0]);
        dst[1] = iShape.GetA2DPoint(templateTriangles[j].m_vVertexIndexes[1]);
        dst[2] = iShape.GetA2DPoint(templateTriangles[j].m_vVertexIndexes[2]);

        matWarping[j] = cv::getAffineTransform( src, dst );
    }

    cv::Rect rect = iShape.GetShapeBoundRect();
    // Why +1? A must.
    // The bounded rectangle could be (0, 0, 2, 2)
    // That means the width of the image is 2-0+1=3 (from the aspect of pixel)
    rect.width +=1; rect.height +=1;

double time1 = (double)cvGetTickCount();
double elapsed = (time1 -  time0 )/  (cvGetTickFrequency()*1000.);
fs << "Before Mapping -- Step 1 of warping time: " << elapsed << "millisec."  << std::endl;

    cv::Mat Img2BExtracted;

    switch(trm)
    {
    case VO_Features::LAPLACE:
        {
            cv::Mat tempImg2BExtracted = cv::Mat::zeros(img.size(), CV_32F);
            img.convertTo( tempImg2BExtracted, tempImg2BExtracted.type() );

            // Explained by JIA Pei, 2008-03-09.
            // Why I don't do cvCopy(tempImg2BExtracted, tempExcavated); right here,
            // but after cvSmooth, cvLaplace, cvAbs?
            // Because we may deal with the boundary and corners much better in this way.
            cv::GaussianBlur( tempImg2BExtracted, tempImg2BExtracted, cv::Size(5, 5), 0.5, 0.5);
            cv::Laplacian( tempImg2BExtracted, tempImg2BExtracted, tempImg2BExtracted.depth(), 3);
            cv::abs(tempImg2BExtracted);

            Img2BExtracted = tempImg2BExtracted(rect);
        }
        break;
    case VO_Features::HARRISCORNER:
        {
            cv::Mat tempImg2BExtracted;

            // Explained by JIA Pei, 2008-03-09.
            // Why I don't do cvCopy(tempImg2BExtracted, tempExcavated); right here,
            // but after cvCornerHarris?
            // Because we may deal with the boundary and corners much better in this way.
            // cvCornerHarris is for one channel

            switch (NbOfChannels)
            {
            case GRAYCHANNELS:
                {
                    cv::cornerHarris( img, tempImg2BExtracted, 3, 3, 0.02);
                    cv::abs(tempImg2BExtracted);
                }
                break;
            case COLORCHANNELS:
            default:
                {
                    std::vector<cv::Mat> bgr, bgrHC;
                    bgrHC.resize(3);
                    cv::split(img, bgr);

                    for(unsigned int i = 0; i < 3; i++)
                    {
                        cv::cornerHarris( bgr[i], bgrHC[i], 3, 3, 0.02);
                    }

                    cv::merge(bgrHC, tempImg2BExtracted);
                    cv::abs(tempImg2BExtracted);
                }
                break;
            }
            
            Img2BExtracted = tempImg2BExtracted(rect);
        }
        break;
    case VO_Features::GABOR: // This might be very slow
        {
        }
        break;
    case VO_Features::SEGMENTATION:
        {
            cv::Mat tempImg2BExtracted = cv::Mat::zeros(img.size(), CV_32F);
            img.convertTo( tempImg2BExtracted, tempImg2BExtracted.type() );
            
            cv::GaussianBlur( tempImg2BExtracted, tempImg2BExtracted, cv::Size(5, 5), 0.5, 0.5);
            Img2BExtracted = tempImg2BExtracted(rect );

            cv::threshold( Img2BExtracted, Img2BExtracted, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU );    // only for single channel images
        }
        break;
    case VO_Features::HISTOGRAMEQUALIZED:
        {
            Img2BExtracted = img(rect);

            switch (NbOfChannels)
            {
            case GRAYCHANNELS:
                cv::equalizeHist( Img2BExtracted, Img2BExtracted );
                break;
            case COLORCHANNELS:
            default:
                {
                    std::vector<cv::Mat> bgr;
                    cv::split(Img2BExtracted, bgr);

                    for(unsigned int i = 0; i < 3; i++)
                        cv::equalizeHist( bgr[i], bgr[i] );

                    cv::merge(bgr, Img2BExtracted);
                }
                break;
            }
        }
        break;
    case VO_Features::DIRECT:
        {
            Img2BExtracted = img(rect);
        }
    default:
        break;
    }

double time2 = (double)cvGetTickCount();
elapsed = (time2 - time1)/  (cvGetTickFrequency()*1000.);
fs << "Mapping -- Step 2 of warping time: " << elapsed << "millisec."  << std::endl;

    //cv::Mat Img4Display = cv::Mat::zeros(Img2BExtracted.size(), CV_8U);
    //Img2BExtracted.convertTo(Img4Display, Img4Display.type());
    //cv::imwrite("testtest.jpg", Img4Display);

    float x;
    float y;
    register int X;
    register int Y ;
    register int X1;
    register int Y1;
    register float s;
    register float t;
    register float s1;
    register float t1;
    float XX, YY;

    if(Img2BExtracted.type() == CV_32FC3)
    {
        for (unsigned int i = 0; i < NbOfPixels; i++ )
        {
            // Explained by Yao Wei. This part causes the slow speed of the warping.
//            // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
//            warpsrc(0, 0) = warpInfo[i].m_CVPosition.x;
//            warpsrc(1, 0) = warpInfo[i].m_CVPosition.y;
//            warpsrc(2, 0) = 1.0;
////          cv::gemm(matWarping[warpInfo[i].m_iTriangleIndex], warpsrc, 1.0, cv::Mat(), 0.0, warpeddst);
//            warpeddst = matWarping[warpInfo[i].m_iTriangleIndex] * warpsrc;
            
            // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
            const cv::Mat_<float>& sss = matWarping[warpInfo[i].m_iTriangleIndex];
            XX = sss(0,0)*warpInfo[i].m_CVPosition.x + sss(0,1)*warpInfo[i].m_CVPosition.y
                +sss(0,2);
            YY = sss(1,0)*warpInfo[i].m_CVPosition.x + sss(1,1)*warpInfo[i].m_CVPosition.y
                +sss(1,2);

            // Revised by Yao Wei. Now, much much faster !!!
            x = XX - rect.x;
            y = YY - rect.y;
            X = cvFloor(x);
            Y = cvFloor(y);
            X1 = cvCeil(x);
            Y1 = cvCeil(y);
            s=x-X;
            t=y-Y;
            s1 = 1.0f - s;
            t1 = 1.0f - t;
            
            for (int j = 0; j < 3; j++)
            {
                oTexture.m_MatTexture(j, i) =
                ( t1 * Img2BExtracted.at<cv::Vec3f>(Y, X)[j] +
                t * Img2BExtracted.at<cv::Vec3f>(Y1, X)[j] ) * s1 +
                ( t1 * Img2BExtracted.at<cv::Vec3f>(Y, X1)[j] +
                t * Img2BExtracted.at<cv::Vec3f>(Y1, X1)[j] ) * s;
            }
        }
    }
    else if(Img2BExtracted.type() == CV_8UC3)
    {
        for (unsigned int i = 0; i < NbOfPixels; i++ )
        {
            // Explained by Yao Wei. This part causes the slow speed of the warping.
//            // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
//            warpsrc(0, 0) = warpInfo[i].m_CVPosition.x;
//            warpsrc(1, 0) = warpInfo[i].m_CVPosition.y;
//            warpsrc(2, 0) = 1.0;
////            cv::gemm(matWarping[warpInfo[i].m_iTriangleIndex], warpsrc, 1.0, cv::Mat(), 0.0, warpeddst);
//            warpeddst = matWarping[warpInfo[i].m_iTriangleIndex] * warpsrc;

            // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
            const cv::Mat_<float>& sss = matWarping[warpInfo[i].m_iTriangleIndex];
            XX = sss(0,0)*warpInfo[i].m_CVPosition.x + sss(0,1)*warpInfo[i].m_CVPosition.y
                +sss(0,2);
            YY = sss(1,0)*warpInfo[i].m_CVPosition.x + sss(1,1)*warpInfo[i].m_CVPosition.y
                +sss(1,2);

            // Revised by Yao Wei. Now, much much faster !!!
            x = XX - rect.x;
            y = YY - rect.y;
            X = cvFloor(x);
            Y = cvFloor(y);
            X1 = cvCeil(x);
            Y1 = cvCeil(y);
            s=x-X;
            t=y-Y;
            s1 = 1.0f - s;
            t1 = 1.0f - t;

            for (int j = 0; j < 3; j++)
            {
                oTexture.m_MatTexture(j, i) =
                ( t1 * Img2BExtracted.at<cv::Vec3b>(Y, X)[j] +
                t * Img2BExtracted.at<cv::Vec3b>(Y1, X)[j] ) * s1 +
                ( t1 * Img2BExtracted.at<cv::Vec3b>(Y, X1)[j] +
                t * Img2BExtracted.at<cv::Vec3b>(Y1, X1)[j] ) * s;
            }
        }
    }
    else if(Img2BExtracted.type() == CV_32FC1)
    {
        for (unsigned int i = 0; i < NbOfPixels; i++ )
        {
            // Explained by Yao Wei. This part causes the slow speed of the warping.
//            // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
//            warpsrc(0, 0) = warpInfo[i].m_CVPosition.x;
//            warpsrc(1, 0) = warpInfo[i].m_CVPosition.y;
//            warpsrc(2, 0) = 1.0;
////          cv::gemm(matWarping[warpInfo[i].m_iTriangleIndex], warpsrc, 1.0, cv::Mat(), 0.0, warpeddst);
//            warpeddst = matWarping[warpInfo[i].m_iTriangleIndex] * warpsrc;

            // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
            const cv::Mat_<float>& sss = matWarping[warpInfo[i].m_iTriangleIndex];
            XX = sss(0,0)*warpInfo[i].m_CVPosition.x + sss(0,1)*warpInfo[i].m_CVPosition.y
                +sss(0,2);
            YY = sss(1,0)*warpInfo[i].m_CVPosition.x + sss(1,1)*warpInfo[i].m_CVPosition.y
                +sss(1,2);

            // Revised by Yao Wei. Now, much much faster !!!
            x = XX - rect.x;
            y = YY - rect.y;
            X = cvFloor(x);
            Y = cvFloor(y);
            X1 = cvCeil(x);
            Y1 = cvCeil(y);
            s=x-X;
            t=y-Y;
            s1 = 1.0f - s;
            t1 = 1.0f - t;

            oTexture.m_MatTexture(0, i) =
            ( t1 * Img2BExtracted.at<float>(Y, X) +
            t * Img2BExtracted.at<float>(Y1, X) ) * s1 +
            ( t1 * Img2BExtracted.at<float>(Y, X1) +
            t * Img2BExtracted.at<float>(Y1, X1) ) * s;
        }
    }
    else if(Img2BExtracted.type() == CV_8UC1)
    {
        for (unsigned int i = 0; i < NbOfPixels; i++ )
        {
            // Explained by Yao Wei. This part causes the slow speed of the warping.
//            // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
//            warpsrc(0, 0) = warpInfo[i].m_CVPosition.x;
//            warpsrc(1, 0) = warpInfo[i].m_CVPosition.y;
//            warpsrc(2, 0) = 1.0;
////            cv::gemm(matWarping[warpInfo[i].m_iTriangleIndex], warpsrc, 1.0, cv::Mat(), 0.0, warpeddst);
//            warpeddst = matWarping[warpInfo[i].m_iTriangleIndex] * warpsrc;
            

            // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
            const cv::Mat_<float>& sss = matWarping[warpInfo[i].m_iTriangleIndex];
            XX = sss(0,0)*warpInfo[i].m_CVPosition.x + sss(0,1)*warpInfo[i].m_CVPosition.y
                +sss(0,2);
            YY = sss(1,0)*warpInfo[i].m_CVPosition.x + sss(1,1)*warpInfo[i].m_CVPosition.y
                +sss(1,2);

            // Revised by Yao Wei. Now, much much faster !!!
            x = XX - rect.x;
            y = YY - rect.y;
            X = cvFloor(x);
            Y = cvFloor(y);
            X1 = cvCeil(x);
            Y1 = cvCeil(y);
            s=x-X;
            t=y-Y;
            s1 = 1.0f - s;
            t1 = 1.0f - t;

            oTexture.m_MatTexture(0, i) =
            ( t1 * Img2BExtracted.at<uchar>(Y, X) +
            t * Img2BExtracted.at<uchar>(Y1, X) ) * s1 +
            ( t1 * Img2BExtracted.at<uchar>(Y, X1) +
            t * Img2BExtracted.at<uchar>(Y1, X1) ) * s;
        }
    }
double time3 = (double)cvGetTickCount();
elapsed = (time3 - time2)/  (cvGetTickFrequency()*1000.);
fs << "Mapping -- Step 3 of warping time: " << elapsed << "millisec."  << std::endl;

//cv::Rect rect1                   = VO_TextureModel::VO_CalcBoundingRectFromTriangles(templateTriangles);
//cv::Mat otmpImg;
//if(NbOfChannels == 1)
//    otmpImg = cv::Mat::zeros(Size(rect1.width, rect1.height), CV_8UC1);
//else if(NbOfChannels == 3)
//    otmpImg = cv::Mat::zeros(Size(rect1.width, rect1.height), CV_8UC3);
//VO_TextureModel::VO_PutOneTextureToTemplateShape(oTexture, templateTriangles, otmpImg);
//cv::imwrite("ttttt.jpg", otmpImg);
///** How many triangles totally */
//std::string trianglestr;
//std::stringstream ssi;
//std::string stri;
//static int NbOfImages = 0;
//ssi << NbOfImages;
//ssi >> stri;
//if(stri.length() == 2)
//    trianglestr = "0" + stri + ".jpg";
//else if(stri.length() == 1)
//    trianglestr = "00" + stri + ".jpg";
//else
//    trianglestr = stri + ".jpg";
//
//cv::imwrite(trianglestr.c_str(), otmpImg);
//
//ssi.clear();
//NbOfImages++;

    fs.close();
    return true;

}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Normalize all textures - 2-norm all to "1"
 * @param          vTextures               Input     - all textures before normalization
 * @param          normalizedTextures      Output    - all textures after normalization
 * @return         return                  float     average texture size of all textures
*/
float VO_TextureModel::VO_NormalizeAllTextures(const std::vector<VO_Texture>& vTextures, std::vector<VO_Texture>& normalizedTextures)
{
    unsigned int NbOfSamples                    = vTextures.size();
    unsigned int NbOfPixels                       = vTextures[0].GetNbOfPixels();
    float averageTextureStandardDeviation       = 0.0f;

    normalizedTextures = vTextures;

    for(unsigned int i = 0; i < NbOfSamples; i++)
    {
        averageTextureStandardDeviation += normalizedTextures.at(i).GetStandardizedTextureNorm();
        normalizedTextures[i].Normalize();
    }
    averageTextureStandardDeviation /= (float)NbOfSamples;

    return averageTextureStandardDeviation;
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Rescale the normalizetextures so that meantexture's 2-norm could be "1"
 * @param          meanNormalizeTexture    Input - meannormalizedtexture that all normalizedtextures should rescale to
 * @param          normalizedTextures      Input and Output - normalized texture and normalized rescaled texture
 * @return         void
*/
void VO_TextureModel::VO_RescaleAllNormalizedTextures(const VO_Texture& meanNormalizeTexture,
                                                        std::vector<VO_Texture>& normalizedTextures)
{
    unsigned int NbOfSamples = normalizedTextures.size();

    // Explained by JIA Pei. 2010-02-10. scale back so that the mean shape size is equal to 1.0
    for(unsigned int i = 0; i < NbOfSamples; i++)
    {
        VO_TextureModel::VO_RescaleOneNormalizedTexture( meanNormalizeTexture, normalizedTextures[i] );
    }
}


/**
 * @author         JIA Pei
 * @version        2010-02-20
 * @brief          Rescale the normalizedTexture to the already trained meanNormalizeTexture
 * @param          meanNormalizeTexture    Input - meanNormalizeTexture that all normalizedTextures should rescale to
 * @param          normalizedTexture       Input and Output - normalized texture and normalized rescaled texture
*/
void VO_TextureModel:: VO_RescaleOneNormalizedTexture(const VO_Texture& meanNormalizeTexture,
                                                        VO_Texture& normalizedTexture)
{
    float ts = sqrt ( fabs(normalizedTexture.dot(meanNormalizeTexture) ) );
    normalizedTexture.Scale( 1.0f/ts );
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Calculate mean texture
 * @param          vTextures         Input     - all textures
 * @param          meanTexture       Output     - mean texture
*/
void VO_TextureModel::VO_CalcMeanTexture(const std::vector<VO_Texture>& vTextures, VO_Texture& meanTexture)
{
    unsigned int NbOfSamples    = vTextures.size();
    meanTexture = vTextures[0];

    for(unsigned int i = 1; i < NbOfSamples; i++)
    {
        meanTexture += vTextures[i];
    }

    meanTexture /= (float)NbOfSamples;
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Put one texture into the template shape with a corresponding warp
 * @param          texture                 Input
 * @param          triangles               Input     - template triangle, contains warping information
 * @param          oImg                    Output
 * @note           All texture std::vectors are of the same size. So, you can't put it into the respective triangulation
                   for respective image. You've got to put a texture into a template shape first, then VO_WarpFromOneShapeToAnother
 * @return         void
*/
void VO_TextureModel::VO_PutOneTextureToTemplateShape(const VO_Texture& texture, const std::vector <VO_Triangle2DStructure>& triangles, cv::Mat& oImg)
{
    unsigned int NbOfChannels = texture.GetNbOfTextureRepresentation() >= 3 ? 3:1;
    VO_Shape shape = VO_Triangle2DStructure::Triangle2D2Shape(triangles);
    cv::Rect rect = shape.GetShapeBoundRect();
    if(NbOfChannels == 1)
        oImg = cv::Mat::zeros(cv::Size(rect.width, rect.height), CV_8UC1);
    else if(NbOfChannels == 3)
        oImg = cv::Mat::zeros(cv::Size(rect.width, rect.height), CV_8UC3);

    cv::Point2f pt;
    // Get the image m_ImageTemplateFace, for alignment!
    int PixelsInFaceTemplate = 0;
    
    if(NbOfChannels == 1)
    {
        for (unsigned int Y = 0; Y < oImg.rows; Y++)
        {
            for (unsigned int X = 0; X < oImg.cols; X++)
            {
                pt.x    = X;
                pt.y    = Y;

                int k = VO_Triangle2DStructure::IsPointInTriangles(pt, triangles);
                if(k>=0)
                {
                    oImg.at<uchar>(Y, X) = (unsigned char)texture.m_MatTexture(0, PixelsInFaceTemplate);
                    PixelsInFaceTemplate++;
                }
            }
        }
    }
    else if(NbOfChannels == 3)
    {
        for (unsigned int Y = 0; Y < oImg.rows; Y++)
        {
            for (unsigned int X = 0; X < oImg.cols; X++)
            {
                pt.x    = X;
                pt.y    = Y;

                int k = VO_Triangle2DStructure::IsPointInTriangles(pt, triangles);
                if(k>=0)
                {
                    for (unsigned int chan = 0; chan < NbOfChannels; chan++)
                    {
                        oImg.at<cv::Vec3b>(Y, X)[chan] = (unsigned char)texture.m_MatTexture(chan, PixelsInFaceTemplate);
                    }
                    PixelsInFaceTemplate++;
                }
            }
        }
    }
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Put one texture into the template shape with a corresponding warp
 * @param          iShape              Input - shape warp from
 * @param          oShape              Input - shape warp to
 * @param          triangles           Input - contains warp information
 * @param          iImg                Input - input image, extracted texture from
 * @param          oImg                Output - output image, put the texture on to this image
 * @note           All texture std::vectors are of the same size. So, you can't put it into the respective triangulation
                   for respective image. You've got to put a texture into a template shape first, then VO_WarpFromOneShapeToAnother
*/
unsigned int VO_TextureModel::VO_WarpFromOneShapeToAnother( const VO_Shape& iShape, 
                                                            const VO_Shape& oShape, 
                                                            const std::vector <VO_Triangle2DStructure>& triangles,
                                                            const cv::Mat& iImg, 
                                                            cv::Mat& oImg)
{
    unsigned int NbOfChannels     = iImg.channels();
    unsigned int NbOfPoints = iShape.GetNbOfPoints();
    unsigned int NbOfTriangles  = triangles.size();
    unsigned int NbOfPixels     = 0;
    
    cv::Point2f src[3], dst[3];
    std::vector< cv::Mat_<float> > matWarping;
    matWarping.resize(NbOfTriangles);
    std::vector<VO_Triangle2DStructure> warpedTriangles = oShape.GetTriangle2DStructure(triangles);
    cv::Rect rect_in = iShape.GetShapeBoundRect();
    cv::Rect rect_out = oShape.GetShapeBoundRect();
    oImg = cv::Mat::zeros( cv::Size(rect_out.width, rect_out.height), iImg.type() );
    unsigned int vIdx0, vIdx1, vIdx2;
    
    // calculate all the possible mapping (for speeding up) 95 mapping totally
    for (unsigned int i = 0; i < NbOfTriangles; i++ )
    {
        vIdx0 = triangles[i].m_vVertexIndexes[0];
        vIdx1 = triangles[i].m_vVertexIndexes[1];
        vIdx2 = triangles[i].m_vVertexIndexes[2];
        
        // Get the affine transformation for each triangle pair.
        src[0] = oShape.GetA2DPoint(vIdx0);
        src[1] = oShape.GetA2DPoint(vIdx1);
        src[2] = oShape.GetA2DPoint(vIdx2);

        dst[0] = iShape.GetA2DPoint(vIdx0);
        dst[1] = iShape.GetA2DPoint(vIdx1);
        dst[2] = iShape.GetA2DPoint(vIdx2);

        matWarping[i] = cv::getAffineTransform( src, dst );
    }
    
    float XX, YY;
    cv::Point2f pt;
    
    if(NbOfChannels == 1)
    {
        float gray = 0.0;

        for (unsigned int Y = 0; Y < oImg.rows; Y++)
        {
            for (unsigned int X = 0; X < oImg.cols; X++)
            {
                pt.x = X + rect_out.x;
                pt.y = Y + rect_out.y;

                int k = VO_Triangle2DStructure::IsPointInTriangles(pt, warpedTriangles);
                if(k>=0)
                {
                    const cv::Mat_<float>& sss = matWarping[k];
                    XX = sss(0,0)*pt.x + sss(0,1)*pt.y + sss(0,2);
                    YY = sss(1,0)*pt.x + sss(1,1)*pt.y + sss(1,2);
                    
                    // Since the above calculations are basically matrix calculation, 
                    // they won't be able to always ensure XX or YY are always within the image.
                    // Therefore, a constrain in the following is a must!!!
                    if (XX < 0.0f) XX = 0.0f;
                    if (YY < 0.0f) YY = 0.0f;
                    if (XX > ((float)(rect_in.width - 1) - 0.001f)) XX = (float) (rect_in.width - 1) - 0.001f;
                    if (YY > ((float)(rect_in.height - 1) - 0.001f)) YY = (float) (rect_in.height - 1) - 0.001f;

//                    // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
//                    warpsrc(0, 0) = pt.x;
//                    warpsrc(1, 0) = pt.y;
//                    warpsrc(2, 0) = 1.0;
//
//    //                cv::gemm(matWarping[k], warpsrc, 1.0, cv::Mat(), 0.0, warpeddst);
//                    warpeddst = matWarping[k] * warpsrc;

                    // extract the B,G,R on each shape/image respectively into textures
                    // warpeddst.at<float>(0, 0) is for x while
                    // warpeddst.at<float>(1, 0) is for y. But,
                    // x determines cols, while y determines rows.
//                    VO_TextureModel::VO_CalcSubPixelTexture ( warpeddst(0, 0), warpeddst(1, 0), iImg, &gray);
                    VO_TextureModel::VO_CalcSubPixelTexture ( XX, YY, iImg, &gray);
                    oImg.at<uchar>(Y, X) = (unsigned char) gray;

                    NbOfPixels ++;
                }
            }
        }
    }
    else if(NbOfChannels == 3)
    {
        float b = 0.0, g = 0.0, r = 0.0;
        
        for (unsigned int Y = 0; Y < oImg.rows; Y++)
        {
            for (unsigned int X = 0; X < oImg.cols; X++)
            {
                pt.x = X + rect_out.x;
                pt.y = Y + rect_out.y;

                int k = VO_Triangle2DStructure::IsPointInTriangles(pt, warpedTriangles);
                if(k>=0)
                {
                    const cv::Mat_<float>& sss = matWarping[k];
                    XX = sss(0,0)*pt.x + sss(0,1)*pt.y + sss(0,2);
                    YY = sss(1,0)*pt.x + sss(1,1)*pt.y + sss(1,2);
                    
                    // Since the above calculations are basically matrix calculation, 
                    // they won't be able to always ensure XX or YY are always within the image.
                    // Therefore, a constrain in the following is a must!!!
                    if (XX < 0.0f) XX = 0.0f;
                    if (YY < 0.0f) YY = 0.0f;
                    if (XX > ((float)(rect_in.width - 1) - 0.001f)) XX = (float) (rect_in.width - 1) - 0.001f;
                    if (YY > ((float)(rect_in.height - 1) - 0.001f)) YY = (float) (rect_in.height - 1) - 0.001f;
                    
//                    // warp from m_vTemplateTriangle2D[j] (template pixel in the specific triangle) to each shape/image
//                    warpsrc(0, 0) = pt.x;
//                    warpsrc(1, 0) = pt.y;
//                    warpsrc(2, 0) = 1.0;
//
//    //                cv::gemm(matWarping[k], warpsrc, 1.0, cv::Mat(), 0.0, warpeddst);
//                    warpeddst = matWarping[k] * warpsrc;

                    // extract the B,G,R on each shape/image respectively into textures
                    // warpeddst.at<float>(0, 0) is for x while
                    // warpeddst.at<float>(1, 0) is for y. But,
                    // x determines cols, while y determines rows.
//                    VO_TextureModel::VO_CalcSubPixelTexture (warpeddst(0, 0), warpeddst(1, 0), iImg, &b, &g, &r);
                    VO_TextureModel::VO_CalcSubPixelTexture (XX, YY, iImg, &b, &g, &r);
                    oImg.at<cv::Vec3b>(Y, X)[0] = (unsigned char) b;
                    oImg.at<cv::Vec3b>(Y, X)[1] = (unsigned char) g;
                    oImg.at<cv::Vec3b>(Y, X)[2] = (unsigned char) r;
                    
                    NbOfPixels ++;
                }
            }
        }
    }
    return NbOfPixels;
}


/**
 * @brief        image morphing
 * @param        iShape1            Input        the first shape
 * @param        iShape2            Input        the second shape
 * @param        oShapes            Output        intermediate shapes during the process of morphing
 * @param        triangles        Input        a list of triangles
 * @param        iImg1            Input        the first image
 * @param        iImg2            Input        the second image
 * @param        oImgs            Output        the output images
 * @param        step            Input        between 0 to 1, Normally, 0.1 or 0.2 are good selections
 * @note        Current version requires iShape1 and iShape2 have the same size
 **/
void VO_TextureModel::VO_Morphing(const VO_Shape& iShape1, const VO_Shape& iShape2, std::vector<VO_Shape>& oShapes, const std::vector<VO_Triangle2DStructure>& triangles, const cv::Mat& iImg1, const cv::Mat& iImg2, std::vector<cv::Mat>& oImgs, float step)
{
    assert (iImg1.cols == iImg2.cols && iImg1.rows == iImg2.rows);
    unsigned int NbOfFrames     = cvRound(1.0/step);
    oShapes.resize(NbOfFrames+1);
    oImgs.resize(NbOfFrames+1);

    cv::Mat morph1, morph2;

    oShapes[0]                  = iShape1;
    oShapes[NbOfFrames]         = iShape2;
    iImg1.copyTo(oImgs[0]);
    iImg2.copyTo(oImgs[NbOfFrames]);

    for(unsigned int i = 1; i < NbOfFrames; ++i)
    {
        oShapes[i] = const_cast<VO_Shape&>(iShape1)*(step*i) + const_cast<VO_Shape&>(iShape2)*(1.0-step*i);
        VO_TextureModel::VO_WarpFromOneShapeToAnother(iShape1, oShapes[i], triangles, iImg1, morph1);
        VO_TextureModel::VO_WarpFromOneShapeToAnother(iShape2, oShapes[i], triangles, iImg2, morph2);
        cv::addWeighted( morph1, step*i, morph2, 1.0-step*i, 0.0, oImgs[i] );
    }
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Put one texture into the template shape with a corresponding warp
 * @param          iShape              Input - shape warp from
 * @param          oShape              Input - shape warp to
 * @param          triangles           Input - contains warp information
 * @param          iImg                Input - input image, extracted texture from
 * @param          oImg                Output - output image, put the texture on to this image
 * @note           All texture std::vectors are of the same size. So, you can't put it into the respective triangulation
                   for respective image. You've got to put a texture into a template shape first, then VO_WarpFromOneShapeToAnother
*/
void VO_TextureModel::VO_PutOneTextureToOneShape(const VO_Texture& texture, const VO_Shape& oShape, const std::vector <VO_Triangle2DStructure>& triangles, cv::Mat& oImg)
{
    cv::Mat intermediateImg (oImg);
    VO_TextureModel::VO_PutOneTextureToTemplateShape(texture, triangles, intermediateImg);
    VO_Shape intermediateShape = VO_Triangle2DStructure::Triangle2D2Shape(triangles);
    VO_TextureModel::VO_WarpFromOneShapeToAnother(intermediateShape, oShape, triangles, intermediateImg, oImg);
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Calculate sub pixel texture of a point in a gray-level image
 * @param          gray             - output the gray level
 * @note           In the pictures, x represents cols, y represents rows!
 *                 In cv::Mat& image, x represents cols, y represents rows as well!!!
 * @return         void
*/
void VO_TextureModel::VO_CalcSubPixelTexture(float x, float y, const cv::Mat& image, float* gray)
{
    assert(image.channels() == GRAYCHANNELS);
// double sec = (double)cvGetTickCount();   // Now, pretty fast already for gray-level images

    int Y0 = (int)y;
    int X0 = (int)x;
    int Y1 = (int)(y+1);
    int X1 = (int)(x+1);

    float s=x-X0;
    float t=y-Y0;
    float t1=1.0f-t;
    float s1=1.0f-s;

    float tempA = t1 * image.at<uchar>(Y0, X0)
                  + t * image.at<uchar>(Y1, X0);
    float tempB = t1 * image.at<uchar>(Y0, X1)
                  + t * image.at<uchar>(Y1, X1);
    *gray = tempA * s1 + tempB * s;

// sec = ((double)cvGetTickCount() -  sec )/  (cvGetTickFrequency());
// cout << "Interpolation time cost: " << sec << " millisec" << endl;
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Calculate sub pixel texture of a point in a color image
 * @param          gray - output the gray level
 * @note           In the pictures, x represents cols, y represents rows!
                   In cv::Mat& image, x represents cols, y represents rows as well!!!
 * @return         void
*/
void VO_TextureModel::VO_CalcSubPixelTexture(float x, float y, const cv::Mat& image, float* b, float* g, float* r)
{
    assert(image.channels() == COLORCHANNELS);

// double sec = (double)cvGetTickCount();

    int Y0 = (int)y;
    int X0 = (int)x;
    int Y1 = (int)(y+1);
    int X1 = (int)(x+1);

    float s=x-X0;
    float t=y-Y0;
    float s1=1.0f-s;
    float t1=1.0f-t;


    float tempA_b = t1 * image.at<cv::Vec3b>(Y0, X0)[0]
                    + t * image.at<cv::Vec3b>(Y1, X0)[0];
    float tempB_b = t1 * image.at<cv::Vec3b>(Y0, X1)[0]
                    + t * image.at<cv::Vec3b>(Y1, X1)[0];
    float tempA_g = t1 * image.at<cv::Vec3b>(Y0, X0)[1]
                    + t * image.at<cv::Vec3b>(Y1, X0)[1];
    float tempB_g = t1 * image.at<cv::Vec3b>(Y0, X1)[1]
                    + t * image.at<cv::Vec3b>(Y1, X1)[1];
    float tempA_r = t1 * image.at<cv::Vec3b>(Y0, X0)[2]
                    + t * image.at<cv::Vec3b>(Y1, X0)[2];
    float tempB_r = t1 * image.at<cv::Vec3b>(Y0, X1)[2]
                    + t * image.at<cv::Vec3b>(Y1, X1)[2];
    *b = tempA_b * s1 + tempB_b * s;
    *g = tempA_g * s1 + tempB_g * s;
    *r = tempA_r * s1 + tempB_r * s;

// sec = ((double)cvGetTickCount() -  sec )/  (cvGetTickFrequency());
// cout << "Interpolation time cost: " << sec << " millisec" << endl;
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Calculate sub pixel texture of a point in image
 * @return         std::vector<float>   - a std::vector of size 1 or 3
 * @note           In the pictures, x represents cols, y represents rows!
                   In cv::Mat& image, x represents cols, y represents rows as well!!!
 * @return         void
*/
std::vector<float> VO_TextureModel::VO_CalcSubPixelTexture(float x, float y, const cv::Mat& image)
{
// double sec = (double)cvGetTickCount();

    std::vector<float> result;
    unsigned int channels = image.channels();
    if (!(channels == 1 || channels == 3))
    {
        std::cerr << "Cannot deal with images with nChannels != 1 or 3." << std::endl;
        exit(EXIT_FAILURE);
    }

    int Y0         = (int)y;
    int X0         = (int)x;
    int Y1         = (int)(y+1);
    int X1         = (int)(x+1);

    float s        = x-X0;
    float t        = y-Y0;
    float s1    = 1.0f-s;
    float t1    = 1.0f-t;

    float LeftTopB, LeftTopG, LeftTopR;
    float LeftBottomB, LeftBottomG, LeftBottomR;
    float RightTopB, RightTopG, RightTopR;
    float RightBottomB, RightBottomG, RightBottomR;

    VO_TextureModel::VO_CalcPixelRGB(X0, Y0, image, LeftTopB, LeftTopG, LeftTopR);
    VO_TextureModel::VO_CalcPixelRGB(X0, Y1, image, LeftBottomB, LeftBottomG, LeftBottomR);
    VO_TextureModel::VO_CalcPixelRGB(X1, Y0, image, RightTopB, RightTopG, RightTopR);
    VO_TextureModel::VO_CalcPixelRGB(X1, Y1, image, RightBottomB, RightBottomG, RightBottomR);

    float tempAB, tempAG, tempAR;
    float tempBB, tempBG, tempBR;

    if(channels == 1)
    {
        tempAB = t1 * LeftTopB + t * LeftBottomB;
        tempBB = t1 * RightTopB + t * RightBottomB;
        result.push_back (tempAB * s1 + tempBB * s);
    }
    else
    {
        tempAB = t1 * LeftTopB + t * LeftBottomB;
        tempBB = t1 * RightTopB + t * RightBottomB;
        result.push_back (tempAB * s1 + tempBB * s);
        tempAG = t1 * LeftTopG + t * LeftBottomG;
        tempBG = t1 * RightTopG + t * RightBottomG;
        result.push_back (tempAG * s1 + tempBG * s);
        tempAR = t1 * LeftTopR + t * LeftBottomR;
        tempBR = t1 * RightTopR + t * RightBottomR;
        result.push_back (tempAR * s1 + tempBR * s);
    }

// sec = ((double)cvGetTickCount() -  sec )/  (cvGetTickFrequency());Vec3b
// cout << "Interpolation time cost: " << sec << " millisec" << endl;

    return result;
}


/**
 * @author      JIA Pei
 * @version     2010-02-10
 * @brief       Calculate RGB value for a point in image
 * @param       image
 * @return      no return value, in order to speed up !!
*/
void VO_TextureModel::VO_CalcPixelRGB(int x, int y, const cv::Mat& image, float& B, float& G, float& R)
{
    unsigned int channels = image.channels();
    if (!(channels == 1 || channels == 3))
    {
        std::cerr << "Cannot deal with images with nChannels != 1 or 3." << std::endl;
        exit(EXIT_FAILURE);
    }

    switch(image.depth())
    {
    case IPL_DEPTH_8U:
        {
            if(channels == 1)
                B = (float)image.at<uchar>(y, x );
            else
            {
                B = (float)image.at<uchar>(y, x*3 );
                G = (float)image.at<uchar>(y, x*3+1 );
                R = (float)image.at<uchar>(y, x*3+2 );
            }
        }
        break;
    case IPL_DEPTH_8S:
        {
            if(channels == 1)
                B = (float)image.at<char>(y, x );
            else
            {
                B = (float)image.at<char>(y, x*3 );
                G = (float)image.at<char>(y, x*3+1 );
                R = (float)image.at<char>(y, x*3+2 );
            }
        }
        break;
    case IPL_DEPTH_16S:
        {
            if(channels == 1)
                B = (float)image.at<short int>(y, x );
            else
            {
                B = (float)image.at<short int>(y, x*3 );
                G = (float)image.at<short int>(y, x*3+1 );
                R = (float)image.at<short int>(y, x*3+2 );
            }
        }
        break;
     case IPL_DEPTH_16U:
        {
            if(channels == 1)
                B = (float)image.at<unsigned short int>(y, x );
            else
            {
                B = (float)image.at<unsigned short int>(y, x*3 );
                G = (float)image.at<unsigned short int>(y, x*3+1 );
                R = (float)image.at<unsigned short int>(y, x*3+2 );
            }
        }
         break;
    case IPL_DEPTH_32S:
        {
            if(channels == 1)
                B = (float)image.at<int>(y, x );
            else
            {
                B = (float)image.at<int>(y, x*3 );
                G = (float)image.at<int>(y, x*3+1 );
                R = (float)image.at<int>(y, x*3+2 );
            }
        }
        break;
    case IPL_DEPTH_32F:
        {
            if(channels == 1)
                B = image.at<float>(y, x );
            else
            {
                B = image.at<float>(y, x*3 );
                G = image.at<float>(y, x*3+1 );
                R = image.at<float>(y, x*3+2 );
            }
        }
        break;
    case IPL_DEPTH_64F:
        {
            if(channels == 1)
                B = (float)image.at<double>(y, x );
            else
            {
                B = (float)image.at<double>(y, x*3 );
                G = (float)image.at<double>(y, x*3+1 );
                R = (float)image.at<double>(y, x*3+2 );
            }
        }
        break;
    }
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Normalized texture to reference scale texture
 * @param          inTexture       Input     - input texture
 * @param          textureSD       Input     - texture standard deviation
 * @param          outTexture      Output     - output texture in reference scale
 * @return         void
*/
void VO_TextureModel::VO_NormalizedTexture2ReferenceScale(const VO_Texture& inTexture, float textureSD, VO_Texture& outTexture)
{
    outTexture = const_cast<VO_Texture&> (inTexture) * textureSD + AVERAGEFACETEXTURE;

    outTexture.Clamp(0.0, 255.0);
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Reference scale texture back to normalized one
 * @param          inTexture       Input - reference texture
 * @param          textureSD       Input - texture standard deviation
 * @param          outTexture      Output - output normalized texture 
 * @return         void
*/
void VO_TextureModel::VO_ReferenceTextureBack2Normalize(const VO_Texture& inTexture, float textureSD, VO_Texture& outTexture)
{
    outTexture = ( const_cast<VO_Texture&> (inTexture) - AVERAGEFACETEXTURE ) / textureSD;
}


/**
 * @author        JIA Pei
 * @version       2010-02-10
 * @brief         Put edges on template face
 * @param         edges               Input     - all edges information
 * @param         templateShape       Input     - template shape
 * @param         iImg                Input     - template image
 * @param         oImg                Output     - output image with edges on oImg
 * @return        void
*/
void VO_TextureModel::VO_PutEdgesOnTemplateFace(const std::vector<VO_Edge>& edges,
                                                const VO_Shape& templateShape,
                                                const cv::Mat& iImg, 
                                                cv::Mat& oImg)
{
    unsigned int NbOfEdges = edges.size();
    cv::Point2f iorg,idst;

    iImg.copyTo(oImg);

    for (unsigned int i = 0; i < NbOfEdges; i++)
    {
        iorg = templateShape.GetA2DPoint(edges[i].GetIndex1() );
        idst = templateShape.GetA2DPoint(edges[i].GetIndex2() );
        cv::line( oImg, iorg, iorg, colors[8], 2, 0, 0 );
        cv::line( oImg, iorg, idst, colors[8], 1, 0, 0 );
    }
}


///**
// * @author     JIA Pei
// * @version    2010-02-10
// * @brief      Put convex hull on template face
// * @param      ch              Input - convex hull
// * @param      iImg            Input - template image
// * @param      oImg            Output - output images with convex hull on oImg
//*/
//void VO_TextureModel::VO_PutConvexHullOnTemplateFace(const cv::Mat& iImg, cv::Mat& oImg)
//{
//    unsigned int NbOfPointsOnConvexHull = ch.cols;
//    cv::Point iorg,idst;
//
//    iImg.copyTo(oImg);
//
//    for (unsigned int i = 0; i < NbOfPointsOnConvexHull; i++)
//    {
//        if(i != NbOfPointsOnConvexHull - 1 )
//        {
//            iorg = cvcv::PointFrom32f( ch.at<cv::Point2f>(0, i ) );
//            idst = cvcv::PointFrom32f( ch.at<cv::Point2f>(0, i+1 ) );
//            cv::line( oImg, iorg, iorg, colors[8], 2, 0, 0 );     // emphasize the vertex
//            cv::line( oImg, iorg, idst, colors[8], 1, 0, 0 );
//        }
//        else
//        {
//            iorg = cvcv::PointFrom32f( ch.at<cv::Point2f>(0, i ) );
//            idst = cvcv::PointFrom32f( ch.at<cv::Point2f>(0, 0 ) );
//            cv::line( oImg, iorg, iorg, colors[8], 2, 0, 0 );     // emphasize the vertex
//            cv::line( oImg, iorg, idst, colors[8], 1, 0, 0 );
//        }
//    }
//}
//
//
///**
// * @author     JIA Pei
// * @version    2010-02-10
// * @brief      Put concave pixels on template face - inside convex hull but out of template face
// * @param      ch              Input - convex hull
// * @param      triangles       Input - all triangles information
// * @param      iImg            Input - template image
// * @param      oImg            Output - output images with concave pixels on oImg
//*/
//void VO_TextureModel::VO_PutConcavePixelsOnTemplateFace(const cv::Mat& ch, const std::vector <VO_Triangle2DStructure>& triangles,
//                                               const cv::Mat& iImg, cv::Mat& oImg)
//{
//    iImg.copyTo(oImg);
//
//    cv::Point2f pt;
//    for (unsigned int i = 0; i < iImg.rows; i++)
//    {
//        for (unsigned int j = 0; j < iImg.cols; j++)
//        {
//            pt.x = (float)j;
//            pt.y = (float)i;
//
//            if( VO_TextureModel::VO_Iscv::PointInConvexHull(pt, ch, true) && !VO_TextureModel::VO_Iscv::PointInTemplateFace(triangles, pt) )
//            {
//                cv::Point iorg = cvcv::PointFrom32f(pt);
//                cv::line( oImg, iorg, iorg, colors[8], 1, 0, 0 );   // Here, must not emphasize the points
//            }
//        }
//    }
//}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Put every single triangle onto template face
 * @param          triangles       Input - all triangles information
 * @param          iImg            Input - template image
 * @param          oImgs           Output - output images with single triangle on every single oImg
 * @return         void
*/
void VO_TextureModel::VO_PutTrianglesOnTemplateFace(const std::vector <VO_Triangle2DStructure>& triangles,
                                                    const cv::Mat& iImg, 
                                                    std::vector<cv::Mat>& oImgs)
{
    unsigned int NbOfTriangles = triangles.size();
    oImgs.resize(NbOfTriangles);

    std::vector<cv::Point2f> iorgFloat, idstFloat;
    iorgFloat.resize(3);
    idstFloat.resize(3);
        
    for(unsigned int i = 0; i < NbOfTriangles; i++)
    {
        iImg.copyTo(oImgs[i]);

        iorgFloat[0]    = triangles[i].GetA2DPoint(0);
        iorgFloat[1]    = triangles[i].GetA2DPoint(1);
        iorgFloat[2]    = triangles[i].GetA2DPoint(2);
        idstFloat[0]    = triangles[i].GetA2DPoint(1);
        idstFloat[1]    = triangles[i].GetA2DPoint(2);
        idstFloat[2]    = triangles[i].GetA2DPoint(0);

        cv::line( oImgs[i], iorgFloat[0], idstFloat[0], colors[8], 1, 0, 0 );
        cv::line( oImgs[i], iorgFloat[1], idstFloat[1], colors[8], 1, 0, 0 );
        cv::line( oImgs[i], iorgFloat[2], idstFloat[2], colors[8], 1, 0, 0 );
    }
}


/**
 * @author      JIA Pei
 * @version     2014-05-07
 * @brief       draw all PDM ellipses onto the textured template face
 * @param       iShape      Input    -    the input shape
 * @param       iImg        Input    -    the input image
 * @param       oImg        Output   -    the output image
 * @return      void
 */
void VO_TextureModel::VO_PutPDMEllipsesOnTemplateFace(const std::vector<VO_Ellipse>& ellipses, const cv::Mat& iImg, cv::Mat& oImg)
{
    unsigned int NbOfEllipses =  ellipses.size();
    iImg.copyTo(oImg);
    VO_Ellipse ellipse;
    cv::Point2f iPoint;

    for(unsigned int i = 0; i < NbOfEllipses; i++)
    {
        ellipse = ellipses.at(i);
        iPoint = ellipse.GetCOG();

        cv::ellipse(oImg,
                    cv::Point( (int)iPoint.x, (int)iPoint.y ),
                    cv::Size(ellipse.GetAxisXHalfLen(), ellipse.GetAxisYHalfLen()),
                    ellipse.GetAngle(),
                    ellipse.GetStartAngle(),
                    ellipse.GetEndAngle(),
                    colors[7],
                    1,
                    0,
                    0);
    }
}


/**
 * @author      JIA Pei
 * @version     2010-02-10
 * @brief       draw the shape's key points onto the textured template face
 * @param       iShape      Input    -    the input shape
 * @param       iImg        Input    -    the input image
 * @param       oImg        Output   -    the output image
 * @return      void
 */
void VO_TextureModel::VO_PutShapeOnTemplateFace(const VO_Shape& iShape, const cv::Mat& iImg, cv::Mat& oImg)
{
    unsigned int NbOfPoints =  iShape.GetNbOfPoints();
    iImg.copyTo(oImg);
    cv::Point2f iPoint;

    for(unsigned int i = 0; i < NbOfPoints; i++)
    {
        iPoint    = iShape.GetA2DPoint(i);

        cv::line( oImg, iPoint, iPoint, colors[7], 2, 0, 0 );
    }
}


/**
 * @author         JIA Pei
 * @version        2010-04-07
 * @brief          texture parameters constrain
 * @param          ioT          Input and Output - texture parameters
 * @param          nSigma       Input - number of sigmas
 * @return         void
*/
void VO_TextureModel::VO_TextureParameterConstraint(cv::Mat_<float>& ioT, float nSigma)
{
    for (unsigned int i = 0; i < ioT.cols; ++i)
    {
        float ct = nSigma * sqrt(this->m_PCANormalizedTexture.eigenvalues.at<float>(i,0) );
        if ( ioT(0, i) > ct )
        {
            ioT(0, i) = ct;
        }
        else if ( ioT(0, i) < -ct )
        {
            ioT(0, i) = -ct;
        }
    }
}


/**
 * @author         JIA Pei
 * @version        2010-04-10
 * @brief          texture parameters back project to normalized texture
 * @param          iTexture        Input - input normalized texture
 * @param          outT            Output - the projected texture parameters
*/
void VO_TextureModel::VO_NormalizedTextureProjectToTParam(const VO_Texture& iTexture, cv::Mat_<float>& outT) const
{
    this->m_PCANormalizedTexture.project(iTexture.GetTheTextureInARow(), outT);
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          texture parameters back project to normalized texture
 * @param          inC             Input - input texture parameters
 * @param          oTexture        Output - the back projected texture in a row
 * @param          tr              Input - Number of texture representations
*/
void VO_TextureModel::VO_TParamBackProjectToNormalizedTexture(const cv::Mat_<float>& inT, VO_Texture& oTexture, int tr) const
{
    oTexture.SetTheTexture(this->m_PCANormalizedTexture.backProject(inT), tr);
}

/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          texture parameters back project to normalized texture
 * @param          inC             Input - input texture parameters
 * @param          oTexture        Output - the back projected texture in a row
*/
void VO_TextureModel::VO_TParamBackProjectToNormalizedTexture(const cv::Mat_<float>& inT, cv::Mat_<float>& oTextureMat) const
{
    oTextureMat = this->m_PCANormalizedTexture.backProject(inT);
}

/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Calculate all parameters for an arbitrary texture
 * @param          iTexture        Input     - input texture
 * @param          oTexture        Output     - output texture
 * @param          outT            Output     - texture parameters
 * @return         void
*/
void VO_TextureModel::VO_CalcAllParams4AnyTexture(const cv::Mat_<float>& iTexture, cv::Mat_<float>& oTexture, cv::Mat_<float>& outT)
{
    // Here, for VO_Texture; there is no point to know how many texture representations for each VO_Texture
    VO_Texture oT(iTexture);
    oT.Normalize();
    oTexture = oT.GetTheTextureInARow();
    this->m_PCANormalizedTexture.project(oTexture, outT );
}


/**
 * @author         JIA Pei
 * @version        2010-02-10
 * @brief          Calculate all parameters for an arbitrary texture
 * @param          ioTexture        Input and Output     - input texture, output normalized texture
 * @param          outT            Output                - output texture model parameters
 * @return         void
*/
void VO_TextureModel::VO_CalcAllParams4AnyTexture(VO_Texture& ioTexture, cv::Mat_<float>& outT)
{
    ioTexture.Normalize();
    this->m_PCANormalizedTexture.project(ioTexture.GetTheTextureInARow(), outT );
}


/**
 * @author         JIA Pei
 * @version        2010-02-05
 * @brief          Load Training data for texture model
 * @return         void
*/
bool VO_TextureModel::VO_LoadTextureTrainingData(const std::vector<std::string>& allImgFiles4Training,
                                                unsigned int channels,
                                                int trm )
{
    this->m_vStringTrainingImageNames       = allImgFiles4Training;
    this->m_iNbOfChannels                   = channels;
    this->m_iTextureRepresentationMethod    = trm;
    
    this->m_vTextures.resize(this->m_iNbOfSamples);
    this->m_vNormalizedTextures.resize(this->m_iNbOfSamples);
    cv::Mat img;
    
    for(unsigned int i = 0; i < this->m_iNbOfSamples; ++i)
    {
        if(this->m_iNbOfChannels == 1)
            img = cv::imread ( this->m_vStringTrainingImageNames[i].c_str (), 0 );
        else if (this->m_iNbOfChannels == 3)
            img = cv::imread ( this->m_vStringTrainingImageNames[i].c_str (), 1 );
        else
            std::cerr << "We can't deal with image channels not equal to 1 or 3!" << std::endl;

        double start = (double)cvGetTickCount();
        // Explained by JIA Pei -- warping
        if ( !VO_TextureModel::VO_LoadOneTextureFromShape(  this->m_vShapes[i], 
                                                            img, 
                                                            this->m_vTemplateTriangle2D, 
                                                            this->m_vTemplatePointWarpInfo,
                                                            this->m_vTextures[i], 
                                                            this->m_iTextureRepresentationMethod) )
        {
            std::cout << "Texture Fail to Load at image " << i << std::endl;
            return false;
        }

        double end = (double)cvGetTickCount();
        double elapsed = (end - start) / (cvGetTickFrequency()*1000.0);
    }

    return true;
}


/**
 * @author      JIA Pei
 * @version     2010-02-05
 * @brief       build Texture Model
 * @param       allLandmarkFiles4Training   Input - all training landmark files
 * @param       allImgFiles4Training        Input - all training image files
 * @param       shapeinfoFileName           Input - shape info file
 * @param       database                    Input - which database is it?
 * @param       channels                    Input - How many channels are to be used?
 * @param       trm                         Input - texture representation method
 * @param       TPShape                     Input - truncated percentage for shape model
 * @param       TPTexture                   Input - truncated percentage for texture model
 * @param       useKnownTriangles           Input - use known triangle structures??
 * @note        Refer to "Statistical Models of Appearance for Computer Vision" page 31, Cootes
 * @return      void
*/
void VO_TextureModel::VO_BuildTextureModel( const std::vector<std::string>& allLandmarkFiles4Training,
                                            const std::vector<std::string>& allImgFiles4Training,
                                            const std::string& shapeinfoFileName, 
                                            unsigned int database,
                                            unsigned int channels,
                                            int trm, 
                                            float TPShape, 
                                            float TPTexture, 
                                            bool useKnownTriangles)
{
    if (allLandmarkFiles4Training.size() != allImgFiles4Training.size() )
        std::cerr << "allLandmarkFiles4Training should have the same number of allImgFiles4Training! " << std::endl;

    this->VO_BuildShapeModel(allLandmarkFiles4Training, shapeinfoFileName, database, TPShape, useKnownTriangles);
    this->m_iNbOfPixels                     = VO_TextureModel::VO_CalcPointWarpingInfo(this->m_vTemplateTriangle2D, this->m_vTemplatePointWarpInfo);
    this->VO_LoadTextureTrainingData( allImgFiles4Training, channels, trm);

    if(this->m_iNbOfSamples != this->m_vTextures.size() )
    {
        std::cout << "Number of Shape Samples is NOT EQUAL TO number of Texture Samples." << std::endl;
    }
    this->m_iNbOfTextureRepresentations     = this->m_vTextures[0].GetNbOfTextureRepresentation();
    this->m_iNbOfTextures                   = this->m_iNbOfPixels*this->m_iNbOfTextureRepresentations;
    this->m_iNbOfEigenTexturesAtMost        = MIN(this->m_iNbOfSamples, this->m_iNbOfTextures);
    this->m_fTruncatedPercent_Texture       = TPTexture;
    
    
    VO_TextureModel::VO_BuildTextureModel(  this->m_vTextures,
                                            this->m_vNormalizedTextures,
                                            this->m_VOAlignedMeanShape,
                                            this->m_VOReferenceShape, 
                                            this->m_VOPDM,
                                            this->m_VONormalizedMeanTexture,
                                            this->m_VOReferenceTexture,
                                            this->m_PCANormalizedTexture,
                                            this->m_vTemplatePointWarpInfo,
                                            this->m_vNormalizedPointWarpInfo,
                                            this->m_vTemplateTriangle2D,
                                            this->m_vNormalizedTriangle2D,
                                            this->m_vEdge,
                                            this->m_iNbOfTriangles,
                                            this->m_iNbOfPixels,
                                            this->m_fAverageShapeSize,
                                            this->m_fAverageTextureStandardDeviation,
                                            this->m_ImageTemplateFace,
                                            this->m_ImageEdges,
                                            this->m_ImageEllipses,
                                            this->m_iNbOfTextureEigens, 
                                            this->m_iNbOfSamples,
                                            this->m_iNbOfTextureRepresentations,
                                            this->m_iNbOfTextures,
                                            this->m_fTruncatedPercent_Shape);
}



/**
 * @author      JIA Pei
 * @version     2016-08-29
 * @brief       build texture model
 * @param       allTextures             Input - all original loaded textures
 * @param       allNormalizedTextures   Output - all normalized textures
 * @return      void
*/
void VO_TextureModel::VO_BuildTextureModel( const std::vector<VO_Texture>& allTextures,
                                            std::vector<VO_Texture>& allNormalizedTextures,
                                            const VO_Shape& alignedMeanShape,
                                            const VO_Shape& referenceShape, 
                                            const VO_Point2DDistributionModel& pdm,
                                            VO_Texture& normalizedMeanTexture,
                                            VO_Texture& referenceTexture,
                                            cv::PCA& pca,
                                            std::vector<VO_WarpingPoint>& templatePointWarpInfo,
                                            std::vector<VO_WarpingPoint>& normalizedPointWarpInfo,
                                            const std::vector<VO_Triangle2DStructure>& templateTriangle2D,
                                            const std::vector<VO_Triangle2DStructure>& normalizedTriangle2D,
                                            const std::vector<VO_Edge>& edges,
                                            unsigned int nbOfTrianges,
                                            unsigned int nbOfPixels,
                                            float avgShapeSize,
                                            float& avgTextureStandardDeviation,
                                            cv::Mat& imgTemplateFace,
                                            cv::Mat& imgEdges,
                                            cv::Mat& imgEllipses,
                                            unsigned int& nbOfTextureEigens,
                                            unsigned int nbOfSamples,
                                            unsigned int nbOfTextureRepresentations,
                                            unsigned int nbOfTextures,
                                            float TPTexture )
{
        
    cv::Mat_<float> matNormalizedTextures       = cv::Mat_<float>::zeros(nbOfSamples, nbOfTextures);

    // Normalize all textures
    avgTextureStandardDeviation     = VO_TextureModel::VO_NormalizeAllTextures(allTextures, allNormalizedTextures);
    VO_TextureModel::VO_CalcMeanTexture(allNormalizedTextures, normalizedMeanTexture);
    // Calculate reference texture
    VO_TextureModel::VO_NormalizedTexture2ReferenceScale(normalizedMeanTexture, avgTextureStandardDeviation, referenceTexture);
//VO_TextureModel::VO_PutOneTextureToTemplateShape(this->m_VOReferenceTexture, this->m_vTemplateTriangle2D, this->m_ImageTemplateFace);
//cv::imwrite("template.jpg",this->m_ImageTemplateFace);

    for(unsigned int i = 0; i < nbOfSamples; ++i)
    {
        cv::Mat_<float> textureInARow = allNormalizedTextures[i].GetTheTextureInARow();

        for(unsigned int j = 0; j < nbOfTextures; j++)
        {
            matNormalizedTextures.at<float>(i,j) = textureInARow.at<float>(0,j);
        }
    }

    //////////////////////////////////////////////////////////////////////////
    /// Calculate PCA ////////////////////////////////////////////////////////
    pca = cv::PCA(matNormalizedTextures, cv::Mat(), CV_PCA_DATA_AS_ROW, (double)TPTexture );
    nbOfTextureEigens = pca.eigenvalues.rows;
    pca.mean = normalizedMeanTexture.GetTheTextureInARow();
//    for(int i = 0; i < this->m_PCANormalizedTexture.mean.rows; i++)
//    {
//        for(int j = 0; j < this->m_PCANormalizedTexture.mean.cols; j++)
//            std::cout << this->m_PCANormalizedTexture.mean.at<float>(i, j) << std::endl;
//    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Calculate m_vNormalizedPointWarpInfo
    //////////////////////////////////////////////////////////////////////////
    cv::Point2f src[3];
    cv::Point2f dst[3];

    // warp from reference triangles to normalized triangles, it's basically just a translation and scaling
    std::vector< cv::Mat_<float> > matWarping;
    matWarping.resize(nbOfTrianges);

    // calculate all the possible mapping (for speeding up) 95 mapping totally
    // Here, actually, a translation and a scaling can do this as well!
    for (unsigned int k = 0; k < nbOfTrianges; k++ )
    {
        // Get the affine transformation for each triangle pair.
        src[0] = templateTriangle2D[k].GetA2DPoint(0);
        src[1] = templateTriangle2D[k].GetA2DPoint(1);
        src[2] = templateTriangle2D[k].GetA2DPoint(2);

        dst[0] = alignedMeanShape.GetA2DPoint( templateTriangle2D[k].GetVertexIndex(0) );
        dst[1] = alignedMeanShape.GetA2DPoint( templateTriangle2D[k].GetVertexIndex(1) );
        dst[2] = alignedMeanShape.GetA2DPoint( templateTriangle2D[k].GetVertexIndex(2) );

        matWarping[k] = cv::getAffineTransform( src, dst );
    }

    unsigned int triangleIndex;
    cv::Point2f pt, pt0;
    cv::Mat_<float> warpsrc     = cv::Mat_<float>::ones(3, 1);
    cv::Mat_<float> warpeddst     = cv::Mat_<float>::zeros(2, 1);
    for (unsigned int i = 0; i < nbOfPixels; i++)
    {
        // JIA Pei. 2006-11-25. You will see the following (int) is very important
        // without (int), the result here is not correct at all!!
        pt = templatePointWarpInfo[i].GetPosition();
        triangleIndex = templatePointWarpInfo[i].GetTriangleIndex();

        warpsrc(0, 0) = pt.x;
        warpsrc(1, 0) = pt.y;
        warpsrc(2, 0) = 1.0;

        warpeddst = matWarping[triangleIndex] * warpsrc;
        pt0.x = warpeddst.at<float>(0, 0);
        pt0.y = warpeddst.at<float>(1, 0);

        VO_WarpingPoint tempNormalizedPixelTriangle;

        tempNormalizedPixelTriangle.SetPosition(pt0);
        tempNormalizedPixelTriangle.SetTriangleIndex(triangleIndex);
        tempNormalizedPixelTriangle.SetPointIndex(i);
        tempNormalizedPixelTriangle.SetTriangle2DStructure(normalizedTriangle2D[triangleIndex] );

        // Very important!! Note by JIA Pei, push_back cannot perform on std::vector< std::vector < > >
        normalizedPointWarpInfo.push_back (tempNormalizedPixelTriangle);
    }
    //////////////////////////////////////////////////////////////////////////

    // Calculate template images
    VO_TextureModel::VO_PutOneTextureToTemplateShape(referenceTexture, templateTriangle2D, imgTemplateFace);
    VO_TextureModel::VO_PutEdgesOnTemplateFace(edges, referenceShape, imgTemplateFace, imgEdges);

    //////////////////////////////////////////////////////////////////////////
    VO_Shape tmpRefShape = const_cast<VO_Shape&>(alignedMeanShape)*avgShapeSize;
    std::vector<VO_Ellipse> refEllipses = pdm.GetPDMEllipses();
    VO_Point2DDistributionModel::VO_ScalePDMEllipses(refEllipses, avgShapeSize, refEllipses);
    cv::Mat_<float> translatePt = cv::Mat_<float>::zeros(2, 1);
    for(int i = 0; i < refEllipses.size(); i++)
    {
        translatePt(0,0) = tmpRefShape.GetA2DPoint(i).x;
        translatePt(1,0) = tmpRefShape.GetA2DPoint(i).y;
        refEllipses[i].Translate( translatePt );
    }
    cv::Rect brect = VO_Ellipse::VO_CalcBoundingRect4MultipleEllipses (refEllipses);
    cv::Mat_<float> ellipseMin = cv::Mat_<float>::zeros(2, 1);
    ellipseMin(0,0) = -brect.x;
    ellipseMin(1,0) = -brect.y;
    tmpRefShape.Translate( ellipseMin );
    for(unsigned int i = 0; i < refEllipses.size(); i++)
        refEllipses[i].Translate(ellipseMin);

    imgEllipses = cv::Mat::zeros(brect.height, brect.width, imgTemplateFace.type());
    VO_TextureModel::VO_PutShapeOnTemplateFace(tmpRefShape, imgEllipses, imgEllipses);
    VO_TextureModel::VO_PutPDMEllipsesOnTemplateFace(refEllipses, imgEllipses, imgEllipses);
    //////////////////////////////////////////////////////////////////////////
}


/**
 * @author         JIA Pei
 * @version        2010-02-13
 * @brief          Save AAM to a specified folder
 * @param          fd             Input - the folder that AAM to be saved to
 * @return         void
*/
void VO_TextureModel ::VO_Save(const std::string& fd)
{
    VO_ShapeModel::VO_Save(fd);

    std::string fn = fd+"/TextureModel";
    if (!boost::filesystem::is_directory(fn) )
        boost::filesystem::create_directory( fn );

    std::fstream fp;
    std::string tempfn;

    // TextureModel
    tempfn = fn + "/TextureModel" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);

    fp << "m_iTextureRepresentationMethod" << std::endl << this->m_iTextureRepresentationMethod << std::endl;           // m_iTextureRepresentationMethod
    fp << "m_iNbOfTextureRepresentations" << std::endl << this->m_iNbOfTextureRepresentations << std::endl;             // m_iNbOfTextureRepresentations
    fp << "m_iNbOfChannels" << std::endl << this->m_iNbOfChannels << std::endl;                                         // m_iNbOfChannels
    fp << "m_iNbOfPixels" << std::endl << this->m_iNbOfPixels << std::endl;                                             // m_iNbOfPixels
    fp << "m_iNbOfTextures" << std::endl << this->m_iNbOfTextures << std::endl;                                         // m_iNbOfTextures
    fp << "m_iNbOfEigenTexturesAtMost" << std::endl << this->m_iNbOfEigenTexturesAtMost << std::endl;                   // m_iNbOfEigenTexturesAtMost
    fp << "m_iNbOfTextureEigens" << std::endl << this->m_iNbOfTextureEigens << std::endl;                               // m_iNbOfTextureEigens
    fp << "m_fAverageTextureStandardDeviation" << std::endl << this->m_fAverageTextureStandardDeviation << std::endl;   // m_fAverageTextureStandardDeviation
    fp << "m_fTruncatedPercent_Texture" << std::endl << this->m_fTruncatedPercent_Texture << std::endl;                 // m_fTruncatedPercent_Texture
    fp.close();fp.clear();

    // m_PCANormalizedTextureMean
    tempfn = fn + "/m_PCANormalizedTextureMean" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_PCANormalizedTextureMean" << std::endl;
    fp << cv::Mat_<float>(this->m_PCANormalizedTexture.mean);
    fp.close();fp.clear();

    // m_PCANormalizedTextureEigenValues
    tempfn = fn + "/m_PCANormalizedTextureEigenValues" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_PCANormalizedTextureEigenValues" << std::endl;
    fp << cv::Mat_<float>(this->m_PCANormalizedTexture.eigenvalues);
    fp.close();fp.clear();
    
    // m_PCANormalizedTextureEigenVectors
    tempfn = fn + "/m_PCANormalizedTextureEigenVectors" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_PCANormalizedTextureEigenVectors" << std::endl;
    fp << cv::Mat_<float>(this->m_PCANormalizedTexture.eigenvectors);
    fp.close();fp.clear();

    // m_VONormalizedMeanTexture
    tempfn = fn + "/m_VONormalizedMeanTexture" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_VONormalizedMeanTexture" << std::endl;
    fp << this->m_VONormalizedMeanTexture;
    fp.close();fp.clear();
    
    // m_VOReferenceTexture
    tempfn = fn + "/m_VOReferenceTexture" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_VOReferenceTexture" << std::endl;
    fp << this->m_VOReferenceTexture;
    fp.close();fp.clear();

    // m_vTextures
    tempfn = fn + "/m_vTextures" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vTextures" << std::endl;
    fp << this->m_vTextures;
    fp.close();fp.clear();

    // m_vNormalizedTextures
    tempfn = fn + "/m_vNormalizedTextures" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vNormalizedTextures" << std::endl;
    fp << this->m_vNormalizedTextures;
    fp.close();fp.clear();
    
    // m_vTemplatePointWarpInfo
    tempfn = fn + "/m_vTemplatePointWarpInfo" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vTemplatePointWarpInfo" << std::endl;
    fp << this->m_vTemplatePointWarpInfo;
    fp.close();fp.clear();

    // m_vNormalizedPointWarpInfo
    tempfn = fn + "/m_vNormalizedPointWarpInfo" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vNormalizedPointWarpInfo" << std::endl;
    fp << this->m_vNormalizedPointWarpInfo;
    fp.close();fp.clear();

    /** Template face image */
    tempfn = fn + "/Reference.jpg";
    cv::imwrite(tempfn.c_str(), this->m_ImageTemplateFace);

    /** Image of edges */
    tempfn = fn + "/edges.jpg";
    cv::imwrite(tempfn.c_str(), this->m_ImageEdges);

    /** Image of ellipse */
    tempfn = fn + "/ellipses.jpg";
    cv::imwrite(tempfn.c_str(), this->m_ImageEllipses);

    /** How many triangles totally */
    std::vector<cv::Mat> imageTriangles;
    VO_TextureModel::VO_PutTrianglesOnTemplateFace(this->m_vTemplateTriangle2D, this->m_ImageTemplateFace, imageTriangles);
    std::string trianglestr;
    std::stringstream ssi;
    std::string stri;
    for (unsigned int i = 0; i < imageTriangles.size(); i++)
    {
        ssi << i;
        ssi >> stri;
        if(stri.length() == 2)
            trianglestr = fn + "/triangle0" + stri + ".jpg";
        else if(stri.length() == 1)
            trianglestr = fn + "/triangle00" + stri + ".jpg";
        else
            trianglestr = fn + "/triangle" + stri + ".jpg";

        cv::imwrite(trianglestr.c_str(), imageTriangles[i] );

        ssi.clear();
    }
}


/**
 * @author         JIA Pei
 * @version        2010-02-13
 * @brief          Load all Texture Modeldata from a specified folder
 * @param          fd             Input - the folder that Texture Model to be loaded from
 * @return         void
*/
void VO_TextureModel ::VO_Load(const std::string& fd)
{
    VO_ShapeModel::VO_Load(fd);
    
    this->VO_LoadParameters4Fitting(fd);
    
    std::string fn = fd+"/TextureModel";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "TextureModel subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;
    
    // m_vTextures
    tempfn = fn + "/m_vTextures" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    this->m_vTextures.resize(this->m_iNbOfSamples);
    fp >> this->m_vTextures;
    fp.close();fp.clear();

    // m_vNormalizedTextures
    tempfn = fn + "/m_vNormalizedTextures" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    this->m_vNormalizedTextures.resize(this->m_iNbOfSamples);
    fp >> this->m_vNormalizedTextures;
    fp.close();fp.clear();
    
    /** Image of edges */
    tempfn = fn + "/edges.jpg";
    this->m_ImageEdges = cv::imread(tempfn.c_str(), CV_LOAD_IMAGE_ANYCOLOR );

}


/**
 * @author         JIA Pei
 * @version        2010-02-13
 * @brief          Load all AAM data from a specified folder for later fitting
 * @param          fd       Input - the folder that AAM to be loaded from
 * @return         void
*/
void VO_TextureModel::VO_LoadParameters4Fitting(const std::string& fd)
{
    VO_ShapeModel::VO_LoadParameters4Fitting(fd);

    std::string fn = fd+"/TextureModel";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "TextureModel subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;

    // TextureModel
    tempfn = fn + "/TextureModel" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp >> this->m_iTextureRepresentationMethod;
    fp >> temp >> this->m_iNbOfTextureRepresentations;
    fp >> temp >> this->m_iNbOfChannels;
    fp >> temp >> this->m_iNbOfPixels;
    fp >> temp >> this->m_iNbOfTextures;
    fp >> temp >> this->m_iNbOfEigenTexturesAtMost;
    fp >> temp >> this->m_iNbOfTextureEigens;
    fp >> temp >> this->m_fAverageTextureStandardDeviation;
    fp >> temp >> this->m_fTruncatedPercent_Texture;
    fp.close();fp.clear();
    
    this->m_PCANormalizedTexture = cv::PCA();

    // m_PCANormalizedTextureMean
    this->m_PCANormalizedTexture.mean = cv::Mat_<float>::zeros(1, this->m_iNbOfTextures);
    tempfn = fn + "/m_PCANormalizedTextureMean" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_PCANormalizedTexture.mean;
    fp.close();fp.clear();
    
    // m_PCANormalizedTextureEigenValues
    this->m_PCANormalizedTexture.eigenvalues = cv::Mat_<float>::zeros(this->m_iNbOfTextureEigens, 1);
    tempfn = fn + "/m_PCANormalizedTextureEigenValues" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_PCANormalizedTexture.eigenvalues;
    fp.close();fp.clear();
    
    // m_PCANormalizedTextureEigenVectors
    this->m_PCANormalizedTexture.eigenvectors = cv::Mat_<float>::zeros(this->m_iNbOfTextureEigens, this->m_iNbOfTextures);
    tempfn = fn + "/m_PCANormalizedTextureEigenVectors" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_PCANormalizedTexture.eigenvectors;
    fp.close();fp.clear();

    // m_VONormalizedMeanTexture
    this->m_VONormalizedMeanTexture.m_MatTexture = cv::Mat_<float>::zeros(this->m_iNbOfTextureRepresentations, this->m_iNbOfPixels);
    tempfn = fn + "/m_VONormalizedMeanTexture" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_VONormalizedMeanTexture;
    fp.close();fp.clear();

    // m_VOReferenceTexture
    this->m_VOReferenceTexture.m_MatTexture = cv::Mat_<float>::zeros(this->m_iNbOfTextureRepresentations, this->m_iNbOfPixels);
    tempfn = fn + "/m_VOReferenceTexture" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_VOReferenceTexture;
    fp.close();fp.clear();

    // m_vTemplatePointWarpInfo
    tempfn = fn + "/m_vTemplatePointWarpInfo" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    this->m_vTemplatePointWarpInfo.resize(this->m_iNbOfPixels);
    fp >> this->m_vTemplatePointWarpInfo;
    fp.close();fp.clear();
    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)
    {
        this->m_vTemplatePointWarpInfo[i].SetTriangle2DStructure( this->m_vTemplateTriangle2D[this->m_vTemplatePointWarpInfo[i].GetTriangleIndex ()] );
    }

    // m_vNormalizedPointWarpInfo
    tempfn = fn + "/m_vNormalizedPointWarpInfo" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    this->m_vNormalizedPointWarpInfo.resize(this->m_iNbOfPixels);
    fp >> this->m_vNormalizedPointWarpInfo;
    fp.close();fp.clear();
    for (unsigned int i = 0; i < this->m_iNbOfPixels; i++)
    {
        this->m_vNormalizedPointWarpInfo[i].SetTriangle2DStructure( this->m_vNormalizedTriangle2D[this->m_vNormalizedPointWarpInfo[i].GetTriangleIndex ()] );
    }

    /** Template face image */
    tempfn = fn + "/Reference.jpg";
    this->m_ImageTemplateFace = cv::imread(tempfn.c_str(), CV_LOAD_IMAGE_ANYCOLOR );
}

