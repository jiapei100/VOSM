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

#include <sstream>
#include <cstring>
#include <iostream>
#include <fstream>

#include "VO_ScanFilesInDir.h"



/**
 * @author      JIA Pei
 * @version     2007-08-08
 * @brief       Scan a directory and sort all files with a specified extension
 * @param       dir_path            input parameter, path to read from
 * @param       file_extension      input parameter, file extension to search for
 * @param       files               output parameter, file names found without any path
 * @return      bool                fail to scan or not
 * @note        http://www.boost.org/libs/filesystem/doc/index.htm
*/
bool VO_ScanFilesInDir::ScanNSortDirectory( const std::string& dir_path,
                                            const std::string& file_extension, 
                                            std::vector<std::string>& files)
{
    boost::filesystem::path tempp(dir_path);
    
    if ( !exists( tempp ) )
    {
        return false;
    }

    boost::filesystem::directory_iterator end_itr;

    for ( boost::filesystem::directory_iterator itr(tempp); itr != end_itr; ++itr )
    {
        if ( boost::filesystem::is_directory(itr->status()) )
        {
            VO_ScanFilesInDir::ScanNSortDirectory(itr->path().string(), file_extension, files);
        }
        else if ( boost::filesystem::extension( itr->path() ) == file_extension )
        {
            files.push_back( itr->path().string() );
        }
    }
    
    // sort the filenames
    if(files.size() > 0)
    {
        qsort( (void *)&(files[0]), (size_t)files.size(), sizeof(std::string), str_compare );
    }

    return true;
}


/**
 * @author      JIA Pei
 * @version     2007-08-08
 * @brief       Scan a directory and sorts all file in format of .pts or .asf
 * @param       dir_path                    input parameter, path to read from
 * @return      std::vector<std::string>    A vector of all scanned file names
*/
std::vector<std::string> VO_ScanFilesInDir::ScanNSortAnnotationInDirectory(const std::string& dir_path)
{
    std::vector<std::string> annotationALL;
    std::vector< std::vector<std::string> > annotations;
    annotations.resize(4);  // 3 types, pts, asf, obj, wrl    // Here, look on Lightwave .obj and VRML .wrl as annotations
    for(unsigned int i = 0; i < annotations.size(); i++)
    {
        annotations[i].resize(0);
    }

    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".pts", annotations[0]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".asf", annotations[1]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".obj", annotations[2]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".wrl", annotations[3]);

    for(unsigned int i = 0; i < annotations.size(); i++)
    {
        for(unsigned int j = 0; j < annotations[i].size(); j++)
        {
            annotationALL.push_back(annotations[i][j]);
        }
    }

    // sort the filenames
    if(annotationALL.size() > 0)
    {
        qsort( (void *)&(annotationALL[0]), (size_t)annotationALL.size(), sizeof(std::string), str_compare );
    }

    return annotationALL;
}


/**
 * @author      JIA Pei
 * @version     2007-08-08
 * @brief       Scan a directory and sort all files in format of .jpg .bmp .ppm .pgm .png .gif .tif
 * @param       dir_path                        input parameter, path to read from
 * @return      std::vector<std::string>        A vector of all scanned file names
*/
std::vector<std::string> VO_ScanFilesInDir::ScanNSortImagesInDirectory(const std::string& dir_path)
{
    std::vector<std::string> imgALL;
    std::vector< std::vector<std::string> > imgs;
    imgs.resize(7);
    for(unsigned int i = 0; i < imgs.size(); i++)
    {
        imgs[i].resize(0);
    }

    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".jpg", imgs[0]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".bmp", imgs[1]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".ppm", imgs[2]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".pgm", imgs[3]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".png", imgs[4]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".gif", imgs[5]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".tif", imgs[6]);

    for(unsigned int i = 0; i < imgs.size(); i++)
    {
        for(unsigned int j = 0; j < imgs[i].size(); j++)
        {
            imgALL.push_back(imgs[i][j]);
        }
    }

    // sort the filenames
    if(imgALL.size() > 0)
    {
        qsort( (void *)&(imgALL[0]), (size_t)imgALL.size(), sizeof(std::string), str_compare );
    }

    return imgALL;
}


/**
 * @author      JIA Pei
 * @version     2010-03-13
 * @brief       Scan a directory and sort all files in format of .xml, .yml, .yaml
 * @param       dir_path                        input parameter, path to read from
 * @return      std::vector<std::string>        A std::vector of all scanned file names
*/
std::vector<std::string> VO_ScanFilesInDir::ScanNSortXMLYMLsInDirectory(const std::string& dir_path)
{
    std::vector<std::string> mlALL;
    std::vector< std::vector<std::string> > mls;
    mls.resize(3);
    for(unsigned int i = 0; i < mls.size(); i++)
    {
        mls[i].resize(0);
    }

    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".xml", mls[0]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".yml", mls[1]);
    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".yaml", mls[2]);

    for(unsigned int i = 0; i < mls.size(); i++)
    {
        for(unsigned int j = 0; j < mls[i].size(); j++)
        {
            mlALL.push_back(mls[i][j]);
        }
    }

    // sort the filenames
    if(mlALL.size() > 0)
    {
        qsort( (void *)&(mlALL[0]), (size_t)mlALL.size(), sizeof(std::string), str_compare );
    }

    return mlALL;
}


/**
 * @author      JIA Pei
 * @version     2010-03-13
 * @brief       Scan a directory and sort all files in format of .txt
 * @param       dir_path                        input parameter, path to read from
 * @return      std::vector<std::string>        A vector of all scanned file names
*/
std::vector<std::string> VO_ScanFilesInDir::ScanNSortTextFilesInDirectory(const std::string& dir_path)
{
    std::vector<std::string> textALL;
    std::vector< std::vector<std::string> > texts;
    texts.resize(3);
    for(unsigned int i = 0; i < texts.size(); i++)
    {
        texts[i].resize(0);
    }

    VO_ScanFilesInDir::ScanNSortDirectory( dir_path, ".txt", texts[0]);

    for(unsigned int i = 0; i < texts.size(); i++)
    {
        for(unsigned int j = 0; j < texts[i].size(); j++)
        {
            textALL.push_back(texts[i][j]);
        }
    }

    // sort the filenames
    if(textALL.size() > 0)
    {
        qsort( (void *)&(textALL[0]), (size_t)textALL.size(), sizeof(std::string), str_compare );
    }

    return textALL;
}

