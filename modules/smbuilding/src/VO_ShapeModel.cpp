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
*                   4) I. cv::Matthews and S. Baker. Active appearance models revisited.            *
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


#include <fstream>
#include <string>
#include <set>
#include <algorithm>

#include "opencv/cvaux.h"
#include <boost/filesystem.hpp>
#include "VO_Triangle2DStructure.h"
#include "VO_ShapeModel.h"
#include "VO_CVCommon.h"
#include "VO_AnnotationDBIO.h"


/** Default Constructor */
VO_ShapeModel::VO_ShapeModel()
{
    this->init();
}


/** Initialization */
void VO_ShapeModel::init()
{
    this->m_iNbOfSamples                                    = 0;
	this->m_iNbOfShapeDim                                   = 0;
    this->m_iNbOfPoints                                     = 0;
    this->m_iNbOfShapes                                     = 0;
    this->m_iNbOfShapeEigens                            	= 0;
    this->m_iNbOfEigenShapesAtMost                          = 0;
	this->m_iNbOfEdges										= 0;
	this->m_iNbOfTriangles									= 0;
    this->m_fAverageShapeSize                               = 0.0f;
    this->m_fTruncatedPercent_Shape                         = 0.95f;
    this->m_vShapes.clear();
    this->m_vAlignedShapes.clear();
    this->m_vShape2DInfo.clear();
    this->m_vEdge.clear();
    this->m_vTemplateTriangle2D.clear();
    this->m_vNormalizedTriangle2D.clear();
}


/** Destructor */
VO_ShapeModel::~VO_ShapeModel()
{
    this->m_vShapes.clear();
    this->m_vAlignedShapes.clear();
    this->m_vShape2DInfo.clear();
    this->m_vEdge.clear();
    this->m_vTemplateTriangle2D.clear();
    this->m_vNormalizedTriangle2D.clear();
}



/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Align all shapes before PCA
 * @param	    vShapes         Input - all shapes before alignment
 * @param	    alignedShapes   Output - all shapes after alignment
 * @return     	float           return average shape size of all shapes
 * @note       	make sure all alignedShapes, meanshape as well, are of size "1" !!!
*/
float VO_ShapeModel::VO_AlignAllShapes(const std::vector<VO_Shape>& vShapes, std::vector<VO_Shape>& alignedShapes)
{
    unsigned int NbOfSamples    	= vShapes.size();
    unsigned int NbOfAnglesDim  	= (vShapes[0].GetNbOfDim() == 2) ? 1:3;		// 3 or 2, if 2, change to 1
    float averageShapeSize      	= 0.0f;
    alignedShapes 					= vShapes;

	//////////////////////////////////////////////////////////////////////////////////////
	// First estimation is mean of all VO_Shape
    VO_Shape meanAlignedShape;
    for(unsigned int i = 0; i < NbOfSamples; ++i)
    {
		averageShapeSize += alignedShapes[i].GetCentralizedShapeSize();
        alignedShapes[i].Normalize();
    }
    averageShapeSize /= (float)NbOfSamples;    	// Why this is the average shape size without minor errors?
												// Because later do-while loop doesn't change the normalized shape size
    VO_ShapeModel::VO_CalcMeanShape( alignedShapes, meanAlignedShape );
	//////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////
	// iterative Procrustes Analysis
    // do a number of alignment iterations until the mean shape estimate is stable
    float diff, diff_max = FLT_EPSILON;
    int max_iter = 10, iter = 1;
    VO_Shape tempMeanShape;
    std::vector<float> theta, angles;
    theta.resize( NbOfAnglesDim );
    angles.resize(NbOfAnglesDim);
    cv::Mat_<float> rots = cv::Mat_<float>::zeros(NbOfAnglesDim, NbOfSamples);

    do
    {
        // normalize and align all other shapes to the mean shape estimate
        for(unsigned int i=0;i < NbOfSamples;i++)
        {
            // align the i-th shape to the estimate of the mean shape
            alignedShapes[i].AlignTo( meanAlignedShape, NULL, &theta, NULL );
            for(unsigned int j = 0; j < NbOfAnglesDim; ++j)
                rots(j,i)  = theta[j];  // record the rotation
			
            // re-scale to unit size to avoid the so-called 'shrinking effect'
            // i.e. the alignment error goes towards zero, when the shapes are downscaled
            alignedShapes[i].Scale( 1.0f/alignedShapes[i].GetShapeNorm () );
        }
        tempMeanShape = meanAlignedShape;
        // estimate the new mean shape
        VO_ShapeModel::VO_CalcMeanShape( alignedShapes, meanAlignedShape );

        // if first iteration, adjust the orientation of the mean shape, so the rotation of the training set to the mean shape is
        // -- on average -- zero or put more clearly: "make the meanshape have a mean orientation"
        if (iter==1)
        {
            for(unsigned int k = 0; k < NbOfAnglesDim; ++k)
            {
                angles[k] = cv::mean( rots.row(k) ).val[0];
            }
            meanAlignedShape.Rotate ( angles );
        }

        diff = (tempMeanShape-meanAlignedShape).GetShapeNorm();
	
        ++iter;

    }while( fabs(diff)/meanAlignedShape.GetShapeNorm() > diff_max && iter < max_iter );	
	
	//////////////////////////////////////////////////////////////////////////////////////
    return averageShapeSize;
}


/**
 * @author     JIA Pei
 * @version    2010-02-07
 * @brief      Rescale the alignedshapes so that meanshape's 2-norm could be "1"
 * @param      meanAlignedShape    Input - meanalignedshape that all alignedshapes should rescale to
 * @param      alignedShapes       Input and Output - aligned shape and aligned rescaled shape
*/
void VO_ShapeModel::VO_RescaleAllAlignedShapes(const VO_Shape& meanAlignedShape,
                                                std::vector<VO_Shape>& alignedShapes)
{
    unsigned int NbOfSamples = alignedShapes.size();

    // Explained by JIA Pei. 2010-02-07. scale back so that the mean shape size is equal to 1.0
    for(unsigned int i = 0; i < NbOfSamples; i++)
    {
        VO_ShapeModel::VO_RescaleOneAlignedShape(meanAlignedShape, alignedShapes[i]);
    }
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Rescale the alignedShape to the already trained meanAligneShape
 * @param      	meanAlignedShape    Input - meanalignedshape that all alignedshapes should rescale to
 * @param      	alignedShape        Input and Output - aligned shape and aligned rescaled shape
 * @return		void
*/
void VO_ShapeModel::VO_RescaleOneAlignedShape(const VO_Shape& meanAlignedShape, VO_Shape& alignedShape)
{
    float ts = sqrt ( fabs(alignedShape.dot(meanAlignedShape) ) );
    alignedShape.Scale( 1.0f/ts );
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Calculate mean shape
 * @param      	vShapes     		Input - all shapes
 * @param      	meanShape   		Output - mean shape
 * @return 		void
*/
void VO_ShapeModel::VO_CalcMeanShape(const std::vector<VO_Shape>& vShapes, VO_Shape& meanShape)
{
    unsigned int NbOfSamples    = vShapes.size();
    meanShape = vShapes[0];

    for(unsigned int i = 1; i < NbOfSamples; i++)
    {
        meanShape += vShapes[i];
    }

    meanShape /= (float)NbOfSamples;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Judge is point "pt" inside the convex hull "ch"
 * @param      	pt              	Input - the point
 * @param      	ch              	Input - convex hull
 * @param      	includingHull		Input flag - whether including the boundary
 * @return     	bool            	including or excluding
*/
bool VO_ShapeModel::VO_IsPointInConvexHull(const cv::Point2f pt, const cv::Mat_<float>& ch, bool includingHull)
{
    if(!includingHull)
    {
        if (cv::pointPolygonTest( ch, pt, true ) > 0.0 )
            return true;
    }
    else
    {
        if (cv::pointPolygonTest( ch, pt, true ) >= 0.0)
            return true;
    }

    return false;
}


/**
 * @author		JIA Pei
 * @version    	2010-02-07
 * @brief      	Judge whether edge indexed by (ind1+ind2) is already in the std::vector of "edges"
 * @param      	edges           	edge collection
 * @param      	ind1            	first index of the edge to be judged
 * @param      	ind2	        	second index of the edge to be judged
 * @return     	bool            	counted or not
*/
bool VO_ShapeModel::VO_EdgeHasBeenCounted(const std::vector<VO_Edge>& edges, unsigned int ind1, unsigned int ind2)
{
    unsigned int NbOfEdges = edges.size ();
    for (unsigned int i = 0; i < NbOfEdges; i++)
    {
        if ( ( (edges[i].GetIndex1() == ind1) && (edges[i].GetIndex2() == ind2) )
            || ( (edges[i].GetIndex1() == ind2) && (edges[i].GetIndex2() == ind1) ) )
        {
            return true;
        }
    }

    return false;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Judge whether triangle t is already in the std::vector of "triangles".
 * @param      	triangles       triangle collection
 * @param      	t               the triangle to be judged
 * @return		bool			whether the triangle "t" has been counted or not
*/
bool VO_ShapeModel::VO_TriangleHasBeenCounted(const std::vector<VO_Triangle2DStructure>& triangles, const std::vector<unsigned int>& t)
{
    std::set<unsigned int> tTriangle;
    std::set<unsigned int> sTriangle;
    unsigned int NbOfTriangles = triangles.size ();

    for (unsigned int i = 0; i < NbOfTriangles; i ++)
    {
        // These two clear() are very important, cannot be displaced by empty().
        tTriangle.clear ();
        sTriangle.clear ();
        for (unsigned int j = 0; j < 3; j++ )
        {
            tTriangle.insert (triangles[i].GetVertexIndex(j) );
            sTriangle.insert (t[j]);
        }
        if (tTriangle == sTriangle)
        {
            return true;	// has been counted already
        }
    }

    return false;			// not counted yet
}


/**
 * @author    	JIA Pei
 * @version    	2010-02-07
 * @brief      	Build Edges
 * @param      	iShape              Input - all vertexes/points composing the shape
 * @param      	Subdiv              Input - sub division which is already computed beforehand
 * @param      	outEdges	        Output - edges
 * @return     	unsigned int        Number of edges
*/
//unsigned int VO_ShapeModel::VO_BuildEdges(const VO_Shape& iShape, const CvSubdiv2D* subdiv, std::vector<VO_Edge>& outEdges)
//{
//    unsigned int NbOfPoints = iShape.GetNbOfPoints();
//    CvSeqReader  reader;

//    cvStartReadSeq( (CvSeq*)(Subdiv->edges), &reader, 0 );

//    for( unsigned int i = 0; i < Subdiv->edges->total; i++ )
//    {
//        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);

//        if( CV_IS_SET_ELEM( edge ))
//        {
//            cv::Point2f org;
//            cv::Point2f dst;

//            CvSubdiv2DPoint* org_pt = cvSubdiv2DEdgeOrg((CvSubdiv2DEdge)edge);
//            CvSubdiv2DPoint* dst_pt = cvSubdiv2DEdgeDst((CvSubdiv2DEdge)edge);

//            if( org_pt && dst_pt )
//            {
//                org = org_pt->pt;
//                dst = dst_pt->pt;

//                for (unsigned int j = 0; j < NbOfPoints; j++)
//                {
//                    // if the current edge convex (org points, not the dst point) is in our point list
//                    if ( (fabs ( org.x - iShape.GetACol(j)(0, 0) ) < FLT_EPSILON )
//                        && ( fabs ( org.y - iShape.GetACol(j)(1, 0) ) < FLT_EPSILON ) )
//                    {
//                        for (unsigned int k = 0; k < NbOfPoints; k++)
//                        {
//                            // With the above org point, we search around for the dst point(s),
//                            // which make org-dst an edge during cvSubdivDelaunay2DInsert()
//                            if ( ( fabs (dst.x - iShape.GetACol(k)(0, 0) ) < FLT_EPSILON )
//                                && ( fabs (dst.y - iShape.GetACol(k)(1, 0) ) < FLT_EPSILON ) )
//                            {
//                                // Already tested, this->m_vEdge is definitely correct!
//                                outEdges.push_back ( VO_Edge(j,k) );
//                            }
//                        }
//                    }
//                }
//            }
//        }

//        CV_NEXT_SEQ_ELEM( Subdiv->edges->elem_size, reader );
//    }

//    return outEdges.size();
//}


/**
 * @author  JIA Pei
 * @version 2014-04-18
 * @brief   VO_ShapeModel::VO_BuildEdges
 * @param   iShape              Input - all vertexes/points composing the shape
 * @param   Subdiv              Input - sub division which is already computed beforehand
 * @param   outEdges            Output - edges
 * @return  unsigned int        Number of edges
 */
unsigned int VO_ShapeModel::VO_BuildEdges(const VO_Shape& iShape, const cv::Subdiv2D& subdiv, std::vector<VO_Edge>& outEdges)
{
    unsigned int NbOfPoints = iShape.GetNbOfPoints();
    std::vector<cv::Vec4f> edgeList;
    subdiv.getEdgeList(edgeList);
    for( unsigned int i = 0; i < edgeList.size(); i++ )
    {
        cv::Vec4f e = edgeList[i];
        cv::Point2f org = cv::Point2f(e[0], e[1]);
        cv::Point2f dst = cv::Point2f(e[2], e[3]);

        for (unsigned int j = 0; j < NbOfPoints; j++)
        {
            // if the current edge convex (org points, not the dst point) is in our point list
            if ( (fabs ( org.x - iShape.GetACol(j)(0, 0) ) < FLT_EPSILON )
                && ( fabs ( org.y - iShape.GetACol(j)(1, 0) ) < FLT_EPSILON ) )
            {
                for (unsigned int k = 0; k < NbOfPoints; k++)
                {
                    // With the above org point, we search around for the dst point(s),
                    // which make org-dst an edge during cvSubdivDelaunay2DInsert()
                    if ( ( fabs (dst.x - iShape.GetACol(k)(0, 0) ) < FLT_EPSILON )
                        && ( fabs (dst.y - iShape.GetACol(k)(1, 0) ) < FLT_EPSILON ) )
                    {
                        // Already tested, this->m_vEdge is definitely correct!
                        outEdges.push_back ( VO_Edge(j,k) );
                    }
                }
            }
        }
    }

    return 0;
}

/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Build AAM Triangles
 * @param      	iShape               	Input 	- the input shape
 * @param      	edges               	Input 	- to built edges
 * @param		outTriangles			Output	- the output triangles
 * @return     	unsigned int          	Number of triangles
*/
unsigned int VO_ShapeModel::VO_BuildTriangles(  const VO_Shape& iShape,
                                                const std::vector<VO_Edge>& edges,
                                                std::vector<VO_Triangle2DStructure>& outTriangles)
{
    outTriangles.clear();
    unsigned int NbOfEdges 	= edges.size ();
    unsigned int NbOfPoints = iShape.GetNbOfPoints();
	
    for (unsigned int i = 0; i < NbOfEdges; i++)
    {
        unsigned int ind1 = edges[i].GetIndex1();
        unsigned int ind2 = edges[i].GetIndex2();

        for (unsigned int j = 0; j < NbOfPoints; j++)
        {
            // For each edge, there are at most 2 triangles that could be added
            if( VO_ShapeModel::VO_EdgeHasBeenCounted(edges, ind1, j) && VO_ShapeModel::VO_EdgeHasBeenCounted(edges, ind2, j) )
            {
                std::vector<unsigned int> iVertexes;
                iVertexes.resize (3);
                iVertexes[0] = ind1;
                iVertexes[1] = ind2;
                iVertexes[2] = j;
				// If the triangle has not been counted yet
                if (!VO_ShapeModel::VO_TriangleHasBeenCounted(outTriangles, iVertexes) )
                {
                    cv::Mat_<float> vVertexes = iShape.GetSubShape(iVertexes).GetTheShape();
					// Note: Explained by JIA Pei, 2009-08-09, triangle vertex sequence should be adjusted here
					VO_Triangle2DStructure temp(vVertexes, iVertexes);
					temp.AdjustVertexSequence();
                    outTriangles.push_back (temp);
                }
            }
        }
    }

    return outTriangles.size();
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Calculation triangulation mesh
				For IMM 58 points dataset, 19 edges on the convex hull, 133 inner edges.
				Totally, 133+19=152 edges
				(133*2+19)/3=95 triangles
 * @param		iShape			Input	- the input shape
 * @param		edges			Input	- the constructed edges
 * @param		triangles		Input	- the constructed triangles
 * @return		void
*/
//void VO_ShapeModel::VO_BuildTemplateMesh(const VO_Shape& iShape,
//                                        std::vector<VO_Edge>& edges,
//                                        std::vector<VO_Triangle2DStructure>& triangles )
//{
//    unsigned int NbOfPoints = iShape.GetNbOfPoints();

//    //////////////////////////////////////////////////////////////////////////
//    // Build Delaunay Triangulation Sub Divisions
//    // Later VO_BuildEdges need DTSubdiv information
//    CvSubdiv2D* tempCVSubdiv = NULL;

//    cv::Rect rect = iShape.GetShapeBoundRect();

//    CvMemStorage* DelaunayStorage = cvCreateMemStorage(0);

//    // By JIA Pei, 2006-09-20. How to release this storage?
//    tempCVSubdiv = cvCreateSubdivDelaunay2D( rect, DelaunayStorage );

//    for( unsigned int i = 0; i < NbOfPoints; i++ )
//    {
//        cv::Point2f onePoint = iShape.GetA2DPoint(i);
//        cvSubdivDelaunay2DInsert( tempCVSubdiv, onePoint);
//    }
//    //////////////////////////////////////////////////////////////////////////

//    unsigned int NbOfEdges = VO_ShapeModel::VO_BuildEdges(iShape, tempCVSubdiv, edges);
//    unsigned int NbOfTriangles = VO_ShapeModel::VO_BuildTriangles (iShape, edges, triangles);

//    // How to release CvSubdiv2D* m_CVSubdiv is still a problem.
//    if (tempCVSubdiv)   cvClearSubdivVoronoi2D( tempCVSubdiv );
//    cvReleaseMemStorage( &DelaunayStorage );
//}

void VO_ShapeModel::VO_BuildTemplateMesh(const VO_Shape& iShape,
                                        std::vector<VO_Edge>& edges,
                                        std::vector<VO_Triangle2DStructure>& triangles )
{
    unsigned int NbOfPoints = iShape.GetNbOfPoints();

    //////////////////////////////////////////////////////////////////////////
    // Build Delaunay Triangulation Sub Divisions
    // Later VO_BuildEdges need DTSubdiv information
    cv::Rect rect = iShape.GetShapeBoundRect();
    cv::Subdiv2D tempCVSubdiv(rect);

    for( unsigned int i = 0; i < NbOfPoints; i++ )
    {
        cv::Point2f onePoint = iShape.GetA2DPoint(i);
        tempCVSubdiv.insert(onePoint);
    }
    //////////////////////////////////////////////////////////////////////////

    unsigned int NbOfEdges = VO_ShapeModel::VO_BuildEdges(iShape, tempCVSubdiv, edges);
    unsigned int NbOfTriangles = VO_ShapeModel::VO_BuildTriangles (iShape, edges, triangles);

}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Calculation triangulation mesh
				For IMM 58 points dataset, 19 edges on the convex hull, 133 inner edges.
				Totally, 133+19=152 edges
				(133*2+19)/3=95 triangles
 * @param		iShape			Input	- the input shape
 * @param		iFaceParts		Input	- face parts
 * @param		edges			Input	- the constructed edges
 * @param		triangles		Input	- the constructed triangles
*/
void VO_ShapeModel::VO_BuildTemplateMesh(const VO_Shape& iShape, 
										const VO_FaceParts& iFaceParts, 
                                        std::vector<VO_Edge>& edges,
                                        std::vector<VO_Triangle2DStructure>& triangles )
{
    cv::Mat_<float> vVertexes;
    unsigned int NbOfPoints 				= iShape.GetNbOfPoints();

    std::vector< std::vector < unsigned int > > ti 	= iFaceParts.GetTriangleIndexes();
    unsigned int NbOfTriangles 				= ti.size();

    triangles.resize(NbOfTriangles);
    for(unsigned int i = 0; i < NbOfTriangles; ++i)
    {
        vVertexes 		= iShape.GetSubShape(ti[i]).GetTheShape();
        triangles[i] 	= VO_Triangle2DStructure(vVertexes, ti[i]);

        if( !VO_ShapeModel::VO_EdgeHasBeenCounted(edges, ti[i][0], ti[i][1]) )
            edges.push_back( VO_Edge(ti[i][0], ti[i][1]) );

        if( !VO_ShapeModel::VO_EdgeHasBeenCounted(edges, ti[i][0], ti[i][2]) )
            edges.push_back( VO_Edge(ti[i][0], ti[i][2]) );

        if( !VO_ShapeModel::VO_EdgeHasBeenCounted(edges, ti[i][1], ti[i][2]) )
            edges.push_back( VO_Edge(ti[i][1], ti[i][2]) );
    }
}


/**
 * @author     	JIA Pei
 * @version   	2010-02-07
 * @brief     	Is iShape inside img
 * @param		iShape			Input	- the input shape
 * @param		img				Input	- the image
 * @return    	bool
*/
bool VO_ShapeModel::VO_IsShapeInsideImage(const VO_Shape& iShape, const cv::Mat& img)
{
    cv::Rect_<float> rect = iShape.GetShapeRect();

    // The following line should be avoided. explained by JIA Pei. Try the second line!
    //if ( (rect.x > 0) && (rect.y > 0) && ( (rect.x + rect.width) <= img.cols ) && ( (rect.y + rect.height) <= img.rows ) )
    if ( (rect.x >= 0.0) && (rect.y >= 0.0) && ( (rect.x + rect.width) < (float)img.cols - 1.0f -  FLT_EPSILON ) && ( (rect.y + rect.height) < (float)img.rows - 1.0f - FLT_EPSILON ) )
        return true;
    else
        return false;
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Reference scale texture back to aligned one
 * @param      	inShape         Input 	- reference shape
 * @param      	shapeSD         Input 	- shape standard deviation
 * @param      	outShape        Output 	- output aligned shape
 * @return		void
*/
void VO_ShapeModel::VO_ReferenceShapeBack2Aligned(const VO_Shape& inShape, float shapeSD, VO_Shape& outShape)
{
    outShape 			= inShape;
    cv::Mat_<float> center 	= outShape.CenterOfGravity( );		// centralize first
    outShape.Translate( -center );
	outShape.Scale(1.0f/shapeSD );							// scale second
	// note: no rotation!!!
}


/**
 * @author		JIA Pei
 * @version		2010-02-09
 * @brief		calculate the boundary rectangle of a list of triangles
 * @param		triangles	    	Input - A list of triangles
 * @return		cv::Rect				the boundary rectangle.
*/
cv::Rect VO_ShapeModel::VO_CalcBoundingRectFromTriangles(const std::vector <VO_Triangle2DStructure>& triangles)
{
	VO_Shape shape = VO_Triangle2DStructure::Triangle2D2Shape(triangles);

    return shape.GetShapeBoundRect();
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	shape parameters constrain
 * @param      	ioP				Input and Output - shape parameters
 * @param      	nSigma          Input - number of sigmas
 * @return		void
*/
void VO_ShapeModel::VO_ShapeParameterConstraint(cv::Mat_<float>& ioP, float nSigma)
{
    for (unsigned int i = 0; i < ioP.cols; ++i)
    {
		float ct = nSigma * sqrt(this->m_PCAAlignedShape.eigenvalues.at<float>(i,0) );
        if ( ioP(0, i) > ct )
        {
            ioP(0, i) = ct;
        }
        else if ( ioP(0, i) < -ct )
        {
            ioP(0, i) = -ct;
        }
    }
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	aligned shape project to shape parameters
 * @param      	inP             Input 	- input shape
 * @param      	oShape          Output 	- the projected shape parameters
 * @return		void
*/
void VO_ShapeModel::VO_AlignedShapeProjectToSParam(const VO_Shape& iShape, cv::Mat_<float>& outP) const
{
	this->m_PCAAlignedShape.project(iShape.GetTheShapeInARow(), outP);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	shape parameters back project to aligned shape
 * @param      	inP             Input 	- input shape parameters
 * @param      	oShape          Output 	- the back projected shape
 * @param		dim				dim		- input
 * @return		void
*/
void VO_ShapeModel::VO_SParamBackProjectToAlignedShape(const cv::Mat_<float>& inP, VO_Shape& oShape, int dim) const
{
	oShape.SetTheShape(this->m_PCAAlignedShape.backProject(inP), dim);
}

/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	shape parameters back project to aligned shape
 * @param      	inP             Input 	- input shape parameters
 * @param      	oShapeMat       Output 	- the back projected shape in a row matrix
 * @return		void
*/
void VO_ShapeModel::VO_SParamBackProjectToAlignedShape(const cv::Mat_<float>& inP, cv::Mat_<float>& oShapeMat) const
{
    oShapeMat = this->m_PCAAlignedShape.backProject(inP);
}

/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Calculate all parameters for an arbitrary shape
 * @param      	iShape			Input 	- 	the reference shape
 * @param		oShape			Output	-	output shape
 * @param      	outP            Output 	- 	shape parameters
 * @param      	norm            Output 	- 	2-norm, scaling
 * @param      	angle		    Output 	- 	rotation in 2D
 * @param      	translation     Output 	- 	translation
 * @return		void
*/
void VO_ShapeModel::VO_CalcAllParams4AnyShapeWithConstrain(	const cv::Mat_<float>& iShape,
                                                            cv::Mat_<float>& oShape,
                                                            cv::Mat_<float>& outP,
															float& norm,
                                                            std::vector<float>& angles,
                                                            cv::Mat_<float>& translation )
{
	VO_Shape oS(iShape, this->m_iNbOfShapeDim);
	oS.ProcrustesAnalysis( this->m_VOAlignedMeanShape, norm, angles, translation );
	this->VO_AlignedShapeProjectToSParam(oS, outP);
	this->VO_ShapeParameterConstraint(outP);
    this->VO_SParamBackProjectToAlignedShape(outP, oS, this->m_iNbOfShapeDim);
	oS.InverseProcrustesAnalysis( norm, angles, translation );
	oShape = oS.GetTheShapeInARow();
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Calculate all parameters for an arbitrary shape
 * @param      	iShape        	Input 	- 	the input shape
 * @param		oShape			Output	-	output shape
 * @param      	outP            Output 	- 	shape parameters, a 1*m_iNbOfShapeDim row std::vector
 * @param      	outQ            Output 	- 	similarity transform parameters, a 1*4 row std::vector
 * @return		void
*/
//void VO_ShapeModel::VO_CalcAllParams4AnyShapeWithConstrain(	const cv::Mat_<float>& iShape,
//															cv::Mat_<float>& oShape,
//															cv::Mat_<float>& outP,
//															cv::Mat_<float>& outQ )
//{
//	float norm;
//	std::vector<float> angles;
//	cv::Mat_<float> translation;
//
//	this->VO_CalcAllParams4AnyShapeWithConstrain(	iShape,
//													oShape,
//													outP,
//													norm,
//													angles,
//													translation );
//	VO_Shape::SimilarityTrans2GlobalShapeNormalization(norm, -angles, translation, outQ);
//}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Calculate all parameters for an arbitrary shape
 * @param      	ioShape			Input and output 	- input/output shape
 * @param      	outP            Output 	- shape parameters
 * @param      	norm            Output 	- 2-norm, scaling
 * @param      	angles          Output 	- rotation
 * @param      	translation    	Output 	- translation
 * @return		void
*/
void VO_ShapeModel::VO_CalcAllParams4AnyShapeWithConstrain( VO_Shape& ioShape, 
                                                            cv::Mat_<float>& outP,
															float& norm, 
                                                            std::vector<float>& angles,
                                                            cv::Mat_<float>& translation )
{
    ioShape.ProcrustesAnalysis( this->m_VOAlignedMeanShape, norm, angles, translation );
	this->VO_AlignedShapeProjectToSParam(ioShape, outP);
	this->VO_ShapeParameterConstraint(outP);
    this->VO_SParamBackProjectToAlignedShape(outP, ioShape, ioShape.GetNbOfDim());
    ioShape.InverseProcrustesAnalysis( norm, angles, translation );
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Calculate all parameters for an arbitrary shape
 * @param      	ioShape			Input and output 	- input/output shape
 * @param      	outP            Output -- shape parameters
 * @param      	outQ			Output -- similarity transform parameters
 * @return		void
*/
//void VO_ShapeModel::VO_CalcAllParams4AnyShapeWithConstrain(VO_Shape& ioShape, cv::Mat_<float>& outP, cv::Mat_<float>& outQ )
//{
//	float norm;
//	std::vector<float> angles;
//	cv::Mat_<float> translation;
//
//	this->VO_CalcAllParams4AnyShapeWithConstrain(	ioShape,
//													outP,
//													norm,
//													angles,
//													translation );
//	VO_Shape::SimilarityTrans2GlobalShapeNormalization(norm, -angles, translation, outQ);
//}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	Build up a shape from all rigid and non-rigid parameters
 * @param      	inP            	Input -- shape parameters, for nonrigid
 * @param      	inQ				Input -- similarity transform parameters, for rigid
 * @param      	oShape			output -- output shape
 * @return		void
*/
//void VO_ShapeModel::VO_BuildUpShapeFromRigidNonRigidParams(const cv::Mat_<float>& inP, const cv::Mat_<float>& inQ, VO_Shape& oShape )
//{
//	float norm;
//	std::vector<float> angles;
//	cv::Mat_<float> translation;
//	
//	this->VO_SParamBackProjectToAlignedShape(inP, oShape, 2);
////	VO_Shape::GlobalShapeNormalization2SimilarityTrans(inQ, norm, angles, translation);
////	oShape.InverseProcrustesAnalysis( norm, angles, translation );
//	oShape.GlobalShapeNormalization2D(inQ);
//}


/**
 * @author     	JIA Pei
 * @version    	2010-02-07
 * @brief      	build shape model
 * @param      	allLandmarkFiles4Training		Input - all landmark files
 * @param      	shapeinfoFileName				Input - shape info file
 * @param		database						Input - which database is it?
 * @param      	TPShape     					Input - truncated percentage for shape model
 * @param      	useKnownTriangles  				Input - use known triangle structures??
 * @return		void
*/
void VO_ShapeModel::VO_BuildShapeModel(const std::vector<std::string>& allLandmarkFiles4Training,
										const std::string& shapeinfoFileName, 
										unsigned int database,
										float TPShape, 
										bool useKnownTriangles)
{
	// load auxiliary shape information
	VO_Shape2DInfo::ReadShape2DInfo(shapeinfoFileName, this->m_vShape2DInfo, this->m_FaceParts);
	CAnnotationDBIO::VO_LoadShapeTrainingData( allLandmarkFiles4Training, database, this->m_vShapes);

    this->m_iNbOfSamples            			= this->m_vShapes.size();
    this->m_iNbOfShapeDim           			= this->m_vShapes[0].GetNbOfDim();
    this->m_iNbOfPoints             			= this->m_vShapes[0].GetNbOfPoints();
    this->m_iNbOfShapes             			= this->m_iNbOfShapeDim * this->m_iNbOfPoints;
	this->m_iNbOfEigenShapesAtMost 				= MIN(this->m_iNbOfSamples, this->m_iNbOfShapes);
    this->m_fTruncatedPercent_Shape 			= TPShape;
    cv::Mat_<float> matAlignedShapes			= cv::Mat_<float>::zeros(this->m_iNbOfSamples, this->m_iNbOfShapes);
    //cv::Mat_<float> matAlignedMeanShape			= cv::Mat_<float>::zeros(1, this->m_iNbOfShapes);

    // Align all shapes
    this->m_fAverageShapeSize = VO_ShapeModel::VO_AlignAllShapes(this->m_vShapes, this->m_vAlignedShapes);
    VO_ShapeModel::VO_CalcMeanShape(this->m_vAlignedShapes, this->m_VOAlignedMeanShape);

	// Calculate reference shape
	this->m_VOReferenceShape 					= this->m_VOAlignedMeanShape*this->m_fAverageShapeSize;
    cv::Mat_<float> refMin 						= this->m_VOReferenceShape.Min();
    this->m_VOReferenceShape.Translate( -refMin );

	//////////////////////////////////////////////////////////////////////////
    // Build VO_Point2DDistributionModel /////////////////////////////////////
    this->m_VOPDM.VO_BuildPointDistributionModel(this->m_vAlignedShapes);
	//////////////////////////////////////////////////////////////////////////

    //matAlignedMeanShape = this->m_VOAlignedMeanShape.GetTheShapeInARow();
    for(unsigned int i = 0; i < this->m_iNbOfSamples; i++)
	{
        cv::Mat_<float> shapeInARow = this->m_vAlignedShapes[i].GetTheShapeInARow();

        for(unsigned int j = 0; j < this->m_iNbOfShapes; j++)
        {
            matAlignedShapes.at<float>(i,j) = shapeInARow.at<float>(0,j);
        }
	}
//    // Modifed by Pei JIA, 2014-05-07. PCA changed after OpenCV 2.4.9
//    //this->m_PCAAlignedShape = cv::PCA(matAlignedShapes, cv::Mat(), CV_PCA_DATA_AS_ROW, (int)(this->m_iNbOfEigenShapesAtMost) );
//    this->m_PCAAlignedShape = cv::PCA(matAlignedShapes, matAlignedMeanShape, CV_PCA_USE_AVG, (int)(this->m_iNbOfEigenShapesAtMost) );
//	// to decide how many components to be selected
//    this->m_iNbOfShapeEigens = 0;

//    double SumOfEigenValues = cv::sum( this->m_PCAAlignedShape.eigenvalues ).val[0];
//    double ps = 0.0f;

//    for(unsigned int i = 0; i < this->m_iNbOfEigenShapesAtMost; i++)
//    {
//        ps += this->m_PCAAlignedShape.eigenvalues.at<float>( i,0 );
//        ++this->m_iNbOfShapeEigens;
//        if( ps/SumOfEigenValues >= this->m_fTruncatedPercent_Shape) break;
//    }
//	// m_iNbOfShapeEigens decided. For simplicity, we carry out PCA once again.
//    // Modifed by Pei JIA, 2014-05-07. PCA changed after OpenCV 2.4.9
//    //this->m_PCAAlignedShape = cv::PCA(matAlignedShapes, cv::Mat(), CV_PCA_DATA_AS_ROW, (int)(this->m_iNbOfShapeEigens) );
//    this->m_PCAAlignedShape = cv::PCA(matAlignedShapes, matAlignedMeanShape, CV_PCA_USE_AVG, (int)(this->m_iNbOfShapeEigens) );
    this->m_PCAAlignedShape = cv::PCA(matAlignedShapes, cv::Mat(), CV_PCA_DATA_AS_ROW, (double)(this->m_fTruncatedPercent_Shape) );
    this->m_iNbOfShapeEigens = this->m_PCAAlignedShape.eigenvalues.rows;

    //////////////////////////////////////////////////////////////////////////
    // Calculate template shape mesh
    //////////////////////////////////////////////////////////////////////////
    if (this->m_FaceParts.GetTriangleIndexes().size() != 0)
        useKnownTriangles = true;
    else
        useKnownTriangles = false;
    if( !useKnownTriangles )
        VO_ShapeModel::VO_BuildTemplateMesh(this->m_VOReferenceShape, this->m_vEdge, this->m_vTemplateTriangle2D );
    else
        VO_ShapeModel::VO_BuildTemplateMesh(this->m_VOReferenceShape, this->m_FaceParts, this->m_vEdge, this->m_vTemplateTriangle2D );

	this->m_iNbOfEdges = this->m_vEdge.size();
	this->m_iNbOfTriangles = this->m_vTemplateTriangle2D.size();
	
    // 2) Calculate m_vNormalizedTriangle2D - make sure the mesh has been built first, so that we have m_iNbOfTriangles
    std::vector<cv::Point2f> tempVertexes;
    std::vector<unsigned int> iVertexes;
    tempVertexes.resize(3);
    cv::Mat_<float> threePoints;

    for (unsigned int i = 0; i < this->m_iNbOfTriangles; i++)
    {
        iVertexes = this->m_vTemplateTriangle2D[i].GetVertexIndexes();
        threePoints = this->m_VOAlignedMeanShape.GetSubShape(iVertexes).GetTheShape();
		for(unsigned int j = 0; j < 3; j++)
            tempVertexes[j] = cv::Point2f(threePoints.at<float>(0, j), threePoints.at<float>(1,j));

        this->m_vNormalizedTriangle2D.push_back (VO_Triangle2DStructure(tempVertexes, iVertexes));
    }
}


/**
 * @author     JIA Pei
 * @version    2010-02-22
 * @brief      Save ASM to a specified folder
 * @param      fd         	Input - the folder that ASM to be saved to
*/
void VO_ShapeModel::VO_Save(const std::string& fd)
{
    // create ShapeModel subfolder for just ShapeModel data
    std::string fn = fd+"/ShapeModel";
    if (!boost::filesystem::is_directory(fn) )
        boost::filesystem::create_directory( fn );

    std::fstream fp;
    std::string tempfn;

    // ShapeModel
    tempfn = fn + "/ShapeModel" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_iNbOfSamples" << std::endl << this->m_iNbOfSamples << std::endl;							// m_iNbOfSamples
    fp << "m_iNbOfShapeDim" << std::endl << this->m_iNbOfShapeDim << std::endl;						// m_iNbOfShapeDim
    fp << "m_iNbOfPoints" << std::endl << this->m_iNbOfPoints << std::endl;							// m_iNbOfPoints
    fp << "m_iNbOfShapes" << std::endl << this->m_iNbOfShapes << std::endl;							// m_iNbOfShapes
    fp << "m_iNbOfEigenShapesAtMost" << std::endl << this->m_iNbOfEigenShapesAtMost << std::endl;		// m_iNbOfEigenShapesAtMost
    fp << "m_iNbOfShapeEigens" << std::endl << this->m_iNbOfShapeEigens << std::endl;					// m_PCAAlignedShape
    fp << "m_iNbOfEdges" << std::endl << this->m_iNbOfEdges << std::endl;								// m_iNbOfEdges
    fp << "m_iNbOfTriangles" << std::endl << this->m_iNbOfTriangles << std::endl;						// m_iNbOfTriangles
    fp << "m_fAverageShapeSize" << std::endl << this->m_fAverageShapeSize << std::endl;				// m_fAverageShapeSize
    fp << "m_fTruncatedPercent_Shape" << std::endl << this->m_fTruncatedPercent_Shape << std::endl;	// m_fTruncatedPercent_Shape
    fp.close();fp.clear();

    // m_PCAAlignedShapeMean=m_cv::MatAlignedMeanShapes
    tempfn = fn + "/m_PCAAlignedShapeMean" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_PCAAlignedShapeMean" << std::endl;
    fp << cv::Mat_<float>(this->m_PCAAlignedShape.mean) << std::endl;
    fp.close();fp.clear();

    // m_PCAAlignedShapeEigenValues
    tempfn = fn + "/m_PCAAlignedShapeEigenValues" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_PCAAlignedShapeEigenValues" << std::endl;
    fp << cv::Mat_<float>(this->m_PCAAlignedShape.eigenvalues) << std::endl;
    fp.close();fp.clear();

    // m_PCAAlignedShapeEigenVectors
    tempfn = fn + "/m_PCAAlignedShapeEigenVectors" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_PCAAlignedShapeEigenVectors" << std::endl;
    fp << cv::Mat_<float>(this->m_PCAAlignedShape.eigenvectors) << std::endl;
    fp.close();fp.clear();

    // m_VOAlignedMeanShape
    tempfn = fn + "/m_VOAlignedMeanShape" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_VOAlignedMeanShape" << std::endl;
    fp << this->m_VOAlignedMeanShape << std::endl;
    fp.close();fp.clear();
	
    // m_VOReferenceShape
    tempfn = fn + "/m_VOReferenceShape" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_VOReferenceShape" << std::endl;
    fp << this->m_VOReferenceShape << std::endl;
    fp.close();fp.clear();

    // m_vShapes
    tempfn = fn + "/m_vShapes" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vShapes" << std::endl;
    fp << m_vShapes << std::endl;
    fp.close();fp.clear();

    // m_vAlignedShapes
    tempfn = fn + "/m_vAlignedShapes" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vAlignedShapes" << std::endl;
    fp << this->m_vAlignedShapes << std::endl;
    fp.close();fp.clear();

    // m_vShape2DInfo
    tempfn = fn + "/m_vShape2DInfo" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << this->m_vShape2DInfo.size() << std::endl;
    fp << "m_vShape2DInfo" << std::endl;
    fp << this->m_vShape2DInfo << std::endl;
    fp << this->m_FaceParts << std::endl;
    fp.close();fp.clear();

	// m_vEdge
    tempfn = fn + "/m_vEdge" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vEdge" << std::endl;
    fp << this->m_vEdge << std::endl;
    fp.close();fp.clear();

    // m_vTemplateTriangle2D
    tempfn = fn + "/m_vTemplateTriangle2D" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vTemplateTriangle2D" << std::endl;
    fp << this->m_vTemplateTriangle2D << std::endl;
    fp.close();fp.clear();

    // m_vNormalizedTriangle2D
    tempfn = fn + "/m_vNormalizedTriangle2D" + ".txt";
    fp.open(tempfn.c_str (), std::ios::out);
    fp << "m_vNormalizedTriangle2D" << std::endl;
    fp << this->m_vNormalizedTriangle2D << std::endl;
    fp.close();fp.clear();

	// m_VOPDM
	this->m_VOPDM.VO_Save(fd);
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-22
 * @brief      	Load all ASM data from a specified folder
 * @param      	fd         	Input - the folder that ASM to be loaded from
*/
void VO_ShapeModel::VO_Load(const std::string& fd)
{
	this->VO_LoadParameters4Fitting(fd);
	
	std::string fn = fd+"/ShapeModel";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "ShapeModel subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;
	
	// m_vShapes
    tempfn = fn + "/m_vShapes" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    this->m_vShapes.resize(this->m_iNbOfSamples);
    fp >> this->m_vShapes;
    fp.close();fp.clear();

    // m_vAlignedShapes
    tempfn = fn + "/m_vAlignedShapes" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_vAlignedShapes;
    fp.close();fp.clear();
}


/**
 * @author     	JIA Pei
 * @version    	2010-02-22
 * @brief      	Load all ASM data from a specified folder for later fitting
 * @param      	fd         		Input - the folder that ASM to be loaded from
*/
void VO_ShapeModel::VO_LoadParameters4Fitting(const std::string& fd)
{
    std::string fn = fd+"/ShapeModel";
    if (!boost::filesystem::is_directory(fn) )
    {
        std::cout << "ShapeModel subfolder is not existing. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream fp;
    std::string tempfn;
    std::string temp;

    // ShapeModel
    tempfn = fn + "/ShapeModel" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp >> this->m_iNbOfSamples;
	fp >> temp >> this->m_iNbOfShapeDim;
    fp >> temp >> this->m_iNbOfPoints;
    fp >> temp >> this->m_iNbOfShapes;
	fp >> temp >> this->m_iNbOfEigenShapesAtMost;
	fp >> temp >> this->m_iNbOfShapeEigens;
	fp >> temp >> this->m_iNbOfEdges;
	fp >> temp >> this->m_iNbOfTriangles;
    fp >> temp >> this->m_fAverageShapeSize;
    fp >> temp >> this->m_fTruncatedPercent_Shape;
    fp.close();fp.clear();
	
	this->m_PCAAlignedShape = cv::PCA();

    // m_PCAAlignedShapeMean
    this->m_PCAAlignedShape.mean = cv::Mat_<float>::zeros(1, this->m_iNbOfShapes);
    tempfn = fn + "/m_PCAAlignedShapeMean" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_PCAAlignedShape.mean;
    fp.close();fp.clear();

	// m_PCAAlignedShapeEigenValues
    this->m_PCAAlignedShape.eigenvalues = cv::Mat_<float>::zeros(this->m_iNbOfShapeEigens, 1);
    tempfn = fn + "/m_PCAAlignedShapeEigenValues" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_PCAAlignedShape.eigenvalues;
    fp.close();fp.clear();

	// m_PCAAlignedShapeEigenVectors
    this->m_PCAAlignedShape.eigenvectors = cv::Mat_<float>::zeros(this->m_iNbOfShapeEigens, this->m_iNbOfShapes);
    tempfn = fn + "/m_PCAAlignedShapeEigenVectors" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_PCAAlignedShape.eigenvectors;
    fp.close();fp.clear();

	// m_VOAlignedMeanShape
    this->m_VOAlignedMeanShape.m_MatShape = cv::Mat_<float>::zeros(this->m_iNbOfShapeDim, this->m_iNbOfPoints);
    tempfn = fn + "/m_VOAlignedMeanShape" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_VOAlignedMeanShape;
    fp.close();fp.clear();

    // m_VOReferenceShape
    this->m_VOReferenceShape.m_MatShape = cv::Mat_<float>::zeros(this->m_iNbOfShapeDim, this->m_iNbOfPoints);
    tempfn = fn + "/m_VOReferenceShape" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_VOReferenceShape;
    fp.close();fp.clear();

    // m_vShape2DInfo & m_FaceParts
    this->m_vShape2DInfo.resize(this->m_iNbOfPoints);
    tempfn = fn + "/m_vShape2DInfo" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;	// 58
	fp >> temp;
    fp >> this->m_vShape2DInfo;
	fp >> this->m_FaceParts;
    fp.close();fp.clear();

    // m_vEdge
	this->m_vEdge.resize(this->m_iNbOfEdges);
    tempfn = fn + "/m_vEdge" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_vEdge;
    fp.close();fp.clear();

     // m_vTemplateTriangle2D
	this->m_vTemplateTriangle2D.resize(this->m_iNbOfTriangles);
    tempfn = fn + "/m_vTemplateTriangle2D" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    fp >> this->m_vTemplateTriangle2D;
    fp.close();fp.clear();

    // m_vNormalizedTriangle2D
	this->m_vNormalizedTriangle2D.resize(this->m_iNbOfTriangles);
    tempfn = fn + "/m_vNormalizedTriangle2D" + ".txt";
    fp.open(tempfn.c_str (), std::ios::in);
    fp >> temp;
    this->m_vNormalizedTriangle2D.resize(this->m_iNbOfTriangles);
    fp >> this->m_vNormalizedTriangle2D;
    fp.close();fp.clear();
	
	this->m_VOPDM.VO_LoadParameters4Fitting(fd);
}

