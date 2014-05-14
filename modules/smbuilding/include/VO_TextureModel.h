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


#ifndef __VO_TEXTUREMODEL_H__
#define __VO_TEXTUREMODEL_H__


#include <vector>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "VO_Texture.h"
#include "VO_WarpingPoint.h"
#include "VO_ShapeModel.h"
#include "VO_Features.h"

#define AVERAGEFACETEXTURE 128



/** 
 * @author		JIA Pei
 * @brief		Statistical texture model.
 */
class VO_TextureModel : public VO_ShapeModel
{
friend class VO_Fitting2DSM;
friend class VO_FittingAAMBasic;
friend class VO_FittingAAMForwardIA;
friend class VO_FittingAAMInverseIA;
friend class VO_FittingASMLTCs;
friend class VO_FittingASMNDProfiles;
protected:
    /** PCA transform for texture, including eigenvectors, eigenvalues, and mean */
    cv::PCA							m_PCANormalizedTexture;

    /** Texture representation method - DIRECTTEXTURE, LAPLACETEXTURE, HARRISCORNERTEXTURE, HISTOGRAMEQUALIZED, GABOR, SEGMENTATION, etc. */
    unsigned int                	m_iTextureRepresentationMethod;

    /** Number of texture representations could be more or less than m_iNbOfChannels */
    unsigned int                	m_iNbOfTextureRepresentations;

	/** COLOR or Gray-level - 3 - COLOR; 1 - Gray-level */
	unsigned int					m_iNbOfChannels;

    /** Number of pixels in template face convex hull or concave hull. For IMM, 30132 */
    unsigned int                	m_iNbOfPixels;

    /** length of texture std::vector in format of b1b2b3...g1g2g3...r1r2r3.... m_iNbOfTextureRepresentations*m_iNbOfPixels. For IMM, 30132*3=90396 */
    unsigned int                	m_iNbOfTextures;

    /** Most possible texture eigens before PCA. For IMM: min (90396, 240) = 240 */
    unsigned int                	m_iNbOfEigenTexturesAtMost;

    /** Number of texture model eigens. For IMM: 127 */
    unsigned int               	 	m_iNbOfTextureEigens;

    /** Reference texture which is of size close to "1", but not guaranteed */
    VO_Texture         				m_VONormalizedMeanTexture;

    /** Reference texture which is scaled back to the original gray/color intensities */
    VO_Texture             			m_VOReferenceTexture;

    /** The template texture average standard deviation : 12364.1 */
    float                       	m_fAverageTextureStandardDeviation;

    /** Truncate Percentage for texture model PCA. Normally, 0.95 */
    float                       	m_fTruncatedPercent_Texture;

    /** All loaded textures in a std::vector format. For IMM, 240*90396 */
    std::vector<VO_Texture>         m_vTextures;

    /** All normalized textures in a std::vector format. For IMM, 240*90396 */
    std::vector<VO_Texture>         m_vNormalizedTextures;

    /** Template face image */
    cv::Mat                         m_ImageTemplateFace;

    /** Image of edges */
    cv::Mat                      	m_ImageEdges;

	/** Image of 2D normal distribution elllipses */
    cv::Mat							m_ImageEllipses;

	/** Unnormalized point warping information. For IMM, 30132 */
    std::vector<VO_WarpingPoint>	m_vTemplatePointWarpInfo;

    /** Normalized point warping information. For IMM, 30132 */
    std::vector<VO_WarpingPoint>  	m_vNormalizedPointWarpInfo;

	/** We need these image file names for later image loading */
    std::vector<std::string>		m_vStringTrainingImageNames;

    /** Initialization */
    void                        	init();

public:
    /** Default constructor to create a VO_TextureModel object */
    VO_TextureModel();

    /** Destructor */
    virtual ~VO_TextureModel();

    /** Calculate point warping information */
    static unsigned int         	VO_CalcPointWarpingInfo(const std::vector<VO_Triangle2DStructure>& templateTriangles, std::vector<VO_WarpingPoint>& warpInfo);

    /** Load a texture std::vector from the image "img", in terms of "iShape", with a texture building method */
    static bool                 	VO_LoadOneTextureFromShape(const VO_Shape& iShape, 
                                                                const cv::Mat& img,
																const std::vector<VO_Triangle2DStructure>& templateTriangles, 
                                                                const std::vector<VO_WarpingPoint>& warpInfo,
																VO_Texture& oTexture, 
																int trm = VO_Features::DIRECT);

    /** Normalize all textures */
    static float                	VO_NormalizeAllTextures(const std::vector<VO_Texture>& vTextures, std::vector<VO_Texture>& normalizedTextures);

    /** Rescale all normalized textures */
    static void                 	VO_RescaleAllNormalizedTextures(const VO_Texture& meanNormalizeTexture, std::vector<VO_Texture>& normalizedTextures);

    /** Rescale one normalized texture */
    static void                 	VO_RescaleOneNormalizedTexture(const VO_Texture& meanNormalizeTexture, VO_Texture& normalizedTexture);

    /** Returns the mean texture of all textures */
    static void                 	VO_CalcMeanTexture(const std::vector<VO_Texture>& vTextures, VO_Texture& meanTexture);

    /** Put one texture to the template face. Just for display! */
    static void                 	VO_PutOneTextureToTemplateShape(const VO_Texture& texture, const std::vector<VO_Triangle2DStructure>& triangles, cv::Mat& oImg);

    /** Warp form one shape to another */
    static unsigned int             VO_WarpFromOneShapeToAnother(const VO_Shape& iShape, const VO_Shape& oShape, const std::vector<VO_Triangle2DStructure>& triangles, const cv::Mat& iImg, cv::Mat& oImg);

    /** Morphing */
    static void                 	VO_Morphing(const VO_Shape& iShape1, const VO_Shape& iShape2, std::vector<VO_Shape>& oShapes, const std::vector<VO_Triangle2DStructure>& triangles, const cv::Mat& iImg1, const cv::Mat& iImg2, std::vector<cv::Mat>& oImgs, float step = 0.2);

    /** Put one texture to whatever shape, just for display */
    static void                 	VO_PutOneTextureToOneShape(const VO_Texture& texture, const VO_Shape& oShape, const std::vector<VO_Triangle2DStructure>& triangles, cv::Mat& oImg);

    /** Warp form one shape to another */
    static std::vector<float>       VO_CalcSubPixelTexture(float x, float y, const cv::Mat& image);
    static void                 	VO_CalcSubPixelTexture(float x, float y, const cv::Mat& image, float* gray);
    static void                 	VO_CalcSubPixelTexture(float x, float y, const cv::Mat& image, float* b, float* g, float* r);

    /** Get an intensity std::vector of size 1 or 3 (rgb), at point (x,y) in image */
    static void						VO_CalcPixelRGB(int x, int y, const cv::Mat& image, float& B, float& G, float& R);

    /** Change the normalized texture inTexture to the reference one outTexture */
    static void                 	VO_NormalizedTexture2ReferenceScale(const VO_Texture& inTexture, float textureSD, VO_Texture& outTexture);

    /** Normalize inTexture to outTexture */
    static void                 	VO_ReferenceTextureBack2Normalize(const VO_Texture& inTexture, float textureSD, VO_Texture& outTexture);

    /** Put edges on template face */
    static void                 	VO_PutEdgesOnTemplateFace(const std::vector<VO_Edge>& edges, const VO_Shape& templateShape, const cv::Mat& iImg, cv::Mat& oImg);

    /** Put every single triangle onto iImg and obtaining oImg */
    static void                 	VO_PutTrianglesOnTemplateFace(const std::vector<VO_Triangle2DStructure>& triangles, const cv::Mat& iImg, std::vector<cv::Mat>& oImgs);
	
	/** Put every single ellipse onto iImg and obtaining oImg */
    static void                 	VO_PutPDMEllipsesOnTemplateFace(const std::vector<VO_Ellipse>& ellipses, const cv::Mat& iImg, cv::Mat& oImg);

    /** Put a shape onto iImg and obtaining oImg, without the edge information */
    static void                 	VO_PutShapeOnTemplateFace(const VO_Shape& iShape, const cv::Mat& iImg, cv::Mat& oImg);

	/** Texture parameters constraints */
    void							VO_TextureParameterConstraint(cv::Mat_<float>& ioT, float nSigma = 4.0f);

    /** Texture projected to texture parameters*/
    void   	                		VO_NormalizedTextureProjectToTParam(const VO_Texture& iTexture, cv::Mat_<float>& outT) const;

    /** Texture parameters back projected to texture parameters */
    void	                   		VO_TParamBackProjectToNormalizedTexture(const cv::Mat_<float>& inT, VO_Texture& oTexture, int tr = 3) const;
    void	                   		VO_TParamBackProjectToNormalizedTexture(const cv::Mat_<float>& inT, cv::Mat_<float>& oTextureMat) const;

    /** texture -> normalized -> project to texture parameters */
    void   	                    	VO_CalcAllParams4AnyTexture(const cv::Mat_<float>& iTexture, cv::Mat_<float>& oTexture, cv::Mat_<float>& outT);
    void                            VO_CalcAllParams4AnyTexture(VO_Texture& ioTexture, cv::Mat_<float>& outT);

	/** Load Training data for texture model */
	bool							VO_LoadTextureTrainingData( const std::vector<std::string>& allImgFiles4Training,
																unsigned int channels,
																int trm = VO_Features::DIRECT);

    /** Build Texture Model */
    void                            VO_BuildTextureModel(	const std::vector<std::string>& allLandmarkFiles4Training,
															const std::vector<std::string>& allImgFiles4Training,
															const std::string& shapeinfoFileName, 
															unsigned int database,
															unsigned int channels = 3,
															int trm = VO_Features::DIRECT, 
															float TPShape = 0.95f, 
															float TPTexture = 0.95f, 
															bool useKnownTriangles = false);

    /** Save Texture Model, to a specified folder */
    void                            VO_Save(const std::string& fd);

    /** Load all parameters */
    void                            VO_Load(const std::string& fd);

    /** Load Parameters for fitting */
    void                            VO_LoadParameters4Fitting(const std::string& fd);

    /** Gets and Sets */
    cv::Mat_<float>                 GetNormalizedTextureMean() const {return this->m_PCANormalizedTexture.mean;}
    cv::Mat_<float>                 GetNormalizedTextureEigenValues() const {return this->m_PCANormalizedTexture.eigenvalues;}
    cv::Mat_<float>                 GetNormalizedTextureEigenVectors() const {return this->m_PCANormalizedTexture.eigenvectors;}
    unsigned int                    GetTextureExtractionMethod() const {return this->m_iTextureRepresentationMethod;}
    unsigned int                    GetNbOfTextureRepresentations() const {return this->m_iNbOfTextureRepresentations;}
	unsigned int                    GetNbOfChannels() const {return this->m_iNbOfChannels;}
    unsigned int                    GetNbOfPixels() const {return this->m_iNbOfPixels;}
    unsigned int                    GetNbOfTextures() const {return this->m_iNbOfTextures;}
    unsigned int                    GetNbOfEigenTexturesAtMost() const {return this->m_iNbOfEigenTexturesAtMost;}
	unsigned int                    GetNbOfTextureEigens() const {return this->m_iNbOfTextureEigens;}
	VO_Texture						GetNormalizedMeanTexture() const {return this->m_VONormalizedMeanTexture;}
    VO_Texture                 		GetAAMReferenceTexture() const {return this->m_VOReferenceTexture;}
    float                           GetAverageTextureStandardDeviation() const {return this->m_fAverageTextureStandardDeviation;}
    float                           GetTruncatedPercent_Texture() const {return this->m_fTruncatedPercent_Texture;}
    std::vector<VO_Texture>         GetTextures() const {return this->m_vTextures;}
    std::vector<VO_Texture>         GetNormalizedTextures() const {return this->m_vNormalizedTextures;}
    cv::Mat                       	GetIplTemplateFace() const {return this->m_ImageTemplateFace;}
    cv::Mat                       	GetIplEdges() const {return this->m_ImageEdges;}
    std::vector<VO_WarpingPoint>    GetTemplatePointWarpInfo() const {return this->m_vTemplatePointWarpInfo;}
    std::vector<VO_WarpingPoint>    GetNormalizedPointWarpInfo() const {return this->m_vNormalizedPointWarpInfo;}
    std::vector<std::string>		GetStringTrainingImageNames() const {return this->m_vStringTrainingImageNames;}

//    void                            SetTextureExtractionMethod(unsigned int tem) {this->m_iTextureRepresentationMethod = tem;}
//    void                            SetNbOfNbOfChannels(unsigned int inNbOfChannels) {this->m_iNbOfTextureRepresentations = inNbOfChannels;}
//    void                            SetNbOfPixels(unsigned int inNbOfPixels) {this->m_iNbOfPixels = inNbOfPixels;}
//    void                            SetNbOfTextures(unsigned int inNbOfTextures) {this->m_iNbOfTextures = inNbOfTextures;}
//    void                            SetNbOfTruncatedTextures(unsigned int inNbOfTruncatedTextures)
//                                    {this->m_iNbOfTextureEigens = inNbOfTruncatedTextures;}
//    void                            SetNbOfEigenTexturesAtMost(unsigned int inNbOfEigenTexturesAtMost)
//                                    {this->m_iNbOfEigenTexturesAtMost = inNbOfEigenTexturesAtMost;}
//    void                            SetAAMReferenceTexture(const VO_Texture& inAAMReferenceTexture)
//                                    {this->m_VOReferenceTexture = inAAMReferenceTexture;}
//    void                            SetAverageTextureStandardDeviation(float inAverageTextureStandardDeviation)
//                                    {this->m_fAverageTextureStandardDeviation = inAverageTextureStandardDeviation;}
//    void                            SetTruncatedPercent_Texture(float inTP) {this->m_fTruncatedPercent_Texture = inTP;}
//    void                            SetIplTemplateFace(const cv::Mat& inIplTF)
//                                    {inIplTF.copyTo(this->m_ImageTemplateFace);}
//    void                            SetIplEdges(const cv::Mat& inIplEdges)
//                                    {inIplEdges.copyTo(this->m_ImageEdges);}
//    void                            SetNormalizedMeanTexture(const VO_Texture& inNormalizedMeanTexture)
//                                    {this->m_VONormalizedMeanTexture = inNormalizedMeanTexture;}
//    void                            Setcv::PointWarpInfo(const std::vector<VO_WarpingPoint>& incv::PointWarpInfo)
//                                    {this->m_vNormalizedPointWarpInfo = incv::PointWarpInfo;}

};


#endif // __VO_TEXTUREMODEL_H__

