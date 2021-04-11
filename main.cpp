#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

void qSort(int windowWidth, int windowHeight, int maxNumber, int *foo, int arrSize, int *stack,
           sf::RenderWindow &window, int &start, int &end, int &top);

void insertionSort(int foo[], int arrSize, int &pos);

void iSort(int windowWidth, int windowHeight, int maxNumber, int *foo, int arrSize,
           sf::RenderWindow &window, int &pos);

void shuffleArray(int maxNumber, int *foo, int arrSize, int &start, int &end, int &top, int &pos, int &iteration);

void swap(int *value1, int *value2);

int partition(int foo[], int start, int end);

void quicksort(int foo[], int &start, int &end, int &top, int stack[]);

void bubbleSort(int foo[], int arrSize, int &iteration);

void bSort(int windowWidth, int windowHeight, int maxNumber, int *foo, int arrSize,
           sf::RenderWindow &window, int &iteration);


int main() {
    int windowWidth = 1500;
    int windowHeight = 1000;
    int maxNumber = 1000;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sorting Algorithms");

    int foo[2000];
    int arrSize = sizeof(foo) / sizeof(foo[0]);
    int start, end, top, pos, iteration;

    shuffleArray(maxNumber, foo, arrSize, start, end, top, pos, iteration);

    // Create an auxiliary stack
    int stack[end - start + 1];

    // push initial values of start and end to stack
    stack[++top] = start;
    stack[++top] = end;

    qSort(windowWidth, windowHeight, maxNumber, foo, arrSize, stack, window, start, end, top);
    window.display();

    bool quickSort = false;
    bool insertSort = false;
    bool bubbleSort = false;

    // run the program as long as the window is open
    while (window.isOpen()) {
        window.clear(sf::Color::Black);

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    quickSort = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    insertSort = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                    bubbleSort = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {

                    for (int i = 0; i < arrSize; ++i) {
                        foo[i] = rand() % maxNumber;
                    }

                    shuffleArray(maxNumber, foo, arrSize, start, end, top, pos, iteration);

                    // push initial values of start and end to stack
                    stack[++top] = start;
                    stack[++top] = end;

                    window.clear(sf::Color::Black);
                    qSort(windowWidth, windowHeight, maxNumber, foo, arrSize, stack, window, start, end, top);
                    window.display();
                    quickSort = false;
                    insertSort = false;
                    bubbleSort = false;
                }
            }
        }


        if (quickSort) {
            if (top != -1) {
                qSort(windowWidth, windowHeight, maxNumber, foo, arrSize, stack, window, start, end,
                      top);
                window.display();
            } else {
                quickSort = false;
            }
        } else if (insertSort) {
            if (pos > -1) {
                iSort(windowWidth, windowHeight, maxNumber, foo, arrSize, window, pos);
                window.display();
            } else {
                insertSort = false;
            }
        } else if (bubbleSort) {
            if (iteration < arrSize){
                bSort(windowWidth, windowHeight, maxNumber, foo, arrSize, window, iteration);
                window.display();
            }else{
                bubbleSort = false;
            }
        }
    }
    return 0;
}

void shuffleArray(int maxNumber, int *foo, int arrSize, int &start, int &end, int &top, int &pos, int &iteration) {
    start = 0;
    end = arrSize - 1;
    top = -1;
    pos = arrSize - 1;
    iteration = 0;
    for (int i = 0; i < arrSize; ++i) {
        foo[i] = rand() % maxNumber;
    }
}

void qSort(int windowWidth, int windowHeight, int maxNumber, int *foo, int arrSize, int *stack,
           sf::RenderWindow &window, int &start, int &end, int &top) {
    float width = ((float) windowWidth / (float) arrSize);
    float offset = 0;

    if (top != -1) {
        quicksort(foo, start, end, top, stack);
    }

    std::vector<sf::RectangleShape> rectangles(arrSize);
    for (int i = 0; i < rectangles.size(); ++i) {
        float height = (float) windowHeight * ((float) foo[i] / (float) maxNumber);
        rectangles[i] = sf::RectangleShape(sf::Vector2f(width, height));
        rectangles[i].setOrigin(0, 0);
        rectangles[i].move(offset, (float) windowHeight - height);
        rectangles[i].setFillColor(sf::Color(255, 255, 255));
        offset += width;
        window.draw(rectangles[i]);
    }
}

void iSort(int windowWidth, int windowHeight, int maxNumber, int *foo, int arrSize,
           sf::RenderWindow &window, int &pos) {

    float width = ((float) windowWidth / (float) arrSize);
    float offset = 0;
    if (pos > -1) {
        insertionSort(foo, arrSize, pos);
    }

    std::vector<sf::RectangleShape> rectangles(arrSize);
    for (int i = 0; i < rectangles.size(); ++i) {
        float height = (float) windowHeight * ((float) foo[i] / (float) maxNumber);
        rectangles[i] = sf::RectangleShape(sf::Vector2f(width, height));
        rectangles[i].setOrigin(0, 0);
        rectangles[i].move(offset, (float) windowHeight - height);
        rectangles[i].setFillColor(sf::Color(255, 255, 255));
        offset += width;
        window.draw(rectangles[i]);
    }
}

void bSort(int windowWidth, int windowHeight, int maxNumber, int *foo, int arrSize,
           sf::RenderWindow &window, int &iteration) {

    float width = ((float) windowWidth / (float) arrSize);
    float offset = 0;

    bubbleSort(foo, arrSize, iteration);

    std::vector<sf::RectangleShape> rectangles(arrSize);
    for (int i = 0; i < rectangles.size(); ++i) {
        float height = (float) windowHeight * ((float) foo[i] / (float) maxNumber);
        rectangles[i] = sf::RectangleShape(sf::Vector2f(width, height));
        rectangles[i].setOrigin(0, 0);
        rectangles[i].move(offset, (float) windowHeight - height);
        rectangles[i].setFillColor(sf::Color(255, 255, 255));
        offset += width;
        window.draw(rectangles[i]);
    }
}

void insertionSort(int foo[], int arrSize, int &pos) {
    int indexNew = pos - 1;
    int valueNew = foo[indexNew];
    while ((indexNew < arrSize - 1) && (valueNew > foo[indexNew + 1])) {
        foo[indexNew] = foo[indexNew + 1];
        indexNew++;
    }
    foo[indexNew] = valueNew;
    pos--;
}

void swap(int *value1, int *value2) {
    int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

int partition(int foo[], int start, int end) {
    int pivot = foo[end];

    int i = (start - 1);

    for (int j = start; j <= end - 1; j++) {
        if (foo[j] < pivot) {
            i++;
            swap(&foo[i], &foo[j]);
        }
    }
    swap(&foo[i + 1], &foo[end]);
    return i + 1;
}

void quicksort(int foo[], int &start, int &end, int &top, int stack[]) {
    if (top >= 0) {
        // Pop end and start
        end = stack[top--];
        start = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int p = partition(foo, start, end);

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > start) {
            stack[++top] = start;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < end) {
            stack[++top] = p + 1;
            stack[++top] = end;
        }
    }
}

void bubbleSort(int foo[], int arrSize, int &iteration) {
    // Last i elements are already in place
    for (int j = 0; j < arrSize - iteration - 1; j++) {
        if (foo[j] > foo[j + 1]) {
            swap(&foo[j], &foo[j + 1]);
        }
    }
    iteration++;
}