#include "Reservoir.h"

void addReservoir(Reservoir*& reservoirs, int& count, const Reservoir& newReservoir) {
    Reservoir* temp = new Reservoir[count + 1];
    for (int i = 0; i < count; ++i) {
        temp[i] = reservoirs[i];
    }
    temp[count] = newReservoir;
    delete[] reservoirs;
    reservoirs = temp;
    ++count;
}

void deleteReservoir(Reservoir*& reservoirs, int& count, int index) {
    if (index < 0 || index >= count) {
        cout << "Invalid index!" << endl;
        return;
    }

    Reservoir* temp = new Reservoir[count - 1];
    for (int i = 0, j = 0; i < count; ++i) {
        if (i != index) {
            temp[j++] = reservoirs[i];
        }
    }
    delete[] reservoirs;
    reservoirs = temp;
    --count;
}

void displayAllReservoirs(Reservoir* reservoirs, int count) {
    if (count == 0) {
        cout << "No reservoirs available." << endl;
        return;
    }
    for (int i = 0; i < count; ++i) {
        cout << "Reservoir #" << (i + 1) << ":" << endl;
        reservoirs[i].display();
        cout << "---------------------" << endl;
    }
}

void saveToFile(Reservoir* reservoirs, int count, const char* filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Error opening file for saving!" << endl;
        return;
    }
    for (int i = 0; i < count; ++i) {
        reservoirs[i].saveToFile(outFile);
    }
    outFile.close();
    cout << "Data saved to " << filename << endl;
}

void loadFromFile(Reservoir*& reservoirs, int& count, const char* filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Error opening file for loading!" << endl;
        return;
    }

    delete[] reservoirs;
    reservoirs = nullptr;
    count = 0;

    while (inFile.peek() != EOF) {
        Reservoir temp;
        temp.loadFromFile(inFile);
        addReservoir(reservoirs, count, temp);
    }
    inFile.close();
    cout << "Data loaded from " << filename << endl;
}

void showMenu() {
    cout << endl;
    cout << "1. Add Reservoir" << endl;
    cout << "2. Delete Reservoir" << endl;
    cout << "3. Display All Reservoirs" << endl;
    cout << "4. Save to File" << endl;
    cout << "5. Load from File" << endl;
    cout << "0. Exit" << endl;
    cout << endl;
    cout << "Choose an option\n\n--> ";
}

int main() {
    Reservoir* reservoirs = nullptr;
    int count = 0;
    char filename[256] = "reservoirs.bin";

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            char name[100], type[100];
            double width, length, maxDepth;

            cout << "Enter reservoir name\n\n--> ";
            cin.ignore();
            cin.getline(name, 100);

            cout << "Enter reservoir type (e.g., 'Sea', 'Lake')\n\n--> ";
            cin.getline(type, 100);

            cout << "Enter width\n\n--> ";
            cin >> width;

            cout << "Enter length\n\n--> ";
            cin >> length;

            cout << "Enter max depth\n\n--> ";
            cin >> maxDepth;

            Reservoir newReservoir(name, type, width, length, maxDepth);
            addReservoir(reservoirs, count, newReservoir);

            cout << "Reservoir added" << endl;
            break;
        }
        case 2: {
            int index;
            cout << "Enter the index of the reservoir to delete (1-based)\n\n--> ";
            cin >> index;

            deleteReservoir(reservoirs, count, index - 1);
            cout << "Reservoir deleted" << endl;
            break;
        }
        case 3:
            displayAllReservoirs(reservoirs, count);
            break;
        case 4:
            saveToFile(reservoirs, count, filename);
            break;
        case 5:
            loadFromFile(reservoirs, count, filename);
            break;
        case 0:
            break;
        default:
            cout << "The option pulls a prank on you" << endl;
        }
    } while (choice != 0);

    delete[] reservoirs;
    return 0;
}