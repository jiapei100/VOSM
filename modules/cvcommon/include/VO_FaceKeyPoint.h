/****************************************************************************
*                                                                           *
*   IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.       *
*                                                                           *
*   By downloading, copying, installing or using the software you agree to  *
*   this license. If you do not agree to this license, do not download,     *
*   install, copy or use the software.                                      *
*                                                                           *
*                           License Agreement                               *
*                   For Vision Open Statistical Models                      *
*                                                                           *
*   Copyright (C):      2006~2012 by JIA Pei, all rights reserved.          *
*                                                                           *
*   VOSM is free software under the terms of the GNU Lesser General Public  *
*   License (GNU LGPL) as published by the Free Software Foundation; either *
*   version 3.0 of the License, or (at your option) any later version.      *
*   You can use it, modify it, redistribute it, etc; and redistribution and *
*   use in source and binary forms, with or without modification, are       *
*   permitted provided that the following conditions are met:               *
*                                                                           *
*   a) Redistribution's of source code must retain this whole paragraph of  *
*   copyright notice, including this list of conditions and all the         *
*   following contents in this  copyright paragraph.                        *
*                                                                           *
*   b) Redistribution's in binary form must reproduce this whole paragraph  *
*   of copyright notice, including this list of conditions and all the      *
*   following contents in this copyright paragraph, and/or other materials  *
*   provided with the distribution.                                         *
*                                                                           *
*   c) The name of the copyright holders may not be used to endorse or      *
*   promote products derived from this software without specific prior      *
*   written permission.                                                     *
*                                                                           *
*   Any publications based on this code must cite the following five papers,*
*   technical reports and on-line materials.                                *
*   1) P. JIA, 2D Statistical Models, Technical Report of Vision Open       *
*   Working Group, 2st Edition, October 21, 2010.                           *
*   http://www.visionopen.com/members/jiapei/publications/pei_sm2dreport2010.pdf*
*   2) P. JIA. Audio-visual based HMI for an Intelligent Wheelchair.        *
*   PhD thesis, University of Essex, February, 2011.                        *
*   http://www.visionopen.com/members/jiapei/publications/pei_phdthesis2010.pdf*
*   3) T. Cootes and C. Taylor. Statistical models of appearance for        *
*   computer vision. Technical report, Imaging Science and Biomedical       *
*   Engineering, University of Manchester, March 8, 2004.                   *
*   http://www.isbe.man.ac.uk/~bim/Models/app_models.pdf                    *
*   4) I. Matthews and S. Baker. Active appearance models revisited.        *
*   International Journal of Computer Vision, 60(2):135--164, November 2004.*
*   http://www.ri.cmu.edu/pub_files/pub4/matthews_iain_2004_2/matthews_iain_2004_2.pdf*
*   5) M. B. Stegmann, Active Appearance Models: Theory, Extensions and     *
*   Cases, 2000.                                                            *
*   http://www2.imm.dtu.dk/~aam/main/                                       *
*                                                                           *
* Version:          0.4                                                     *
* Author:           JIA Pei                                                 *
* Contact:          jp4work@gmail.com                                       *
* URL:              http://www.visionopen.com                               *
* Create Date:      2010-02-05                                              *
* Revise Date:      2012-03-22                                              *
*****************************************************************************/


#ifndef __VO_FACEKEYPOINT_H__
#define __VO_FACEKEYPOINT_H__


#include <vector>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "VO_Shape.h"
#include "VO_FaceParts.h"

using namespace std;
using namespace cv;


/** 
 * @author      JIA Pei
 * @brief       Calculate some face key points.
 */
class VO_KeyPoint
{
public:
    enum {  CENTEROFGRAVITY = 0,
            LEFTEYELEFTCORNER = 1,
            LEFTEYERIGHTCORNER = 2,
            LEFTEYECENTER = 3,
            RIGHTEYELEFTCORNER = 4,
            RIGHTEYERIGHTCORNER = 5,
            RIGHTEYECENTER = 6,
            NOSETIPKEY = 7,
            NOSTRILLEFT = 8,
            NOSTRILRIGHT = 9,
            NOSECENTER = 10,
            MOUTHLEFTCORNER = 11,
            MOUTHRIGHTCORNER = 12,
            MOUTHCENTER = 13,
            EARLOBELEFT = 14,
            EARLOBERIGHT = 15 };

    /** Constructor */
    explicit VO_KeyPoint() {}

    /** Destructor */
    ~VO_KeyPoint() {}

    static void CalcFaceKeyline(
        vector<float>& oLine, 
        const VO_Shape& iShape, 
        const VO_FaceParts& iFaceParts, 
        VO_Shape& oSubshape, 
        unsigned int partIdx = VO_FacePart::MIDLINEPOINTS);

    static void CalcFaceKeyPoint(
        Point2f& oPoint, 
        const VO_Shape& iShape, 
        const VO_FaceParts& iFaceParts, 
        unsigned int ptType );
};

#endif  // __VO_FACEKEYPOINT_H__

