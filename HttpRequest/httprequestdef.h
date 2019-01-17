#pragma once

#include <functional>
#include <memory>

#ifndef INT64
#define INT64 long long int
#endif

//{int id, bool success, const std::string& data, const std::string& error_string}
typedef std::function<void(int, bool, const std::string&, const std::string&)> ResultCallback;
//{int id, bool is_download, INT64 total_size, INT64 current_size}
typedef std::function<void(int, bool, INT64, INT64)> ProgressCallback;

class RequestInterface
{
public:
	RequestInterface() {}
	virtual ~RequestInterface() {}
public:
	virtual int	perform() = 0;
	virtual void cancel() = 0;
	virtual int	requestId() = 0;
	virtual bool isRunning() const = 0;
	virtual bool isCanceled() const = 0;
	virtual bool isFailed() const = 0;
	virtual bool isMultiDownload() const = 0;
	virtual INT64 totalBytes() const = 0;
	virtual INT64 currentBytes() const = 0;
	virtual void setCurrentBytes(INT64) = 0;
};

struct ThreadChunk
{
	RequestInterface* _helper;
	FILE* _fp;
	long _startidx;
	long _endidx;

	ThreadChunk()
	{
		_helper = nullptr;
		_fp = nullptr;
		_startidx = 0;
		_endidx = 0;
	}
	~ThreadChunk()
	{
		_helper = nullptr;
		_fp = nullptr;
		_startidx = 0;
		_endidx = 0;
	}
};

