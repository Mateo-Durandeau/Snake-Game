#include <SFML/Graphics.hpp>
#include <cstdlib> // Pour srand() et rand()
#include <ctime>   // Pour time()


// ################################################################################
// Initialisation des variables constantes

int square = 25;
int size = square * square;
int size_x = size;
int size_y = size;

int longueur = 1;

int dir = 2;

int pos_x = square*3;
int pos_y = square;

int pos_x_temp = pos_x;
int pos_y_temp = pos_y;

int snakeLength = 200;

int min = 0;
int max = square-1;

int status = 0;


// Constructeur des fonctions
// ################################################################################

void action(std::vector<sf::RectangleShape>& snakeBody);
void collision(std::vector<sf::RectangleShape>& snakeBody, int number);
void restart(std::vector<sf::RectangleShape>& snakeBody, int number);

int main()
{
    // Instance principale du jeu
    // ################################################################################

    sf::RenderWindow window(sf::VideoMode(size_x, size_y), "SFML Snake Game");

    std::vector<sf::RectangleShape> snakeBody;
    sf::Vector2i segmentSize(square, square); // Taille de chaque segment du serpent en entiers



    // ################################################################################
    // initialisation des pommes

    sf::RectangleShape apple(sf::Vector2f(square, square));
    apple.setFillColor(sf::Color::Red);

    srand(static_cast<unsigned int>(time(NULL)));

    int randomnumber_x = min + rand() % (max - min + 1);
    int randomnumber_y = min + rand() % (max - min + 1);

    int pos_apple_x = square * randomnumber_x;
    int pos_apple_y = square * randomnumber_y;

    apple.setPosition(pos_apple_x, pos_apple_y);

    // ################################################################################

    // Chargement de la couleur aléatoire
    int randomnumber_color = 0 + rand() % (4 - 0 + 1);

    // Chargement du corps du snack
    for (int i = 0; i < snakeLength; i++)
    {
        sf::RectangleShape segment(sf::Vector2f(segmentSize.x, segmentSize.y));
        segment.setFillColor(sf::Color::Yellow); // Couleur du segment
        segment.setPosition(pos_x_temp, pos_y_temp);
        pos_x_temp -= square;
        snakeBody.push_back(segment); // ajout d'un partie du corps dans le tableau bodysnake
    }


    // Rafraichissement de l'écran (vitesse de déplacement du serpent)
    window.setFramerateLimit(10);


    //####################################################################################

    while (window.isOpen())
    {
        sf::Event event;

        // GESTION DES EVENEMENTS
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Réagit uniquement aux événements d'appui sur une touche
            if (event.type == sf::Event::KeyPressed) {
                status = 1;
                if (event.key.code == sf::Keyboard::Left) dir = 1;
                else if (event.key.code == sf::Keyboard::Right) dir = 2;
                else if (event.key.code == sf::Keyboard::Up) dir = 3;
                else if (event.key.code == sf::Keyboard::Down) dir = 4;
            }
        }



        // GESTION DE LA POMME
        // ################################################################################
        sf::Vector2f head_pos = snakeBody[0].getPosition();
        sf::Vector2f apple_pos = apple.getPosition();

        if (head_pos.x == apple_pos.x and head_pos.y == apple_pos.y)
        {
            int randomnumber_x = min + rand() % (max - min + 1);
            int randomnumber_y = min + rand() % (max - min + 1);

            int pos_apple_x = square * randomnumber_x;
            int pos_apple_y = square * randomnumber_y;

            apple.setPosition(pos_apple_x, pos_apple_y);

            longueur += 1;
        }


        if (status != 0) {
            // GESTION DES DEPLACEMENT
            action(snakeBody);


            window.clear();

            // GESTION DES COLLISIONS
            collision(snakeBody, randomnumber_color);
        }

        if (status == 0) {
            randomnumber_color = 0 + rand() % (4 - 0 + 1);
            window.clear();
            window.draw(snakeBody[0]);
            window.draw(apple);
        }
        

        // GESTION DE L'AFFICHAGE
        for (int i = 0; i < longueur; i++)
        {
            window.draw(snakeBody[i]);
        }
        window.draw(apple);

        window.display();

    }
    return 0;
}


void action(std::vector<sf::RectangleShape>& snakeBody) {

    // Sauvegarde la position actuelle de la tête avant de la déplacer.
    sf::Vector2f prevPosition = snakeBody[0].getPosition();

    // Calcule la nouvelle position de la tête en fonction de la direction.
    if (dir == 1) {
        snakeBody[0].setPosition(prevPosition.x - square, prevPosition.y);
    }
    else if (dir == 2) {
        snakeBody[0].setPosition(prevPosition.x + square, prevPosition.y);
    }
    else if (dir == 3) {
        snakeBody[0].setPosition(prevPosition.x, prevPosition.y - square);
    }
    else if (dir == 4) {
        snakeBody[0].setPosition(prevPosition.x, prevPosition.y + square);
    }

    // Fait déplacer chaque segment suivant à la position précédente du segment qui le précède.
    for (int i = 1; i < longueur; i++) {
        sf::Vector2f currentPos = snakeBody[i].getPosition(); // Position actuelle du segment courant
        snakeBody[i].setPosition(prevPosition); // Déplace ce segment à la position précédente du segment devant lui
        prevPosition = currentPos; // Met à jour prevPosition pour le prochain segment
    }
}



void restart(std::vector<sf::RectangleShape>& snakeBody, int number)
{
    dir = 2;
    longueur = 1;
    status = 0;

    sf::Vector2i segmentSize(square, square); // Taille de chaque segment du serpent en entiers
    pos_x = square * 3;
    pos_y = square;

    snakeBody[0].setPosition(pos_x, pos_y);

    for (int i = 0; i < snakeLength; i++)
    {
        if (number == 0) snakeBody[i].setFillColor(sf::Color::Green); // Couleur du segment
        else if (number == 1) snakeBody[i].setFillColor(sf::Color::Blue); // Couleur du segment
        else if (number == 2) snakeBody[i].setFillColor(sf::Color::Yellow); // Couleur du segment
        else if (number == 3) snakeBody[i].setFillColor(sf::Color::Magenta); // Couleur du segment
        else if (number == 4) snakeBody[i].setFillColor(sf::Color::White); // Couleur du segment
        else snakeBody[i].setFillColor(sf::Color::Cyan); // Couleur du segment
    }
}


void collision(std::vector<sf::RectangleShape>& snakeBody, int number)
{
    sf::Vector2f head_pos = snakeBody[0].getPosition();
    
    for (int i = 1; i < longueur; i++)
    {
        sf::Vector2f body_pos = snakeBody[i].getPosition();
        if (head_pos.x == body_pos.x and head_pos.y == body_pos.y)
        {
            restart(snakeBody, number);
        }
    }

    if (head_pos.x < 0 or head_pos.y < 0) restart(snakeBody, number);
    if (head_pos.x > size_x or head_pos.y > size_y) restart(snakeBody, number);

}