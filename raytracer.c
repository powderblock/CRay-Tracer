#include <stdio.h>
#include <stdbool.h> /* Needed for boolean datatype */

int width = 256;
int height = 256;

/* The vector structure */
typedef struct{
      float x, y, z;
}vector;

/* The sphere */
typedef struct{
        vector pos;
        float radius;
}sphere;

/* The ray */
typedef struct{
        vector start;
        vector dir;
}ray;

/* Subtract two vectors and return the resulting vector */
vector vectorSub(vector *v1, vector *v2){
	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
	return result;
}

/* Multiply two vectors and return the resulting scalar (dot product) */
float vectorDot(vector *v1, vector *v2){
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/* Check if the ray and sphere intersect */
bool intersectRaySphere(ray *r, sphere *s){
	/* A = d.d, the vector dot product of the direction */
	float A = vectorDot(&r->dir, &r->dir); 
	
	/* We need a vector representing the distance between the start of 
	 * the ray and the position of the circle.
	 * This is the term (p0 - c) 
	 */
	vector dist = vectorSub(&r->start, &s->pos);
	
	/* 2d.(p0 - c) */  
	float B = 2 * vectorDot(&r->dir, &dist);
	
	/* (p0 - c).(p0 - c) - r^2 */
	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
	
	/* Solving the discriminant */
	float discr = B * B - 4 * A * C;
	
	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 */
	if(discr < 0)
		return false;
	else
		return true;
}

int main(){
    printf("P6\n"); // Define what type of BM we are going to do.
    printf("%d %d\n255\n", width, height); // Give information about height and color depth.
	/* Our ray and a sphere */
	sphere s;
	/* Position the sphere */
	s.pos.x = 128;
	s.pos.y = 128;
	s.pos.z = 20;

	ray r;
	/* Sphere radius */
	s.radius = 30;

	/* Direction of the ray */
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 1;

	/* Start position of the ray, z coordinate */
	r.start.z = 0;

	//Don't know how to do def within for loop, yet...
	int y;
	int x;
	
	// Iterate over every pixel
	for(y= 0; y < width; ++y){
		/* Set the y-coordinate of the start position of the ray */
		r.start.y = y; 
		for(x = 0; x < height; ++x){
			/* Set the x-coordinate of the start position of the ray */
			r.start.x = x;

			/* Check if the ray intersects with the shpere */
			if(intersectRaySphere(&r, &s)){
				printf("%c%c%c", 255, 0, 0);
			}
			else{
				printf("%c%c%c", 0, 0, 0);
			}
		}
	}
}