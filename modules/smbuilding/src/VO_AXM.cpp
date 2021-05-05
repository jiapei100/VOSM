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

#include "VO_AXM.h"


/**
 * @author      JIA Pei
 * @version     2016-08-24
 * @brief       a pair of shape and texture, respectively decomposed to a shape and a texture
 * @param       iPairShapeTexture   Input - the pair of shape and texture
 * @param       oShapeParams        Output - shape parameters
 * @param       oTextureParams      Output - texture parameters
 * @return      void
*/
void VO_AXM::SplitShapeTextureParams(const std::pair<VO_Shape, VO_Texture>& iPairShapeTexture, 
                                    cv::Mat_<float>& oShapeParams, 
                                    cv::Mat_<float>& oTextureParams )
{
    VO_Shape iShape = iPairShapeTexture.first;
    VO_Texture iTexture = iPairShapeTexture.second;

    unsigned int NbOfShapeDim = iShape.GetNbOfDim();
    float tempNorm = 0.0f;
    std::vector<float> tempTheta;
    tempTheta.resize(NbOfShapeDim == 2? 1:3);
    cv::Mat_<float> tempCOG = cv::Mat_<float>::zeros(1, NbOfShapeDim);
    
    this->VO_CalcAllParams4AnyShapeWithConstrain(iShape, oShapeParams, tempNorm, tempTheta, tempCOG);
    this->VO_CalcAllParams4AnyTexture(iTexture, oTextureParams);
}


/**
 * @author      JIA Pei
 * @version     2016-08-24
 * @brief       shapeParam to shape, textureParam to texture, then, combine to a pair
 * @param       iShapeParams        Input - shape parameters
 * @param       iTextureParams      Input - texture parameters
 * @param       oPairShapeTexture   Output - the pair of shape and texture    
 * @return      void
*/
void VO_AXM::CombineShapeTextureParams( const cv::Mat_<float>& iShapeParams, 
                                        const cv::Mat_<float>& iTextureParams,
                                        std::pair<VO_Shape, VO_Texture>& oPairShapeTexture )
{
    unsigned int NbOfShapeDim = iShapeParams.rows;
    unsigned int NbOfTextureRep = iTextureParams.rows;
    
    VO_Shape oShape;
    VO_Texture oTexture;
    this->VO_SParamBackProjectToAlignedShape(iShapeParams, oShape, NbOfShapeDim);
    this->VO_TParamBackProjectToNormalizedTexture(iTextureParams, oTexture, NbOfTextureRep);
    
    oPairShapeTexture.first = oShape;
    oPairShapeTexture.second = oTexture;
}


/**
 * @author      JIA Pei
 * @version     2010-02-13
 * @brief       Save ASM to a specified folder
 * @param       fd      Input - the folder that ASM to be saved to
 * @return      void
*/
void VO_AXM::VO_Save ( const std::string& fd )
{
    switch(this->m_iMethod)
    {
        case AAM_BASIC:
        case AAM_DIRECT:
        case AAM_FAIA:
        case AAM_CMUICIA:
        case AAM_IAIA:
        VO_TextureModel::VO_Save(fd);
        break;
        case ASM_PROFILEND:
        case ASM_LTC:
        VO_ShapeModel::VO_Save(fd);
        break;
        case CLM:
        case AFM:
        break;
    }
    
    // create AXM subfolder for just AXM model data
    std::string fn = fd+"/AXM";
    if (!boost::filesystem::is_directory(fn) )
        boost::filesystem::create_directory( fn );

    std::ofstream fp;
    std::string tempfn;

    // AXM
    tempfn = fn + "/AXM" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_iNbOfPyramidLevels" << std::endl << this->m_iNbOfPyramidLevels << std::endl;
    fp.close();fp.clear();
}


/**
 * @author      JIA Pei
 * @version     2010-02-13
 * @brief       Load all trained data
 * @param       fd      Input - the folder that ASM to be saved to
 * @return      void
*/
void VO_AXM::VO_Load ( const std::string& fd )
{
    switch(this->m_iMethod)
    {
        case AAM_BASIC:
        case AAM_DIRECT:
        case AAM_FAIA:
        case AAM_CMUICIA:
        case AAM_IAIA:
        VO_TextureModel::VO_Load(fd);
        break;
        case ASM_PROFILEND:
        case ASM_LTC:
        VO_ShapeModel::VO_Load(fd);
        break;
        case CLM:
        case AFM:
        break;
    }
    
    std::string fn = fd+"/AXM";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "AXM subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;

    // AXM
    tempfn = fn + "/AXM" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp >> this->m_iNbOfPyramidLevels;           // m_iNbOfPyramidLevels
    fp.close();fp.clear();
}


/**
 * @author      JIA Pei
 * @version     2010-02-13
 * @brief       Load all trained data for fitting
 * @param       fd      Input - the folder that ASM to be saved to
 * @return      void
*/
void VO_AXM::VO_LoadParameters4Fitting ( const std::string& fd )
{
    switch(this->m_iMethod)
    {
        case AAM_BASIC:
        case AAM_DIRECT:
        case AAM_FAIA:
        case AAM_CMUICIA:
        case AAM_IAIA:
        VO_TextureModel::VO_LoadParameters4Fitting(fd);
        break;
        case ASM_PROFILEND:
        case ASM_LTC:
        VO_ShapeModel::VO_LoadParameters4Fitting(fd);
        break;
        case CLM:
        case AFM:
        break;
    }
    
    std::string fn = fd+"/AXM";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "AXM subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;

    // AXM
    tempfn = fn + "/AXM" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp >> this->m_iNbOfPyramidLevels;                    // m_iNbOfPyramidLevels
    fp.close();fp.clear();
}

