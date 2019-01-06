package arc

import (
	"fmt"
	"testing"
)

func TestInitEngine(t *testing.T) {
	InitEngine("虹软sdk_app_id","虹软sdk_key")
	if data,err:=GetFeature("测试图片地址");err==nil{
		fmt.Printf("feature data is--->%s",data)
	}else {
		print(err)
	}
}