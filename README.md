# go-arcface
基于虹软算法的go语言封装，实现了算法的初始化及人脸特征值提取功能，受限于算法支持的平台，目前仅可运行在Linux 64位环境中。

使用C++对算法进行了简单封装，编译为so动态库（位于lib目录下），将lib目录下的三个so库复制到 /usr/lib目录下后即可运行。如需要自行修改库对arc.cpp进行修改再自行编译即可。

目前实现功能较少，后续有时间会增加其它功能，由于对C/C++不太熟悉，欢迎有兴趣的小伙伴加入一起完善功能。

虹软文档：
http://ai.arcsoft.com.cn/manual/arcface_linux_fd.html
