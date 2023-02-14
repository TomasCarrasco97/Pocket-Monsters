//Tomas Carrasco
// COP 3003 Tomas Carrasco TR - 3:00 - 4:15pm
// Created a simple ui where the player can choose
//from a boy or girl giving them their own character to move around.


#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	// Create the window with a size of 800x600
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Game");

	// Load font
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error loading font." << std::endl;
	}

	// Welcome text
	sf::Text welcomeText;
	welcomeText.setFont(font);
	welcomeText.setString("Welcome to the Pocketmon Game!\n\nAre you a boy or a girl?");
	welcomeText.setCharacterSize(24);
	welcomeText.setFillColor(sf::Color::White);
	welcomeText.setPosition(200, 200);

	// Boy text
	sf::Text boyText;
	boyText.setFont(font);
	boyText.setString("Boy");
	boyText.setCharacterSize(24);
	boyText.setFillColor(sf::Color::Red);
	boyText.setPosition(350, 300);

	// Girl text
	sf::Text girlText;
	girlText.setFont(font);
	girlText.setString("Girl");
	girlText.setCharacterSize(24);
	girlText.setFillColor(sf::Color::Blue);
	girlText.setPosition(450, 300);

	// Character sprite
	sf::Texture characterTexture;
	if (!characterTexture.loadFromFile("character.png"))
	{
		std::cout << "Error loading character texture." << std::endl;
	}

	sf::Sprite characterSprite;
	characterSprite.setTexture(characterTexture);
	characterSprite.setPosition(100, 400);

	// Movement speed
	float speed = 5.0f;

	// Game loop
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close the window when the close button is clicked
			if (event.type == sf::Event::Closed)
				window.close();

			// Change the character texture when either the boy or girl text is clicked
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (boyText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					characterTexture.loadFromFile("boy_character.png");
				}
				else if (girlText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
				{
					characterTexture.loadFromFile("girl_character.png");
				}
			}
		}

		// Clear the window
		window.clear();

		// Handle character movement
		sf::Vector2f movement(0.0f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			movement.y -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			movement.y += speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			movement.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			movement.x += speed;
		}

		//Stops the character from going out of bounds
		if (characterSprite.getPosition().x < 0)
		{
			movement.x = 0;
			characterSprite.setPosition(0, characterSprite.getPosition().y);
		}
		if (characterSprite.getPosition().x + characterSprite.getGlobalBounds().width > window.getSize().x)
		{
			movement.x = 0;
			characterSprite.setPosition(window.getSize().x - characterSprite.getGlobalBounds().width, characterSprite.getPosition().y);
		}
		if (characterSprite.getPosition().y < 0)
		{
			movement.y = 0;
			characterSprite.setPosition(characterSprite.getPosition().x, 0);
		}
		if (characterSprite.getPosition().y + characterSprite.getGlobalBounds().height > window.getSize().y)
		{
			movement.y = 0;
			characterSprite.setPosition(characterSprite.getPosition().x, window.getSize().y - characterSprite.getGlobalBounds().height);
		}


		// Update character sprite position
		characterSprite.move(movement * (1.0f / 60.0f));

		// Draw everything
		window.draw(welcomeText);
		window.draw(boyText);
		window.draw(girlText);
		window.draw(characterSprite);

		// Display the window
		window.display();
	}

	return 0;
}


