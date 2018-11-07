#include <bmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int load_image(const char* filename, image_t* image)
{
	FILE* file = fopen(filename, "r");
	if(file == NULL)
	{
		return FILE_NOT_FOUND;	
	}
	struct BITMAPFILEHEADER bf; 
	struct BITMAPINFOHEADER bi;

	/*read the file header and do some sanity checks*/
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, file);
	if(bf.bfType != 0x4D42 || bf.bfReserved1 != 0 || bf.bfReserved2 != 0)
	{
		fclose(file);
		return INVALID_FORMAT;
	}

	/*read the info header and do sanity checks*/
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, file);
	if(bi.biBitCount != 24 ||  bi.biCompression != 0)
	{
		fclose(file);
		return INVALID_FORMAT;
	}
	
	fseek(file, bf.bfOffBits - sizeof(BITMAPINFOHEADER) - sizeof(BITMAPFILEHEADER), SEEK_CUR);

	int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLET)) % 4) % 4;
	int height = abs(bi.biHeight);
	int width = bi.biWidth;
	uint32_t* data = (uint32_t*) malloc(sizeof(uint32_t) * width * height);
	if(data == NULL)
	{
		fclose(file);
		return UNEXPECTED_ERROR;
	}
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			RGBTRIPLET triplet;
			size_t n = fread(&triplet, sizeof(RGBTRIPLET), 1, file);
			if(n < 1)
			{
				free(data);
				fclose(file);
				return CORRUPTED;
			}
			data[(width * i) + j] = (0xFF << 24) | (triplet.rgbBlue << 16) | (triplet.rgbGreen) << 8 | triplet.rgbRed;
		}
		fseek(file, padding, SEEK_CUR);
	}
	
	image->data = data;
	image->width = width;
	image->height = height;
	image->frame_width = width;
	image->frame_height = height;
	return 0;
}


void translate_image(image_t* img, const int c)
{
	uint32_t* copy = (uint32_t*)malloc(sizeof(uint32_t) * img->height * img->width);
	for(int i = 0; i < img->height; i++)
	{
		for(int j = 0; j < img->width; j++)
		{
			copy[i * img->width + j] = img->data[i * img->width + j];
		}
	}
	
	for(int i = 0; i < img->height; i++)
	{
		int index = i - c;
		if(index < 0)
		{
			index = img->height + index;	
		}
		else
		{
			index = index % img->height;	
		}
		for(int j = 0; j < img->width; j++)
		{
			img->data[index * img->width + j] = copy[i * img->width + j];
		}
	}
	free(copy);
}

void duplicate_image(image_t* img)
{
	
	img->data = (uint32_t*)realloc(img->data, sizeof(uint32_t) * img->width * img->height * 2);

	for(int i = 0; i < img->height; i++)
	{
		for(int j = 0; j < img->width; j++)
		{
			img->data[(img->width * img->height) + i * img->width + j] = img->data[i * img->width + j];
		}
	}
	img->start = img->data;
}

void translate_duplicated_image(image_t* image)
{
	if(image->start == image->data + (sizeof(uint32_t) * image->width) * image->height)
	{
		image->start = image->data;
	}
	else
	{
		image->start = image->start + sizeof(uint32_t) * image->width;
	}
}


void set_upper_transparency(image_t* image, BYTE alpha)
{
	for(int i = 0; i < image->width; i++)
	{
		image->data[i] = image->data[i] & 0x00FFFFFF;
		image->data[i] = image->data[i] | (alpha << 24);
	}
}

void set_lower_transparency(image_t* image, BYTE alpha)
{
	int height = (image->height - 1) * image->width;
	for(int i = 0; i < image->width; i++)
	{
		image->data[height + i] = image->data[height + i] & 0x00FFFFFF;
		image->data[height + i] = image->data[height + i] | (alpha << 24);
	}
}

void replace_pixels(image_t* original, image_t* copy, uint32_t pixel)
{
	int ptr = 0;
	for(int i = 0, n = original->width * original->height; i < n; i++)
	{
		if(original->data[i] == pixel)
		{
			original->data[i] = copy->data[ptr++ % (copy->height * copy->width)];
		}
	}
}

void set_color_to_alpha(image_t* image, uint32_t min, uint32_t max)
{
	for(int i = 0, n = image->width * image->height; i < n; i++)
	{
		//image->data[i] =0xFFFFFFFF;	
		if((image->data[i] & 0x00FFFFFF) >= (min & 0x00FFFFFF) && (image->data[i] & 0x00FFFFFF) <= (max & 0x00FFFFFF))
		{
			image->data[i] =0;	
		}
	}
}

static int min(int x, int y)
{
	return x < y ? x : y;
}
static int max(int x, int y)
{
	return x > y ? x : y;
}
void append_image(image_t* image1, image_t* image2)
{
	size_t size = (min(image1->width, image2->width) * (image1->height + image2->height));
	uint32_t* data = (uint32_t*) malloc(sizeof(uint32_t) * size);


	for(int i = 0 ; i < image1->height; i++)
	{
		for(int j = 0, n = min(image1->width, image2->width); j < n; j++)
		{
			data[i * n + j] = image1->data[i * image1->width + j];
		}
	}

	int offset = min(image1->width, image2->width) * image1->height;
	for(int i = 0; i < image2->height; i++)
	{
		for(int j = 0, n = min(image1->width, image2->width); j < n; j++)
		{
			data[offset + (i * n + j)] = image2->data[i*image2->height + j];
		}
	}
	image1->frame_width = min(image1->width, image2->width);
	image1->frame_height = min(image1->height, image2->height);

	image1->width = min(image1->width, image2->width);
	image1->height = image1->height + image2->height;

	free(image1->data);
	image1->data = data;
	
}