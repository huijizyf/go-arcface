package arc

/*
#cgo CFLAGS: -I${SRCDIR}/inc
#cgo LDFLAGS: -L/usr/lib -larcsoft_face -larcsoft_face_engine -larc_face
#include "arcsoft_face_sdk.h"
#include "amcomdef.h"
#include "asvloffscreen.h"
#include "arc.h"
*/
import "C"
import (
	"errors"
	"fmt"
	"image"
	_ "image/jpeg"
	_ "image/png"
	"os"
	"unsafe"
)

var(
	InitResult int32=0
)

func InitEngine(appId,sdkKey string)  {
	InitResult = int32(C.initEngine(C.CString(appId), C.CString(sdkKey)))
	fmt.Printf("face engine init result is %d\n",InitResult)
}

func GetFeature(filePath string)(string,error){
	if InitResult==0 {
		var feature C.ASF_FaceFeature
		file, err := os.Open(filePath)
		if err != nil {
			return "",err
		}
		img,_,err:=image.Decode(file)
		if err!=nil {
			return "",err
		}
		rect:=img.Bounds()
		width:=rect.Max.X-rect.Min.X
		height:=rect.Max.Y-rect.Min.Y
		gray:=image.Gray{Pix:make([]uint8,width*height),Rect:rect,Stride:width}
		for row:=rect.Min.Y;row<rect.Max.Y;row++{
			for col := rect.Min.X; col < rect.Max.X; col++ {
				gray.Set(col,row,img.At(col,row))
			}
		}
		grayData:=make([]C.MUInt8,len(gray.Pix))
		for i,d:=range gray.Pix{
			grayData[i]=C.MUInt8(d)
		}
		if result:=int32(C.getFeature(&feature,&grayData[0],C.int(width),C.int(height)));result==0{
			data:=C.GoBytes(unsafe.Pointer(feature.feature), C.int(feature.featureSize))
		  	return string(fmt.Sprintf("%x",data)),nil
		}else {
			return "",errors.New(fmt.Sprintf("get feature failed,result is %d",result))
		}
	}else {
		return 	"",errors.New("you should init the engine first or you are init failed")
	}
}
