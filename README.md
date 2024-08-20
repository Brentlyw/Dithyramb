# Dithyramb
Dithyramb is a C++ ransomware foundation which uses indirection via monads, higher-order functions, functors, and lambdas.

# Why is it special?
- Uses monads to chain operations / manage control-flow
- Uses higher-order functions to encapsulate & "pass around" functionality
- Uses functors to abstract operations, also allows for deferred execution
- Uses lambdas to create inline anon functions to handle tasks with minimal boilerplate.

# What are the detections like?
Upon development of Dithyramb the detections are below:  

*Virustotal: 5/75*  
*Any.run: No threats detected*  
- https://app.any.run/tasks/30ec6da6-f974-4e26-a3d7-73a16c02c984
- https://www.virustotal.com/gui/file/20d41bf0390ce8a97ac766cc11efafc7d500d06eac463a344cfa8357f439db7c?nocache=1

- #How to compile?
  cl /EHsc /std:c++17 Dithyramb.cpp /link ole32.lib shell32.lib

