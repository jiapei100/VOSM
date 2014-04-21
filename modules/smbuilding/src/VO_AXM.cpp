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

#include "VO_AXM.h"


VO_AXM::VO_AXM(unsigned int method, unsigned int levels)
{
	this->init(method, levels);
}


void VO_AXM::init(unsigned int method, unsigned int levels)
{
	this->m_iMethod					=	method;
    this->m_iNbOfPyramidLevels 		= 	levels;
}


VO_AXM::~VO_AXM()
{
	
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-13
 * @brief      	Save ASM to a specified folder
 * @param      	fd         	Input - the folder that ASM to be saved to
 * @return		void
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
    fp.open(tempfn.c_str (), ios::out);
    fp << "m_iNbOfPyramidLevels" << endl << this->m_iNbOfPyramidLevels << endl;
    fp.close();fp.clear();
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-13
 * @brief      	Load all trained data
 * @param      	fd         	Input - the folder that ASM to be saved to
 * @return		void
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
        cout << "AXM subfolder is not existing. " << endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;

    // AXM
    tempfn = fn + "/AXM" + ".txt";
    fp.open(tempfn.c_str (), ios::in);
    fp >> temp >> this->m_iNbOfPyramidLevels;					// m_iNbOfPyramidLevels
    fp.close();fp.clear();
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-13
 * @brief      	Load all trained data for fitting
 * @param      	fd         	Input - the folder that ASM to be saved to
 * @return		void
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
        cout << "AXM subfolder is not existing. " << endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;

    // AXM
    tempfn = fn + "/AXM" + ".txt";
    fp.open(tempfn.c_str (), ios::in);
    fp >> temp >> this->m_iNbOfPyramidLevels;					// m_iNbOfPyramidLevels
    fp.close();fp.clear();
}

