#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
/*
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
*/

#include "myHeader.h"

int jpegFileReadDecode (RAWDATA_t * rawData, const char *filename)
{
  struct jpeg_decompress_struct jpeg;
  struct jpeg_error_mgr err;

  FILE *fi;
  unsigned int ch = 0;
  int i, j, c;
  JSAMPLE *tmp;

  jpeg.err = jpeg_std_error (&err);

  fi = fopen (filename, "rb");
  if (fi == NULL)
    {
      printf ("can't open %s\n", filename);
      return -1;
    }
  jpeg_create_decompress (&jpeg);
  jpeg_stdio_src (&jpeg, fi);
  jpeg_read_header (&jpeg, TRUE);
  jpeg_start_decompress (&jpeg);

#ifdef CHKIMG                   //if you want to know the info of structure, please define CHKIMG in myHeader.h
  printf ("width = %d, height = %d, ch = %d\n", jpeg.output_width,
          jpeg.output_height, jpeg.out_color_components);
#endif

  rawData->data =
    (unsigned char *) malloc (sizeof (unsigned char) * jpeg.output_width *
                              jpeg.output_height * jpeg.out_color_components);
  if (rawData->data == NULL)
    {
      printf ("data malloc error\n");
      fclose (fi);
      jpeg_destroy_decompress (&jpeg);
      return -1;
    }

  for (j = 0; j < jpeg.output_height; j++)
    {
      tmp = rawData->data + j * jpeg.out_color_components * jpeg.output_width;
      jpeg_read_scanlines (&jpeg, &tmp, 1);
    }

  rawData->height = jpeg.output_height;
  rawData->width = jpeg.output_width;
  rawData->ch = jpeg.out_color_components;

  jpeg_finish_decompress (&jpeg);
  jpeg_destroy_decompress (&jpeg);

  fclose (fi);

  return 0;
}

int
jpegFileEncodeWrite (RAWDATA_t * rawData, const char *filename)
{
  struct jpeg_compress_struct jpeg;
  struct jpeg_error_mgr err;
  FILE *fo;
  unsigned char *data;
  JSAMPLE *address;
  int j;

  jpeg.err = jpeg_std_error (&err);
  jpeg_create_compress (&jpeg);

  fo = fopen (filename, "wb");
  if (fo == NULL)
    {
      printf ("%sは開けません\n", filename);
      jpeg_destroy_compress (&jpeg);
      return -1;
    }

  jpeg_stdio_dest (&jpeg, fo);

  jpeg.image_width = rawData->width;
  jpeg.image_height = rawData->height;
  jpeg.input_components = rawData->ch;
  jpeg.in_color_space = JCS_RGB;
  jpeg_set_defaults (&jpeg);

  jpeg_set_quality (&jpeg, 50, TRUE);

  jpeg_start_compress (&jpeg, TRUE);

  for (j = 0; j < jpeg.image_height; j++)
    {
      address = rawData->data + (j * rawData->width * rawData->ch);
      jpeg_write_scanlines (&jpeg, &address, 1);
    }

  jpeg_finish_compress (&jpeg);

  jpeg_destroy_compress (&jpeg);

  return 0;
}

void *
jpegConvertColourtoGray (void *D)
{
  int j, i, c, k;
  int ave, sum;
  RAWDATA_t *DD = (RAWDATA_t *) D;
  //  for(k=0;k<10;k++){
  for (j = 0; j < DD->height; j++)
    {
      for (i = 0; i < DD->width; i++)
        {
          sum = 0;
          for (c = 0; c < DD->ch; c++)
            {
              sum += DD->data[DD->ch * (i + j * DD->width) + c];
            }
          ave = sum / DD->ch;
          for (c = 0; c < DD->ch; c++)
            {
              DD->data[DD->ch * (i + j * DD->width) + c] = ave;
            }
        }
    }
}

int
freeRawData (RAWDATA_t * raw)
{
  free (raw->data);
  return 0;
}
