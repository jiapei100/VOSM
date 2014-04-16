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


#include "VO_AnnotationDBIO.h"


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Read a file and obtain all annotation data in VO_Shape
 * @param       filename    input parameter, 
 *                          which .asf annotation file to read
 * @param       oAAMShape   output parameter, 
 *                          save annotation data to AAM shape data structure
*/
void CAnnotationDBIO::ReadASF(  const string &filename,
                                VO_Shape& oAAMShape )
{
    oAAMShape.SetAnnotationFileName(filename);

    fstream fp;
    fp.open(filename.c_str (), ios::in);

    stringstream ss;
    string temp;
    float tempFloat = 0.0f;

    // Just for the specific .asf
    for(unsigned int i = 0; i < 10; i++)
        //fp >> temp;
        getline(fp, temp);

    unsigned int NbOfPoints = atoi(temp.c_str ());
    oAAMShape.Resize(2, NbOfPoints);

    // Just for the specific .asf
    for(unsigned int i = 0; i < 6; i++)
        //fp >> temp;
        getline(fp, temp);

    for (unsigned int i = 0; i < NbOfPoints; i++)
    {
        fp >> temp >> temp >> temp;
        // In DTU IMM , x means rows from left to right
        ss << temp;
        ss >> tempFloat;
        ss.clear();
        oAAMShape(0, i) = tempFloat;
        fp >> temp;
        // In DTU IMM , y means cols from top to bottom
        ss << temp;
        ss >> tempFloat;
        ss.clear();
        //fp >> temp;
        getline(fp, temp);
        // In sum, topleft is (0,0), right bottom is (640,480)
        oAAMShape(1, i) = tempFloat;
    }

    // Just for the specific .asf
    for(unsigned int i = 0; i < 5; i++)
        fp >> temp;

    fp.close ();

}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Read a file and obtain all annotation data in VO_Shape
 * @param       filename    input parameter, which .pts annotation file to read
 * @param       oAAMShape   output parameter, save annotation data to AAM shape data structure
*/
void CAnnotationDBIO::ReadPTS(  const string &filename,
                                VO_Shape& oAAMShape)
{
    oAAMShape.SetAnnotationFileName(filename);

    fstream fp;
    fp.open(filename.c_str (), ios::in);

    string temp, oneLine;
    stringstream ss;
    float tempFloat = 0.0f;

    do
    {
        fp >> temp;
    }while (temp!="n_points:");


    fp >> temp;
    ss << temp;
    unsigned int NbOfPoints;
    ss >> NbOfPoints;
    ss.clear();
    oAAMShape.Resize(2, NbOfPoints);

    fp >> temp;

    for (unsigned int i = 0; i < NbOfPoints; i++)
    {
        fp >> temp;
        // x refers to a row from left to right
        ss << temp;
        ss >> tempFloat;
        ss.clear();
        oAAMShape(0, i) = tempFloat;
        fp >> temp;
        // y refers to a col from top to bottom
        ss << temp;
        ss >> tempFloat;
        ss.clear();
        // In sum, topleft is (0,0), right bottom is (720,576)
        oAAMShape(1, i) = tempFloat;
    }

    fp.close ();fp.clear();
}


/**
 * @author         JIA Pei
 * @version        2010-02-07
 * @brief          Read a file and obtain all annotation data in VO_Shape
 * @param          filename        input parameter, which .asf annotation file to read
 * @param          oAAMShape       output parameter, save annotation data to AAM shape data structure
*/
void CAnnotationDBIO::ReadOBJ(  const string &filename,
                                VO_Shape& oAAMShape )
{
    oAAMShape.SetAnnotationFileName(filename);

    fstream fp;
    fp.open(filename.c_str (), ios::in);

    stringstream ss;
    string temp;
    float tempFloat = 0.0f;

    // Just for the specific .obj produced by Freiburg
    for(unsigned int i = 0; i < 4; i++)
        fp >> temp;

    fp >> temp >> temp;
    unsigned int NbOfPoints = atoi(temp.c_str ());
    fp >> temp;

    for (unsigned int i = 0; i < NbOfPoints; i++)
    {
        fp >> temp;     // v

        for(unsigned int j = 0; j < 3; j++)
        {
            fp >> temp;
            ss << temp;
            ss >> tempFloat;
            ss.clear();
            //oAAMShape.InsertShape(tempFloat);
        }
    }

    fp.close ();

}


/**
 * @author         JIA Pei
 * @version        2010-02-07
 * @brief          Read a file and obtain all annotation data in VO_Shape
 * @param          filename        input parameter, which .pts annotation file to read
 * @param          oAAMShape       output parameter, save annotation data to AAM shape data structure
*/
void CAnnotationDBIO::ReadWRL(  const string &filename,
                                VO_Shape& oAAMShape)
{
    oAAMShape.SetAnnotationFileName(filename);

    fstream fp;
    fp.open(filename.c_str (), ios::in);

    string temp;
    stringstream ss;
    Mat_<float> translation(3, 1);
    float tempFloat = 0.0f;

    // Just for the specific .wrl produced by XM2VTS3D
    // 2 children of the scene, find the 2nd translation
    do
    {
        getline(fp, temp);
    }while (temp.find("Transform") == string::npos);
    do
    {
        getline(fp, temp);
    }while (temp.find("Transform") == string::npos);
    fp >> temp;
    fp >> translation;

    do
    {
        getline(fp, temp);
    }while (temp.find("point    [ 0 0 0,") == string::npos);

    do
    {
        for(unsigned int i = 0; i < 3; i++)
        {
            fp >> tempFloat;
            //oAAMShape.InsertShape( tempFloat + translation[i]);
            //oAAMShape.InsertShape( tempFloat);
        }
        fp >> temp;
    }while (temp != "]");

    fp.close ();
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      Write all annotation data in VO_Shape to a file
 * @param      filename     output parameter, which .pts annotation file to write
 * @param      iAAMShape    input parameter, save annotation data from AAM shape data structure
*/
void CAnnotationDBIO::WriteASF( const string &filename,
                                const VO_Shape& iAAMShape)
{

}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Write all annotation data in VO_Shape to a file
 * @param       filename    output parameter, which .pts annotation file to write
 * @param       iAAMShape   input parameter, save annotation data from AAM shape data structure
*/
void CAnnotationDBIO::WritePTS( const string &filename,
                                const VO_Shape& iAAMShape)
{
    fstream fp;
    fp.open(filename.c_str (), ios::out);

    string temp, oneLine;
    stringstream ss;
    float tempFloat = 0.0f;
    unsigned int NbOfPoints = iAAMShape.GetNbOfPoints();

    fp << "version: 1" << endl
    << "n_points: " << NbOfPoints << endl
    << "{" << endl;

    for (unsigned int i = 0; i < NbOfPoints; i++)
    {
        fp << iAAMShape.GetA2DPoint(i).x << " " << iAAMShape.GetA2DPoint(i).y << endl;
    }

    fp << "}" << endl << endl;

    fp.close ();
}



/**
 * @author         JIA Pei
 * @version        2010-02-07
 * @brief          Write all annotation data in VO_Shape to a file
 * @param          filename        output parameter, which .pts annotation file to write
 * @param          iAAMShape       input parameter, save annotation data from AAM shape data structure
*/
void CAnnotationDBIO::WriteOBJ( const string &filename,
                                const VO_Shape& iAAMShape)
{

}


/**
 * @author         JIA Pei
 * @version        2010-02-07
 * @brief          Write all annotation data in VO_Shape to a file
 * @param          filename        output parameter, which .pts annotation file to write
 * @param          iAAMShape       input parameter, save annotation data from AAM shape data structure
*/
void CAnnotationDBIO::WriteWRL( const string &filename,
                                const VO_Shape& iAAMShape)
{

}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Load Training data for shape model
 * @param       allLandmarkFiles4Training        Input - all landmark files
  * @param      database                        Input - which database is it?
 * @param       oShapes         Output - the loaded shape
 * @return      void
*/
void CAnnotationDBIO::VO_LoadShapeTrainingData(
    const vector<string>& allLandmarkFiles4Training,
    unsigned int database,
    vector<VO_Shape>& oShapes )
{
    oShapes.clear();

    // Load the annotated information
    switch ( database )
    {
        case BFM3D:
        case USF3D:
        break;
        case XM2VTS3D:
        break;
        case AGING:
        case BIOID:
        case XM2VTS:
        case FRANCK:
        case EMOUNT:
        case JIAPEI:
        {
            // Read all PTS file data into shps
            for ( unsigned int i = 0; i < allLandmarkFiles4Training.size(); i++ )
            {
                VO_Shape tempAAMShape(2);
                CAnnotationDBIO::ReadPTS (
                    allLandmarkFiles4Training[i],
                    tempAAMShape );
                oShapes.push_back ( tempAAMShape );
            }
        }
        break;
        case IMM:
        default:
        {
            // Read all ASF file data into shps and scale back to the original size
            for ( unsigned int i = 0; i < allLandmarkFiles4Training.size(); i++ )
            {
                Mat_<float> scale = Mat_<float>::zeros(2, 1);
                scale(0, 0) = 640;
                scale(1, 0) = 480;
                VO_Shape tempAAMShape(2);
                CAnnotationDBIO::ReadASF (
                    allLandmarkFiles4Training[i],
                    tempAAMShape );
                tempAAMShape.Scale ( scale );
                oShapes.push_back ( tempAAMShape );
            }
        }
        break;
    }
}


/**
 * @author      JIA Pei
 * @version     2010-02-07
 * @brief       Load Training data for shape model
 * @param       allLandmarkFiles4Training    Input - all landmark files
 * @return      void
*/
void CAnnotationDBIO::VO_LoadShapeTrainingData(
    const vector<string>& allLandmarkFiles4Training,
    vector<VO_Shape>& oShapes)
{
    unsigned int NbOfAnnotations = allLandmarkFiles4Training.size();
    string fileType = allLandmarkFiles4Training[0].substr
        (allLandmarkFiles4Training[0].find_last_of("."), 3);
    if(fileType == "pts")
    {
        // Read all PTS file data into shps
        for ( unsigned int i = 0; i < NbOfAnnotations; i++ )
        {
            VO_Shape tempAAMShape(2);
            CAnnotationDBIO::ReadPTS ( allLandmarkFiles4Training[i], tempAAMShape );
            oShapes.push_back ( tempAAMShape );
        }
    }
    else if(fileType == "asf")
    {
        // Read all ASF file data into shps and scale back to the original size
        for ( unsigned int i = 0; i < NbOfAnnotations; i++ )
        {
            Mat_<float> scale = Mat_<float>::zeros(2, 1);
            scale(0, 0) = 640;
            scale(1, 0) = 480;
            VO_Shape tempAAMShape(2);
            CAnnotationDBIO::ReadASF ( allLandmarkFiles4Training[i], tempAAMShape );
            tempAAMShape.Scale ( scale );
            oShapes.push_back ( tempAAMShape );
        }
    }
}
