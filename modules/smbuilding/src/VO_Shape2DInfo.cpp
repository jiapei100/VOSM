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

#include "VO_Shape2DInfo.h"


std::ostream& operator<<(std::ostream& os, const VO_Shape2DInfo& shapeinfo)
{
   os << shapeinfo.GetPath() << " "
        << shapeinfo.GetType() << " "
        << shapeinfo.GetIndex() << " "
        << shapeinfo.GetFrom() << " "
        << shapeinfo.GetTo();

	return os;
}


std::istream& operator>>(std::istream &is, VO_Shape2DInfo& shapeinfo)
{
    unsigned int tempUI;

    // path
    is >> tempUI;
    shapeinfo.SetPath(tempUI);
    // type
    is >> tempUI;
    shapeinfo.SetType(tempUI);
    // current point index
    is >> tempUI;
    shapeinfo.SetIndex(tempUI);
    // connects from
    is >> tempUI;
    shapeinfo.SetFrom(tempUI);
    // connects to
    is >> tempUI;
    shapeinfo.SetTo(tempUI);

    return is;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-05
 * @brief      	read a file to get the shape information
 * @param      	filename                        input parameter, file to read from
 * @param      	cv::vector<VO_Shape2DInfo>       	output parameter, a cv::vector of all shape points' information
 * @param      	VO_FaceParts       				output parameter, a cv::vector of all parts information
*/
void VO_Shape2DInfo::ReadShape2DInfo(const std::string& filename, cv::vector<VO_Shape2DInfo>& oShapeInfo, VO_FaceParts& faceparts)
{
    VO_Shape2DInfo tempShapeInfo;
    VO_FacePart onePart;

    std::fstream fp;
    std::string temp, line;
    unsigned int tempUI;
    unsigned int NbOfPoints;

     // ShapeInfo.txt
    fp.open(filename.c_str (), std::ios::in);
    fp >> tempUI;
    getline(fp, temp);
    NbOfPoints = tempUI;
    oShapeInfo.resize(NbOfPoints);
    getline(fp, temp);
    for(unsigned int i = 0; i < NbOfPoints; i++)
    {
        // Path
        fp >> tempUI;
        tempShapeInfo.SetPath(tempUI);
        // type
        fp >> tempUI;
        tempShapeInfo.SetType(tempUI);
        // Index
        fp >> tempUI;
        tempShapeInfo.SetIndex(tempUI);
        // connects from
        fp >> tempUI;
        tempShapeInfo.SetFrom(tempUI);
        // connects to
        fp >> tempUI;
        tempShapeInfo.SetTo(tempUI);

        oShapeInfo[i] = tempShapeInfo;
    }
    fp >> faceparts;

    fp.close();fp.clear();
}

