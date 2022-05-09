#include "gtest/gtest.h"

#include <boost/filesystem.hpp>
#include <iostream>

namespace fs = boost::filesystem;
using namespace std;

string filename = ".crash";
string mountpoint = "/tmp/mntFuseFS";
static const char *content = "Hello World crash!";

namespace {
    TEST(BasicTestSuite, check_existing_file)
    {
        string finalPath = mountpoint + "/" + filename;
        fs::path p(finalPath.c_str());
        EXPECT_TRUE(fs::exists(p)) << ".crash file doesn't exist at mountpoint " << mountpoint;
    }

    TEST(BasicTestSuite, check_a_single_file)
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

    TEST(BasicTestSuite, check_file_content)
    {
        string finalPath = mountpoint + "/" + filename;
        fs::path p(finalPath.c_str());
        EXPECT_TRUE(fs::exists(p)) << ".crash file doesn't exist at mountpoint " << mountpoint;

        // Check whether the file .crash has the content it is supposed
        if (fs::exists(p)) {
            string fileContent, line;
            ifstream file(finalPath);
            while (getline(file, line)) {
                fileContent += line;
            }
            EXPECT_TRUE(strcmp(fileContent.c_str(), content) == 0) << 
            ".crash file doesn't have the content " << content << 
            " it has the content " << fileContent << "\n";
        }
    }
}   // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
