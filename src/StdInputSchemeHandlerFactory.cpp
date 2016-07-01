#include "StdInputSchemeHandlerFactory.h"
#include <string>
#include <iostream>
#include "include/wrapper/cef_stream_resource_handler.h"

StdInputSchemeHandlerFactory::StdInputSchemeHandlerFactory() {}

CefRefPtr<CefStreamReader> StdInputSchemeHandlerFactory::GetStdInputStream()
{
    std::string input;

    std::cout << "Waiting for input until EOF (Unix: Ctrl+D, Windows: Ctrl+Z)" << std::endl;

    for (std::string line; std::getline(std::cin, line);) {
        input.append(line + "\n");
    }

    CefRefPtr<CefStreamReader> stream = CefStreamReader::CreateForData(
        const_cast<void *>(static_cast<const void *>(input.c_str())), input.size()
    );

    return stream;
}

CefRefPtr<CefResourceHandler> StdInputSchemeHandlerFactory::Create(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    const CefString& scheme_name,
    CefRefPtr<CefRequest> request
) {
    CefRefPtr<CefStreamReader> stream = GetStdInputStream();
    return new CefStreamResourceHandler("text/html", stream);
}