#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(512, 512), "Game 15"); //Главное окно приложения
	window.setFramerateLimit(60); // Ограничение частоты кадров
	Texture texture; // Создание и загрузка текстуры
	texture.loadFromFile("C:\\SFML-2.5.1\\Game15\\15.png");
	int blockWidht = 128;// Размер стороны блока в пикселах
	int logikPole[6][6] = { 0 }; // Логическое представление игрового поля
	Sprite sprite[17]; // Массив спрайтов
	// Создание спрайтов и заполнение ячейки игрового поля
	int n = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++){
			n++;
			sprite[n].setTexture(texture);
			sprite[n].setTextureRect(IntRect(i * blockWidht, j * blockWidht, blockWidht, blockWidht));
			logikPole[i + 1][j + 1] = n;
		}
	while (window.isOpen()){	// Главный цикл приложения. Выполняется, пока открыто окно
		Event event; // Обработка очереди событий в окне
		while (window.pollEvent(event)){
			if (event.type == Event::Closed) // Закрытие окна нажатием на крестик
				window.close();
			if (event.type == Event::MouseButtonPressed) { // Обработка нажатий мыши
				if (event.key.code == Mouse::Left){
					Vector2i position = Mouse::getPosition(window); // Получение координат в окне
					int x = position.x / blockWidht + 1;
					int y = position.y / blockWidht + 1;	
					int dx = 0; // Горизонтальное смещение
					int dy = 0; // Вертикальное смещение
					if (logikPole[x + 1][y] == 16) { dx = 1; dy = 0; }; // Если справа пустое место
					if (logikPole[x][y + 1] == 16) { dx = 0; dy = 1; }; // Если снизу пустое место
					if (logikPole[x][y - 1] == 16) { dx = 0; dy = -1; }; // Если сверху пустое место
					if (logikPole[x - 1][y] == 16) { dx = -1; dy = 0; }; // Если слева пустое место
					int temp = logikPole[x][y]; // Временная переменная для замены пустой клетки
					logikPole[x][y] = 16;
					logikPole[x + dx][y + dy] = temp;
					sprite[16].move(-dx * blockWidht, -dy * blockWidht); // Анимация перемещения
					double speed = 6; // Скорость анимации
					for (int i = 0; i < blockWidht; i += speed){
						sprite[temp].move(speed * dx, speed * dy); // Двигаем выбранный блок
						window.draw(sprite[16]); // Отрисовка пустого блока
						window.draw(sprite[temp]); // Отрисовка выбранного блока
						window.display();
					}
				}
			}
		}
		window.clear(Color::White); // Установка фона
		// Установка каждого спрайта на свое место + Отрисовка спрайта
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				// Считываем значение ячейки игрового поля…
				int n = logikPole[i + 1][j + 1];
				// …и устанавливаем на нее соответствующий спрайт
				sprite[n].setPosition(i * blockWidht, j * blockWidht);
				// Отрисовка спрайта
				window.draw(sprite[n]);
			}
		}
		window.display(); // Отрисовка окна	
	}
	return 0;
}