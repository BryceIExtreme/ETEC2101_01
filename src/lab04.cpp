#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array_list.h>
#include <string>


class TextCircle
{
private:
	sf::Text my_text;
	sf::CircleShape my_circle;

public:
	TextCircle(sf::Font& the_font) : my_text(the_font)  // We HAVE to use this syntax to pass
	{								// the required parameter to my_text's constructor
		//my_text(the_font);		// Nice thought, but too late.
	}

	void set_position(float x, float y)
	{
		my_text.setPosition(sf::Vector2f(x, y));
		my_circle.setPosition(sf::Vector2f(x, y));
	}

	void set_text(std::string s)
	{
		my_text.setString(s);
		// Adjust circle radius to fit??
	}

	void draw(sf::RenderWindow& rw)
	{
		rw.draw(my_text);
		rw.draw(my_circle);
	}
};


int main(int argc, char** argv)
{
	// User's view
	WordReader WR("..\\..\\..\\media\\scowl.txt");
	for (int i = 0; i < 10; i++)
	{
		std::cout << WR.getWord() << "\n";
	}

	// Internal in WordReader
	// 1. Constructor should open file in binary mode.  Gets the file
	//      length (in bytes), saves as an attribute
	//     - fp.seekg(0, std::ios::end);
	//     - fp.tellg();
	// 2. getWord()
	//      a. Go to random byte location
	//      b. Adjust till we're at newline boundary
	//      c. call std::getline to read the line and return it.


	// This code is run before the game starts.  Note how SFML is very object-oriented (creating
	// objects and calling methods) rather than SDL, which is very C based (mostly calling functions
	// and passing around structs)
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "JasonW Lab4 Solution");
	sf::CircleShape test_circle(100.0f);
	test_circle.setFillColor(sf::Color(200, 255, 100, 255));
	test_circle.setPosition(sf::Vector2f(10.0f, 10.0f));
	test_circle.setOrigin(sf::Vector2f(100.0f, 100.0f));

	sf::Texture my_hand_image("..\\..\\..\\media\\hand.png");
	sf::Sprite my_hand_sprite(my_hand_image);
	my_hand_sprite.setRotation(sf::degrees(45.0f));
	my_hand_sprite.setPosition(sf::Vector2f(200.0f, 200.f));

	// Load a font and make a Text object from it.
	// Reference: https://www.sfml-dev.org/tutorials/3.0/graphics/text
	sf::Font my_font("..\\..\\..\\media\\Oswald\\static\\Oswald-Regular.ttf");
	sf::Text test_text(my_font);
	test_text.setString("Hello!");
	test_text.setCharacterSize(24);
	test_text.setFillColor(sf::Color(100, 255, 100, 128));
	test_text.setPosition(sf::Vector2f(50.0f, 50.0f));
	sf::FloatRect test_text_bounds = test_text.getLocalBounds();
	sf::Vector2f test_text_size = test_text_bounds.size;
	test_text.setOrigin(sf::Vector2f(test_text_size.x / 2.0f, test_text_size.y / 2.0f));
	test_text.setRotation(sf::degrees(-15));

	// Create the ArrayLists that will hold the data related to the falling circles
	//ssuds::ArrayList<TextCircle> my_circles;
	//TextCircle test(my_font);
	//my_circles.append(test);
	// Suggestion: make a collection of parallel arrays to store all DATA related to the
	// falling circles.
	ssuds::ArrayList<float> circle_xlist;
	ssuds::ArrayList<float> circle_ylist;
	ssuds::ArrayList<std::string> circle_strings;


	// This is the "GAME LOOP" -- it runs as long as the window is open.  The two main
	// parts of a game loop are input-handling and drawing.  You might want to add a third
	// section that does other (non-input-related) updates.
	while (window.isOpen())
	{
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ UPDATES (not input driven)              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// ....

		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ Input-handling (keyboard and mouse)     @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// std::optional is a new C++-17+ thing -- it's kind of like
		// in python, if a function doesn't return anything useful, None is
		// returned.
		// Normally you would use == like this in a while loop -- this is assigning a result to event
		// AND THEN using that value as the "truth-test" for the while condition
		while (const std::optional event = window.pollEvent())
		{
			// We use event to see if it's something we care about
			if (event->is<sf::Event::Closed>())
			{
				// The quit button was pressed.
				window.close();
			}
			else if (const sf::Event::KeyPressed* keyEvt = event->getIf<sf::Event::KeyPressed>())
			{
				// We get here if a key is pressed.  Now see if it's a key we care about
				if (keyEvt->code == sf::Keyboard::Key::Escape)
				{
					window.close();
				}
			}
			else if (const sf::Event::MouseButtonPressed* buttonEvt =
				event->getIf<sf::Event::MouseButtonPressed>())
			{
				// We get here if any mouse button is pressed.  Now see if it's
				// a button press that we care about
				if (buttonEvt->button == sf::Mouse::Button::Left)
				{
					// We get here if it's a left-mouse button pressed.  Move green circle
					// here
					//sf::Vector2f temp_pos(buttonEvt->position.x, buttonEvt->position.y);
					//test_circle.setPosition(temp_posT

					// Spawn a new circle
					circle_xlist.append(buttonEvt->position.x);
					circle_ylist.append(buttonEvt->position.y);
					circle_strings.append("test");
				}
			}
			// ... mouse moved
		}

		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ Drawing (to the window)     @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		window.clear();
		window.draw(test_circle);
		window.draw(my_hand_sprite);
		window.draw(test_text);
		// All circle-data lists have the same size
		for (int i = 0; i < circle_xlist.size(); i++)
		{
			float x = circle_xlist[i];
			float y = circle_ylist[i];
			std::string s = circle_strings[i];
			TextCircle temp(my_font);
			temp.set_position(x, y);
			temp.set_text(s);
			// Draw temp.
			temp.draw(window);
			// Resume @ 1:30pm
		}

		window.display();// Shows our drawings
	}
	return 0;
}