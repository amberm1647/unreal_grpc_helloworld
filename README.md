# Unreal gRPC Example

This is a simple example of building a C++ gRPC client as a dll and linking it within Unreal Engine 5.

## Build client dll

Complete the steps in this repository to build the client dll: https://github.com/amberm1647/grpc_example/tree/master

## Unreal Engine

Download and install the Epic Games Launcher from the official webpage. https://www.unrealengine.com/en-US/download

Make sure to set proxy environment variables if on the corporate network.

Install Unreal Engine 5.4.4 from the launcher. 

## Project setup

Copy the client.dll, client.exp, and client.lib you built in the grpc_example repository into this project at Source/MyProject/dll/. The contents of the client.h file here should match the greeter_client.h from grpc_example. (Outside of a prototype use case this all should be wrapped in an Unreal plugin. See https://github.com/Frozen-Projects/FF_PDFium/blob/main/Source/FF_PDFium/FF_PDFium.Build.cs for reference.)

Right click on the .uproject file and select "Generate Visual Studio project files". 

Unreal 5.4 needs an older version of MSVC to build. When opening the project in VS, there should be a pop up in the upper right above the Solution Explorer prompting you to install additional components; click on the link and install them. Otherwise, open Visual Studio Installer, click Modify on the installed version of VS, go to the Individual Components tab, and search for the components manually.

The components are:
- .NET 6.0 Runtime (Out of support)
- MSVC v143 - VS 2022 C++ x64/x86 build tools (v14.38-17.8)

Please note that this MSVC version will cause the gRPC build in grpc_example to fail with linker errors.

Set the solution configuration to "Development Editor" and solution platform to "Win64", and configure the startup project to be "MyProject". Build the project and open it in the Unreal Editor.

If there are build errors caused by absl, see the section "Abseil errors" below.

## Run example

On the remote machine, run the gRPC server executable built in the grpc_example repository:

```
cd grpc_example\build\Releases\

.\server.exe
```

In the Unreal editor, open the C++ classes folder in the Content Browser. Drag and drop ActorTest into the level, click the Play in Editor button (green play button), and the Hello World text from the gRPC server should appear as debug text in the corner and as a Text Render within the game world.

If the connection fails, check that your client machine is on the same network as the server.

## Where to make changes

Library linking and includes are in Source/MyProject/MyProject.Build.cs. If your vcpkg is installed in a different location, change the hardcoded paths in this file.

Delayed loading of client.dll is in Source/MyProject/MyProject.cpp, but this is not strictly necessary and the dll could also be loaded the same way as its dependencies in MyProject.Build.cs. See here for more information on different methods of loading dependencies: https://www.unrealcode.net/WrappingALibrary.html#import-libraries

The logic for calling the exported dll function is in Source/MyProject/ActorTest.cpp and should be a good starting point for wrapper code in a plugin. Changing the actual dll interface will involve editing and re-compiling greeter_client.cc and .h in grpc_example and updating the client.h in this project to match.

## Abseil errors

Abseil errors are caused by a conflict between the function `verify()` defined in the library and UE's macro definition of `verify()`. In C:\src\vcpkg\installed\x64-windows\include\absl\container\internal\btree.h, make the following changes to cancel the UE macro definition in context:

Around line 1579, after modification:
```
#ifdef verify
#undef verify
#endif
  // Verifies the structure of the btree.
  void verify() const;
#ifndef verify
#define verify(expr)			UE_CHECK_IMPL(expr)  // copy from line 221 of /Engine/Source/Runtime/Core/Public/Misc/AssertionMacros.h
#endif
```

Around line 2610, after modification:
```
#ifdef verify
#undef verify
#endif
template <typename P>
void btree<P>::verify() const {
  assert(root() != nullptr);
  assert(leftmost() != nullptr);
  assert(rightmost() != nullptr);
  assert(empty() || size() == internal_verify(root(), nullptr, nullptr));
  assert(leftmost() == (++const_iterator(root(), -1)).node_);
  assert(rightmost() == (--const_iterator(root(), root()->finish())).node_);
  assert(leftmost()->is_leaf());
  assert(rightmost()->is_leaf());
}
#ifndef verify
#define verify(expr)			UE_CHECK_IMPL(expr)  // copy from line 221 of /Engine/Source/Runtime/Core/Public/Misc/AssertionMacros.h
#endif
```

In file C:\src\vcpkg\installed\x64-windows\include\absl\container\internal\btree_container.h, around line 225, after modification: 

```
#ifdef verify
#undef verify
#endif
  void verify() const { tree_.verify(); }
#ifndef verify
#define verify(expr)			UE_CHECK_IMPL(expr)  // copy from line 221 of /Engine/Source/Runtime/Core/Public/Misc/AssertionMacros.h
#endif
```

(Taken from https://forums.unrealengine.com/t/abseil-cpp-absl-in-thirdparty-redefinition-error/1794996/2)
