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

#include "VO_WeakClassifier.h"
#include <queue>

//void VO_WeakClassifier::split_node_data( CvDTreeNode* node )
//{
//	int vi, i, n = node->sample_count, nl, nr, scount = data->sample_count;
//    char* dir = (char*)data->direction->data.ptr;
//    CvDTreeNode *left = 0, *right = 0;
//    int* new_idx = data->split_buf->data.i;
//    int new_buf_idx = data->get_child_buf_idx( node );
//    int work_var_count = data->get_work_var_count();
//    CvMat* buf = data->buf;
//    cv::AutoBuffer<uchar> inn_buf(n*(3*sizeof(int) + sizeof(float)));
//    int* temp_buf = (int*)(uchar*)inn_buf;
//    bool split_input_data;
//
//    complete_node_dir(node);
//
//    for( i = nl = nr = 0; i < n; i++ )
//    {
//        int d = dir[i];
//        // initialize new indices for splitting ordered variables
//        new_idx[i] = (nl & (d-1)) | (nr & -d); // d ? ri : li
//        nr += d;
//        nl += d^1;
//    }
//
//    node->left = left = data->new_node( node, nl, new_buf_idx, node->offset );
//    node->right = right = data->new_node( node, nr, new_buf_idx, node->offset + nl );
//
//    split_input_data = node->depth + 1 < data->params.max_depth &&
//        (node->left->sample_count > data->params.min_sample_count ||
//        node->right->sample_count > data->params.min_sample_count);
//
//    // split ordered variables, keep both halves sorted.
//    for( vi = 0; vi < ((CvCascadeBoostTrainData*)data)->numPrecalcIdx; vi++ )
//    {
//        int ci = data->get_var_type(vi);
//
//        if( ci >= 0 || !split_input_data )
//            continue;
//
//        int n1 = node->get_num_valid(vi);
//        float* src_val_buf = (float*)(uchar*)(temp_buf + n);
//        int *src_sorted_idx_buf = (int*)(src_val_buf + n);
//        int *src_sample_idx_buf = src_sorted_idx_buf + n;
//        const int* src_sorted_idx = 0;
//        const float* src_val = 0;
//        data->get_ord_var_data(node, vi, src_val_buf, src_sorted_idx_buf, &src_val, &src_sorted_idx, src_sample_idx_buf);
//
//        for(i = 0; i < n; i++)
//            temp_buf[i] = src_sorted_idx[i];
//
//        if (data->is_buf_16u)
//        {
//            unsigned short *ldst, *rdst, *ldst0, *rdst0;
//            ldst0 = ldst = (unsigned short*)(buf->data.s + left->buf_idx*buf->cols + 
//                vi*scount + left->offset);
//            rdst0 = rdst = (unsigned short*)(ldst + nl);
//
//            // split sorted
//            for( i = 0; i < n1; i++ )
//            {
//                int idx = temp_buf[i];
//                int d = dir[idx];
//                idx = new_idx[idx];
//                if (d)
//                {
//                    *rdst = (unsigned short)idx;
//                    rdst++;
//                }
//                else
//                {
//                    *ldst = (unsigned short)idx;
//                    ldst++;
//                }
//            }
//            assert( n1 == n);
//
//            left->set_num_valid(vi, (int)(ldst - ldst0));
//            right->set_num_valid(vi, (int)(rdst - rdst0));
//        }   
//        else
//        {
//            int *ldst0, *ldst, *rdst0, *rdst;
//            ldst0 = ldst = buf->data.i + left->buf_idx*buf->cols + 
//                vi*scount + left->offset;
//            rdst0 = rdst = buf->data.i + right->buf_idx*buf->cols + 
//                vi*scount + right->offset;
//
//            // split sorted
//            for( i = 0; i < n1; i++ )
//            {
//                int idx = temp_buf[i];
//                int d = dir[idx];
//                idx = new_idx[idx];
//                if (d)
//                {
//                    *rdst = idx;
//                    rdst++;
//                }
//                else
//                {
//                    *ldst = idx;
//                    ldst++;
//                }
//            }
//
//            left->set_num_valid(vi, (int)(ldst - ldst0));
//            right->set_num_valid(vi, (int)(rdst - rdst0));
//            CV_Assert( n1 == n);
//        }  
//    }
//
//    // split cv_labels using new_idx relocation table
//    int *src_lbls_buf = temp_buf + n;
//    const int* src_lbls = data->get_cv_labels(node, src_lbls_buf);
//
//    for(i = 0; i < n; i++)
//        temp_buf[i] = src_lbls[i];
//
//    if (data->is_buf_16u)
//    {
//        unsigned short *ldst = (unsigned short *)(buf->data.s + left->buf_idx*buf->cols + 
//            (work_var_count-1)*scount + left->offset);
//        unsigned short *rdst = (unsigned short *)(buf->data.s + right->buf_idx*buf->cols + 
//            (work_var_count-1)*scount + right->offset);            
//        
//        for( i = 0; i < n; i++ )
//        {
//            int idx = temp_buf[i];
//            if (dir[i])
//            {
//                *rdst = (unsigned short)idx;
//                rdst++;
//            }
//            else
//            {
//                *ldst = (unsigned short)idx;
//                ldst++;
//            }
//        }
//
//    }
//    else
//    {
//        int *ldst = buf->data.i + left->buf_idx*buf->cols + 
//            (work_var_count-1)*scount + left->offset;
//        int *rdst = buf->data.i + right->buf_idx*buf->cols + 
//            (work_var_count-1)*scount + right->offset;
//        
//        for( i = 0; i < n; i++ )
//        {
//            int idx = temp_buf[i];
//            if (dir[i])
//            {
//                *rdst = idx;
//                rdst++;
//            }
//            else
//            {
//                *ldst = idx;
//                ldst++;
//            }
//        }
//    }        
//    for( vi = 0; vi < data->var_count; vi++ )
//    {
//        left->set_num_valid(vi, (int)(nl));
//        right->set_num_valid(vi, (int)(nr));
//    }
//
//    // split sample indices
//    int *sample_idx_src_buf = temp_buf + n;
//    const int* sample_idx_src = data->get_sample_indices(node, sample_idx_src_buf);
//
//    for(i = 0; i < n; i++)
//        temp_buf[i] = sample_idx_src[i];
//
//    if (data->is_buf_16u)
//    {
//        unsigned short* ldst = (unsigned short*)(buf->data.s + left->buf_idx*buf->cols + 
//            work_var_count*scount + left->offset);
//        unsigned short* rdst = (unsigned short*)(buf->data.s + right->buf_idx*buf->cols + 
//            work_var_count*scount + right->offset);
//        for (i = 0; i < n; i++)
//        {
//            unsigned short idx = (unsigned short)temp_buf[i];
//            if (dir[i])
//            {
//                *rdst = idx;
//                rdst++;
//            }
//            else
//            {
//                *ldst = idx;
//                ldst++;
//            }
//        }
//    }
//    else
//    {
//        int* ldst = buf->data.i + left->buf_idx*buf->cols + 
//            work_var_count*scount + left->offset;
//        int* rdst = buf->data.i + right->buf_idx*buf->cols + 
//            work_var_count*scount + right->offset;
//        for (i = 0; i < n; i++)
//        {
//            int idx = temp_buf[i];
//            if (dir[i])
//            {
//                *rdst = idx;
//                rdst++;
//            }
//            else
//            {
//                *ldst = idx;
//                ldst++;
//            }
//        }
//    }
//
//    // deallocate the parent node data that is not needed anymore
//    data->free_node_data(node); 
//}

