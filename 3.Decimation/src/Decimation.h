#include<fstream>

class Decimation
{
public:
    FILE *ptr_myfile;
    const char* myfile;
    std::ofstream after;
    double Decimate(int channel,int point);
    size_t GetFileSize();
    Decimation(const char* filename);
    ~Decimation();
};
