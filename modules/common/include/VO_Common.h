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
* Create Date:      2010-11-24                                                                      *
* Modify Date:      2014-04-15                                                                      *
****************************************************************************************************/


#ifndef __VO_COMMON_H__
#define __VO_COMMON_H__


#include "stdio.h"
#include "stdlib.h"
#include "float.h"
#include <climits>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <ctime>

//#include <gsl/gsl_matrix.h>
//#include <gsl/gsl_linalg.h>



#define INF											DBL_MAX

#define ROW                                         1
#define COL                                         2


//////////////////////////////////////////////////////////////////////////
#define AVNONE										0
#define AVAUDIO										1
#define AVVIDEO										2
#define AVAUDIOVIDEO								3

#define SYNCEVEN									1
#define SYNCTIMESTAMP								2

#define INTER_NONSYNC								1
#define INTER_SYNCAUDIO								2
#define INTER_SYNCVIDEO								3

#define	AUDIO_MFCC									1
#define	AUDIO_RASTA									2
#define	AUDIO_PLP									3
#define	AUDIO_TECC									4					// Teager Energy


#define SR_LINEAR									1

#define MFCC_FRAMEOVERLAPCUT 						1
#define MFCC_FRAMEOVERLAPACCUMULATE					2

#define VAD_FRAMEENERGYFREQUENCY                    1
#define VAD_SPECTRALENTROPYWITHENERGY				2
#define VAD_AUTOCORRELATION							3
#define VAD_WAVELET									4
#define	VAD_SPEEX									10

#define DTW_FULL									1
#define DTW_GC_SakoeChibaBand						1
#define DTW_GC_ItakuraParallelogram					2

#define LB_KEOGH									1
#define LB_YI										2
#define LB_KIM										3
//////////////////////////////////////////////////////////////////////////


#define CLAMP										1
#define STRETCH										2

// For detected face or tracking face constrain
#define FACESMALLESTSIZE                            80		// for both detection and tracking
#define FACEBIGGESTSIZE                             240		// for both detection and tracking
#define FACEPARTSMALLESTSIZE                        16
#define FACEPARTBIGGESTSIZE                         128
#define FRAMEEDGE									5		// if too close the image boundary, look on as lost

#define AAMADABOOSTDOWNPERCENTAGE                   0.2

#define FACEHEIGHT2WIDTH                            1.1

#define SHAPE                                       1
#define TEXTURE                                     2

// a) Single image b) image sequence c) webcam d) video
#define NOTHINGLOADED								0
#define SINGLEIMAGE									1
#define IMAGESEQUENCE								2
#define CAM                                         3
#define AVI                                         4


#define HORIZONTAL                                  1
#define VERTICAL                                    2
#define ANY                                         3

#define GRAYCHANNELS                                1
#define COLORCHANNELS                               3   // R G B 3 channels

#define DIRECTMAP                                   1
#define LINEARIZEMAP                                2


// video show type
#define ORIGINAL                                    0
#define DETECTED                                    1
#define FIT                                         2

#define MEAN0NORM1                                  1
#define VARY01                                      2


#define STRING_MAXSIZE                              1024

enum { 
	Audio_LChannel,
	Audio_RChannel,
	Audio_BChannel
};



/** local (static) compare function for the qsort() call */
static int str_compare( const void *arg1, const void *arg2 )
{
    return strcmp ( ( * ( std::string* ) arg1 ).c_str (), ( * ( std::string* ) arg2 ).c_str () );
}


/** simple clamp function */
template <class T1, class T2>
static T2 clamp ( T1 input, T2 low, T2 up )
{
    return ( input < low ? low : ( input > up ? up : ( T2 ) input ) );
}


/** vector element-wise summation */
template <class T, class T1>
static std::vector<T> operator+ ( const std::vector<T>& vect1, const std::vector<T1>& vect2 )
{
    std::vector<T> res;
    unsigned int size = vect1.size() < vect2.size() ? vect1.size() : vect2.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
        res[i] = vect1[i] + vect2[i];
    return res;
}


/** every element of a vector add the same value */
template <class T, class T1>
static std::vector<T> operator+ ( const std::vector<T>& vect1, T1 value )
{
    std::vector<T> res;
    unsigned int size = vect1.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
        res[i] = vect1[i] + value;
    return res;
}


/** vector element-wise summation */
template <class T, class T1>
static std::vector<T> operator += ( std::vector<T>& vect1, const std::vector<T1>& vect2 )
{
    unsigned int size = vect1.size() < vect2.size() ? vect1.size() : vect2.size();
    for ( unsigned int i = 0; i < size; ++i )
        vect1[i] += vect2[i];
    return vect1;
}


/** every element of a vector add the same value */
template <class T, class T1>
static std::vector<T> operator += ( std::vector<T>& vect1, T1 value )
{
    unsigned int size = vect1.size();
    for ( unsigned int i = 0; i < size; ++i )
        vect1[i] += value;
    return vect1;
}


/** reverse sign */
template <class T>
static std::vector<T> operator- ( const std::vector<T>& vect )
{
    std::vector<T> res;
    unsigned int size = vect.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
        res[i] = -vect[i];
    return res;
}


/** vector element-wise subtraction */
template <class T, class T1>
static std::vector<T> operator- ( const std::vector<T>& vect1, const std::vector<T1>& vect2 )
{
    std::vector<T> res;
    unsigned int size = vect1.size() < vect2.size() ? vect1.size() : vect2.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
        res[i] = vect1[i] - vect2[i];
    return res;
}


/** every element of a vector subtract the same value */
template <class T, class T1>
static std::vector<T> operator- ( const std::vector<T>& vect1, T1 value )
{
    std::vector<T> res;
    unsigned int size = vect1.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
        res[i] = vect1[i] - value;
    return res;
}


/** vector element-wise subtraction */
template <class T, class T1>
static std::vector<T> operator -= ( std::vector<T>& vect1, const std::vector<T1>& vect2 )
{
    unsigned int size = vect1.size() < vect2.size() ? vect1.size() : vect2.size();
    for ( unsigned int i = 0; i < size; ++i )
        vect1[i] -= vect2[i];
    return vect1;
}


/** every element of a vector subtract the same value */
template <class T, class T1>
static std::vector<T> operator -= ( std::vector<T>& vect1, T1 value )
{
    unsigned int size = vect1.size();
    for ( unsigned int i = 0; i < size; ++i )
        vect1[i] -= value;
    return vect1;
}


/** vector element-wise multiplication */
template <class T, class T1>
static std::vector<T> operator* ( const std::vector<T>& vect1, const std::vector<T1>& vect2 )
{
    std::vector<T> res;
    unsigned int size = vect1.size() < vect2.size() ? vect1.size() : vect2.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
        res[i] = vect1[i] * vect2[i];
    return res;
}


/** every element of a vector multiply the same value */
template <class T, class T1>
static std::vector<T> operator* ( const std::vector<T>& vect1, T1 value )
{
    std::vector<T> res;
    unsigned int size = vect1.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
        res[i] = vect1[i] * value;
    return res;
}


/** vector element-wise multiplication */
template <class T, class T1>
static std::vector<T> operator *= ( std::vector<T>& vect1, const std::vector<T1>& vect2 )
{
    unsigned int size = vect1.size() < vect2.size() ? vect1.size() : vect2.size();
    for ( unsigned int i = 0; i < size; ++i )
        vect1[i] *= vect2[i];
    return vect1;
}


/** every element of a vector multiply the same value */
template <class T, class T1>
static std::vector<T> operator *= ( std::vector<T>& vect1, T1 value )
{
    unsigned int size = vect1.size();
    for ( unsigned int i = 0; i < size; ++i )
        vect1[i] *= value;
    return vect1;
}


/** vector element-wise division */
template <class T, class T1>
static std::vector<T> operator/ ( const std::vector<T>& vect1, const std::vector<T1>& vect2 )
{
    std::vector<T> res;
    unsigned int size = vect1.size() < vect2.size() ? vect1.size() : vect2.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
    {
        if (fabs((float)vect2[i]) < FLT_MIN)
        {
            std::cerr << "divide by 0 ! " << std::endl;
            exit(EXIT_FAILURE);
        }
        res[i] = vect1[i] / vect2[i];
    }
    return res;
}


/** every element of a vector multiply the same value */
template <class T, class T1>
static std::vector<T> operator/ ( const std::vector<T>& vect1, T1 value )
{
    if (fabs((float)value) < FLT_MIN)
    {
        std::cerr << "divide by 0 ! " << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<T> res;
    unsigned int size = vect1.size();
    res.resize ( size );
    for ( unsigned int i = 0; i < size; ++i )
        res[i] = vect1[i] / value;
    return res;
}


/** vector element-wise division */
template <class T, class T1>
static std::vector<T> operator /= ( std::vector<T>& vect1, const std::vector<T1>& vect2 )
{
    unsigned int size = vect1.size() < vect2.size() ? vect1.size() : vect2.size();
    for ( unsigned int i = 0; i < size; ++i )
    {
        if (fabs((float)vect2[i]) < FLT_MIN)
        {
            std::cerr << "divide by 0 ! " << std::endl;
            exit(EXIT_FAILURE);
        }
        vect1[i] /= vect2[i];
    }
    return vect1;
}


/** every element of a vector multiply the same value */
template <class T, class T1>
static std::vector<T> operator /= ( std::vector<T>& vect1, T1 value )
{
    if (fabs((float)value) < FLT_MIN)
    {
        std::cerr << "divide by 0 ! " << std::endl;
        exit(EXIT_FAILURE);
    }
    unsigned int size = vect1.size();
    for ( unsigned int i = 0; i < size; ++i )
        vect1[i] /= value;
    return vect1;
}


///** output gsl_matrix */
//static std::ostream& operator<< (std::ostream &os, const gsl_matrix* gslm)
//{
//    for (unsigned int i = 0; i < gslm->size1; ++i)
//    {
//        for(unsigned int j = 0; j < gslm->size2; ++j)
//        {
//            os << gsl_matrix_get (gslm, i, j) << " ";
//        }
//        os << std::endl;
//    }
//    return os;
//}
//
//
///** input gsl_matrix */
//static std::istream& operator>> ( std::istream &is, gsl_matrix* gslm)
//{
//    for ( unsigned int i = 0; i < gslm->size1; ++i )
//    {
//        for ( unsigned int j = 0; j < gslm->size2; ++j )
//        {
//            is >> gslm->data[i * gslm->tda + j];
//        }
//    }
//    return is;
//}


template <class T>
static std::ostream& operator<< ( std::ostream &os, const std::vector<T>& vec )
{
    unsigned int size = vec.size();
    for ( unsigned int i = 0; i < size; i++ )
    {
        os << vec[i] << std::endl;
    }
    return os;
}


template <class T>
static std::istream& operator>> ( std::istream &is, std::vector<T>& vec )
{
    unsigned int size = vec.size();
    for ( unsigned int i = 0; i < size; i++ )
    {
        is >> vec[i];
    }
    return is;
}


template <class T>
static std::ostream& operator<< ( std::ostream &os, const std::vector< std::vector<T> >& vec )
{
    unsigned int row = vec.size();
    if(row !=0)
    {
        unsigned int col = vec[0].size();
        for ( unsigned int i = 0; i < row; i++ )
        {
            for ( unsigned int j = 0; j < col; j++ )
            {
                os << vec[i][j] << " ";
            }
            os << std::endl;
        }
    }
    return os;
}


template <class T>
static std::istream& operator>> ( std::istream &is, std::vector< std::vector<T> >& vec )
{
    unsigned int row = vec.size();
    if(row !=0)
    {
        unsigned int col = vec[0].size();
        for ( unsigned int i = 0; i < row; i++ )
        {
            for ( unsigned int j = 0; j < col; j++ )
            {
                is >> vec[i][j];
            }
        }
    }
    return is;
}


/** static template function to judge whether the vector contains a value */
template <class T>
static bool IsContaining ( std::vector<T> v, T t )
{
    unsigned int size = v.size();
    for ( unsigned int i = 0; i < size; i++ )
    {
        if ( v[i] == t )
            return true;
    }

    return false;
}


/** static template function to judge whether the vector contains another vector */
template <class T>
static bool IsContaining ( std::vector<T> v, std::vector<T> t )
{
    unsigned int size = t.size();
    for ( unsigned int i = 0; i < size; i++ )
    {
        if ( !IsContaining ( v, t[i] ) )
            return false;
    }

    return true;
}


static int sign(double in)
{
	if (fabs(in) <= DBL_MIN ) return 0;
	else if (in > DBL_MIN ) return 1;
	else return -1;
}




static void SaveData(const double * d,
                     unsigned int datasize,
                     const std::string& fn)
{
    std::ofstream fp;
	fp.open(fn.c_str ());
    fp << "# Coordinates" << std::endl;
	for(unsigned int i = 0; i < datasize; ++i)
	{
        fp << i << "   " << d[i] << std::endl;
	}
	fp.close();
}


static void SaveData(const std::vector<double>& d, const std::string& fn)
{
	std::ofstream fp;
	fp.open(fn.c_str ());
    fp << "# Coordinates" << std::endl;
	for(unsigned int i = 0; i < d.size(); ++i)
	{
        fp << i << "   " << d[i] << std::endl;
	}
	fp.close();
}

//////////////////////////////////////////////////////////////////////////
/////////////Just make sure all ranges in ranges are exclusive////////////
static int inWhichRange(std::vector< std::pair<int, int> > ranges, int nb)
{
    for (int i = 0; i < ranges.size(); i++)
    {
        if( (nb >= ranges[i].first) && (nb <= ranges[i].second) )
            return i;
    }
    return -1;
}


static std::vector<std::string> decomposePageString(const std::string& istr)
{
    std::vector<std::string> res;

    std::istringstream iss(istr);
    std::string line;
    while (std::getline(iss, line, '\n'))
    {
        line.erase(std::remove(line.begin(), line.end(), 0x0D), line.end());	//	remove '\r'
        res.push_back(line);
    }

    return res;
}


static std::string convertInt(int number)
{
   std::stringstream ss;    //create a stringstream
   ss << number;            //add number to the stream
   return ss.str();         //return a string with the contents of the stream
}


static void replaceChar(std::string& str, const char ch1, const char ch2)
{
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == ch1)
            str[i] = ch2;
    }
}


static void makeStdString(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), 0x2C), str.end());	//	remove ','
    str.erase(std::remove(str.begin(), str.end(), 0x0A), str.end());	//	remove '\n'
    str.erase(std::remove(str.begin(), str.end(), 0x0D), str.end());	//	remove '\r'
    replaceChar(str, 0x3A, 0x5F);	//	':'	->	'_'
    replaceChar(str, 0x20, 0x5F);	//	' '	->	'_'
    replaceChar(str, 0x2F, 0x5F);	//	'/'	->	'_'
    replaceChar(str, 0x5C, 0x5F);	//	'\'	->	'_'
}


static std::string ws2s(const std::wstring& ws)
{
    std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
    setlocale(LC_ALL, "chs");
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest,0,_Dsize);
    wcstombs(_Dest,_Source,_Dsize);
    std::string result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}


static std::wstring s2ws(const std::string& s)
{
    setlocale(LC_ALL, "chs");
    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, "C");
    return result;
}


static std::wstring Longest_Common_Substring(const std::wstring& _str1, const std::wstring& _str2)
{
    if(_str1.empty() || _str2.empty())
    {
        return L"";
    }

    static int curr[1024];
    int maxSubstr = 0;
    int maxidx = -1;

    for(int i = 0; i < _str1.length(); ++i)
    {
        for(int j = _str2.length() - 1; j >= 0; j--)
        {
            if(_str1[i] != _str2[j])
            {
                curr[j] = 0;
            }
            else
            {
                if(i == 0 || j == 0)
                {
                    curr[j] = 1;
                }
                else
                {
                    curr[j] = 1 + curr[j-1];
                }
                if(maxSubstr < curr[j])
                {
                    maxSubstr = curr[j];
                    maxidx = j;
                }
            }
        }
    }
    return maxSubstr > 0 ? _str2.substr(maxidx, maxSubstr) : L"";
}


static int Longest_Common_Subsequence(const std::wstring &_str1, const std::wstring &_str2)
{
    if(_str1.empty() || _str2.empty())
    {
        return 0;
    }

    static int lcs_record[1024][1024];
    memset(lcs_record, 0, sizeof(lcs_record));

    for (int i = 0; i < _str1.length(); i++)
    {
        lcs_record[i][0] = 0;
    }
    for (int i = 0; i < _str2.length(); i++)
    {
        lcs_record[0][i] = 0;
    }
    for (int i = 1; i <= _str1.length(); i++)
    {
        for (int j = 1; j <= _str2.length(); j++)
        {
            if (_str1[i-1] == _str2[j-1])
            {
                lcs_record[i][j] = lcs_record[i-1][j-1] + 1;
            }
            else
            {
                lcs_record[i][j] = lcs_record[i-1][j] > lcs_record[i][j-1] ?
                    lcs_record[i-1][j] : lcs_record[i][j-1];
            }
        }
    }
    return lcs_record[_str1.length()][_str2.length()];
}


static std::vector<std::wstring> VectorString2VectorWString(const std::vector<std::string> &_vstr)
{
    std::vector<std::wstring> vwstr;
    vwstr.clear();
    for (int i = 0; i < _vstr.size(); i++)
    {
        vwstr.push_back(s2ws(_vstr[i]));
    }
    return vwstr;
}


static std::wstring get_the_best_match(const std::vector<std::wstring> &_database, const std::wstring &_query_str)
{
    int best_match_idx = -1;
    int best_match_score = -INT_MAX;
    int best_match_length = INT_MAX;
    for (int i = 0; i < _database.size(); i++)
    {
        if (Longest_Common_Substring(_database[i], _query_str) == _query_str)
        {
            best_match_idx = i;
            return _query_str;
        }
        int score = Longest_Common_Subsequence(_database[i], _query_str);
        if (score > best_match_score)
        {
            best_match_idx = i;
            best_match_score = score;
        }
        else if (score == best_match_score)
        {
            if (_database[i].length() < best_match_length)
            {
                best_match_length = _database[i].length();
                best_match_score = score;
                best_match_idx = i;
            }
        }

    }
    return _database[best_match_idx];
}


static std::string get_the_best_match(const std::vector<std::wstring> &_database, const std::string &_query_str)
{
    return ws2s(get_the_best_match(_database, s2ws(_query_str)));
}


static std::string getSystemTimeInString(bool year = true,
                                        bool mon = true,
                                        bool mday = true,
                                        bool hour = false,
                                        bool min = false,
                                        bool sec =  false)
{
    std::string res = "";
    std::stringstream ss;
    std::string s_year, s_mon, s_mday, s_hour, s_min, s_sec;

    time_t rawtime;
    struct tm * timeinfo = NULL;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    if(year)		{ ss << (timeinfo->tm_year+1900); ss >> s_year; res += s_year; ss.clear();}
    if(mon)
    {
        ss << (timeinfo->tm_mon+1); ss >> s_mon;
        if(timeinfo->tm_mon < 10)
            res += "0" + s_mon;
        else
            res += s_mon;
        ss.clear();
    }
    if(mday)
    {
        ss << timeinfo->tm_mday; ss >> s_mday;
        if(timeinfo->tm_mday < 10)
            res += "0" + s_mday;
        else
            res += s_mday;
        ss.clear();
    }
    if(hour)		{ ss << timeinfo->tm_hour; ss >> s_hour; res += s_hour; ss.clear();}
    if(min)			{ ss << timeinfo->tm_min; ss >> s_min; res += s_min; ss.clear();}
    if(sec)			{ ss << timeinfo->tm_sec; ss >> s_sec; res += s_sec; ss.clear();}

    return res;
}


static std::string GetCurrentLocalTimeInString()
{
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    std::string stime(asctime(timeinfo));

    stime = stime.substr(0, stime.length()-1);

    return stime;
}


static std::string StandardizeFN(unsigned int idx,
    unsigned int totalNumber = 100000,
    const std::string& prefix="",
    const std::string& suffix=".jpg")
{
    std::string res = prefix;
    std::stringstream ssidx, sstotal;
    std::string stridx, strtotal;
    ssidx << idx;
    ssidx >> stridx;
    sstotal << totalNumber;
    sstotal >> strtotal;

    for(unsigned int i = 0; i < strtotal.length() - stridx.length(); ++i )
    {
        res += "0";
    }

    res+=stridx;
    res+=suffix;

    ssidx.clear();
    sstotal.clear();

    return res;
}


static std::vector<std::string> StandardizeFNS(unsigned int idx,
    unsigned int totalNumber = 100000,
    unsigned int subNumber = 8,
    const std::string& prefix="",
    const std::string& suffix=".pcm")
{
    std::vector<std::string> res(subNumber);
    for(int i = 0; i < res.size(); i++)
        res[i] = prefix;
    std::stringstream ssidx, sstotal;
    std::string stridx, strtotal;
    ssidx << idx;
    ssidx >> stridx;
    sstotal << totalNumber;
    sstotal >> strtotal;

    for(int i = 0; i < subNumber; i++)
    {
        for(int j = 0; j < strtotal.length() - stridx.length(); ++j )
        {
            res[i] += "0";
        }

        res[i] += stridx;
        res[i] += "_";
        std::stringstream tmpSubssidx;
        std::string tmpSubstridx;
        tmpSubssidx << i;
        tmpSubssidx >> tmpSubstridx;
        res[i] += tmpSubstridx;

        res[i] += suffix;

        tmpSubssidx.clear();
    }

    ssidx.clear();
    sstotal.clear();

    return res;
}


static void write_text_to_log_file( const std::string &text, const std::string& logfilename = "" )
{
    std::string logfn = "";
    if (logfilename == "")
        logfn = "log_file.txt";
    else
        logfn = logfilename;
    std::ofstream log_file;
    log_file.open(logfn.c_str(), std::ios_base::out | std::ios_base::app );
    log_file << text << std::endl;
}

#ifdef _POSIX
#include "webcam.h"

#elif _WIN32

#include <windows.h>
#include <dshow.h>

typedef struct
{
    char			szRIFF[4];
    long			lRIFFSize;
    char			szWave[4];
    char			szFmt[4];
    long			lFmtSize;
    WAVEFORMATEX	wfex;
    char			szData[4];
    long			lDataSize;
} WAVEHEADER;



static std::string ConvertWCSToMBS(const wchar_t* pstr, long wslen)
{
    int len = ::WideCharToMultiByte(CP_ACP, 0, pstr, wslen, NULL, 0, NULL, NULL);

    std::string dblstr(len, '\0');
    len = ::WideCharToMultiByte(CP_ACP, 0 /* no flags */,
        pstr, wslen /* not necessary NULL-terminated */,
        &dblstr[0], len,
        NULL, NULL /* no default char */);

    return dblstr;
}

static std::string ConvertBSTRToMBS(BSTR bstr)
{
    int wslen = ::SysStringLen(bstr);
    return ConvertWCSToMBS((wchar_t*)bstr, wslen);
}

static BSTR ConvertMBSToBSTR(const std::string& str)
{
    int wslen = ::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
        str.data(), str.length(),
        NULL, 0);

    BSTR wsdata = ::SysAllocStringLen(NULL, wslen);
    ::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
        str.data(), str.length(),
        wsdata, wslen);
    return wsdata;
}

static std::string GetDevicePath(const IMoniker* pMoniker)
{
    IPropertyBag *pPropBag = NULL;
    HRESULT hr = const_cast<IMoniker*>(pMoniker)->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
    VARIANT var;
    VariantInit(&var);

    std::string s = "";
    hr = pPropBag->Read(L"DevicePath", &var, 0);
    if (SUCCEEDED(hr))
    {
        VariantClear(&var);
        s = ConvertBSTRToMBS(var.bstrVal);
    }

    pPropBag->Release();

    return s;
}


static std::string GetDeviceFriendlyName(const IMoniker* pMoniker)
{
    IPropertyBag *pPropBag = NULL;
    HRESULT hr = const_cast<IMoniker*>(pMoniker)->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
    VARIANT var;
    VariantInit(&var);

    std::string fullname = "";
    hr = pPropBag->Read(L"FriendlyName", &var, 0);
    if (SUCCEEDED(hr))
    {
        VariantClear(&var);
        fullname = ConvertBSTRToMBS(var.bstrVal);
    }

    pPropBag->Release();

    return fullname;
}

#endif		// _WIN32


#endif  // __VO_COMMON_H__

