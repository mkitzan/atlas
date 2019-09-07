# Developer's Manual

The purpose of this page is to provide some documentation on how to develop
for Atlas, as well as how to use it in your own projects. Since Atlas is still
in a development phase, pull requests are currently not accepted. If you find a
bug, please report it as an issue in GitHub.

## Contents

1. [Setting up Atlas](#install)
2. [Running the Tests](#tests)

## Setting up Atlas <a name="install"></a>

First make sure that you have all of the core requirements of Atlas and that you
have a C++17 compliant compiler installed. If you do not wish to install the
libraries that Atlas depends on, then Git is also required.

> **Note:**
> If you're going to be doing development for Atlas it is recommended that you
> install the libraries as it will make development easier. The version numbers
> can be found in the top-level `CMakeLists.txt` file.

> **Warning:**
> If you do not wish to install the libraries, be advised that Atlas utilizes
> git to clone down the libraries during the cmake step.

Either clone or download the code and then run CMake to generate the appropriate
build system. Make sure that you enable the tests for Atlas to ensure that
everything works in your system. Then compile the framework.

> **Note:**
> If you did not install the libraries and you're on Windows, please make sure
> that **before** making any changes to the CMake configuration, that you generate
> the project files. GLM requires a file that is only created in the generate
> stage. Failure to do this will result in an error being generated. If this
> happens, simply delete the build directory and the cache.

## Running the Tests <a name="tests"></a>

Once Atlas is compiled, please run the tests to ensure everything works
correctly. Most of them are code driven so no user interaction is required.
There are 4 tests that do require user input. These are described below:

### Window Callbacks Test

A black window will appear. Please make sure that you perform the following
operations:

1. Click any mouse button inside the black area,
2. Move the mouse within the black area,
3. Scroll within the black area,
4. Press any key (except for ESC) with the window in focus,
5. Resize the window,
6. and close the window.

If the test fails it's probably because an operation was not captured. This is
not entirely critical as it is more important that the window appears as it
signals that GLFW initialized correctly and that the callbacks are correctly
set.

### Multiple Windows

Two windows, one red and one green will appear. Click in both windows and then
close them. The test should pass. Similar to before, if it doesn't, it is not
entirely relevant.

### UI Tests

Simply click the button that is mentioned in the UI.

If all the tests passed, then your system fully supports Atlas and you're now
ready to begin developing your application.
