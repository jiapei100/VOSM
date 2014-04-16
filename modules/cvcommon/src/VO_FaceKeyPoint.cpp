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


#include "VO_FaceKeyPoint.h"
#include "VO_Common.h"

/**
* @brief    Calculate some key lines on the face
* @param    oLine       Output  output those lines
* @param    iShape      Input   the known shape
* @param    iFaceParts  Input   the faceparts
* @param    oSubshape   Output  the output subshape, namely, the line is represented by a VO_Shape
* @param    partIdx     Input   which part is it
* @return   void
 */
void VO_KeyPoint::CalcFaceKeyline(
    vector<float>& oLine,
    const VO_Shape& iShape,
    const VO_FaceParts& iFaceParts,
    VO_Shape& oSubshape,
    unsigned int partIdx)
{
    oLine.resize(3);
    int dim = iShape.GetNbOfDim();

    Vec4f line;
    vector<unsigned int> linePoints;

    switch(partIdx)
    {
    case VO_FacePart::NOSTRIL:
        linePoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::NOSTRIL).GetIndexes();
        break;
    case VO_FacePart::MOUTHCORNERPOINTS:
        linePoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::MOUTHCORNERPOINTS).GetIndexes();
        break;
    case VO_FacePart::PITCHAXISLINEPOINTS:
        linePoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::PITCHAXISLINEPOINTS).GetIndexes();
        break;
    case VO_FacePart::EYECORNERPOINTS:
        linePoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::EYECORNERPOINTS).GetIndexes();
        break;
    case VO_FacePart::MIDLINEPOINTS:
    default:
        linePoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::EYECORNERPOINTS).GetIndexes();
        break;
    }
    
    oSubshape = iShape.GetSubShape(linePoints);

    // Explained by JIA Pei, some times, there is no linePoints, which means the specified parts are not in one of the database
    if(linePoints.size() >= 2 )
    {
        cv::fitLine( oSubshape.GetTheShape(), line, CV_DIST_L2, 0, 0.001, 0.001 );

        // Ax+By+C = 0
        oLine[0] = -line[1];
        oLine[1] = line[0];
        oLine[2] = line[1]*line[2]-line[0]*line[3];
    }
}


/**
 * @brief
 * @param       oPoint      output  point list
 * @param       iShape      input   shape
 * @param       iFaceParts  inut    faceparts
 * @param       ptType      input   point type
 * @return      void
 */
void VO_KeyPoint::CalcFaceKeyPoint( Point2f& oPoint,
                                    const VO_Shape& iShape,
                                    const VO_FaceParts& iFaceParts,
                                    unsigned int ptType)
{
    vector<unsigned int> facePartsPoints;
    VO_Shape subiShape;
    // Very very very very important.
    // Explained by JIA Pei.
    // "resize()" is just for resize;
    // it doesn't always set what's already inside the the vector to "0"
    // Therefore, clear() is a must before resize().

    switch(ptType)
    {
    case CENTEROFGRAVITY:
        if (iShape.GetNbOfPoints() > 0)
            oPoint = iShape.GetA2DPoint( VO_Shape::CENTER);
        break;
    case LEFTEYELEFTCORNER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTEYE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint(VO_Shape::LEFTMOST);
            }
        }
        break;
    case LEFTEYERIGHTCORNER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTEYE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint(VO_Shape::RIGHTMOST);
            }
        }
        break;
    case LEFTEYECENTER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTEYE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint( VO_Shape::CENTER);
            }
        }
        break;
    case RIGHTEYELEFTCORNER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTEYE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint(VO_Shape::LEFTMOST);
            }
        }
        break;
    case RIGHTEYERIGHTCORNER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTEYE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint(VO_Shape::RIGHTMOST);
            }
        }
        break;
    case RIGHTEYECENTER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTEYE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint( VO_Shape::CENTER);
            }
        }
        break;
    case NOSETIPKEY:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::NOSETIP).GetIndexes();    // Just one point
            if (facePartsPoints.size() == 1)
                oPoint = iShape.GetA2DPoint(facePartsPoints[0]);
        }
        break;
    case NOSTRILLEFT:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::NOSTRIL).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint(VO_Shape::LEFTMOST);
            }
        }
        break;
    case NOSTRILRIGHT:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::NOSTRIL).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint(VO_Shape::RIGHTMOST);
            }
        }
        break;
    case NOSECENTER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::NOSE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint( VO_Shape::CENTER);
            }
        }
        break;
    case MOUTHLEFTCORNER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPOUTERLINE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint(VO_Shape::LEFTMOST);
            }
        }
        break;
    case MOUTHRIGHTCORNER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPOUTERLINE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint(VO_Shape::RIGHTMOST);
            }
        }
        break;
    case MOUTHCENTER:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::LIPOUTERLINE).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
                subiShape = iShape.GetSubShape(facePartsPoints);
                oPoint = subiShape.GetA2DPoint( VO_Shape::CENTER);
            }
        }
        break;
    case EARLOBELEFT:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::LEFTEAR).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
            }
        }
        break;
    case EARLOBERIGHT:
        {
            facePartsPoints = iFaceParts.VO_GetOneFacePart(VO_FacePart::RIGHTEAR).GetIndexes();
            if (facePartsPoints.size() > 0)
            {
            }
        }
        break;
    }
}


//    string stri;
//    string keypointjpgstr, keypointtxtstr;
//    /** image patches for key points */
//    for(unsigned int i = 0; i < this->m_iNbOfKeyPoints; ++i)
//    {
//        ssi << i;
//        ssi >> stri;
//        if(stri.length() == 1)
//        {
//            keypointjpgstr = fn + "/keypoint0" + stri + ".jpg";
//            keypointtxtstr = fn + "/keypoint0" + stri + ".txt";
//        }
//        else
//        {
//            keypointjpgstr = fn + "/keypoint" + stri + ".jpg";
//            keypointtxtstr = fn + "/keypoint" + stri + ".txt";
//        }
//
//        this->m_vLocalImagePatchAroundKeyPoints[i] = imread(keypointjpgstr.c_str(), CV_LOAD_IMAGE_ANYCOLOR );
//
//        this->m_vGSLWaveletParams4KeyPoints[i] = gsl_matrix_alloc (this->m_vLocalImagePatchAroundKeyPoints[i].cols, this->m_vLocalImagePatchAroundKeyPoints[i].rows);
//        fp.open(keypointtxtstr.c_str (), ios::in);
//        fp >> this->m_vGSLWaveletParams4KeyPoints[i];
//        fp.close();fp.clear();
//
//        ssi.clear();
//    }
