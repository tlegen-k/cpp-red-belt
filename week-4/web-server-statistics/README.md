# Web server statistic

Let's imagine that we have a web server that serves requests to an online store. It supports the following set of HTTP requests:

-    GET / HTTP / 1.1 - get the main page of the store
-    POST / order HTTP / 1.1 - place a new order
-    POST / product HTTP / 1.1 - add a new product to the store (admin command)
-    GET / order HTTP / 1.1 - get order details
-    PUT / product HTTP / 1.1 - the same as POST / order HTTP / 1.1
-    GET / basket HTTP / 1.1 - get the composition of the current customer basket
-    DELETE / product HTTP / 1.1 - delete a product from the online store (admin command)
-    GET / help HTTP / 1.1 - get a page on how to use the online store

From the point of view of the HTTP protocol, the first parts of the above requests ("GET", "POST", "PUT", "DELETE") are called methods. The second parts are called URI (Uniform Resource Identifier). The third part is the protocol version. Thus, our web server supports 4 methods: GET, POST, PUT, DELETE and 5 URIs: “/”, “/ order”, “/ product”, “/ basket”, “/ help”.

The main system administrator of our server took care of its scaling and first decided to study the usage statistics. For each method and each URI, he wants to count how many times he met in requests to the server in the last month. He asked you to help with this.

You already have a codebase of some kind for examining server requests and want to use it to save time. You have a header file http_request.h containing the HttpRequest structure:
```cpp
#pragma once

#include <string_view>

using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;
};
```
In addition, there is a header file stats.h containing declarations for the Stats class and the ParseRequest function:
```cpp
#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

using namespace std;

class Stats {
public:
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
};

HttpRequest ParseRequest(string_view line);
```
Finally, you have the ServeRequests function ready:
```cpp
Stats ServeRequests(istream& input) {
  Stats result;
  for (string line; getline(input, line); ) {
    const HttpRequest req = ParseRequest(line);
    result.AddUri(req.uri);
    result.AddMethod(req.method);
  }
  return result;
}
```

You need to implement the Stats class and the ParseRequest function based on the implementation of the ServeRequests function.

Additional requirements for the Stats class:

-    the GetMethodStats method returns a dictionary that stores for each method how many times it was encountered as an argument to the AddMethod method;
-    the GetUriStats method works similarly for URIs;
-    if the method passed to the AddMethod method is not supported by our server (the list of supported methods is given above), then you need to increase the counter for the "UNKNOWN" method by one (for more details, see unit tests in the solution template);
-    if the URI passed to the AddUri method is not supported by our server, then you need to increase the counter for the URI "unknown" by one.

More information about the ParseRequest function:

-    the ParseRequest function splits the original request into three corresponding parts (method, URI, protocol version), returning the result in the fields of the corresponding HttpRequest structure;
-    when parsing the original query, each part of the query must be selected and saved into the resulting structure without any additional changes. For example, for a request "UNDEFINED / something HTTP / 1.1 ++", in the method, URI and protocol fields of the HttpRequest structure, you must write "UNDEFINED", "/ something" and "HTTP / 1.1 ++", respectively.

For verification, send an archive consisting of the stats.h and stats.cpp files (as well as any other files that you deem necessary to add to your project). At the same time, your files should not contain the implementation of the ServeRequests function (if your package contains the ServeRequests function, you will receive a compilation error).

## How your package will be tested

A cpp file will be added to the project from your archive, which:

-     includes the stats.h header file;
-     contains exactly the same implementation of the ServeRequests function as shown in the statement;
-     contains a main function with a set of unit tests for the ServeRequests function

Your project will be built and run.
How to submit

When you're ready to submit, you can upload files for each part of the assignment on the "My submission" tab.
