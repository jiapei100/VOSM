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

#include "VO_FacePart.h"

std::ostream& operator<<(std::ostream& os, const VO_FacePart& facepart)
{
    switch( facepart.GetType() )
    {
    case VO_FacePart::CHIN:
        os << "m_vChin" << " ";
        break;
    case VO_FacePart::LEFTEYEBROW:
        os << "m_vLeftEyebrow" << " ";
        break;
    case VO_FacePart::RIGHTEYEBROW:
        os << "m_vRightEyebrow" << " ";
        break;
    case VO_FacePart::LEFTEYE:
        os << "m_vLeftEye" << " ";
        break;
    case VO_FacePart::RIGHTEYE:
        os << "m_vRightEye" << " ";
        break;
    case VO_FacePart::NOSE:
        os << "m_vNose" << " ";
        break;
    case VO_FacePart::NOSTRIL:
        os << "m_vNostril" << " ";
        break;
    case VO_FacePart::NOSETIP:
        os << "m_vNoseTip" << " ";
        break;
    case VO_FacePart::LIPOUTERLINE:
        os << "m_vLipOuterLine" << " ";
        break;
    case VO_FacePart::LIPINNERLINE:
        os << "m_vLipInnerLine" << " ";
        break;
    case VO_FacePart::LIPUPPEROUTERLINE:
        os << "m_vLipUpperOuterLine" << " ";
        break;
    case VO_FacePart::LIPUPPERINNERLINE:
        os << "m_vLipUpperInnerLine" << " ";
        break;
    case VO_FacePart::LIPDOWNEROUTERLINE:
        os << "m_vLipDownerOuterLine" << " ";
        break;
    case VO_FacePart::LIPDOWNERINNERLINE:
        os << "m_vLipDownerInnerLine" << " ";
        break;
    case VO_FacePart::LEFTSIDEPOINTS:
        os << "m_vLeftSidePoints" << " ";
        break;
    case VO_FacePart::RIGHTSIDEPOINTS:
        os << "m_vRightSidePoints" << " ";
        break;
    case VO_FacePart::MIDLINEPOINTS:
        os << "m_vMidlinePoints" << " ";
        break;
    case VO_FacePart::EYECORNERPOINTS:
        os << "m_vEyeCornerPoints" << " ";
        break;
    case VO_FacePart::MOUTHCORNERPOINTS:
        os << "m_vMouthCornerPoints" << " ";
        break;
    case VO_FacePart::PITCHAXISLINEPOINTS:
        os << "m_vPitchAxisLinePoints" << " ";
        break;
    case VO_FacePart::LEFTIRIS:
        os << "m_vLeftIris" << " ";
        break;
    case VO_FacePart::RIGHTIRIS:
        os << "m_vRightIris" << " ";
        break;
    case VO_FacePart::LEFTEAR:
        os << "m_vLeftEar" << " ";
        break;
    case VO_FacePart::RIGHTEAR:
        os << "m_vRightEar" << " ";
        break;
    }

    if( facepart.IsClosedOrNot() )
        os << "closed" << " ";
    else
        os << "open" << " ";

    for(unsigned int i = 0; i < facepart.GetIndexes().size(); i++)
    {
        os << facepart.GetIndexes()[i] << " ";
    }

    return os;
}


std::istream& operator>>(std::istream& is, VO_FacePart& facepart)
{
    std::string temp;
    unsigned int tempUI;

    is >> temp;
    if(temp == "m_vChin")
    {
        facepart.m_iType = VO_FacePart::CHIN;
    }
    else if(temp == "m_vLeftEyebrow")
    {
        facepart.m_iType = VO_FacePart::LEFTEYEBROW;
    }
    else if(temp == "m_vRightEyebrow")
    {
        facepart.m_iType = VO_FacePart::RIGHTEYEBROW;
    }
    else if(temp == "m_vLeftEye")
    {
        facepart.m_iType = VO_FacePart::LEFTEYE;
    }
    else if(temp == "m_vRightEye")
    {
        facepart.m_iType = VO_FacePart::RIGHTEYE;
    }
    else if(temp == "m_vNose")
    {
        facepart.m_iType = VO_FacePart::NOSE;
    }
    else if(temp == "m_vNostril")
    {
        facepart.m_iType = VO_FacePart::NOSTRIL;
    }
    else if(temp == "m_vNoseTip")
    {
        facepart.m_iType = VO_FacePart::NOSETIP;
    }
    else if(temp == "m_vLipOuterLine")
    {
        facepart.m_iType = VO_FacePart::LIPOUTERLINE;
    }
    else if(temp == "m_vLipInnerLine")
    {
        facepart.m_iType = VO_FacePart::LIPINNERLINE;
    }
    else if(temp == "m_vLipUpperOuterLine")
    {
        facepart.m_iType = VO_FacePart::LIPUPPEROUTERLINE;
    }
    else if(temp == "m_vLipUpperInnerLine")
    {
        facepart.m_iType = VO_FacePart::LIPUPPERINNERLINE;
    }
    else if(temp == "m_vLipDownerOuterLine")
    {
        facepart.m_iType = VO_FacePart::LIPDOWNEROUTERLINE;
    }
    else if(temp == "m_vLipDownerInnerLine")
    {
        facepart.m_iType = VO_FacePart::LIPDOWNERINNERLINE;
    }
    else if(temp == "m_vLeftSidePoints")
    {
        facepart.m_iType = VO_FacePart::LEFTSIDEPOINTS;
    }
    else if(temp == "m_vRightSidePoints")
    {
        facepart.m_iType = VO_FacePart::RIGHTSIDEPOINTS;
    }
    else if(temp == "m_vMidlinePoints")
    {
        facepart.m_iType = VO_FacePart::MIDLINEPOINTS;
    }
    else if(temp == "m_vEyeCornerPoints")
    {
        facepart.m_iType = VO_FacePart::EYECORNERPOINTS;
    }
    else if(temp == "m_vMouthCornerPoints")
    {
        facepart.m_iType = VO_FacePart::MOUTHCORNERPOINTS;
    }
    else if(temp == "m_vPitchAxisLinePoints")
    {
        facepart.m_iType = VO_FacePart::PITCHAXISLINEPOINTS;
    }
    else if(temp == "m_vLeftIris")
    {
        facepart.m_iType = VO_FacePart::LEFTIRIS;
    }
    else if(temp == "m_vRightIris")
    {
        facepart.m_iType = VO_FacePart::RIGHTIRIS;
    }
    else if(temp == "m_vLeftEar")
    {
        facepart.m_iType = VO_FacePart::LEFTEAR;
    }
    else if(temp == "m_vRightEar")
    {
        facepart.m_iType = VO_FacePart::RIGHTEAR;
    }

    is >> temp;
    if(temp == "open")
        facepart.m_bClosed = false;
    else if(temp == "closed")
        facepart.m_bClosed = true;

    while (is >> tempUI)
    {
        facepart.m_vIndexes.push_back(tempUI);
    }

    return is;
}

