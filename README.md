# cef-pdf

`cef-pdf` is a command line utility (with embedded HTTP server as an optional mode) for creating PDF documents from HTML content. It uses Google Chrome browser's [Chromium Embedded Framework (CEF)](https://bitbucket.org/chromiumembedded/cef/overview) library for all it's internal work; loading urls, rendering HTML & CSS pages and PDF printing, therefore, it produces perfect, accurate, excellent quality PDF documents.

### Usage:

    cef-pdf [options] --url=<url>|--file=<path> [output]

    Options:
      --help -h        This help screen.
      --url=<url>      URL to load, may be http, file, data, anything supported by Chromium.
      --file=<path>    File path to load using file:// scheme. May be relative to current directory.
      --stdin          Read content from standard input until EOF (Unix: Ctrl+D, Windows: Ctrl+Z).
      --size=<spec>    Size (format) of the paper: A3, B2.. or custom <width>x<height> in mm.
                       A4 is the default.
      --list-sizes     Show all defined page sizes.
      --landscape      Wheather to print with a landscape page orientation.
                       Default is portrait.
      --margin=<spec>  Paper margins in mm (much like CSS margin but without units)
                       If omitted some default margin is applied.
      --javascript     Enable JavaScript.
      --backgrounds    Print with backgrounds. Default is without.

    Server options:
      --server         Start HTTP server
      --host=<host>    If starting server, specify ip address to bind to.
                       Default is 127.0.0.1
      --port=<port>    Specify server port number. Default is 9288

    Output:
      PDF file name to create. Default is to write binary data to standard output.

### HTTP server usage

Execute `cef-pdf` with `--server` option and visit `localhost:9288` with web browser. Default json response, with status and version number, should indicate the server is up and running on local machine:

    {
        "status": "ok",
        "version": "0.2.0"
    }

To receive a PDF, just make POST request to `localhost:9288/foo.pdf`with some HTML content as the request body. `foo` may be any name you choose, `.pdf` suffix is always required. The response will contain the PDF data, with `application/pdf` as the content type.

In addition to POSTing content inside the request body, special HTTP header `Content-Location` is supported, which should be an URL to some external content. `cef-pdf` will try to grab the content from this URL and use it just like it was the request's body.


### Changelog
# Tangro-Adjustments:

a) in src\Client.cpp
```
m_settings.command_line_args_disabled = false;
```
This change allows passing command line parameters to the CEF, e.g. : 
```
--proxy-server="proxy.tangro.de:8080"
```
See the following uri for Chrome proxy configuration parameters:
http://www.chromium.org/developers/design-documents/network-settings#TOC-Command-line-options-for-proxy-settings

b) in src\Client.cpp
```
m_settings.ignore_certificate_errors = true;
```

This settings ignores any certificate error in the future; e.g. if any certificate or even CA validity has expired. the rest is identical to the project cef-pdf.

# .gitignore changes
Added VisualStudio .gitignore defaults entries from GitHub.com



### Building

`cef-pdf` should compile without problems with cmake/ninja on Windows (7, x64), Linux (tested on Debian 8.5.0, x64) and Mac OS X (10.11.6) using decent C++11 compiler. In order to build, [CEF build distribution files](http://opensource.spotify.com/cefbuilds/index.html) must be downloaded and placed in some directory, like `/path/to/cef/release` in the example below.

```
$ mkdir ~/build
$ cd ~/build
$ cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCEF_ROOT=/path/to/cef/release /path/to/cef-pdf
$ ninja
```

### Building in VS2019

I had to struggle, as I do not know cmake and not to much about C++ to compile.
You can do it different, but his is just a hint how I got it working.

Treet structure I use:

C:\source\repros\cef-pdf\
	├───asio
	├───cef
	│   ├───cmake
	│   ├───Debug
	│   ├───include
	│   ├───libcef_dll
	│   ├───Release
	│   ├───Resources
	│   ├───tests
	│   └───VS2019
	├───cmake
	├───resource
	├───src
	└───VS2019

Build I do will be x64 & release

Steps:
1. you ned [Cmake](https://cmake.org/download/)
2. Lets say you use C:\source\repros for git download and compiling.
3. open command prompt or use a Windows Git client, then call:
> cd /d c:\source\repros\
> git clone --recursive https://github.com/spajak/cef-pdf
4. download CEF binary for windows from: [CEF Binaries](http://opensource.spotify.com/cefbuilds/index.html) with Webbrowser, select x64 version
(I used cef_binary_73.1.13+g6e3c989+chromium-73.0.3683.75_windows64.tar.bz2)
5. extract files of CEF to cef-pdf directory in subdirectory cef
(release, cmake etc. directores must be directly placed in c:\source\repos\cef-pdf\cef\
6. open VS Developer prompt, now we use cmd-prompt to continue
7. go to cef-pdf source
>cd /d c:\source\repros\cef-pdf
8. Make directory VS2019
>mkdir VS2019
9. go to subdirectory CEF
>cd cef
10. make directory VS2019
>mkdir VS2019
11. change to directory VS2019
>cd VS2019
12. run cmake:
> cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release  ../
13. If successfully, change directory to cef-pdf\VS2019
>cd ..\..\VS2019
14. run cmake:
>cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release -DCEF_ROOT=C:/Source/cef-pdf/cef ../
15. should run trough
16. open c:\source\repos\cef-pdf\VS2019\cef-pdf.sln in VS2019
17. now compile and find allot of errors.
```3>------ Build started: Project: cef-pdf, Configuration: Release x64 ------
3>Build started 29.01.2020 22:29:02.
3>Target ResolveProjectReferences:
3>Target PrepareForBuild:
3>  Creating directory "C:\source\repos\cef-pdf\VS2019\src\Release\".
3>  Creating directory "cef-pdf.dir\Release\cef-pdf.tlog\".
3>Target InitializeBuildStatus:
3>  Creating "cef-pdf.dir\Release\cef-pdf.tlog\unsuccessfulbuild" because "AlwaysCreate" was specified.
3>Target CustomBuild:
3>  Building Custom Rule C:/source/repos/cef-pdf/src/CMakeLists.txt
3>Target ClCompile:
3>  Client.cpp
3>  Common.cpp
3>  Job.cpp
3>  Manager.cpp
3>  StdInputStreamReader.cpp
3>  PrintHandler.cpp
3>  RenderHandler.cpp
3>  RenderProcessHandler.cpp
3>  C:\source\repos\cef-pdf\src\Job\StdInputStreamReader.h(33,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\StdInputStreamReader.cpp)
3>  SchemeHandlerFactory.cpp
3>  C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\PrintHandler.h(43,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\PrintHandler.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Job.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\RenderHandler.cpp)
3>  Server.cpp
3>  C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Job.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  Session.cpp
3>  C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\RenderProcessHandler.h(42,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\RenderProcessHandler.cpp)
3>  C:\source\repos\cef-pdf\src\RenderProcessHandler.h(29,18): error C3668: 'cefpdf::RenderProcessHandler::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\RenderProcessHandler.cpp)
3>  SessionManager.cpp
3>  C:\source\repos\cef-pdf\src\Job\Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Local.h(32,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Remote.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\Job\StdInput.h(20,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Loader.h(39,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Printer.h(53,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\Job\StdInputStreamReader.h(33,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\Job\ContentProvider.h(48,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>  C:\source\repos\cef-pdf\src\Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\SchemeHandlerFactory.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\PrintHandler.h(43,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  main.cpp
3>  C:\source\repos\cef-pdf\src\RenderProcessHandler.h(42,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\RenderProcessHandler.h(29,18): error C3668: 'cefpdf::RenderProcessHandler::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\Client.cpp(103,86): error C2660: 'CefBrowserHost::CreateBrowser': function does not take 5 arguments
3>  C:\source\repos\cef-pdf\cef\include/cef_browser.h(287,15): message : see declaration of 'CefBrowserHost::CreateBrowser' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\SchemeHandlerFactory.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\SchemeHandlerFactory.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>  C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\SchemeHandlerFactory.cpp)
3>  C:\source\repos\cef-pdf\src\SchemeHandlerFactory.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\SchemeHandlerFactory.cpp)
3>  C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>  C:\source\repos\cef-pdf\src\Server\../Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Server\../Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>  C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>  C:\source\repos\cef-pdf\src\Server\../Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\Server\../Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Server\../Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>  C:\source\repos\cef-pdf\src\Server\../Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>  C:\source\repos\cef-pdf\src\Server\Session.h(99,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Server\SessionManager.h(36,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Server\../Job/Local.h(32,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Server\../Job/Remote.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>  C:\source\repos\cef-pdf\src\Server\Session.h(99,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\Server\SessionManager.h(36,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\Server\Server.h(53,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>  C:\source\repos\cef-pdf\src\Server\Session.h(99,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Server\SessionManager.h(36,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Server/Server.h(53,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Job/Remote.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Job/StdInput.h(20,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>  C:\source\repos\cef-pdf\src\Server\Session.h(99,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>  C:\source\repos\cef-pdf\src\Server\SessionManager.h(36,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>Done building target "ClCompile" in project "cef-pdf.vcxproj" -- FAILED.
3>
3>Done building project "cef-pdf.vcxproj" -- FAILED.
3>
3>Build FAILED.
3>
3>C:\source\repos\cef-pdf\src\Job\StdInputStreamReader.h(33,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\StdInputStreamReader.cpp)
3>C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\PrintHandler.h(43,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\PrintHandler.cpp)
3>C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Job.cpp)
3>C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\RenderHandler.cpp)
3>C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Job.cpp)
3>C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\RenderProcessHandler.h(42,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\RenderProcessHandler.cpp)
3>C:\source\repos\cef-pdf\src\RenderProcessHandler.h(29,18): error C3668: 'cefpdf::RenderProcessHandler::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\RenderProcessHandler.cpp)
3>C:\source\repos\cef-pdf\src\Job\Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Job\Local.h(32,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Job\Remote.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Job\StdInput.h(20,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Job\Loader.h(39,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Job\Printer.h(53,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Job\StdInputStreamReader.h(33,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Job\ContentProvider.h(48,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Job\Manager.cpp)
3>C:\source\repos\cef-pdf\src\Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\SchemeHandlerFactory.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\PrintHandler.h(43,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\RenderProcessHandler.h(42,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\RenderProcessHandler.h(29,18): error C3668: 'cefpdf::RenderProcessHandler::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Client.cpp)
3>C:\source\repos\cef-pdf\src\Client.cpp(103,86): error C2660: 'CefBrowserHost::CreateBrowser': function does not take 5 arguments
3>C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\SchemeHandlerFactory.cpp)
3>C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\SchemeHandlerFactory.cpp)
3>C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Job\Visitor.h(26,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\SchemeHandlerFactory.cpp)
3>C:\source\repos\cef-pdf\src\SchemeHandlerFactory.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\SchemeHandlerFactory.cpp)
3>C:\source\repos\cef-pdf\src\Job\Job.h(87,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>C:\source\repos\cef-pdf\src\Server\../Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Server\../Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\Job/Manager.h(54,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>C:\source\repos\cef-pdf\src\RenderHandler.h(31,5): error C2144: syntax error: 'int' should be preceded by ';' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>C:\source\repos\cef-pdf\src\Server\../Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\Server\../Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Server\../Client.h(173,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>C:\source\repos\cef-pdf\src\Server\../Client.h(107,18): error C3668: 'cefpdf::Client::OnProcessMessageReceived': method with override specifier 'override' did not override any base class methods (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>C:\source\repos\cef-pdf\src\Server\Session.h(99,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Server\SessionManager.h(36,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Server\../Job/Local.h(32,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Server\../Job/Remote.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Session.cpp)
3>C:\source\repos\cef-pdf\src\Server\Session.h(99,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\Server\SessionManager.h(36,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\Server\Server.h(53,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\Server.cpp)
3>C:\source\repos\cef-pdf\src\Server\Session.h(99,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Server\SessionManager.h(36,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Server/Server.h(53,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Job/Remote.h(29,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Job/StdInput.h(20,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\main.cpp)
3>C:\source\repos\cef-pdf\src\Server\Session.h(99,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>C:\source\repos\cef-pdf\src\Server\SessionManager.h(36,1): error C2143: syntax error: missing ';' before '}' (compiling source file C:\source\repos\cef-pdf\src\Server\SessionManager.cpp)
3>    0 Warning(s)
3>    70 Error(s)
3>
3>Time Elapsed 00:00:04.21
```

18. go troug all files that VS claims as errors and add a semicolon at the end, example:
```IMPLEMENT_REFCOUNTING(XYZ)```
to
```IMPLEMENT_REFCOUNTING(XYZ);```

19. Add missing parameter for OnProcessMessageReceived
```
bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                CefProcessId source_process,
                                CefRefPtr<CefProcessMessage> message) OVERRIDE
```
to
```
bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame, //Newly added
                                CefProcessId source_process,
                                CefRefPtr<CefProcessMessage> message) OVERRIDE
```
20. Compile and hope ist sucessful now :)

Hope this helps, for pplz that donot use C++ usually

### License

`cef-pdf` is licensed under the MIT license.
