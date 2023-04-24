# DLLInjectorAPI_ForPython
 Simple DLL Injector for Python or usable in any other language. 

### How does this inject a DLL ?
This project uses the simple method of calling LoadLibrary with an dll path.

### Only Python support?
No, in theory you can use this in any language you want but I only included any python example with it.

### How can I use this in other languages?
Research how U can load and call an exported function, the DLL contains an exported function called InjectDLL and takes arguments (int, const char*) while it returns a boolean value. False if fail.
