HttpRequest moudle
======================================================
@version: 1.0.3  
@Author: Vilas Wang  
@Contact: QQ451930733 | 451930733@qq.com  


** HttpRequest is free library licensed under the term of LGPL v3.0. **



## Detailed Description


HttpRequest库是对libcurl的封装，结合C++线程池，实现http多线程异步/同步请求。
- 多任务并发执行
- 请求支持同步和异步两种方式调用
- 所有方法线程安全
- 支持结束单个请求任务和结束所有请求任务

本模块使用的是vs2015编译的带openssl的libcurl库，版本不同请自行编译。 
libcurl更多版本请见https://github.com/VilasWang/3rd_Dev_Library.git
 
sample项目是Qt写的可视化界面，若不适用Qt，可以将该项目自行移除。


## How to use

>同步下载：
> 

```cpp
#include "HttpRequest.h"
#include "HttpReply.h"


const std::string strUrl = "...";
const std::string strFilePath = "...";

HttpRequest request;
request.setUrl(strUrl);
request.setDownloadFile(strFilePath);

std::shared_ptr<HttpReply> reply = request.perform(HTTP::Download, HTTP::Sync);
std::cout << reply->id() << reply->httpStatusCode() << reply->errorString() << reply->readAll() << std::endl;
```

>异步下载：
> 

```cpp
#include "HttpRequest.h"
#include "HttpReply.h"

const std::string strUrl = "...";
const std::string strFilePath = "...";

HttpRequest request;
request.setUrl(strUrl);
request.setDownloadFile(strFilePath);
request.setResultCallback(std::bind(&CurlTool::onRequestResultCallback, this, 
	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
request.setProgressCallback(std::bind(&CurlTool::onProgressCallback, this, 
	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

std::shared_ptr<HttpReply> reply = request.perform(HTTP::Download, HTTP::Async);
std::cout << reply->id();
```


>异步上传
>

```cpp
#include "HttpRequest.h"
#include "HttpReply.h"

const std::string strUrl = "...";
const std::string strUploadFilePath = "...";

HttpRequest request;
request.setUrl(strUrl);
request.setUploadFile(strUploadFilePath);
request.setResultCallback(std::bind(&CurlTool::onRequestResultCallback, this, 
	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
request.setProgressCallback(std::bind(&CurlTool::onProgressCallback, this, 
	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

std::shared_ptr<HttpReply> reply = request.perform(HTTP::Upload, HTTP::Async);
std::cout << reply->id();
```

