01-hello-world tests

How to configure tests for 01-hello-world project?
==================================================

Functional tests are configured during the compilation process by running the following steps:

1- Create a build folder inside the source code folder:
cd fuse-examples/01-hello-world
mkdir build && cd build

2- Generate makefiles:
cmake -DCMAKE_BUILD_TYPE=Debug ../ .

This step generates the makefiles and downloads the gtests dependencies for running the tests. It may need root permissions for execution.

2- Run make for hello-world and tests:
make -j

3- Run the tests with the following code:
sudo ./bin/tests

For running tests it may be necessary root permissions to grant access to the FUSE filesystem.
