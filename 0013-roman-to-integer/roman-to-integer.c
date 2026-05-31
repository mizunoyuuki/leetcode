/* ローマ数字から整数への変換 */

/*
 * ローマ数字
 *
 * I V X L C D M
 *
 * I 1
 * V 5
 * X 10
 * L 50
 * C 100
 * D 500
 * M 1000
 * */

int romanToInt(char *s){
	int i = 0;
	int result = 0;
	while(s[i] != 0){
		if (s[i] == 'M'){
			result += 1000;
			i++;
			continue;
		}
		if (s[i] == 'D'){
			result += 500;
			i++;
			continue;
		}
		if (s[i] == 'C'){
			if (s[i+1] == 'D'){
				result += 400;
				i += 2;
				continue;
			}
			if (s[i+1] == 'M'){
				result += 900;
				i += 2;
				continue;
			}
			result += 100;
			i++;
			continue;
		}
		if (s[i] == 'L'){
			result += 50;
			i++;
			continue;
		}
		if (s[i] == 'X'){
			if (s[i+1] == 'L'){
				result += 40;
				i += 2;
				continue;
			}
			if (s[i+1] == 'C'){
				result += 90;
				i += 2;
				continue;
			}
			result += 10;
			i++;
			continue;
		}

		if (s[i] == 'V' ){
			result += 5;
			i++;
			continue;
		}
		
		if (s[i] == 'I'){
			if (s[i+1] == 'V'){
				result += 4;
				i += 2;
				continue;
			}
			if (s[i+1] == 'X'){
				result += 9;
				i += 2;
				continue;
			}

			result += 1;
			i++;
			continue;
		}


	}

	return result;
}
