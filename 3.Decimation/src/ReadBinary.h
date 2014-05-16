#include<fstream>

class ReadBinary
{
public:
    FILE *ptr_myfile;
    const char* myfile;
    std::ofstream after;
    double Decimate(int channel,int point);
    size_t GetFileSize();
    ReadBinary(const char* filename);
    ~ReadBinary();
};
