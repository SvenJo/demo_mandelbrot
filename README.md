# C++ Demo for the mandelbrot algorithm

*TODO:* add a nice description

## Install

*TODO:* Try to be more detailed

You need 

* CMake 2.8.11 or newer
* boost (1.60.0 or edit CMakefile.txt)
    * http://boost.org
    * optioal, only for program_options
* Intel TBB (optional)
    * http://threadingbuildingblocks.org
* Catch (for tests, download only the single header file)
    https://github.com/philsquared/Catch    
* C++ Vector class library
    * http://www.agner.org/

### Catch

Copy catch.hpp to `extern/catch`

### Vector class library  

download the zip and unpack the files into `extern/vectorclass`

### CMake

Parameter
* -DBOOST_ROOT=%BOOST_DIR% 
* -DBoost_DEBUG=%BOOST_DEBUG% [OFF/ON optional] 
* -DTBB_INSTALL_DIR="path_to_tbb\tbb44_20151115oss" [only for windows, on linux install dev package for TBB] 
