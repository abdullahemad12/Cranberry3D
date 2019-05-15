#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool check_extension(const char* filename)
{
	bool check;
	int n = strlen(filename);
	check = filename[n - 1] == 'c' || filename[n - 1] == 'a';
	check = check && filename[n - 2] == 'b';
	check = check && filename[n - 3] == 'c';
	check = check && filename[n - 4] == '.';
	return check;
}

/**
  * EFFECTS: loads a text file into memory and removes all the comments and extra lines 
  * REQUIRES: a correct path and file extension
  * MODIFIES: text_ret
  * RETURNS:
  * - 0 on success
  * - 1 if no such a file exists
  * - 2 if the extension is not cbc or cba
  * - 3 if Unexpected Error has occured (such as out of memory)
  * PARAMETERS:
  * - const char* path: path to the file to be read
  * - char* text_ret[]: array of text lines that were read from the file
  */
int load_file(const char* path, char*** text_ret)
{
	FILE* file;		
	size_t file_size;
	char* buff;
	int i;
	int n;
	bool ignore = false;
	int j;
	int k;
	int n_lines;
	bool found_char;
	bool comment;
	char** ret;

	if(!check_extension(path))
	{
		return 2;
	}
	 file = fopen(path, "r");
	if(file == NULL)
	{
		return 1;
	}

	/*calculates the total size of the file*/
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	buff = malloc(file_size);
	if(buff == NULL)
	{
		fclose(file);
		return 3;
	}
	
	/*reads the file into the buffer*/
	i = 0	
	while(true)
	{
		int old = i;
		i += fread(&buff[i / sizeof(char)], sizeof(char), 10, file);
		if(i <= old)
		{
			/*unexpected error becuase EOF is not set*/
			if(feof(file) == 0)
			{
				free(buff);
				fclose(file);
				return 3;
			}
			buff[(++i) / sizeof(char)] = '\0';
			break;
		}
	}

	n = strlen(buff);
	n_lines = 1;
	found_char = false;
	for(i = 0; i < n; i++)
	{
		if(buff[i] == '\n' && found_char)
		{
			found_char = false;
			n_lines++;
		}
		else if(buff[i] != ' ' && != '\n')
		{
			found_char = true;
		}
	}

	ret = malloc(sizeof(char*) * n_lines);
	ret[0] = malloc(sizeof(char));
	j = 0; 
	k = 0;
	found_char = false;
	comment = false;
	for(i = 0; i < n; i++)
	{
		if(buff[i] == '\n' && found_char)
		{
			found_char = false;
			comment = false
			ret[j][k] = '\0';
			ret[++j] = malloc(sizeof(char));
		}
		else if(buff[i] == '#')
		{
			comment = true;
		}
		else if(buff[i] != ' ' && != '\n' && !comment)
		{
			found_char = true;
			ret[j] = realloc(&ret[j], k+1);
			ret[j][k++] = buff[i]; 
		}
	}
	 
	
}


