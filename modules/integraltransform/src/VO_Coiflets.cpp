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

#include "VO_Coiflets.h"


/// Coiflets transform parameters
float VO_Coiflets::coif[5][30] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.1028594569415370, 0.4778594569415370, 1.2057189138830700, 0.5442810861169260, -0.1028594569415370, -0.0221405430584631},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0231751934774337, -0.0586402759669371, -0.0952791806220162, 0.5460420930695330, 1.1493647877137300, 0.5897343873912380, -0.1081712141834230, -0.0840529609215432, 0.0334888203265590, 0.0079357672259240, -0.0025784067122813, -0.0010190107982153},
    {0,0,0,0,0,0,0,0,0,0,0,0,-0.0053648373418441, 0.0110062534156628, 0.0331671209583407, -0.0930155289574539, -0.0864415271204239, 0.5730066705472950, 1.1225705137406600, 0.6059671435456480, -0.1015402815097780, -0.1163925015231710, 0.0488681886423339, 0.0224584819240757, -0.0127392020220977, -0.0036409178311325, 0.0015804102019152, 0.0006593303475864, -0.0001003855491065, -0.0000489314685106},
    {0,0,0,0,0,0,0.0012619224228619, -0.0023044502875399, -0.0103890503269406, 0.0227249229665297, 0.0377344771391261, -0.1149284838038540, -0.0793053059248983, 0.5873348100322010, 1.1062529100791000, 0.6143146193357710, -0.0942254750477914, -0.1360762293560410, 0.0556272739169390, 0.0354716628454062, -0.0215126323101745, -0.0080020216899011, 0.0053053298270610, 0.0017911878553906, -0.0008330003901883, -0.0003676592334273, 0.0000881604532320, 0.0000441656938246, -0.0000046098383254, -0.0000025243583600},
    {-0.0002999290456692, 0.0005071055047161, 0.0030805734519904, -0.0058821563280714, -0.0143282246988201, 0.0331043666129858, 0.0398380343959686, -0.1299967565094460, -0.0736051069489375, 0.5961918029174380, 1.0950165427080700, 0.6194005181568410, -0.0877346296564723, -0.1492888402656790, 0.0583893855505615, 0.0462091445541337, -0.0279425853727641, -0.0129534995030117, 0.0095622335982613, 0.0034387669687710, -0.0023498958688271, -0.0009016444801393, 0.0004268915950172, 0.0001984938227975, -0.0000582936877724, -0.0000300806359640, 0.0000052336193200, 0.0000029150058427, -0.0000002296399300, -0.0000001358212135}
};


/**
 * @brief VO_Coiflets::init
 */
void VO_Coiflets::init()
{
//    this->m_iWaveletType        = COIF;
    this->m_bInvertible             = true;
    this->m_bOrthogonal             = true;
    this->m_bBiorthogonal           = false;
}


/**
 * @author      JIA Pei
 * @brief       Create Coiflets wavelet
 * @ref         http://en.wikipedia.org/wiki/Coiflet
 *              B_k = ( − 1)^k *C_{N − 1 − k}
 */
void VO_Coiflets::VO_PrepareKernel(unsigned int coifN)
{
    if( ! (coifN % 6) )
    {
        std::cerr << "VO_Coiflets coifN should be able to be devided by 6" << std::endl;
        exit(1);
    }
    if( coifN < 6 || coifN > 30 )
    {
        std::cerr << "VO_Coiflets coifN should be between 6 and 30" << std::endl;
        exit(1);
    }

    unsigned int idx = coifN/6 - 1;
    this->m_MatKernel = cv::Mat_<float>::zeros(coifN, coifN);
    for(unsigned int i = 0; i < coifN; i++)
    {
        for(unsigned int j = 0; j < coifN; j++)
        {
            this->m_MatKernel(i, j) = VO_Coiflets::coif[idx][coifN-1-j]*(j%2?-1:1);
        }
    }

    switch(coifN)
    {
        case 6:
            this->m_iWaveletType    =     COIFLET6;
        break;
        case 12:
            this->m_iWaveletType    =     COIFLET12;
        break;
        case 18:
            this->m_iWaveletType    =     COIFLET18;
        break;
        case 24:
            this->m_iWaveletType    =     COIFLET24;
        break;
        case 30:
            this->m_iWaveletType    =     COIFLET30;
        break;
    }
    this->m_iCoifN = coifN;
}


/**
 * @author      JIA Pei
 * @version     2010-03-05
 * @brief       Forward Coiflets Transform
 * @return      void
 */
void VO_Coiflets::VO_ForwardTransform(const cv::Mat_<float>& iImg, cv::Mat_<float>& oImg) const
{
    
}


/**
 * @author      JIA Pei
 * @version     2010-03-05
 * @brief       Backward Coiflets Transform
 * @return      void
 */
void VO_Coiflets::VO_BackwardTransform(const cv::Mat_<float>& iImg, cv::Mat_<float>& oImg) const
{
    
}

