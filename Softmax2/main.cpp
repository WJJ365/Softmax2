#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<assert.h>

static void softmax(float* input, size_t input_len) { //����Ʈ�ƽ� �Լ� ����
	assert(input);
	float m = -INFINITY;
	for (size_t i = 1; i < input_len; i++) {
		if (input[i] > m) {
			m = input[i];
		}
	}
	float sum = 0.0;
	for (size_t i = 0; i < input_len; i++) {
		sum += expf(input[i] - m);
	}
	float offset = m + logf(sum);
	for (size_t i = 0; i < input_len; i++) {
		input[i] = expf(input[i] - offset);
	}
}

struct matrix {
	float a[2][3]; //[��][��], ��� a
	float b[3][3]; //��� b
};

int main() {
	struct matrix A[40];
	struct matrix B[40];
	float sol[2][2];
	float ans[2][2]; // ��� ��� ����
	for (int j = 0; j < 3; j++) {
		printf("1��°�� ���� ����� %d���� �� ���Ҹ� ������ ���Ŀ� �°� �Է��ϼ���. ex) 1 2\n", j + 1);
		scanf_s("%f %f", &A[1].a[j][0], &A[1].a[j][1], sizeof(float), sizeof(float));
	}

	for (int j = 0; j < 2; j++) {
		printf("1��° �����Ϳ� ���� %d ��° ����ġ(������)�� ���� �� ���Ҹ� ������ ���Ŀ� �°� �Է��ϼ���. ex) 1 2 5\n", j + 1);
		scanf_s("%f %f %f", &B[1].b[j][0], &B[1].b[j][1], &B[1].b[j][2], sizeof(float), sizeof(float), sizeof(float));
	}
	for (int i = 0; i < 100; i++) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				ans[i][j] = !(i ^ j);
			}
		} // xor �����ڿ� not �����ڸ� ���� ���� ���(��� ���� ���� �׵��) ����.

		sol[0][0] = (A[1].a[0][0] * B[1].b[0][0] + A[1].a[1][0] * B[1].b[0][1] + A[1].a[2][0] * B[1].b[0][2]) / 10000;
		sol[1][1] = (A[1].a[0][1] * B[1].b[1][0] + A[1].a[1][1] * B[1].b[1][1] + A[1].a[2][1] * B[1].b[1][2]) / 10000;
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				ans[j][k] = sol[j][k]; // ��� ����� ����

			}
		}
		float arr[2] = { ans[0][0],ans[1][1] };

		softmax(arr, 2);
		printf("�� �����Ͱ� ���� Ȯ��: \n");
		for (int i = 0; i < 2; i++) {
			printf("%f\n", arr[i]);
		}
		if (arr[0] < arr[1]) {
			B[1].b[1][0] = B[1].b[1][0] + 0.05;
			B[1].b[1][1] = B[1].b[1][1] + 0.05;
			B[1].b[1][2] = B[1].b[1][2] + 0.05;
		}
		else if (arr[0] > arr[1]) {
			B[1].b[0][0] = B[1].b[1][0] + 0.05;
			B[1].b[0][1] = B[1].b[1][1] + 0.05;
			B[1].b[0][2] = B[1].b[1][2] + 0.05;
		}
	}
	system("PAUSE");
	return 0;
}
