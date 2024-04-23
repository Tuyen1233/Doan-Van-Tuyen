#pragma once
#ifndef ENTITY_COMPONENT_SYSTEM_H
#define ENTITY_COMPONENT_SYSTEM_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

// Forward declarations
class Component;
class Entity;

// Define a type for component IDs
using ComponentID = std::size_t;

// Function to generate unique component IDs
inline ComponentID getComponentID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

// Template function to generate unique component type IDs
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentID();
    return typeID;
}

// Maximum number of components an entity can have
constexpr std::size_t maxComponents = 32;

// Define aliases for component bitset and array
using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

// Base class for components
class Component
{
public:
    Entity* entity; // Pointer to the entity this component belongs to

    virtual void init() {} // Virtual function for component initialization
    virtual void update() {} // Virtual function for component update
    virtual void draw() {} // Virtual function for component drawing

    virtual ~Component() {} // Virtual destructor
};

// Entity class representing game entities
class Entity
{
private:
    bool active; // Flag indicating whether the entity is active
    std::vector<std::unique_ptr<Component>> components; // Vector to store components
    ComponentArray componentArray; // Array to store pointers to components
    ComponentBitset componentBitset; // Bitset to track component existence

public:
    Entity() : active(true) {} // Constructor initializing entity as active

    // Function to update entity and its components
    void update()
    {
        for (auto& c : components) c->update(); // Update each component
        for (auto& c : components) c->draw(); // Draw each component
    }

    bool isActive() const { return active; } // Function to check if entity is active
    void destroy() { active = false; } // Function to mark entity as inactive

    // Function template to add a new component to the entity
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...)); // Create new component instance
        c->entity = this; // Set entity pointer in component

        std::unique_ptr<Component> uPtr{ c }; // Create unique pointer to component
        components.emplace_back(std::move(uPtr)); // Add component to vector

        componentArray[getComponentTypeID<T>()] = c; // Store component pointer in array
        componentBitset[getComponentTypeID<T>()] = true; // Set corresponding bit in bitset

        c->init(); // Initialize component
        return *c; // Return reference to component
    }

    // Function template to get a component of specified type
    template<typename T> T& getComponent() const
    {
        auto ptr = componentArray[getComponentTypeID<T>()]; // Get component pointer
        if (!ptr) {
            throw std::runtime_error("Component not found"); // Throw exception if component not found
        }
        return *static_cast<T*>(ptr); // Cast component pointer to specified type and return reference
    }
};

// Manager class to manage entities
class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities; // Vector to store entities

public:
    // Function to update all entities
    void update()
    {
        for (auto& e : entities) e->update(); // Update each entity
    }

    // Function to refresh entity list by removing inactive entities
    void refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->isActive();
            }),
            std::end(entities));
    }

    // Function to add a new entity
    Entity& addEntity()
    {
        Entity* e = new Entity(); // Create new entity instance
        std::unique_ptr<Entity> uPtr{ e }; // Create unique pointer to entity
        entities.emplace_back(std::move(uPtr)); // Add entity to vector
        return *e; // Return reference to entity
    }
};

#endif // ENTITY_COMPONENT_SYSTEM_H