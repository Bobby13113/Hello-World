# Getting Started with AI Overlords Game Development

## Prerequisites

Before you begin, ensure you have the following installed:

1. **Unreal Engine 5.0 or later**
   - Download from [unrealengine.com](https://www.unrealengine.com/)

2. **Visual Studio 2022** or **Visual Studio Code**
   - With C++ development tools

3. **Git**
   - For version control

## Quick Start

### Step 1: Initialize Environment

Use the `setup-env` command to set up your development environment:

```
cline --setup-env
```

### Step 2: Create a New Project

Create a new Unreal Engine project:

```
cline --create-project
```

### Step 3: Build the Project

Build your project:

```
cline --build-project
```

## Understanding the Code Structure

### C++ Classes

All C++ classes are located in the `templates/` directory. These are designed to be added to your Unreal Engine project.

| Class              | Purpose                         |
| ------------------ | ------------------------------- |
| `ActorBase`        | Base class for all game actors  |
| `GameMode`         | Manages game rules and state    |
| `AIController`     | Controls non-player characters  |
| `ResistanceUnit`   | Player and enemy units          |
| `Weapon`           | Combat weapons                  |
| `Projectile`       | Projectiles for ranged attacks  |
| `HackingDevice`    | Hacking tools for disrupting AI |
| `UtilityFunctions` | Helper functions                |

### Blueprint Integration

All C++ classes include Blueprint integration, allowing you to:

- Extend C++ classes in Blueprint
- Call C++ functions from Blueprint
- Expose C++ properties to Blueprint

## Theme Elements

This workspace follows the "AI Overlords" theme:

- **Resistance Fighters**: Player characters
- **AI Overlords**: Enemy AI systems
- **Hacking Devices**: Special tools for disrupting AI
- **Scavenged Weapons**: Custom and modified weapons

## Next Steps

1. Explore the templates in `templates/`
2. Customize classes for your specific game
3. Create Blueprints from your C++ classes
4. Build your game world in Unreal Editor

## Getting Help

If you encounter issues:

1. Check Unreal Engine documentation
2. Review the template comments
3. Examine the included utility functions

## Quick Reference

### Common Operations

| Operation              | Command          |
| ---------------------- | ---------------- |
| Initialize environment | `setup-env`      |
| Create project         | `create-project` |
| Build project          | `build-project`  |

### Key Classes

| Class          | Location                     |
| -------------- | ---------------------------- |
| ActorBase      | `templates/ActorBase.*`      |
| GameMode       | `templates/GameMode.*`       |
| ResistanceUnit | `templates/ResistanceUnit.*` |
| Weapon         | `templates/Weapon.*`         |
| Projectile     | `templates/Projectile.*`     |
| HackingDevice  | `templates/HackingDevice.*`  |
