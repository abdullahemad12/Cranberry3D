/**
  * This file contains mathematical functions used to generate paths for the chicken
  */
#include <dimensions.h>
#include <math.h>

float constant(float x)
{
	return (SCREEN_HEIGHT / 2) + 10;
}

float quadratic(float x)
{
	return (x * x) + (SCREEN_HEIGHT / 2)
}

float sqrt(float x)
{
	return sqrt(x) + (SCREEN_HEIGHT / 2);
}