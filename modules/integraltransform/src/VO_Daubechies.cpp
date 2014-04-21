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
* Create Date:      2010-03-05                                                                      *
* Modify Date:      2014-04-15                                                                      *
****************************************************************************************************/


#include "VO_Daubechies.h"
#include <vector>

using namespace std;

// Explained by JIA Pei, we can only deal with Daubechies until D20
float VO_Daubechies::daub[10][20] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.6830127, 1.1830127, 0.3169873, -0.1830127},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.47046721, 1.14111692, 0.650365, -0.19093442, -0.12083221, 0.0498175},
    {0,0,0,0,0,0,0,0,0,0,0,0,0.32580343, 1.01094572, 0.8922014, -0.03957503, -0.26450717, 0.0436163, 0.0465036, -0.01498699},
    {0,0,0,0,0,0,0,0,0,0,0.22641898, 0.85394354, 1.02432694, 0.19576696, -0.34265671, -0.04560113, 0.10970265, -0.00882680, -0.01779187, 4.71742793e-3},
    {0,0,0,0,0,0,0,0,0.15774243, 0.69950381, 1.06226376,     0.44583132, -0.31998660, -0.18351806, 0.13788809, 0.03892321, -0.04466375, 7.83251152e-4, 6.75606236e-3, -1.52353381e-3},
    {0,0,0,0,0,0,0.11009943, 0.56079128, 1.03114849, 0.66437248, -0.20351382, -0.31683501, 0.1008467, 0.11400345, -0.05378245, -0.02343994, 0.01774979, 6.07514995e-4, -2.54790472e-3, 5.00226853e-4},
    {0,0,0,0,0.07695562, 0.44246725, 0.95548615, 0.82781653, -0.02238574, -0.40165863, 6.68194092e-4, 0.18207636, -0.02456390, -0.06235021, 0.01977216, 0.01236884, -6.88771926e-3, -5.54004549e-4, 9.55229711e-4, -1.66137261e-4}, 
    {0,0,0.05385035, 0.34483430, 0.85534906, 0.92954571, 0.18836955, -0.41475176, -0.13695355, 0.21006834, 0.043452675, -0.09564726, 3.54892813e-4, 0.03162417, -6.67962023e-3, -6.05496058e-3, 2.61296728e-3, 3.25814671e-4, -3.56329759e-4, 5.5645514e-5},
    {0.03771716, 0.26612218, 0.74557507, 0.97362811, 0.39763774, -0.35333620, -0.27710988, 0.18012745, 0.13160299, -0.10096657, -0.04165925, 0.04696981, 5.10043697e-3, -0.01517900, 1.97332536e-3, 2.81768659e-3, -9.69947840e-4, -1.64709006e-4, 1.32354367e-4, -1.875841e-5}
};


void VO_Daubechies::init()
{
    this->m_iDaubN = 0;
    //this->m_iWaveletType    = DAUB;
    this->m_bInvertible         = true;
    this->m_bOrthogonal         = true;
    this->m_bBiorthogonal       = false;
}


/**
 * @author      JIA Pei
 * @brief       Create Daubechies wavelet
 * @ref         http://en.wikipedia.org/wiki/Daubechies_wavelet
 *              b_k = ( − 1)^k *a_{N − 1 − k}
 */
void VO_Daubechies::VO_PrepareKernel(unsigned int daubN)
{
    if( ! (daubN % 2) )
    {
        cerr << "VO_Daubechies daubN should be an even number" << endl;
        exit(1);
    }
    if( daubN < 2 || daubN > 20 )
    {
        cerr << "VO_Daubechies daubN should be between 2 and 20" << endl;
        exit(1);
    }

    unsigned int idx = daubN/2 - 1;
    this->m_MatKernel = cv::Mat_<float>::zeros(daubN, daubN);
    for(unsigned int i = 0; i < daubN; i++)
    {
        for(unsigned int j = 0; j < daubN; j++)
        {
            this->m_MatKernel(i, j) = VO_Daubechies::daub[idx][daubN-1-j]*(j%2?-1:1);
        }
    }

    switch(daubN)
    {
        case 2:
            this->m_iWaveletType    =     DAUBECHIES2;
        break;
        case 4:
            this->m_iWaveletType    =     DAUBECHIES4;
        break;
        case 6:
            this->m_iWaveletType    =     DAUBECHIES6;
        break;
        case 8:
            this->m_iWaveletType    =     DAUBECHIES8;
        break;
        case 10:
            this->m_iWaveletType    =     DAUBECHIES10;
        break;
        case 12:
            this->m_iWaveletType    =     DAUBECHIES12;
        break;
        case 14:
            this->m_iWaveletType    =     DAUBECHIES14;
        break;
        case 16:
            this->m_iWaveletType    =     DAUBECHIES16;
        break;
        case 18:
            this->m_iWaveletType    =     DAUBECHIES18;
        break;
        case 20:
            this->m_iWaveletType    =     DAUBECHIES20;
        break;
    }
    this->m_iDaubN = daubN;
}


/**
 * @author      JIA Pei
 * @version     2010-03-05
 * @brief       Forward Daubechies Transform
 * @return      void
 */
void VO_Daubechies::VO_ForwardTransform(const cv::Mat_<float>& iImg, cv::Mat_<float>& oImg) const
{
    
}


/**
 * @author      JIA Pei
 * @version     2010-03-05
 * @brief       Backward Daubechies Transform
 * @return      void
 */
void VO_Daubechies::VO_BackwardTransform(const cv::Mat_<float>& iImg, cv::Mat_<float>& oImg) const
{
    
}

