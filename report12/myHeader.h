typedef struct{
  unsigned char *data;
  unsigned int width;
  unsigned int height;
  unsigned int ch;
} RAWDATA_t;
typedef struct{
  RAWDATA_t *raw;
  int start_height;
  int end_height;
}THREAD_t;

int jpegFileReadDecode(RAWDATA_t *, const char*);
int jpegFileEncodeWrite(RAWDATA_t *, const char*);
int freeRawData(RAWDATA_t *);

void *jpegConvertColourtoGray(void *);

#define EXT ".jpg"
#define FNAMELEN 256
#define THREAD_MAX 256

//#define CHKIMG
