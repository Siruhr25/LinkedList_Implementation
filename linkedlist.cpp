#include <iostream>
#include <GL/glut.h> // OpenGL Utility Toolkit

// Define window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Define a struct for a node in the linked list
struct Node {
    int data;
    Node* next;
    
    // Constructor to initialize a node with given data and next pointer
    Node(int value) : data(value), next(nullptr) {}
};

Node* head = nullptr; // Global pointer to the head of the linked list

// Function to insert a new node at the beginning of the linked list
void insertAtBeginning(int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

// Function to delete a node with given value from the linked list
void deleteNode(int value) {
    if (head == nullptr) {
        return;
    }
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* prev = nullptr;
    Node* current = head;
    while (current != nullptr && current->data != value) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        std::cout << "Node with value " << value << " not found." << std::endl;
        return;
    }
    prev->next = current->next;
    delete current;
}

// Function to print the linked list
void printList() {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

// Function to display linked list using OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    
    // Draw linked list nodes
    Node* temp = head;
    int x = 100;
    while (temp != nullptr) {
        glBegin(GL_POLYGON);
        for (float angle = 0; angle <= 2 * 3.14159; angle += 0.01) {
            glVertex2f(x + 20 * cos(angle), 300 + 20 * sin(angle)); // Draw circle representing node
        }
        glEnd();
        glRasterPos2i(x - 5, 300); // Set position for text
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, temp->data + '0'); // Render data as text
        x += 100; // Increment x coordinate for next node
        temp = temp->next;
    }
    glFlush();
}

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'i':
        case 'I':
            int value;
            std::cout << "Enter value to insert: ";
            std::cin >> value;
            insertAtBeginning(value);
            break;
        case 'd':
        case 'D':
            int delValue;
            std::cout << "Enter value to delete: ";
            std::cin >> delValue;
            deleteNode(delValue);
            break;
        case 'p':
        case 'P':
            printList();
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
    glutPostRedisplay(); // Redraw the scene
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Linked List Operations using OpenGL");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
