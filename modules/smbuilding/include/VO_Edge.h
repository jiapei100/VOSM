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

#ifndef __VO_EDGE_H__
#define __VO_EDGE_H__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


/** 
 * @author      JIA Pei
 * @brief       Edge - indicating two point indexes.
 */
class VO_Edge
{
friend std::ostream& operator<<(std::ostream& os, const VO_Edge& aamedge);
friend std::istream& operator>>(std::istream& is, VO_Edge& aamedge);
private:
    /** First vertex' index of this edge */
    unsigned int index1;

    /** Second vertex' index of this edge */
    unsigned int index2;

public:
    /** Default constructor to create a VO_Edge object */
    VO_Edge() {}

    /** Constructor to create a VO_Edge object with two vertexes' indexes */
    VO_Edge(unsigned int p1, unsigned int p2)
    {
        this->index1 = p1;
        this->index2 = p2;
    }

    /** Destructor */
    virtual ~VO_Edge() {}

    /** Default constructor to create a VO_Edge object */
    bool operator==(const VO_Edge& e) const
    {
        if ( ( this->index1 == e.GetIndex1() && this->index2 == e.GetIndex2() ) ||
            ( this->index1 == e.GetIndex2() && this->index2 == e.GetIndex1() ) )
            return true;
        else return false;
    }

    /** Get first index of the first edge vertex */
    unsigned int GetIndex1() const { return this->index1;}

    /** Get second index of the first edge vertex */
    unsigned int GetIndex2() const { return this->index2;}

    /** Set the first index of the first edge vertex */
    void SetIndex1(unsigned int idx1) { this->index1 = idx1;}

    /** Set the second index of the second edge vertex */
    void SetIndex2(unsigned int idx2) { this->index2 = idx2;}

};

#endif  // __VO_EDGE_H__

