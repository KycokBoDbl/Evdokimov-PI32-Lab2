#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <string>
using namespace std;
//названия классов персонажей
static const char* class_name[]
{
    "Мечник",
    "Лучник",
    "Копейщик",
    "Вор",
    "Молотоборец",
    "Щитоносец"
};
//классы персонажей
enum classes 
{
    swordsman = 0,
    archer,
    spearman,
    thief,
    hammerer,
    shieldbearer
};
//Экипировка
class Equipment {
public:
    char* name;
    int cost;
    Equipment(const char* name, int cost) {
        this->name = _strdup(name);
        this->cost = cost;
    }
    virtual ~Equipment() {
        free(name);
    }
    virtual void showInfo() const = 0;
};
// наследуемый класс оружия
class Weapon : public Equipment {
public:
    classes Class;
    int level;
    double damage;
    Weapon(const char* name, classes Class, int level, int cost, double damage) : Equipment(name, cost) {
        this->Class = Class;
        this->level = level;
        this->damage = damage;
    }
    void showInfo() const override {
        cout << "Оружие: " << name << ", Класс: " << class_name[Class] << ", Уровень: " << level << ", Урон: " << damage << ", Стоимость: " << cost << endl;
    }
};
// наследуемый класс брони
class Armor : public Equipment {
public:
    classes Class;
    int level;
    double defense;
    Armor(const char* name, classes Class, int level, int cost, double defense) : Equipment(name, cost) {
        this->Class = Class;
        this->level = level;
        this->defense = defense;
    }

    void showInfo() const override {
        cout << "Броня: " << name << ", Класс: " << class_name[Class] << ", Уровень: " << level << ", Защита: " << defense << ", Стоимость: " << cost << endl;
    }
};
// наследуемый класс расходуемых предметов
class Item : public Equipment {
public:
    char* description;
    Item(const char* name, const char* description, int cost) : Equipment(name, cost) {
        this->description = _strdup(description);
    }
    ~Item() {
        free(description);
    }
    void showInfo() const override {
        cout << "Предмет: " << name << ", Описание: " << description << ", Стоимость: " << cost << endl;
    }
};
// класс инвентаря
class Inventory {
public:
    int slots;
    Equipment* equipments[100];
    Inventory() {
        slots = 0;
    }
    ~Inventory() {
        for (int i = 0; i < slots; ++i) delete equipments[i];
    }
    //добавление оружия
    void add_weapon(Weapon* weapon) {
        if (slots < 100) {
            equipments[slots++] = weapon;
        }
        else {
            cout << "Инвентарь полон" << endl;
        }
    }
    //добавление брони
    void add_armor(Armor* armor) {
        if (slots < 100) {
            equipments[slots++] = armor;
        }
        else {
            cout << "Инвентарь полон" << endl;
        }
    }
    //добавление расходуемого предмета
    void add_item(Item* item) {
        if (slots < 100) {
            equipments[slots++] = item;
        }
        else {
            cout << "Инвентарь полон" << endl;
        }
    }
    //показать содержимое
    void showInventory() const {
        cout << "Инвентарь:" << endl;
        for (int i = 0; i < slots; ++i) {
            equipments[i]->showInfo();
        }
    }
};
//класс персонажа
class Character {
public:
    string username;
    classes Class;
    int level;
    double health;
    double damage;
    double armor;
    double speed;
    // конструктор по умолчанию
    Character() : username(""), Class(swordsman), level(1), health(100), damage(10), armor(5), speed(3) {}
    // конструктор с параметрами
    Character(const string& username, classes Class, int level, double health, double damage, double armor, double speed)
        : username(username), Class(Class), level(level), health(health), damage(damage), armor(armor), speed(speed) {}
    //вывод характеристик персонажа
    void showStats() const {
        cout << "Имя: " << username << endl;
        cout << "Класс: " << class_name[Class] << endl;
        cout << "Уровень: " << level << endl;
        cout << "Здоровье: " << health << endl;
        cout << "Урон: " << damage << endl;
        cout << "Броня: " << armor << endl;
        cout << "Скорость: " << speed << endl;
    }
    //повышение уровня (изменение характеритик)
    void levelUp() {
        int levels;
        cout << "Введите количество повышенных уровней: ";
        do {
            cin >> levels;
            while (cin.get() != '\n');
        } while (levels < 0 || level + levels > 100);

        if (levels > 0) {
            cout << "Распределите полученные очки навыков:" << endl;
            for (int i = 0; i < levels; i++) {
                int choice;
                cout << "Оставшиеся очки: " << levels - i << endl;
                cout << "1) Здоровье\n2) Урон\n3) Броня\n4) Скорость" << endl;
                do {
                    cin >> choice;
                    while (cin.get() != '\n');
                } while (choice < 1 || choice > 4);

                switch (choice) {
                case 1:
                    health += 5;
                    break;
                case 2:
                    damage++;
                    break;
                case 3:
                    armor++;
                    break;
                case 4:
                    speed++;
                    break;
                }
            }
            level += levels;
        }
    }
};
//класс игрока
class Player {
public:
    Character character;
    Inventory inventory;
    Player(const Character& character) : character(character), inventory() {}
    //создание стартового инвентаря
    void set_inventory() {
        Weapon* weapon;
        Armor* armor;
        Item* item;
        item = new Item("Зелье лечения", "Восстанавливает 30 здоровья", 10);
        inventory.add_item(item);
        item = new Item("Телепортирующее зеркало", "Позволяет вернуться в стартовый город", 30);
        inventory.add_item(item);
        int Class = (classes)character.Class;
        switch (Class)
        {
        case 0:
            weapon = new Weapon("Меч новичка", swordsman, 1, 20, 4);
            inventory.add_weapon(weapon);
            armor = new Armor("Броня мечника", swordsman, 1, 15, 3);
            inventory.add_armor(armor);
            break;
        case 1:
            weapon = new Weapon("Лук новичка", archer, 1, 20, 3);
            inventory.add_weapon(weapon);
            armor = new Armor("Доспехи лучника", archer, 1, 15, 2);
            inventory.add_armor(armor);
            break;
        case 2:
            weapon = new Weapon("Копьё новичка", spearman, 1, 25, 5);
            inventory.add_weapon(weapon);
            armor = new Armor("Броня копейщика", spearman, 1, 18, 3);
            inventory.add_armor(armor);
            break;
        case 3:
            weapon = new Weapon("Кинжалы новичка", thief, 1, 15, 3);
            inventory.add_weapon(weapon);
            armor = new Armor("Лёгкая броня вора", thief, 1, 10, 1);
            inventory.add_armor(armor);
            break;
        case 4:
            weapon = new Weapon("Молот новичка", hammerer, 1, 30, 6);
            inventory.add_weapon(weapon);
            armor = new Armor("Тяжёлая броня молотоборца", hammerer, 1, 20, 4);
            inventory.add_armor(armor);
            break;
        default:
            weapon = new Weapon("Щит новичка", shieldbearer, 1, 20, 2);
            inventory.add_weapon(weapon);
            armor = new Armor("Броня щитоносца", shieldbearer, 1, 17, 5);
            inventory.add_armor(armor);
            break;
        }
    }
    void showStats() const {
        character.showStats();
    }
};
//создание персонажа
Character character_create() {
    int Class;
    cout << "Введите имя: ";
    string name;
    getline(cin, name);
    cout << "Выберете класс персонажа:\n1) Мечник\n2) Лучник\n3) Копейщик\n4) Вор\n5) Молотоборец\n6) Щитоносец" << endl;
    do {
        cin >> Class;
        while (cin.get() != '\n');
    } while (Class < 1 || Class > 6);
    Class--;
    int health;
    int damage;
    int armor;
    int speed;
    switch (Class) {
    case 0:health = 100; damage = 4; armor = 5; speed = 4; break;
    case 1:health = 80; damage = 7; armor = 1; speed = 7; break;
    case 2:health = 100; damage = 6; armor = 3; speed = 4; break;
    case 3:health = 90; damage = 3; armor = 2; speed = 9; break;
    case 4:health = 110; damage = 6; armor = 5; speed = 2; break;
    default:health = 120; damage = 2; armor = 8; speed = 3; break;
    }
    return Character(name, static_cast<classes>(Class), 1, health, damage, armor, speed);
}
int main() {
    setlocale(LC_ALL, "Rus");
    Character ch = character_create();
    Player player(ch);
    player.set_inventory();
    int choice;
    do {
        cout << "Список действий:" << endl;
        cout << "1) Посмотреть инвентарь" << endl;
        cout << "2) Посмотреть характеристики" << endl;
        cout << "3) Пересоздать персонажа" << endl;
        cout << "4) Повысить уровень персонажу" << endl;
        cout << "5) Работа с динамическим массивом объектов" << endl;
        cout << "6) Работа с массивом динамических объектов" << endl;
        cout << "7) Завершение работы" << endl;
        do {
            cin >> choice;
            while (cin.get() != '\n');
        } while (choice < 1 || choice > 7);
        switch (choice) {
        case 1:                                                                         //вывод содержимого инвентаря
            player.inventory.showInventory();
            break;
        case 2:                                                                         //вывод характеристик персонажа
            player.showStats();
            break;
        case 3: {                                                                       //пересоздание персонажа
            Character stats = character_create();
            player = Player(stats);
            player.set_inventory();
            cout << "Стартовый инвентарь создан" << endl;
            break;
        }  
        case 4:                                                                         //повышение уровня персонажа
            player.character.levelUp();
            break;
        case 5: {                                                                       //работа с динамическим массивом объектов (игроков)
            int numCharacters;
            cout << "Введите количество персонажей: ";
            cin >> numCharacters;
            Character* characters = new Character[numCharacters];
            while (cin.get() != '\n');
            for (int i = 0; i < numCharacters; ++i) {
                characters[i] = character_create();
            }

            for (int i = 0; i < numCharacters; ++i) {
                characters[i].showStats();
            }

            delete[] characters;
            break;
        }
        case 6: {                                                                       //работа с массивом динамических объектов (игроков)
            int numCharacters;
            cout << "Введите количество персонажей: ";
            cin >> numCharacters;
            Character** characterPtrs = new Character * [numCharacters];
            while (cin.get() != '\n');
            for (int i = 0; i < numCharacters; ++i) {
                characterPtrs[i] = new Character(character_create());
            }
            for (int i = 0; i < numCharacters; ++i) {
                characterPtrs[i]->showStats();
            }
            for (int i = 0; i < numCharacters; ++i) {
                delete characterPtrs[i];
            }
            delete[] characterPtrs;
            break;
        }
        default:  break;                                                                 //завершение работы
           
        }
    } while (choice != 7);
}

