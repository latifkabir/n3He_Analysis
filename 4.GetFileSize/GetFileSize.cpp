#include <iostream>
#include <sys/stat.h>

using namespace std;
/**
 * Get the size of a file.
 * @param filename The name of the file to check size for
 * @return The filesize, or 0 if the file does not exist.
 */
//size_t getFilesize(const string& filename) {
size_t getFilesize(const char* filename) {
    const string fname=string(filename);

    struct stat st;
    if(stat(fname.c_str(), &st) != 0) {
        return 0;
    }
    return st.st_size;   
}

int main(void)
{
    const char* file="../data/000";

    int x=getFilesize(file);
    cout<<x<<endl;
    return(0);
}
