HttpRequest moudle
======================================================
@version: 1.0.1  
@Author: Vilas Wang  
@Contact: QQ451930733 | 451930733@qq.com  




## Detailed Description


HttpRequest库是Windows平台下对libcurl的封装，结合C++线程池，实现http多线程异步/同步请求。
- 请求支持同步和异步两种方式调用
- 异步请求结果异步返回
- 异步请求支持自定义回调接口
- 支持多任务并发执行
- 支持停止单个请求或所有请求
- 所有方法线程安全


本模块使用的是vs2015编译的带openssl的libcurl库，版本不同请自行编译。 
libcurl更多版本请见https://github.com/VilasWang/3rd_Dev_Library.git
 
sample项目是Qt写的可视化界面，若不使用Qt，可以将该项目自行移除。


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

auto onRequestResultCallback = [](int id, bool success, const std::string& data, const std::string& error_string) {
    ...
};

auto onProgressCallback = [](int id, bool bDownload, qint64 total_size, qint64 current_size) {
    ...
};

const std::string strUrl = "...";
const std::string strFilePath = "...";

HttpRequest request;
request.setUrl(strUrl);
request.setDownloadFile(strFilePath);
request.registerResultCallback(onRequestResultCallback);
request.registerProgressCallback(onProgressCallback);

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
request.registerResultCallback(onRequestResultCallback);
request.registerProgressCallback(onProgressCallback);

std::shared_ptr<HttpReply> reply = request.perform(HTTP::Upload, HTTP::Async);
std::cout << reply->id();
```

