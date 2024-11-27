/*Idea: For polynomials \sum_i=0^n a_ix^i (n positive), map coefficients a_i into an int array coef with a_i = coef[i].
 *Make functions for polynomial arithmetics, basic calculus and evaluations.
 * */
#include <stdio.h>
#include <stdlib.h>
int	ft_count(char* input){
	int	i = 0;
	while (*input){
		if (*input == ' '){
			i++;
		}
		input++;
	}
	return (i + 1);
}

int	ft_strlen(char* input){
	int	i = 0;
	while (*input && *input != ' '){
		input++;
		i++;
	}
	return (i);
}

char	**ft_split(char* input, int distinct){
	char	**output = malloc(sizeof(char*) * distinct);
	if (output == NULL){
		printf("Malloc failed at split");
		return (output);
	}
	int	i = 0;
	int	j = 0;
	int	k = 0;
	while (i < distinct){
		j = ft_strlen(input);
		output[i] = malloc(j + 1);
		k = 0;
		while (k < j){
			output[i][k] = *input;
			input++;
			k++;
		}
		output[i][k] = '\0';
		input++;
		i++;
	}
	return (output);
}

double	ft_atod(char* input){
	int	i = 0;
	int	mark = 1;
	int	sign = 1;
	double	power = 10;
	double	sum = 0;
	if (input[i] == '-'){
		sign = -1;
		i++;
	}
	while (input[i]){
		if (input[i] == '.'){
			mark = -1;
		}
		else if (mark == 1){
			sum = sum * 10 + input[i] - '0';
		}
		else if (mark == -1){
			sum = sum + (input[i] - '0')/power;
			power = power * 10;	
		}
		i++;
	}
	return sum * sign;
}

double	*ft_convert(char** input, int distinct){
	double	*result = malloc(sizeof(double) * distinct);
	if (result == NULL){
		printf("Malloc failed at convert");
		return (result);
	}
	int	i = 0;
	while (i < distinct){
		result[i] = ft_atod(input[i]);
		i++;
	}
	return (result);
}

typedef struct Polynomial{
	int	deg;
	double	*coef;
}	poly;

poly ft_poly_mult(poly *poly_1, poly *poly_2){
	int	deg = poly_1->deg + poly_2->deg - 1;
	int	i = 0;
	int	j = 0;
	poly	result;
	result.coef = calloc(deg, sizeof(double));
	if (result.coef == NULL){
		printf("Malloc failed at poly mult");
		return (result);
	}
	result.deg = deg;
	while (i < poly_1->deg){
		j = 0;
		while (j < poly_2->deg){
			result.coef[i+j] = result.coef[i+j] + poly_1->coef[i] * poly_2->coef[j];
			j++;
		}
		i++;
	}
	return result;
}

void	ft_poly_init(poly *input, int deg){
	input->coef = malloc(sizeof(double) * deg);
	if (input->coef == NULL){
		printf("Malloc failed at init");
	}
	input->deg = deg;
}


int	main(int ac, char **av){
	char	*input = av[1];
	char	*input_2 = av[2];
	char	**temp_poly;
	int	i = 0;
	poly	poly_1;
	poly	poly_2;
	poly	result;

//	printf("Please provide ALL the coefficients of the first polynomial (starting from degree 0), seperated by space:");
//	scanf("%s", input);
	
	ft_poly_init(&poly_1, ft_count(input));
	temp_poly = ft_split(input, poly_1.deg);
	poly_1.coef = ft_convert(temp_poly, poly_1.deg);
	
	while (i < poly_1.deg){
		free(temp_poly[i]);
		i++;
	}
	free(temp_poly);

//	printf("Please provide ALL the coefficients of the second polynomial (starting from degree 0), seperated by space:");
//	scanf("%s", input_2);
	
	ft_poly_init(&poly_2, ft_count(input_2));
	temp_poly = ft_split(input_2, poly_2.deg);
	poly_2.coef = ft_convert(temp_poly, poly_2.deg);

	i = 0;
	while (i < poly_2.deg){
		free(temp_poly[i]);
		i++;
	}
	free(temp_poly);

	result = ft_poly_mult(&poly_1, &poly_2);
	
	free(poly_1.coef);
	free(poly_2.coef);
	
	i = 0;
	while (i < result.deg){
		if (i == 0){
			printf("%f\n", result.coef[i]);
		}
		else if (result.coef[i] < 0 && i != 0){
			printf("%f x^%d\n", result.coef[i], i);
		}
		else {
			printf("+%f x^%d\n", result.coef[i], i);
		}
		i++;
	}

	free(result.coef);
	return (ac);
}





