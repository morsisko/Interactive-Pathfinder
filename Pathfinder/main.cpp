#include <SFML/Graphics.hpp>
#include <valarray>
#include <iostream>
#include "Map.h"
#include "Pathfinder.h"
#include "SimpleIni.h"

int main()
{
	CSimpleIniA ini;
	if (ini.LoadFile("config.ini") != SI_OK)
		return -1;

	const int WINDOW_WIDTH = atoi(ini.GetValue("window", "width", "1024"));
	const int WINDOW_HEIGTH = atoi(ini.GetValue("window", "height", "768"));
	const int MAP_WIDTH = atoi(ini.GetValue("map", "width", "20"));
	const int MAP_HEIGHT = atoi(ini.GetValue("map", "height", "19"));
	const int START_NODE_X = atoi(ini.GetValue("start_node", "x", "0"));
	const int START_NODE_Y = atoi(ini.GetValue("start_node", "y", "0"));
	const int STOP_NODE_X = atoi(ini.GetValue("end_node", "x", "15"));
	const int STOP_NODE_Y = atoi(ini.GetValue("end_node", "y", "15"));

	const int BOX_WIDTH_HEIGHT = atoi(ini.GetValue("visuals", "box_width_height", "40"));
	const int BOX_DRAW_OFFSET = atoi(ini.GetValue("visuals", "box_draw_offset", "3"));
	const int BOX_THICKNESS = atoi(ini.GetValue("visuals", "box_thickness", "2"));
	const int DRAW_TEXT = atoi(ini.GetValue("visuals", "draw_text", "1"));
	const int TEXT_SIZE = atoi(ini.GetValue("visuals", "text_size", "15"));
	const int TEXT_X_OFFSET = atoi(ini.GetValue("visuals", "text_x_offset", "8"));
	const int TEXT_Y_OFFSET = atoi(ini.GetValue("visuals", "text_y_offset", "8"));

	const int ALGORITHM = atoi(ini.GetValue("pathfinding", "algorithm", "0"));
	Pathfinder::Algorithm algorithm = Pathfinder::A_STAR;

	if (ALGORITHM == 1)
		algorithm = Pathfinder::DIJKSTRA;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Pathfinder by morsisko");
	sf::RectangleShape rect;
	sf::Text text;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	rect.setSize(sf::Vector2f(BOX_WIDTH_HEIGHT, BOX_WIDTH_HEIGHT));
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color::White);
	rect.setOutlineThickness(BOX_THICKNESS);
	text.setFont(font);
	text.setCharacterSize(TEXT_SIZE);
	text.setFillColor(sf::Color::Black);
	
	Point start(START_NODE_X, START_NODE_Y);
	Point stop(STOP_NODE_X, STOP_NODE_Y);

	Map map(MAP_WIDTH, MAP_HEIGHT);
	Pathfinder pathfinder(map, algorithm);

	pathfinder.begin(start.x, start.y, stop.x, stop.y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Right && !pathfinder.isEnd())
					pathfinder.oneStepSearch();

				else if (event.key.code == sf::Keyboard::Space && !pathfinder.isEnd())
					pathfinder.search();
			}

			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) && !pathfinder.isStarted())
			{			
				auto pos = sf::Mouse::getPosition(window);
				int x = pos.x;
				int y = pos.y;

				int logicX = (x - BOX_DRAW_OFFSET) / BOX_WIDTH_HEIGHT;
				int logicY = (y - BOX_DRAW_OFFSET) / BOX_WIDTH_HEIGHT;

				map.changeStateOfCell(logicX, logicY, sf::Mouse::isButtonPressed(sf::Mouse::Right));
			}
		}

		window.clear(sf::Color::White);
		Point currentPoint;
		for (int y = 0; y < map.getHeight(); y++)
		{
			for (int x = 0; x < map.getWidth(); x++)
			{
				bool drawText = false;
				currentPoint.x = x;
				currentPoint.y = y;
				rect.setPosition(BOX_DRAW_OFFSET + BOX_WIDTH_HEIGHT * x, BOX_DRAW_OFFSET + BOX_WIDTH_HEIGHT * y);
				text.setPosition(TEXT_X_OFFSET + BOX_WIDTH_HEIGHT * x, TEXT_Y_OFFSET + BOX_WIDTH_HEIGHT * y);

				if (currentPoint == start || currentPoint == stop)
					rect.setFillColor(sf::Color::Magenta);

				else if (pathfinder.isInFoundRoute(currentPoint))
					rect.setFillColor(sf::Color::Blue);

				else if (Node* tNode = pathfinder.getNodeFromClosedList(currentPoint))
				{
					text.setString(std::to_string(tNode->getF()));
					drawText = true;
					rect.setFillColor(sf::Color::Red);
				}

				else if (Node* tNode = pathfinder.getNodeFromOpenList(currentPoint))
				{
					text.setString(std::to_string(tNode->getF()));
					drawText = true;
					rect.setFillColor(sf::Color::Green);
				}

				else if (!map.isWalkable(currentPoint))
					rect.setFillColor(sf::Color::Yellow);

				else
					rect.setFillColor(sf::Color::White);

				window.draw(rect);
				if (drawText && DRAW_TEXT)
					window.draw(text);
			}
		}
		window.display();
	}

	return 0;
}