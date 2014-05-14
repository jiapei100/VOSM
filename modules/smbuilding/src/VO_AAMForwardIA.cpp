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


#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/filesystem.hpp>

#include "VO_AAMForwardIA.h"



VO_AAMForwardIA::VO_AAMForwardIA()
{
    this->init();
}

/** Initialization */
void VO_AAMForwardIA::init()
{
	this->m_iMethod				= VO_AXM::AAM_FAIA;
}


VO_AAMForwardIA::~VO_AAMForwardIA()
{

}


/**
 * @author     	JIA Pei
 * @version    	2010-04-03
 * @brief		FCIA AAM
 * @param      	allLandmarkFiles4Training		Input - all training landmark files
 * @param		allImgFiles4Training			Input - all training image files
 * @param      	shapeinfoFileName				Input - shape info file
 * @param		database						Input - which database is it?
 * @param		levels							Input - multiscale levels
 * @param		channels						Input - How many channels are to be used?
 * @param		trm								Input - texture representation method
 * @param      	TPShape     					Input - truncated percentage for shape model
 * @param      	TPTexture     					Input - truncated percentage for texture model
 * @param      	useKnownTriangles  				Input - use known triangle structures??
 * @return		void
 * @note		Using "float* oProf" is much much faster than using "VO_Profile& oProf" or "std::vector<float>"
 */
void VO_AAMForwardIA::VO_BuildAAMFCIA(const std::vector<std::string>& allLandmarkFiles4Training,
                                    const std::vector<std::string>& allImgFiles4Training,
									const std::string& shapeinfoFileName, 
									unsigned int database,
									unsigned int levels,
									unsigned int channels,
									int trm, 
									float TPShape, 
									float TPTexture, 
									bool useKnownTriangles)
{
    this->VO_BuildTextureModel(	allLandmarkFiles4Training,
								allImgFiles4Training,
								shapeinfoFileName, 
								database,
								channels,
								trm, 
								TPShape, 
								TPTexture, 
								useKnownTriangles);

}


/**
 * @author		JIA Pei
 * @version    	2010-04-03
 * @brief      	Save AAMFCIA to a specified folder
 * @param      	fn         Input - the folder that AAMFCIA to be saved to
*/
void VO_AAMForwardIA::VO_Save(const std::string& fd)
{
    VO_AXM::VO_Save(fd);

    std::string fn = fd+"/AAMFCIA";
    if (!boost::filesystem::is_directory(fn) )
        boost::filesystem::create_directory( fn );

    std::fstream fp;
    std::string tempfn;

}


/**
 * @author     JIA Pei
 * @version    2010-04-03
 * @brief      Load all AAMFCIA data from a specified folder
 * @param      fd         Input - the folder that AAMFCIA to be loaded from
*/
void VO_AAMForwardIA::VO_Load(const std::string& fd)
{
    VO_AXM::VO_Load(fd);

    std::string fn = fd+"/AAMFCIA";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "AAMFCIA subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }
}


/**
 * @author     JIA Pei
 * @version    2010-04-03
 * @brief      Load all AAMICIA data from a specified folder
 * @param      fd         Input - the folder that AAMICIA to be loaded from
*/
void VO_AAMForwardIA::VO_LoadParameters4Fitting(const std::string& fd)
{
    VO_AXM::VO_LoadParameters4Fitting(fd);

    std::string fn = fd+"/AAMFCIA";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "AAMFCIA subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::fstream fp;
    std::string tempfn;
    std::string temp;

}

