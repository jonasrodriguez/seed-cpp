#pragma once

#include <memory>


namespace systelab { namespace web_server {

	class Reply;
	class Request;

	class IWebService
	{
	public:
		virtual std::unique_ptr<Reply> process(const Request& request) const = 0;
	};

}}
