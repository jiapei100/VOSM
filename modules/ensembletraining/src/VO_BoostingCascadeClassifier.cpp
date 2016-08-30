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

#include "VO_BoostingCascadeClassifier.h"
#include <queue>


/**
 * @brief Constructor
 */
VO_BoostingCascadeClassifier::VO_BoostingCascadeClassifier()
{
    this->m_iNbOfStages                 = 0;
    this->m_VOFeatures                  = NULL;
}


/**
 * @brief Destructor
 */
VO_BoostingCascadeClassifier::~VO_BoostingCascadeClassifier()
{

}


/**
 * FIXME: to be finished
 * @brief   Train a boosting cascade classifier
 * @param   _cascadeDirName     -- Input    where to store the cascade (could be half trained)
 * @param   _posFilenames       -- Input    all positive file names
 * @param   _negFilenames       -- Input    all negative file names
 * @param   _precalcValBufSize  -- Input    all positive file names
 * @param   _precalcIdxBufSize  -- Input    all negative file names
 * @param   _numStages          -- Input    number of stages
 * @param   _featureParams      -- Input    how to extract those features
 * 
 */
bool VO_BoostingCascadeClassifier::train(   const std::string& _cascadeDirName,
                                            const std::vector<std::string> _posFilenames,
                                            const std::vector<std::string> _negFilenames,
                                            int _precalcValBufSize,
                                            int _precalcIdxBufSize,
                                            int _numStages,
                                            float _minTruePositive,
                                            float _maxWrongClassification,
                                            const VO_Features* _featureParams)
{
    this->m_iNbOfPositiveSamples            = _posFilenames.size();
    this->m_iNbOfNegativeSamples            = _negFilenames.size();
    this->m_iNbOfSamples                    = this->m_iNbOfPositiveSamples + this->m_iNbOfNegativeSamples;
    this->m_iNbOfStages                     = _numStages;
    this->m_fMinTruePositive                = _minTruePositive;
    this->m_fMaxWrongClassification         = _maxWrongClassification;

    std::string dirName;
    if ( _cascadeDirName.find('/') != std::string::npos )
        dirName = _cascadeDirName + '/';
    else
        dirName = _cascadeDirName + '\\';

    /** FIXME: to be finished */
    /** OpenCV traincascade module */
    
    return true;
}
