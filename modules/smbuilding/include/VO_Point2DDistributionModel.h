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

#ifndef __VO_POINT2DDISTRIBUTIONMODEL_H__
#define __VO_POINT2DDISTRIBUTIONMODEL_H__


#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "VO_Shape.h"
#include "VO_Ellipse.h"


/** 
 * @author      JIA Pei
 * @brief       2D point distribution model
 */
class VO_Point2DDistributionModel
{
friend class VO_Fitting2DSM;
friend class VO_FittingAAMBasic;
friend class VO_FittingAAMForwardIA;
friend class VO_FittingAAMInverseIA;
friend class VO_FittingAFM;
friend class VO_FittingASMLTCs;
friend class VO_FittingASMNDProfiles;
protected:
    /** 2D normal distribution can be represented by rotated ellipse */
    std::vector<VO_Ellipse>         m_VONormalizedEllipses;

    /** Initialization */
    void                            init();

public:
    /** Default constructor to create a VO_Point2DDistributionModel object */
    VO_Point2DDistributionModel();

    /** Destructor */
    virtual ~VO_Point2DDistributionModel();

    /** Build cv::Point Model */
    void                            VO_BuildPointDistributionModel(    const std::vector<VO_Shape>& allAlignedShapes );

    /** Constrain respective single point according to its PDM */
    static void                     VO_ConstrainSinglePoint(cv::Point2f& pt, const VO_Ellipse& ellipse);
    
    /** Scale all ellipses in this PDM */
    static void                     VO_ScalePDMEllipses(const std::vector<VO_Ellipse>& iEllipses, float scale, std::vector<VO_Ellipse>& oEllipses);

    /** Constrain a shape into cv::Point Distribution Models */
    void                            VO_ConstrainAllPoints(VO_Shape& ioShape);

    /** Save cv::Point Model, to a specified folder */
    void                            VO_Save(const std::string& fd);

    /** Load all parameters */
    void                            VO_Load(const std::string& fd);

    /** Load parameters for fitting */
    void                            VO_LoadParameters4Fitting(const std::string& fd);
    
    /** Gets and Sets */
    std::vector<VO_Ellipse>         GetPDMEllipses() const { return this->m_VONormalizedEllipses; }

};

#endif // __VO_POINT2DDISTRIBUTIONMODEL_H__

