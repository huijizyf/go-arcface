#ifdef __cplusplus
extern "C"{
#endif

#include "arcsoft_face_sdk.h"
#include "amcomdef.h"
#include "asvloffscreen.h"
#include "merror.h"

extern MRESULT initEngine(char* appId,char* sdkKey);

extern MRESULT deinitEngine();

extern MRESULT getFeature(ASF_FaceFeature* feature,MUInt8* imageData,int width,int height);

#ifdef __cplusplus
}
#endif
