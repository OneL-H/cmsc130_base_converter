#include <stdio.h>
#define MAX_NUM_LEN 10

char character_numbers[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};


// returns a negative number if ERROR, otherwise returns location of radix point
// -1 => your number has a digit exceeding the base
// -2 => your number has multiple decimal points
int reformat_bad_numbers(char *str_number, int base){

	// move through "number" and check for invalid characters
	int point_count = -1;
	for(int i = 0; str_number[i] != "\0" || i < 12; i++){

		// wait theres a good solution here actually.
		// convert the number to .lower with ascii addtion
		// then cycles through the character_numbers to see if the character exists
		// if it doesn't find it, returns -1 and ends the loop

		// finding the decimal point
		if(str_number[i] == '.'){
			if(point_count != -1){
				return -2;
			}
			point_count = i;
		}
	}



}

long pow(long base, int power){
	
	for(int i = 0; i < power; i++){
		base *= power;
	}

	return base;
}

int find_length(char base_x[MAX_NUM_LEN]){

	for(int i = 0; i < MAX_NUM_LEN; i++){
		if(base_x[MAX_NUM_LEN] == '\0'){
			return i+1;
		}
	}
}

long whole_base_to_dec(char base_x[MAX_NUM_LEN], int base){

	int str_len = find_length(base_x);
	long running_total = 0;

	for(int i = str_len-1; i > -1; i--){
		running_total += character_numbers[base_x[i]] * running_total(base, str_len - i - 1);
	}

	return running_total;
}

int main(){

	char base_x_inp[MAX_NUM_LEN+2];
	int init_base;
	int target_base;

	int radix_point_loc;
	char whole_base_x[MAX_NUM_LEN+1];
	char decimal_base_x[MAX_NUM_LEN+1];

	// okay this idea just sounded too based not to do
	// instead of dealing with the inherent inaccuracies of representing base numbers
	// with floats and doubles, leave them represented as a fraction which you then multiply
	// the new base with similar to the old method and do the carry
	// this might be a whole pain in the ass to do but i aint gonna settle with that bs
	long whole_dec;
	long decimal_numerator_dec;
	long decimal_denominator_dec;

	char whole_new_base[MAX_NUM_LEN+1];
	char decimal_new_base[MAX_NUM_LEN+1];




	while(1){

		printf("Enter positive number in whatever base, or enter [Q] to quit \n");

		// NEEDS IMPROVEMENTS: RESTRICT INPUT LENGTH
		scanf("%s", &base_x_inp);

		if(base_x_inp == "Q"){
			break;
		}

		// take in bases, reset if invalid base.
		printf("This number is in what base?");
		scanf("%d", &init_base);

		if(2 > init_base || init_base > 16){
			printf("\n This base is unsupported. 2 <= radix <= 16 only");
			continue;
		}

		printf("\n Convert to what base?");
		scanf("%d", &target_base);

		if(2 > target_base || target_base > 16){
			printf("\n This base is unsupported. 2 <= radix <= 16 only");
			continue;
		}

		// reformat input and find location of radix point
		radix_point_loc = reformat_bad_numbers(base_x_inp, init_base);

		// TODO: add more detailed error numbers
		if(radix_point_loc < 0){
			printf("\n Invalid number format. Please try again.")
		}

		// separate the whole and decimal parts of the number into separate arrays
		for(int i = 0; i < radix_point_loc + 1; i++){
			
			if(base_x_inp[i] == '.'){
				whole_base_x[i] = '\0';
				break;
			}
			
			whole_base_x[i] = base_x_inp[i];
		}

		if(radix_point_loc > 0){
			for(int j = radix_point_loc+1; j < find_length(base_x_inp); j++){
	
				decimal_base_x[i] = base_x_inp[i];

			}
		}





	}

	return 0;
}