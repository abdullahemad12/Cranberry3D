#include <stdio.h>
#include <stdlib.h>
#include <linkedlist.h>

/**
  * EFFECTS: reads a single float from an opened file 
  * RETUNRS: the read float
  */
float readFloat(FILE* stream)
{
	static char tmp[11];
	unsigned int tmptr = 0;
	
	char c;
	do{
		fread(&c, sizeof(char), 1, stream);
	
	}while(c == ' ');
	tmp[tmptr++] = c;
	do{
		fread(&c, sizeof(char), 1, stream);
		tmp[tmptr++] = c;
	}while(c != ' ' && c != '\n');
	
	return atof(tmp);
}

/**
  * 
  * EFFECTS: loads the file into the given Array object
  * MODIFIES: normRet, vertRet, colorsRet, indRet
  * RETURNS: 0 on success, non-zero number on failure
  * PARAMETERS: 
  * - Array** vertRet: array of verticies
  * - Array** normRet: array of normals
  * - Array** colorsRet: array of verticies colors (could be NULL)
  * - Array** indRet: array of indicies
  */
int parseFile(const char* filename, Array** vertRet, Array** normRet, Array** colorsRet, Array** indRet)
{
	char c1, c2;
	Linkedlist* verticies = new Linkedlist();
	Linkedlist* normals = new Linkedlist();
	Linkedlist* colors = new Linkedlist();
	Linkedlist* indicies = new Linkedlist();
	/*opens the file*/
	FILE* file = fopen(filename, "r");
	if(file == NULL)
	{
		printf("couldn't open %s\n", filename);
		return 1;	
	}
	
	/*read the file contents character by character*/
	while(!feof(file))
	{
		/*skip over the top of the file and any addition no recognizable characters*/
		do{
			fread(&c1, sizeof(char), 1, file);
			if (feof(file))
				break;
		}while(!(c1 == 'v' || c1 == 'f'));
	
		/*reads the verticies and normals*/
		fread(&c2, sizeof(char), 1, file);
		if(c1 == 'v' && c2 == 'n')
		{
			float* vect = (float*) malloc(sizeof(float) * 3);
			for(int i = 0; i < 3; i++)	
			{
				vect[i] = readFloat(file);
			}
			normals->add(vect);
		}
		else if(c1 == 'v' && c2 == ' ')
		{
			float* vect = new float[3]();
			fscanf(file, "%f %f %f", &vect[0], &vect[1], &vect[2]);
			verticies->add(vect);
			/*skips over any spaces*/
			char tmp;
			do
			{
				fread(&tmp, sizeof(char), 1, file);
			}while(tmp == ' ');

			if(tmp != '\n')
			{
				fseek(file, -sizeof(char), SEEK_CUR);
				float* colorsR = (float*) malloc(sizeof(float) * 3);
				for(int i = 0; i < 3; i++)
				{
					colorsR[i] = readFloat(file);
				}
				colors->add(colorsR);
			}
		}
		else if(c1 == 'f')
		{
			int* faces = (int*) malloc(sizeof(int) * 3);
			int ignore;
			fscanf(file, "%d//%d %d//%d %d//%d", &faces[0], &ignore, &faces[1], &ignore, &faces[2], &ignore);
			--faces[0];
			--faces[1];
			--faces[2];
			indicies->add(faces);
		}
	}
	
	*vertRet = verticies->toArray(sizeof(float) * 3);
	*normRet = normals->toArray(sizeof(float) * 3);
	*colorsRet = colors->toArray(sizeof(float) * 3);
	*indRet = indicies->toArray(sizeof(int));
	
	fclose(file);
	return 0;

}


int main(void){

}
