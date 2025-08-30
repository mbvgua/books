/* Keypad array holding the keys in a grid arrangement*/
unsigned char keypad[4][4] = {{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{'C','0','=','+'}};

/* Function that checks the key that has been pressed on the keypad*/
unsigned char check_Keypad(char input_val){
	int row = input_val/4;
	int col = input_val%4;
	if((input_val>= 0) & (input_val<16)) return (keypad[row][col]);
	else return 0;
}
