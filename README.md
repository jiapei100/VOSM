# VOSM

## What does VOSM stand for?

Vision Open Statistical Model ([VOSM](https://github.com/jiapei100/VOSM)) contains variants of 2D Statistical Models, namely, variants of [ASMs](https://en.wikipedia.org/wiki/Active_shape_model) and [AAMs](https://en.wikipedia.org/wiki/Active_appearance_model). It's mainly composed of two parts:

* **Building**: build the statistical models (**both 2D and 3D** are supported in [VOSM](https://github.com/jiapei100/VOSM)). For now, the following models can be built by specifying different parameters:
  - Shape Model: ```-t "SM"```, fundamental shape model
  - Texture Model: ```-t "TM"```, fundamental texture model
  - [Appearance Model](http://www.imm.dtu.dk/~aam/main/node15.html): ```-t "AM"```, fundamental appearance model, originated from [Basic AAM](http://www.imm.dtu.dk/~aam/main/node16.html)
  - Image Alignment appearance Model: ```-t "IA"```, inverse compositional image alignment, for [ICIA AAM](https://www.ri.cmu.edu/pub_files/pub4/matthews_iain_2004_2/matthews_iain_2004_2.pdf)
  - Feature Model: ```-t "FM"```, a generalized model based on **ANY** type of features adopted by the users
  - Shape model with Local Texture Constraints: ```-t "SMLTC"```, originated from [CLM](https://personalpages.manchester.ac.uk/staff/timothy.f.cootes/Models/clm.html)
  - SMNDPROFILE. ```-t "SMNDPROFILE"```, including original [1D profile ASM](http://www.imm.dtu.dk/~aam/downloads/asmprops/node3.html) and [2D profile ASM](http://www.visionopen.com/members/jiapei/publications/pei_thesischapter34.pdf) proposed by me, please check [chapter 3 of my PhD thesis](http://www.visionopen.com/members/jiapei/publications/pei_thesischapter34.pdf).

* **Fitting**: test the effects of fitting (**ONLY 2D fitting** is suppprted in [VOSM](https://github.com/jiapei100/VOSM))


## Current Version
0.3.5


## Annotated Datasets
| Datasets | No. Of Annotated Points |
|:----------:|:-------------------------:|
| [IMM](https://www2.imm.dtu.dk/~aam/datasets/datasets.html) | 58 |
| [AGING](http://sting.cycollege.ac.cy/~alanitis/fgnetaging/index.htm) | 68 |
| [BIOID](https://www.bioid.com/facedb/) | 68 |
| [FRANCK/Talking Face](http://www-prima.inrialpes.fr/FGnet/data/01-TalkingFace/talking_face.html) | 68 |
| [XM2VTS](http://www.ee.surrey.ac.uk/CVSSP/xm2vtsdb/) | 68 |
| [UMDFaces](http://www.umdfaces.io/) | 21 |


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
Please refer to our wiki [How to use VOSM?](https://github.com/jiapei100/VOSM/wiki/How-to-use-VOSM%3F).


## Cascade Files for Face Components
In file [testsmfitting](https://github.com/jiapei100/VOSM/blob/master/samples/testsmfitting/testsmfitting.cpp), 4 cascade files are used to detect 4 different face parts:

* left eye: haarcascade_mcs_lefteye_alt.xml
* right eye: haarcascade_mcs_righteye_alt.xml
* nose: haarcascade_mcs_nose.xml
* mouth: haarcascade_mcs_mouth.xml

which can be found in [opencv_contrib](https://github.com/opencv/opencv_contrib/tree/master/modules/face/data/cascades).


## Key Relative Publications

1) P. JIA, [2D Statistical Models](http://www.visionopen.com/members/jiapei/publications/pei_sm2dreport2010.pdf), Technical Report of Vision Open Working Group, 2st Edition, Oct 21, 2010.

2) P. JIA. [Audio-visual based HMI for an Intelligent Wheelchair](http://www.visionopen.com/members/jiapei/publications/pei_thesischapter34.pdf). PhD thesis, University of Essex, 2010.

3) T. Cootes and C. Taylor. [Statistical models of appearance for computer
vision](http://www.face-rec.org/algorithms/aam/app_models.pdf). Technical report, Imaging Science and Biomedical Engineering, University of Manchester, March 8 2004.

4) I. Matthews and S. Baker. [Active appearance models revisited](https://www.ri.cmu.edu/pub_files/pub4/matthews_iain_2004_2/matthews_iain_2004_2.pdf). International Journal of Computer Vision, 60(2):135–164, November 2004.

5) M. B. Stegmann, [Active Appearance Models: Theory, Extensions and Cases](http://www2.imm.dtu.dk/~aam/main/), 2000.
