#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#define true 1
#define false 0
#define MAX_SIZE_MAZE 50
#define SIZE_FILE_NAME 100
#define ESC 27
#define	ENTER 13
#define BACKSPACE 8
#define	prnt(x, y, message) glRasterPos2f(x, y);\
for (char* c = message; *c != '\0'; c++)\
glutBitmapCharacter((void*)GLUT_BITMAP_TIMES_ROMAN_24, *c);

struct size
{
	struct window//размер окна
	{
		int width;//высота окна
		int height;//ширина окна

	}window;
	struct labyrint//размеры лабиринта, задаются пользователем
	{//количество квадратов WxH
		int width;//количество столбцов
		int height;//количество строк
	}labyrint;
	struct labyrint_depend_on_the_window//константые значения, толщина стенки лабиринта
	{
		GLfloat square;//размер квадрата лабиринта (в графических значених)
		GLfloat wall;//стена лабиринта (его толщина)
	}ldow;//сокращение labyrint_depend_on_the_window
	struct print//вывод данных о лабиринте
	{
		char* labyrint;
		char current_labyrint[MAX_SIZE_MAZE];
		int type;
		char* file_name;
		int flag;
	}print;
}_labyrint;
struct locate_red_square
{
	int row;
	int column;
};
struct square//таблица
{
	int left;
	int up;
	int* down;
	int* right;
	int status;
};
struct list
{
	int number;
	char name_labirynt[50];
	struct list* next_ptr;
};

struct locate_red_square current = { 0 };
struct square** number_square = { 0 };
struct size _size = { 0 };

void insert(struct list** start_ptr, const char name[], int number_type)
{
	struct list* new_ptr = NULL, * prev_ptr = NULL, * cur_ptr = *start_ptr;
	new_ptr = (struct list*)malloc(sizeof(struct list));
	if (new_ptr != NULL)
	{
		memset(new_ptr, 0, sizeof(struct list));
		strcpy(new_ptr->name_labirynt, name);
		new_ptr->number = number_type;
		new_ptr->next_ptr = NULL;

		while (cur_ptr != NULL)
		{
			prev_ptr = cur_ptr;
			cur_ptr = cur_ptr->next_ptr;
		}

		if (prev_ptr == NULL)
		{
			new_ptr->next_ptr = *start_ptr;
			*start_ptr = new_ptr;
		}
		else
		{
			prev_ptr->next_ptr = new_ptr;
			new_ptr->next_ptr = cur_ptr;
		}
	}
}
void initialization(void)
{
	for (int j = 0; j < _size.labyrint.height; j++)
	{
		for (int i = 0; i < _size.labyrint.width; i++)
		{
			number_square[j][i].up = 1;//по умолчанию стенка стоит
			number_square[j][i].left = 1;//по умолчанию стенка стоит
			number_square[j][i].down = &number_square[(j + 1) % _size.labyrint.height][i].up;
			number_square[j][i].right = &number_square[j][(i + 1) % _size.labyrint.width].left;
			number_square[j][i].status = 0;//по умолчанию не посещена
		}
	}
}
void renderString(void)
{
	char* prnt1 = _size.print.labyrint;
	while (*(--prnt1) != '\0');
	prnt1++;

	char* prnt2 = _labyrint.print.file_name;
	while (*(--prnt2) != '\0');
	prnt2++;

	struct list* type = NULL;
	insert(&type, "Not selected", 0);
	insert(&type, "Aldous Broder", 1);
	insert(&type, "Sidewinder", 2);
	insert(&type, "Binary tree", 3);
	insert(&type, "Hunt and kill", 4);
	while (type->number != _labyrint.print.type)
		type = type->next_ptr;

	char message1[] = { "Enter(h, w) -" };
	char message2[] = { "Current size(h, w)  -" };
	char message3[] = { "Current alghoritm  -" };
	char message4[] = { "File name    -" };
	char message5[] = { "q - aldous broder" };
	char message6[] = { "w - sidewinder" };
	char message7[] = { "e - binary tree" };
	char message8[] = { "r - hunt and kill" };
	char message9[] = { "i - import maze" };
	char message10[] = { "s - save maze" };
	char message11[] = { "esc  -  exit" };
	char message12[] = { "Be careful, the program" };
	char message13[] = { "does not respond during" };
	char message14[] = { "generation" };

	if (_labyrint.print.flag == 1)
	{
		prnt(-1.7, 0.92, "-->")
	}
	else
	{
		prnt(-1.7, 0.85, "-->")
	}
	prnt(-1.10, 0.92, prnt1)//для отображения ввода размера лабиринта
	prnt(0.65, 0.92, _size.print.current_labyrint)//для отображения текущего размера
	prnt(0.65, 0.85, type->name_labirynt)//для отображения типа алгоритма
	prnt(-1.10, 0.85, prnt2)//для отображения ввода имени файла
	prnt(-1.55, 0.92, message1)
	prnt(0.05, 0.92, message2)
	prnt(0.05, 0.85, message3)
	prnt(-1.55, 0.85, message4)
	prnt(-1.55, 0.6, message5)
	prnt(-1.55, 0.5, message6)
	prnt(-1.55, 0.4, message7)
	prnt(-1.55, 0.3, message8)
	prnt(-1.55, 0.2, message9)
	prnt(-1.55, 0.1, message10)
	prnt(-1.55, 0.0, message11)
	prnt(-1.65, -0.3, message12)
	prnt(-1.65, -0.4, message13)
	prnt(-1.65, -0.5, message14)
}
int from_char_to_int(void)
{
	while (*(--_size.print.labyrint) != '\0');
	_size.print.labyrint++;
	int check = 0;
	if (check = atoi(_size.print.labyrint))
	{
		while (*_size.print.labyrint && *(_size.print.labyrint++) != 'x');
		if (*_size.print.labyrint)
		{
			if (atoi(_size.print.labyrint))
			{
				_size.labyrint.width = check;
				_size.labyrint.height = atoi(_size.print.labyrint);
				while (*(--_size.print.labyrint) != '\0');
				_size.print.labyrint++;
				return 1;
			}
		}
	}
	while (*(--_size.print.labyrint) != '\0');
	memset(_size.print.labyrint, 0, MAX_SIZE_MAZE);
	_size.print.labyrint++;
	return 0;
}
void renderScene(void)//отрисовка лабиринта
{
	GLfloat x = -0.9;
	GLfloat y = 0.82 - _size.ldow.wall;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_QUADS);
	for (int j = 0; j < _size.labyrint.height; j++)
		for (int i = 0; i < _size.labyrint.width; i++)
		{
			if (number_square[j][i].up)
			{
				glVertex2f(x + _size.ldow.square * i, y - _size.ldow.square * j);
				glVertex2f(x + _size.ldow.square * (i + 1) + _size.ldow.wall, y - _size.ldow.square * j);
				glVertex2f(x + _size.ldow.square * (i + 1) + _size.ldow.wall, y - _size.ldow.square * j + _size.ldow.wall);
				glVertex2f(x + _size.ldow.square * i, y - _size.ldow.square * j + _size.ldow.wall);
			}
			if (number_square[j][i].left)
			{
				glVertex2f(x + _size.ldow.square * i, y - _size.ldow.square * j + _size.ldow.wall);
				glVertex2f(x + _size.ldow.square * i, y - _size.ldow.square * (j + 1));
				glVertex2f(x + _size.ldow.square * i + _size.ldow.wall, y - _size.ldow.square * (j + 1));
				glVertex2f(x + _size.ldow.square * i + _size.ldow.wall, y - _size.ldow.square * j + _size.ldow.wall);
			}
		}

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x + _size.ldow.square * (current.row + 1), y - _size.ldow.square * (current.column + 1) + _size.ldow.wall);
	glVertex2f(x + _size.ldow.square * current.row + _size.ldow.wall, y - _size.ldow.square * (current.column + 1) + _size.ldow.wall);
	glVertex2f(x + _size.ldow.square * current.row + _size.ldow.wall, y - _size.ldow.square * current.column);
	glVertex2f(x + _size.ldow.square * (current.row + 1), y - _size.ldow.square * current.column);
	glColor3f(1.0, 1.0, 1.0);


	glVertex2f(x, y - _size.ldow.square * _size.labyrint.height);
	glVertex2f(x + _size.ldow.square * _size.labyrint.width, y - _size.ldow.square * _size.labyrint.height);
	glVertex2f(x + _size.ldow.square * _size.labyrint.width, y - _size.ldow.square * _size.labyrint.height + _size.ldow.wall);
	glVertex2f(x, y - _size.ldow.square * _size.labyrint.height + _size.ldow.wall);

	glVertex2f(x + _size.ldow.square * _size.labyrint.width, y + _size.ldow.wall);
	glVertex2f(x + _size.ldow.square * _size.labyrint.width, y - _size.ldow.square * _size.labyrint.height);
	glVertex2f(x + _size.ldow.square * _size.labyrint.width + _size.ldow.wall, y - _size.ldow.square * _size.labyrint.height);
	glVertex2f(x + _size.ldow.square * _size.labyrint.width + _size.ldow.wall, y + _size.ldow.wall);
	glEnd();
	renderString();
	glutSwapBuffers();
}
void change_size_window(int width, int height)//если будут менять рамзмеры окна
{
	if (!height)
		height = 1;
	float window_ratio;
	window_ratio = 1.0 * width / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	if (height >= width)
		gluOrtho2D(-1.0, 1.0, -1.0 / window_ratio, 1.0 / window_ratio);
	else
		gluOrtho2D(-1.0 * window_ratio, 1.0 * window_ratio, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
}
void change_size_labyrint(void)
{
	if (!from_char_to_int())
		return;
	memset(_size.print.current_labyrint, 0, MAX_SIZE_MAZE);
	strcpy(_size.print.current_labyrint, _size.print.labyrint);
	memset(_size.print.labyrint, 0, MAX_SIZE_MAZE);

	if (_size.labyrint.width >= _size.labyrint.height)
		_size.ldow.square = 1.76 / _size.labyrint.width;
	else
		_size.ldow.square = 1.76 / _size.labyrint.height;
	_size.ldow.wall = _size.ldow.square / 5.0;

	free(number_square);
	number_square = (struct square**)calloc(_size.labyrint.height, sizeof(struct square*));
	if (number_square)
	{
		for (int i = 0; i < _size.labyrint.height; i++)
			*(number_square + i) = (struct square*)calloc(_size.labyrint.width, sizeof(struct square));
	}
	else
		exit(1);
	initialization();

	current.row = 0;
	current.column = 0;
	_labyrint.print.type = 0;

	glutReshapeFunc(change_size_window);
	renderScene();
	glutDisplayFunc(renderScene);
}
unsigned int rand2(void)
{
	unsigned long long int a = 2147483629;
	unsigned long long int c = 2147483587;
	unsigned long long int m = INT_MAX;
	static unsigned long long  int x = 1;
	x = ((a * x + c) % m ) ;
	
	return x;
}
unsigned int rand3(void)
{
	static unsigned long long int x = 10;
	x = ((2147483629 * x + 2147483587) % 2147483647);
	return x;
}

void O1_Aldous_Broder(void)
{
	initialization();
	int j = rand3() % _size.labyrint.height;
	int i = rand3() % _size.labyrint.width;
	number_square[j][i].status = 1;
	int square = _size.labyrint.width * _size.labyrint.height;

	int byt = 0, number_vector = 0, vector = 0;

	int slh = _size.labyrint.height - 1;
	int slw = _size.labyrint.width - 1;
	for (int count = 1; count < square;)
	{
		
		if (!byt)
		{
			byt = 16;
			number_vector = rand3();
		}

		byt -= 2;
		vector = number_vector & 3;
		number_vector >>= 2;

		switch (vector)
		{
		case 0:	(j > 0) ? --j : j;	break;
		case 1:	(i > 0) ? --i : i; break;
		case 2: (j < slh) ? ++j : j; break;
		case 3: (i < slw) ? ++i : i; break;
		}
		if (number_square[j][i].status == 0)
		{
			count++;
			number_square[j][i].status = 1;
			switch (vector)
			{
			case 0: *number_square[j][i].down = 0; break;
			case 1: *number_square[j][i].right = 0; break;
			case 2: number_square[j][i].up = 0; break;
			case 3: number_square[j][i].left = 0; break;
			}
		}
	}
	renderScene();

}
void Aldous_Broder(void)
{
	initialization();
	srand((unsigned int)time(NULL));
	int j = rand2() % _size.labyrint.height;
	int i = rand2() % _size.labyrint.width;
	number_square[j][i].status = 1;
	int square = _size.labyrint.width * _size.labyrint.height;

	int byt = 32;
	int number_vector = rand2();
	
	int vector = number_vector & 3;
	byt -= 4;
	number_vector >>= 2;
	long slh = _size.labyrint.height - 1;
	long slw = _size.labyrint.width - 1;
	for (int count = 1; count < square;)
	{
		switch (vector)
		{
			case 0:	(j > 0) ? --j : j;	break;
			case 1:	(i > 0) ? --i : i; break;
			case 2: (j < slh) ? ++j : j; break;
			case 3: (i < slw) ? ++i : i; break;
		}
		if (number_square[j][i].status == 0)
		{
			count++;
			number_square[j][i].status = 1;
			switch (vector)
			{
				case 0: *number_square[j][i].down = 0; break;
				case 1: *number_square[j][i].right = 0; break;
				case 2: number_square[j][i].up = 0; break;
				case 3: number_square[j][i].left = 0; break;
				
			}
			current.row = i;
			current.column = j;
			renderScene();
		}
		if(byt)
		{
			byt -= 4;
			vector = number_vector & 3;
			number_vector >>= 2;
		}
		else
		{
			byt = 32;
			number_vector = rand2();
		}
	}
	renderScene();
	glutIdleFunc(NULL);
}
void O2_sidewinder(void)
{
	initialization();
	int i = 0;
	int j = 0;
	int n = 1;
	long slw = _size.labyrint.width - 1;
	for (j = 0; j < slw; j++)
		*number_square[0][j].right = 0;

	int byt = 0, number_vector = 0, vector = 0;

	for (i = 1; i < _size.labyrint.height; i++)
	{
		for (j = 0, n = 1; j < slw; j++)
		{
			current.row = j;
			current.column = i;
			renderScene();
			if (!byt)
			{
				byt = 16;
				number_vector = rand2();
			}
			byt--;
			vector = number_vector & 1;
			number_vector >>= 1;

			if (vector)
			{
				number_square[i][j - rand3() % n].up = 0;
				n = 1;
			}
			else
			{
				*number_square[i][j].right = 0;
				n++;
			}
		}
		number_square[i][j - rand3() % n].up = 0;
	}
	renderScene();
}
void sidewinder(void)
{
	initialization();
	srand((unsigned int)time(NULL));
	int i = 0;
	int j = 0;
	int n = 1;

	for (j = 0; j < _size.labyrint.width - 1; j++)
		*number_square[0][j].right = 0;

	for (i = 1; i < _size.labyrint.height; i++)
	{
		for (j = 0, n = 1; j < _size.labyrint.width - 1; j++)
		{
			if (rand() & 1)
			{
				number_square[i][j - rand() % n].up = 0;
				n = 1;
			}
			else
			{
				*number_square[i][j].right = 0;
				n++;

			}
			current.row = j;
			current.column = i;
			renderScene();
		}
		number_square[i][j - rand() % n].up = 0;
	}
	renderScene();
	glutIdleFunc(NULL);
}
void O2_binary_tree(void)//двоичное дерево
{
	initialization();
	int j = 0;
	for (; j < _size.labyrint.width - 1; j++)
		*number_square[0][j].right = 0;
	int byt = 0, number_vector = 0, vector = 0;
	for (int i = 1; i < _size.labyrint.height; i++)
	{
		for (j = 0; j < _size.labyrint.width - 1; j++)
		{
			current.row = j;
			current.column = i;
			renderScene();
			if (!byt)
			{
				byt = 31;
				number_vector = rand2();
			}
			byt -= 1;
			vector = number_vector & 1;
			number_vector >>= 1;

			if (vector)
				*number_square[i][j].right = 0;
			else
				number_square[i][j].up = 0;
		}
		number_square[i][j].up = 0;
	}
	renderScene();
}
void binary_tree(void)//двоичное дерево
{
	initialization();
	int j = 0;

	for (; j < _size.labyrint.width - 1; j++)
		*number_square[0][j].right = 0;
	for (int i = 1; i < _size.labyrint.height; i++)
	{
		for (j = 0; j < _size.labyrint.width - 1; j++)
		{
			if (rand2() % 2)
				*number_square[i][j].right = 0;
			else
				number_square[i][j].up = 0;
		}
		number_square[i][j].up = 0;
		current.row = j;
		current.column = i;
		renderScene();
	}
	renderScene();
	glutIdleFunc(NULL);
}
struct coordinate
{
	int j;
	int i;
};
struct coordinate finding_ways3(int i, int j)// для hunt and kill
{
	struct coordinate min_coordinate;
	min_coordinate.j = j;
	min_coordinate.i = i;
	int byt = 0, number_vector = 0, vector = 0;
	current.row = j;
	current.column = i;
	renderScene();
	number_square[i][j].status = 1;
	while ((j + 1 < _size.labyrint.width && number_square[i][j + 1].status == 0) ||
		(i + 1 < _size.labyrint.height && number_square[i + 1][j].status == 0) ||
		(j - 1 >= 0 && number_square[i][j - 1].status == 0) ||
		(i - 1 >= 0 && number_square[i - 1][j].status == 0))
	{
		current.row = j;
		current.column = i;
		renderScene();
		if (!byt)
		{
			byt = 16;
			number_vector = rand2();
		}

		byt -= 2;
		vector = number_vector & 3;
		number_vector >>= 2;

		if (vector == 3 && j + 1 < _size.labyrint.width && number_square[i][j + 1].status == 0)
		{
			*number_square[i][j].right = 0;
			j++;
			number_square[i][j].status = 1;
			continue;
		}

		if (vector == 2 && i + 1 < _size.labyrint.height && number_square[i + 1][j].status == 0)
		{
			*number_square[i][j].down = 0;
			i++;
			number_square[i][j].status = 1;
			continue;
		}

		if (vector == 1 && j - 1 >= 0 && number_square[i][j - 1].status == 0)
		{
			number_square[i][j].left = 0;
			j--;
			if (min_coordinate.i == i && min_coordinate.j > j)
				min_coordinate.j = j;
			number_square[i][j].status = 1;
			continue;
		}
		if (vector == 0 && i - 1 >= 0 && number_square[i - 1][j].status == 0)
		{
			number_square[i][j].up = 0;
			i--;
			if (min_coordinate.i > i)
			{
				min_coordinate.i = i;
				min_coordinate.j = j;
			}
			number_square[i][j].status = 1;
			continue;
		}
	}
	current.row = j;
	current.column = i;
	renderScene();
	return min_coordinate;
}
void O2_hunt_and_kill(void)
{
	int i = 0;
	int j = 0;

	struct coordinate min_coordinate;
	min_coordinate.j = _size.labyrint.width;
	min_coordinate.i = _size.labyrint.height;
	initialization();

	i = rand2() % _size.labyrint.height;
	j = rand2() % _size.labyrint.width;
	current.row = j;
	current.column = i;
	renderScene();
	min_coordinate = finding_ways3(i, j);
	i = min_coordinate.i;
	j = min_coordinate.j;

	for (; i < _size.labyrint.height; i++, j = 0)
	{
		for (; j < _size.labyrint.width;)
		{
			current.row = j;
			current.column = i;
			renderScene();
			if (number_square[i][j].status == 1 && ((i > 0 && number_square[i - 1][j].status == 0) ||
				(j < _size.labyrint.width - 1 && number_square[i][j + 1].status == 0) || (j > 0 && number_square[i][j - 1].status == 0) ||
				(i < _size.labyrint.height - 1 && number_square[i + 1][j].status == 0)))
			{
				min_coordinate = finding_ways3(i, j);
				i = min_coordinate.i;
				j = min_coordinate.j;
				
			}
			else
				j++;
			
		}
	}
}
struct coordinate finding_ways(int i, int j)// для hunt and kill
{
	struct coordinate min_coordinate;
	min_coordinate.j = j;
	min_coordinate.i = i;
	int rnd = 0;

	number_square[i][j].status = 1;
	while ((j + 1 < _size.labyrint.width && number_square[i][j + 1].status == 0) ||
		(i + 1 < _size.labyrint.height && number_square[i + 1][j].status == 0) ||
		(j - 1 >= 0 && number_square[i][j - 1].status == 0) ||
		(i - 1 >= 0 && number_square[i - 1][j].status == 0))
	{
		current.row = j;
		current.column = i;
		renderScene();

		rnd = rand2() % 4;

		if (rnd == 3 && j + 1 < _size.labyrint.width && number_square[i][j + 1].status == 0)
		{
			*number_square[i][j].right = 0;
			j++;
			number_square[i][j].status = 1;
			continue;
		}

		if (rnd == 2 && i + 1 < _size.labyrint.height && number_square[i + 1][j].status == 0)
		{
			*number_square[i][j].down = 0;
			i++;
			number_square[i][j].status = 1;
			continue;
		}

		if (rnd == 1 && j - 1 >= 0 && number_square[i][j - 1].status == 0)
		{
			number_square[i][j].left = 0;
			j--;
			if (min_coordinate.i == i && min_coordinate.j > j)
				min_coordinate.j = j;
			number_square[i][j].status = 1;
			continue;
		}
		if (rnd == 0 && i - 1 >= 0 && number_square[i - 1][j].status == 0)
		{
			number_square[i][j].up = 0;
			i--;
			if (min_coordinate.i > i)
			{
				min_coordinate.i = i;
				min_coordinate.j = j;
			}
			number_square[i][j].status = 1;
			continue;
		}

	}
	current.row = j;
	current.column = i;
	renderScene();

	return min_coordinate;
}
void hunt_and_kill(void)
{
	int i = 0;
	int j = 0;

	struct coordinate min_coordinate;
	min_coordinate.j = _size.labyrint.width;
	min_coordinate.i = _size.labyrint.height;
	initialization();
	srand((unsigned int)time(NULL));

	i = rand2() % _size.labyrint.height;
	j = rand2() % _size.labyrint.width;

	min_coordinate = finding_ways(i, j);
	i = min_coordinate.i;
	j = min_coordinate.j;

	current.row = j;
	current.column = i;
	renderScene();
	for (; i < _size.labyrint.height; i++, j = 0)
	{
		for (; j < _size.labyrint.width;)
		{
			current.row = j;
			current.column = i;
			renderScene();
			if (number_square[i][j].status == 1 && ((i > 0 && number_square[i - 1][j].status == 0) || 
				(j < _size.labyrint.width - 1 && number_square[i][j + 1].status == 0) || (j > 0 && number_square[i][j - 1].status == 0) || 
				(i < _size.labyrint.height - 1 && number_square[i + 1][j].status == 0)))
			{
				min_coordinate = finding_ways(i, j);
				i = min_coordinate.i;
				j = min_coordinate.j;
			}
			else
				j++;
		}
	}

	renderScene();

}

void import(void)
{
	while (*(--_labyrint.print.file_name));
	_labyrint.print.file_name++;
	char message[] = { "\"not found file\"" };
	if (_labyrint.print.file_name == 0)
	{
		memset(_labyrint.print.file_name, 0, SIZE_FILE_NAME);
		strcpy(_labyrint.print.file_name, message);
	}
	else
	{
		FILE* input = fopen(_labyrint.print.file_name, "rb");
		if (input == NULL)
		{
			memset(_labyrint.print.file_name, 0, SIZE_FILE_NAME);
			strcpy(_labyrint.print.file_name, message);
		}
		else
		{
			int check_EOF = 0;
			check_EOF = fread(&_size.labyrint.height, sizeof(int), 1, input);
			check_EOF = fread(&_size.labyrint.width, sizeof(int), 1, input);
			while (*(--_size.print.labyrint));
			_size.print.labyrint++;
			check_EOF = sprintf(_size.print.labyrint,"%dx%d", _size.labyrint.height, _size.labyrint.width);
			change_size_labyrint();
			for (int i = 0; i < _size.labyrint.height; i++)
				for (int j = 0; j < _size.labyrint.width; j++)
					check_EOF = fread(&number_square[i][j], sizeof(number_square[i][j]), 1, input);
			fclose(input);
		}
	}
	
	renderScene();
	glutDisplayFunc(renderScene);
	return;
}
void save_labyrint()
{
	while (*(--_labyrint.print.file_name) != '\0');
	_labyrint.print.file_name++;
	char message[] = { "\"not found file\"" };
	if (_labyrint.print.file_name == 0)
	{
		memset(_labyrint.print.file_name, 0, SIZE_FILE_NAME);
		strcpy(_labyrint.print.file_name, message);
	}
	else
	{
		FILE* output = fopen(_labyrint.print.file_name, "wb");
		if (output == NULL)
		{
			memset(_labyrint.print.file_name, 0, SIZE_FILE_NAME);
			strcpy(_labyrint.print.file_name, message);
		}
		else
		{
			int check_EOF = 0;

			check_EOF = fwrite(&_size.labyrint.height, sizeof(int), 1, output);
			check_EOF = fwrite(&_size.labyrint.width, sizeof(int), 1, output);
			for (int i = 0; i < _size.labyrint.height; i++)
				for (int j = 0; j < _size.labyrint.width && check_EOF; j++)
					check_EOF = fwrite(&number_square[i][j], sizeof(number_square[i][j]), 1, output);
			fclose(output);
		}
	}
	renderScene();
	glutDisplayFunc(renderScene);
	return;
}
void keyboard(unsigned char key, int x, int y)//обработка клавиатуры
{
	if (_labyrint.print.flag == 1)
	{
		switch (key)
		{
			case ESC: exit(0);break;
			case 'q': _labyrint.print.type = 1; glutIdleFunc(renderScene); O1_Aldous_Broder(); break;
				
			case 'w': _labyrint.print.type = 2; glutIdleFunc(renderScene); O2_sidewinder(); break;
			case 'e': _labyrint.print.type = 3; glutIdleFunc(renderScene); O2_binary_tree(); break;
			case 'r': _labyrint.print.type = 4; glutIdleFunc(renderScene); O2_hunt_and_kill(); break;

			case 'i': _labyrint.print.flag = 2; memset(_labyrint.print.file_name, 0, SIZE_FILE_NAME); break;
			case 's': _labyrint.print.flag = 3;  memset(_labyrint.print.file_name, 0, SIZE_FILE_NAME); break;//save

			//для указания размеров лабиринта
			case 'x': *_size.print.labyrint++ = 'x'; break;
			case '0': *_size.print.labyrint++ = '0'; break;
			case '1': *_size.print.labyrint++ = '1'; break;
			case '2': *_size.print.labyrint++ = '2'; break;
			case '3': *_size.print.labyrint++ = '3'; break;
			case '4': *_size.print.labyrint++ = '4'; break;
			case '5': *_size.print.labyrint++ = '5'; break;
			case '6': *_size.print.labyrint++ = '6'; break;
			case '7': *_size.print.labyrint++ = '7'; break;
			case '8': *_size.print.labyrint++ = '8'; break;
			case '9': *_size.print.labyrint++ = '9'; break;

			//применить изменения размера лабиринта
			case ENTER:  change_size_labyrint(); break;
			case BACKSPACE:(*--_size.print.labyrint == '\0') ? _size.print.labyrint++ : ( *_size.print.labyrint = '\0'); break;//ограничение границ массива
		}
	}
	else
	{	
		switch (key)
		{
			case ESC: exit(0); break;
			case ENTER: (_labyrint.print.flag == 2) ? import() : save_labyrint(); _labyrint.print.flag = 1;  break;
			case BACKSPACE:(*--_labyrint.print.file_name == '\0') ? _labyrint.print.file_name++ : (*_labyrint.print.file_name = '\0'); break;
			default: (*_labyrint.print.file_name) = (char)key; _labyrint.print.file_name++; 
		}
	}
	renderScene();
	glutDisplayFunc(renderScene);
}

void help(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	char message[] = { "Click on the right mouse button to open the menu.." };
	prnt(-0.8, 0.5, message);;
	glutSwapBuffers();
}
void control(void)
{
	char message1[] = { "enter the size of the labyrint in 'number'x'number' format, then press 'enter'." };
	char message2[] = { "ex. 12x12" };
	char message3[] = { "q - aldous broder" };
	char message4[] = { "w - sidewinder" };
	char message5[] = { "e - binary tree" };
	char message6[] = { "r - hunt and kill" };
	char message7[] = { "To import(save) a file, first switch the layout with the 'i'('s') key, enter the file name and press enter." };
	char message8[] = { "There is no need to switch the keyboard back..." };
	char message9[] = { "f - import maze" };
	char message10[] = { "s - save maze" };
	char message11[] = { "esc  -  exit" };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	prnt(-1.1, 0.4, message1);
	prnt(-1.1, 0.3, message2);
	prnt(-1.1, 0.2, message3);
	prnt(-1.1, 0.1, message4);
	prnt(-1.1, 0.0, message5);
	prnt(-1.1, -0.1, message6);
	prnt(-1.1, -0.2, message7);
	prnt(-1.3, -0.3, message8);
	prnt(-1.1, -0.4, message9);
	prnt(-1.1, -0.5, message10);
	prnt(-1.1, -0.6, message11);
	glutSwapBuffers();
}
void about_programm(void)
{
	char message1[] = { "About creators:" };
	char message2[] = { "Motshenkov Denis Sergeevich" };
	char message3[] = { "Motshenkov Andrey Sergeevich" };
	char message4[] = { "students of the Polytechnic University, 1st year, group 4851004/10001" };
	char message5[] = { "Course work: maze generator" };
	char message6[] = { "date of creation - 2022" };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	prnt(-0.8, 0.5, message1);
	prnt(-0.8, 0.4, message2);
	prnt(-0.8, 0.3, message3);
	prnt(-0.8, 0.2, message4);
	prnt(-0.8, 0.1, message5);
	prnt(-0.8, 0.0, message6);

	glutSwapBuffers();
}
void processMenuEvents(int option) 
{
	switch (option) 
	{
		case 1: renderScene(); glutDisplayFunc(renderScene); break;
		case 2:	control(); glutDisplayFunc(control); break;
		case 3: help(); glutDisplayFunc(help); break;
		case 4: about_programm(); glutDisplayFunc(about_programm); break;
	}
}
void menu(void) 
{
	glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("generate labyrint", 1);
	glutAddMenuEntry("Control", 2);
	glutAddMenuEntry("Help", 3);
	glutAddMenuEntry("About programm", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char** argv)
{
	//размеры окна

	_size.window.width = 1280;
	_size.window.height = 720;
	_labyrint.print.file_name = (char*)calloc(SIZE_FILE_NAME, sizeof(char));
	if (_labyrint.print.file_name == NULL)
		exit(2);
	_labyrint.print.file_name++;
	//размеры лабиринта
	_size.labyrint.height = 10;
	_size.labyrint.width = 10;
	_size.print.labyrint = (char*)calloc(MAX_SIZE_MAZE, sizeof(char));
	if (_size.print.labyrint == NULL)
		exit(3);
	_size.print.labyrint++;//нулевой элемент есть барьер

	if (_size.labyrint.width >= _size.labyrint.height)
		_size.ldow.square = 1.76 / _size.labyrint.width;
	else
		_size.ldow.square = 1.76 / _size.labyrint.height;
	_size.ldow.wall = _size.ldow.square / 5.0;

	_labyrint.print.flag = 1;
	sprintf(_size.print.current_labyrint, "%dx%d", _size.labyrint.height, _size.labyrint.width);

	number_square = (struct square**)calloc(_size.labyrint.height, sizeof(struct square*));
	if (number_square)
	{
		for (int i = 0; i < _size.labyrint.height; i++)
			*(number_square + i) = (struct square*)calloc(_size.labyrint.width, sizeof(struct square));
		// инициализация
		initialization();
		
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(_size.window.width, _size.window.height);
		glutCreateWindow("курсовая");

		glutReshapeFunc(change_size_window);
		glutKeyboardFunc(keyboard);
		glutDisplayFunc(help);
		//renderScene();
		glutPostRedisplay();
		menu();
	//	glutDisplayFunc(renderScene);
		glutIdleFunc(NULL);
		
		//основной цикл 
		glutMainLoop();
	}
	else
		exit(4);
	return 0;
}