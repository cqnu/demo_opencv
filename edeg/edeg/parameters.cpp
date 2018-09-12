

#include <iostream>
#include <opencv2/opencv.hpp>
#include "model.h"
#include <fstream>
#include "matio.h"

using namespace std;
using namespace cv;

_para initial_para() {
    _para o;
    o.name = " ";
    o.alpha = 0.65;
    o.beta = 0.75;
    o.eta = 1;
    o.minScore = 0.01;
    o.maxBoxes = 10000;
    o.edgeMinMag = 0.1;
    o.edgeMergeThr = 0.5;
    o.clusterMinMag = 0.5;
    o.maxAspectRatio = 3;
    o.minBoxArea = 1000;//1600,20000
    o.maxBoxLength = 10000;//250,500
    o.gamma = 2;
    o.kappa = 1.5;
    return o;
}

_model loadmodel() {
    _model model1;


    mat_t *matfp;
    matvar_t *model;
    matfp = Mat_Open("model/model.mat", MAT_ACC_RDONLY);
    if(matfp != NULL);
    model = Mat_VarRead(matfp, "model");
	if (model != NULL)
	{
		/*float *thrs = (float *)(Mat_VarGetStructFieldByName(model, "thrs", 0)->data);
		uint32 *fids = (uint32 *)(Mat_VarGetStructFieldByName(model, "fids", 0)->data);
		uint32 *child = (uint32 *)(Mat_VarGetStructFieldByName(model, "child", 0)->data);
		uint32 *count = (uint32 *)(Mat_VarGetStructFieldByName(model, "count", 0)->data);
		uint32 *depth = (uint32 *)(Mat_VarGetStructFieldByName(model, "depth", 0)->data);
		uint8 *segs = (uint8 *)(Mat_VarGetStructFieldByName(model, "segs", 0)->data);
		uint8 *nSegs = (uint8 *)(Mat_VarGetStructFieldByName(model, "nSegs", 0)->data);
		uint16 *eBins = (uint16 *)(Mat_VarGetStructFieldByName(model, "eBins", 0)->data);
		uint32 *eBnds = (uint32 *)(Mat_VarGetStructFieldByName(model, "eBnds", 0)->data);*/





		matvar_t *opts = Mat_VarGetStructFieldByName(model, "opts", 0);
		assert(opts != 0);
		model1.opts.imWidth = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "imWidth", 0)->data));
		model1.opts.gtWidth = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "gtWidth", 0)->data));
		model1.opts.nPos = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nPos", 0)->data));
		model1.opts.nNeg = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nNeg", 0)->data));
		model1.opts.nTrees = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nTrees", 0)->data));
		model1.opts.nImgs = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nImgs", 0)->data));
		model1.opts.fracFtrs = *(double *)(Mat_VarGetStructFieldByName(opts, "fracFtrs", 0)->data);
		model1.opts.minCount = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "minCount", 0)->data));
		model1.opts.minChild = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "minChild", 0)->data));
		model1.opts.maxDepth = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "maxDepth", 0)->data));
		model1.opts.nSamples = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nSamples", 0)->data));
		model1.opts.nClasses = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nClasses", 0)->data));
		model1.opts.nOrients = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nOrients", 0)->data));
		model1.opts.grdSmooth = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "grdSmooth", 0)->data));
		model1.opts.chnSmooth = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "chnSmooth", 0)->data));
		model1.opts.simSmooth = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "simSmooth", 0)->data));
		model1.opts.normRad = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "normRad", 0)->data));
		model1.opts.shrink = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "shrink", 0)->data));
		model1.opts.nCells = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nCells", 0)->data));
		model1.opts.rgbd = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "rgbd", 0)->data));
		model1.opts.stride = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "stride", 0)->data));
		model1.opts.multiscale = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "multiscale",
			0)->data));
		model1.opts.sharpen = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "sharpen", 0)->data));
		model1.opts.nTreesEval = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nTreesEval",
			0)->data));
		model1.opts.nThreads = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nThreads", 0)->data));
		model1.opts.nms = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nms", 0)->data));
		model1.opts.seed = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "seed", 0)->data));
		model1.opts.useParfor = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "useParfor", 0)->data));
		model1.opts.nChns = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nChns", 0)->data));
		model1.opts.nChnFtrs = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nChnFtrs", 0)->data));
		model1.opts.nSimFtrs = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nSimFtrs", 0)->data));
		model1.opts.nTotFtrs = static_cast<uint32>(*(double *)(Mat_VarGetStructFieldByName(opts, "nTotFtrs", 0)->data));
		model1.opts.discretize = (char *)(Mat_VarGetStructFieldByName(opts, "discretize", 0)->data);
		model1.opts.split = (char *)(Mat_VarGetStructFieldByName(opts, "split", 0)->data);
		model1.opts.modelDir = (char *)(Mat_VarGetStructFieldByName(opts, "modelDir", 0)->data);
		model1.opts.modelFnm = (char *)(Mat_VarGetStructFieldByName(opts, "modelFnm", 0)->data);
		model1.opts.bsdsDir = (char *)(Mat_VarGetStructFieldByName(opts, "bsdsDir", 0)->data);


		return model1;
	}
}
//void getadd(Mat I, float *I_data) {
//	vector<Mat> Ivec;
//	split(I, Ivec);
//	for (int i1 = 0; i1 < I.channels(); i1++) {
//		for (int j1 = 0; j1 < I.cols; j1++) {
//			for (int k1 = 0; k1 < I.rows; k1++) {
//				I_data[i1 * I.rows * I.cols + j1 * I.rows + k1] = Ivec[i1].at<float>(k1, j1);
//			}
//		}
//	}
//}
//
////for uint8 mat
//void getaddu(Mat I, uint8 *I_data) {
//	vector<Mat> Ivec;
//	split(I, Ivec);
//	for (int i1 = 0; i1 < I.channels(); i1++) {
//		for (int j1 = 0; j1 < I.cols; j1++) {
//			for (int k1 = 0; k1 < I.rows; k1++) {
//				I_data[i1 * I.rows * I.cols + j1 * I.rows + k1] = Ivec[i1].at<uint8>(k1, j1);
//			}
//		}
//	}
//}
//
//
////for float mat
//void fillmat(float *I_data, Mat I) {
//	assert(I.channels() == 1 || I.channels() == 2 || I.channels() == 3 || I.channels() == 4);
//	if (I.channels() == 4) {
//		for (int i1 = 0; i1 < I.channels(); i1++) {
//			for (int j1 = 0; j1 < I.cols; j1++) {
//				for (int k1 = 0; k1 < I.rows; k1++) {
//					I.at<Vec4f>(k1, j1)[i1] = I_data[i1 * I.rows * I.cols + j1 * I.rows + k1];
//				}
//			}
//		}
//	}
//	else if (I.channels() == 3) {
//		for (int i1 = 0; i1 < I.channels(); i1++) {
//			for (int j1 = 0; j1 < I.cols; j1++) {
//				for (int k1 = 0; k1 < I.rows; k1++) {
//					I.at<Vec3f>(k1, j1)[i1] = I_data[i1 * I.rows * I.cols + j1 * I.rows + k1];
//				}
//			}
//		}
//	}
//	else if (I.channels() == 2) {
//		for (int i1 = 0; i1 < I.channels(); i1++) {
//			for (int j1 = 0; j1 < I.cols; j1++) {
//				for (int k1 = 0; k1 < I.rows; k1++) {
//					I.at<Vec2f>(k1, j1)[i1] = I_data[i1 * I.rows * I.cols + j1 * I.rows + k1];
//				}
//			}
//		}
//	}
//	else {
//		for (int j1 = 0; j1 < I.cols; j1++) {
//			for (int k1 = 0; k1 < I.rows; k1++) {
//				I.at<float>(k1, j1) = I_data[j1 * I.rows + k1];
//			}
//		}
//	}
//}
//
//
////for uint8 mat
//void fillmatu(uint8 *I_data, Mat I) {
//	assert(I.channels() == 1 || I.channels() == 2 || I.channels() == 3 || I.channels() == 4);
//	if (I.channels() == 4) {
//		for (int i1 = 0; i1 < I.channels(); i1++) {
//			for (int j1 = 0; j1 < I.cols; j1++) {
//				for (int k1 = 0; k1 < I.rows; k1++) {
//					I.at<Vec4b>(k1, j1)[i1] = I_data[i1 * I.rows * I.cols + j1 * I.rows + k1];
//				}
//			}
//		}
//	}
//	else if (I.channels() == 3) {
//		for (int i1 = 0; i1 < I.channels(); i1++) {
//			for (int j1 = 0; j1 < I.cols; j1++) {
//				for (int k1 = 0; k1 < I.rows; k1++) {
//					I.at<Vec3b>(k1, j1)[i1] = I_data[i1 * I.rows * I.cols + j1 * I.rows + k1];
//				}
//			}
//		}
//	}
//	else if (I.channels() == 2) {
//		for (int i1 = 0; i1 < I.channels(); i1++) {
//			for (int j1 = 0; j1 < I.cols; j1++) {
//				for (int k1 = 0; k1 < I.rows; k1++) {
//					I.at<Vec2b>(k1, j1)[i1] = I_data[i1 * I.rows * I.cols + j1 * I.rows + k1];
//				}
//			}
//		}
//	}
//	else {
//		for (int j1 = 0; j1 < I.cols; j1++) {
//			for (int k1 = 0; k1 < I.rows; k1++) {
//				I.at<uint8>(k1, j1) = I_data[j1 * I.rows + k1];
//			}
//		}
//	}
//}
//
//
//
