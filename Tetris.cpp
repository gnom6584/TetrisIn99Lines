#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <ctime>
const int width = 10;
const int height = 24;
const int delay = 20;
const float speed = 0.3f;
const char background = '-';

void draw(char c, float x, float y, const std::vector<int> &shape, std::vector<std::string> &lines) {
	for (int i = 1; i < shape.size(); i += 2) {
		lines[(int)(y - shape[i + 1])][(int)(x + shape[i])] = c;
	}
};

void rotateShape(std::vector<int> &shape, float direction, float originX, float originY) {
	for (int i = 1; i < shape.size(); i += 2) {
		float tempY = (shape[i] - originX) * direction;
		shape[i] = (int)(-(shape[i + 1] - originY) * direction + originX + 0.5f);
		shape[i + 1] = (int)(tempY + originY + 0.5f);
	}
};

bool checkCollision(float x, float y, const std::vector<int> &shape, const std::vector<std::string> &lines) {
	for (int i = 1; i < shape.size(); i += 2) {
		if (!((y - shape[i + 1]) >= 0 && (y - shape[i + 1]) < height && (x + shape[i]) >= 0 && (x + shape[i]) < width) || lines[(int)(y - shape[i + 1])][(int)(x + shape[i])] != background) {
			return true;
		}
	}
	return false;
};

int main() {
	std::string emptyLine = std::string(width, background);
	std::vector<std::string> lines;
	std::vector<int> shapes[7] = { 
		{'0', 0, 1, 1, 1, 2, 1, 3, 1}, 
		{'1', 1, 1, 1, 2, 2, 1, 2, 2}, 
		{'2', 1, 2, 2, 2, 2, 1, 3, 1}, 
		{'3', 1, 1, 2, 2, 2, 1, 3, 2}, 
		{'4', 1, 1, 2, 1, 3, 1, 1, 2},
		{'5', 1, 1, 2, 1, 3, 1, 3, 2},
		{'6', 1, 1, 2, 1, 3, 1, 2, 2} 
	};
	std::vector<int> currentShape = shapes[rand() % 7];
	for (int i = 0; i < height; i++) {
		lines.push_back(emptyLine);
	}
	char key = ' ';
	float x = width / 2;
	float y = height - 1;
	int lastFrame = -delay;
	while (key != 'q') {
		if (clock() - lastFrame > delay) {
			system("CLS"); //system("clear"); linux
			draw(background, x, y, currentShape, lines);
			if (_kbhit()) {
				key = _getch();
				if (key == 'r') {
					rotateShape(currentShape, 1, 2, 1);
					if (checkCollision(x, y, currentShape, lines)) {
						rotateShape(currentShape, -1, 2, 1);
					}
				}
				x += (key == 'a') ? -1 : ((key == 'd') ? 1 : 0);
				if (checkCollision(x, y, currentShape, lines)) {
					x -= (key == 'a') ? -1 : ((key == 'd') ? 1 : 0);
				}
			}
			y -= speed;
			if (checkCollision(x, y, currentShape, lines)) {
				y += speed;
				key = (y == height - 1) ? 'q' : 0;
				draw(currentShape[0], x, y, currentShape, lines);
				y = height - 1;
				x = width / 2;
				currentShape = shapes[rand() % 7];
				for (int i = 0; i < lines.size(); i++) {
					if(lines[i].find(background) == std::string::npos){
						lines.erase(lines.begin() + i);
						lines.push_back(emptyLine);
						i--;
					}
				}
			}
			lastFrame = clock();
			draw(currentShape[0], x, y, currentShape, lines);
			for (int i = height - 1; i >= 0; i--) {
				std::string longstr = std::string(width * 2, ' ');
				for (int x = 0; x < lines[i].length(); x++) {
					longstr[x * 2] = lines[i][x];
				}
				std::cout << longstr << std::endl;
			}
		}
	}
}
