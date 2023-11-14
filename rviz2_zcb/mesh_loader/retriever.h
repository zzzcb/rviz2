#ifndef OGRE_RENDERING__RETRIEVER_H_
#define OGRE_RENDERING__RETRIEVER_H_

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>

typedef void CURL;

namespace resource_retriever
{
	class Exception : public std::runtime_error
	{
	public:
		Exception(const std::string& file, const std::string& error_msg)
			: std::runtime_error("Error retrieving file [" + file + "]: " + error_msg)
		{
		}
	};

	struct MemoryResource
	{
		MemoryResource()
			: size(0)
		{
		}

		std::shared_ptr<uint8_t> data;
		size_t size;
	};

	class Retriever
	{
	public:
		Retriever();

		~Retriever();

		MemoryResource get(const std::string& url);

	private:
		Retriever(const Retriever& ret) = delete;

		CURL* curl_handle_;
	};

}

#endif
