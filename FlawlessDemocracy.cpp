
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>

constexpr int grid_width{ 200 };
constexpr int grid_height{ 200 };

constexpr int cell_width{ 4 };
constexpr int cell_height{ 4 };

int random(const int max) {
    return rand() % max;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(grid_height * cell_height, grid_width * cell_width), "Flawless Democracy", sf::Style::Titlebar | sf::Style::Close);
    sf::RenderTexture texture;
    texture.create(grid_height * cell_height, grid_width * cell_width);

    std::vector<sf::RectangleShape> cells(grid_width * grid_height);

    // initialize grid
    for (int y = 0; y < grid_height; y++)
    {
        for (int x = 0; x < grid_width; x++)
        {
            sf::RectangleShape rect(sf::Vector2f(cell_width, cell_height));
            rect.setPosition(sf::Vector2f(x * cell_width, y * cell_height));
            rect.setFillColor(random(2) ? sf::Color::Blue : sf::Color::Red);
            cells[grid_width * y + x] = rect;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear();
        texture.clear();

        // get random cell coordinates
        int rx = random(grid_width);
        int ry = random(grid_height);

        sf::RectangleShape cell = cells[grid_width * ry + rx];

        // determine neighbor position relative to cell
        switch (random(4))
        {
            case 0:
                ry -= 1;
                break;
            case 1:
                rx += 1;
                break;
            case 2:
                ry += 1;
                break;
            case 3:
                rx -= 1;
                break;
        }

        // wraparound check
        if (ry >= grid_height)
        {
            ry = 0;
        }

        if (ry <= 0) {
            ry = grid_height - 1;
        }

        if (rx >= grid_width)
        {
            rx = 0;
        }

        if (rx <= 0)
        {
            rx = grid_width - 1;
        }

        //neighbor.setFillColor(random(2) ? sf::Color::Blue : sf::Color::Red);

        if (random(2) && cells[grid_width * ry + rx].getFillColor() != cell.getFillColor())
        {
            cells[grid_width * ry + rx].setFillColor(cell.getFillColor());
        }

        for (int i = 0; i < grid_height * grid_width; i++)
        {
            texture.draw(cells[i]);
        }

        texture.display();
        window.draw(sf::Sprite(texture.getTexture()));
        window.display();
    }

    return 0;
}
