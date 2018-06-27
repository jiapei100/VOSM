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
* Modify Date:      2014-04-15                                                                      *
****************************************************************************************************/

#include <iostream>
#include <fstream>
#include "float.h"
#include <boost/filesystem.hpp>
#include <boost/regex/v4/fileiter.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "smf.h"
#include "VO_FaceKeyPoint.h"


/**
 * @brief How to use testsmfitting?
 */
void usage_build()
{
    std::cout << "Usage: smfitting [options] trained_data type testing_images testing_annotations database staticORdynamic recording" << std::endl
        << "options: " << std::endl
        << "   -o   trained data directory (required) " << std::endl
        << "   -t   fitting method to be used (ASM_PROFILEND, ASM_LTC, AAM_BASIC, AAM_CMUICIA, AAM_IAIA. default ASM_PROFILEND ) " << std::endl
        << "   -i   testing image directory containing at least one image (required) " << std::endl
        << "   -a   testing annotation directory (can be ignored) " << std::endl
        << "   -d   testing database -- if annotation directory is specified, database should also be specified for further evaluation on fitting performance (can be ignored) " << std::endl
        << "   -s   static image sequence or dynamic image sequence (default value true) " << std::endl
        << "   -r   recording the fitting results or not (default value false) " << std::endl
        << std::endl << std::endl;

    std::cout << "Note: current testsmfitting adopts 2D Profile ASM by default. " << std::endl
        << "If you would like to try 1D Profile ASM, you have to manually change the code " << std::endl
        << "in function VO_Fitting2DSM::VO_StartFitting in file VO_Fitting2DSM.cpp, say, " << std::endl
        << "around line 318 of file VO_Fitting2DSM.cpp: " << std::endl
        << "change the 5th parameter from '2' to '1' of function " << std::endl
        << "dynamic_cast<VO_FittingASMNDProfiles*>(this)->VO_ASMNDProfileFitting. " << std::endl
        << std::endl << std::endl;
    
    std::cout << "Face Detection: current testsmfitting use Adaboost technology to detect face " << std::endl
        << "as well as face components for face location initialization. " << std::endl
        << "Refer to CFaceDetectionAlgs in main(). Default Adaboost detectors " << std::endl
        << "installed with OpenCV installation are adopted in current testsmfitting. " << std::endl
        << "You may manually change the Adaboost detectors according to your own cascade file paths. " << std::endl
        << std::endl << std::endl;
    
    std::cout << "Face Tracking: current testsmfitting only deal with image sequences. " << std::endl
        << "- For static images, it's pointless to do tracking. " << std::endl
        << "- For dynamic image sequences, Camshift tracking strategy is adopted. " << std::endl
        << "Please Refer to CTrackingAlgs() in main(), the default setting of function " << std::endl
        << "function CTrackingAlgs() is Camshift algorithm. " << std::endl
        << std::endl << std::endl;
        
    std::cout<< "Vision Open doesn't provide the video IO or webcam IO although I've done my own IO for all kinds." << std::endl
        << "FFmpeg is so competent. Users are highly encouraged to use their own video file IO " << std::endl
        << "and webcam IO and use VOSM in their own real-time applications. " << std::endl
        << std::endl << std::endl;
    
    exit(0);
}


/**
 * @brief parse the arguments
 */
void parse_option(  int argc,
                    char **argv,
                    std::string& trainedData,
                    unsigned int& type,
                    std::vector<std::string>& imageFNs,
                    std::vector<std::string>& annotationFNs,
                    unsigned int& database,
                    bool& staticOrNot,
                    bool& recordOrNot)
{
    char *arg = NULL;
    int optindex, handleoptions=1;
    
    /* parse options */
    optindex = 0;
    while (++optindex < argc)
    {
        if(argv[optindex][0] != '-') break;
        if(++optindex >= argc) usage_build();

        switch(argv[optindex-1][1])
        {
        case 'o':
            trainedData = argv[optindex];
            break;
        case 't':
        {
            if(strcmp(argv[optindex], "ASM_PROFILEND") == 0)
                type    = VO_AXM::ASM_PROFILEND;
            else if(strcmp(argv[optindex], "ASM_LTC") == 0)
                type    = VO_AXM::ASM_LTC;
            else if(strcmp(argv[optindex], "AAM_BASIC") == 0)
                type    = VO_AXM::AAM_BASIC;
            else if(strcmp(argv[optindex], "AAM_CMUICIA") == 0)
                type    = VO_AXM::AAM_CMUICIA;
            else if(strcmp(argv[optindex], "AAM_IAIA") == 0)
                type    = VO_AXM::AAM_IAIA;
            else
            {
                std::cerr << "Wrong fitting type parameters!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
            break;
        case 'i':
        {
            if ( ! boost::filesystem::is_directory( argv[optindex] ) )
            {
                std::cerr << "image path does not exist!" << std::endl;
                exit(EXIT_FAILURE);
            }
            imageFNs    = VO_ScanFilesInDir::ScanNSortImagesInDirectory ( argv[optindex] );
        }
            break;
        case 'a':
        {
            if ( ! boost::filesystem::is_directory( argv[optindex] ) )
            {
                std::cerr << "landmark path does not exist!" << std::endl;
                exit(EXIT_FAILURE);
            }
            annotationFNs   = VO_ScanFilesInDir::ScanNSortAnnotationInDirectory ( argv[optindex] );
        }
            break;
        case 'd':
        {
            if(strcmp(argv[optindex], "PUT") == 0)
                database    = CAnnotationDBIO::PUT;
            else if(strcmp(argv[optindex], "IMM") == 0)
                database    = CAnnotationDBIO::IMM;
            else if(strcmp(argv[optindex], "AGING") == 0)
                database    = CAnnotationDBIO::AGING;
            else if(strcmp(argv[optindex], "BIOID") == 0)
                database    = CAnnotationDBIO::BIOID;
            else if(strcmp(argv[optindex], "XM2VTS") == 0)
                database    = CAnnotationDBIO::XM2VTS;
            else if(strcmp(argv[optindex], "FRANCK") == 0)
                database    = CAnnotationDBIO::FRANCK;
            else if(strcmp(argv[optindex], "EMOUNT") == 0)
                database    = CAnnotationDBIO::EMOUNT;
            else if(strcmp(argv[optindex], "JIAPEI") == 0)
                database    = CAnnotationDBIO::JIAPEI;
            else
            {
                std::cerr << "Wrong database parameters!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
            break;
        case 's':
        {
            if(strcmp(argv[optindex], "false") == 0)
                staticOrNot = false;
            else if(strcmp(argv[optindex], "true") == 0)
                staticOrNot = true;
            else
            {
                std::cerr << "Wrong StaticOrNot parameter!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
            break;
        case 'r':
        {
            if(strcmp(argv[optindex], "false") == 0)
                recordOrNot = false;
            else if(strcmp(argv[optindex], "true") == 0)
                recordOrNot = true;
            else
            {
                std::cerr << "Wrong recordOrNot parameter!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
            break;
        default:
        {
            std::cerr << "unknown options" << std::endl;
            usage_build();
        }
            break;
        }
    }
    
    if (imageFNs.size() == 0)
    {
        std::cerr << " No image loaded" << std::endl;
        usage_build();
        exit(EXIT_FAILURE);
    }
    if (annotationFNs.size() != 0 && annotationFNs.size() != imageFNs.size() )
    {
        std::cerr << " If annotations are loaded, then, the number of landmarks should be equal to the number of images " << std::endl;
        usage_build();
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char **argv)
{
    std::string                 traineddatadir;
    unsigned int                fittingmtd = VO_AXM::ASM_PROFILEND;
    unsigned int                database = CAnnotationDBIO::EMOUNT;
    std::vector<std::string>    AllImgFiles4Testing;
    std::vector<std::string>    AllAnnotationFiles4Evaluation;
    bool                        staticOrNot = true;
    bool                        record = false;
    
    parse_option(   argc,
                    argv,
                    traineddatadir,
                    fittingmtd,
                    AllImgFiles4Testing,
                    AllAnnotationFiles4Evaluation,
                    database,
                    staticOrNot,
                    record);

    CTrackingAlgs* trackAlg = new CTrackingAlgs();
    VO_Fitting2DSM* fitting2dsm = NULL;
    switch(fittingmtd)
    {
    case VO_AXM::AAM_BASIC:
    case VO_AXM::AAM_DIRECT:
        fitting2dsm = new VO_FittingAAMBasic();
        dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)->VO_LoadParameters4Fitting(traineddatadir);
        break;
    case VO_AXM::CLM:
    case VO_AXM::AFM:
        fitting2dsm = new VO_FittingAFM();
        dynamic_cast<VO_FittingAFM*>(fitting2dsm)->VO_LoadParameters4Fitting(traineddatadir);
        break;
    case VO_AXM::AAM_IAIA:
    case VO_AXM::AAM_CMUICIA:
        fitting2dsm = new VO_FittingAAMInverseIA();
        dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)->VO_LoadParameters4Fitting(traineddatadir);
        break;
    case VO_AXM::AAM_FAIA:
        fitting2dsm = new VO_FittingAAMForwardIA();
        dynamic_cast<VO_FittingAAMForwardIA*>(fitting2dsm)->VO_LoadParameters4Fitting(traineddatadir);
        break;
    case VO_AXM::ASM_LTC:
        fitting2dsm = new VO_FittingASMLTCs();
        dynamic_cast<VO_FittingASMLTCs*>(fitting2dsm)->VO_LoadParameters4Fitting(traineddatadir);
        break;
    case VO_AXM::ASM_PROFILEND:
        fitting2dsm = new VO_FittingASMNDProfiles();
        dynamic_cast<VO_FittingASMNDProfiles*>(fitting2dsm)->VO_LoadParameters4Fitting(traineddatadir);
        break;
    }


    std::vector<cv::Mat> oImages;
    std::vector<VO_Shape> oShapes;
    int nb = 20;
    bool doEvaluation = false;
    cv::Mat_<float> nbOfIterations;
    cv::Mat_<float> deviations;
    cv::Mat_<float> ptsErrorFreq;
    cv::Mat_<float> times;
    if (AllAnnotationFiles4Evaluation.size() !=0 )
    {
        unsigned int nbOfSamples = AllAnnotationFiles4Evaluation.size();
        doEvaluation = true;
        nbOfIterations = cv::Mat_<float>::zeros(1, nbOfSamples);
        deviations = cv::Mat_<float>::zeros(1, nbOfSamples);
        ptsErrorFreq = cv::Mat_<float>::zeros(nbOfSamples, nb);
        times = cv::Mat_<float>::zeros(1, nbOfSamples);
    }
    CAnnotationDBIO::VO_LoadShapeTrainingData( AllAnnotationFiles4Evaluation, database, oShapes);

    CFaceDetectionAlgs* fd = new CFaceDetectionAlgs("", VO_AdditiveStrongerClassifier::BOOSTING);
    cv::Point2f ptLeftEyeCenter, ptRightEyeCenter, ptMouthCenter;
    fd->SetConfiguration(   "/usr/local/share/OpenCV/lbpcascades/lbpcascade_frontalface_improved.xml", 
                            "/usr/local/share/OpenCV/lbpcascades/lbpcascade_profileface.xml",
                            "/usr/local/share/OpenCV/cascades/haarcascade_mcs_lefteye_alt.xml",
                            "/usr/local/share/OpenCV/cascades/haarcascade_mcs_righteye_alt.xml",
                            "/usr/local/share/OpenCV/cascades/haarcascade_mcs_nose.xml",
                            "/usr/local/share/OpenCV/cascades/haarcascade_mcs_mouth.xml",
                            VO_AdditiveStrongerClassifier::BOOSTING,
                            CFaceDetectionAlgs::FRONTAL );

    cv::Mat iImage, resizedImage, drawImage, fittedImage;
    VO_Shape fittingShape;
    unsigned int detectionTimes = 0;
    
    // For static images from stadard face databases
    // (Detection only, no tracking) + ASM/AAM
    if(staticOrNot)
    {
        detectionTimes = 0;
        for(unsigned int i = 0; i < AllImgFiles4Testing.size(); i++)
        {
            iImage = cv::imread(AllImgFiles4Testing[i]);
            // Explained by JIA Pei. You can use cv::resize() to ensure before fitting starts,
            // every image to be tested is of a standard size, say (320, 240)
            iImage.copyTo(resizedImage);
            // cv::resize(iImage, resizedImage, Size(320, 240) );
            iImage.copyTo(fittedImage);
            size_t found1 = AllImgFiles4Testing[i].find_last_of("/\\");
            size_t found2 = AllImgFiles4Testing[i].find_last_of(".");
            std::string prefix = AllImgFiles4Testing[i].substr(found1+1, found2-1-found1);
            
            detectionTimes++;
            fd->FullFaceDetection(  resizedImage,
                                    NULL,
                                    true,
                                    true,
                                    true,
                                    true,
                                    1.0,
                                    cv::Size(80,80),
                                    cv::Size( std::min(resizedImage.rows,resizedImage.cols), std::min(resizedImage.rows,resizedImage.cols) ) ); // Size(240,240)

            if( fd->IsFaceDetected() )
            {
                fd->CalcFaceKeyPoints();
                double tmpScaleX = (double)iImage.cols/(double)resizedImage.cols;
                double tmpScaleY = (double)iImage.rows/(double)resizedImage.rows;
                cv::Rect rect = fd->GetDetectedFaceWindow();
                ptLeftEyeCenter = fd->GetDetectedFaceKeyPoint(VO_KeyPoint::LEFTEYECENTER);
                ptRightEyeCenter = fd->GetDetectedFaceKeyPoint(VO_KeyPoint::RIGHTEYECENTER);
                ptMouthCenter = fd->GetDetectedFaceKeyPoint(VO_KeyPoint::MOUTHCENTER);
                ptLeftEyeCenter.x *= tmpScaleX;
                ptLeftEyeCenter.y *= tmpScaleY;
                ptRightEyeCenter.x *= tmpScaleX;
                ptRightEyeCenter.y *= tmpScaleY;
                ptMouthCenter.x *= tmpScaleX;
                ptMouthCenter.y *= tmpScaleY;
                
                // Explained by JIA Pei, you can save to see the detection results.
//                iImage.copyTo(drawImage);
//                cv::cv::Rectangle(drawImage, Point(ptLeftEyeCenter.x-1, ptLeftEyeCenter.y-1),
//                                     Point(ptLeftEyeCenter.x+1, ptLeftEyeCenter.y+1),
//                                colors[5], 2, 8, 0);
//                cv::cv::Rectangle(drawImage, Point(ptRightEyeCenter.x-1, ptRightEyeCenter.y-1),
//                                     Point(ptRightEyeCenter.x+1, ptRightEyeCenter.y+1),
//                                colors[6], 2, 8, 0);
//                cv::cv::Rectangle(drawImage, Point(ptMouthCenter.x-1, ptMouthCenter.y-1),
//                                     Point(ptMouthCenter.x+1, ptMouthCenter.y+1),
//                                colors[7], 2, 8, 0);
//                imwrite("drawImage.jpg", drawImage);
//                imwrite("resizedImage.jpg", resizedImage);
                fitting2dsm->VO_StartFitting(   iImage,
                                                oImages,
                                                fittingmtd,
                                                ptLeftEyeCenter,
                                                ptRightEyeCenter,
                                                ptMouthCenter,
                                                VO_Fitting2DSM::EPOCH, // at most, how many iterations will be carried out
                                                4,
                                                record );
                nbOfIterations(0,i) = (float)(fitting2dsm->GetNbOfIterations());
                fittingShape = fitting2dsm->GetFittedShape();
                times(0,i) = fitting2dsm->GetFittingTime();
//                cout << nbOfIterations(0,i) << std::endl;
            }
            
            if(record)
            {
                // Explained by JIA Pei. For static images, we can save all intermediate images of the fitting process.
                SaveSequentialImagesInFolder(oImages, prefix);
                std::string fn = prefix+".jpg";
                if(oImages.size() > 0)
                {
                    fittedImage = oImages.back();
                    cv::imwrite(fn.c_str(), fittedImage);
                    oImages.clear();
                }
            }
            
            // For evaluation
            if(doEvaluation)
            {
                std::vector<float> ptErrorFreq;
                float deviation = 0.0f;
                std::vector<unsigned int> unsatisfiedPtList;
                unsatisfiedPtList.clear();
                CRecognitionAlgs::CalcShapeFittingEffect(   oShapes[i],
                                                            fittingShape,
                                                            deviation,
                                                            ptErrorFreq,
                                                            nb);
                deviations(0,i) = deviation;
                for(unsigned int j = 0; j < nb; j++)
                    ptsErrorFreq(i, j) = ptErrorFreq[j];
                CRecognitionAlgs::SaveShapeRecogResults("./",
                                                        prefix,
                                                        deviation,
                                                        ptErrorFreq);
            }
        }
        
        std::cout << "detection times = " << detectionTimes << std::endl;
        float avgIter = cv::mean(nbOfIterations).val[0];
        std::cout << avgIter << std::endl;
        float avgTime = cv::mean(times).val[0];
        std::cout << avgTime << std::endl;
        cv::Scalar avgDev, stdDev;
        cv::meanStdDev(deviations, avgDev, stdDev);
        std::cout << avgDev.val[0] << " " << stdDev.val[0] << std::endl << std::endl;
        std::vector<float> avgErrorFreq(nb, 0.0f);
        for(int j = 0; j < nb; j++)
        {
            cv::Mat_<float> col = ptsErrorFreq.col(j);
            avgErrorFreq[j] = cv::mean(col).val[0];
            std::cout << j << " " << avgErrorFreq[j] << std::endl;
        }
    }
    // For dynamic image sequences
    // (Detection or Tracking) + ASM/AAM
    else
    {
        bool isTracked = false;
        detectionTimes = 0;
        for(unsigned int i = 0; i < AllImgFiles4Testing.size(); i++)
        {
            iImage = cv::imread(AllImgFiles4Testing[i]);
            // Explained by JIA Pei. You can use cv::resize() to ensure before fitting starts,
            // every image to be tested is of a standard size, say (320, 240)
            // iImage.copyTo(resizedImage);    // 
            cv::resize(iImage, resizedImage, cv::Size(320, 240) );
            iImage.copyTo(fittedImage);
            size_t found1 = AllImgFiles4Testing[i].find_last_of("/\\");
            size_t found2 = AllImgFiles4Testing[i].find_last_of(".");
            std::string prefix = AllImgFiles4Testing[i].substr(found1+1, found2-1-found1);

            if(!isTracked)
            {
                detectionTimes++;
                fd->FullFaceDetection(  resizedImage,
                                        NULL,
                                        true,
                                        true,
                                        true,
                                        true,
                                        1.0,
                                        cv::Size(80,80),
                                        cv::Size( std::min(resizedImage.rows,resizedImage.cols), std::min(resizedImage.rows,resizedImage.cols) ) ); // Size(240,240)
                if( fd->IsFaceDetected() )
                {
                    fd->CalcFaceKeyPoints();
                    double tmpScaleX = (double)iImage.cols/(double)resizedImage.cols;
                    double tmpScaleY = (double)iImage.rows/(double)resizedImage.rows;
                    cv::Rect rect = fd->GetDetectedFaceWindow();
                    ptLeftEyeCenter = fd->GetDetectedFaceKeyPoint(VO_KeyPoint::LEFTEYECENTER);
                    ptRightEyeCenter = fd->GetDetectedFaceKeyPoint(VO_KeyPoint::RIGHTEYECENTER);
                    ptMouthCenter = fd->GetDetectedFaceKeyPoint(VO_KeyPoint::MOUTHCENTER);
                    ptLeftEyeCenter.x *= tmpScaleX;
                    ptLeftEyeCenter.y *= tmpScaleY;
                    ptRightEyeCenter.x *= tmpScaleX;
                    ptRightEyeCenter.y *= tmpScaleY;
                    ptMouthCenter.x *= tmpScaleX;
                    ptMouthCenter.y *= tmpScaleY;
                
                    // Explained by JIA Pei, you can save to see the detection results.
//                    resizedImage.copyTo(drawImage);
//                    fd->VO_DrawDetection(drawImage, true, true, true, true, true);
//                    imwrite("drawImage.jpg", drawImage);
//                    imwrite("resizedImage.jpg", resizedImage);
//                    imwrite("iImage.jpg", iImage);
                    fitting2dsm->SetInputImage(iImage);
                    
                    
                    switch(fittingmtd)
                    {
                    case VO_AXM::AAM_BASIC:
                        {
                            fittingShape.clone(dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)->m_VOAAMBasic->GetAlignedMeanShape() );
                            fittingShape.Affine2D(  VO_Fitting2DSM::VO_FirstEstimationBySingleWarp(
                                                    dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)->m_VOAAMBasic->GetFaceParts(),
                                                    fittingShape,
                                                    ptLeftEyeCenter,
                                                    ptRightEyeCenter,
                                                    ptMouthCenter) );
                            fittingShape.ConstrainShapeInImage(iImage);

                            dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)
                                            ->VO_BasicAAMFitting(iImage,
                                                                fittingShape,
                                                                fittedImage,
                                                                VO_Fitting2DSM::EPOCH );
                        }
                        break;
                    case VO_AXM::AAM_DIRECT:
                        {
                            fittingShape.clone(dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)->m_VOAAMBasic->GetAlignedMeanShape() );
                            fittingShape.Affine2D(  VO_Fitting2DSM::VO_FirstEstimationBySingleWarp(
                                                    dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)->m_VOAAMBasic->GetFaceParts(),
                                                    fittingShape,
                                                    ptLeftEyeCenter,
                                                    ptRightEyeCenter,
                                                    ptMouthCenter) );
                            fittingShape.ConstrainShapeInImage(iImage);

                            dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)
                                            ->VO_DirectAAMFitting(iImage,
                                                                fittingShape,
                                                                fittedImage,
                                                                VO_Fitting2DSM::EPOCH );
                        }
                        break;
                    case VO_AXM::CLM:
                    case VO_AXM::AFM:
                        break;
                    case VO_AXM::AAM_IAIA:
                        {
                            fittingShape.clone(dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)->m_VOAAMInverseIA->GetAlignedMeanShape() );
                            fittingShape.Affine2D(  VO_Fitting2DSM::VO_FirstEstimationBySingleWarp(
                                                    dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)->m_VOAAMInverseIA->GetFaceParts(),
                                                    fittingShape,
                                                    ptLeftEyeCenter,
                                                    ptRightEyeCenter,
                                                    ptMouthCenter) );
                            fittingShape.ConstrainShapeInImage(iImage);

                            dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)
                                                ->VO_IAIAAAMFitting(iImage,
                                                                    fittingShape,
                                                                    fittedImage,
                                                                    VO_Fitting2DSM::EPOCH );
                        }
                        break;
                    case VO_AXM::AAM_CMUICIA:
                        {
                            fittingShape.clone(dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)->m_VOAAMInverseIA->GetAlignedMeanShape() );
                            fittingShape.Affine2D(  VO_Fitting2DSM::VO_FirstEstimationBySingleWarp(
                                                    dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)->m_VOAAMInverseIA->GetFaceParts(),
                                                    fittingShape,
                                                    ptLeftEyeCenter,
                                                    ptRightEyeCenter,
                                                    ptMouthCenter) );
                            fittingShape.ConstrainShapeInImage(iImage);

                            dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)
                                                ->VO_ICIAAAMFitting(iImage,
                                                                    fittingShape,
                                                                    fittedImage,
                                                                    VO_Fitting2DSM::EPOCH );
                        }
                        break;
                    case VO_AXM::AAM_FAIA:
                        break;
                    case VO_AXM::ASM_LTC:
                        {
                            fittingShape.clone(dynamic_cast<VO_FittingASMLTCs*>(fitting2dsm)->m_VOASMLTC->GetAlignedMeanShape() );
                            fittingShape.Affine2D(  VO_Fitting2DSM::VO_FirstEstimationBySingleWarp(
                                                    dynamic_cast<VO_FittingASMLTCs*>(fitting2dsm)->m_VOASMLTC->GetFaceParts(),
                                                    fittingShape,
                                                    ptLeftEyeCenter,
                                                    ptRightEyeCenter,
                                                    ptMouthCenter) );
                            fittingShape.ConstrainShapeInImage(iImage);

                            dynamic_cast<VO_FittingASMLTCs*>(fitting2dsm)
                                        ->VO_ASMLTCFitting( iImage,
                                                            fittingShape,
                                                            fittedImage,
                                                            VO_Features::DIRECT,
                                                            VO_Fitting2DSM::EPOCH,
                                                            3);    // change this 2 to 1 for 1D profile ASM
                        }
                        break;
                        case VO_AXM::ASM_PROFILEND:    // default, 2D Profile ASM
                        {
                            fittingShape.clone(dynamic_cast<VO_FittingASMNDProfiles*>(fitting2dsm)->m_VOASMNDProfile->GetAlignedMeanShape() );
                            fittingShape.Affine2D(  VO_Fitting2DSM::VO_FirstEstimationBySingleWarp(
                                                    dynamic_cast<VO_FittingASMNDProfiles*>(fitting2dsm)->m_VOASMNDProfile->GetFaceParts(),
                                                    fittingShape,
                                                    ptLeftEyeCenter,
                                                    ptRightEyeCenter,
                                                    ptMouthCenter)
                                                );
                            fittingShape.ConstrainShapeInImage(iImage);

                            dynamic_cast<VO_FittingASMNDProfiles*>(fitting2dsm)
                                        ->VO_ASMNDProfileFitting(   iImage,
                                                                    fittingShape,
                                                                    fittedImage,
                                                                    VO_Fitting2DSM::EPOCH,
                                                                    4,
                                                                    1);    // change this 2 to 1 for 1D profile ASM
                        }
                        break;
                    }
                    // Whenever the face is re-detected, initialize the tracker and set isTracked = true;
                    cv::Rect rect1 =    fittingShape.GetShapeBoundRect();
                    trackAlg->UpdateTracker(iImage, rect1);
                    isTracked =  true;
                }
            }
            else
            {
                switch(fittingmtd)
                {
                    case VO_AXM::AAM_BASIC:
                    {
                        dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)
                                        ->VO_BasicAAMFitting(iImage,
                                                            fittingShape,
                                                            fittedImage,
                                                            VO_Fitting2DSM::EPOCH);    
                    }
                    break;
                    case VO_AXM::AAM_DIRECT:
                    {
                        dynamic_cast<VO_FittingAAMBasic*>(fitting2dsm)
                                        ->VO_DirectAAMFitting(iImage,
                                                            fittingShape,
                                                            fittedImage,
                                                            VO_Fitting2DSM::EPOCH);    
                    }
                    break;
                    case VO_AXM::CLM:
                    case VO_AXM::AFM:
                    break;
                    case VO_AXM::AAM_IAIA:
                    {
                        dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)
                                        ->VO_IAIAAAMFitting(iImage,
                                                            fittingShape,
                                                            fittedImage,
                                                            VO_Fitting2DSM::EPOCH);                        
                    }
                    break;
                    case VO_AXM::AAM_CMUICIA:
                    {
                        dynamic_cast<VO_FittingAAMInverseIA*>(fitting2dsm)
                                        ->VO_ICIAAAMFitting(iImage,
                                                            fittingShape,
                                                            fittedImage,
                                                            VO_Fitting2DSM::EPOCH);    
                    }
                    break;
                    case VO_AXM::AAM_FAIA:
                    break;
                    case VO_AXM::ASM_LTC:
                    {
                        dynamic_cast<VO_FittingASMLTCs*>(fitting2dsm)
                                        ->VO_ASMLTCFitting( iImage,
                                                            fittingShape,
                                                            fittedImage,
                                                            VO_Features::DIRECT,
                                                            VO_Fitting2DSM::EPOCH,
                                                            3);
                    }
                    break;
                    case VO_AXM::ASM_PROFILEND:
                    {
                        dynamic_cast<VO_FittingASMNDProfiles*>(fitting2dsm)
                            ->VO_ASMNDProfileFitting(   iImage,
                                                        fittingShape,
                                                        fittedImage,
                                                        VO_Fitting2DSM::EPOCH,
                                                        4,
                                                        1);    // change this 2 to 1 for 1D profile ASM
                    }
                    break;
                }
                // Explained by JIA Pei. For every consequent image, whose previous image is regarded as tracked, 
                // we have to double-check whether current image is still a tracked one.
//                isTracked = true;
                isTracked = CRecognitionAlgs::EvaluateFaceTrackedByProbabilityImage(
                                                        trackAlg,
                                                        iImage,
                                                        fittingShape,
                                                        cv::Size(80,80),
                                                        cv::Size( std::min(iImage.rows,iImage.cols), std::min(iImage.rows,iImage.cols) ) );
            }

            nbOfIterations(0,i) = (float)(fitting2dsm->GetNbOfIterations());
            fittingShape = fitting2dsm->GetFittedShape();
            times(0,i) = fitting2dsm->GetFittingTime();
            

            if(record)
            {
                std::string fn = prefix+".jpg";
                cv::imwrite(fn.c_str(), fittedImage);
            }
            
            // For evaluation
            if(doEvaluation)
            {
                std::vector<float> ptErrorFreq;
                float deviation = 0.0f;
                std::vector<unsigned int> unsatisfiedPtList;
                unsatisfiedPtList.clear();
                CRecognitionAlgs::CalcShapeFittingEffect(   oShapes[i],
                                                            fittingShape,
                                                            deviation,
                                                            ptErrorFreq,
                                                            nb);
                deviations(0,i) = deviation;
                for(unsigned int j = 0; j < nb; j++)
                    ptsErrorFreq(i, j) = ptErrorFreq[j];
                CRecognitionAlgs::SaveShapeRecogResults("./",
                                                        prefix,
                                                        deviation,
                                                        ptErrorFreq);
            }
        }
        
        std::cout << "detection times = " << detectionTimes << std::endl;
        float avgIter = cv::mean(nbOfIterations).val[0];
        std::cout << avgIter << std::endl;
        float avgTime = cv::mean(times).val[0];
        std::cout << avgTime << std::endl;
        cv::Scalar avgDev, stdDev;
        cv::meanStdDev(deviations, avgDev, stdDev);
        std::cout << avgDev.val[0] << " " << stdDev.val[0] << std::endl << std::endl;
        std::vector<float> avgErrorFreq(nb, 0.0f);
        for(int j = 0; j < nb; j++)
        {
            cv::Mat_<float> col = ptsErrorFreq.col(j);
            avgErrorFreq[j] = cv::mean(col).val[0];
            std::cout << j << " " << avgErrorFreq[j] << std::endl;
        }
    }

    return 0;
}
