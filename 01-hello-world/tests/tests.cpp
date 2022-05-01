#include "gtest/gtest.h"

#include <boost/filesystem.hpp>
#include <iostream>

namespace fs = boost::filesystem;
using namespace std;

string filename = ".crash";
string mountpoint = "/tmp/mntFuseFS";

namespace {
    TEST(tests, check_existing_file)
    {
        string finalPath = mountpoint + "/" + filename;
        fs::path p(finalPath.c_str());
        EXPECT_TRUE(fs::exists(p)) << ".crash file doesn't exist at mountpoint " << mountpoint;
    }

    TEST(tests, check_a_single_file)
    {
        fs::path p (mountpoint);

        // Checking whether mountpoint directory exists
        EXPECT_TRUE(fs::exists(p));

        if (is_directory(p))
        {
            int children = 0;
            for (fs::directory_entry& x : fs::directory_iterator(p))
                children++;

            // Checking whether the FUSE filesystem is mounted
            EXPECT_FALSE(children == 0) << "The FUSE filesystem is not mounted\n";

            // Checking whether the FUSE filesystem only contains a single file: .crash
            EXPECT_FALSE(children > 1) << "The FUSE filesystem has more files beside file .crash";
        }
    }
}   // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
