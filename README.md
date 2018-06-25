# VOSM

## What does VOSM stand for?

Vision Open Statistical Model ([VOSM](https://github.com/jiapei100/VOSM)) contains variants of 2D Statistical Models, namely, variants of [ASMs](https://en.wikipedia.org/wiki/Active_shape_model) and [AAMs](https://en.wikipedia.org/wiki/Active_appearance_model). It's mainly composed of two parts:

* Building: build the statistical models (both 2D and 3D are supported in [VOSM](https://github.com/jiapei100/VOSM)). For now, the following models can be built by specifying different parameters:
  - Shape Model: ```-t "SM"```, fundamental shape model
  - Texture Model: ```-t "TM"```, fundamental texture model
  - [Appearance Model](http://www.imm.dtu.dk/~aam/main/node15.html): ```-t "AM"```, fundamental appearance model, originated from [Basic AAM](http://www.imm.dtu.dk/~aam/main/node16.html)
  - Image Alignment appearance Model: ```-t IA```, inverse compositional image alignment, for [ICIA AAM](https://www.ri.cmu.edu/pub_files/pub4/matthews_iain_2004_2/matthews_iain_2004_2.pdf)
  - Feature Model: ```-t "FM"```, a generalized model based on **ANY** type of features adopted by the users
  - Shape model with Local Texture Constraints: ```-t "SMLTC"```, originated from [CLM](https://personalpages.manchester.ac.uk/staff/timothy.f.cootes/Models/clm.html)
  - SMNDPROFILE. ```-t "SMNDPROFILE"```, including original [1D profile ASM](http://www.imm.dtu.dk/~aam/downloads/asmprops/node3.html) and [2D profile ASM](http://www.visionopen.com/members/jiapei/publications/pei_thesischapter34.pdf) proposed by me, please check [chapter 3 of my PhD thesis](http://www.visionopen.com/members/jiapei/publications/pei_thesischapter34.pdf).

* Fitting: test the effects of fitting (**ONLY** 2D is suppprted in [VOSM](https://github.com/jiapei100/VOSM))


## Current Version
0.3.5


## Prerequisites

- [OpenCV](https://github.com/opencv/opencv): >= [Version 3.4.1](https://github.com/opencv/opencv/releases/tag/3.4.1).
- [Boost](https://www.boost.org/): >= [Version 1.65.1](https://www.boost.org/users/history/version_1_65_1.html).


## Download, Compile, and Build

```
$ git clone https://github.com/jiapei100/VOSM
$ mkdir build
$ cd build
$ ccmake ../
$ make -j8
$ sudo make install
```

Two commands and eight libraries will be built:
By default, 2 commands will be built under: **/usr/local/bin**:
- testsmbuilding
- testsmfitting

By default, 8 libraries will be built under: **/usr/local/lib**:
- libvosm_comalgs.so
- libvosm_common.so
- libvosm_cvcommon.so
- libvosm_ensembletraining.so
- libvosm_featureextraction.so
- libvosm_integraltransform.so
- libvosm_smbuilding.so
- libvosm_smfitting.so


## How to use VOSM?

Let's check the **help** info about both commands **testsmbuilding** amnd **testsmfitting**.

**testsmbulding**

```
$ testsmbuilding --help
Usage: test_smbuilding [options] save_directory annotation_directory image_directory shapeinfo_path database channels type levels percentage
options:
   -o    output directory (default './')
   -a    annotation directory (required)
   -i    image directory (required)
   -s    path of the file shapeinfo (required)
   -d    training database (required, IMM, AGING, BIOID, XM2VTS, FRANCK, EMOUNT, JIAPEI )
   -c    channels (1 or 3, default 3)
   -t    statistical model type (SM, TM, AM, IA, FM, SMLTC, SMNDPROFILE. default SMNDPROFILE )
   -l    level of parymid (default 4)
   -p    percentage of shape, texture and appearance PCA (default 0.95)
Note: If you are building SMLTC or SMNDPROFILE, you must specify
 -c 1, namely, SMLTC and SMNDPROFILE can only deal with gray-level images.
 ```

**testsmfitting**

```
$ testsmfitting --help
Usage: smfitting [options] trained_data type testing_images testing_annotations database staticORdynamic recording
options:
   -o   trained data DIRECTory (required)
   -t   fitting method to be used (ASM_PROFILEND, ASM_LTC, AAM_BASIC, AAM_CMUICIA, AAM_IAIA. default ASM_PROFILEND )
   -i   testing image DIRECTory containing at least one image (required)
   -a   testing annotation DIRECTory (can be ignored)
   -d   testing database -- if annotation DIRECTory is specified, database should also be specified for further evaluation on fitting performance (can be ignored)
   -s   static image sequence or dynamic image sequence (default value true)
   -r   recording the fitting results or not (default value false)


Note: current smfitting doesn't defaultly afford 1D Profile ASM.
If you would like to try 1D Profile ASM for static images in current smfitting,
you have to manually change the code in function VO_Fitting2DSM::VO_StartFitting
in file VO_Fitting2DSM.cpp, say, around line 290 of file VO_Fitting2DSM.cpp
change the 5th parameter from '2' to '1' of function
dynamic_cast<VO_FittingASMNDProfiles*>(this)->VO_ASMNDProfileFitting
If you would like to try 1D Profile ASM for dynamic image sequence in current smfitting,
you have to manually change the code in function
in file smfitting.cpp, say around line 453 of file smfitting.cpp
change the 5th parameter from '2' to '1' of function
dynamic_cast<VO_FittingASMNDProfiles*>(fitting2dsm)->VO_ASMNDProfileFitting


Face Detection: current smfitting use Adaboost technology to detect face as well as face components
for face location initialization. Refer to CFaceDetectionAlgs in main().
Default Adaboost detectors installed with OpenCV installation are used in current smfitting
You may manually change the Adaboost detectors according to your own cascade file paths


Face Tracking: current smfitting only deal with image sequences.
If static images are to be tested, there is no point to carry out tracking because
for every image, Adaboost detection will be executed.
If dynamic image sequences are to be tested, current smfitting only provides Camshift tracking strategy.
Please Refer to CTrackingAlgs() in main(), the default setting of function CTrackingAlgs() is Camshift algorithm


Vision Open doesn't provide the video IO or webcam IO although I've done his own IO for all kinds. FFmpeg is so competent.
Users are highly encouraged to use their own video file IO and webcam IO and use VOSM in their own real-time applications.
```


## Usage Examples

We can always run 3 similar commands to build **ALL** supported statistical models. Let's take **IMM** as an example.

```
$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IMM" -c 1 -t "SMNDPROFILE" -l 4 -p 0.95

$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "AM" -c 3 -t "AM" -l 4 -p 0.95

$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IA" -c 3 -t "IA" -l 4 -p 0.95
```




## Key Relative Publications

1) P. JIA, [2D Statistical Models](http://www.visionopen.com/members/jiapei/publications/pei_sm2dreport2010.pdf), Technical Report of Vision Open Working Group, 2st Edition, Oct 21, 2010.

2) P. JIA. [Audio-visual based HMI for an Intelligent Wheelchair](http://www.visionopen.com/members/jiapei/publications/pei_thesischapter34.pdf). PhD thesis, University of Essex, 2010.

3) T. Cootes and C. Taylor. [Statistical models of appearance for computer
vision](http://www.face-rec.org/algorithms/aam/app_models.pdf). Technical report, Imaging Science and Biomedical Engineering, University of Manchester, March 8 2004.

4) I. Matthews and S. Baker. [Active appearance models revisited](https://www.ri.cmu.edu/pub_files/pub4/matthews_iain_2004_2/matthews_iain_2004_2.pdf). International Journal of Computer Vision, 60(2):135–164, November 2004.

5) M. B. Stegmann, [Active Appearance Models: Theory, Extensions and Cases](http://www2.imm.dtu.dk/~aam/main/), 2000.
