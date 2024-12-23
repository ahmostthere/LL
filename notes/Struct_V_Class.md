In C++, the choice between using a `struct` and a `class` often comes down to the intended use, style preferences, and design principles. Here are some key differences and guidelines for when to use each:

### 1. **Default Access Modifiers**
- **Struct**: Members are public by default.
- **Class**: Members are private by default.

**Use Case**: 
- Use a `struct` for plain data structures where you want to group related variables without much encapsulation (e.g., simple data containers).
- Use a `class` when you want to encapsulate data and behavior, controlling access with public, private, and protected members.

### 2. **Intended Use**
- **Struct**: Typically used for data structures that are primarily intended to hold data with little or no behavior (methods).
- **Class**: Typically used for objects that encapsulate both data and behavior, implementing methods that operate on the data.

**Use Case**:
- Use a `struct` for simple data objects (e.g., `Tile`, `Point`, `Vector`).
- Use a `class` for more complex objects that have significant functionality (e.g., `GameObject`, `Player`, `Enemy`).

### 3. **Inheritance**
- **Struct**: Supports inheritance just like classes, but the default access is public.
- **Class**: Supports inheritance, with private access as the default.

**Use Case**:
- You can use either for inheritance, but typically `class` is used when defining base classes with private/protected members to enforce encapsulation.

### 4. **Conventions and Readability**
- **Struct**: Generally conveys a simpler, more data-focused purpose. This makes it easier for others to understand that the primary intent is data storage.
- **Class**: Suggests a more complex object-oriented design with behavior and encapsulation.

**Use Case**:
- Use a `struct` when you want to convey that the focus is on storing data without complex behavior.
- Use a `class` when you want to signal that the object has a significant role in the application, with behavior defined through methods.

### Example

**Using a Struct for Simple Data:**
```cpp
struct Tile {
    std::string type;   // Type of tile
    bool passable;      // Can be walked on
};
```

**Using a Class for Complex Behavior:**
```cpp
class Player {
private:
    int health;
    int attackPower;

public:
    Player(int hp, int ap) : health(hp), attackPower(ap) {}

    void attack(Player& target) {
        target.takeDamage(attackPower);
    }

    void takeDamage(int damage) {
        health -= damage;
    }

    int getHealth() const { return health; }
};
```

### Summary
- Use `struct` for simple data structures where public access is appropriate.
- Use `class` when you need encapsulation, behavior, and a more complex object-oriented design.

Ultimately, the choice may also come down to personal or team conventions. The important thing is to maintain consistency throughout your codebase!