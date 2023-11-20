
#include "retriever.h"

#include <curl/curl.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include <iostream>

namespace resource_retriever
{

	class CURLStaticInit
	{
	public:
		CURLStaticInit()
			: initialized_(false)
		{
			CURLcode ret = curl_global_init(CURL_GLOBAL_ALL);
			if (ret != 0) {
				fprintf(stderr, "Error initializing libcurl! retcode = %d", ret);
			}
			else {
				initialized_ = true;
			}
		}

		~CURLStaticInit()
		{
			if (initialized_) {
				curl_global_cleanup();
			}
		}

		bool initialized_;
	};
	static CURLStaticInit g_curl_init;

	Retriever::Retriever()
	{
		curl_handle_ = curl_easy_init();
	}

	Retriever::~Retriever()
	{
		if (curl_handle_) {
			curl_easy_cleanup(curl_handle_);
		}
	}

	struct MemoryBuffer
	{
		std::vector<uint8_t> v;
	};

	size_t curlWriteFunc(void* buffer, size_t size, size_t nmemb, void* userp)
	{
		MemoryBuffer* membuf = reinterpret_cast<MemoryBuffer*>(userp);

		size_t prev_size = membuf->v.size();
		membuf->v.resize(prev_size + size * nmemb);
		memcpy(&membuf->v[prev_size], buffer, size * nmemb);

		return size * nmemb;
	}

	MemoryResource Retriever::get(const std::string& url)
	{
		std::string mod_url = url;

		if (url.find("://") == std::string::npos)
		{
			mod_url = "file://" + url;
		}
		
		//if (url.find("package://") == 0) {
		//	mod_url.erase(0, strlen("package://"));
		//	size_t pos = mod_url.find("/");
		//	if (pos == std::string::npos) {
		//		throw Exception(url, "Could not parse package:// format into file:// format");
		//	}
		//	std::string package = mod_url.substr(0, pos);
		//	if (package.empty()) {
		//		throw Exception(url, "Package name must not be empty");
		//	}
		//	mod_url.erase(0, pos);
		//	std::string package_path;
		//	try {
		//		package_path = ament_index_cpp::get_package_share_directory(package);
		//	}
		//	catch (const ament_index_cpp::PackageNotFoundError&) {
		//		throw Exception(url, "Package [" + package + "] does not exist");
		//	}
		//	mod_url = "file://" + package_path + mod_url;
		//}

		curl_easy_setopt(curl_handle_, CURLOPT_URL, mod_url.c_str());
		curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, curlWriteFunc);

		char error_buffer[CURL_ERROR_SIZE];
		curl_easy_setopt(curl_handle_, CURLOPT_ERRORBUFFER, error_buffer);

		MemoryResource res;
		MemoryBuffer buf;
		curl_easy_setopt(curl_handle_, CURLOPT_WRITEDATA, &buf);

		CURLcode ret = curl_easy_perform(curl_handle_);
		if (ret != 0) {
			throw Exception(mod_url, error_buffer);
		}
		else if (!buf.v.empty()) {
			res.size = buf.v.size();
			// Converted from boost::shared_array, see: https://stackoverflow.com/a/8624884
			res.data.reset(new uint8_t[res.size], std::default_delete<uint8_t[]>());
			memcpy(res.data.get(), &buf.v[0], res.size);
		}

		return res;
	}
}