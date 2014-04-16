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
* Create Date:      2010-11-04                                              *
* Revise Date:      2012-03-22                                              *
*****************************************************************************/


#ifndef __VO_ANNOTATIONDBIO_H__
#define __VO_ANNOTATIONDBIO_H__


#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "VO_CVCommon.h"
//#include "yaml.h"
#include "VO_Shape.h"


using namespace std;
using namespace cv;


/** 
 * @author  JIA Pei
 * @brief   IO to read/write 2D annotation files from standard databases,
 *          as well as 3D .obj files from 3D face database USF.
 */
class CAnnotationDBIO
{
public:
    /** databases for statistical shape models */
    enum DB{ BFM3D = 0,
            USF3D = 1,
            XM2VTS3D = 2,
            PUT = 3,
            IMM = 4,
            AGING = 5,
            BIOID = 6,
            XM2VTS = 7,
            FRANCK = 8,
            EMOUNT = 9,
            JIAPEI = 10 };
    
    /** Constructor */
    CAnnotationDBIO() {}

    /** Destructor */
    ~CAnnotationDBIO() {}

    /** read all annotations for .asf files */
    static void         ReadASF(const string& filename,
                                VO_Shape& oAAMShape);

    /** read all annotations for .pts files */
    static void         ReadPTS(const string& filename,
                                VO_Shape& oAAMShape);

    /** read all annotations for .obj files */
    static void         ReadOBJ(const string& filename,
                                VO_Shape& oAAMShape);

    /** read all annotations for .wrl files */
    static void         ReadWRL(const string& filename,
                                VO_Shape& oAAMShape);

    /** write all annotations for .asf files */
    static void         WriteASF(   const string& filename,
                                    const VO_Shape& iAAMShape);

    /** write all annotations for .pts files */
    static void         WritePTS(   const string& filename,
                                    const VO_Shape& iAAMShape);

    /** write all annotations for .obj files */
    static void         WriteOBJ(   const string& filename,
                                    const VO_Shape& iAAMShape);

    /** write all annotations for .wrl files */
    static void         WriteWRL(   const string& filename,
                                    const VO_Shape& iAAMShape);
    
    /** Load Training data for shape model */
    static void         VO_LoadShapeTrainingData(
                            const vector<string>& allLandmarkFiles4Training,
                            unsigned int database,
                            vector<VO_Shape>& oShapes);

    /** Load Training data for shape model */
    static void         VO_LoadShapeTrainingData(
                            const vector<string>& allLandmarkFiles4Training,
                            vector<VO_Shape>& oShapes);
};

#endif    // __VO_ANNOTATIONDBIO_H__

