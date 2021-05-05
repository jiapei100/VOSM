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

#include <fstream>
#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include "VO_ASMLTCs.h"
#include "VO_CVCommon.h"

#include "VO_DirectFeatures.h"
#include "VO_LBPFeatures.h"
#include "VO_HaarFeatures.h"
#include "VO_GaborFeatures.h"
#include "VO_DaubechiesFeatures.h"


/** Initialization */
void VO_ASMLTCs::init()
{
    this->m_iMethod                 = VO_AXM::ASM_LTC;
    this->m_iLTCMethod              = VO_Features::DIRECT;
    this->m_iNbOfLTC4PerPoint       = 0;
    this->m_pVOfeatures             = NULL;
}


/** Default constructor */
VO_ASMLTCs::VO_ASMLTCs()
{
    this->init();
}


/** Destructor */
VO_ASMLTCs::~VO_ASMLTCs()
{
    
}


/**
 * @author      JIA Pei
 * @version     2010-02-22
 * @brief       Build Local Texture Constraint ASM
 * @param       allLandmarkFiles4Training   Input - all training landmark files
 * @param       allImgFiles4Training        Input - all training image files
 * @param       shapeinfoFileName           Input - shape info file
 * @param       database                    Input - which database is it?
 * @param       channels                    Input - How many channels are to be used?
 * @param       levels                      Input - multiscale levels
 * @param       trm                         Input - texture representation method
 * @param       TPShape                     Input - truncated percentage for shape model
 * @param       useKnownTriangles           Input - use known triangle structures??
 * @param       ltcMtd                      Input - local texture constrain methods
 * @return      void
 * @note        Using "float* oProf" is much much faster than using "VO_Profile& oProf" or "std::vector<float>"
 */
void VO_ASMLTCs::VO_BuildASMLTCs (  const std::vector<std::string>& allLandmarkFiles4Training,
                                    const std::vector<std::string>& allImgFiles4Training,
                                    const std::string& shapeinfoFileName,
                                    unsigned int database,
                                    unsigned int channels,
                                    unsigned int levels,
                                    int trm,
                                    float TPShape,
                                    bool useKnownTriangles,
                                    unsigned int ltcMtd,
                                    cv::Size imgSize)
{
    if (allLandmarkFiles4Training.size() != allImgFiles4Training.size() )
        std::cerr << "allLandmarkFiles4Training should have the same number of allImgFiles4Training! " << std::endl;

    this->VO_BuildShapeModel(allLandmarkFiles4Training, shapeinfoFileName, database, TPShape, useKnownTriangles);
    this->m_iNbOfPyramidLevels                  = levels;
    this->m_iNbOfChannels                       = channels;
    this->m_iTextureRepresentationMethod        = trm;
    this->m_iLTCMethod                          = ltcMtd;
    this->m_localImageSize                      = imgSize;
    this->m_vStringTrainingImageNames           = allImgFiles4Training;

    // Initialize all member variables
    switch(this->m_iLTCMethod)
    {
        case VO_Features::LBP:
            this->m_pVOfeatures = new VO_LBPFeatures();
        break;
        case VO_Features::HAAR:
            this->m_pVOfeatures = new VO_HaarFeatures();
        break;
        case VO_Features::GABOR:
            this->m_pVOfeatures = new VO_GaborFeatures();
        break;
        case VO_Features::DAUBECHIES:
            this->m_pVOfeatures = new VO_DaubechiesFeatures();
        break;
        case VO_Features::DIRECT:
        default:
            this->m_pVOfeatures = new VO_DirectFeatures();
        break;
    }
    this->m_pVOfeatures->VO_GenerateAllFeatureInfo(this->m_localImageSize, 2);
    this->m_iNbOfLTC4PerPoint = this->m_pVOfeatures->GetNbOfFeatures();
    
    this->m_vvCVMInverseOfLTCCov.resize(this->m_iNbOfPyramidLevels);
    this->m_vvLTCMeans.resize(this->m_iNbOfPyramidLevels);
    for(unsigned int i = 0; i < this->m_iNbOfPyramidLevels; i++)
    {
        this->m_vvCVMInverseOfLTCCov[i].resize(this->m_iNbOfPoints);
        this->m_vvLTCMeans[i].resize(this->m_iNbOfPoints);
    }

    this->m_vvLTCs.resize(this->m_iNbOfSamples);
    this->m_vvNormalizedLTCs.resize(this->m_iNbOfSamples);
    for(unsigned int i = 0; i < this->m_iNbOfSamples; ++i)
    {
        this->m_vvLTCs[i].resize(this->m_iNbOfPyramidLevels);
        this->m_vvNormalizedLTCs[i].resize(this->m_iNbOfPyramidLevels);
        for(unsigned int j = 0; j < this->m_iNbOfPyramidLevels; ++j)
        {
            this->m_vvLTCs[i][j] = cv::Mat_<float>::zeros(this->m_iNbOfPoints, this->m_iNbOfLTC4PerPoint );
            this->m_vvNormalizedLTCs[i][j] = cv::Mat_<float>::zeros(this->m_iNbOfPoints, this->m_iNbOfLTC4PerPoint );
        }
    }


    this->VO_LoadLTCTrainingData();
    this->VO_CalcStatistics4AllLTCs();
}


/**
 * @author      JIA Pei
 * @version     2010-02-22
 * @brief       Calculate Image Patch cv::Rectangle
 * @param       iImg        Input    -- the concerned image
 * @param       pt          Input    -- the point in the center of the image patch
 * @param       imgSize     Input    -- image patch size
 * @return      cv::Rect    of size imgSize*imgSize
 */
cv::Rect VO_ASMLTCs::VO_CalcImagePatchRect(const cv::Mat& iImg, const cv::Point2f& pt, cv::Size imgSize)
{
    // ensure the small image patch is within the image
    cv::Rect rect;
    if(pt.x - imgSize.width/2 >= 0)
    {
        if(pt.x + imgSize.width/2 < iImg.cols)
            rect.x = cvRound( pt.x - imgSize.width/2);
        else
            rect.x = cvFloor(iImg.cols - imgSize.width);
    }
    else rect.x = 0;

    if(pt.y - imgSize.height/2 >= 0)
    {
        if(pt.y + imgSize.height/2 < iImg.rows)
            rect.y = cvRound(pt.y - imgSize.height/2);
        else
            rect.y = cvFloor(iImg.rows - imgSize.height);
    }
    else rect.y = 0;

    rect.width = imgSize.width;
    rect.height = imgSize.height;

    return rect;
}


/**
 * @author      JIA Pei
 * @version     2010-02-05
 * @brief       Load Training data for texture model
 * @param       mtd     Input    -- ltc method
 * @return      void
*/
void VO_ASMLTCs::VO_LoadLTCTrainingData()
{
    cv::Mat img, resizedImg;
    VO_Shape resizedShape;
    float PyrScale, scale, sampleScale;
    float refScale = this->m_VOReferenceShape.GetCentralizedShapeSize();
    
    for(unsigned int i = 0; i < this->m_iNbOfSamples; ++i)
    {
        img = cv::imread ( this->m_vStringTrainingImageNames[i].c_str (), 0 );

        sampleScale = this->m_vShapes[i].GetCentralizedShapeSize();

        for( unsigned int j = 0; j < this->m_iNbOfPyramidLevels; ++j)
        {
            PyrScale = pow(2.0f, (float)j);
            scale = refScale/sampleScale/PyrScale;

            resizedShape = this->m_vShapes[i]*scale;
            cv::resize(img, resizedImg, cv::Size( (int)(img.cols*scale), (int)(img.rows*scale) ) );

// static std::stringstream ss;
// static std::string ssi;
// ss << i;
// ss >> ssi;
// static std::string fn = ssi+".jpg";
// cv::imwrite(fn.c_str(), resizedImg);

        // Explained by JIA Pei -- wavelet feature extraction
        for( unsigned int k = 0; k < this->m_iNbOfPoints; ++k )
        {
            VO_ASMLTCs::VO_LoadLTC4OneAnnotatedPoint(    resizedImg,
                                                        resizedShape,
                                                        k,
                                                        this->m_localImageSize,
                                                        this->m_pVOfeatures);
            cv::Mat_<float> oneLTC = this->m_pVOfeatures->m_MatFeatures;
            cv::Mat_<float> tmpRow = this->m_vvLTCs[i][j].row(k);
            oneLTC.copyTo( tmpRow );
            cv::normalize(oneLTC, oneLTC);
            cv::Mat_<float> tmpRow1 = this->m_vvNormalizedLTCs[i][j].row(k);
            oneLTC.copyTo(tmpRow1);
        }
    }
    }
}


/**
 * @author      JIA Pei
 * @version     2010-02-22
 * @brief       Build wavelet for key points
 * @param       iImg            Input    -- the concerned image
 * @param       theShape        Input    -- the concerned shape
 * @param       ptIdx           Input    -- which point?
 * @param       imgSize         Input    -- the image size
 * @param       mtd             Input    -- LTC method
 * @param       shiftX          Input    -- shift in X direction
 * @param       shiftY          Input    -- shift in Y direction
 * @return      cv::Mat_<float> Output   -- the extracted LTC
 */
void VO_ASMLTCs::VO_LoadLTC4OneAnnotatedPoint(  const cv::Mat& iImg,
                                                const VO_Shape& theShape,
                                                unsigned int ptIdx,
                                                cv::Size imgSize,
                                                VO_Features* vofeatures,
                                                int shiftX,
                                                int shiftY)
{
    cv::Point2f pt                 = theShape.GetA2DPoint(ptIdx);
    pt.x                        += shiftX;
    pt.y                        += shiftY;
    cv::Rect rect                 = VO_ASMLTCs::VO_CalcImagePatchRect(iImg, pt, imgSize);
    cv::Mat imgPatch             = iImg(rect);
    vofeatures->VO_GenerateAllFeatures(imgPatch);
}


void VO_ASMLTCs::VO_CalcStatistics4AllLTCs()
{
    cv::Mat_<float> normalizedLTCs4SinglePoint = cv::Mat_<float>::zeros(this->m_iNbOfSamples, this->m_iNbOfLTC4PerPoint);
    cv::Mat_<float> Covar = cv::Mat_<float>::zeros(this->m_iNbOfLTC4PerPoint, this->m_iNbOfLTC4PerPoint );

    for(unsigned int i = 0; i < this->m_iNbOfPyramidLevels; i++)
    {
        for(unsigned int j = 0; j < this->m_iNbOfPoints; j++)
        {
            for(unsigned int k = 0; k < this->m_iNbOfSamples; k++)
            {
                cv::Mat_<float> tmpRow = normalizedLTCs4SinglePoint.row(k);
                this->m_vvNormalizedLTCs[k][i].row(j).copyTo(tmpRow);
            }
            // OK! Now We Calculate the Covariance cv::Matrix of prof for Landmark icv::Point
            cv::calcCovarMatrix(normalizedLTCs4SinglePoint,
                                Covar,
                                this->m_vvLTCMeans[i][j],
                                cv::COVAR_NORMAL+cv::COVAR_ROWS+cv::COVAR_SCALE,
                                CV_32F);
            this->m_vvCVMInverseOfLTCCov[i][j] = Covar.inv(cv::DECOMP_SVD);
        }
    }
}


/**
 * @author      JIA Pei
 * @version     2010-02-22
 * @brief       Save wavelet image , 1 single channel
 * @param       fn              Input    -- file name
 * @param       imgSize         Input    -- the transformed image
 * @param       displayMtd      Input    -- two choices, 1) show directly with clamp 2) normalize to 0-255 without clamp
 * @return      void
 */
void VO_ASMLTCs::VO_HardSaveWaveletSingleChannelImage(const std::string& fn, 
                                                        cv::Size imgSize,
                                                        unsigned int displayMtd)
{
    cv::Mat img = cv::Mat::ones(imgSize, CV_8UC1);(imgSize, CV_8UC1);
    float onePixel = 0.0;
    
    double minPixel;
    double maxPixel;
    double pixelStretch = maxPixel - minPixel;
    if(fabs(pixelStretch) < FLT_EPSILON)
    {
        img = img*(unsigned char) pixelStretch;
    }
    else
    {
        switch(displayMtd)
        {
            case CLAMP:
            {
                for(unsigned int i = 0; i < imgSize.height; i++)
                {
                    for(unsigned int j = 0; j < imgSize.width; j++)
                    {
                        if(onePixel <= 0.0)            img.at<uchar>(i, j) = 0;
                        else if(onePixel >= 255.0)    img.at<uchar>(i, j) = 255;
                        else                        img.at<uchar>(i, j) = (unsigned char) onePixel;
                    }
                }
            }
            break;
            case STRETCH:
            {
                for(unsigned int i = 0; i < imgSize.height; i++)
                {
                    for(unsigned int j = 0; j < imgSize.width; j++)
                    {
//                        onePixel = ( gsl_matrix_get (waveParams, i, j) - minPixel) / (maxPixel - minPixel) * 255.0;
                        img.at<uchar>(i, j) = (unsigned char) onePixel;
                    }
                }
            }
            break;
        }
    }
    cv::imwrite(fn, img);
}


/**
 * @author      JIA Pei
 * @version     2010-06-06
 * @brief       Save ASMLTC to a specified folder
 * @param       fd      Input - the folder that ASM to be saved to
*/
void VO_ASMLTCs::VO_Save ( const std::string& fd )
{
    VO_AXM::VO_Save(fd);

    // create ASMLTCs subfolder for justASMLTCs model data
    std::string fn = fd+"/ASMLTCs";
    if (!boost::filesystem::is_directory(fn) )
        boost::filesystem::create_directory( fn );

    std::ofstream fp;
    std::string tempfn;

    // ASMLTCs
    tempfn = fn + "/ASMLTCs" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);

    fp << "m_iLTCMethod" << std::endl << this->m_iLTCMethod << std::endl;
    fp << "m_iNbOfLTC4PerPoint" << std::endl << this->m_iNbOfLTC4PerPoint << std::endl;
    fp << "m_localImageSize" << std::endl << this->m_localImageSize.height << " " << this->m_localImageSize.width << std::endl;
    fp.close();fp.clear();

    // m_vvLTCMeans
    tempfn = fn + "/m_vvLTCMeans" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vvLTCMeans" << std::endl;
    for (unsigned int i = 0; i < this->m_iNbOfPyramidLevels; i++)
    {
        for (unsigned int j = 0; j < this->m_iNbOfPoints; j++)
        {
            fp << "level " << i << " node " << j << std::endl;
            fp << this->m_vvLTCMeans[i][j] << std::endl;
        }
    }
    fp.close();fp.clear();

    // m_vvCVMInverseOfLTCCov
    tempfn = fn + "/m_vvCVMInverseOfLTCCov" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vvCVMInverseOfLTCCov" << std::endl;
    for (unsigned int i = 0; i < this->m_iNbOfPyramidLevels; i++)
    {
        for (unsigned int j = 0; j < this->m_iNbOfPoints; j++)
        {
            fp << "level " << i << " node " << j << std::endl;
            fp << this->m_vvCVMInverseOfLTCCov[i][j] << std::endl;
        }
    }
    fp << this->m_vvCVMInverseOfLTCCov << std::endl;
    fp.close();fp.clear();
}


/**
 * @author      JIA Pei
 * @version     2010-06-06
 * @brief       Load all ASMLTC data from a specified folder
 * @param       fd      Input - the folder that ASMLTC to be loaded from
*/
void VO_ASMLTCs::VO_Load ( const std::string& fd )
{
    VO_AXM::VO_Load(fd);
}


/**
 * @author      JIA Pei
 * @version     2010-06-06
 * @brief       Load all ASMLTC data from a specified folder for later fitting
 * @param       fd      Input - the folder that ASMLTC to be loaded from
*/
void VO_ASMLTCs::VO_LoadParameters4Fitting ( const std::string& fd )
{
    VO_AXM::VO_LoadParameters4Fitting(fd);     // Note, for ASMProfile fitting, no problem
    
    std::string fn = fd+"/ASMLTCs";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "VO_ASMLTCs subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;

    // ASMLTCs
    tempfn = fn + "/ASMLTCs" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp >> this->m_iLTCMethod;
    fp >> temp >> this->m_iNbOfLTC4PerPoint;
    fp >> temp >> this->m_localImageSize.height >> this->m_localImageSize.width;
    fp.close();fp.clear();
    // Initialize all member variables
    switch(this->m_iLTCMethod)
    {
    case VO_Features::LBP:
        this->m_pVOfeatures = new VO_LBPFeatures();
        break;
    case VO_Features::HAAR:
        this->m_pVOfeatures = new VO_HaarFeatures();
        break;
    case VO_Features::GABOR:
        this->m_pVOfeatures = new VO_GaborFeatures();
        break;
    case VO_Features::DAUBECHIES:
        this->m_pVOfeatures = new VO_DaubechiesFeatures();
        break;
    case VO_Features::DIRECT:
    default:
        this->m_pVOfeatures = new VO_DirectFeatures();
        break;
    }
    this->m_pVOfeatures->VO_GenerateAllFeatureInfo(this->m_localImageSize, 2);

    // m_vvLTCMeans
    tempfn = fn + "/m_vvLTCMeans" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    getline(fp, temp);
    this->m_vvLTCMeans.resize(this->m_iNbOfPyramidLevels);
    for (unsigned int i = 0; i < this->m_iNbOfPyramidLevels; i++)
    {
        this->m_vvLTCMeans[i].resize(this->m_iNbOfPoints);
        for (unsigned int j = 0; j < this->m_iNbOfPoints; j++)
        {
            fp >> temp;
            while ( !fp.eof() && temp!="level")
            {
                fp >> temp;
            }
            getline(fp, temp);
            this->m_vvLTCMeans[i][j] = cv::Mat_<float>::zeros(1, this->m_iNbOfLTC4PerPoint );
            fp >> this->m_vvLTCMeans[i][j];
        }
    }
    fp.close();fp.clear();
    
    // m_vvCVMInverseOfLTCCov
    tempfn = fn + "/m_vvCVMInverseOfLTCCov" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    this->m_vvCVMInverseOfLTCCov.resize(this->m_iNbOfPyramidLevels);
    for (unsigned int i = 0; i < this->m_iNbOfPyramidLevels; i++)
    {
        this->m_vvCVMInverseOfLTCCov[i].resize(this->m_iNbOfPoints);
        for (unsigned int j = 0; j < this->m_iNbOfPoints; j++)
        {
            fp >> temp;
            while ( !fp.eof() && temp!= "level")
            {
                fp >> temp;
            }
            getline(fp, temp);
            this->m_vvCVMInverseOfLTCCov[i][j] = cv::Mat_<float>::zeros( this->m_iNbOfLTC4PerPoint, this->m_iNbOfLTC4PerPoint);
            fp >> this->m_vvCVMInverseOfLTCCov[i][j];
        }
    }
    fp.close();fp.clear();
}

