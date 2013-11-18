char ** recebeDados(char *buf){
	char *dados[5];
	char *result = NULL;
	int count = 0;
	result = strtok(buf, " ");
	while (result != NULL) {  
	    dados[count] = result;
	    result = strtok(NULL," ");
	    count++;
	}
	return dados;
}