#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAXLINE 256

typedef struct head {
	unsigned char type;
	unsigned int len;
} head;

typedef struct data_structure {
	head *header;
	void *data;
} data_structure;

// function that reads parameters from stdin and stores them into a data structure
data_structure *read_param(char *tmp) {
	data_structure *data = malloc(sizeof(data_structure));
	if (!data) {
		printf("malloc failed :(\n");
		return NULL;
	}
	data->header = malloc(sizeof(head));
	if (!data->header) {
		printf("malloc failed :(\n");
		return NULL;
	}
	data->header->len = 0;
	tmp = strtok(NULL, "\n ");
	memcpy(&data->header->type, tmp, sizeof(unsigned char));
	tmp = strtok(NULL, "\n ");
	char* first_name = malloc((strlen(tmp) + 1) * sizeof(char));
	if (!first_name) {
		printf("malloc failed :(\n");
		return NULL;
	}
	memcpy(first_name, tmp, (strlen(tmp) + 1) * sizeof(char));
	// different read depending on type of value
	if (data->header->type == '1') {
		int8_t bancnota1, bancnota2;
		tmp = strtok(NULL, "\n ");
		bancnota1 = atoi(tmp);
		tmp = strtok(NULL, "\n ");
		bancnota2 = atoi(tmp);
		tmp = strtok(NULL, "\n ");
		char* second_name = malloc((strlen(tmp) + 1) * sizeof(char));
		if (!second_name) {
			printf("malloc failed :(\n");
			return NULL;
		}
		memcpy(second_name, tmp, (strlen(tmp) + 1) * sizeof(char));
		data->data = malloc((strlen(first_name) + 1) * sizeof(char) + 2 * sizeof(int8_t) + (strlen(second_name) + 1) * sizeof(char));
		if (!data->data) {
			printf("malloc failed :(\n");
			return NULL;
		}
		memcpy(data->data, first_name, (strlen(first_name) + 1) * sizeof(char));
		data->header->len += (strlen(first_name) + 1) * sizeof(char);
		memcpy(data->data + data->header->len, &bancnota1, sizeof(bancnota1));
		data->header->len += sizeof(int8_t);
		memcpy(data->data + data->header->len, &bancnota2, sizeof(bancnota2));
		data->header->len += sizeof(int8_t);
		memcpy(data->data + data->header->len, second_name, (strlen(second_name) + 1) * sizeof(char));
		data->header->len += (strlen(second_name) + 1) * sizeof(char);
		free(first_name);
		free(second_name);
	} else if (data->header->type == '2') {
		int16_t bancnota1;
		int32_t bancnota2;
		tmp = strtok(NULL, "\n ");
		bancnota1 = atoi(tmp);
		tmp = strtok(NULL, "\n ");
		bancnota2 = atoi(tmp);
		tmp = strtok(NULL, "\n ");
		char* second_name = malloc((strlen(tmp) + 1) * sizeof(char));
		if (!second_name) {
			printf("malloc failed :(\n");
			return NULL;
		}
		memcpy(second_name, tmp, (strlen(tmp) + 1) * sizeof(char));
		data->data = malloc((strlen(first_name) + 1) * sizeof(char) + sizeof(int16_t) + sizeof(int32_t) + (strlen(second_name) + 1) * sizeof(char));
		if (!data->data) {
			printf("malloc failed :(\n");
			return NULL;
		}
		memcpy(data->data, first_name, (strlen(first_name) + 1) * sizeof(char));
		data->header->len += (strlen(first_name) + 1) * sizeof(char);
		memcpy(data->data + data->header->len, &bancnota1, sizeof(bancnota1));
		data->header->len += sizeof(int16_t);
		memcpy(data->data + data->header->len, &bancnota2, sizeof(bancnota2));
		data->header->len += sizeof(int32_t);
		memcpy(data->data + data->header->len, second_name, (strlen(second_name) + 1) * sizeof(char));
		data->header->len += (strlen(second_name) + 1) * sizeof(char);
		free(first_name);
		free(second_name);
	} else if (data->header->type == '3') {
		int32_t banknote1, banknote2;
		tmp = strtok(NULL, "\n ");
		banknote1 = atoi(tmp);
		tmp = strtok(NULL, "\n ");
		banknote2 = atoi(tmp);
		tmp = strtok(NULL, "\n ");
		char* second_name = malloc((strlen(tmp) + 1) * sizeof(char));
		if (!second_name) {
			printf("malloc failed :(\n");
			return NULL;
		}
		memcpy(second_name, tmp, (strlen(tmp) + 1) * sizeof(char));
		data->data = malloc((strlen(first_name) + 1) * sizeof(char) + 2 * sizeof(int32_t) + (strlen(second_name) + 1) * sizeof(char));
		if (!data->data) {
			printf("malloc failed :(\n");
			return NULL;
		}
		memcpy(data->data, first_name, (strlen(first_name) + 1) * sizeof(char));
		data->header->len += (strlen(first_name) + 1) * sizeof(char);
		memcpy(data->data + data->header->len, &banknote1, sizeof(banknote1));
		data->header->len += sizeof(int32_t);
		memcpy(data->data + data->header->len, &banknote2, sizeof(banknote2));
		data->header->len += sizeof(int32_t);
		memcpy(data->data + data->header->len, second_name, (strlen(second_name) + 1) * sizeof(char));
		data->header->len += (strlen(second_name) + 1) * sizeof(char);
		free(first_name);
		free(second_name);
	} else {
		return NULL;
	}
	return data;
}

int add_last(void **arr, int *len, data_structure *data)
{
	// calculating the total length of the array
	unsigned int position = 0, size;
	for (int i = 0; i < *len; i++) {
		memcpy(&size, *arr + position + sizeof(unsigned char), sizeof(unsigned int));
		position += size + sizeof(unsigned int) + sizeof(unsigned char);
	}
	(*len)++;
	*arr = realloc(*arr, position + sizeof(unsigned char) + sizeof(unsigned int) + data->header->len);
	if (!*arr) {
		printf("realloc failed :(\n");
		return 1;
	}
	// adding the data at the end of the array
	memcpy(*arr + position, &data->header->type, sizeof(unsigned char));
	position += sizeof(unsigned char);
	memcpy(*arr + position, &data->header->len, sizeof(unsigned int));
	position += sizeof(unsigned int);
	memcpy(*arr + position, data->data, data->header->len);
	free(data->data);
	free(data->header);
	free(data);
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	if (index > *len) {
		index = *len;
	}
	// calculating the total length of the array
	unsigned int realloc_size = 0, size;
	for (int i = 0; i < *len; i++) {
		memcpy(&size, *arr + realloc_size + sizeof(unsigned char), sizeof(unsigned int));
		realloc_size += size + sizeof(unsigned int) + sizeof(unsigned char);
	}
	// calculating the length of data before the insertion index
	unsigned int insert_idx = 0, size_i;
	for (int i = 0; i < index; i++) {
		memcpy(&size_i, *arr + insert_idx + sizeof(unsigned char), sizeof(unsigned int));
		insert_idx += size_i + sizeof(unsigned int) + sizeof(unsigned char);
	}
	unsigned int shift_idx = insert_idx + sizeof(unsigned char) + sizeof(unsigned int) + data->header->len;
	(*len)++;
	*arr = realloc(*arr, realloc_size + sizeof(unsigned char) + sizeof(unsigned int) + data->header->len);
	if (!*arr) {
		printf("realloc failed :(\n");
		return 1;
	}
	void *aux = malloc(realloc_size - insert_idx);
	if (!aux) {
		printf("malloc failed :(\n");
		return 1;
	}
	// shifting the data using an auxiliary variable
	memcpy(aux, *arr + insert_idx, realloc_size - insert_idx);
	memcpy(*arr + shift_idx, aux, realloc_size - insert_idx);
	free(aux);
	// inserting the data
	memcpy(*arr + insert_idx, &data->header->type, sizeof(unsigned char));
	insert_idx += sizeof(unsigned char);
	memcpy(*arr + insert_idx, &data->header->len, sizeof(unsigned int));
	insert_idx += sizeof(unsigned int);
	memcpy(*arr + insert_idx, data->data, data->header->len);
	free(data->data);
	free(data->header);
	free(data);
	return 0;
}

void find(void *data_block, int len, int index)
{
	if (index > len) {
		index = len;
	}
	// calculating the position of the desired data
	unsigned int position = 0, size;
	for (int i = 0; i < index; i++) {
		memcpy(&size, data_block + position + sizeof(unsigned char), sizeof(unsigned int));
		position += size + sizeof(unsigned int) + sizeof(unsigned char);
	}
	void *data;
	unsigned char *type = data_block + position;
	char *first, *second;
	// printing the data with respect to its type
	if (*type == '1') {
		data = data_block + position + sizeof(unsigned char) + sizeof(unsigned int);
		first = data;
		data += strlen(first) + 1;
		int8_t *b1, *b2;
		b1 = data;
		data += sizeof(int8_t);
		b2 = data;
		data += sizeof(int8_t);
		second = data;
		printf("Tipul %c\n", *type);
	    printf("%s pentru %s\n", first, second);
        printf("%"PRId8"\n%"PRId8"\n", *b1, *b2);
	} else if (*type == '2') {
		data = data_block + position + sizeof(unsigned char) + sizeof(unsigned int);
		first = data;
		data += strlen(first) + 1;
		int16_t *b1;
		int32_t *b2;
		b1 = data;
		data += sizeof(int16_t);
		b2 = data;
		data += sizeof(int32_t);
		second = data;
		printf("Tipul %c\n", *type);
	    printf("%s pentru %s\n", first, second);
        printf("%"PRId16"\n%"PRId32"\n", *b1, *b2);
	} else if (*type == '3') {
		data = data_block + position + sizeof(unsigned char) + sizeof(unsigned int);
		first = data;
		data += strlen(first) + 1;
		int32_t *b1, *b2;
		b1 = data;
		data += sizeof(int32_t);
		b2 = data;
		data += sizeof(int32_t);
		second = data;
		printf("Tipul %c\n", *type);
	    printf("%s pentru %s\n", first, second);
        printf("%"PRId32"\n%"PRId32"\n", *b1, *b2);
	} else {
		return;
	}
	printf("\n");
}

int delete_at(void **arr, int *len, int index)
{
	if (index > *len) {
		index = *len;
	}
	// total size of the data
	unsigned int realloc_size = 0, size;
	for (int i = 0; i < *len; i++) {
		memcpy(&size, *arr + realloc_size + sizeof(unsigned char), sizeof(unsigned int));
		realloc_size += size + sizeof(unsigned int) + sizeof(unsigned char);
	}
	// position of the data to be deleted
	unsigned int delete_idx = 0, size_i;
	for (int i = 0; i < index; i++) {
		memcpy(&size_i, *arr + delete_idx + sizeof(unsigned char), sizeof(unsigned int));
		delete_idx += size_i + sizeof(unsigned int) + sizeof(unsigned char);
	}
	int *data_len = *arr + delete_idx + sizeof(unsigned char);
	unsigned int shift_idx = delete_idx + sizeof(unsigned char) + sizeof(unsigned int) + *data_len;
	// overwriting the data to be deleted
	if (realloc_size - shift_idx) {
		memcpy(*arr + delete_idx, *arr + shift_idx, realloc_size - shift_idx);
	}
	(*len)--;
	if (*len != 0) {
		*arr = realloc(*arr, realloc_size - sizeof(unsigned char) - sizeof(unsigned int) - *data_len);
	} else {
		free(*arr);
	}
	if (!*arr) {
		printf("realloc failed :(\n");
		return 1;
	}
	return 0;
}

void print(void *arr, int len) {
	for (int i = 0; i < len; i++) {
		find(arr, len, i);
	}
}

void exit_program(void **arr, int len) {
	if (len) {
		free(*arr);
	}
	arr = NULL;
}

int main() {
	void *arr = NULL;
	int len = 0;
    char command[MAXLINE];
	char *tmp;
	do {
		fgets(command, MAXLINE, stdin);
		tmp = strtok(command, "\n ");
		if (strcmp(command, "insert") == 0) {
			data_structure *new_data = read_param(tmp);
			add_last(&arr, &len, new_data);
		} else if (strcmp(command, "insert_at") == 0) {
			tmp = strtok(NULL, "\n ");
			int idx = atoi(tmp);
			data_structure *new_data = read_param(tmp);
			add_at(&arr, &len, new_data, idx);
		} else if (strcmp(command, "find") == 0) {
			tmp = strtok(NULL, "\n ");
			int idx = atoi(tmp);
			find(arr, len, idx);
		} else if (strcmp(command, "delete_at") == 0) {
			tmp = strtok(NULL, "\n ");
			int idx = atoi(tmp);
			delete_at(&arr, &len, idx);
		} else if (strcmp(command, "print") == 0) {
			print(arr, len);
		}
	} while(strcmp(command, "exit") != 0);
	exit_program(&arr, len);
	return 0;
}