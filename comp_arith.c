#include <stdio.h>
#include <stdlib.h>

typedef struct complex_number {
double	real;
double	im;
} comp;

comp	*ft_add(comp *in_1, comp *in_2){
	comp	*result = malloc(sizeof(comp));
	if (result == NULL){
		printf("Malloc failed");
		return (NULL);
	}
	result->real = in_1->real + in_2->real;
	result->im = in_1->im + in_2->im;
	return (result);
}

comp *ft_minus(comp *in_1, comp *in_2){
	comp	*result = malloc(sizeof(comp));
	if (result == NULL){
		printf("Malloc failed");
		return (NULL);
	}
	result->real = in_1->real - in_2->real;
	result->im = in_1->im - in_2->im;
	return (result);
}

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

comp	*operation(comp	*(*func)(comp*, comp*), comp *in_1, comp *in_2){
	return (func(in_1, in_2));
}

int	main(int ac, char **av){
	comp	*result;
	comp	*(*func)(comp*, comp*);	
	if (ac != 2){
		printf("Wrong number of arguements!");
		return (-1);
	}
	if (*av[1] == '+'){
		func = &ft_add;
	}
	else if (*av[1] == '*'){
		func = &ft_mult;
	}
	else if (*av[1] == '-'){
		func = &ft_minus;
	}
	else if (*av[1] == '/'){
		func = &ft_div;
	}
	comp in_1;
	comp in_2;

	printf("Please provide the real part of the 1st complex number: \n");
	scanf("%lf", &in_1.real);
	printf("Please provide the imaginary part of the 1st complex number: \n");
	scanf("%lf", &in_1.im);
	printf("Please provide the real part of the 2nd complex number: \n");
	scanf("%lf", &in_2.real);
	printf("Please provide the imaginary part of the 2nd complex number: \n");
	scanf("%lf", &in_2.im);
	
	result = func(&in_1, &in_2);

	printf("%lf + i %lf", result->real, result->im);
	free(result);
	return (ac);
}
