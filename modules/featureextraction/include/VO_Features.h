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
* Create Date:      2010-03-08                                                                      *
* Modify Date:      2014-04-15                                                                      *
****************************************************************************************************/


#ifndef _VO_FEATURES_H_
#define _VO_FEATURES_H_

#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include <opencv2/imgproc/imgproc.hpp>



#define CC_FEATURES         FEATURES
#define CC_FEATURE_PARAMS   "featureParams"
#define CC_MAX_CAT_COUNT    "maxCatCount"
#define CC_RECTS            "rects"
#define CC_RECT             "rect"

#define FEATURES "features"

#define CV_SUM_OFFSETS( p0, p1, p2, p3, rect, step )                      \
    /* (x, y) */                                                          \
    (p0) = (rect).x + (step) * (rect).y;                                  \
    /* (x + w, y) */                                                      \
    (p1) = (rect).x + (rect).width + (step) * (rect).y;                   \
    /* (x, y + h) */                                                      \
    (p2) = (rect).x + (step) * ((rect).y + (rect).height);                \
    /* (x + w, y + h) */                                                  \
    (p3) = (rect).x + (rect).width + (step) * ((rect).y + (rect).height);

#define CV_TILTED_OFFSETS( p0, p1, p2, p3, rect, step )                   \
    /* (x, y) */                                                          \
    (p0) = (rect).x + (step) * (rect).y;                                  \
    /* (x + w, y + w) */                                                  \
    (p1) = (rect).x + (rect).width + (step) * ((rect).y + (rect).width);  \
    /* (x - h, y + h) */                                                  \
    (p2) = (rect).x - (rect).height + (step) * ((rect).y + (rect).height);\
    /* (x + w - h, y + w + h) */                                          \
    (p3) = (rect).x + (rect).width - (rect).height                        \
           + (step) * ((rect).y + (rect).width + (rect).height);


template<class Feature>
void _writeFeatures(const std::vector<Feature> features,
                    cv::FileStorage &fs,
                    const cv::Mat& featureMap )
{
    fs << FEATURES << "[";
    const cv::Mat_<int>& featureMap_ = (const cv::Mat_<int>&)featureMap;
    for ( int fi = 0; fi < featureMap.cols; fi++ )
        if ( featureMap_(0, fi) >= 0 )
        {
            fs << "{";
            features[fi].write( fs );
            fs << "}";
        }
    fs << "]";
}


//template<class Feature>
//void _readFeatures( vector<Feature> features, const FileStorage &fs, const Mat& featureMap )
//{
//
//    fs >> FEATURES >> "[";
//    const cv::Mat_<int>& featureMap_ = (const cv::Mat_<int>&)featureMap;
//    for ( int fi = 0; fi < featureMap.cols; fi++ )
//        if ( featureMap_(0, fi) >= 0 )
//        {
//            fs << "{";
//            features[fi].write( fs );
//            fs << "}";
//        }
//    fs << "]";
//}
//


/**
 * @author      JIA Pei
 * @version     2010-03-13
 * @brief       Generalized class for feature evaluator, namely, extracted features
  */
class VO_Features
{
friend class VO_ASMLTCs;
friend class VO_FittingASMLTCs;
protected:
    /** All features are stored as a row vector */
    cv::Mat_<float>                 m_MatFeatures;

    /** Feature type -- which type of the feature is it? LBP, Haar, Gabor, etc. */
    unsigned int                m_iFeatureType;

    /** Total number of feature categories. Some times, 
     * we have thousands of features, but they can be categorized into 16 categories.
     * --  0 in case of numerical features */
    unsigned int                m_iNbOfFeatureCategories;

    /** Total number of features */
    unsigned int                m_iNbOfFeatures;
    
    /** Total number of adopted features */
    unsigned int                m_iNbOfAdoptedFeatures;

    /** Adopted feature indexes */
    std::vector<unsigned int>   m_vAdoptedFeatureIndexes;

    /** All features are extracted from an image patch of such a size */
    cv::Size                    m_CVSize;

    /** Integral image */
    cv::Mat                     m_MatIntegralImage;

    /** Square image */            
    cv::Mat                     m_MatSquareImage;

    /** Tilted integral image */
    cv::Mat                     m_MatTiltedIntegralImage;

    /** Normalization factor */
    cv::Mat                     m_MatNormFactor;

    /** Initialization */
    void                        init()
    {
        this->m_MatFeatures.release();
        this->m_iFeatureType    = UNDEFINED;
        this->m_CVSize          = cv::Size(0, 0);
        this->m_MatIntegralImage.release();
        this->m_MatSquareImage.release();
        this->m_MatTiltedIntegralImage.release();
        this->m_MatNormFactor.release();
    }

public:
    enum {
        UNDEFINED = 0,
        DIRECT = 1,
        HISTOGRAMEQUALIZED = 2,
        LAPLACE = 3,
        GABOR = 4,
        HAAR = 5,
        LBP = 6,
        DAUBECHIES = 7,
        COIFLETS = 8,
        SEGMENTATION = 9,
        HARRISCORNER = 10,
        SELFDEFINED = 11
    };

    /** Default constructor */
    VO_Features()               {this->init();}

    /** Constructor */
    VO_Features(unsigned int type, cv::Size size)
    {
        this->init();
        this->m_iFeatureType    = type;
        this->m_CVSize          = size;
    }

    /** Destructor */
    virtual ~VO_Features()
    {
        this->m_MatFeatures.release();
        this->m_MatIntegralImage.release();
        this->m_MatSquareImage.release();
        this->m_MatTiltedIntegralImage.release();
        this->m_MatNormFactor.release();
    }

    /** Generate all features within such a size of window */
    virtual void                VO_GenerateAllFeatureInfo(const cv::Size& size, unsigned int generatingMode = 0) = 0;
    virtual void                VO_GenerateAllFeatures(const cv::Mat& iImg, cv::Point pt = cv::Point(0,0)) = 0;

    /** Read and write */
    virtual void                ReadFeatures( const cv::FileStorage& fs, cv::Mat_<float>& featureMap ) = 0;
    virtual void                WriteFeatures( cv::FileStorage& fs, const cv::Mat_<float>& featureMap ) const = 0;

    // Gets and Sets
    unsigned int                GetFeatureType() const { return this->m_iFeatureType; }
    unsigned int                GetNbOfFeatureCategories() const { return this->m_iNbOfFeatureCategories; }
    unsigned int                GetNbOfFeatures() const { return this->m_iNbOfFeatures; }
    unsigned int                GetNbOfAdoptedFeatures() const {return this->m_iNbOfAdoptedFeatures; }
    std::vector<unsigned int>   GetAdoptedFeatureIndexes() const { return this->m_vAdoptedFeatureIndexes; }
    cv::Mat_<float>             GetFeatures() const { return this->m_MatFeatures; }
    cv::Mat_<float>             GetAdoptedFeatures() const
    {
                                cv::Mat_<float> res = cv::Mat_<float>::zeros(1, this->m_iNbOfAdoptedFeatures);
                                for(unsigned int i = 0; i < this->m_iNbOfAdoptedFeatures; i++)
                                {
                                    res(0, i) = this->m_MatFeatures(0, this->m_vAdoptedFeatureIndexes[i]);
                                }
                                return res;
    }
    cv::Size                    GetSize() const { return this->m_CVSize; }
};

#endif        // _VO_FEATURES_H_
