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
* Create Date:      2013-09-12                                                                      *
****************************************************************************************************/


#ifndef __VO_BOOSTCOMMON_H__
#define __VO_BOOSTCOMMON_H__

#ifdef _WIN32
#include <Windows.h>
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/path.hpp"


/**
 * @author     	JIA Pei
 * @version    	2012-10-01
 * @brief      	Get local date by using boost functions
 * @param      	None
 * @return     	std::string         the current local date
*/
static std::string boostGetLocalDate()
{
    std::string str;
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    std::stringstream ss;
    ss << now.date();
    str = ss.str();
    return str;
}

/**
 * @author     	JIA Pei
 * @version    	2012-10-01
 * @brief      	Get local time by using boost functions
 * @param      	None
 * @return     	std::string         the current local time
*/
static std::string boostGetLocalTime()
{
    std::string str;
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    std::stringstream ss;
    ss << now.time_of_day();
    str = ss.str();
    return str;
}

/**
 * @author     	JIA Pei
 * @version    	2012-10-01
 * @brief      	Get local date and time by using boost functions
 * @param      	None
 * @return     	std::string         the current local date and time
*/
static std::string boostGetLocalDateTime()
{
    std::string str = boostGetLocalDate();
    str += " , ";
    str += boostGetLocalTime();

    return str;
}

/**
 * @author     	JIA Pei
 * @version    	2012-10-01
 * @brief      	Get file path from an entire file name by using boost functions
 * @param      	const std::string	the entire file name
 * @return     	std::string         the obtained file path
*/
static std::string boostGetPathFromName(const std::string fn)
{
	std::string filename_noext = boost::filesystem::path(fn).stem().string();
	return filename_noext;
}

#endif		// __VO_BOOSTCOMMON_H__
