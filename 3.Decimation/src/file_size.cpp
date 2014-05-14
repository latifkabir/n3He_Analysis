#include <iostream>
#include <sys/stat.h>

using namespace std;
/**
 * Get the size of a file.
 * @param filename The name of the file to check size for
 * @return The filesize, or 0 if the file does not exist.
 */
size_t getFilesize(const string& filename) {
    struct stat st;
    if(stat(filename.c_str(), &st) != 0) {
        return 0;
    }
    return st.st_size;   
}

int main(void)
{
   int x=getFilesize("../data/000");
   cout<<x<<endl;
   return(0);
}
