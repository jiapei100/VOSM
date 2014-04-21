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


#include <fstream>
#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include "VO_AFM.h"
#include "VO_CVCommon.h"


VO_AFM::VO_AFM()
{
	this->init();
}


void VO_AFM::init()
{
	this->m_iMethod							= VO_AXM::AFM;		// CLM
	this->m_iLocalFeatureExtractionMethod 	= VO_DiscreteWavelet::HAAR;
}


VO_AFM::~VO_AFM()
{
	
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	feature parameters constrain
 * @param      	ioC				Input and Output - appearance parameters
 * @param      	nSigma          Input - number of sigmas
 * @return		void
*/
void VO_AFM::VO_FeatureParameterConstraint(cv::Mat_<float>& ioF, float nSigma)
{
	for (unsigned int i = 0; i < ioF.cols; ++i)
    {
		float ct = nSigma * sqrt(this->m_PCANormalizedFeatures.eigenvalues.at<float>(i,0) );
        if ( ioF(0, i) > ct )
        {
            ioF(0, i) = ct;
        }
        else if ( ioF(0, i) < -ct )
        {
            ioF(0, i) = -ct;
        }
    }
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-22
 * @brief		Build Active Feature Model - quite similar to Edwards method, but proposed by Cristinace and modified by me.
 * @param      	allLandmarkFiles4Training		Input - all training landmark files
 * @param		allImgFiles4Training			Input - all training image files
 * @param      	shapeinfoFileName				Input - shape info file
 * @param		database						Input - which database is it?
 * @param		channels						Input - How many channels are to be used?
 * @param		levels							Input - multiscale levels
 * @param		trm								Input - texture representation method
 * @param      	TPShape     					Input - truncated percentage for shape model
 * @param      	useKnownTriangles  				Input - use known triangle structures??
 * @param		ltcMtd							Input - local texture constrain methods
 * @return		void
 * @note		Using "float* oProf" is much much faster than using "VO_Profile& oProf" or "cv::vector<float>"
 */
void VO_AFM::VO_BuildFeatureModel ( const cv::vector<std::string>& allLandmarkFiles4Training,
							const cv::vector<std::string>& allImgFiles4Training,
							const std::string& shapeinfoFileName,
							unsigned int database,
							unsigned int channels,
							unsigned int levels,
							int trm,
							float TPShape,
							bool useKnownTriangles,
							unsigned int ltcMtd,
							Size imgSize)
{
	if (allLandmarkFiles4Training.size() != allImgFiles4Training.size() )
		cerr << "allLandmarkFiles4Training should have the same number of allImgFiles4Training! " << endl;

	this->VO_BuildShapeModel(allLandmarkFiles4Training, shapeinfoFileName, database, TPShape, useKnownTriangles);
    this->m_iNbOfPyramidLevels      			= levels;
	this->m_iNbOfChannels						= channels;
	this->m_iTextureRepresentationMethod		= trm;
	this->m_iLocalFeatureExtractionMethod		= ltcMtd;
	this->m_localImageSize						= imgSize;
	this->m_vStringTrainingImageNames 			= allImgFiles4Training;

	this->VO_LoadFeatureTrainingData( this->m_iLocalFeatureExtractionMethod);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-22
 * @brief		Calculate Image Patch cv::Rectangle
 * @param		iImg					Input	-- the concerned image
 * @param		pt						Input	-- the point
 * @param		imgSize					Input	-- image size
 * @return		cv::Rect					of size imgSize*imgSize
 */
cv::Rect VO_AFM::VO_CalcImagePatchRect(const cv::Mat& iImg, const cv::Point2f& pt, Size imgSize)
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
 * @author     	JIA Pei
 * @version    	2010-02-05
 * @brief      	Load Training data for texture model
 * @param		mtd			Input	-- ltc method
 * @return		void
*/
void VO_AFM::VO_LoadFeatureTrainingData(unsigned int mtd)
{
	this->m_vLTCs.resize(this->m_iNbOfSamples);
	this->m_vNormalizedLTCs.resize(this->m_iNbOfSamples);
	cv::Mat img;
	cv::Mat_<float> oneLTC, tmpRow;

	for(unsigned int i = 0; i < this->m_iNbOfSamples; ++i)
	{
		unsigned int count = 0;
        this->m_vLTCs[i].Resize(this->m_iNbOfPoints, this->m_localImageSize.width*this->m_localImageSize.height);
		img = imread ( this->m_vStringTrainingImageNames[i].c_str (), 0 );

		double start = (double)cvGetTickCount();
		// Explained by JIA Pei -- wavelet feature extraction
        for(unsigned int j = 0; j < this->m_iNbOfPoints; ++j)
		{
            oneLTC = this->VO_LoadLTC4OneAnnotatedPoint(img,
														this->m_vShapes[i],
														j,
														this->m_localImageSize,
														mtd);
            tmpRow = this->m_vLTCs[i].m_MatTexture.row(j);
			oneLTC.copyTo(tmpRow);
		}

		double end = (double)cvGetTickCount();
		double elapsed = (end - start) / (cvGetTickFrequency()*1000.0);
	}
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-22
 * @brief		Build wavelet for key points
 * @param		iImg 					Input	-- the concerned image
 * @param		theShape				Input	-- the concerned shape
 * @param		ptIdx					Input	-- which point?
 * @param		imgSize					Input	-- the image size
 * @param		mtd						Input	-- LTC method
 * @return		cv::Mat_<float>				Output	-- the extracted LTC
 */
cv::Mat_<float> VO_AFM::VO_LoadLTC4OneAnnotatedPoint(const cv::Mat& iImg,
														const VO_Shape& theShape,
														unsigned int ptIdx,
                                                        cv::Size imgSize,
														unsigned int mtd)
{
	cv::Mat_<float> resLTC;
    cv::Point2f pt 					= theShape.GetA2DPoint(ptIdx);
    cv::Rect rect 					= this->VO_CalcImagePatchRect(iImg, pt, imgSize);
	cv::Mat imgPatch 				= iImg(rect);

	switch(mtd)
	{
		case VO_Features::LBP:
		{
			// initialize the image before wavelet transform 
			for(unsigned int i = 0; i < rect.height; ++i)
			{
				for(unsigned int j = 0; j < rect.width; ++j)
				{
					
				}
			}

			bool showWaveletImage =  true;
			if(showWaveletImage)
			{
				imwrite("originalImage.jpg", imgPatch);
	//			this->VO_HardSaveWaveletSingleChannelImage("waveletImage.jpg", waveParamsGray, imgSize);
	//			this->VO_HardSaveWaveletSingleChannelImage("inverseWaveletImage.jpg", waveParamsGray, imgSize);
			}
		}
		default:
		break;
	}
	
	return resLTC;
}


void VO_AFM::VO_Save ( const std::string& fd )
{
    VO_AXM::VO_Save(fd);

    // create AFM subfolder for just AFM model data
    std::string fn = fd+"/AFM";
    if (!boost::filesystem::is_directory(fn) )
        boost::filesystem::create_directory( fn );

    std::ofstream fp;
    std::string tempfn;

    // AFM
    tempfn = fn + "/AFM" + ".txt";
    fp.open(tempfn.c_str (), ios::out);

    fp << "m_iLocalFeatureExtractionMethod" << std::endl << this->m_iLocalFeatureExtractionMethod << std::endl;
    fp << "m_localImageSize" << std::endl << this->m_localImageSize.height << " " << this->m_localImageSize.width << std::endl;

    fp.close();fp.clear();

    // m_PCANormalizedLTCMean
    tempfn = fn + "/m_PCANormalizedLTCMean" + ".txt";
    fp.open(tempfn.c_str (), ios::out);
    fp << "m_PCANormalizedLTCMean" << endl;
    fp << cv::Mat_<float>(this->m_PCANormalizedFeatures.mean);
    fp.close();fp.clear();

    // m_PCANormalizedLTCeigenvectors
    tempfn = fn + "/m_PCANormalizedLTCeigenvectors" + ".txt";
    fp.open(tempfn.c_str (), ios::out);
    fp << "m_PCANormalizedLTCeigenvectors" << endl;
    fp << cv::Mat_<float>(this->m_PCANormalizedFeatures.eigenvectors);
    fp.close();fp.clear();

    // m_PCANormalizedLTCEigenvalues
    tempfn = fn + "/m_PCANormalizedLTCEigenvalues" + ".txt";
    fp.open(tempfn.c_str (), ios::out);
    fp << "m_PCANormalizedLTCEigenvalues" << endl;
    fp << cv::Mat_<float>(this->m_PCANormalizedFeatures.eigenvalues);
    fp.close();fp.clear();

}


void VO_AFM::VO_Load ( const std::string& fd )
{
    VO_AXM::VO_Load(fd);
}


void VO_AFM::VO_LoadParameters4Fitting ( const std::string& fd )
{
    VO_AXM::VO_LoadParameters4Fitting(fd); 	// Note, for ASMProfile fitting, no problem
}

