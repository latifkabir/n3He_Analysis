
class ReadBinary
{
public:
    FILE *ptr_myfile;
    const char* myfile;
    double Decimate(int channel,long point);
    size_t GetFileSize();
    ReadBinary(const char* filename);
    ~ReadBinary();
};
