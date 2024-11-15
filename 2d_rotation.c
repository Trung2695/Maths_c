#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct complex_number {
double	real;
double	im;
} comp;

comp	*ft_mult(comp *in_1, comp *in_2){
	comp	*result = malloc(sizeof(comp));
	if (result == NULL){
		printf("Malloc failed");
		return (NULL);
	}
	result->real = in_1->real * in_2->real - in_1->im * in_2->im;
	result->im = in_1->real * in_2->im + in_1->im * in_2->real;
	return (result);
}

void	ft_conj(comp *in){
	in->im = -in->im;
}

comp	*ft_div(comp *in_1, comp *in_2){
	comp	temp;
	comp	*result = malloc(sizeof(comp));
	if (result == NULL){
		printf("Malloc failed");
		return (NULL);
	}
	temp = *in_2;
	ft_conj(&temp);
	result->real = (ft_mult(in_1, &temp)->real) / (ft_mult(in_2, &temp)->real);
	result->im = (ft_mult(in_1, &temp)->im) / (ft_mult(in_2,&temp)->real);
	return (result);

}

double	ft_norm(comp *num){
	comp	temp = *num;
	ft_conj(&temp);
	return (ft_mult(num, &temp)->real);
}

comp	*operation(comp	*(*func)(comp*, comp*), comp *in_1, comp *in_2){
	return (func(in_1, in_2));
}

comp	*ft_comp_gen(double theta){
	comp	*vect = malloc(sizeof(comp));
	
	vect->real = cos(theta);
	vect->im = sin(theta);
	return(vect);
}

int	main(void){	
	comp	*result;
	comp	*in_2;
	comp	in_1;
	double	theta;
	printf("Please provide the real part of the 1st complex number: \n");
	scanf("%lf", &in_1.real);
	printf("Please provide the imaginary part of the 1st complex number: \n");
	scanf("%lf", &in_1.im);
	printf("Please provide the rotation angle: \n");
	scanf("%lf", &theta); 
	
	in_2 = ft_comp_gen(theta);
	result = ft_mult(&in_1, in_2);
	free(in_2);
	printf("%lf + i %lf", result->real, result->im);
	free(result);
	return (1);
}
