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
* Create Date:      2010-02-06                                                                      *
* Modify Date:      2014-04-16                                                                      *
****************************************************************************************************/


#include <fstream>
#include <iostream>
#include "VO_DetectionDBIO.h"
#include "VO_ScanFilesInDir.h"


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Read all files from PUT face database 4 MVFD purpose
 * @param       dir_path    Input    --    The input directory
 * @param       faceComps   Output    --    face components
 * @return      void
*/
void CDetectionDBIO::ReadAllFilesFromPUT4MVFD(
    const std::string& dir_path,
    std::vector<VO_FaceCompPos>& faceComps)
{
    std::vector<std::string> labelFileNames = VO_ScanFilesInDir::ScanNSortXMLYMLsInDirectory ( dir_path );
    int NbOfFiles                           = labelFileNames.size();
    faceComps.resize(NbOfFiles);
    
    for ( unsigned int i = 0; i < NbOfFiles; i++ )
    {
        CDetectionDBIO::ReadOneFileFromPUT4MVFD(labelFileNames[i], faceComps[i]);
    }
}


/** input a FileNode to a cv::Rect */
//void operator >> (const YAML::Node& node, cv::Rect& rect) {
void operator >> (const cv::FileNode& node, cv::Rect& rect)
{
    node["x"] >> rect.x;
    node["y"] >> rect.y;
    node["width"] >> rect.width;
    node["height"] >> rect.height;
}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Read a single file from PUT face database 4 MVFD purpose
 * @param       filename        Input    --    The file name
 * @param       faceComps        Output    --    face components
 * @return      void
*/
void CDetectionDBIO::ReadOneFileFromPUT4MVFD(
    const std::string& filename,
    VO_FaceCompPos& oFaceComps)
{
    std::vector<cv::Rect> allRects;
    allRects.resize(5);

    //std::ifstream fin(filename.c_str());
    //YAML::Parser parser(fin);
    //YAML::Node doc;
    //parser.GetNextDocument(doc);
    
    //doc["Face"] >> oFaceComps.m_rectObject;
    //// Explained by JIA Pei. for PUT database, lefteye and righteye should be reversed.
    ////doc["Left eye"] >> oFaceComps.m_rectLeftEye;
    ////doc["Right eye"] >> oFaceComps.m_rectRightEye;
    //doc["Left eye"] >> oFaceComps.m_rectRightEye;
    //doc["Right eye"] >> oFaceComps.m_rectLeftEye;
    //doc["Mouth"] >> oFaceComps.m_rectMouth;
    //doc["Nose"] >> oFaceComps.m_rectNose;
    
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    cv::FileNode node = fs["Face"];

    node >> oFaceComps.m_rectObject;
    // Explained by JIA Pei. for PUT database, lefteye and righteye should be reversed.
    //fs["Left eye"] >> oFaceComps.m_rectLeftEye;
    //fs["Right eye"] >> oFaceComps.m_rectRightEye;
    node = fs["Left eye"];
    node >> oFaceComps.m_rectRightEye;
    node = fs["Right eye"];
    node >> oFaceComps.m_rectLeftEye;
    node = fs["Mouth"];
    node >> oFaceComps.m_rectMouth;
    node = fs["Nose"];
    node >> oFaceComps.m_rectNose;
}
    
    
/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Read all files from CAS-PEAL-R1 face databse for MVFD training
 * @param       dir_path    Input   --  The input directory
 * @param       faceComps   Output  --  face components
 * @return      void
*/
void CDetectionDBIO::ReadAllFilesFromCASPEALR14MVFD(
    const std::string& dir_path,
    std::vector< std::vector<VO_FaceCompPos> >& faceComps)
{
    std::vector<std::string> labelFileNames   = VO_ScanFilesInDir::ScanNSortTextFilesInDirectory ( dir_path );
    int NbOfFiles                   = labelFileNames.size();
    faceComps.resize(NbOfFiles);

    // bottom, middel, up -- 3
    // -67,-45,-22,0,22,45,67 -- 7
    // -45,-30,-15,0,15,30,45 -- 7
    for ( unsigned int i = 0; i < NbOfFiles; i++ )
    {
        CDetectionDBIO::ReadOneFileFromCASPEALR14MVFD(labelFileNames[i], faceComps[i]);
    }
}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Read a single file from CAS-PEAL-R1 face database for MVFD training
 * @note        a single faceFP file from CAS-PEAL-R1 contains all information of all 21 images for one individual
 * @param       filename    Input    --    The input file name
 * @param       faceComps   Output    --    face components corresponding to 1 person. should be a std::vector of 21
 * @return      void
*/
void CDetectionDBIO::ReadOneFileFromCASPEALR14MVFD(
    const std::string& filename,
    std::vector<VO_FaceCompPos>& oFaceComps)
{
    int dmu, degrees, idx;
    cv::Point leftEyeCenter, rightEyeCenter;
    int rightbottomx, rightbottomy;
    cv::Rect leftEyeRect, rightEyeRect, faceRect, noseRect, mouthRect;

    std::string fn;
    std::ifstream ifs;
    ifs.open(filename.c_str(), std::ifstream::in);

    oFaceComps.resize(21);
    for(int i = 0; i < 21; i++)
    {
        ifs >> fn >> leftEyeCenter.x >> leftEyeCenter.y 
            >> rightEyeCenter.x >> rightEyeCenter.y;

        CDetectionDBIO::AnalyzeFileNameFromCASPEALR14MVFD(filename, dmu, degrees);
        CDetectionDBIO::EstimateRects4MVFD( leftEyeCenter,
                                            rightEyeCenter,
                                            dmu,
                                            degrees,
                                            faceRect,
                                            leftEyeRect,
                                            rightEyeRect,
                                            mouthRect,
                                            noseRect);

        idx = dmu*7+(degrees/15+3);
        oFaceComps[idx].SetImageFileName(filename);
        oFaceComps[idx].SetLeftEyeRect(leftEyeRect);
        oFaceComps[idx].SetRightEyeRect(rightEyeRect);
        oFaceComps[idx].SetObjectRect(faceRect);
    }

    ifs.close();
}


/**
 * @author      JIA Pei
 * @version     2010-04-07
 * @brief       Read degree information from the file name
 * @param       filename    Input    --  filename hides the degrees
 * @param       dmu         Output   --  face directions, down, middle or up
 * @param       degrees     Output   --  face degrees, read from filename
 * @return      void
*/
void CDetectionDBIO::AnalyzeFileNameFromCASPEALR14MVFD(
    const std::string& filename,
    int& dmu,
    int& degrees)
{
    std::string s_dmu = filename.substr(17, 2);
    if(s_dmu == "PD") dmu = DOWN;
    else if(s_dmu == "PM") dmu = MIDDLE;
    else if(s_dmu == "PU") dmu = UP;

    std::string s_degrees = filename.substr(20, 2);
    std::stringstream ss;
    ss << s_degrees;
    ss >> degrees;
}


/**
 * @author      JIA Pei
 * @version     2010-04-07
 * @brief       Estimate face rectangle using a simple 3D face model
 * @param       leftEyeCenter   Input   --   left eye center
 * @param       rightEyeCenter  Input   --   right eye center
 * @param       dmu             Input   --   down, middle, up, supposing down -30 degrees, middle 0 degrees, up +30 degrees
 * @param       degrees         Input   --   face degrees, read from filename
 * @param       faceRect        Output  --   face rectangle
 * @param       leftEyeRect     Output  --   left eye rectangle
 * @param       rightEyeRect    Output  --   right eye rectangle
 * @param       mouthRect       Output  --   mouth rectangle
 * @param       noseRect        Output  --   nose rectangle
 * @return      void
*/
void CDetectionDBIO::EstimateRects4MVFD(
    const cv::Point& leftEyeCenter,
    const cv::Point& rightEyeCenter,
    int dmu,
    int degrees,
    cv::Rect& faceRect,
    cv::Rect& leftEyeRect,
    cv::Rect& rightEyeRect,
    cv::Rect& mouthRect,
    cv::Rect& noseRect)
{
    switch( dmu*7+(degrees/15+3) )
    {
        case 0:
        {
            
        }
        break;
        case 1:
        {
            
        }
        break;
        case 2:
        {
            
        }
        break;
        case 3:
        {
            
        }
        break;
        case 4:
        {
            
        }
        break;
        case 5:
        {
            
        }
        break;
        case 6:
        {
            
        }
        break;
        case 7:
        {
            
        }
        break;
        case 8:
        {
            
        }
        break;
        case 9:
        {
            
        }
        break;
        case 10:
        {
            
        }
        break;
        case 11:
        {
            leftEyeRect.x = leftEyeCenter.x - 16;
            leftEyeRect.y = leftEyeCenter.y - 16;
            leftEyeRect.width = 32;
            leftEyeRect.height = 32;
            rightEyeRect.x = rightEyeCenter.x - 16;
            rightEyeRect.y = rightEyeCenter.y - 16;
            rightEyeRect.width = 32;
            rightEyeRect.height = 32;
        }
        break;
        case 12:
        {
            
        }
        break;
        case 13:
        {
            
        }
        break;
        case 14:
        {
            
        }
        break;
        case 15:
        {
            
        }
        break;
        case 16:
        {
            
        }
        break;
        case 17:
        {
            
        }
        break;
        case 18:
        {
            
        }
        break;
        case 19:
        {
            
        }
        break;
        case 20:
        {
            
        }
        break;
    }
}


/**
 * @author      JIA Pei
 * @version     2010-04-07
 * @brief       Load face components from training files
 * @param       allFaceCompFiles4Training   Input  --  file names of all training face files
 * @param       database   Input   --  database, including PUT and CASPEALR1
 * @param       faceComps  Output  --  a std::vector of all face components from all files
 * @return      void
*/
void CDetectionDBIO::VO_LoadFaceCompTrainingData(
    const std::vector<std::string>& allFaceCompFiles4Training,
    unsigned int database,
    std::vector<VO_FaceCompPos>& faceComps)
{
    faceComps.clear();
    
    // Load face database
    switch ( database )
    {
        case CASPEALR1:
        {
            int NbOfFiles   = allFaceCompFiles4Training.size();
            std::vector< std::vector<VO_FaceCompPos> > tempFaceComps;
            tempFaceComps.resize(NbOfFiles);
            
            for ( unsigned int i = 0; i < NbOfFiles; i++ )
            {
                CDetectionDBIO::ReadOneFileFromCASPEALR14MVFD(allFaceCompFiles4Training[i], tempFaceComps[i]);
                for(unsigned int j = 0; j < tempFaceComps[i].size(); j++)
                {
                    faceComps.push_back(tempFaceComps[i][j]);
                }
            }
        }
        break;
        case PUT:
        default:
        {
            int NbOfFiles   = allFaceCompFiles4Training.size();
            faceComps.resize(NbOfFiles);
            
            for ( unsigned int i = 0; i < NbOfFiles; i++ )
            {
                CDetectionDBIO::ReadOneFileFromPUT4MVFD(allFaceCompFiles4Training[i], faceComps[i]);
            }
        }
        break;
    }
}


/**
 * @author      JIA Pei
 * @version     2010-04-07
 * @brief       Load object rectangles from training files
 * @param       allFaceCompFiles4Training   Input   --  file names of all training face files
 * @param       database    Input   --  database, including PUT and CASPEALR1
 * @param       objRects    Output  --  a std::vector of all face components from all files
 * @return      void
*/
void CDetectionDBIO::VO_LoadFaceCompTrainingData(
    const std::vector<std::string>& allFaceCompFiles4Training,
    unsigned int database,
    std::vector<cv::Rect>& objRects)
{
    std::vector<VO_FaceCompPos> faceComps;
    CDetectionDBIO::VO_LoadFaceCompTrainingData(allFaceCompFiles4Training,
                                                database,
                                                faceComps);
    objRects.clear();
    unsigned int NbOfObjRects = faceComps.size();
    
    for(unsigned int i = 0; i < NbOfObjRects; i++)
    {
        objRects.push_back( faceComps[i].GetObjectRect() );
    }
}

