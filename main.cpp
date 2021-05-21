#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(512, 512), "Game 15"); //������� ���� ����������
	window.setFramerateLimit(60); // ����������� ������� ������
	Texture texture; // �������� � �������� ��������
	texture.loadFromFile("C:\\SFML-2.5.1\\Game15\\15.png");
	int blockWidht = 128;// ������ ������� ����� � ��������
	int logikPole[6][6] = { 0 }; // ���������� ������������� �������� ����
	Sprite sprite[17]; // ������ ��������
	// �������� �������� � ���������� ������ �������� ����
	int n = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++){
			n++;
			sprite[n].setTexture(texture);
			sprite[n].setTextureRect(IntRect(i * blockWidht, j * blockWidht, blockWidht, blockWidht));
			logikPole[i + 1][j + 1] = n;
		}
	while (window.isOpen()){	// ������� ���� ����������. �����������, ���� ������� ����
		Event event; // ��������� ������� ������� � ����
		while (window.pollEvent(event)){
			if (event.type == Event::Closed) // �������� ���� �������� �� �������
				window.close();
			if (event.type == Event::MouseButtonPressed) { // ��������� ������� ����
				if (event.key.code == Mouse::Left){
					Vector2i position = Mouse::getPosition(window); // ��������� ��������� � ����
					int x = position.x / blockWidht + 1;
					int y = position.y / blockWidht + 1;	
					int dx = 0; // �������������� ��������
					int dy = 0; // ������������ ��������
					if (logikPole[x + 1][y] == 16) { dx = 1; dy = 0; }; // ���� ������ ������ �����
					if (logikPole[x][y + 1] == 16) { dx = 0; dy = 1; }; // ���� ����� ������ �����
					if (logikPole[x][y - 1] == 16) { dx = 0; dy = -1; }; // ���� ������ ������ �����
					if (logikPole[x - 1][y] == 16) { dx = -1; dy = 0; }; // ���� ����� ������ �����
					int temp = logikPole[x][y]; // ��������� ���������� ��� ������ ������ ������
					logikPole[x][y] = 16;
					logikPole[x + dx][y + dy] = temp;
					sprite[16].move(-dx * blockWidht, -dy * blockWidht); // �������� �����������
					double speed = 6; // �������� ��������
					for (int i = 0; i < blockWidht; i += speed){
						sprite[temp].move(speed * dx, speed * dy); // ������� ��������� ����
						window.draw(sprite[16]); // ��������� ������� �����
						window.draw(sprite[temp]); // ��������� ���������� �����
						window.display();
					}
				}
			}
		}
		window.clear(Color::White); // ��������� ����
		// ��������� ������� ������� �� ���� ����� + ��������� �������
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				// ��������� �������� ������ �������� �����
				int n = logikPole[i + 1][j + 1];
				// �� ������������� �� ��� ��������������� ������
				sprite[n].setPosition(i * blockWidht, j * blockWidht);
				// ��������� �������
				window.draw(sprite[n]);
			}
		}
		window.display(); // ��������� ����	
	}
	return 0;
}