# How to use VOSM?

## help

Let's check the **help** info about both commands **testsmbuilding** amnd **testsmfitting**.

### testsmbulding

```
$ testsmbuilding --help
Usage: test_smbuilding [options] save_directory annotation_directory image_directory shapeinfo_path database channels type levels percentage
options:
   -o    output directory (default './')
   -a    annotation directory (required)
   -i    image directory (required)
   -s    path of the file shapeinfo (required)
   -d    training database (required, IMM, AGING, BIOID, FRANCK, XM2VTS, UMDFaces )
   -c    channels (1 or 3, default 3)
   -t    statistical model type (SM, TM, AM, IA, FM, SMLTC, SMNDPROFILE. default SMNDPROFILE )
   -l    level of parymid (default 4)
   -p    percentage of shape, texture and appearance PCA (default 0.95)

Note: If you are building SMLTC or SMNDPROFILE, you must specify
 -c 1, namely, SMLTC and SMNDPROFILE can only deal with gray-level images.
 ```

### testsmfitting

```
$ testsmfitting --help
Usage: smfitting [options] trained_data type testing_images testing_annotations database staticORdynamic recording
options:
   -o   trained data directory (required)
   -t   fitting method to be used (ASM_PROFILEND, ASM_LTC, AAM_BASIC, AAM_CMUICIA, AAM_IAIA. default ASM_PROFILEND )
   -i   testing image directory containing at least one image (required)
   -a   testing annotation directory (can be ignored)
   -d   testing database -- if annotation directory is specified, database should also be specified for further evaluation on fitting performance (can be ignored)
   -s   static image sequence or dynamic image sequence (default value true)
   -r   recording the fitting results or not (default value false)


Note: current testsmfitting adopts 2D Profile ASM by default.
If you would like to try 1D Profile ASM, you have to manually change the code
in function VO_Fitting2DSM::VO_StartFitting in file VO_Fitting2DSM.cpp, say,
around line 318 of file VO_Fitting2DSM.cpp:
change the 5th parameter from '2' to '1' of function
dynamic_cast<VO_FittingASMNDProfiles*>(this)->VO_ASMNDProfileFitting.


Face Detection: current testsmfitting use Adaboost technology to detect face
as well as face components for face location initialization.
Refer to CFaceDetectionAlgs in main(). Default Adaboost detectors
installed with OpenCV installation are adopted in current testsmfitting.
You may manually change the Adaboost detectors according to your own cascade file paths.


Face Tracking: current testsmfitting only deal with image sequences.
- For static images, it's pointless to do tracking.
- For dynamic image sequences, Camshift tracking strategy is adopted.
Please Refer to CTrackingAlgs() in main(), the default setting of function
function CTrackingAlgs() is Camshift algorithm.


Vision Open doesn't provide the video IO or webcam IO although I've done my own IO for all kinds.
FFmpeg is so competent. Users are highly encouraged to use their own video file IO
and webcam IO and use VOSM in their own real-time applications.
```


## Usage Examples

### shapeinfo

All **ShapeInfo.txt** are provided at [https://github.com/jiapei100/VOSM/tree/master/shapeinfo](https://github.com/jiapei100/VOSM/tree/master/shapeinfo).


### testsmbulding

As described in **help**, current [VOSM]() supports 7 types of statistical models. We try them one by one.
Here, let's take [**IMM**](https://www2.imm.dtu.dk/~aam/datasets/datasets.html) as an example.

#### 1. SM

##### Command

```
$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IMM" -c 1 -t "SM" -l 4 -p 0.95
```

##### Output

Two folders: **Point2DDistributionModel** and **ShapeModel**.

#### 2. TM

##### Command

```
$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IMM" -c 3 -t "TM" -l 4 -p 0.95
```

##### Output

Three folders: **Point2DDistributionModel**, **ShapeModel** and **TextureModel**.

#### 3. AM

##### Command

```
$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IMM" -c 3 -t "AM" -l 4 -p 0.95
```

##### Output

Five folders: **Point2DDistributionModel**, **ShapeModel**, **TextureModel**, **AppearanceModel** and **AXM**.

#### 4. IA

##### Command

```
$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IMM" -c 3 -t "IA" -l 4 -p 0.95
```

##### Output

Five folders: **Point2DDistributionModel**, **ShapeModel**, **TextureModel**, **AAMICIA** and **AXM**.

#### 5. FM

##### Command

```
$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IMM" -c 3 -t "FM" -l 4 -p 0.95
```

##### Output

Two folders: **AFM** and **AXM**.

#### 6. SMLTC

##### Command

```
$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IMM" -c 3 -t "SMLTC" -l 4 -p 0.95
```

##### Output

Four folders: **Point2DDistributionModel**, **ShapeModel**, **ASMLTCs** and **AXM**.

#### 7. SMNDPROFILE

##### Command

```
$ testsmbuilding -o "./output" -a "./annotations/training/" -i "./images/training/" -s "../VOSM/shapeinfo/IMM/ShapeInfo.txt" -d "IMM" -c 1 -t "SMNDPROFILE" -l 4 -p 0.95
```

##### Output

Four folders: **Point2DDistributionModel**, **ShapeModel**, **ASMNDProfiles** and **AXM**.

Clearly, in total, 9 models can be generated by [Current VOSM](https://github.com/jiapei100/VOSM/releases) . They are:
* Point2DDistributionModel
* ShapeModel
* TextureModel
* AppearanceModel
* AAMICIA
* AFM
* AXM
* ASMLTCs
* ASMNDProfiles


### testsmfitting

```
$ testsmfitting -o "./output/" -t "ASM_PROFILEND" -i "./images/testing/" -a "./annotations/testing/" -d "IMM" -s true -r true
```
