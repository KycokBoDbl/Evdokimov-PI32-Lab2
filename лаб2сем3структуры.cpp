#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>

static const char* class_name[]
{
	"Мечник",
	"Лучник",
	"Копейщик",
	"Вор",
	"Молотоборец",
	"Щитоносец"
};
enum classes 
{
	archer = 0,
	swordsman,
	spearman,
	thief,
	hammerer,
	shieldbearer
};

struct Weapon
{
	char* name;
	classes Class;
	int level;
	int cost;
	double damage;
};
struct Armor
{
	char* name;
	classes Class;
	int level;
	int cost;
	double defense;
};
struct Item
{
	char* name;
	char* description;
	int cost;
};
struct inventory
{
	int w_slots;
	int a_slots;
	int i_slots;
	Weapon weapons[10];
	Armor armors[10];
	Item items[100];
};
struct character
{
	char* username;
	classes Class;
	int level;
	double health;
	double damage;
	double armor;
	double speed;
};
struct player
{
	character character;
	inventory inventory;
};

character character_create();
player set_character(character stats);
player set_inventory(player* stats);
Item item_create(const char* name, const char* description, int cost);
void add_item(player* stats, Item object);
Weapon weapon_create(const char* name, classes Сlass, int level, int cost, double damage);
void add_weapon(player* stats, Weapon weapon);
Armor armor_create(const char* name, classes Class, int level, int cost, double defense);
void add_armor(player* stats, Armor armor);
void show_inventory(player stats);
void show_stats(player stats);
void level_up(player* stats);
int main()
{
	setlocale(LC_ALL, "Rus");
	player Player;
	character stats = character_create();
	Player = set_character(stats);
	set_inventory(&Player);
	puts("Стартовый инвентарь создан");
	int choice;
	do
	{
		printf("Список действий:\n1)Посмотреть инвентарь\n2)Посмотреть характеристики\n3)Пересоздать персонажа\n4)Повысить уровень персонажу\n5)Завершение работы\n");
		do {
			scanf("%d", &choice);
			while (getchar() != '\n');
		} while (choice<1 || choice>5);
		switch (choice)
		{
		case 1:
			show_inventory(Player);
			break;
		case 2:
			show_stats(Player);
			break;
		case 3:
			stats = character_create();
			Player = set_character(stats);
			set_inventory(&Player);
			puts("Стартовый инвентарь создан");
			break;
		case 4:
			level_up(&Player);
			break;
		default:
			break;
		}
	} while (choice != 5);
}

character character_create()
{
	int Class;
	puts("Введите имя:");
	char* name = (char*)malloc(30 * sizeof(char));
	fgets(name, 30, stdin);
	puts("Выберете класс персонажа:\n1)Мечник\n2)Лучник\n3)Копейщик\n4)Вор\n5)Молотоборец\n6)Щитоносец");
	do {
		scanf("%d", &Class);
		while (getchar() != '\n');
	} while (Class < 1 || Class>6);
	Class--;
	character player;
	player.username = name;
	player.Class = (classes)Class;
	player.level = 1;
	switch (Class)
	{
	case 1:
		player.health = 100;
		player.damage = 4;
		player.armor = 5;
		player.speed = 4;
		break;
	case 2:
		player.health = 80;
		player.damage = 7;
		player.armor = 1;
		player.speed = 7;
		break;
	case 3:
		player.health = 100;
		player.damage = 6;
		player.armor = 3;
		player.speed = 4;
		break;
	case 4:
		player.health = 90;
		player.damage = 3;
		player.armor = 2;
		player.speed = 9;
		break;
	case 5:
		player.health = 110;
		player.damage = 6;
		player.armor = 5;
		player.speed = 2;
		break;
	default: 
		player.health = 120;
		player.damage = 2;
		player.armor = 8;
		player.speed = 3;
		break;
	}
	return player;
}
player set_character(character stats)
{
	player gamer;
	gamer.character = stats;
	gamer.inventory.w_slots = gamer.inventory.a_slots = gamer.inventory.i_slots = 0;
	return gamer;
}
player set_inventory(player* stats)
{
	Item health_potion = item_create("Зелье лечения", "Восстанавливает 30 здоровья", 10);
	add_item(stats, health_potion);
	Item teleport = item_create("Телепортирующее зеркало", "Позволяет вернуться в стартовый город", 30);
	add_item(stats, teleport);
	switch (stats->character.Class)
	{
	case 0:
		Weapon sword = weapon_create("Меч новичка", swordsman, 1, 20, 4);
		add_weapon(stats, sword);
		Armor sword_armor = armor_create("Броня мечника", swordsman, 1, 15, 3);
		add_armor(stats, sword_armor);
		break;
	case 1:
		Weapon bow = weapon_create("Лук новичка", archer, 1, 20, 3);
		add_weapon(stats, bow);
		Armor bow_armor = armor_create("Доспехи лучника", archer, 1, 15, 2);
		add_armor(stats, bow_armor);
		break;
	case 2:
		Weapon spear = weapon_create("Копьё новичка", spearman, 1, 25, 5);
		add_weapon(stats, spear);
		Armor spear_armor = armor_create("Броня копейщика", spearman, 1, 18, 3);
		add_armor(stats, spear_armor);
		break;
	case 3:
		Weapon dagger = weapon_create("Кинжалы новичка", thief, 1, 15, 3);
		add_weapon(stats, dagger);
		Armor thief_armor = armor_create("Лёгкая броня вора", thief, 1, 10, 1);
		add_armor(stats, thief_armor);
		break;
	case 4:
		Weapon hammer = weapon_create("Молот новичка", hammerer, 1, 30, 6);
		add_weapon(stats, hammer);
		Armor hammer_armor = armor_create("Тяжёлая броня молотоборца", hammerer, 1, 20, 4);
		add_armor(stats, hammer_armor);
		break;
	default: 
		Weapon shield = weapon_create("Щит новичка", shieldbearer, 1, 20, 2);
		add_weapon(stats, shield);
		Armor shield_armor = armor_create("Броня щитоносца", shieldbearer, 1, 17, 5);
		add_armor(stats, shield_armor);
		break;
	}
	return *stats;
}
Item item_create(const char* name, const char* description, int cost)
{
	Item new_item;
	new_item.name = _strdup(name);
	new_item.description = _strdup(description);
	new_item.cost = cost;
	return new_item;
}
void add_item(player* stats, Item object)
{
	if (stats->inventory.i_slots < 100)
	{
		stats->inventory.items[stats->inventory.i_slots] = object;
		stats->inventory.i_slots++;
	}
	else puts("Инвентарь полон");
}
Weapon weapon_create(const char* name, classes Сlass, int level, int cost, double damage)
{
	Weapon new_weapon;
	new_weapon.name = _strdup(name);
	new_weapon.Class = Сlass;
	new_weapon.level = level;
	new_weapon.cost = cost;
	new_weapon.damage = damage;
	return new_weapon;
}
void add_weapon(player* stats, Weapon weapon) 
{
	if (stats->inventory.w_slots < 10) 
	{
		stats->inventory.weapons[stats->inventory.w_slots] = weapon;
		stats->inventory.w_slots++;
	}
	else 
	{
		puts("Нет места для оружия");
	}
}
Armor armor_create(const char* name, classes Class, int level, int cost, double defense) 
{
	Armor new_armor;
	new_armor.name = _strdup(name);
	new_armor.Class = Class;
	new_armor.level = level;
	new_armor.cost = cost;
	new_armor.defense = defense;
	return new_armor;
}
void add_armor(player* stats, Armor armor) 
{
	if (stats->inventory.a_slots < 10) 
	{
		stats->inventory.armors[stats->inventory.a_slots] = armor;
		stats->inventory.a_slots++;
	}
	else {
		puts("Нет места для брони");
	}
}
void show_inventory(player stats)
{
	printf("Содержимое инвентаря:\n");
	printf("Оружие\n");
	for (int i = 0; i < stats.inventory.w_slots; i++) {
		Weapon weapon = stats.inventory.weapons[i];
		printf("Предмет %d: \n", i + 1);
		printf("  Название: %s\n", weapon.name);
		printf("  Класс: %s\n", class_name[weapon.Class]);
		printf("  Уровень: %d\n", weapon.level);
		printf("  Цена: %d\n", weapon.cost);
		printf("  Урон: %1f\n", weapon.damage);
	}
	printf("Броня\n");
	for (int i = 0; i < stats.inventory.a_slots; i++) {
		Armor armor = stats.inventory.armors[i];
		printf("Предмет %d: \n", i + 1);
		printf("  Название: %s\n", armor.name);
		printf("  Класс: %s\n", class_name[armor.Class]);
		printf("  Уровень: %d\n", armor.level);
		printf("  Цена: %d\n", armor.cost);
		printf("  Урон: %1f\n", armor.defense);
	}
	printf("Предметы\n");
	for (int i = 0; i < stats.inventory.i_slots; i++) {
		Item item = stats.inventory.items[i];
		printf("Предмет %d: \n", i + 1);
		printf("  Название: %s\n", item.name);
		printf("  Описание: %s\n", item.description);;
		printf("  Цена: %d\n", item.cost);
	}
}
void show_stats(player stats)
{
	printf("Ваше имя: %s", stats.character.username);
	printf("Ваш класс: %s\n", class_name[stats.character.Class]);
	printf("Статистика:\nУровень: %d\nЗдоровье: %.1f\nУрон: %.1f\nБроня: %.1f\nСкорость: %.1f\n",stats.character.level, 
		stats.character.health, stats.character.damage, stats.character.armor, stats.character.speed);
}
void level_up(player* stats)
{
	int levels;
	printf("Введите количество повышенных уровней: ");
	do {
		scanf("%d", &levels);
		while (getchar() != '\n');
	} while (levels<0 || stats->character.level+levels>100);
	if (levels)
	{
		printf("Распределите полученные очки навыков:\n");
		for (int i = 0; i < levels; i++)
		{
			int choice;
			printf("Оставшиеся очки: %d\n", levels - i);
			printf("1)Здоровье\n2)Урон\n3)Броня\n4)Скорость\n");
			do {
				scanf("%d", &choice);
				while (getchar() != '\n');
			} while (choice < 0 || choice>4);
			switch (choice)
			{
			case 1:
				stats->character.health+=5;
				break;
			case 2:
				stats->character.damage++;
				break;
			case 3:
				stats->character.armor++;
				break;
			default:
				stats->character.speed++;
				break;
			}
		}
	}
}