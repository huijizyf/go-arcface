#include "inc/arc.h"
#include <iostream>  
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define NSCALE 16 
#define FACENUM	1

#define SafeFree(p) { if ((p)) free(p); (p) = NULL; }
#define SafeArrayDelete(p) { if ((p)) delete [] (p); (p) = NULL; } 
#define SafeDelete(p) { if ((p)) delete (p); (p) = NULL; } 

MHandle handle = NULL;

MRESULT initEngine(char* appId,char* sdkKey){
	//激活SDK
	MRESULT res = ASFActivation(appId, sdkKey);
	if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
		printf("ALActivation fail: %d\n", res);
	else
		printf("ALActivation sucess: %d\n", res);
	//初始化引擎
	MInt32 mask = ASF_FACE_DETECT | ASF_FACERECOGNITION | ASF_AGE | ASF_GENDER | ASF_FACE3DANGLE;
	res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_0_HIGHER_EXT, NSCALE, FACENUM, mask, &handle);
	if (res != MOK)
		printf("ALInitEngine fail: %d\n", res);
	else
		printf("ALInitEngine sucess: %d\n", res);
	return res;
}

MRESULT deinitEngine(){
	MRESULT res = ASFUninitEngine(handle);
	if (res != MOK)
		printf("ALUninitEngine fail: %d\n", res);
	else
		printf("ALUninitEngine sucess: %d\n", res);
	return res;
}

MRESULT getFeature(ASF_FaceFeature* feature,MUInt8* imageData,int width,int height){
	// 人脸检测
	ASF_MultiFaceInfo detectedFaces = { 0 };
	ASF_SingleFaceInfo SingleDetectedFaces = { 0 };
	MRESULT res = ASFDetectFaces(handle, width, height, ASVL_PAF_RGB24_B8G8R8, imageData, &detectedFaces);
	if (res != MOK)
		printf("ASFDetectFaces fail: %d\n", res);
	else
	{
		printf("ASFDetectFaces sucess: %d\n", res);
		SingleDetectedFaces.faceRect.left = detectedFaces.faceRect[0].left;
		SingleDetectedFaces.faceRect.top = detectedFaces.faceRect[0].top;
		SingleDetectedFaces.faceRect.right = detectedFaces.faceRect[0].right;
		SingleDetectedFaces.faceRect.bottom = detectedFaces.faceRect[0].bottom;
		SingleDetectedFaces.faceOrient = detectedFaces.faceOrient[0];
	}
	// 单人脸特征提取
	res = ASFFaceFeatureExtract(handle, width, height, ASVL_PAF_RGB24_B8G8R8, imageData, &SingleDetectedFaces, feature);
	return res;
}
