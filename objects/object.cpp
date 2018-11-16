/*************************************************
 * Author: Abdullah Emad                         *
 * Description: this class contains the abstract *
 * implementation of an Object in a 3D world     *
 *************************************************/

/*
 * Inherit this if you need to add more features to your object
 *
 */
#include <object.h>
#include <linkedlist.h>

// prototypes
float readFloat(FILE* stream);
int parseFile(const char* filename, Linkedlist** vertRet, Linkedlist** normRet, Linkedlist** colorsRet, Linkedlist** indRet);

/**
  * constructor
  * EFFECTS: given a path to a .obj file that contains the description of
  * 		 a 3D object, parses the file and stores the description of the 
  *          object.
  * MODIFIES: this 
  * REQUIRES: a valid path
  */
Object::Object(const char* filename)
{
	int err;
	Linkedlist* verticies;
	Linkedlist* normals;
	Linkedlist* colors;
	Linkedlist* indicies;
	err = parseFile(filename, &verticies, &normals, &colors, &indicies);
	if(err)
	{
		printf("couldn't read %s\n", filename);
	}

	this->verticies = verticies->toArray(sizeof(float) * 3);
	this->normals = normals->toArray(sizeof(float) * 3);
	this->colors = colors->toArray(sizeof(float) * 3);
	this->indicies = indicies->toArray(sizeof(int));

	delete verticies;
	delete normals;
	delete colors;
	delete indicies;


	/***Done Parsing the file***/

	/*
     * Now it is time to initialize the bufffers
     */

	glGenVertexArrays(1, &this->VAO);
	// Now allocate some space for all the buffer objects
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->NBO);
	glGenBuffers(1, &this->EBO);
	glGenBuffers(1, &this->CBO);
	this->bound = false;
}

Object::Object(Array* verticies, Array* normals, Array* colors, Array* indicies){
	this->verticies = verticies; 
	this->normals = normals;
	this->colors = colors;
	this->indicies = indicies;

	glGenVertexArrays(1, &this->VAO);
	// Now allocate some space for all the buffer objects
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->NBO);
	glGenBuffers(1, &this->EBO);
	if(this->colors)
	{
		glGenBuffers(1, &this->CBO);
	}
	this->bound = false;
}

void Object::bind(void)
{
	int length; 
	void* data;
	if(this->bound)
	{
		return;
	}
	glBindVertexArray(this->VAO);

	/*bind verticies array*/
	data = this->verticies->getArray();
	length = this->verticies->getLength();
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length * 3, data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	/*Bind Normal Array*/
	data = this->normals->getArray();
	length = this->normals->getLength();
	glBindBuffer(GL_ARRAY_BUFFER, this->NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length * 3, data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	/*bind Colors if any*/
	
	if(this->colors)
	{
		data = this->colors->getArray();
		length = this->normals->getLength();
		glBindBuffer(GL_ARRAY_BUFFER, this->CBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length * 3, data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	}

	
	/*bind the faces*/
	data = this->indicies->getArray();
	length = this->indicies->getLength();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * length, data, GL_STATIC_DRAW);

	/*unbind when done*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	
	this->bound = true;
}


void draw(void)
{
	
}

/****************************
 *                          *
 *        helpers           *
 *                          *
 ****************************/

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
  * EFFECTS: loads the file into the given linkedlists
  * MODIFIES: normRet, vertRet, colorsRet, indRet
  */
int parseFile(const char* filename, Linkedlist** vertRet, Linkedlist** normRet, Linkedlist** colorsRet, Linkedlist** indRet)
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
		printf("%i", 1);
	}
	
	*vertRet = verticies;
	*normRet = normals;
	*colorsRet = colors;
	*indRet = indicies;
	fclose(file);
	return 0;

}
