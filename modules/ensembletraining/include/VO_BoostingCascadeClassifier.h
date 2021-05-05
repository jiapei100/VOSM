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

#ifndef __VO_BOOSTINGCASCADECLASSIFIER_H__
#define __VO_BOOSTINGCASCADECLASSIFIER_H__


#include "VO_Features.h"
#include "VO_AdditiveStrongerClassifier.h"
#include "VO_BoostingSingleEnsembleClassifier.h"


/** 
 * @author      JIA Pei
 * @brief       Boosting cascade classifier.
 * @note        FIXME
 */
class VO_BoostingCascadeClassifier : public VO_AdditiveStrongerClassifier
{
private:
    /** Number of stages */
    unsigned int                m_iNbOfStages;
    
    /** min true positive */
    float                         m_fMinTruePositive;
    
    /** max wrong classification */
    float                         m_fMaxWrongClassification;
    
    /** Used Features */
    /** Explained by JIA Pei. Abstract class can't be instantiated, so, use pointer */
    /** In addition, Dimashova, Maria's precious suggestion is "do not load all features once for all" 
     * http://opencv.willowgarage.com/wiki/Contributors */
    VO_Features*                m_VOFeatures;
    
public:
    /** Boosting cascade structure */
    enum {UNDEFINED = 0, SINGLECASCADE = 1, PARALLELCASCADE = 2, CASCADEDECISIONTREE = 3, BFSCASCADE = 4};

    /** Constructor */
    explicit VO_BoostingCascadeClassifier();

    /** Destructor */
    ~VO_BoostingCascadeClassifier();

    /** training the boosting cascade classifier */
    bool train( const std::string& _cascadeDirName,
                const std::vector<std::string> _posFilenames,
                const std::vector<std::string> _negFilenames,
                int _precalcValBufSize,
                int _precalcIdxBufSize,
                int _numStages,
                float _minTruePositive,
                float _maxWrongClassification,
                const VO_Features* _featureParams);
};

#endif  // __VO_BOOSTINGCASCADECLASSIFIER_H__

