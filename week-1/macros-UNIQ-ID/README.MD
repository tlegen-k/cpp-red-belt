## Macros UNIQ_ID

Develop a UNIQ_ID macro that will generate an identifier that is unique within a given cpp file. For example, the following code should compile and work:
```cpp
int UNIQ_ID = 5;
string UNIQ_ID = "hello!";
```
Problem permits that code
```cpp
int UNIQ_ID = 5; string UNIQ_ID = "hello"; // both definitions on same line
```
will not compile.
