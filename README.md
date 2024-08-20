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
*Threatzone: Clean*  
*Tria.ge: 6/10 - Suspicious*  
*Kaspersky Opentip: Malicious*  

- https://app.any.run/tasks/30ec6da6-f974-4e26-a3d7-73a16c02c984
- https://www.virustotal.com/gui/file/20d41bf0390ce8a97ac766cc11efafc7d500d06eac463a344cfa8357f439db7c?nocache=1
- https://app.threat.zone/submission/f81fc160-af37-4f80-a23e-c2e324038984/static-scan-report/general-info
- https://tria.ge/240820-tzmfpawcpq
- https://opentip.kaspersky.com/20D41BF0390CE8A97AC766CC11EFAFC7D500D06EAC463A344CFA8357F439DB7C/results
# How to compile?
  cl /EHsc /std:c++17 Dithyramb.cpp /link ole32.lib shell32.lib

